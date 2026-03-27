#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/goo/gmem.h"



class GMemTest_18 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(GMemTest_18, CopyString_NormalOperation_18) {

    const char* input = "Hello";

    size_t n = 5;

    char* result = copyString(input, n);

    EXPECT_STREQ(result, "Hello");

    gfree(result);

}



TEST_F(GMemTest_18, CopyString_BoundaryCondition_EmptyString_18) {

    const char* input = "";

    size_t n = 0;

    char* result = copyString(input, n);

    EXPECT_STREQ(result, "");

    gfree(result);

}



TEST_F(GMemTest_18, CopyString_BoundaryCondition_MaxSize_18) {

    const char* input = "This is a test string that is quite long to check boundary conditions.";

    size_t n = strlen(input);

    char* result = copyString(input, n);

    EXPECT_STREQ(result, input);

    gfree(result);

}



TEST_F(GMemTest_18, CopyString_ErrorCase_NullInput_18) {

    const char* input = nullptr;

    size_t n = 5;

    // Assuming that passing a null pointer to copyString results in a nullptr return

    char* result = copyString(input, n);

    EXPECT_EQ(result, nullptr);

}



TEST_F(GMemTest_18, CopyString_ErrorCase_ZeroLength_18) {

    const char* input = "Hello";

    size_t n = 0;

    char* result = copyString(input, n);

    EXPECT_STREQ(result, "");

    gfree(result);

}
