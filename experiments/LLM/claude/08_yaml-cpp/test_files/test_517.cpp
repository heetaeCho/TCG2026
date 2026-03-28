#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_517 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_517, DefaultConstructor_IsGood_517) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_517, DefaultConstructor_EmptyOutput_517) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_517, DefaultConstructor_CStr_517) {
  EXPECT_NE(emitter.c_str(), nullptr);
  EXPECT_STREQ(emitter.c_str(), "");
}

TEST_F(EmitterTest_517, DefaultConstructor_NoError_517) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_517, StreamConstructor_IsGood_517) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

// ==================== SetOutputCharset ====================

TEST_F(EmitterTest_517, SetOutputCharset_EmitUTF8_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_517, SetOutputCharset_EscapeNonAscii_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_517, SetOutputCharset_InvalidValue_ReturnsFalse_517) {
  // Passing an unrelated EMITTER_MANIP that doesn't correspond to charset
  EXPECT_FALSE(emitter.SetOutputCharset(YAML::Auto));
}

// ==================== SetStringFormat ====================

TEST_F(EmitterTest_517, SetStringFormat_SingleQuoted_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_517, SetStringFormat_DoubleQuoted_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_517, SetStringFormat_Literal_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_517, SetStringFormat_InvalidValue_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetStringFormat(YAML::Dec));
}

// ==================== SetBoolFormat ====================

TEST_F(EmitterTest_517, SetBoolFormat_TrueFalseBool_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_517, SetBoolFormat_YesNoBool_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_517, SetBoolFormat_OnOffBool_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_517, SetBoolFormat_UpperCase_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_517, SetBoolFormat_LowerCase_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_517, SetBoolFormat_CamelCase_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_517, SetBoolFormat_LongBool_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_517, SetBoolFormat_ShortBool_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

// ==================== SetNullFormat ====================

TEST_F(EmitterTest_517, SetNullFormat_LowerNull_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_517, SetNullFormat_UpperNull_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
}

TEST_F(EmitterTest_517, SetNullFormat_CamelNull_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
}

TEST_F(EmitterTest_517, SetNullFormat_TildeNull_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

// ==================== SetIntBase ====================

TEST_F(EmitterTest_517, SetIntBase_Dec_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_517, SetIntBase_Hex_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_517, SetIntBase_Oct_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_517, SetIntBase_InvalidValue_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetIntBase(YAML::Flow));
}

// ==================== SetSeqFormat ====================

TEST_F(EmitterTest_517, SetSeqFormat_Block_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_517, SetSeqFormat_Flow_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_517, SetSeqFormat_InvalidValue_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetSeqFormat(YAML::Dec));
}

// ==================== SetMapFormat ====================

TEST_F(EmitterTest_517, SetMapFormat_Block_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_517, SetMapFormat_Flow_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_517, SetMapFormat_InvalidValue_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetMapFormat(YAML::Dec));
}

// ==================== SetIndent ====================

TEST_F(EmitterTest_517, SetIndent_ValidValue_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_517, SetIndent_MinValue2_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_517, SetIndent_ValueOfOne_ReturnsFalse_517) {
  // Indent of 1 is generally too small
  EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_517, SetIndent_ValueOfZero_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetIndent(0));
}

// ==================== SetPreCommentIndent ====================

TEST_F(EmitterTest_517, SetPreCommentIndent_ValidValue_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_517, SetPreCommentIndent_Zero_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetPreCommentIndent(0));
}

// ==================== SetPostCommentIndent ====================

TEST_F(EmitterTest_517, SetPostCommentIndent_ValidValue_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_517, SetPostCommentIndent_Zero_ReturnsFalse_517) {
  EXPECT_FALSE(emitter.SetPostCommentIndent(0));
}

// ==================== SetFloatPrecision / SetDoublePrecision ====================

TEST_F(EmitterTest_517, SetFloatPrecision_ValidValue_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_517, SetDoublePrecision_ValidValue_ReturnsTrue_517) {
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== Write Scalars ====================

TEST_F(EmitterTest_517, WriteString_ProducesOutput_517) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteInt_ProducesOutput_517) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteBool_True_ProducesOutput_517) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteBool_False_ProducesOutput_517) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteNull_ProducesOutput_517) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteFloat_ProducesOutput_517) {
  emitter << 3.14f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_517, WriteDouble_ProducesOutput_517) {
  emitter << 3.14159265;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_517, WriteBlockSequence_ProducesValidOutput_517) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteFlowSequence_ProducesValidOutput_517) {
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

// ==================== Maps ====================

TEST_F(EmitterTest_517, WriteBlockMap_ProducesValidOutput_517) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_517, WriteFlowMap_ProducesValidOutput_517) {
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_517, WriteNestedMapInSequence_517) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_517, WriteNestedSequenceInMap_517) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list" << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Comments ====================

TEST_F(EmitterTest_517, WriteComment_ProducesOutput_517) {
  emitter << YAML::Comment("this is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_517, WriteAnchor_ProducesOutput_517) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("anchor1") << "value1";
  emitter << YAML::Alias("anchor1");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
  EXPECT_NE(output.find("*anchor1"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_517, WriteTag_ProducesOutput_517) {
  emitter << YAML::BeginSeq;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Stream Output ====================

TEST_F(EmitterTest_517, StreamConstructor_OutputToStream_517) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_TRUE(e.good());
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_517, SetLocalValue_Flow_517) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Bool Format Variations ====================

TEST_F(EmitterTest_517, BoolFormat_YesNo_517) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  // Should contain "yes" in some case
  EXPECT_TRUE(output.find("yes") != std::string::npos ||
              output.find("Yes") != std::string::npos ||
              output.find("YES") != std::string::npos);
}

TEST_F(EmitterTest_517, BoolFormat_OnOff_517) {
  emitter.SetBoolFormat(YAML::OnOffBool);
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("off") != std::string::npos ||
              output.find("Off") != std::string::npos ||
              output.find("OFF") != std::string::npos);
}

// ==================== Int Base Variations ====================

TEST_F(EmitterTest_517, IntBase_Hex_517) {
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_517, IntBase_Oct_517) {
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Null Format Variations ====================

TEST_F(EmitterTest_517, NullFormat_LowerNull_517) {
  emitter.SetNullFormat(YAML::LowerNull);
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_517, NullFormat_UpperNull_517) {
  emitter.SetNullFormat(YAML::UpperNull);
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("NULL"), std::string::npos);
}

TEST_F(EmitterTest_517, NullFormat_TildeNull_517) {
  emitter.SetNullFormat(YAML::TildeNull);
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_517, WriteBinary_ProducesOutput_517) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Empty String ====================

TEST_F(EmitterTest_517, WriteEmptyString_ProducesOutput_517) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_517, RestoreGlobalModifiedSettings_517) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_517, MultipleDocuments_517) {
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

// ==================== Long Key ====================

TEST_F(EmitterTest_517, LongKey_517) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "long key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Newline ====================

TEST_F(EmitterTest_517, Newline_517) {
  emitter << YAML::BeginSeq;
  emitter << "a";
  emitter << YAML::Newline;
  emitter << "b";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Char Write ====================

TEST_F(EmitterTest_517, WriteChar_ProducesOutput_517) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Precision ====================

TEST_F(EmitterTest_517, SetLocalPrecision_517) {
  emitter << YAML::BeginSeq;
  emitter << YAML::FloatPrecision(2) << 3.14159f;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_517, SetLocalIndent_517) {
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== String with special chars ====================

TEST_F(EmitterTest_517, WriteStringWithSpecialChars_517) {
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_517, WriteStringWithNewlines_517) {
  emitter << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== SetStringFormat Literal multiline ====================

TEST_F(EmitterTest_517, SetStringFormat_Literal_MultilineOutput_517) {
  emitter.SetStringFormat(YAML::Literal);
  emitter << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Complex nested structure ====================

TEST_F(EmitterTest_517, ComplexNestedStructure_517) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "servers" << YAML::Value;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "host" << YAML::Value << "localhost";
  emitter << YAML::Key << "port" << YAML::Value << 8080;
  emitter << YAML::EndMap;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "host" << YAML::Value << "remote";
  emitter << YAML::Key << "port" << YAML::Value << 9090;
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("servers"), std::string::npos);
  EXPECT_NE(output.find("localhost"), std::string::npos);
  EXPECT_NE(output.find("8080"), std::string::npos);
  EXPECT_NE(output.find("remote"), std::string::npos);
  EXPECT_NE(output.find("9090"), std::string::npos);
}

// ==================== Write with size overload ====================

TEST_F(EmitterTest_517, WriteCStrWithSize_517) {
  const char* data = "hello world";
  emitter.Write(data, 5);  // Write only "hello"
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

// ==================== Empty sequence ====================

TEST_F(EmitterTest_517, EmptyFlowSequence_517) {
  emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("[]"), std::string::npos);
}

// ==================== Empty map ====================

TEST_F(EmitterTest_517, EmptyFlowMap_517) {
  emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{}"), std::string::npos);
}

// ==================== Negative numbers ====================

TEST_F(EmitterTest_517, WriteNegativeInt_517) {
  emitter << -42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-42"), std::string::npos);
}

// ==================== Large number ====================

TEST_F(EmitterTest_517, WriteLargeInt_517) {
  emitter << 2147483647;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("2147483647"), std::string::npos);
}

// ==================== DoubleQuoted String Format ====================

TEST_F(EmitterTest_517, SetStringFormat_DoubleQuoted_Output_517) {
  emitter.SetStringFormat(YAML::DoubleQuoted);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// ==================== SingleQuoted String Format ====================

TEST_F(EmitterTest_517, SetStringFormat_SingleQuoted_Output_517) {
  emitter.SetStringFormat(YAML::SingleQuoted);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}
