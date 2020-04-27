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

  struct QuizDetails {
    string quiz_info;
    int quizcode;
    int maxscore;
    string quiz_path;
    string quiz_creator;
  };

  struct GradeDetails {
    string username;
    int grade;
    int quizcode;
    int max_score;
  };

  class UserDatabase {
   private:
    sqlite::database db;

   public:

    /**
     * Loads the database AND creates user_information, grades, quiz tables
     * @param db_path The path of sqlite database
     */
    explicit UserDatabase(const std::string& db_path);

    /**
     *Creates a new user and stores the information in user_information
     * @param user
     * @return The boolean value of if the query was executed succesfully
     */
    bool CreateUser(User user);

    /**
     * Inserts the grade details in the grades table
     * @param details The details which need to be inserted
     * @return The boolean value of whether the query was executed succesfully
     */
    bool InsertGrades(GradeDetails details);

    /**
     * Insert the quiz in the quiz sql table
     * @param quiz which needs to be inserted in the table
     * @return
     */
    bool InsertQuiz(QuizDetails quiz);

    /**
     * Returns the password stored for the user in the database
     * @param username - The username for which you require the password
     * @param evaluated_correctly  - Whether the query was executed succesfully
     * and the correct password was returned
     * @param is_student - If the user is a student or not
     * @return The passoword
     */
    string GetUserPassword(string username, bool &evaluated_correctly, bool &is_student);

    /**
     * Returns the path for the json file which contains the quiz
     * @param quiz_code The quiz_code of the quiz whose path you require
     * @param evaluated_correctly Boolean value of if the query was executed
     * succesfully
     * @return The oath of the quiz
     */
    string GetQuizPath(int quiz_code,  bool &evaluated_correctly);

    /**
     * Exports the grades for a certain quiz to the path of the given CSV file
     * @param path The path of the csv file
     * @param quiz_code for the quiz whose grades you require.
     * @return The boolean value of if the grades were exported succesfully.
     */
    bool ExportGrades(string path, int quiz_code);
  };
}


#endif  // FINALPROJECT_USER_DATABASE_H
