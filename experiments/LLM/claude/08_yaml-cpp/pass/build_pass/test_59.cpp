#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_59 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_59, DefaultConstructor_GoodState_59) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, DefaultConstructor_EmptyOutput_59) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_59, DefaultConstructor_CStrNotNull_59) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_59, DefaultConstructor_NoError_59) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_59, StreamConstructor_GoodState_59) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

TEST_F(EmitterTest_59, StreamConstructor_WritesToStream_59) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_FALSE(ss.str().empty());
}

// ==================== Write Strings ====================

TEST_F(EmitterTest_59, WriteString_Simple_59) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_59, WriteString_Empty_59) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, WriteString_SizeIncreases_59) {
  emitter << "test";
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_59, WriteCString_59) {
  const char* str = "world";
  emitter << str;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("world"), std::string::npos);
}

// ==================== Write Bool ====================

TEST_F(EmitterTest_59, WriteBool_True_59) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_59, WriteBool_False_59) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// ==================== Write Integers ====================

TEST_F(EmitterTest_59, WriteInt_59) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_59, WriteNegativeInt_59) {
  emitter << -10;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-10"), std::string::npos);
}

TEST_F(EmitterTest_59, WriteZero_59) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Write Float/Double ====================

TEST_F(EmitterTest_59, WriteFloat_59) {
  emitter << 3.14f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_59, WriteDouble_59) {
  emitter << 2.71828;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Write Char ====================

TEST_F(EmitterTest_59, WriteChar_59) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Write Null ====================

TEST_F(EmitterTest_59, WriteNull_59) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_59, BlockSequence_59) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_59, FlowSequence_59) {
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_59, EmptySequence_59) {
  emitter << YAML::BeginSeq << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Maps ====================

TEST_F(EmitterTest_59, BlockMap_59) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_59, FlowMap_59) {
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_59, EmptyMap_59) {
  emitter << YAML::BeginMap << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Nested Structures ====================

TEST_F(EmitterTest_59, NestedMapInSequence_59) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "val";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, NestedSequenceInMap_59) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list";
  emitter << YAML::Value << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Comments ====================

TEST_F(EmitterTest_59, WriteComment_59) {
  emitter << YAML::Comment("this is a comment");
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("this is a comment"), std::string::npos);
  EXPECT_NE(output.find("#"), std::string::npos);
}

// ==================== Anchor and Alias ====================

TEST_F(EmitterTest_59, WriteAnchor_59) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("myanchor") << "value";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("myanchor"), std::string::npos);
}

TEST_F(EmitterTest_59, WriteAlias_59) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("ref") << "value";
  emitter << YAML::Alias("ref");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("*ref"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_59, WriteTag_59) {
  emitter << YAML::BeginSeq;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Global Settings ====================

TEST_F(EmitterTest_59, SetIndent_Valid_59) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_59, SetIndent_MinBoundary_59) {
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_59, SetIndent_One_59) {
  // Indent of 1 may be invalid per YAML spec
  bool result = emitter.SetIndent(1);
  // We don't assert true/false since it depends on implementation
  (void)result;
}

TEST_F(EmitterTest_59, SetStringFormat_59) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_59, SetBoolFormat_TrueFalseLowerCase_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_59, SetBoolFormat_YesNo_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_59, SetBoolFormat_OnOff_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_59, SetBoolFormat_UpperCase_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_59, SetBoolFormat_CamelCase_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_59, SetBoolFormat_LongBool_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_59, SetBoolFormat_ShortBool_59) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

TEST_F(EmitterTest_59, SetIntBase_Dec_59) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_59, SetIntBase_Hex_59) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_59, SetIntBase_Oct_59) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_59, SetSeqFormat_Block_59) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_59, SetSeqFormat_Flow_59) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_59, SetMapFormat_Block_59) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_59, SetMapFormat_Flow_59) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_59, SetFloatPrecision_59) {
  EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

TEST_F(EmitterTest_59, SetDoublePrecision_59) {
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

TEST_F(EmitterTest_59, SetPreCommentIndent_59) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_59, SetPostCommentIndent_59) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_59, SetOutputCharset_UTF8_59) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_59, SetNullFormat_59) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

// ==================== Local Manipulators ====================

TEST_F(EmitterTest_59, SetLocalIndent_ViaOperator_59) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, SetLocalValue_Flow_59) {
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Binary ====================

TEST_F(EmitterTest_59, WriteBinary_59) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary binary(data, sizeof(data));
  emitter << binary;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_59, WriteBinary_Empty_59) {
  YAML::Binary binary(nullptr, 0);
  emitter << binary;
  EXPECT_TRUE(emitter.good());
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_59, BeginAndEndDoc_59) {
  emitter << YAML::BeginDoc;
  emitter << "hello";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_59, MultipleDocuments_59) {
  emitter << YAML::BeginDoc;
  emitter << "first";
  emitter << YAML::EndDoc;
  emitter << YAML::BeginDoc;
  emitter << "second";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
}

// ==================== Hex Int Output ====================

TEST_F(EmitterTest_59, HexIntBase_59) {
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_59, OctIntBase_59) {
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

// ==================== Bool Format Variations ====================

TEST_F(EmitterTest_59, BoolFormat_TrueFalse_59) {
  emitter.SetBoolFormat(YAML::TrueFalseBool);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Should contain some variant of "true"
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_59, BoolFormat_YesNo_59) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter << true;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, BoolFormat_OnOff_59) {
  emitter.SetBoolFormat(YAML::OnOffBool);
  emitter << false;
  EXPECT_TRUE(emitter.good());
}

// ==================== String Format Variations ====================

TEST_F(EmitterTest_59, StringFormat_SingleQuoted_59) {
  emitter << YAML::SingleQuoted << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_59, StringFormat_DoubleQuoted_59) {
  emitter << YAML::DoubleQuoted << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_59, StringFormat_Literal_59) {
  emitter << YAML::Literal << "line1\nline2";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== LongKey ====================

TEST_F(EmitterTest_59, LongKey_59) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey << YAML::Key << "long_key_name" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Stream constructor output verification ====================

TEST_F(EmitterTest_59, StreamConstructor_OutputMatchesCStr_59) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_EQ(std::string(e.c_str()), ss.str());
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_59, RestoreGlobalModifiedSettings_59) {
  emitter.SetIndent(6);
  emitter.RestoreGlobalModifiedSettings();
  // After restoring, emitter should still be good
  EXPECT_TRUE(emitter.good());
}

// ==================== Complex structures ====================

TEST_F(EmitterTest_59, ComplexNestedStructure_59) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "sequence" << YAML::Value;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "nested_key" << YAML::Value << "nested_value";
  emitter << YAML::EndMap;
  emitter << "simple_item";
  emitter << 42;
  emitter << YAML::EndSeq;
  emitter << YAML::Key << "boolean" << YAML::Value << true;
  emitter << YAML::Key << "null_val" << YAML::Value << YAML::Null;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("sequence"), std::string::npos);
  EXPECT_NE(output.find("nested_key"), std::string::npos);
  EXPECT_NE(output.find("nested_value"), std::string::npos);
  EXPECT_NE(output.find("simple_item"), std::string::npos);
  EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== Newline ====================

TEST_F(EmitterTest_59, NewlineManip_59) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << YAML::Newline;
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Multiple scalar writes at top level ====================

TEST_F(EmitterTest_59, MultipleTopLevelScalars_ErrorState_59) {
  emitter << "first";
  emitter << "second";
  // Writing two scalars at top level without document separators may cause error
  // The behavior depends on implementation; we just check if good() reflects state
  // We don't assert true or false specifically
  (void)emitter.good();
}

// ==================== Copy prevention ====================

// Emitter is non-copyable, which is enforced at compile time
// No runtime test needed, but we verify the interface is usable

TEST_F(EmitterTest_59, Emitter_IsUsableAfterConstruction_59) {
  YAML::Emitter e;
  EXPECT_TRUE(e.good());
  EXPECT_EQ(e.size(), 0u);
  e << "test";
  EXPECT_TRUE(e.good());
  EXPECT_GT(e.size(), 0u);
}

// ==================== Large data ====================

TEST_F(EmitterTest_59, LargeSequence_59) {
  emitter << YAML::BeginSeq;
  for (int i = 0; i < 1000; ++i) {
    emitter << i;
  }
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 1000u);
}

TEST_F(EmitterTest_59, LargeMap_59) {
  emitter << YAML::BeginMap;
  for (int i = 0; i < 100; ++i) {
    emitter << YAML::Key << ("key" + std::to_string(i));
    emitter << YAML::Value << i;
  }
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Special string values ====================

TEST_F(EmitterTest_59, StringWithSpecialChars_59) {
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  // Strings with colons should be quoted or handled
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_59, StringWithNewlines_59) {
  emitter << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_59, StringWithHashMark_59) {
  emitter << "value # not a comment";
  EXPECT_TRUE(emitter.good());
}

// ==================== Precision settings ====================

TEST_F(EmitterTest_59, FloatPrecision_59) {
  emitter.SetFloatPrecision(2);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, DoublePrecision_59) {
  emitter.SetDoublePrecision(15);
  emitter << 3.141592653589793;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_59, LocalPrecision_59) {
  emitter << YAML::BeginSeq;
  emitter << YAML::FloatPrecision(3) << 3.14159f;
  emitter << YAML::DoublePrecision(5) << 2.71828182845;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}
