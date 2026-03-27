#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.cpp"



using namespace Catch::Benchmark::Detail;



TEST(optimized_away_error_Test_983, InheritsFromStdException_983) {

    optimized_away_error error;

    EXPECT_TRUE(dynamic_cast<const std::exception*>(&error) != nullptr);

}



TEST(optimized_away_error_Test_983, WhatMethodReturnsExpectedMessage_983) {

    optimized_away_error error;

    EXPECT_STREQ(error.what(), "could not measure benchmark, maybe it was optimized away");

}
