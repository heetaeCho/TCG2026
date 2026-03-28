#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_37 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Basic Construction and State ====================

TEST_F(EmitterTest_37, DefaultConstructor_GoodState_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_37, StreamConstructor_GoodState_37) {
    std::ostringstream stream;
    YAML::Emitter emitter(stream);
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_37, DefaultConstructor_EmptyOutput_37) {
    YAML::Emitter emitter;
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_37, CStr_ReturnsNonNull_37) {
    YAML::Emitter emitter;
    EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_37, GetLastError_EmptyOnGoodState_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.GetLastError().empty());
}

// ==================== Writing Simple Scalars ====================

TEST_F(EmitterTest_37, WriteString_BasicString_37) {
    YAML::Emitter emitter;
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_37, WriteString_StdString_37) {
    YAML::Emitter emitter;
    std::string val = "world";
    emitter << val;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_37, WriteString_EmptyString_37) {
    YAML::Emitter emitter;
    emitter << "";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_37, WriteBool_True_37) {
    YAML::Emitter emitter;
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, WriteBool_False_37) {
    YAML::Emitter emitter;
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, WriteChar_37) {
    YAML::Emitter emitter;
    emitter << 'a';
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("a"), std::string::npos);
}

TEST_F(EmitterTest_37, WriteInt_37) {
    YAML::Emitter emitter;
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_37, WriteNegativeInt_37) {
    YAML::Emitter emitter;
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-10"), std::string::npos);
}

TEST_F(EmitterTest_37, WriteDouble_37) {
    YAML::Emitter emitter;
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, WriteFloat_37) {
    YAML::Emitter emitter;
    emitter << 1.5f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, WriteNull_37) {
    YAML::Emitter emitter;
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ==================== Sequences ====================

TEST_F(EmitterTest_37, BlockSequence_Basic_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << "item3";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
    EXPECT_NE(output.find("item3"), std::string::npos);
}

TEST_F(EmitterTest_37, FlowSequence_Basic_37) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_37, EmptySequence_37) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_37, BlockMap_Basic_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "John";
    emitter << YAML::Key << "age" << YAML::Value << 30;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("name"), std::string::npos);
    EXPECT_NE(output.find("John"), std::string::npos);
    EXPECT_NE(output.find("age"), std::string::npos);
    EXPECT_NE(output.find("30"), std::string::npos);
}

TEST_F(EmitterTest_37, FlowMap_Basic_37) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap;
    emitter << YAML::Key << "x" << YAML::Value << 1;
    emitter << YAML::Key << "y" << YAML::Value << 2;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_37, EmptyMap_37) {
    YAML::Emitter emitter;
    emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_37, NestedMapInSeq_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
}

TEST_F(EmitterTest_37, NestedSeqInMap_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("items"), std::string::npos);
}

// ==================== Comments ====================

TEST_F(EmitterTest_37, Comment_37) {
    YAML::Emitter emitter;
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_37, Anchor_37) {
    YAML::Emitter emitter;
    emitter << YAML::Anchor("myanchor") << "value";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_37, Alias_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::Anchor("item") << "value";
    emitter << YAML::Alias("item");
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("*item"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_37, Tag_37) {
    YAML::Emitter emitter;
    emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Set Format Functions ====================

TEST_F(EmitterTest_37, SetStringFormat_DoubleQuoted_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_37, SetStringFormat_SingleQuoted_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_37, SetBoolFormat_TrueFalseCase_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_37, SetBoolFormat_UpperCase_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_37, SetBoolFormat_CamelCase_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_37, SetBoolFormat_YesNoBool_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // Should contain some form of "yes"
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, SetNullFormat_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_37, SetIntBase_Hex_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_37, SetIntBase_Oct_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
    emitter << 8;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_37, SetSeqFormat_Flow_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_37, SetSeqFormat_Block_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
    emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("-"), std::string::npos);
}

TEST_F(EmitterTest_37, SetMapFormat_Flow_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "k" << YAML::Value << "v";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_37, SetIndent_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_37, SetIndent_MinValue_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_37, SetIndent_InvalidValue_37) {
    YAML::Emitter emitter;
    // Indent of 1 or 0 might be invalid
    EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_37, SetPreCommentIndent_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_37, SetPostCommentIndent_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_37, SetFloatPrecision_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_37, SetDoublePrecision_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== Stream Constructor Output ====================

TEST_F(EmitterTest_37, StreamConstructor_OutputGoesToStream_37) {
    std::ostringstream stream;
    YAML::Emitter emitter(stream);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    // The output should appear in the stream
    std::string output = stream.str();
    EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_37, StreamConstructor_MapGoesToStream_37) {
    std::ostringstream stream;
    YAML::Emitter emitter(stream);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = stream.str();
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("val"), std::string::npos);
}

// ==================== Size ====================

TEST_F(EmitterTest_37, Size_IncreasesAfterWrite_37) {
    YAML::Emitter emitter;
    std::size_t initialSize = emitter.size();
    emitter << "test";
    EXPECT_GT(emitter.size(), initialSize);
}

TEST_F(EmitterTest_37, Size_MatchesCStrLength_37) {
    YAML::Emitter emitter;
    emitter << "hello world";
    std::string output = emitter.c_str();
    EXPECT_EQ(emitter.size(), output.size());
}

// ==================== Local Value (Manipulators) ====================

TEST_F(EmitterTest_37, LocalValue_DoubleQuoted_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << YAML::DoubleQuoted << "quoted";
    emitter << "unquoted";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("\"quoted\""), std::string::npos);
}

TEST_F(EmitterTest_37, LocalValue_Literal_37) {
    YAML::Emitter emitter;
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_37, Binary_Write_37) {
    YAML::Emitter emitter;
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, Binary_EmptyData_37) {
    YAML::Emitter emitter;
    emitter << YAML::Binary(nullptr, 0);
    EXPECT_TRUE(emitter.good());
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_37, MultipleDocuments_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
    emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== Newline ====================

TEST_F(EmitterTest_37, Newline_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    emitter << "a";
    emitter << YAML::Newline;
    emitter << "b";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Complex Scenarios ====================

TEST_F(EmitterTest_37, ComplexNestedStructure_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "people" << YAML::Value;
    emitter << YAML::BeginSeq;
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

TEST_F(EmitterTest_37, LongInteger_37) {
    YAML::Emitter emitter;
    emitter << 9223372036854775807LL;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(EmitterTest_37, UnsignedInteger_37) {
    YAML::Emitter emitter;
    emitter << 42u;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_37, RestoreGlobalModifiedSettings_37) {
    YAML::Emitter emitter;
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter.RestoreGlobalModifiedSettings();
    // After restore, should still be in good state
    emitter << "test";
    EXPECT_TRUE(emitter.good());
}

// ==================== Local Indent ====================

TEST_F(EmitterTest_37, LocalIndent_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "outer" << YAML::Value;
    emitter << YAML::Indent(4) << YAML::BeginSeq;
    emitter << "a" << "b";
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_37, SetOutputCharset_UTF8_37) {
    YAML::Emitter emitter;
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Edge Case: Writing after sequence/map ====================

TEST_F(EmitterTest_37, MultipleTopLevelScalars_ShouldFail_37) {
    YAML::Emitter emitter;
    emitter << "first";
    emitter << "second";
    // Writing two top-level scalars is typically not valid
    EXPECT_FALSE(emitter.good());
}

TEST_F(EmitterTest_37, WriteAfterEndDoc_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginDoc << "value" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    emitter << YAML::BeginDoc << "value2" << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
}

// ==================== String with special characters ====================

TEST_F(EmitterTest_37, StringWithNewlines_37) {
    YAML::Emitter emitter;
    emitter << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_37, StringWithSpecialChars_37) {
    YAML::Emitter emitter;
    emitter << "key: value";
    EXPECT_TRUE(emitter.good());
    // Should be quoted or escaped since it contains colon+space
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ==================== Key with LongKey ====================

TEST_F(EmitterTest_37, LongKey_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "longkey" << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== SetFloatPrecision effect ====================

TEST_F(EmitterTest_37, FloatPrecision_Effect_37) {
    YAML::Emitter emitter;
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    // With precision 2, should have limited decimal digits
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_37, DoublePrecision_Effect_37) {
    YAML::Emitter emitter;
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265358979;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_FALSE(output.empty());
}

// ==================== Zero value edge cases ====================

TEST_F(EmitterTest_37, WriteZeroInt_37) {
    YAML::Emitter emitter;
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_37, WriteZeroFloat_37) {
    YAML::Emitter emitter;
    emitter << 0.0;
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Large sequence ====================

TEST_F(EmitterTest_37, LargeSequence_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginSeq;
    for (int i = 0; i < 100; ++i) {
        emitter << i;
    }
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== LongKey with complex value ====================

TEST_F(EmitterTest_37, MapWithSequenceAsKey_37) {
    YAML::Emitter emitter;
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    emitter << YAML::Value << "val";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}
