//
// Created by Aryaman Parekh on 4/16/20.
//

#include "../include/mylibrary/user_database.h"

#include <sqlite3.h>

#include "../../../blocks/Cinder-ImGui/lib/imgui/imgui.h"
#include "../include/sqlite_modern_cpp.h"
#include "sqlite3.h"

using namespace sqlite;
using namespace std;

namespace mylibrary {

UserDatabase::UserDatabase(const string& db_path) : db{db_path} {
  //Creates three defult tables in the database
  db << "CREATE TABLE if not exists user_information (\n"
    "  username TEXT NOT NULL Primary Key,\n"
    "  user_password TEXT NOT NULL,\n"
    "  is_student bool NOT NULL\n"
    ");";
  db << "CREATE TABLE if not exists grades (\n"
        "  username  TEXT NOT NULL,\n"
        "  grade integer NOT NULL,\n"
        "  quiz_code Integer NOT NULL,\n"
        "  max_score Integer NOT NULL\n"
        ");";

  db << "CREATE TABLE if not exists quiz (\n"
        "  quiz_code  Integer NOT NULL Primary Key,\n"
        "  quiz_path TEXT NOT NULL,\n"
        " quiz_creator TEXT Not Null \n"
        ");";

}

bool UserDatabase::CreateUser(User user) {
  try {
    string bool_value;
    if (user.is_student) {
      bool_value = "true";
    } else {
      bool_value = "false";
    }
    string query_to_execute = "INSERT INTO user_information (username, user_password, is_student) VALUES(\""
                              + user.name + "\", \"" + user.password + "\", " + bool_value + ");";
    db << query_to_execute;
    return true;
  } catch (exception e) {
    cout << e.what();
    return false;
  }
}

bool UserDatabase::InsertGrades(GradeDetails details) {
    string query_to_execute = "INSERT INTO grades (username, grade, quiz_code, max_score) VALUES(\""
                              + details.username + "\", " + to_string(details.grade) + ", " + to_string(details.quizcode) + ", " + to_string(details.max_score)  + ");";
    db << query_to_execute;
    return true;

}

bool UserDatabase::InsertQuiz(QuizDetails quiz) {
  try {
    string query_to_execute = "INSERT INTO quiz (quiz_code, quiz_path, quiz_creator) VALUES("
                              + to_string(quiz.quizcode) + ", \"" + quiz.quiz_path + "\", \"" + quiz.quiz_creator + "\");";
    db << query_to_execute;
    return true;
  } catch (exception e) {
    return false;
  }
}


string UserDatabase::GetUserPassword(string username, bool &evaluated_correctly,
                                     bool &is_student) {
  string to_return;
  try {
    db << "Select user_password from user_information where username = \"" +
          username + "\";" >> to_return;
    db << "Select is_student from user_information where username = \"" +
          username + "\";" >> is_student;
    evaluated_correctly = true;
    return to_return;
  } catch (exception e) {
    evaluated_correctly = false;
    if (e.what() == "sqlite::errors::no_rows") {
      cout << "yes";
    }
    return "-1";
  }

}

string UserDatabase::GetQuizPath(int quiz_code,  bool &evaluated_correctly) {
  string to_return;
  try {
    db << "Select quiz_path from quiz where quiz_code = " +
          to_string(quiz_code) + ";" >> to_return;
    evaluated_correctly = true;
    return to_return;
  } catch (exception e) {
    evaluated_correctly = false;
    if (e.what() == "sqlite::errors::no_rows") {
      cout << "yes";
    }
    return "-1";
  }
}

int UserDatabase::GetQuizAttempt(int quiz_code, User current_user_) {
  try {
    int to_return = 0;
    string query = "Select count(*) from grades where username = \"" +
                   current_user_.name +
                   "\" and quiz_code = " + to_string(quiz_code) + ";";
    db << query >> to_return;
    return to_return;
  } catch (exception e) {
    return -1;
  }
}


bool UserDatabase::ExportGrades(string path, int quiz_code) {
  try {
    string query = "SELECT * from grades;";
    sqlite::database_binder rows = db << query;
    return true;
  } catch (exception e) {
    return false;
  }


  return true;
}

}