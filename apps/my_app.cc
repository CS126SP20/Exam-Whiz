// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include "mylibrary/user_database.h"

namespace myapp {

using cinder::app::KeyEvent;
using namespace std;

MyApp::MyApp() { }

void MyApp::setup() {
  mylibrary::UserDatabase a{cinder::app::getAssetPath("database.db").string()};
  mylibrary::User user;
  user.name = "Aryaman";
  user.password = "AAAA";
  user.is_student = true;
  a.CreateUsername(user);
  std::cout << a.GetUserPassword(user.name) << endl;
  mylibrary::Quiz q;
  q.quizcode = 1;
  q.maxscore = 100;
  a.UpdateGrades(user, q, 100);
  std::cout << a.GetUserGrade(user, q) << endl;
}

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
