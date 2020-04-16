//
// Created by Aryaman Parekh on 4/16/20.
//

#ifndef FINALPROJECT_USER_DATABASE_H
#define FINALPROJECT_USER_DATABASE_H
#include <string>;
#include "../include/sqlite_modern_cpp.h"

using namespace std;


namespace mylibrary {

  struct User {
    string name;
    string password;
    bool is_student;
  };

  struct Quiz {
    int quizcode;
    int maxscore;
  };

  class UserDatabase {
   private:
    sqlite::database db;

   public:
  explicit UserDatabase(const std::string& db_path);
   bool CreateUsername(User user);
   string GetUserPassword(string username);
    void UpdateGrades(User user, Quiz quiz, int user_score);
  int GetUserGrade(User user, Quiz quiz);
  };
}


#endif  // FINALPROJECT_USER_DATABASE_H
