const mongoose = require('mongoose');
const cities = require('./cities');
const { places, descriptors } = require('./seedHelpers');
const Campground = require('../models/campground');

mongoose.connect('mongodb://localhost:27017/yelp-camp', {
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
    await Campground.deleteMany({});
    for (let i = 0; i < 200; i++) {
        const random1000 = Math.floor(Math.random() * 1000);
        const price = Math.floor(Math.random() * 20) + 10;
        const camp = new Campground({
            author: '608a51a02ccdaf26e4132fb9',
            location: `${cities[random1000].city}, ${cities[random1000].state}`,
            title: `${sample(descriptors)} ${sample(places)}`,
            description: 'dasdsajkfhsdjkhfla',
            price,
            geometry: { 
                type: 'Point', 
                coordinates: [ 
                    cities[random1000].longitude,
                    cities[random1000].latitude,
                ]  
            },
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
        await camp.save();
    }
}

seedDB().then(() => {
    mongoose.connection.close();
})