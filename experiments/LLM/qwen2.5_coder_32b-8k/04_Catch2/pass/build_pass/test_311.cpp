#include <gtest/gtest.h>

#include "catch2/generators/catch_generator_exception.hpp"



class GeneratorExceptionTest_311 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(GeneratorExceptionTest_311, ConstructorSetsMessage_311) {

    const char* expected_message = "Test message";

    Catch::GeneratorException exception(expected_message);

    EXPECT_STREQ(exception.what(), expected_message);

}



TEST_F(GeneratorExceptionTest_311, WhatReturnsCorrectMessage_311) {

    const char* expected_message = "Another test message";

    Catch::GeneratorException exception(expected_message);

    EXPECT_STREQ(exception.what(), expected_message);

}



TEST_F(GeneratorExceptionTest_311, EmptyStringConstructor_311) {

    const char* expected_message = "";

    Catch::GeneratorException exception(expected_message);

    EXPECT_STREQ(exception.what(), expected_message);

}



TEST_F(GeneratorExceptionTest_311, NoThrowOnConstruction_311) {

    EXPECT_NO_THROW(Catch::GeneratorException("This should not throw"));

}
