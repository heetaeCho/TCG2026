#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_519 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// =============================================================================
// Construction and initial state tests
// =============================================================================

TEST_F(EmitterTest_519, DefaultConstructor_GoodState_519) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_519, DefaultConstructor_EmptyOutput_519) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_519, DefaultConstructor_CStrNotNull_519) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_519, DefaultConstructor_NoError_519) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_519, StreamConstructor_GoodState_519) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

// =============================================================================
// SetBoolFormat tests
// =============================================================================

TEST_F(EmitterTest_519, SetBoolFormat_TrueFalseFmt_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_519, SetBoolFormat_YesNoBool_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_519, SetBoolFormat_OnOffBool_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_519, SetBoolFormat_UpperCase_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_519, SetBoolFormat_LowerCase_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_519, SetBoolFormat_CamelCase_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_519, SetBoolFormat_LongBool_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_519, SetBoolFormat_ShortBool_519) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

TEST_F(EmitterTest_519, SetBoolFormat_InvalidValue_ReturnsFalse_519) {
  // A value that has nothing to do with bool format
  EXPECT_FALSE(emitter.SetBoolFormat(YAML::Hex));
}

TEST_F(EmitterTest_519, SetBoolFormat_AnotherInvalidValue_519) {
  EXPECT_FALSE(emitter.SetBoolFormat(YAML::Flow));
}

// =============================================================================
// SetBoolFormat affects output tests
// =============================================================================

TEST_F(EmitterTest_519, SetBoolFormat_TrueFalse_WritesTrue_519) {
  emitter.SetBoolFormat(YAML::TrueFalseBool);
  emitter << true;
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("true") != std::string::npos ||
              output.find("True") != std::string::npos ||
              output.find("TRUE") != std::string::npos);
}

TEST_F(EmitterTest_519, SetBoolFormat_YesNo_WritesYes_519) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter << true;
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("yes") != std::string::npos ||
              output.find("Yes") != std::string::npos ||
              output.find("YES") != std::string::npos ||
              output.find("y") != std::string::npos ||
              output.find("Y") != std::string::npos);
}

TEST_F(EmitterTest_519, SetBoolFormat_OnOff_WritesOn_519) {
  emitter.SetBoolFormat(YAML::OnOffBool);
  emitter << true;
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("on") != std::string::npos ||
              output.find("On") != std::string::npos ||
              output.find("ON") != std::string::npos);
}

TEST_F(EmitterTest_519, SetBoolFormat_FalseValue_519) {
  emitter.SetBoolFormat(YAML::TrueFalseBool);
  emitter << false;
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("false") != std::string::npos ||
              output.find("False") != std::string::npos ||
              output.find("FALSE") != std::string::npos);
}

TEST_F(EmitterTest_519, SetBoolFormat_UpperCase_TrueFalse_519) {
  emitter.SetBoolFormat(YAML::UpperCase);
  emitter.SetBoolFormat(YAML::TrueFalseBool);
  emitter << true;
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("TRUE") != std::string::npos ||
              output.find("true") != std::string::npos ||
              output.find("True") != std::string::npos);
}

TEST_F(EmitterTest_519, SetBoolFormat_LowerCase_YesNo_519) {
  emitter.SetBoolFormat(YAML::LowerCase);
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter << true;
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("yes") != std::string::npos ||
              output.find("y") != std::string::npos);
}

// =============================================================================
// SetOutputCharset tests
// =============================================================================

TEST_F(EmitterTest_519, SetOutputCharset_UTF8_519) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_519, SetOutputCharset_EscapeNonAscii_519) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_519, SetOutputCharset_InvalidValue_519) {
  EXPECT_FALSE(emitter.SetOutputCharset(YAML::Flow));
}

// =============================================================================
// SetStringFormat tests
// =============================================================================

TEST_F(EmitterTest_519, SetStringFormat_Auto_519) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::Auto));
}

TEST_F(EmitterTest_519, SetStringFormat_SingleQuoted_519) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_519, SetStringFormat_DoubleQuoted_519) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_519, SetStringFormat_Literal_519) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_519, SetStringFormat_Invalid_519) {
  EXPECT_FALSE(emitter.SetStringFormat(YAML::Hex));
}

// =============================================================================
// SetNullFormat tests
// =============================================================================

TEST_F(EmitterTest_519, SetNullFormat_LowerNull_519) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_519, SetNullFormat_TildeNull_519) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_519, SetNullFormat_UpperNull_519) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
}

TEST_F(EmitterTest_519, SetNullFormat_CamelNull_519) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
}

TEST_F(EmitterTest_519, SetNullFormat_Invalid_519) {
  EXPECT_FALSE(emitter.SetNullFormat(YAML::Flow));
}

// =============================================================================
// SetIntBase tests
// =============================================================================

TEST_F(EmitterTest_519, SetIntBase_Dec_519) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_519, SetIntBase_Hex_519) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_519, SetIntBase_Oct_519) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_519, SetIntBase_Invalid_519) {
  EXPECT_FALSE(emitter.SetIntBase(YAML::Flow));
}

// =============================================================================
// SetSeqFormat tests
// =============================================================================

TEST_F(EmitterTest_519, SetSeqFormat_Block_519) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_519, SetSeqFormat_Flow_519) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_519, SetSeqFormat_Invalid_519) {
  EXPECT_FALSE(emitter.SetSeqFormat(YAML::Hex));
}

// =============================================================================
// SetMapFormat tests
// =============================================================================

TEST_F(EmitterTest_519, SetMapFormat_Block_519) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_519, SetMapFormat_Flow_519) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_519, SetMapFormat_Invalid_519) {
  EXPECT_FALSE(emitter.SetMapFormat(YAML::Hex));
}

// =============================================================================
// SetIndent tests
// =============================================================================

TEST_F(EmitterTest_519, SetIndent_ValidValue_519) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_519, SetIndent_MinValue_519) {
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_519, SetIndent_TooSmall_519) {
  // Indent of 1 is typically rejected
  EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_519, SetIndent_Zero_519) {
  EXPECT_FALSE(emitter.SetIndent(0));
}

// =============================================================================
// SetPreCommentIndent / SetPostCommentIndent tests
// =============================================================================

TEST_F(EmitterTest_519, SetPreCommentIndent_ValidValue_519) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_519, SetPostCommentIndent_ValidValue_519) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_519, SetPreCommentIndent_Zero_519) {
  // Zero may be invalid
  EXPECT_FALSE(emitter.SetPreCommentIndent(0));
}

TEST_F(EmitterTest_519, SetPostCommentIndent_Zero_519) {
  EXPECT_FALSE(emitter.SetPostCommentIndent(0));
}

// =============================================================================
// SetFloatPrecision / SetDoublePrecision tests
// =============================================================================

TEST_F(EmitterTest_519, SetFloatPrecision_Valid_519) {
  EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

TEST_F(EmitterTest_519, SetDoublePrecision_Valid_519) {
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// =============================================================================
// Write string tests
// =============================================================================

TEST_F(EmitterTest_519, WriteString_SimpleString_519) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("hello") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteString_StdString_519) {
  std::string str = "world";
  emitter << str;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// Write integer tests
// =============================================================================

TEST_F(EmitterTest_519, WriteInt_Positive_519) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("42") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteInt_Negative_519) {
  emitter << -10;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("-10") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteInt_Zero_519) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("0") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteInt_HexFormat_519) {
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("0xff") != std::string::npos ||
              output.find("0xFF") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteInt_OctFormat_519) {
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("010") != std::string::npos ||
              output.find("0o10") != std::string::npos);
}

// =============================================================================
// Write bool tests
// =============================================================================

TEST_F(EmitterTest_519, WriteBool_True_519) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_519, WriteBool_False_519) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// Write Null tests
// =============================================================================

TEST_F(EmitterTest_519, WriteNull_Default_519) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("~") != std::string::npos ||
              output.find("null") != std::string::npos ||
              output.find("Null") != std::string::npos ||
              output.find("NULL") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteNull_TildeFormat_519) {
  emitter.SetNullFormat(YAML::TildeNull);
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("~") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteNull_LowerNull_519) {
  emitter.SetNullFormat(YAML::LowerNull);
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("null") != std::string::npos);
}

// =============================================================================
// Sequence tests
// =============================================================================

TEST_F(EmitterTest_519, BlockSequence_Simple_519) {
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("1") != std::string::npos);
  EXPECT_TRUE(output.find("2") != std::string::npos);
  EXPECT_TRUE(output.find("3") != std::string::npos);
}

TEST_F(EmitterTest_519, FlowSequence_Simple_519) {
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("[") != std::string::npos);
  EXPECT_TRUE(output.find("]") != std::string::npos);
}

// =============================================================================
// Map tests
// =============================================================================

TEST_F(EmitterTest_519, BlockMap_Simple_519) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("name") != std::string::npos);
  EXPECT_TRUE(output.find("test") != std::string::npos);
}

TEST_F(EmitterTest_519, FlowMap_Simple_519) {
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "val";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("{") != std::string::npos);
  EXPECT_TRUE(output.find("}") != std::string::npos);
}

// =============================================================================
// Comment tests
// =============================================================================

TEST_F(EmitterTest_519, WriteComment_519) {
  emitter << YAML::Comment("this is a comment");
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("this is a comment") != std::string::npos);
  EXPECT_TRUE(output.find("#") != std::string::npos);
}

// =============================================================================
// Anchor and Alias tests
// =============================================================================

TEST_F(EmitterTest_519, WriteAnchor_519) {
  emitter << YAML::Anchor("anchorName");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("anchorName") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteAlias_519) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("anchor1") << "value";
  emitter << YAML::Alias("anchor1");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("*anchor1") != std::string::npos);
}

// =============================================================================
// Tag tests
// =============================================================================

TEST_F(EmitterTest_519, WriteTag_519) {
  emitter << YAML::LocalTag("myTag") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("myTag") != std::string::npos);
}

// =============================================================================
// Stream constructor output tests
// =============================================================================

TEST_F(EmitterTest_519, StreamConstructor_OutputGoesToStream_519) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_TRUE(e.good());
  EXPECT_TRUE(ss.str().find("hello") != std::string::npos);
}

// =============================================================================
// Multiple documents
// =============================================================================

TEST_F(EmitterTest_519, MultipleDocuments_519) {
  emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
  emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("doc1") != std::string::npos);
  EXPECT_TRUE(output.find("doc2") != std::string::npos);
}

// =============================================================================
// Nested structures
// =============================================================================

TEST_F(EmitterTest_519, NestedMapInSeq_519) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key1" << YAML::Value << "val1";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("key1") != std::string::npos);
  EXPECT_TRUE(output.find("val1") != std::string::npos);
}

TEST_F(EmitterTest_519, NestedSeqInMap_519) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list" << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// Double and float write tests
// =============================================================================

TEST_F(EmitterTest_519, WriteDouble_519) {
  emitter << 3.14159;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("3.14") != std::string::npos);
}

TEST_F(EmitterTest_519, WriteFloat_519) {
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("2.5") != std::string::npos);
}

// =============================================================================
// RestoreGlobalModifiedSettings test
// =============================================================================

TEST_F(EmitterTest_519, RestoreGlobalModifiedSettings_519) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter.RestoreGlobalModifiedSettings();
  // After restoring, defaults should be active. Write a bool and check it still works.
  emitter << true;
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// SetLocalValue test
// =============================================================================

TEST_F(EmitterTest_519, SetLocalValue_Flow_519) {
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("[") != std::string::npos);
}

// =============================================================================
// Write char test
// =============================================================================

TEST_F(EmitterTest_519, WriteChar_519) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("A") != std::string::npos);
}

// =============================================================================
// Binary test
// =============================================================================

TEST_F(EmitterTest_519, WriteBinary_519) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary binary(data, sizeof(data));
  emitter << binary;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// Empty string test
// =============================================================================

TEST_F(EmitterTest_519, WriteEmptyString_519) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// SetStringFormat affects output
// =============================================================================

TEST_F(EmitterTest_519, SetStringFormat_DoubleQuoted_Output_519) {
  emitter.SetStringFormat(YAML::DoubleQuoted);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("\"hello\"") != std::string::npos);
}

TEST_F(EmitterTest_519, SetStringFormat_SingleQuoted_Output_519) {
  emitter.SetStringFormat(YAML::SingleQuoted);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("'hello'") != std::string::npos);
}

// =============================================================================
// size() increases after writes
// =============================================================================

TEST_F(EmitterTest_519, SizeIncreasesAfterWrite_519) {
  std::size_t initial = emitter.size();
  emitter << "test";
  EXPECT_GT(emitter.size(), initial);
}

// =============================================================================
// LongKey in map
// =============================================================================

TEST_F(EmitterTest_519, LongKeyInMap_519) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey << YAML::Key << "longkey" << YAML::Value << "val";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("longkey") != std::string::npos);
}

// =============================================================================
// SetSeqFormat globally affects sequences
// =============================================================================

TEST_F(EmitterTest_519, SetSeqFormat_GlobalFlow_519) {
  emitter.SetSeqFormat(YAML::Flow);
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("[") != std::string::npos);
}

TEST_F(EmitterTest_519, SetMapFormat_GlobalFlow_519) {
  emitter.SetMapFormat(YAML::Flow);
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_TRUE(output.find("{") != std::string::npos);
}
