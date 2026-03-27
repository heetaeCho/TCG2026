#include <gtest/gtest.h>

#include <yaml-cpp/exceptions.h>



class ExceptionMsgTest_87 : public ::testing::Test {

protected:

    // Additional setup can go here if needed.

};



TEST_F(ExceptionMsgTest_87, BAD_SUBSCRIPT_WITH_KEY_ReturnsCorrectString_87) {

    const char* key = "test_key";

    std::string expected = "operator[] call on a scalar (key: \"test_key\")";

    EXPECT_EQ(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key), expected);

}



TEST_F(ExceptionMsgTest_87, BAD_SUBSCRIPT_WITH_KEY_EmptyKey_ReturnsCorrectString_87) {

    const char* key = "";

    std::string expected = "operator[] call on a scalar (key: \"\")";

    EXPECT_EQ(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key), expected);

}



TEST_F(ExceptionMsgTest_87, BAD_SUBSCRIPT_WITH_KEY_NullKey_ReturnsCorrectString_87) {

    const char* key = nullptr;

    std::string expected = "operator[] call on a scalar (key: \"(null)\")";

    EXPECT_EQ(YAML::ErrorMsg::BAD_SUBSCRIPT_WITH_KEY(key), expected);

}
