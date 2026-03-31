#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// Test fixture for Emitter tests
class EmitterTest_39 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_39, DefaultConstructor_GoodState_39) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, DefaultConstructor_EmptyOutput_39) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_39, DefaultConstructor_CStrNotNull_39) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_39, DefaultConstructor_NoError_39) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_39, StreamConstructor_GoodState_39) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

TEST_F(EmitterTest_39, StreamConstructor_WritesToStream_39) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// ==================== Writing Scalars ====================

TEST_F(EmitterTest_39, WriteString_SimpleString_39) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteStdString_39) {
  std::string s = "world";
  emitter << s;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteBoolTrue_39) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteBoolFalse_39) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteChar_39) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteInt_39) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteNegativeInt_39) {
  emitter << -7;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteDouble_39) {
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteFloat_39) {
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_39, WriteNull_39) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_39, WriteBlockSequence_39) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteFlowSequence_39) {
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteEmptySequence_39) {
  emitter << YAML::BeginSeq << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, WriteNestedSequence_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2;
  emitter << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Maps ====================

TEST_F(EmitterTest_39, WriteBlockMap_39) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "John";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteFlowMap_39) {
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteEmptyMap_39) {
  emitter << YAML::BeginMap << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, WriteMapMultipleEntries_39) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key1" << YAML::Value << "val1";
  emitter << YAML::Key << "key2" << YAML::Value << "val2";
  emitter << YAML::Key << "key3" << YAML::Value << "val3";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("val3"), std::string::npos);
}

// ==================== Complex Structures ====================

TEST_F(EmitterTest_39, WriteMapWithSequenceValue_39) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items";
  emitter << YAML::Value << YAML::BeginSeq;
  emitter << "a" << "b" << "c";
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, WriteSequenceOfMaps_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "x" << YAML::Value << 1;
  emitter << YAML::EndMap;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "y" << YAML::Value << 2;
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Comments ====================

TEST_F(EmitterTest_39, WriteComment_39) {
  emitter << YAML::Comment("This is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_39, WriteAnchor_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("anchor1") << "value";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteAlias_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("anchor1") << "value";
  emitter << YAML::Alias("anchor1");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("*anchor1"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_39, WriteTag_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// ==================== Document Markers ====================

TEST_F(EmitterTest_39, WriteBeginDoc_39) {
  emitter << YAML::BeginDoc;
  emitter << "value";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteMultipleDocuments_39) {
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

// ==================== Format Settings ====================

TEST_F(EmitterTest_39, SetBoolFormat_TrueFalse_39) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_39, SetBoolFormat_YesNo_39) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_39, SetBoolFormat_OnOff_39) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("off"), std::string::npos);
}

TEST_F(EmitterTest_39, SetBoolFormat_UpperCase_39) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_39, SetBoolFormat_CamelCase_39) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_39, SetIntBase_Hex_39) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_39, SetIntBase_Oct_39) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_39, SetStringFormat_SingleQuoted_39) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_39, SetStringFormat_DoubleQuoted_39) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_39, SetSeqFormat_Flow_39) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_39, SetSeqFormat_Block_39) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-"), std::string::npos);
}

TEST_F(EmitterTest_39, SetMapFormat_Flow_39) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_39, SetMapFormat_Block_39) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, SetIndent_39) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_39, SetIndent_MinBoundary_39) {
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_39, SetPreCommentIndent_39) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_39, SetPostCommentIndent_39) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_39, SetFloatPrecision_39) {
  EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

TEST_F(EmitterTest_39, SetDoublePrecision_39) {
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// ==================== Local Value Settings ====================

TEST_F(EmitterTest_39, SetLocalValue_Flow_39) {
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_39, SetLocalIndent_39) {
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Newline ====================

TEST_F(EmitterTest_39, WriteNewline_39) {
  emitter << YAML::BeginSeq;
  emitter << "a";
  emitter << YAML::Newline;
  emitter << "b";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Size and c_str ====================

TEST_F(EmitterTest_39, SizeIncreasesAfterWrite_39) {
  std::size_t initialSize = emitter.size();
  emitter << "hello";
  EXPECT_GT(emitter.size(), initialSize);
}

TEST_F(EmitterTest_39, CStrMatchesSize_39) {
  emitter << "test";
  std::string output(emitter.c_str());
  EXPECT_EQ(output.size(), emitter.size());
}

// ==================== Binary ====================

TEST_F(EmitterTest_39, WriteBinary_39) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary binary(data, sizeof(data));
  emitter << binary;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_39, WriteBinaryEmpty_39) {
  YAML::Binary binary(nullptr, 0);
  emitter << binary;
  EXPECT_TRUE(emitter.good());
}

// ==================== Null Format ====================

TEST_F(EmitterTest_39, SetNullFormat_39) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_39, SetNullFormat_Tilde_39) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Long Key ====================

TEST_F(EmitterTest_39, WriteLongKey_39) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "long_key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("long_key"), std::string::npos);
}

// ==================== EmptyString ====================

TEST_F(EmitterTest_39, WriteEmptyString_39) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, WriteEmptyStdString_39) {
  emitter << std::string("");
  EXPECT_TRUE(emitter.good());
}

// ==================== Large values ====================

TEST_F(EmitterTest_39, WriteLargeInt_39) {
  emitter << 2147483647;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("2147483647"), std::string::npos);
}

TEST_F(EmitterTest_39, WriteZero_39) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_39, RestoreGlobalModifiedSettings_39) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

// ==================== Output Charset ====================

TEST_F(EmitterTest_39, SetOutputCharset_UTF8_39) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Chaining ====================

TEST_F(EmitterTest_39, ChainingWrites_39) {
  emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
  EXPECT_NE(output.find("c"), std::string::npos);
}

// ==================== Stream output ====================

TEST_F(EmitterTest_39, StreamConstructorMatchesCStr_39) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_EQ(std::string(e.c_str()), ss.str());
}

// ==================== Special characters in strings ====================

TEST_F(EmitterTest_39, WriteStringWithSpecialChars_39) {
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_39, WriteStringWithNewline_39) {
  emitter << "line1\nline2";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Literal and Folded ====================

TEST_F(EmitterTest_39, WriteLiteralBlock_39) {
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Long Integer Types ====================

TEST_F(EmitterTest_39, WriteLongLong_39) {
  long long val = 9223372036854775807LL;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_39, WriteUnsignedInt_39) {
  unsigned int val = 4294967295u;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("4294967295"), std::string::npos);
}

// ==================== SetLocalPrecision ====================

TEST_F(EmitterTest_39, SetLocalPrecision_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::FloatPrecision(3) << 3.14159f;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_39, SetLocalDoublePrecision_39) {
  emitter << YAML::BeginSeq;
  emitter << YAML::DoublePrecision(3) << 3.14159265358979;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}
