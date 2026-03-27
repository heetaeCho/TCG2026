#include <gtest/gtest.h>

#include "yaml-cpp/exceptions.h"

#include <string>



class ExceptionMsgTest_86 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if necessary

};



TEST_F(ExceptionMsgTest_86, BAD_SUBSCRIPT_WITH_KEY_NormalOperation_86) {

    std::string key = "testKey";

    std::string expectedMessage = "operator[] call on a scalar (key: \"testKey\")";

    EXPECT_EQ(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key), expectedMessage);

}



TEST_F(ExceptionMsgTest_86, BAD_SUBSCRIPT_WITH_KEY_EmptyKey_86) {

    std::string key = "";

    std::string expectedMessage = "operator[] call on a scalar (key: \"\")";

    EXPECT_EQ(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key), expectedMessage);

}



TEST_F(ExceptionMsgTest_86, BAD_SUBSCRIPT_WITH_KEY_SpecialCharactersKey_86) {

    std::string key = "!@#$%^&*()";

    std::string expectedMessage = "operator[] call on a scalar (key: \"!@#$%^&*()\")";

    EXPECT_EQ(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key), expectedMessage);

}
