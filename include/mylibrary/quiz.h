//
// Created by Aryaman Parekh on 4/17/20.
//

#ifndef FINALPROJECT_QUIZ_H
#define FINALPROJECT_QUIZ_H
#include "user_database.h"
#include <string>
#include <vector>

using namespace std;

namespace mylibrary {
  struct Question {
    string question;
    bool is_mcq;
    vector<string> options;
    int correct_option;
    string correct_answer;
    int max_marks;
  };
  class Quiz {
   private:

   public:
    Quiz() {}

    /**
    * Extracts the information from the json file and stores the information in
    * quiz_details and questions
    * @param json_path The path for the json file you want to extract info from
    * @param evaluated_correctly Boolean value of if the info was extracted correctly
     */
    Quiz(const char * json_path,  bool & evaluated_correctly);

   /**
    * Extracts the information from the json file and stores the information in
    * quiz_details and questions
    * @param json_path The path for the json file you want to extract info from
    * @param evaluated_correctly Boolean value of if the info was extracted correctly
    * @return
    */
    int LoadQuiz(const char *  json_path, bool & evaluated_correctly);
    QuizDetails quiz_details;
    vector<Question> questions;

  };

}


#endif  // FINALPROJECT_QUIZ_H
