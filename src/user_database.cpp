//
// Created by Aryaman Parekh on 4/16/20.
//

#include "../include/mylibrary/user_database.h"
#include <sqlite3.h>
#include "sqlite3.h"
#include "../include/sqlite_modern_cpp.h"

using namespace sqlite;
using namespace std;

namespace mylibrary {

UserDatabase::UserDatabase(const string& db_path) : db{db_path} {
  db << "DROP TABLE user_information";
  db << "CREATE TABLE if not exists user_information (\n"
    "  username TEXT NOT NULL,\n"
    "  user_password TEXT NOT NULL,\n"
    "  is_student bool NOT NULL\n"
    ");";
  db << "CREATE TABLE if not exists grades (\n"
        "  username  TEXT NOT NULL,\n"
        "  grade integer NOT NULL,\n"
        "  quiz_code Integer NOT NULL,\n"
        "  max_score Integer NOT NULL\n"
        ");";
  cout << "table created"  << endl;
}

bool UserDatabase::CreateUsername(User user) {
  string bool_value;
  if (user.is_student) {
    bool_value = "true";
  } else {
    bool_value = "false";
  }
  string query_to_execute = "INSERT INTO user_information (username, user_password, is_student) VALUES(\""
                            + user.name + "\", \"" + user.password + "\", " + bool_value + ");";
  db << query_to_execute;
}

string UserDatabase::GetUserPassword(string username) {
  string to_return;
  db << "Select user_password from user_information where username = \"" +
      username + "\";" >> to_return;
  return to_return;
}

void UserDatabase::UpdateGrades(User user, Quiz quiz, int user_score) {
  string query =  "Insert into grades (username, grade, quiz_code, max_score) Values (\"" +
      user.name + "\", " + to_string(user_score) + ", " + to_string(quiz.quizcode)
      + ", " + to_string(quiz.maxscore) + ");";
  db << query;
}

int UserDatabase::GetUserGrade(User user, Quiz quiz) {
  int to_return;
  db << "Select grade from grades where username = \"" +
        user.name + "\" AND quiz_code = " + to_string(quiz.quizcode) + " ;" >> to_return;
  return to_return;
}

}