# david_project

All of my personal projects are saved here for your reference.

## 1. HSI Prediction
I applied KNN algorithm to predict Hang Seng Index trend by using features "Open-Close" and "High-Low" and picked up k=15 which is the optimal parameter. By using back test, this simple "buy low, sell high" trading strategy can give me over 30% extra return compared to Hang Seng Index itself for past three years.

## 2. KNN Classifier
It is a school project (MSc Data Science at University of London). I wrote KNN algorithm to classify three classes of wines without using any machine learning Python packages. I also applied nested cross-validation to choose best number of neighbours and distance calculation method (Euclidean or Manhattan). I used confusion matrix, accuracy rate, precision and recall to evaluate the machine learning results.

## 3. Yahoo News Web Scrapping and Data Analysis
It is a school project (MSc Data Science at University of London). I used beautiful soup to get information from Yahoo news including news title, descriptions, source, time, links. I also applied sentiment analysis to give sentiment scores for each searching results and present them in a visualized way.

## 4. YelpCamp Web Development (Deployed using Heroku)
Website: https://yelpcampdavidxu.herokuapp.com/

Designed a YelpCamp website with full CRUD function where users can register, login and give scores and reviews to a specific campground 

**Front end**
- Applied *HTML, CSS, Bootstrap, Flexbox* and etc. to design this responsive website
- Used *mapbox API* to render the interactive map showing the campgrounds locations 

**Back end**
- **Routes:** Applied *node.js and express* to build campgrounds, reviews and users routes and render them using *ejs*
- **Database Management:** Built campground, review and user models using mongoose linked with *Mongo Atlas* and with validation schemas using *Joi* and self-coded middlewares
- **Images Upload and Storage:** Applied *Multer-Cloudinary package* and *Cloudinary* to allow users to upload multiple images and render those pictures in show page by getting image URL from Cloudinary
- **User Authentication and Authorization:** Applied *passport package and session* to hash password with salts and store it in *Mongo Atlas* and authenticate users. Authorize users by comparing the author information stored in MongoDB and current user information stored in session
- **Error Handling:** Handled Error by using *middlewares and ExpressErrors package*
- **Security:** Used *helmet, mongo-sanitize and sanitize-html* to prevent potential Mongo injection and cross site scripting
