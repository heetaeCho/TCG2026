#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/goo/gmem.h"

#include <cstring>



class GMemTest_17 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if necessary

    }



    void TearDown() override {

        // Teardown code, if necessary

    }

};



TEST_F(GMemTest_17, CopyString_ReturnsValidCopy_17) {

    const char* original = "Hello, World!";

    char* copy = copyString(original);

    EXPECT_STREQ(copy, original);

    delete[] copy;

}



TEST_F(GMemTest_17, CopyString_EmptyString_17) {

    const char* original = "";

    char* copy = copyString(original);

    EXPECT_STREQ(copy, original);

    delete[] copy;

}



TEST_F(GMemTest_17, CopyString_SingleCharacter_17) {

    const char* original = "A";

    char* copy = copyString(original);

    EXPECT_STREQ(copy, original);

    delete[] copy;

}



TEST_F(GMemTest_17, CopyString_LongString_17) {

    const char* original = "This is a longer string to test the copying functionality of copyString.";

    char* copy = copyString(original);

    EXPECT_STREQ(copy, original);

    delete[] copy;

}
