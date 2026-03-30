#include <gtest/gtest.h>

#include <yaml-cpp/exceptions.h>



class ExceptionsTest_82 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ExceptionsTest_82, KeyNotFoundWithKey_ReturnsCorrectMessage_82) {

    std::string key = "test_key";

    std::string expected_message = "key not found: test_key";

    EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key), expected_message);

}



TEST_F(ExceptionsTest_82, KeyNotFoundWithKey_EmptyKey_ReturnsCorrectMessage_82) {

    std::string key = "";

    std::string expected_message = "key not found: ";

    EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key), expected_message);

}



TEST_F(ExceptionsTest_82, KeyNotFoundWithKey_SpecialCharacters_ReturnsCorrectMessage_82) {

    std::string key = "!@#$%^&*()";

    std::string expected_message = "key not found: !@#$%^&*()";

    EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key), expected_message);

}
