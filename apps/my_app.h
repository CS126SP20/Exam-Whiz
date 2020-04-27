// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/quiz.h>
#include <mylibrary/user_database.h>

namespace myapp {

class MyApp : public cinder::app::App {
 private:
  int field_length_ = 30;
  int error_message_length = 120;
  //string * login_name_
  string empty_string = "";
  char input_json_path_[200];
  char input_csv_path_[200];

  char  login_name_[30];
  char login_password_[30];
  char  signup_name_[30];
  char  signup_password_[30];
  char  signup_username_[30];
  int  user_type = 1;
  int * quiz_code = new int;
  int * exported_quiz_code = new int;
  string  message_;
  mylibrary::User current_user_;
  ~MyApp();
  mylibrary::UserDatabase database{cinder::app::getAssetPath("database.db").string()};
  mylibrary::Quiz quiz;
  vector<int> answers;
  vector<string> text_answers;
  char temp_answer[30];
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void DrawLoginPage();
  void Login();
  void SignUp();
  void SetupQuiz();
  void LoginSuccesfull(mylibrary::User user);
  void DrawQuizCodePage();
  void DrawQuizPage();
  void DrawTeacherHomescreen();
  void EvaluateQuiz();
  void AddQuiz();




  };

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
