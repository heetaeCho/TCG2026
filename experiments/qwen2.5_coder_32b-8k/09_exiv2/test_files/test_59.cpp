#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/error.hpp"



namespace {



using ::testing::HasSubstr;



TEST(ErrorTest_59, ConstructorWithCodeOnly_59) {

    Exiv2::Error error(Exiv2::ErrorCode::kerInvalidMetadata);

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerInvalidMetadata);

}



TEST(ErrorTest_59, ConstructorWithOneArgument_59) {

    Exiv2::Error error(Exiv2::ErrorCode::kerInvalidMetadata, "arg1");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerInvalidMetadata);

    EXPECT_THAT(std::string(error.what()), HasSubstr("arg1"));

}



TEST(ErrorTest_59, ConstructorWithTwoArguments_59) {

    Exiv2::Error error(Exiv2::ErrorCode::kerInvalidMetadata, "arg1", "arg2");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerInvalidMetadata);

    EXPECT_THAT(std::string(error.what()), HasSubstr("arg1"));

    EXPECT_THAT(std::string(error.what()), HasSubstr("arg2"));

}



TEST(ErrorTest_59, ConstructorWithThreeArguments_59) {

    Exiv2::Error error(Exiv2::ErrorCode::kerInvalidMetadata, "arg1", "arg2", "arg3");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerInvalidMetadata);

    EXPECT_THAT(std::string(error.what()), HasSubstr("arg1"));

    EXPECT_THAT(std::string(error.what()), HasSubstr("arg2"));

    EXPECT_THAT(std::string(error.what()), HasSubstr("arg3"));

}



TEST(ErrorTest_59, WhatMethodReturnsNonEmptyString_59) {

    Exiv2::Error error(Exiv2::ErrorCode::kerInvalidMetadata);

    EXPECT_FALSE(std::string(error.what()).empty());

}



}  // namespace
