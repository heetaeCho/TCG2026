#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// Test fixture for Emitter tests
class EmitterTest_51 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// === Basic Construction and State Tests ===

TEST_F(EmitterTest_51, DefaultConstructor_GoodState_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_51, StreamConstructor_GoodState_51) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_51, DefaultConstructor_EmptyOutput_51) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_51, DefaultConstructor_CStr_51) {
  YAML::Emitter emitter;
  EXPECT_NE(emitter.c_str(), nullptr);
  EXPECT_STREQ(emitter.c_str(), "");
}

TEST_F(EmitterTest_51, GetLastError_NoError_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
  // When good, GetLastError should return empty string
  EXPECT_EQ(emitter.GetLastError(), "");
}

// === operator<< for unsigned short ===

TEST_F(EmitterTest_51, WriteUnsignedShort_Zero_51) {
  YAML::Emitter emitter;
  emitter << static_cast<unsigned short>(0);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "0");
}

TEST_F(EmitterTest_51, WriteUnsignedShort_TypicalValue_51) {
  YAML::Emitter emitter;
  emitter << static_cast<unsigned short>(42);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_51, WriteUnsignedShort_MaxValue_51) {
  YAML::Emitter emitter;
  unsigned short maxVal = 65535;
  emitter << maxVal;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "65535");
}

TEST_F(EmitterTest_51, WriteUnsignedShort_One_51) {
  YAML::Emitter emitter;
  emitter << static_cast<unsigned short>(1);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "1");
}

TEST_F(EmitterTest_51, WriteUnsignedShort_ToStream_51) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << static_cast<unsigned short>(123);
  EXPECT_TRUE(emitter.good());
  EXPECT_NE(ss.str().find("123"), std::string::npos);
}

// === Write string tests ===

TEST_F(EmitterTest_51, WriteString_Simple_51) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteString_StdString_51) {
  YAML::Emitter emitter;
  std::string str = "world";
  emitter << str;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteString_EmptyString_51) {
  YAML::Emitter emitter;
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

// === Write bool tests ===

TEST_F(EmitterTest_51, WriteBool_True_51) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteBool_False_51) {
  YAML::Emitter emitter;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("false"), std::string::npos);
}

// === Write int tests ===

TEST_F(EmitterTest_51, WriteInt_Positive_51) {
  YAML::Emitter emitter;
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "42");
}

TEST_F(EmitterTest_51, WriteInt_Negative_51) {
  YAML::Emitter emitter;
  emitter << -10;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "-10");
}

TEST_F(EmitterTest_51, WriteInt_Zero_51) {
  YAML::Emitter emitter;
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_EQ(output, "0");
}

// === Write double/float tests ===

TEST_F(EmitterTest_51, WriteDouble_51) {
  YAML::Emitter emitter;
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteFloat_51) {
  YAML::Emitter emitter;
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("2.5"), std::string::npos);
}

// === Null tests ===

TEST_F(EmitterTest_51, WriteNull_51) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// === Sequence tests ===

TEST_F(EmitterTest_51, WriteBlockSequence_51) {
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

TEST_F(EmitterTest_51, WriteFlowSequence_51) {
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

// === Map tests ===

TEST_F(EmitterTest_51, WriteBlockMap_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteFlowMap_51) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

// === Anchor and Alias tests ===

TEST_F(EmitterTest_51, WriteAnchor_51) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("anchor1");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteAlias_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("item") << "value";
  emitter << YAML::Alias("item");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("*item"), std::string::npos);
}

// === Tag tests ===

TEST_F(EmitterTest_51, WriteTag_51) {
  YAML::Emitter emitter;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// === Comment tests ===

TEST_F(EmitterTest_51, WriteComment_51) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("this is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// === Setting tests ===

TEST_F(EmitterTest_51, SetStringFormat_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_51, SetBoolFormat_TrueFalse_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_51, SetBoolFormat_UpperCase_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_51, SetIntBase_Hex_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_51, SetIntBase_Oct_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_51, SetSeqFormat_Flow_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_51, SetMapFormat_Flow_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_51, SetIndent_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_51, SetPreCommentIndent_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_51, SetPostCommentIndent_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_51, SetFloatPrecision_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_51, SetDoublePrecision_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// === Hex integer base with unsigned short ===

TEST_F(EmitterTest_51, WriteUnsignedShort_HexBase_51) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Hex);
  emitter << static_cast<unsigned short>(255);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0xff"), std::string::npos);
}

TEST_F(EmitterTest_51, WriteUnsignedShort_OctBase_51) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Oct);
  emitter << static_cast<unsigned short>(8);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("010"), std::string::npos);
}

// === Size after writing ===

TEST_F(EmitterTest_51, SizeIncreasesAfterWrite_51) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
  emitter << "hello";
  EXPECT_GT(emitter.size(), 0u);
}

// === Nested structures ===

TEST_F(EmitterTest_51, NestedMapInSeq_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("key"), std::string::npos);
  EXPECT_NE(output.find("value"), std::string::npos);
}

TEST_F(EmitterTest_51, NestedSeqInMap_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items" << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// === Stream output ===

TEST_F(EmitterTest_51, StreamConstructor_OutputMatchesCStr_51) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << "test_value";
  EXPECT_TRUE(emitter.good());
  // The stream should contain the same output as c_str()
  std::string c_str_output(emitter.c_str());
  EXPECT_EQ(ss.str(), c_str_output);
}

// === Write char ===

TEST_F(EmitterTest_51, WriteChar_51) {
  YAML::Emitter emitter;
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("A"), std::string::npos);
}

// === Multiple documents ===

TEST_F(EmitterTest_51, WriteMultipleScalars_InSequence_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << static_cast<unsigned short>(10);
  emitter << static_cast<unsigned short>(20);
  emitter << static_cast<unsigned short>(30);
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("10"), std::string::npos);
  EXPECT_NE(output.find("20"), std::string::npos);
  EXPECT_NE(output.find("30"), std::string::npos);
}

// === Binary tests ===

TEST_F(EmitterTest_51, WriteBinary_51) {
  YAML::Emitter emitter;
  const unsigned char data[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// === RestoreGlobalModifiedSettings ===

TEST_F(EmitterTest_51, RestoreGlobalModifiedSettings_51) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Hex);
  emitter.RestoreGlobalModifiedSettings();
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  // After restore, should be back to decimal
  EXPECT_EQ(output, "42");
}

// === SetLocalValue ===

TEST_F(EmitterTest_51, SetLocalValue_Flow_51) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

// === Null format ===

TEST_F(EmitterTest_51, SetNullFormat_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

// === Emitter with unsigned short in map context ===

TEST_F(EmitterTest_51, UnsignedShortInMapValue_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "port" << YAML::Value << static_cast<unsigned short>(8080);
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("port"), std::string::npos);
  EXPECT_NE(output.find("8080"), std::string::npos);
}

// === Boundary: SetIndent with small values ===

TEST_F(EmitterTest_51, SetIndent_MinimumValue_51) {
  YAML::Emitter emitter;
  // Indent of 2 is typically the minimum valid value
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_51, SetIndent_LargeValue_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(10));
}

// === Output charset ===

TEST_F(EmitterTest_51, SetOutputCharset_UTF8_51) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// === Long key in map ===

TEST_F(EmitterTest_51, LongKey_51) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "very_long_key_name" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// === Verify unsigned short is properly handled as integral type ===

TEST_F(EmitterTest_51, UnsignedShort_ReturnsSameEmitter_51) {
  YAML::Emitter emitter;
  YAML::Emitter& result = (emitter << static_cast<unsigned short>(5));
  EXPECT_EQ(&result, &emitter);
}

// === Double precision setting affects output ===

TEST_F(EmitterTest_51, DoublePrecision_Affects_Output_51) {
  YAML::Emitter emitter;
  emitter.SetDoublePrecision(3);
  emitter << 3.14159265358979;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  // With precision 3, we expect a shorter representation
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

// === Float precision setting ===

TEST_F(EmitterTest_51, FloatPrecision_Affects_Output_51) {
  YAML::Emitter emitter;
  emitter.SetFloatPrecision(2);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("3.1"), std::string::npos);
}
