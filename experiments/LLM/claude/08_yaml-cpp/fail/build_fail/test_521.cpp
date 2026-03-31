#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_521 : public ::testing::Test {
protected:
    YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_521, DefaultConstructor_IsGood_521) {
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_521, DefaultConstructor_EmptyOutput_521) {
    EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_521, DefaultConstructor_CStr_521) {
    const char* result = emitter.c_str();
    EXPECT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(EmitterTest_521, DefaultConstructor_NoLastError_521) {
    EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_521, StreamConstructor_IsGood_521) {
    std::stringstream ss;
    YAML::Emitter streamEmitter(ss);
    EXPECT_TRUE(streamEmitter.good());
}

// ==================== SetIntBase ====================

TEST_F(EmitterTest_521, SetIntBase_Dec_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_521, SetIntBase_Hex_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_521, SetIntBase_Oct_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_521, SetIntBase_InvalidValue_ReturnsFalse_521) {
    // Passing a value that is not a valid int base format
    EXPECT_FALSE(emitter.SetIntBase(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_521, SetIntBase_Dec_OutputDecimal_521) {
    emitter.SetIntBase(YAML::Dec);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "255");
}

TEST_F(EmitterTest_521, SetIntBase_Hex_OutputHex_521) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0xff");
}

TEST_F(EmitterTest_521, SetIntBase_Oct_OutputOctal_521) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0377");
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_521, SetOutputCharset_UTF8_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_521, SetOutputCharset_EscapeNonAscii_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_521, SetOutputCharset_Invalid_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetOutputCharset(YAML::Dec));
}

// ==================== SetStringFormat ====================

TEST_F(EmitterTest_521, SetStringFormat_Auto_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Auto));
}

TEST_F(EmitterTest_521, SetStringFormat_SingleQuoted_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_521, SetStringFormat_DoubleQuoted_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_521, SetStringFormat_Literal_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_521, SetStringFormat_Invalid_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetStringFormat(YAML::Dec));
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterTest_521, SetBoolFormat_TrueFalse_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_521, SetBoolFormat_YesNo_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_521, SetBoolFormat_OnOff_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_521, SetBoolFormat_Upper_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_521, SetBoolFormat_Lower_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_521, SetBoolFormat_Camel_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_521, SetBoolFormat_Long_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_521, SetBoolFormat_Short_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_521, SetNullFormat_LowerNull_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_521, SetNullFormat_UpperNull_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
}

TEST_F(EmitterTest_521, SetNullFormat_CamelNull_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
}

TEST_F(EmitterTest_521, SetNullFormat_TildeNull_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_521, SetNullFormat_Invalid_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetNullFormat(YAML::Dec));
}

// ==================== SetSeqFormat ====================

TEST_F(EmitterTest_521, SetSeqFormat_Block_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_521, SetSeqFormat_Flow_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_521, SetSeqFormat_Invalid_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetSeqFormat(YAML::Dec));
}

// ==================== SetMapFormat ====================

TEST_F(EmitterTest_521, SetMapFormat_Block_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_521, SetMapFormat_Flow_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_521, SetMapFormat_Invalid_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetMapFormat(YAML::Dec));
}

// ==================== SetIndent ====================

TEST_F(EmitterTest_521, SetIndent_Valid_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_521, SetIndent_MinValue_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_521, SetIndent_TooSmall_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_521, SetIndent_Zero_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetIndent(0));
}

// ==================== SetPreCommentIndent / SetPostCommentIndent ====================

TEST_F(EmitterTest_521, SetPreCommentIndent_Valid_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_521, SetPostCommentIndent_Valid_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_521, SetPreCommentIndent_Zero_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetPreCommentIndent(0));
}

TEST_F(EmitterTest_521, SetPostCommentIndent_Zero_ReturnsFalse_521) {
    EXPECT_FALSE(emitter.SetPostCommentIndent(0));
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterTest_521, SetFloatPrecision_Valid_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_521, SetDoublePrecision_Valid_ReturnsTrue_521) {
    EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== Write String ====================

TEST_F(EmitterTest_521, WriteString_Simple_521) {
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "hello");
}

TEST_F(EmitterTest_521, WriteString_StdString_521) {
    std::string s = "world";
    emitter << s;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "world");
}

TEST_F(EmitterTest_521, WriteString_EmptyString_521) {
    emitter << "";
    EXPECT_TRUE(emitter.good());
    // Empty string should produce some representation (e.g., '' or "")
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Write Bool ====================

TEST_F(EmitterTest_521, WriteBool_True_521) {
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_521, WriteBool_False_521) {
    emitter << false;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_521, WriteBool_TrueFalseFormat_521) {
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "true");
}

TEST_F(EmitterTest_521, WriteBool_YesNoFormat_521) {
    emitter.SetBoolFormat(YAML::YesNoBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "yes");
}

TEST_F(EmitterTest_521, WriteBool_UpperCase_521) {
    emitter.SetBoolFormat(YAML::UpperCase);
    emitter.SetBoolFormat(YAML::TrueFalseBool);
    emitter << true;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "TRUE");
}

// ==================== Write Integer ====================

TEST_F(EmitterTest_521, WriteInt_Positive_521) {
    emitter << 42;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_521, WriteInt_Negative_521) {
    emitter << -10;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "-10");
}

TEST_F(EmitterTest_521, WriteInt_Zero_521) {
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0");
}

// ==================== Write Float/Double ====================

TEST_F(EmitterTest_521, WriteDouble_521) {
    emitter << 3.14;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_521, WriteFloat_521) {
    emitter << 2.5f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_FALSE(output.empty());
}

// ==================== Write Null ====================

TEST_F(EmitterTest_521, WriteNull_Default_521) {
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "~");
}

TEST_F(EmitterTest_521, WriteNull_LowerNull_521) {
    emitter.SetNullFormat(YAML::LowerNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "null");
}

TEST_F(EmitterTest_521, WriteNull_UpperNull_521) {
    emitter.SetNullFormat(YAML::UpperNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "NULL");
}

TEST_F(EmitterTest_521, WriteNull_CamelNull_521) {
    emitter.SetNullFormat(YAML::CamelNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "Null");
}

TEST_F(EmitterTest_521, WriteNull_TildeNull_521) {
    emitter.SetNullFormat(YAML::TildeNull);
    emitter << YAML::Null;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "~");
}

// ==================== Sequences ====================

TEST_F(EmitterTest_521, BlockSequence_521) {
    emitter << YAML::BeginSeq;
    emitter << "item1";
    emitter << "item2";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("item1"), std::string::npos);
    EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_521, FlowSequence_521) {
    emitter.SetSeqFormat(YAML::Flow);
    emitter << YAML::BeginSeq;
    emitter << 1 << 2 << 3;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
    EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_521, EmptySequence_521) {
    emitter << YAML::BeginSeq;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Maps ====================

TEST_F(EmitterTest_521, BlockMap_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value << "val1";
    emitter << YAML::Key << "key2" << YAML::Value << "val2";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("key1"), std::string::npos);
    EXPECT_NE(output.find("val1"), std::string::npos);
}

TEST_F(EmitterTest_521, FlowMap_521) {
    emitter.SetMapFormat(YAML::Flow);
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "a" << YAML::Value << 1;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("{"), std::string::npos);
    EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_521, EmptyMap_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_521, NestedMapInSeq_521) {
    emitter << YAML::BeginSeq;
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "name" << YAML::Value << "John";
    emitter << YAML::EndMap;
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_521, NestedSeqInMap_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "items" << YAML::Value;
    emitter << YAML::BeginSeq;
    emitter << "a" << "b";
    emitter << YAML::EndSeq;
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_521, Anchor_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("&anc"), std::string::npos);
}

TEST_F(EmitterTest_521, Alias_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key1" << YAML::Value;
    emitter << YAML::Anchor("anc") << "value";
    emitter << YAML::Key << "key2" << YAML::Value;
    emitter << YAML::Alias("anc");
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_521, Tag_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::Key << "key" << YAML::Value;
    emitter << YAML::Tag("!mytag") << "tagged_value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// ==================== Comments ====================

TEST_F(EmitterTest_521, Comment_521) {
    emitter << YAML::Comment("This is a comment");
    emitter << "value";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ==================== Character Write ====================

TEST_F(EmitterTest_521, WriteChar_521) {
    emitter << 'x';
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "x");
}

// ==================== Stream Output ====================

TEST_F(EmitterTest_521, StreamOutput_521) {
    std::stringstream ss;
    YAML::Emitter streamEmitter(ss);
    streamEmitter << "hello";
    EXPECT_TRUE(streamEmitter.good());
    EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// ==================== Size ====================

TEST_F(EmitterTest_521, Size_AfterWrite_521) {
    emitter << "test";
    EXPECT_EQ(emitter.size(), 4u);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_521, SetLocalValue_Flow_521) {
    emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("["), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_521, RestoreGlobalModifiedSettings_521) {
    emitter.SetIntBase(YAML::Hex);
    emitter.RestoreGlobalModifiedSettings();
    emitter << 255;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    // After restoring, should use default (Dec)
    EXPECT_EQ(output, "255");
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_521, MultipleDocuments_521) {
    emitter << YAML::BeginDoc;
    emitter << "doc1";
    emitter << YAML::EndDoc;
    emitter << YAML::BeginDoc;
    emitter << "doc2";
    emitter << YAML::EndDoc;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("doc1"), std::string::npos);
    EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_521, WriteBinary_521) {
    const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
    emitter << YAML::Binary(data, sizeof(data));
    EXPECT_TRUE(emitter.good());
    EXPECT_GT(emitter.size(), 0u);
}

// ==================== Hex Integer Output ====================

TEST_F(EmitterTest_521, HexIntBase_Zero_521) {
    emitter.SetIntBase(YAML::Hex);
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0x0");
}

TEST_F(EmitterTest_521, OctIntBase_Zero_521) {
    emitter.SetIntBase(YAML::Oct);
    emitter << 0;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_EQ(output, "0");
}

// ==================== Long Key ====================

TEST_F(EmitterTest_521, LongKey_521) {
    emitter << YAML::BeginMap;
    emitter << YAML::LongKey;
    emitter << YAML::Key << "key" << YAML::Value << "value";
    emitter << YAML::EndMap;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== SetLocalIndent ====================

TEST_F(EmitterTest_521, SetLocalIndent_521) {
    emitter << YAML::Indent(4);
    emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}

// ==================== Literal String Format ====================

TEST_F(EmitterTest_521, LiteralStringFormat_521) {
    emitter << YAML::Literal << "line1\nline2\nline3";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== DoubleQuoted String Format ====================

TEST_F(EmitterTest_521, DoubleQuotedStringFormat_521) {
    emitter.SetStringFormat(YAML::DoubleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ==================== SingleQuoted String Format ====================

TEST_F(EmitterTest_521, SingleQuotedStringFormat_521) {
    emitter.SetStringFormat(YAML::SingleQuoted);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("'hello'"), std::string::npos);
}

// ==================== Precision ====================

TEST_F(EmitterTest_521, FloatPrecision_521) {
    emitter.SetFloatPrecision(2);
    emitter << 3.14159f;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.1"), std::string::npos);
}

TEST_F(EmitterTest_521, DoublePrecision_521) {
    emitter.SetDoublePrecision(3);
    emitter << 3.14159265;
    EXPECT_TRUE(emitter.good());
    std::string output(emitter.c_str());
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// ==================== Newline ====================

TEST_F(EmitterTest_521, Newline_521) {
    emitter << YAML::BeginSeq;
    emitter << "a";
    emitter << YAML::Newline;
    emitter << "b";
    emitter << YAML::EndSeq;
    EXPECT_TRUE(emitter.good());
}
