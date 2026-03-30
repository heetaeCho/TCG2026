#include <gtest/gtest.h>

#include "exiv2/error.hpp"



namespace {



class Exiv2ErrorTest : public ::testing::Test {

protected:

    using ErrorCode = Exiv2::ErrorCode;

};



TEST_F(Exiv2ErrorTest_NormalOperation_2150, ConstructorWithCodeOnly_2150) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral);

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

}



TEST_F(Exiv2ErrorTest_NormalOperation_2150, ConstructorWithCodeAndOneArgument_2150) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "test");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

}



TEST_F(Exiv2ErrorTest_NormalOperation_2150, ConstructorWithCodeAndTwoArguments_2150) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "test1", "test2");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

}



TEST_F(Exiv2ErrorTest_BoundaryConditions_2150, ConstructorWithEmptyStrings_2150) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "", "");

    EXPECT_EQ(error.code(), Exiv2::ErrorCode::kerGeneral);

}



TEST_F(Exiv2ErrorTest_ExceptionalCases_2150, WhatMethodReturnsNonEmptyString_2150) {

    Exiv2::Error error(Exiv2::ErrorCode::kerGeneral, "test");

    EXPECT_FALSE(std::string(error.what()).empty());

}



}  // namespace
