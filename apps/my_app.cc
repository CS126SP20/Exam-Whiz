// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <CinderImGui.h>
#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <imgui.h>

#include "mylibrary/quiz.h"
#include "mylibrary/user_database.h"

namespace myapp {

using cinder::app::KeyEvent;
using namespace std;
using namespace ImGui;
using namespace cinder;

bool login_page = true;
bool quiz_page = true;
bool quiz_started = true;
bool teacher_home_screen = true;

MyApp::MyApp() { }

void MyApp::setup() {
  //current_user_->is_student = true;
  setFullScreen(true);
  //Initializes the Buffer fields
  strcpy(login_name_, empty_string.c_str());
  strcpy(login_password_, empty_string.c_str());
  strcpy(signup_name_, empty_string.c_str());
  strcpy(signup_password_, empty_string.c_str());
  strcpy(signup_username_, empty_string.c_str());
  strcpy(input_json_path_, empty_string.c_str());
  strcpy(input_csv_path_, empty_string.c_str());

  *quiz_code = 0;
  *exported_quiz_code = 0;

  string product_sans_path = "/Users/aryamanparekh/Downloads/Cinder/projects/final-project-aparekh5/assets/product-sans/Product Sans Bold.ttf";
  //std::vector<ImWchar> range
  ui::initialize(ui::Options().font( product_sans_path, 24));

  //ui::GetFont()->Glyphs.push_back(a);

  //ui::Set
}

void MyApp::update() { }

void MyApp::draw() {
  int y_offset = -30;
  ImVec2 screen_size(getWindowSize().x, (getWindowSize().y - (2 * y_offset)));
  ui::SetNextWindowSize(screen_size);
  ui::SetNextWindowPos(ImVec2(0, y_offset));
  cinder::gl::clear( Color( 0, 0, 0 ) );
  if (login_page) {
    DrawLoginPage();
  } else if (quiz_page && current_user_.is_student) {
    DrawQuizCodePage();
  } else if (quiz_started && current_user_.is_student){
    DrawQuizPage();
  } else if (!current_user_.is_student && teacher_home_screen) {
    DrawTeacherHomescreen();
  }

  //ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
  //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
}

void MyApp::DrawTeacherHomescreen() {
  ui::Text("Please enter the absolute path for the json file your quiz");
  ui::NewLine();
  ui::InputText("##jsonpath", input_json_path_, 200);
  ui::NewLine();
  ui::Text("Please enter the quiz_code for your quiz : ");
  ui::SameLine();
  ui::InputInt("##quizcode", quiz_code);
  ui::NewLine();
  if (ui::Button("Create Quiz")) {
    AddQuiz();
  }
  ui::NewLine();

  ui::Text("Please enter the quizcode for the quiz whose data you want to export");
  ui::NewLine();
  ui::InputInt("##exportquizcode", exported_quiz_code);
  ui::NewLine();
  ui::Text("Please enter the absolute path for the csv file where you want to export the grades");
  ui::NewLine();
  ui::InputText("##csvfile", input_csv_path_, 200);
  ui::NewLine();
  if (ui::Button("Export Data")) {
    if (database.ExportGrades(input_csv_path_, *exported_quiz_code)) {
      message_ = "Grades Exported Succesfully";
    } else {
      message_ = "The path given is invalid";
    }
  }
  ui::Text(message_.c_str());
}

void MyApp::AddQuiz() {
  bool evaluated_correctly = false;
  mylibrary::QuizDetails new_quiz;
  new_quiz.quiz_creator = current_user_.name;
  new_quiz.quiz_path = input_json_path_;
  new_quiz.quizcode = *quiz_code;
  mylibrary::Quiz quiz1(input_json_path_, evaluated_correctly);
  if (evaluated_correctly) {
    evaluated_correctly = database.InsertQuiz(new_quiz);
    if (evaluated_correctly) {
      //teacher_home_screen = false;
      message_ = "Quiz was added succesfully. The quiz code/ is " + to_string(*quiz_code);
    } else {
      message_ = "The quiz code has already been used please try again with another quizcode";
    }
  } else {
    message_ = "The JSON format of the given quiz is not valid or the file does not exist";
  }
}

void MyApp::DrawLoginPage() {
  //Prints the general instructions for the end user
  ui::BeginGroup();
  ui::Text( "Welcome to Testing System" );
  ui::Text( "If you are a returning user please login." );
  ui::Text( "If you are not a returning user please signup" );
  ui::Text("Please not that username and password are case sensitive");
  ui::EndGroup();

  ui::NewLine();

  ui::BeginGroup();
  ui::Text( "Username : " );
  ui::SameLine();
  ui::InputText("##username" , login_name_, 30);
  ui::NewLine();
  ui::Text( "Password : " );
  ui::SameLine();
  ui::InputText("##password",login_password_,30,ImGuiInputTextFlags_Password);
  ui::NewLine();

  if (ui::Button("Login")) {
    Login();
  }
  ui::EndGroup();

  ui::BeginGroup();
  //Displays the Sign Up part of the page
  ui::NewLine();
  ui::Text("Signup Page: ");
  ui::NewLine();
  ui::Text("Name:  ");
  ui::SameLine();
  ui::InputText("##FullName" ,signup_name_, 30);
  ui::NewLine();
  ui::Text("Username:  ");
  ui::SameLine();
  ui::InputText(" Username should not have any spaces " ,signup_username_, 30);
  ui::NewLine();
  ui::Text("Password:  ");
  ui::SameLine();
  ui::InputText("##signup_password" ,signup_password_, 30);
  ui::RadioButton("Are you a student", &user_type, 1);
  ui::SameLine();
  ui::RadioButton("Are you a Teacher", &user_type, 2);

  ui::NewLine();
  if (ui::Button("Signup and Login")) {
    SignUp();
  }
  ui::EndGroup();

  //Displays the error message to the user if their is one
  ui::NewLine();
  ui::NewLine();
  ui::Text(message_.c_str());

}

void MyApp::Login() {

  bool evaluated_correctly_ = false;
  bool is_student = true;
  string actual_password = database.GetUserPassword(login_name_, evaluated_correctly_, is_student);
  string given_password = login_password_;
  if ((!evaluated_correctly_) || actual_password.compare(given_password) != 0) {
    message_ = "The Given Password is incorrect or the Username does not Exist";
    return;
  }
  mylibrary::User user;
  user.name = login_name_;
  user.is_student = is_student;

  user.password = login_password_;
  LoginSuccesfull(user);

}

void MyApp::SignUp() {
  mylibrary::User user;
  if (user_type == 2)  {
    user.is_student = false;
  } else {
    user.is_student = true;
  }
  user.password = signup_password_;
  user.name = signup_username_;
  if (!database.CreateUser(user)) {
    message_ = "The username has already been taken";
    return;
  }
  LoginSuccesfull(user);
}

void MyApp::DrawQuizCodePage() {
  ui::Text("Please enter the quiz code");
  ui::SameLine();
  ui::InputInt("##quizcode", quiz_code);
  if (ui::Button("Start Quiz")) {
    SetupQuiz();
  }
  ui::NewLine();
  ui::Text(message_.c_str());

}

void MyApp::DrawQuizPage() {
  ui::Text(quiz.quiz_details.quiz_info.c_str());
  for (int question_num = 0; question_num < quiz.questions.size(); question_num++) {
    mylibrary::Question question = quiz.questions[question_num];
    ui::NewLine();
    ui::Text(question.question.c_str());
    if (question.is_mcq) {
      for (int option_num = 0; option_num < question.options.size(); option_num++) {
        string label = question.options[option_num] + "##" + to_string(option_num) + to_string(question_num);
        ui::RadioButton(label.c_str(), &answers[question_num], option_num);
      }
    } else {
      string label = "##" + to_string(question_num);
      ui:InputText(label.c_str(), temp_answer, 30);
      text_answers[question_num] = temp_answer;
    }
    ui::NewLine();
  }
  ui::NewLine();
  if (ui::Button("Submit Quiz")) {
    EvaluateQuiz();
  }
  ui::NewLine();
  ui::NewLine();
}

void MyApp::EvaluateQuiz() {
  int score = 0;
  for (int question_num = 0; question_num < quiz.questions.size(); question_num++) {
    if (quiz.questions[question_num].is_mcq) {
      if (answers[question_num] == quiz.questions[question_num].correct_option) {
        score += quiz.questions[question_num].max_marks;
      }
    } else {
      string answer = text_answers[question_num];
      if (answer.compare(quiz.questions[question_num].correct_answer) == 0) {
        score += quiz.questions[question_num].max_marks;
      }
    }
  }
  mylibrary::GradeDetails grade_details;
  grade_details.username = current_user_.name;
  grade_details.quizcode = quiz.quiz_details.quizcode;
  grade_details.max_score = quiz.quiz_details.maxscore;
  grade_details.grade = score;
  database.InsertGrades(grade_details);
  cout << score << endl;
  quiz_started = false;
}


void MyApp::SetupQuiz() {
  bool evaluated_correctly = false;
  string quiz_path = database.GetQuizPath(*quiz_code, evaluated_correctly);
  if (evaluated_correctly) {
    quiz.LoadQuiz(quiz_path.c_str(), evaluated_correctly);
  } else {
    message_ = "The quiz code you have entered is incorrect";
    return;
  }
  for (mylibrary::Question question : quiz.questions) {
    answers.push_back(-1);
    text_answers.push_back("");
  }
  quiz_page = false;

}

void MyApp::LoginSuccesfull(mylibrary::User user) {
  login_page = false;
  current_user_ = user;
  message_ = "";
}
MyApp::~MyApp() {
  delete quiz_code;
  delete exported_quiz_code;
}

}  // namespace myapp
