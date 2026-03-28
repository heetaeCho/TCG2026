#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/exceptions.h"



using namespace YAML;

using namespace ErrorMsg;



TEST(BAD_SUBSCRIPT_WITH_KEY_Test_88, NumericKey_ReturnsCorrectMessage_88) {

    int key = 42;

    std::string expected_message = BAD_SUBSCRIPT + " (key: \"42\")";

    EXPECT_EQ(BAD_SUBSCRIPT_WITH_KEY(key), expected_message);

}



TEST(BAD_SUBSCRIPT_WITH_KEY_Test_88, ZeroKey_ReturnsCorrectMessage_88) {

    int key = 0;

    std::string expected_message = BAD_SUBSCRIPT + " (key: \"0\")";

    EXPECT_EQ(BAD_SUBSCRIPT_WITH_KEY(key), expected_message);

}



TEST(BAD_SUBSCRIPT_WITH_KEY_Test_88, NegativeKey_ReturnsCorrectMessage_88) {

    int key = -1;

    std::string expected_message = BAD_SUBSCRIPT + " (key: \"-1\")";

    EXPECT_EQ(BAD_SUBSCRIPT_WITH_KEY(key), expected_message);

}



TEST(BAD_SUBSCRIPT_WITH_KEY_Test_88, LargeKey_ReturnsCorrectMessage_88) {

    int key = 999999;

    std::string expected_message = BAD_SUBSCRIPT + " (key: \"999999\")";

    EXPECT_EQ(BAD_SUBSCRIPT_WITH_KEY(key), expected_message);

}
