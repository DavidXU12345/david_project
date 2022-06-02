const express = require('express');
const router = express.Router();
const courses = require('../controllers/courses');
const catchAsync = require('../utils/catchAsync');
const Course = require('../models/course');
const { isLoggedIn, isAuthor, validateCourse } = require('../middleware.js');
const multer = require('multer');
const {storage} = require('../cloudinary');
const upload = multer({ storage });

router.route('/')
    .get(catchAsync(courses.index))
    .post(isLoggedIn, upload.array('image'), validateCourse,  catchAsync(courses.createCourse));

router.get('/new', isLoggedIn, courses.renderNewForm);

router.route('/:id')
    .get(catchAsync(courses.showCourse))
    .put(isLoggedIn, isAuthor, upload.array('image'), validateCourse, catchAsync(courses.updateCourse))
    .delete(isLoggedIn, isAuthor, catchAsync(courses.deleteCourse));

router.get('/:id/edit', isLoggedIn, isAuthor, catchAsync(courses.renderEditForm));


module.exports = router;