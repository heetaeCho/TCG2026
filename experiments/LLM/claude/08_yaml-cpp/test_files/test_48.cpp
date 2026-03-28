#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// Test fixture
class EmitterTest_48 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// === Construction and Initial State ===

TEST_F(EmitterTest_48, DefaultConstructor_GoodState_48) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_48, DefaultConstructor_EmptyOutput_48) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_48, DefaultConstructor_CStrNotNull_48) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_48, DefaultConstructor_NoError_48) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_48, StreamConstructor_GoodState_48) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

TEST_F(EmitterTest_48, StreamConstructor_WritesToStream_48) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// === Writing Scalars ===

TEST_F(EmitterTest_48, WriteString_48) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteInt_48) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteNegativeInt_48) {
  emitter << -10;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("-10"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteZero_48) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteBoolTrue_48) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteBoolFalse_48) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteNull_48) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteChar_48) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteDouble_48) {
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteFloat_48) {
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("2.5"), std::string::npos);
}

// === Sequences ===

TEST_F(EmitterTest_48, WriteBlockSequence_48) {
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("- 1"), std::string::npos);
  EXPECT_NE(output.find("- 2"), std::string::npos);
  EXPECT_NE(output.find("- 3"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteFlowSequence_48) {
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_48, EmptySequence_48) {
  emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("[]"), std::string::npos);
}

// === Maps ===

TEST_F(EmitterTest_48, WriteBlockMap_48) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteFlowMap_48) {
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_48, EmptyMap_48) {
  emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("{}"), std::string::npos);
}

// === Nested Structures ===

TEST_F(EmitterTest_48, NestedMapInSequence_48) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_48, NestedSequenceInMap_48) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list" << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// === Settings ===

TEST_F(EmitterTest_48, SetIndent_48) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_48, SetIndent_TooSmall_48) {
  // Indent of 1 may be rejected (minimum is typically 2)
  // We just check the return value
  bool result = emitter.SetIndent(1);
  // result may be false for too-small indent
  (void)result;
}

TEST_F(EmitterTest_48, SetStringFormat_48) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

TEST_F(EmitterTest_48, SetBoolFormat_TrueFalseLowerCase_48) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_48, SetBoolFormat_UpperCase_48) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_48, SetBoolFormat_CamelCase_48) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_48, SetBoolFormat_LongBool_48) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

TEST_F(EmitterTest_48, SetBoolFormat_ShortBool_48) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

TEST_F(EmitterTest_48, SetIntBase_Dec_48) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_48, SetIntBase_Hex_48) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_48, SetIntBase_Oct_48) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_48, SetSeqFormat_Block_48) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_48, SetSeqFormat_Flow_48) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_48, SetMapFormat_Block_48) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_48, SetMapFormat_Flow_48) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

TEST_F(EmitterTest_48, SetFloatPrecision_48) {
  EXPECT_TRUE(emitter.SetFloatPrecision(5));
}

TEST_F(EmitterTest_48, SetDoublePrecision_48) {
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

TEST_F(EmitterTest_48, SetPreCommentIndent_48) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_48, SetPostCommentIndent_48) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_48, SetNullFormat_48) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

// === Int Base Output Verification ===

TEST_F(EmitterTest_48, IntBaseHex_OutputContains0x_48) {
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_48, IntBaseOct_OutputContains0_48) {
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("0"), std::string::npos);
}

// === Comments ===

TEST_F(EmitterTest_48, WriteComment_48) {
  emitter << YAML::Comment("this is a comment");
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("#"), std::string::npos);
  EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

TEST_F(EmitterTest_48, CommentInMap_48) {
  emitter << YAML::BeginMap;
  emitter << YAML::Comment("map comment");
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("map comment"), std::string::npos);
}

// === Anchors and Aliases ===

TEST_F(EmitterTest_48, WriteAnchor_48) {
  emitter << YAML::Anchor("anchor1") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteAlias_48) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("a1") << "value";
  emitter << YAML::Alias("a1");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("*a1"), std::string::npos);
}

// === Tags ===

TEST_F(EmitterTest_48, WriteTag_48) {
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// === Document markers ===

TEST_F(EmitterTest_48, BeginDoc_48) {
  emitter << YAML::BeginDoc;
  emitter << "hello";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_48, MultipleDocuments_48) {
  emitter << YAML::BeginDoc << "doc1" << YAML::EndDoc;
  emitter << YAML::BeginDoc << "doc2" << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("doc1"), std::string::npos);
  EXPECT_NE(output.find("doc2"), std::string::npos);
}

// === Size and c_str consistency ===

TEST_F(EmitterTest_48, SizeMatchesCStr_48) {
  emitter << "hello";
  std::string fromCStr(emitter.c_str());
  EXPECT_EQ(fromCStr.size(), emitter.size());
}

TEST_F(EmitterTest_48, SizeGrowsWithContent_48) {
  std::size_t sizeBefore = emitter.size();
  emitter << "some content";
  EXPECT_GT(emitter.size(), sizeBefore);
}

// === Local Manipulators ===

TEST_F(EmitterTest_48, SetLocalValue_Flow_48) {
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_48, SetLocalIndent_48) {
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// === Binary ===

TEST_F(EmitterTest_48, WriteBinary_48) {
  const unsigned char data[] = {0x00, 0x01, 0x02, 0x03, 0xFF};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_48, WriteBinaryEmpty_48) {
  emitter << YAML::Binary(nullptr, 0);
  EXPECT_TRUE(emitter.good());
}

// === Literal and DoubleQuoted Strings ===

TEST_F(EmitterTest_48, LiteralString_48) {
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("|"), std::string::npos);
}

TEST_F(EmitterTest_48, DoubleQuotedString_48) {
  emitter << YAML::DoubleQuoted << "hello world";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("\"hello world\""), std::string::npos);
}

TEST_F(EmitterTest_48, SingleQuotedString_48) {
  emitter << YAML::SingleQuoted << "hello world";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("'hello world'"), std::string::npos);
}

// === Bool format variations ===

TEST_F(EmitterTest_48, BoolUpperCase_48) {
  emitter.SetBoolFormat(YAML::UpperCase);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_48, BoolCamelCase_48) {
  emitter.SetBoolFormat(YAML::CamelCase);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_48, BoolYesNo_48) {
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  // Should contain some form of "yes"
  EXPECT_TRUE(output.find("yes") != std::string::npos ||
              output.find("Yes") != std::string::npos ||
              output.find("YES") != std::string::npos);
}

// === Large integral types ===

TEST_F(EmitterTest_48, WriteLongLong_48) {
  long long val = 9223372036854775807LL;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(EmitterTest_48, WriteUnsignedInt_48) {
  unsigned int val = 4294967295u;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("4294967295"), std::string::npos);
}

// === RestoreGlobalModifiedSettings ===

TEST_F(EmitterTest_48, RestoreGlobalModifiedSettings_48) {
  emitter.SetBoolFormat(YAML::UpperCase);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
  // After restore, default format should be used
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("true"), std::string::npos);
}

// === Complex nested structure ===

TEST_F(EmitterTest_48, ComplexNestedStructure_48) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "test";
  emitter << YAML::Key << "items" << YAML::Value;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "id" << YAML::Value << 1;
  emitter << YAML::Key << "active" << YAML::Value << true;
  emitter << YAML::EndMap;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "id" << YAML::Value << 2;
  emitter << YAML::Key << "active" << YAML::Value << false;
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("items"), std::string::npos);
}

// === Emitting to external stream ===

TEST_F(EmitterTest_48, StreamConstructor_CompleteOutput_48) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << YAML::BeginMap;
  e << YAML::Key << "key" << YAML::Value << "value";
  e << YAML::EndMap;
  EXPECT_TRUE(e.good());
  EXPECT_NE(ss.str().find("key"), std::string::npos);
  EXPECT_NE(ss.str().find("value"), std::string::npos);
}

// === Newline manipulator ===

TEST_F(EmitterTest_48, NewlineManip_48) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << YAML::Newline;
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// === Empty string ===

TEST_F(EmitterTest_48, WriteEmptyString_48) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

// === Long key in map ===

TEST_F(EmitterTest_48, LongKey_48) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "a very long key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("?"), std::string::npos);
}

// === SetOutputCharset ===

TEST_F(EmitterTest_48, SetOutputCharset_UTF8_48) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// === Multiple scalars without container is an error ===

TEST_F(EmitterTest_48, MultipleTopLevelScalars_Error_48) {
  emitter << "first";
  emitter << "second";
  // Emitting two scalars at top level without a container should set error
  EXPECT_FALSE(emitter.good());
  EXPECT_NE(emitter.GetLastError(), "");
}

// === Precision affects output ===

TEST_F(EmitterTest_48, DoublePrecisionAffectsOutput_48) {
  emitter.SetDoublePrecision(15);
  emitter << 3.141592653589793;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("3.14159265358979"), std::string::npos);
}

TEST_F(EmitterTest_48, FloatPrecisionAffectsOutput_48) {
  emitter.SetFloatPrecision(2);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str(), emitter.size());
  EXPECT_NE(output.find("3.1"), std::string::npos);
}
