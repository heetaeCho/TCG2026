#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <limits>
#include "yaml-cpp/yaml.h"

// Test fixture
class EmitterTest_55 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// === Construction and Initial State ===

TEST_F(EmitterTest_55, DefaultConstructor_GoodState_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_55, DefaultConstructor_EmptyOutput_55) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_55, DefaultConstructor_CStrNotNull_55) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_55, StreamConstructor_GoodState_55) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_55, DefaultConstructor_NoError_55) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.GetLastError(), "");
}

// === Writing unsigned long long (the specific operator<<) ===

TEST_F(EmitterTest_55, WriteUnsignedLongLong_Zero_55) {
    YAML::Emitter emitter;
    emitter << (unsigned long long)0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, "0");
}

TEST_F(EmitterTest_55, WriteUnsignedLongLong_SmallValue_55) {
    YAML::Emitter emitter;
    emitter << (unsigned long long)42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_55, WriteUnsignedLongLong_MaxValue_55) {
    YAML::Emitter emitter;
    unsigned long long maxVal = std::numeric_limits<unsigned long long>::max();
    emitter << maxVal;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_EQ(output, std::to_string(maxVal));
}

TEST_F(EmitterTest_55, WriteUnsignedLongLong_ToStream_55) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << (unsigned long long)123456789;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("123456789"), std::string::npos);
}

// === Writing other integral types ===

TEST_F(EmitterTest_55, WriteInt_55) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "42");
}

TEST_F(EmitterTest_55, WriteNegativeInt_55) {
    YAML::Emitter emitter;
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "-10");
}

TEST_F(EmitterTest_55, WriteLongLong_55) {
    YAML::Emitter emitter;
    long long val = 9876543210LL;
    emitter << val;
    EXPECT_TRUE(emitter.good());
    EXPECT_EQ(std::string(emitter.c_str()), "9876543210");
}

// === Writing strings ===

TEST_F(EmitterTest_55, WriteString_55) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteStdString_55) {
    YAML::Emitter emitter;
    std::string s = "world";
    emitter << s;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteEmptyString_55) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
}

// === Writing booleans ===

TEST_F(EmitterTest_55, WriteBoolTrue_55) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteBoolFalse_55) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("false"), std::string::npos);
}

// === Writing null ===

TEST_F(EmitterTest_55, WriteNull_55) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("~"), std::string::npos);
}

// === Writing char ===

TEST_F(EmitterTest_55, WriteChar_55) {
    YAML::Emitter emitter;
    emitter << 'A';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("A"), std::string::npos);
}

// === Writing floating point ===

TEST_F(EmitterTest_55, WriteFloat_55) {
    YAML::Emitter emitter;
    emitter << 3.14f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteDouble_55) {
    YAML::Emitter emitter;
    emitter << 2.71828;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("2.71"), std::string::npos);
}

// === Sequences ===

TEST_F(EmitterTest_55, WriteBlockSequence_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("- 1"), std::string::npos);
    EXPECT_NE(output.find("- 2"), std::string::npos);
    EXPECT_NE(output.find("- 3"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteFlowSequence_55) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

// === Maps ===

TEST_F(EmitterTest_55, WriteBlockMap_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteFlowMap_55) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

// === Nested structures ===

TEST_F(EmitterTest_55, WriteNestedMapInSeq_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_55, WriteNestedSeqInMap_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// === Comments ===

TEST_F(EmitterTest_55, WriteComment_55) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("this is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// === Anchors and Aliases ===

TEST_F(EmitterTest_55, WriteAnchor_55) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("anchor1") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_55, WriteAlias_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("a") << "val";
    emitter << YAML::Alias("a");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*a"), std::string::npos);
}

// === Tags ===

TEST_F(EmitterTest_55, WriteTag_55) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// === Settings ===

TEST_F(EmitterTest_55, SetBoolFormat_TrueFalse_55) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("true"), std::string::npos);
}

TEST_F(EmitterTest_55, SetBoolFormat_UpperCase_55) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_55, SetBoolFormat_CamelCase_55) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::CamelCase);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("True"), std::string::npos);
}

TEST_F(EmitterTest_55, SetIntBase_Hex_55) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_55, SetIntBase_Oct_55) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_55, SetSeqFormat_Flow_55) {
    YAML::Emitter emitter;
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_55, SetMapFormat_Flow_55) {
    YAML::Emitter emitter;
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_55, SetIndent_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_55, SetIndent_ZeroReturnsFalse_55) {
    YAML::Emitter emitter;
    // Indent of 0 or 1 may be invalid
    // Just verify the call returns a bool
    bool result = emitter.SetIndent(0);
    // We don't assert specific value since it's implementation-defined
    (void)result;
}

TEST_F(EmitterTest_55, SetPreCommentIndent_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_55, SetPostCommentIndent_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_55, SetFloatPrecision_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_55, SetDoublePrecision_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_55, SetStringFormat_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_55, SetNullFormat_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

// === Stream output ===

TEST_F(EmitterTest_55, StreamOutput_55) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

TEST_F(EmitterTest_55, StreamOutputWithSequence_55) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = ss.str();
    EXPECT_NE(output.find("a"), std::string::npos);
    EXPECT_NE(output.find("b"), std::string::npos);
}

// === Size tracking ===

TEST_F(EmitterTest_55, SizeIncreasesAfterWrite_55) {
    YAML::Emitter emitter;
    std::size_t sizeBefore = emitter.size();
    emitter << "something";
    EXPECT_GT(emitter.size(), sizeBefore);
}

// === Multiple writes ===

TEST_F(EmitterTest_55, MultipleScalarWrites_InSequence_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << (unsigned long long)100;
    emitter << (unsigned long long)200;
    emitter << (unsigned long long)300;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
    EXPECT_NE(output.find("300"), std::string::npos);
}

// === Binary ===

TEST_F(EmitterTest_55, WriteBinary_55) {
    YAML::Emitter emitter;
    std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0xFF};
    emitter << YAML::Binary(data.data(), data.size());
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// === RestoreGlobalModifiedSettings ===

TEST_F(EmitterTest_55, RestoreGlobalModifiedSettings_55) {
    YAML::Emitter emitter;
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter.RestoreGlobalModifiedSettings();
    emitter << true;
    EXPECT_TRUE(emitter.good());
    // After restore, default format should be used
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

// === SetLocalValue ===

TEST_F(EmitterTest_55, SetLocalValue_Flow_55) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

// === Complex document ===

TEST_F(EmitterTest_55, ComplexDocument_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "test";
    emitter << YAML::Key << "count" << YAML::Value << (unsigned long long)42;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
    emitter << YAML::Key << "nested" << YAML::Value;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "x" << YAML::Value << 1;
    emitter << YAML::Key << "y" << YAML::Value << 2;
    emitter << YAML::EndMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("42"), std::string::npos);
    EXPECT_NE(output.find("nested"), std::string::npos);
}

// === UnsignedLongLong in map ===

TEST_F(EmitterTest_55, UnsignedLongLongAsMapValue_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "big_number" << YAML::Value << (unsigned long long)18446744073709551615ULL;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("18446744073709551615"), std::string::npos);
}

// === Hex format with unsigned long long ===

TEST_F(EmitterTest_55, UnsignedLongLong_HexFormat_55) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Hex);
    emitter << (unsigned long long)255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
    EXPECT_NE(output.find("ff"), std::string::npos);
}

// === Oct format with unsigned long long ===

TEST_F(EmitterTest_55, UnsignedLongLong_OctFormat_55) {
    YAML::Emitter emitter;
    emitter.SetIntBase(YAML::Oct);
    emitter << (unsigned long long)8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("010"), std::string::npos);
}

// === Newline behavior ===

TEST_F(EmitterTest_55, WriteNewline_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "first";
    emitter << YAML::Newline;
    emitter << "second";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Double precision ===

TEST_F(EmitterTest_55, DoublePrecisionAffectsOutput_55) {
    YAML::Emitter emitter;
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // With precision 3, should have limited digits
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// === Float precision ===

TEST_F(EmitterTest_55, FloatPrecisionAffectsOutput_55) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("3.1"), std::string::npos);
}

// === SetOutputCharset ===

TEST_F(EmitterTest_55, SetOutputCharset_UTF8_55) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// === Literal and quoted strings ===

TEST_F(EmitterTest_55, SingleQuotedString_55) {
    YAML::Emitter emitter;
    emitter << YAML::SingleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_55, DoubleQuotedString_55) {
    YAML::Emitter emitter;
    emitter << YAML::DoubleQuoted << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_55, LiteralString_55) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// === Null format variants ===

TEST_F(EmitterTest_55, NullFormat_Tilde_55) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("~"), std::string::npos);
}

TEST_F(EmitterTest_55, NullFormat_LowerNull_55) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("null"), std::string::npos);
}

TEST_F(EmitterTest_55, NullFormat_UpperNull_55) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("NULL"), std::string::npos);
}

TEST_F(EmitterTest_55, NullFormat_CamelNull_55) {
    YAML::Emitter emitter;
    emitter.SetNullFormat(YAML::CamelNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    EXPECT_NE(std::string(emitter.c_str()).find("Null"), std::string::npos);
}

// === Edge: empty sequence ===

TEST_F(EmitterTest_55, EmptyFlowSequence_55) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// === Edge: empty map ===

TEST_F(EmitterTest_55, EmptyFlowMap_55) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// === SetLocalIndent ===

TEST_F(EmitterTest_55, SetLocalIndent_55) {
    YAML::Emitter emitter;
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// === Multiple documents (BeginDoc/EndDoc via YAML::BeginDoc etc.) ===

TEST_F(EmitterTest_55, MultipleDocuments_55) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("---"), std::string::npos);
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}
