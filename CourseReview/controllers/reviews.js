const Course = require('../models/course');
const Review = require('../models/review');

module.exports.createReview = async (req, res) => {
    const course = await Course.findById(req.params.id);
    const review = new Review(req.body.review);
    const today = new Date();
    const dateString = today.getFullYear()+'-'+(today.getMonth()+1)+'-'+today.getDate();
    review.date = dateString;
    review.author = req.user._id;
    course.reviews.push(review);
    await review.save();
    await course.save();
    req.flash('success', 'Created new review!')
    res.redirect(`/courses/${course._id}`)
};

module.exports.deleteReview = async (req, res) => {
    const {id, reviewId} = req.params;
    await Course.findByIdAndUpdate(id, {$pull: { reviews: reviewId }});
    await Review.findByIdAndDelete(req.params.reviewId);
    req.flash('success', 'Successfully deleted review');
    res.redirect(`/courses/${id}`);
};