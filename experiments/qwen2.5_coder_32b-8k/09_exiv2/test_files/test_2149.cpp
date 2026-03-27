#include <gtest/gtest.h>

#include "exiv2/error.hpp"



namespace {



TEST(ErrorTest_2149, ConstructorWithErrorCode_2149) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral);

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

}



TEST(ErrorTest_2149, ConstructorWithErrorCodeAndArg1_2149) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "Argument 1");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

    EXPECT_STREQ(strstr(error.what(), "Argument 1"), "Argument 1");

}



TEST(ErrorTest_2149, ConstructorWithErrorCodeAndTwoArgs_2149) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "Argument 1", "Argument 2");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

    EXPECT_STREQ(strstr(error.what(), "Argument 1"), "Argument 1");

    EXPECT_STREQ(strstr(error.what(), "Argument 2"), "Argument 2");

}



TEST(ErrorTest_2149, ConstructorWithErrorCodeAndThreeArgs_2149) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "Argument 1", "Argument 2", "Argument 3");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

    EXPECT_STREQ(strstr(error.what(), "Argument 1"), "Argument 1");

    EXPECT_STREQ(strstr(error.what(), "Argument 2"), "Argument 2");

    EXPECT_STREQ(strstr(error.what(), "Argument 3"), "Argument 3");

}



TEST(ErrorTest_2149, WhatMethodReturnsNonEmptyString_2149) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral);

    EXPECT_STRNE(error.what(), "");

}



TEST(ErrorTest_2149, ErrorCodeIsAccessible_2149) {

    Exiv2::Error error(Exiv2::ErrorCode::kerFileNotFound);

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerFileNotFound);

}



}  // namespace
