#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



using namespace YAML;



class EmitterTest_37 : public ::testing::Test {

protected:

    Emitter emitter;

};



TEST_F(EmitterTest_37, WriteString_NormalOperation_37) {

    std::string testString = "Hello, World!";

    emitter << testString;

    EXPECT_EQ(emitter.c_str(), "Hello, World!");

}



TEST_F(EmitterTest_37, WriteString_EmptyString_37) {

    std::string emptyString = "";

    emitter << emptyString;

    EXPECT_EQ(emitter.c_str(), "");

}



TEST_F(EmitterTest_37, WriteChar_NormalOperation_37) {

    char testChar = 'A';

    emitter << testChar;

    EXPECT_EQ(emitter.c_str(), "A");

}



TEST_F(EmitterTest_37, WriteBool_True_37) {

    bool trueValue = true;

    emitter << trueValue;

    EXPECT_EQ(emitter.c_str(), "true");

}



TEST_F(EmitterTest_37, WriteBool_False_37) {

    bool falseValue = false;

    emitter << falseValue;

    EXPECT_EQ(emitter.c_str(), "false");

}



TEST_F(EmitterTest_37, SetIndent_ValidValue_37) {

    std::size_t indentSize = 4;

    EXPECT_TRUE(emitter.SetIndent(indentSize));

}



TEST_F(EmitterTest_37, SetIndent_ZeroValue_37) {

    std::size_t zeroIndent = 0;

    EXPECT_FALSE(emitter.SetIndent(zeroIndent));

}



TEST_F(EmitterTest_37, SetFloatPrecision_ValidValue_37) {

    std::size_t precision = 5;

    EXPECT_TRUE(emitter.SetFloatPrecision(precision));

}



TEST_F(EmitterTest_37, SetDoublePrecision_ValidValue_37) {

    std::size_t precision = 10;

    EXPECT_TRUE(emitter.SetDoublePrecision(precision));

}



TEST_F(EmitterTest_37, Good_DefaultState_37) {

    EXPECT_TRUE(emitter.good());

}



TEST_F(EmitterTest_37, GetLastError_NoError_37) {

    EXPECT_EQ(emitter.GetLastError(), "");

}
