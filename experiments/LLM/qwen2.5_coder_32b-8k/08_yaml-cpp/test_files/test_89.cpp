#include <gtest/gtest.h>

#include "yaml-cpp/exceptions.h"



class ExceptionsTest_89 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(ExceptionsTest_89, InvalidNodeWithKey_EmptyKey_ReturnsBaseMessage_89) {

    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY("");

    EXPECT_EQ(result, "invalid node; this may result from using a map iterator as a sequence iterator, or vice-versa");

}



TEST_F(ExceptionsTest_89, InvalidNodeWithKey_NonEmptyKey_ReturnsFormattedMessage_89) {

    std::string key = "test_key";

    std::string expected_message = "invalid node; first invalid key: \"test_key\"";

    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);

    EXPECT_EQ(result, expected_message);

}



TEST_F(ExceptionsTest_89, InvalidNodeWithKey_SpecialCharactersInKey_ReturnsFormattedMessage_89) {

    std::string key = "key!@#";

    std::string expected_message = "invalid node; first invalid key: \"key!@#\"";

    std::string result = YAML::ErrorMsg::INVALID_NODE_WITH_KEY(key);

    EXPECT_EQ(result, expected_message);

}
