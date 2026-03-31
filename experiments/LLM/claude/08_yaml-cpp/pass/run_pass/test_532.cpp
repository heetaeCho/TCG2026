#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_532 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_532, DefaultConstructor_IsGood_532) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, DefaultConstructor_EmptyOutput_532) {
  EXPECT_EQ(std::string(""), std::string(emitter.c_str()));
  EXPECT_EQ(0u, emitter.size());
}

TEST_F(EmitterTest_532, DefaultConstructor_NoError_532) {
  EXPECT_EQ("", emitter.GetLastError());
}

TEST_F(EmitterTest_532, StreamConstructor_IsGood_532) {
  std::stringstream ss;
  YAML::Emitter streamEmitter(ss);
  EXPECT_TRUE(streamEmitter.good());
}

// ==================== SetLocalPrecision ====================

TEST_F(EmitterTest_532, SetLocalPrecision_BothPositive_ReturnsEmitter_532) {
  YAML::_Precision prec(5, 10);
  YAML::Emitter& result = emitter.SetLocalPrecision(prec);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetLocalPrecision_FloatNegative_OnlyDoubleSet_532) {
  YAML::_Precision prec(-1, 10);
  YAML::Emitter& result = emitter.SetLocalPrecision(prec);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetLocalPrecision_DoubleNegative_OnlyFloatSet_532) {
  YAML::_Precision prec(5, -1);
  YAML::Emitter& result = emitter.SetLocalPrecision(prec);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetLocalPrecision_BothNegative_NothingSet_532) {
  YAML::_Precision prec(-1, -1);
  YAML::Emitter& result = emitter.SetLocalPrecision(prec);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetLocalPrecision_ZeroPrecision_532) {
  YAML::_Precision prec(0, 0);
  YAML::Emitter& result = emitter.SetLocalPrecision(prec);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetLocalPrecision_LargePrecision_532) {
  YAML::_Precision prec(100, 200);
  YAML::Emitter& result = emitter.SetLocalPrecision(prec);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalPrecision affects float output ====================

TEST_F(EmitterTest_532, SetLocalPrecision_AffectsFloatOutput_532) {
  YAML::_Precision prec(2, 2);
  emitter.SetLocalPrecision(prec);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_532, SetLocalPrecision_AffectsDoubleOutput_532) {
  YAML::_Precision prec(2, 3);
  emitter.SetLocalPrecision(prec);
  emitter << 3.14159265358979;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

// ==================== Write operations ====================

TEST_F(EmitterTest_532, WriteString_532) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("hello"));
}

TEST_F(EmitterTest_532, WriteStdString_532) {
  std::string s = "world";
  emitter << s;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("world"));
}

TEST_F(EmitterTest_532, WriteBoolTrue_532) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_532, WriteBoolFalse_532) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_532, WriteChar_532) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("A"));
}

TEST_F(EmitterTest_532, WriteNull_532) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_532, WriteInteger_532) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("42"));
}

// ==================== Sequences ====================

TEST_F(EmitterTest_532, WriteSequence_532) {
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_532, WriteFlowSequence_532) {
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("["));
  EXPECT_NE(std::string::npos, output.find("]"));
}

// ==================== Maps ====================

TEST_F(EmitterTest_532, WriteMap_532) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("name"));
  EXPECT_NE(std::string::npos, output.find("test"));
}

TEST_F(EmitterTest_532, WriteFlowMap_532) {
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("{"));
  EXPECT_NE(std::string::npos, output.find("}"));
}

// ==================== Comments ====================

TEST_F(EmitterTest_532, WriteComment_532) {
  emitter << YAML::Comment("this is a comment");
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("this is a comment"));
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_532, WriteAnchorAndAlias_532) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("anchor1") << "value";
  emitter << YAML::Alias("anchor1");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("anchor1"));
}

// ==================== Tag ====================

TEST_F(EmitterTest_532, WriteTag_532) {
  emitter << YAML::BeginSeq;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "tagged";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Global Settings ====================

TEST_F(EmitterTest_532, SetOutputCharset_532) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetStringFormat_532) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetBoolFormat_532) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetNullFormat_532) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetIntBase_Dec_532) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetIntBase_Hex_532) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetIntBase_Oct_532) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetSeqFormat_532) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetMapFormat_532) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetIndent_532) {
  EXPECT_TRUE(emitter.SetIndent(4));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetPreCommentIndent_532) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetPostCommentIndent_532) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetFloatPrecision_532) {
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_532, SetDoublePrecision_532) {
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
  EXPECT_TRUE(emitter.good());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_532, RestoreGlobalModifiedSettings_532) {
  emitter.SetIndent(6);
  emitter.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue ====================

TEST_F(EmitterTest_532, SetLocalValue_Flow_532) {
  YAML::Emitter& result = emitter.SetLocalValue(YAML::Flow);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalIndent ====================

TEST_F(EmitterTest_532, SetLocalIndent_532) {
  YAML::_Indent indent(4);
  YAML::Emitter& result = emitter.SetLocalIndent(indent);
  EXPECT_EQ(&emitter, &result);
  EXPECT_TRUE(emitter.good());
}

// ==================== Stream output ====================

TEST_F(EmitterTest_532, StreamConstructor_OutputToStream_532) {
  std::stringstream ss;
  YAML::Emitter streamEmitter(ss);
  streamEmitter << "hello";
  EXPECT_TRUE(streamEmitter.good());
  EXPECT_NE(std::string::npos, ss.str().find("hello"));
}

// ==================== Size tracking ====================

TEST_F(EmitterTest_532, SizeIncreasesAfterWrite_532) {
  EXPECT_EQ(0u, emitter.size());
  emitter << "test";
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== c_str consistency ====================

TEST_F(EmitterTest_532, CStrConsistentWithSize_532) {
  emitter << "hello world";
  std::string output(emitter.c_str());
  EXPECT_EQ(output.size(), emitter.size());
}

// ==================== Complex document ====================

TEST_F(EmitterTest_532, ComplexDocument_532) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "seq" << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::Key << "map" << YAML::Value;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "nested" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Binary data ====================

TEST_F(EmitterTest_532, WriteBinary_532) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0xFF};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Precision chaining ====================

TEST_F(EmitterTest_532, SetLocalPrecision_Chaining_532) {
  YAML::_Precision prec1(3, 6);
  YAML::_Precision prec2(5, 10);
  emitter.SetLocalPrecision(prec1).SetLocalPrecision(prec2);
  EXPECT_TRUE(emitter.good());
}

// ==================== Float with specific precision ====================

TEST_F(EmitterTest_532, FloatPrecision_LowPrecision_532) {
  emitter.SetFloatPrecision(1);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_532, DoublePrecision_HighPrecision_532) {
  emitter.SetDoublePrecision(15);
  emitter << 3.141592653589793;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_FALSE(output.empty());
}

// ==================== Multiple documents ====================

TEST_F(EmitterTest_532, MultipleDocuments_532) {
  emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
  emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("doc1"));
  EXPECT_NE(std::string::npos, output.find("doc2"));
}

// ==================== Hex int output ====================

TEST_F(EmitterTest_532, HexIntOutput_532) {
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("0x"));
}

// ==================== Oct int output ====================

TEST_F(EmitterTest_532, OctIntOutput_532) {
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(std::string::npos, output.find("0"));
}
