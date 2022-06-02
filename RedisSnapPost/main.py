from datetime import timedelta

import redis
from flask import Flask, render_template, request, flash

app = Flask(__name__)
r = redis.Redis('192.168.99.100')
app.secret_key = "secret_key"
last_id = 0


@app.route("/", methods=["GET", "POST"])
def home():
    if request.method == "POST":
        global last_id
        req = request.form
        name = req["full_name"]
        post = req["data"]
        expiry_minutes = int(req["expiry_minutes"])
        last = r.get("last_id")
        if last is None:
            last_id = 1
        else:
            last_id = int(last)
            last_id += 1

        pipeline = r.pipeline()
        if expiry_minutes > 0:
            pipeline.setex(f"news:name:{last_id}", timedelta(minutes=expiry_minutes), value=name)
            pipeline.setex(f"news:post:{last_id}", timedelta(minutes=expiry_minutes), value=post)
        else:
            pipeline.set(f"news:name:{last_id}", name)
            pipeline.set(f"news:post:{last_id}", post)
        pipeline.set("last_id", last_id) # keep tracking of last_id of the user
        pipeline.lpush("post_id", last_id)  # linked list is in order
        pipeline.execute()

        flash("Successfully submitted the post", category='success')

    return render_template("home.html")


@app.route("/all")
def all_post():
    post_ids = r.lrange("post_id", 0, -1)
    posts = dict()

    for post_id in post_ids:
        if r.exists(f"news:name:{post_id.decode('utf-8')}"):
            name_byte = r.get(f"news:name:{post_id.decode('utf-8')}")
            name = name_byte.decode('utf-8')

            post_byte = r.get(f"news:post:{post_id.decode('utf-8')}")
            post_data = post_byte.decode('utf-8')

            posts[name] = post_data
        else:
            r.lrem("post_id", 1, post_id)
    return render_template("all.html", posts=posts)
        

@app.route("/latest")
def latest_post():
    post_ids = r.lrange("post_id", 0, 2)
    posts = dict()

    for post_id in post_ids:
        if r.exists(f"news:name:{post_id.decode('utf-8')}"):
            name_byte = r.get(f"news:name:{post_id.decode('utf-8')}")
            name = name_byte.decode('utf-8')

            post_byte = r.get(f"news:post:{post_id.decode('utf-8')}")
            post_data = post_byte.decode('utf-8')

            posts[name] = post_data
        else:
            r.lrem("post_id", 1, post_id)
    return render_template("latest.html", posts=posts)


if __name__ == "__main__":
    app.run()
