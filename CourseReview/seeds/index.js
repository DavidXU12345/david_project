const mongoose = require('mongoose');
const { places, descriptors } = require('./seedHelpers');
const Course = require('../models/course');

mongoose.connect('mongodb://localhost:27017/course-review', {
    useNewUrlParser: true,
    useCreateIndex: true,
    useUnifiedTopology: true
});

const db = mongoose.connection;

db.on("error", console.error.bind(console, "connection error:"));
db.once("open", () => {
    console.log("Database connected");
});

const sample = array => array[Math.floor(Math.random() * array.length)];


const seedDB = async () => {
    await Course.deleteMany({});
    for (let i = 0; i < 200; i++) {
        const random1000 = Math.floor(Math.random() * 1000);
        const course = new Course({
            author: '608e1a23f7065e429cd4fa93',
            teacher: 'David XU',
            title: `${sample(descriptors)} ${sample(places)}`,
            description: 'Lorem ipsum dolor sit amet consectetur, adipisicing elit. Odio perferendis aliquid saepe distinctio dicta autem quaerat et neque doloremque, tempora repellat eum culpa, quod consequatur mollitia maxime in consectetur dolor.',
            images: [
                  {
                    url: 'https://res.cloudinary.com/dzudoox2j/image/upload/v1619795104/YelpCamp/crwbsbqv3a5dhxjtbgkt.jpg',
                    filename: 'YelpCamp/crwbsbqv3a5dhxjtbgkt'
                  },
                  {
                    url: 'https://res.cloudinary.com/dzudoox2j/image/upload/v1619795101/YelpCamp/hlfdloalzvc9ebi4uluu.jpg',
                    filename: 'YelpCamp/hlfdloalzvc9ebi4uluu'
                  }   
            ]
        })
        await course.save();
    }
}

seedDB().then(() => {
    mongoose.connection.close();
})