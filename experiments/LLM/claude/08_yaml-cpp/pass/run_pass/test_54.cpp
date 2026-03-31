#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <limits>
#include "yaml-cpp/yaml.h"

// Test fixture
class EmitterTest_54 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_54, DefaultConstructor_GoodState_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_54, DefaultConstructor_EmptyOutput_54) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_54, DefaultConstructor_CStrNotNull_54) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_54, StreamConstructor_GoodState_54) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_54, DefaultConstructor_NoError_54) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// ==================== operator<< with long long ====================

TEST_F(EmitterTest_54, WriteLongLong_PositiveValue_54) {
    YAML::Emitter emitter;
    emitter << 42LL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_54, WriteLongLong_Zero_54) {
    YAML::Emitter emitter;
    emitter << 0LL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0");
}

TEST_F(EmitterTest_54, WriteLongLong_NegativeValue_54) {
    YAML::Emitter emitter;
    emitter << -100LL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "-100");
}

TEST_F(EmitterTest_54, WriteLongLong_MaxValue_54) {
    YAML::Emitter emitter;
    long long maxVal = std::numeric_limits<long long>::max();
    emitter << maxVal;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, std::to_string(maxVal));
}

TEST_F(EmitterTest_54, WriteLongLong_MinValue_54) {
    YAML::Emitter emitter;
    long long minVal = std::numeric_limits<long long>::min();
    emitter << minVal;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, std::to_string(minVal));
}

TEST_F(EmitterTest_54, WriteLongLong_ToStream_54) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << 12345LL;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("12345"), std::string::npos);
}

// ==================== Write string ====================

TEST_F(EmitterTest_54, WriteString_SimpleString_54) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteStdString_54) {
    YAML::Emitter emitter;
    std::string str = "world";
    emitter << str;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteEmptyString_54) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

// ==================== Write bool ====================

TEST_F(EmitterTest_54, WriteBool_True_54) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteBool_False_54) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("false"), std::string::npos);
}

// ==================== Write Null ====================

TEST_F(EmitterTest_54, WriteNull_54) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_54, WriteSequence_Block_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteSequence_Flow_54) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteEmptySequence_54) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_54, WriteMap_Block_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteMap_Flow_54) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteEmptyMap_54) {
    YAML::Emitter emitter;
    emitter << YAML::Flow;
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_54, WriteNestedMapInSeq_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_54, WriteNestedSeqInMap_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_54, WriteAnchor_54) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("myanchor");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteAlias_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("a") << "value";
    emitter << YAML::Alias("a");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*a"), std::string::npos);
}

// ==================== Tag ====================

TEST_F(EmitterTest_54, WriteTag_54) {
    YAML::Emitter emitter;
    emitter << YAML::LocalTag("mytag");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// ==================== Comment ====================

TEST_F(EmitterTest_54, WriteComment_54) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterTest_54, SetBoolFormat_UpperCase_54) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_54, SetBoolFormat_CamelCase_54) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::CamelCase);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_54, SetBoolFormat_LongBool_54) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::LongBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== SetIntBase ====================

TEST_F(EmitterTest_54, SetIntBase_Hex_54) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0xff"), std::string::npos);
}

TEST_F(EmitterTest_54, SetIntBase_Oct_54) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("010"), std::string::npos);
}

TEST_F(EmitterTest_54, SetIntBase_Dec_54) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Dec);
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "42");
}

// ==================== SetSeqFormat ====================

TEST_F(EmitterTest_54, SetSeqFormat_Flow_54) {
    YAML::Emitter emitter;
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_54, SetMapFormat_Flow_54) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << "b";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
}

// ==================== SetIndent ====================

TEST_F(EmitterTest_54, SetIndent_ValidValue_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_54, SetIndent_MinValue_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterTest_54, SetFloatPrecision_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(3));
}

TEST_F(EmitterTest_54, SetDoublePrecision_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(6));
}

// ==================== WriteIntegralType with various types ====================

TEST_F(EmitterTest_54, WriteInt_54) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "42");
}

TEST_F(EmitterTest_54, WriteLong_54) {
    YAML::Emitter emitter;
    emitter << 1000000L;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "1000000");
}

TEST_F(EmitterTest_54, WriteUnsignedInt_54) {
    YAML::Emitter emitter;
    emitter << 42u;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "42");
}

// ==================== WriteStreamable (float, double) ====================

TEST_F(EmitterTest_54, WriteFloat_54) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_54, WriteDouble_54) {
    YAML::Emitter emitter;
    emitter << 2.71828;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

// ==================== Write char ====================

TEST_F(EmitterTest_54, WriteChar_54) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Size reflects output ====================

TEST_F(EmitterTest_54, SizeAfterWrite_54) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
    emitter << "hello";
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Multiple writes ====================

TEST_F(EmitterTest_54, MultipleScalarsInSequence_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "one" << "two" << "three";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("one"), std::string::npos);
    EXPECT_NE(output.find("two"), std::string::npos);
    EXPECT_NE(output.find("three"), std::string::npos);
}

// ==================== SetStringFormat ====================

TEST_F(EmitterTest_54, SetStringFormat_DoubleQuoted_54) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_54, SetStringFormat_SingleQuoted_54) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_54, SetLocalValue_Flow_54) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_54, WriteBinary_54) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
    emitter << YAML::Binary(data.data(), data.size());
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_54, SetNullFormat_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterTest_54, SetPreCommentIndent_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_54, SetPostCommentIndent_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ==================== Hex with long long ====================

TEST_F(EmitterTest_54, WriteLongLongHex_54) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255LL;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("0xff"), std::string::npos);
}

// ==================== Stream output ====================

TEST_F(EmitterTest_54, StreamConstructor_OutputGoesToStream_54) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    // The output should appear in the stream
    std::string output = ss.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// ==================== Complex document ====================

TEST_F(EmitterTest_54, ComplexDocument_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "John";
    emitter << YAML::Key << "age" << YAML::Value << 30;
    emitter << YAML::Key << "scores" << YAML::Value;
    emitter << YAML::BeginSeq << 95 << 87 << 92 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
    EXPECT_NE(output.find("age"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
    EXPECT_NE(output.find("scores"), std::string::npos);
}

// ==================== Newline in output ====================

TEST_F(EmitterTest_54, WriteNewline_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\n"), std::string::npos);
}

// ==================== Multiple documents ====================

TEST_F(EmitterTest_54, BeginDocEndDoc_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc;
    emitter << "hello";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("---"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_54, RestoreGlobalModifiedSettings_54) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // After restoring defaults, bool should use default format
    EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_54, SetOutputCharset_UTF8_54) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== LongLong in sequence ====================

TEST_F(EmitterTest_54, WriteLongLongInSequence_54) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1LL << 2LL << 3LL;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// ==================== LongLong as map value ====================

TEST_F(EmitterTest_54, WriteLongLongAsMapValue_54) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "count" << YAML::Value << 9999999999LL;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("9999999999"), std::string::npos);
}

// ==================== SetLocalIndent ====================

TEST_F(EmitterTest_54, SetLocalIndent_54) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Precision local ====================

TEST_F(EmitterTest_54, SetLocalPrecision_54) {
    YAML::Emitter emitter;
    emitter << YAML::FloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
}
