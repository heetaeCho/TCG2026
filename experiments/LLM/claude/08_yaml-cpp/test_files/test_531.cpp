#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

class EmitterTest_531 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction and initial state
TEST_F(EmitterTest_531, DefaultConstruction_GoodState_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_531, DefaultConstruction_EmptyOutput_531) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_531, DefaultConstruction_CStr_531) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_531, DefaultConstruction_NoError_531) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// Test construction with stream
TEST_F(EmitterTest_531, StreamConstruction_GoodState_531) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

// Test writing a simple string
TEST_F(EmitterTest_531, WriteString_531) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_531, WriteStdString_531) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

// Test writing bool
TEST_F(EmitterTest_531, WriteBoolTrue_531) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_531, WriteBoolFalse_531) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test writing integers
TEST_F(EmitterTest_531, WriteInteger_531) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_531, WriteNegativeInteger_531) {
    YAML::Emitter emitter;
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-10"), std::string::npos);
}

// Test writing float/double
TEST_F(EmitterTest_531, WriteDouble_531) {
    YAML::Emitter emitter;
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_531, WriteFloat_531) {
    YAML::Emitter emitter;
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test writing char
TEST_F(EmitterTest_531, WriteChar_531) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test writing Null
TEST_F(EmitterTest_531, WriteNull_531) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_GT(emitter.size(), 0u);
}

// Test sequence emission
TEST_F(EmitterTest_531, WriteBlockSequence_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_531, WriteFlowSequence_531) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// Test map emission
TEST_F(EmitterTest_531, WriteBlockMap_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name";
    emitter << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_531, WriteFlowMap_531) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key";
    emitter << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// Test nested structures
TEST_F(EmitterTest_531, NestedMapInSequence_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k1" << YAML::Value << "v1";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_531, NestedSequenceInMap_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items";
    emitter << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test SetIndent
TEST_F(EmitterTest_531, SetIndent_ValidValue_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_531, SetIndent_MinValue_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

// Test SetLocalIndent
TEST_F(EmitterTest_531, SetLocalIndent_ReturnsEmitterRef_531) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.SetLocalIndent(YAML::Indent(4));
    EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterTest_531, SetLocalIndent_AppliedToOutput_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer";
    emitter << YAML::Value;
    emitter << YAML::Indent(6);
    emitter << YAML::BeginSeq;
    emitter << "a" << "b";
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test SetStringFormat
TEST_F(EmitterTest_531, SetStringFormat_SingleQuoted_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_531, SetStringFormat_DoubleQuoted_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// Test SetBoolFormat
TEST_F(EmitterTest_531, SetBoolFormat_TrueFalse_531) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_531, SetBoolFormat_YesNo_531) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("no"), std::string::npos);
}

// Test SetIntBase
TEST_F(EmitterTest_531, SetIntBase_Hex_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_531, SetIntBase_Oct_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Test SetSeqFormat
TEST_F(EmitterTest_531, SetSeqFormat_Flow_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_531, SetSeqFormat_Block_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

// Test SetMapFormat
TEST_F(EmitterTest_531, SetMapFormat_Flow_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

// Test SetPreCommentIndent and SetPostCommentIndent
TEST_F(EmitterTest_531, SetPreCommentIndent_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(3));
}

TEST_F(EmitterTest_531, SetPostCommentIndent_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(2));
}

// Test SetFloatPrecision and SetDoublePrecision
TEST_F(EmitterTest_531, SetFloatPrecision_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(3));
}

TEST_F(EmitterTest_531, SetDoublePrecision_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// Test Comment
TEST_F(EmitterTest_531, WriteComment_531) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("#"), std::string::npos);
    EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// Test Anchor and Alias
TEST_F(EmitterTest_531, WriteAnchor_531) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("myanchor");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_531, WriteAlias_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "original";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// Test Tag
TEST_F(EmitterTest_531, WriteTag_531) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
    emitter << "tagged";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// Test Binary
TEST_F(EmitterTest_531, WriteBinary_531) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    YAML::Binary binary(data, sizeof(data));
    emitter << binary;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test output to stream
TEST_F(EmitterTest_531, OutputToStream_531) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "test_value";
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("test_value"), std::string::npos);
}

// Test SetLocalValue
TEST_F(EmitterTest_531, SetLocalValue_Flow_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter.SetLocalValue(YAML::Flow);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Test SetLocalPrecision
TEST_F(EmitterTest_531, SetLocalPrecision_531) {
    YAML::Emitter emitter;
    YAML::Emitter& ref = emitter.SetLocalPrecision(YAML::FloatPrecision(3));
    EXPECT_EQ(&ref, &emitter);
}

// Test RestoreGlobalModifiedSettings
TEST_F(EmitterTest_531, RestoreGlobalModifiedSettings_531) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter.RestoreGlobalModifiedSettings();
    // After restoring, should still be good
    EXPECT_TRUE(emitter.good());
}

// Test SetNullFormat
TEST_F(EmitterTest_531, SetNullFormat_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

// Test SetOutputCharset
TEST_F(EmitterTest_531, SetOutputCharset_UTF8_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// Test multiple writes
TEST_F(EmitterTest_531, MultipleScalarWrites_InSequence_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "one";
    emitter << "two";
    emitter << "three";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("one"), std::string::npos);
    EXPECT_NE(output.find("two"), std::string::npos);
    EXPECT_NE(output.find("three"), std::string::npos);
}

// Test empty string
TEST_F(EmitterTest_531, WriteEmptyString_531) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

// Test empty sequence
TEST_F(EmitterTest_531, WriteEmptySequence_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Test empty map
TEST_F(EmitterTest_531, WriteEmptyMap_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// Test size after writes
TEST_F(EmitterTest_531, SizeIncreasesAfterWrite_531) {
    YAML::Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << "something";
    EXPECT_GT(emitter.size(), initialSize);
}

// Test LongKey
TEST_F(EmitterTest_531, LongKey_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "longkey" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// Test complex nested structure
TEST_F(EmitterTest_531, ComplexNestedStructure_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "people";
    emitter << YAML::Value << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "Alice";
    emitter << YAML::Key << "age" << YAML::Value << 30;
    emitter << YAML::EndMap;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "Bob";
    emitter << YAML::Key << "age" << YAML::Value << 25;
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("Alice"), std::string::npos);
    EXPECT_NE(output.find("Bob"), std::string::npos);
}

// Test Newline
TEST_F(EmitterTest_531, WriteNewline_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << YAML::Newline;
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// Test SetBoolFormat with UpperCase
TEST_F(EmitterTest_531, SetBoolFormat_UpperCase_531) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Check for uppercase version
    EXPECT_TRUE(output.find("TRUE") != std::string::npos ||
                output.find("True") != std::string::npos ||
                output.find("YES") != std::string::npos ||
                output.find("Yes") != std::string::npos);
}

// Test writing to stringstream confirms same as c_str
TEST_F(EmitterTest_531, StreamAndCStrMatch_531) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), ss.str());
}

// Test setting invalid manip for SetSeqFormat (wrong category)
TEST_F(EmitterTest_531, SetSeqFormat_InvalidManip_531) {
    YAML::Emitter emitter;
    // Passing a manip that doesn't apply to seq format
    bool result = emitter.SetSeqFormat(YAML::TrueFalseBool);
    EXPECT_FALSE(result);
}

// Test setting invalid manip for SetMapFormat
TEST_F(EmitterTest_531, SetMapFormat_InvalidManip_531) {
    YAML::Emitter emitter;
    bool result = emitter.SetMapFormat(YAML::TrueFalseBool);
    EXPECT_FALSE(result);
}

// Test SetBoolFormat with invalid value
TEST_F(EmitterTest_531, SetBoolFormat_InvalidManip_531) {
    YAML::Emitter emitter;
    bool result = emitter.SetBoolFormat(YAML::Flow);
    EXPECT_FALSE(result);
}

// Test SetIntBase with invalid value
TEST_F(EmitterTest_531, SetIntBase_InvalidManip_531) {
    YAML::Emitter emitter;
    bool result = emitter.SetIntBase(YAML::Flow);
    EXPECT_FALSE(result);
}

// Test SetStringFormat with invalid value
TEST_F(EmitterTest_531, SetStringFormat_InvalidManip_531) {
    YAML::Emitter emitter;
    bool result = emitter.SetStringFormat(YAML::Flow);
    EXPECT_FALSE(result);
}

// Test that Emitter is non-copyable (compile-time check, but verify construction)
TEST_F(EmitterTest_531, EmitterIsNonCopyable_531) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}

// Test YAML::Literal string style
TEST_F(EmitterTest_531, LiteralStringBlock_531) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// Test multiple documents (BeginDoc/EndDoc via manips)
TEST_F(EmitterTest_531, MultipleDocuments_531) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("---"), std::string::npos);
}

// Test zero value integer
TEST_F(EmitterTest_531, WriteZeroInteger_531) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Test large integer
TEST_F(EmitterTest_531, WriteLargeInteger_531) {
    YAML::Emitter emitter;
    emitter << 2147483647;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("2147483647"), std::string::npos);
}

// Test special characters in string
TEST_F(EmitterTest_531, WriteSpecialCharString_531) {
    YAML::Emitter emitter;
    emitter << "hello: world";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test string with newline
TEST_F(EmitterTest_531, WriteStringWithNewline_531) {
    YAML::Emitter emitter;
    emitter << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// Test SetOutputCharset
TEST_F(EmitterTest_531, SetOutputCharset_EscapeAsUnicode_531) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeAsCodePoint));
}
