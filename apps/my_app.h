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

  /**
   * Initializes all the variables to a default value
   */
  void setup() override;
  void update() override;

  /**
   * Manages which page needs to be drawn
   */
  void draw() override;

  /**
   * Draws the login and signup page
   */
  void DrawLoginPage();

  /**
   * Checks if the user exists and his password is correct
   */
  void Login();

  /**
   * Creates a new user and pass the info to the database
   */
  void SignUp();

  /**
   * Gets the path for the quiz which the user plans to take
   */
  void SetupQuiz();

  /**
   * Checks if the user exists and the password is correct
   * @param user
   */
  void LoginSuccesfull(mylibrary::User user);

  /**
   * Draw the page where user can decide which quiz he plans to take
   */
  void DrawQuizCodePage();

  /**
   * Draw the page where the user can take the quiz
   */
  void DrawQuizPage();

  /**
   * Draws the UI for the homescreen for an instructor
   */
  void DrawTeacherHomescreen();

  /**
   * Calculates the total marks for the user in the quiz
   */
  void EvaluateQuiz();

  /**
   * Adds the quiz_details to the database
   */
  void AddQuiz();




  };

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
