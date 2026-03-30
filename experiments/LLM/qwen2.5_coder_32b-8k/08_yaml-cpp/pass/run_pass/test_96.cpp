#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/yaml.h"



using namespace YAML;



class EmitterTest_96 : public ::testing::Test {

protected:

    std::ostringstream output_stream;

    Emitter emitter;

    

    EmitterTest_96() : emitter(output_stream) {}

};



TEST_F(EmitterTest_96, WriteString_NormalOperation_96) {

    const std::string test_string = "test";

    emitter << test_string;

    EXPECT_EQ(test_string, output_stream.str());

}



TEST_F(EmitterTest_96, WriteEmptyString_NormalOperation_96) {

    const std::string empty_string = "";

    emitter << empty_string;

    EXPECT_EQ(empty_string, output_stream.str());

}



TEST_F(EmitterTest_96, WriteBoolTrue_NormalOperation_96) {

    emitter << true;

    EXPECT_EQ("true", output_stream.str());

}



TEST_F(EmitterTest_96, WriteBoolFalse_NormalOperation_96) {

    emitter << false;

    EXPECT_EQ("false", output_stream.str());

}



TEST_F(EmitterTest_96, WriteChar_NormalOperation_96) {

    const char test_char = 'a';

    emitter << test_char;

    EXPECT_EQ(std::string(1, test_char), output_stream.str());

}



TEST_F(EmitterTest_96, WriteNode_ScalarString_96) {

    Node node("test");

    emitter << node;

    EXPECT_EQ("\"test\"", output_stream.str());

}



TEST_F(EmitterTest_96, WriteNode_EmptyScalarString_96) {

    Node empty_node("");

    emitter << empty_node;

    EXPECT_EQ("\"\"", output_stream.str());

}



TEST_F(EmitterTest_96, Good_ReturnsTrueAfterWrite_96) {

    emitter << "test";

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_96, GetLastError_ReturnsEmptyStringWhenNoError_96) {

    emitter << "test";

    EXPECT_EQ("", emitter.GetLastError());

}



TEST_F(EmitterTest_96, SetIndent_NormalOperation_96) {

    EXPECT_TRUE(emitter.SetIndent(2));

}



TEST_F(EmitterTest_96, SetInvalidIndent_ReturnsFalse_96) {

    EXPECT_FALSE(emitter.SetIndent(0));

}



TEST_F(EmitterTest_96, WriteMultipleTimes_ConcatenatesOutput_96) {

    emitter << "first" << "second";

    EXPECT_EQ("firstsecond", output_stream.str());

}
