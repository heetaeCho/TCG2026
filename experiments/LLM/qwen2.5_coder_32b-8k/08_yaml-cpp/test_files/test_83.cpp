#include <gtest/gtest.h>

#include <yaml-cpp/exceptions.h>



class ExceptionsTest_83 : public ::testing::Test {

protected:

    // Setup and teardown can be done here if necessary

};



TEST_F(ExceptionsTest_83, KeyNotFoundWithKey_ReturnsCorrectMessage_83) {

    const char* key = "test_key";

    std::string expected_message = "key not found: test_key";

    EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key), expected_message);

}



TEST_F(ExceptionsTest_83, KeyNotFoundWithKey_EmptyKey_ReturnsCorrectMessage_83) {

    const char* key = "";

    std::string expected_message = "key not found: ";

    EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key), expected_message);

}



TEST_F(ExceptionsTest_83, KeyNotFoundWithKey_NullKey_ReturnsCorrectMessage_83) {

    const char* key = nullptr;

    std::string expected_message = "key not found: (null)";

    EXPECT_EQ(YAML::ErrorMsg::KEY_NOT_FOUND_WITH_KEY(key), expected_message);

}
