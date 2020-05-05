// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <mylibrary/user_database.h>
#include <mylibrary/quiz.h>

const string kTestKeyword = "test";

TEST_CASE("Quiz Json parsing", "[LoadQuiz][Quiz Constructor]") {
  string quiz_path = "/Users/aryamanparekh/Downloads/Cinder/projects/final-project-aparekh5/tests/assets/quiz.json";
  bool parsed_correctly;
  mylibrary::Quiz quiz(quiz_path.c_str(), parsed_correctly);

  SECTION("Quiz parsed correctly") {
    REQUIRE(parsed_correctly);
  }

  SECTION("Quiz Details parsed correctly") {
    REQUIRE(quiz.quiz_details.maxscore == 1);
    REQUIRE(quiz.quiz_details.quizcode == 1);
    REQUIRE(quiz.quiz_details.quiz_creator.compare(kTestKeyword) == 0);
    REQUIRE(quiz.quiz_details.quiz_info.compare(kTestKeyword) == 0);
  }

  SECTION("MCQ parsing") {
    mylibrary::Question question = quiz.questions[0];
    REQUIRE(question.question.compare("What is the capital of India ?") == 0);
    REQUIRE(question.correct_option == 2);
    REQUIRE(question.correct_answer.compare("Mumbai") == 0);
    REQUIRE(question.max_marks == 1);
    REQUIRE(question.is_mcq);
    REQUIRE(question.options[0].compare("Washington DC") == 0);
    REQUIRE(question.options[1].compare("New York") == 0);
    REQUIRE(question.options[2].compare("Delhi") == 0);
    REQUIRE(question.options[3].compare("Mumbai") == 0);
  }

  SECTION("Non MCQ parsing") {
    mylibrary::Question question = quiz.questions[1];
    REQUIRE(question.question.compare("Who is the founder of Apple ?") == 0);
    REQUIRE(question.correct_option == -1);
    REQUIRE(question.correct_answer.compare("Steve Jobs") == 0);
    REQUIRE(question.max_marks == 0);
    REQUIRE_FALSE(question.is_mcq);
  }
}

TEST_CASE("Checking the user_database class", "[CreateUser][InsertGrades]"
                                              "[InsertQuiz][GetUserPassword]"
                                              "[GetQuizPath][ExportGrades]"
                                              "[GetQuizAttempt]") {
  mylibrary::UserDatabase database("/Users/aryamanparekh/Downloads/Cinder/projects/final-project-aparekh5/tests/assets/test_database.db");
  SECTION("Create User and Get User Password") {
    mylibrary::User test_user;
    test_user.name = "test";
    test_user.password = "test";
    test_user.is_student = true;
    database.CreateUser(test_user);
    bool is_student = false;
    bool evaluated_correctly = false;
    string password = database.GetUserPassword(test_user.name, evaluated_correctly, is_student);
    REQUIRE(evaluated_correctly);
    REQUIRE(is_student);
    REQUIRE(test_user.password.compare(password) == 0);
  }

  SECTION("Insert Quiz and Get Quiz Path") {
    mylibrary::QuizDetails details;
    details.quiz_info = "test";
    details.quiz_creator = "test";
    details.quizcode = -1;
    details.maxscore = 100;
    details.quiz_path = "test";
    database.InsertQuiz(details);
    bool evaluated_correctly = false;
    string path = database.GetQuizPath(details.quizcode, evaluated_correctly);
    REQUIRE(evaluated_correctly);
    REQUIRE(path.compare(details.quiz_path) == 0);
  }

  SECTION("Insert Grades and GetQuizAttempt") {
    mylibrary::GradeDetails test_details;
    test_details.quizcode = 1;
    test_details.grade = 100;
    test_details.max_score = 100;
    test_details.username = "test";
    bool evaluated_correctly = database.InsertGrades(test_details);
    REQUIRE(evaluated_correctly);
    mylibrary::User test_user;
    test_user.name = "test";
    REQUIRE(database.GetQuizAttempt(1, test_user) == 1);
    test_user.name = "random";
    REQUIRE(database.GetQuizAttempt(0, test_user) == 0);
  }
}
// Copyright (c) 2020 CS126SP20. All rights reserved.
