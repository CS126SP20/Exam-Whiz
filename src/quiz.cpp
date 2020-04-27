//
// Created by Aryaman Parekh on 4/17/20.
//
#include "../include/mylibrary/quiz.h"

#include <fstream>
#include <iostream>
#include <istream>

#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/document.h"
#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/filereadstream.h"
#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/istreamwrapper.h"
#include "../include/rapidjson/rapidjson.h"
// for convenience
using namespace rapidjson;
namespace mylibrary {

  Quiz::Quiz(const char * json_path,  bool & evaluated_correctly) {

    LoadQuiz(json_path, evaluated_correctly);
  //  cout << d["quizcode"].GetInt() << endl;
  }

  int Quiz::LoadQuiz(const char *json_path, bool & evaluated_correctly) {
    try {
      ifstream ifs(json_path);
      IStreamWrapper isw(ifs);
      Document json_file;
      json_file.ParseStream(isw);
      this->quiz_details.quiz_creator = json_file["quizcreator"].GetString();
      this->quiz_details.quizcode = json_file["quizcode"].GetInt();
      this->quiz_details.maxscore = json_file["maxscore"].GetInt();
      this->quiz_details.quiz_info = json_file["quizinfo"].GetString();
      this->quiz_details.maxscore = json_file["maxscore"].GetInt();

      for (auto question = json_file["Questions"].GetArray().Begin(); question != json_file["Questions"].GetArray().End(); question++) {
        Question q;
        q.is_mcq = question->GetObject()["is_mcq"].GetBool();
        q.question = question->GetObject()["description"].GetString();
        q.correct_option = question->GetObject()["correct_option"].GetInt();
        q.correct_answer = question->GetObject()["correct_answer"].GetString();
        q.max_marks = question->GetObject()["max_marks"].GetInt();
        const Value& json_options = question->GetObject()["options"];
        for (SizeType option_num = 0; option_num < json_options.Size(); option_num++) {
          q.options.push_back(json_options[option_num].GetString());
        }

        this->questions.push_back(q);
      }
      evaluated_correctly = true;
      return 0;
    } catch(exception e) {
      evaluated_correctly = false;
      return -1;
    }

  }

}