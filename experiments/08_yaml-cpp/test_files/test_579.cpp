#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/yaml.h"



using namespace YAML;



class ParseTest_579 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed

};



TEST_F(ParseTest_579, LoadValidString_579) {

    const char* input = "key: value";

    Node node = Load(input);

    ASSERT_TRUE(node.IsMap());

    EXPECT_EQ(node["key"].as<std::string>(), "value");

}



TEST_F(ParseTest_579, LoadEmptyString_579) {

    const char* input = "";

    Node node = Load(input);

    ASSERT_FALSE(node.IsDefined());

}



TEST_F(ParseTest_579, LoadInvalidString_579) {

    const char* input = "key: value\n  invalid:";

    EXPECT_THROW(Load(input), ParserException);

}



TEST_F(ParseTest_579, LoadNullInput_579) {

    const char* input = nullptr;

    EXPECT_THROW(Load(input), ParserException);

}
