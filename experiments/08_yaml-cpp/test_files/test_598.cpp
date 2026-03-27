#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"



class EncodeTest_598 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(EncodeTest_598, ValidStringEncoding_598) {

    const char* input = "valid_string";

    YAML::Node node = YAML::encode(input);

    EXPECT_EQ(node.as<std::string>(), input);

}



TEST_F(EncodeTest_598, EmptyStringEncoding_598) {

    const char* input = "";

    YAML::Node node = YAML::encode(input);

    EXPECT_EQ(node.as<std::string>(), input);

}



TEST_F(EncodeTest_598, NullPointerHandling_598) {

    const char* input = nullptr;

    YAML::Node node = YAML::encode(input);

    // Assuming encoding a null pointer results in an empty string

    EXPECT_TRUE(node.IsNull());

}
