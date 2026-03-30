#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterutils.cpp"

#include "yaml-cpp/emittermanip.h"



using namespace YAML::Utils;



class StringFormatTest_628 : public ::testing::Test {

protected:

    const char* testString = "testString";

    std::size_t testSize = 10;

};



TEST_F(StringFormatTest_628, AutoValidPlainScalar_628) {

    EXPECT_EQ(ComputeStringFormat(testString, testSize, EMITTER_MANIP::Auto, YAML::FlowType::BlockStyle, false), StringFormat::Plain);

}



TEST_F(StringFormatTest_628, AutoInvalidPlainScalar_628) {

    const char* invalidString = "test:string";

    std::size_t invalidSize = 11;

    EXPECT_EQ(ComputeStringFormat(invalidString, invalidSize, EMITTER_MANIP::Auto, YAML::FlowType::BlockStyle, false), StringFormat::DoubleQuoted);

}



TEST_F(StringFormatTest_628, SingleQuotedValidScalar_628) {

    const char* singleQuotedString = "test'string";

    std::size_t singleQuotedSize = 13;

    EXPECT_EQ(ComputeStringFormat(singleQuotedString, singleQuotedSize, EMITTER_MANIP::SingleQuoted, YAML::FlowType::BlockStyle, false), StringFormat::SingleQuoted);

}



TEST_F(StringFormatTest_628, SingleQuotedInvalidScalar_628) {

    const char* invalidString = "test\"string";

    std::size_t invalidSize = 13;

    EXPECT_EQ(ComputeStringFormat(invalidString, invalidSize, EMITTER_MANIP::SingleQuoted, YAML::FlowType::BlockStyle, false), StringFormat::DoubleQuoted);

}



TEST_F(StringFormatTest_628, DoubleQuotedScalar_628) {

    EXPECT_EQ(ComputeStringFormat(testString, testSize, EMITTER_MANIP::DoubleQuoted, YAML::FlowType::BlockStyle, false), StringFormat::DoubleQuoted);

}



TEST_F(StringFormatTest_628, LiteralValidScalar_628) {

    const char* literalString = "test\nstring";

    std::size_t literalSize = 13;

    EXPECT_EQ(ComputeStringFormat(literalString, literalSize, EMITTER_MANIP::Literal, YAML::FlowType::BlockStyle, false), StringFormat::Literal);

}



TEST_F(StringFormatTest_628, LiteralInvalidScalar_628) {

    const char* invalidString = "test:string";

    std::size_t invalidSize = 11;

    EXPECT_EQ(ComputeStringFormat(invalidString, invalidSize, EMITTER_MANIP::Literal, YAML::FlowType::BlockStyle, false), StringFormat::DoubleQuoted);

}



TEST_F(StringFormatTest_628, DefaultCase_628) {

    EXPECT_EQ(ComputeStringFormat(testString, testSize, static_cast<EMITTER_MANIP>(-1), YAML::FlowType::BlockStyle, false), StringFormat::DoubleQuoted);

}
