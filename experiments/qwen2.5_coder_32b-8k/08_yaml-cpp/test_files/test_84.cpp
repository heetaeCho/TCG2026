#include <gtest/gtest.h>

#include "yaml-cpp/exceptions.h"



using namespace YAML;

using namespace ErrorMsg;



class ExceptionMsgTest_84 : public ::testing::Test {

protected:

    void SetUp() override {}

};



TEST_F(ExceptionMsgTest_84, KeyNotFoundWithNumericKey_84) {

    int key = 123;

    std::string expectedMessage = KEY_NOT_FOUND ": " + std::to_string(key);

    EXPECT_EQ(KEY_NOT_FOUND_WITH_KEY(key), expectedMessage);

}



TEST_F(ExceptionMsgTest_84, KeyNotFoundWithZeroKey_84) {

    int key = 0;

    std::string expectedMessage = KEY_NOT_FOUND ": " + std::to_string(key);

    EXPECT_EQ(KEY_NOT_FOUND_WITH_KEY(key), expectedMessage);

}



TEST_F(ExceptionMsgTest_84, KeyNotFoundWithNegativeKey_84) {

    int key = -123;

    std::string expectedMessage = KEY_NOT_FOUND ": " + std::to_string(key);

    EXPECT_EQ(KEY_NOT_FOUND_WITH_KEY(key), expectedMessage);

}
