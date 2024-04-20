const express = require('express');
const passport = require('passport');
const LocalStrategy = require('passport-local').Strategy;
const session = require('express-session');
const bodyParser = require('body-parser');

const app = express();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

app.use(session({
    secret: 'secret',
    resave: false,
    saveUninitialized: false
}));

app.use(passport.initialize());
app.use(passport.session());

const users = [
    { id: 1, username: 'user1', password: 'password1', role: 'user' },
    { id: 2, username: 'admin', password: 'adminpassword1', role: 'admin' }
];

passport.serializeUser((user, done) => {
    done(null, user.id);
});

passport.deserializeUser((id, done) => {
    const user = users.find(user => user.id === id);
    done(null, user);
});

passport.use(new LocalStrategy((username, password, done) => {
    const user = users.find(user => user.username === username && user.password === password);
    if (user) {
        return done(null, user);
    } else {
        return done(null, false, { message: 'Incorrect Username Or Password' });
    }
}));

const isAuthenticated = (req, res, next) => {
    if (req.isAuthenticated()) {
        return next();
    } else {
        res.redirect('/login');
    }
};

app.post('/login',
    passport.authenticate('local', {
        successRedirect: '/profile',
        failureRedirect: '/login',
        failureFlash: true
    })
);

app.get('/logout', (req, res) => {
    req.logout();
    res.redirect('/');
});

app.get('/profile', isAuthenticated, (req, res) => {
    res.send(`Welcome ${req.user.username}, Your role is ${req.user.role}`);
});

app.get('/login', (req, res) => {
    res.send('Login Page');
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server Is Running On Port ${PORT}`);
});
