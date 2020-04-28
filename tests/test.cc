// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/quiz.h>

const string kTestKeyword = "test";

TEST_CASE("Quiz Json parsing", "[random]") {
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
    REQUIRE(question.question.compare("What is the capital of India ?"));
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
    REQUIRE(question.question.compare("Who is the founder of Apple ?"));
    REQUIRE(question.correct_option == -1);
    REQUIRE(question.correct_answer.compare("Steve Jobs") == 0);
    REQUIRE(question.max_marks == 0);
    REQUIRE_FALSE(question.is_mcq);
  }
}