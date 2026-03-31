#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>
#include <vector>

class EmitterTest_515 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_515, DefaultConstructor_IsGood_515) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, DefaultConstructor_EmptyOutput_515) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_515, DefaultConstructor_CStrNotNull_515) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_515, DefaultConstructor_NoError_515) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_515, StreamConstructor_IsGood_515) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

// ==================== Writing Scalars ====================

TEST_F(EmitterTest_515, WriteString_515) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteStringStd_515) {
  std::string str = "world";
  emitter << str;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_515, WriteBoolTrue_515) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Default bool format should produce "true"
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteBoolFalse_515) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteChar_515) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteInteger_515) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteNegativeInteger_515) {
  emitter << -7;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteDouble_515) {
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteFloat_515) {
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_515, WriteNull_515) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_515, WriteBlockSequence_515) {
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

TEST_F(EmitterTest_515, WriteFlowSequence_515) {
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteEmptySequence_515) {
  emitter << YAML::BeginSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Maps ====================

TEST_F(EmitterTest_515, WriteBlockMap_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "John";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteFlowMap_515) {
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteEmptyMap_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_515, WriteNestedMapInSeq_515) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, WriteNestedSeqInMap_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list";
  emitter << YAML::Value;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Comments ====================

TEST_F(EmitterTest_515, WriteComment_515) {
  emitter << YAML::Comment("This is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_515, WriteAnchor_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "anchor_node";
  emitter << YAML::Value << YAML::Anchor("myanchor") << "anchored_value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteAlias_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "first";
  emitter << YAML::Value << YAML::Anchor("ref") << "value";
  emitter << YAML::Key << "second";
  emitter << YAML::Value << YAML::Alias("ref");
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("*ref"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_515, WriteTag_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "tagged";
  emitter << YAML::Value << YAML::LocalTag("mytype") << "tagged_value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!mytype"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteVerbatimTag_515) {
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!<tag:yaml.org,2002:str>"), std::string::npos);
}

// ==================== Binary ====================

TEST_F(EmitterTest_515, WriteBinary_515) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Settings ====================

TEST_F(EmitterTest_515, SetStringFormat_515) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_515, SetStringFormatDoubleQuoted_515) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_515, SetBoolFormat_TrueFalse_515) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_515, SetBoolFormat_YesNo_515) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Should contain "yes" or "Yes" or "YES"
  std::string lower_output = output;
  std::transform(lower_output.begin(), lower_output.end(), lower_output.begin(), ::tolower);
  EXPECT_NE(lower_output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_515, SetBoolFormat_OnOff_515) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  std::string lower_output = output;
  std::transform(lower_output.begin(), lower_output.end(), lower_output.begin(), ::tolower);
  EXPECT_NE(lower_output.find("off"), std::string::npos);
}

TEST_F(EmitterTest_515, SetNullFormat_Tilde_515) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_515, SetNullFormat_LowerNull_515) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_515, SetIntBase_Hex_515) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_515, SetIntBase_Oct_515) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_515, SetSeqFormat_Flow_515) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_515, SetMapFormat_Flow_515) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_515, SetIndent_515) {
  EXPECT_TRUE(emitter.SetIndent(4));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key";
  emitter << YAML::Value << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, SetIndent_MinValue_515) {
  // Indent of 2 should be acceptable
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_515, SetPreCommentIndent_515) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_515, SetPostCommentIndent_515) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_515, SetFloatPrecision_515) {
  EXPECT_TRUE(emitter.SetFloatPrecision(3));
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, SetDoublePrecision_515) {
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
  emitter << 3.14159265358979;
  EXPECT_TRUE(emitter.good());
}

// ==================== Output to Stream ====================

TEST_F(EmitterTest_515, OutputToStream_515) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_TRUE(e.good());
  // The stream should contain the output
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

TEST_F(EmitterTest_515, OutputToStreamMap_515) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << YAML::BeginMap;
  e << YAML::Key << "key" << YAML::Value << "val";
  e << YAML::EndMap;
  EXPECT_TRUE(e.good());
  EXPECT_NE(ss.str().find("key"), std::string::npos);
  EXPECT_NE(ss.str().find("val"), std::string::npos);
}

// ==================== Manipulators ====================

TEST_F(EmitterTest_515, SetLocalValue_Flow_515) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, LongKey_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "long_key";
  emitter << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Newline ====================

TEST_F(EmitterTest_515, Newline_515) {
  emitter << YAML::BeginSeq;
  emitter << "a";
  emitter << YAML::Newline;
  emitter << "b";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_515, MultipleDocuments_515) {
  emitter << YAML::BeginDoc;
  emitter << "doc1";
  emitter << YAML::EndDoc;
  emitter << YAML::BeginDoc;
  emitter << "doc2";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("---"), std::string::npos);
  EXPECT_NE(output.find("doc1"), std::string::npos);
  EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== Size and c_str ====================

TEST_F(EmitterTest_515, SizeMatchesCStr_515) {
  emitter << "test string";
  EXPECT_EQ(emitter.size(), std::string(emitter.c_str()).size());
}

TEST_F(EmitterTest_515, SizeGrowsWithContent_515) {
  std::size_t initial = emitter.size();
  emitter << "hello";
  EXPECT_GT(emitter.size(), initial);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_515, RestoreGlobalModifiedSettings_515) {
  emitter.SetStringFormat(YAML::SingleQuoted);
  emitter.RestoreGlobalModifiedSettings();
  // After restore, emitter should still be good
  EXPECT_TRUE(emitter.good());
}

// ==================== Complex Structures ====================

TEST_F(EmitterTest_515, ComplexNestedStructure_515) {
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

// ==================== Boundary Cases ====================

TEST_F(EmitterTest_515, WriteEmptyString_515) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, WriteLongString_515) {
  std::string longStr(10000, 'x');
  emitter << longStr;
  EXPECT_TRUE(emitter.good());
  EXPECT_GE(emitter.size(), 10000u);
}

TEST_F(EmitterTest_515, WriteStringWithSpecialChars_515) {
  emitter << "hello: world\nnewline\ttab";
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, WriteZero_515) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_515, WriteLargeInteger_515) {
  emitter << 9999999999LL;
  EXPECT_TRUE(emitter.good());
}

// ==================== Invalid Format Settings ====================

TEST_F(EmitterTest_515, SetStringFormatInvalidValue_515) {
  // Pass a MANIP that is not a string format
  bool result = emitter.SetStringFormat(YAML::Hex);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_515, SetBoolFormatInvalidValue_515) {
  bool result = emitter.SetBoolFormat(YAML::Hex);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_515, SetIntBaseInvalidValue_515) {
  bool result = emitter.SetIntBase(YAML::SingleQuoted);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_515, SetSeqFormatInvalidValue_515) {
  bool result = emitter.SetSeqFormat(YAML::Hex);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_515, SetMapFormatInvalidValue_515) {
  bool result = emitter.SetMapFormat(YAML::Hex);
  EXPECT_FALSE(result);
}

// ==================== Charset ====================

TEST_F(EmitterTest_515, SetOutputCharsetUTF8_515) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Emitter Not Copyable ====================

TEST_F(EmitterTest_515, EmitterNotCopyable_515) {
  EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
  EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}

// ==================== Local Manipulator Precision ====================

TEST_F(EmitterTest_515, SetLocalPrecision_515) {
  emitter << YAML::BeginSeq;
  emitter << YAML::DoublePrecision(15) << 3.141592653589793;
  emitter << 3.141592653589793;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_515, SetLocalIndent_515) {
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Flow and Block Mixed ====================

TEST_F(EmitterTest_515, FlowSeqInsideBlockMap_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items";
  emitter << YAML::Value << YAML::Flow << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_515, FlowMapInsideBlockSeq_515) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
}

// ==================== Literal and other string formats ====================

TEST_F(EmitterTest_515, LiteralStringFormat_515) {
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Multiple Keys in Map ====================

TEST_F(EmitterTest_515, MultipleKeysInMap_515) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k1" << YAML::Value << "v1";
  emitter << YAML::Key << "k2" << YAML::Value << "v2";
  emitter << YAML::Key << "k3" << YAML::Value << "v3";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("k1"), std::string::npos);
  EXPECT_NE(output.find("k2"), std::string::npos);
  EXPECT_NE(output.find("k3"), std::string::npos);
}

// ==================== YAML::BeginDoc without explicit EndDoc ====================

TEST_F(EmitterTest_515, SingleDocumentExplicitStart_515) {
  emitter << YAML::BeginDoc;
  emitter << "content";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("---"), std::string::npos);
}

// ==================== Emitter output to ostream matches c_str ====================

TEST_F(EmitterTest_515, StreamOutputMatchesCStr_515) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << YAML::BeginMap;
  e << YAML::Key << "test" << YAML::Value << 42;
  e << YAML::EndMap;
  EXPECT_TRUE(e.good());
  // Stream content and c_str should be consistent
  EXPECT_NE(ss.str().find("test"), std::string::npos);
  EXPECT_NE(ss.str().find("42"), std::string::npos);
}
