#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_57 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// =============================================================================
// Basic construction and initial state tests
// =============================================================================

TEST_F(EmitterTest_57, DefaultConstructor_GoodState_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_57, DefaultConstructor_EmptyOutput_57) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_57, DefaultConstructor_CStrNotNull_57) {
  YAML::Emitter emitter;
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_57, DefaultConstructor_NoError_57) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_57, StreamConstructor_GoodState_57) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// Writing basic scalar types
// =============================================================================

TEST_F(EmitterTest_57, WriteString_57) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteStdString_57) {
  YAML::Emitter emitter;
  std::string value = "world";
  emitter << value;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteInt_57) {
  YAML::Emitter emitter;
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteNegativeInt_57) {
  YAML::Emitter emitter;
  emitter << -100;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-100"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteZero_57) {
  YAML::Emitter emitter;
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteBoolTrue_57) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_57, WriteBoolFalse_57) {
  YAML::Emitter emitter;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_57, WriteDouble_57) {
  YAML::Emitter emitter;
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteFloat_57) {
  YAML::Emitter emitter;
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("2.5"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteChar_57) {
  YAML::Emitter emitter;
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_57, WriteNull_57) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// Sequence tests
// =============================================================================

TEST_F(EmitterTest_57, WriteBlockSequence_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("1"), std::string::npos);
  EXPECT_NE(output.find("2"), std::string::npos);
  EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteFlowSequence_57) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteEmptySequence_57) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("[]"), std::string::npos);
}

// =============================================================================
// Map tests
// =============================================================================

TEST_F(EmitterTest_57, WriteBlockMap_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteFlowMap_57) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteEmptyMap_57) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{}"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteMapMultipleEntries_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key1" << YAML::Value << "val1";
  emitter << YAML::Key << "key2" << YAML::Value << "val2";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("val1"), std::string::npos);
  EXPECT_NE(output.find("key2"), std::string::npos);
  EXPECT_NE(output.find("val2"), std::string::npos);
}

// =============================================================================
// Nested structures
// =============================================================================

TEST_F(EmitterTest_57, WriteNestedMapInSeq_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "x" << YAML::Value << 1;
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_57, WriteNestedSeqInMap_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items";
  emitter << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("items"), std::string::npos);
}

// =============================================================================
// Output to stream constructor
// =============================================================================

TEST_F(EmitterTest_57, StreamConstructor_OutputGoesToStream_57) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_57, StreamConstructor_SequenceGoesToStream_57) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find("["), std::string::npos);
}

// =============================================================================
// Settings tests
// =============================================================================

TEST_F(EmitterTest_57, SetBoolFormat_TrueFalse_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_57, SetBoolFormat_YesNo_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_57, SetBoolFormat_UpperCase_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_57, SetBoolFormat_CamelCase_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_57, SetIntBase_Hex_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_57, SetIntBase_Oct_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_57, SetSeqFormat_Flow_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_57, SetMapFormat_Flow_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_57, SetIndent_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_57, SetPreCommentIndent_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_57, SetPostCommentIndent_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_57, SetFloatPrecision_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(3));
}

TEST_F(EmitterTest_57, SetDoublePrecision_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

TEST_F(EmitterTest_57, SetNullFormat_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_57, SetStringFormat_SingleQuoted_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_57, SetStringFormat_DoubleQuoted_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// =============================================================================
// Comment tests
// =============================================================================

TEST_F(EmitterTest_57, WriteComment_57) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("This is a comment");
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("#"), std::string::npos);
  EXPECT_NE(output.find("This is a comment"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteCommentInMap_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Comment("map comment");
  emitter << YAML::Key << "key" << YAML::Value << "val";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("map comment"), std::string::npos);
}

// =============================================================================
// Anchor and Alias tests
// =============================================================================

TEST_F(EmitterTest_57, WriteAnchor_57) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("myanchor");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteAlias_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("item") << "value";
  emitter << YAML::Alias("item");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("*item"), std::string::npos);
}

// =============================================================================
// Tag tests
// =============================================================================

TEST_F(EmitterTest_57, WriteTag_57) {
  YAML::Emitter emitter;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// =============================================================================
// Binary tests
// =============================================================================

TEST_F(EmitterTest_57, WriteBinary_57) {
  YAML::Emitter emitter;
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary binary(data, sizeof(data));
  emitter << binary;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// size() and c_str() tests
// =============================================================================

TEST_F(EmitterTest_57, SizeIncreasesAfterWrite_57) {
  YAML::Emitter emitter;
  std::size_t before = emitter.size();
  emitter << "something";
  std::size_t after = emitter.size();
  EXPECT_GT(after, before);
}

TEST_F(EmitterTest_57, CStrMatchesSize_57) {
  YAML::Emitter emitter;
  emitter << "test";
  std::string str(emitter.c_str());
  EXPECT_EQ(str.size(), emitter.size());
}

// =============================================================================
// Precision tests
// =============================================================================

TEST_F(EmitterTest_57, DoublePrecision_57) {
  YAML::Emitter emitter;
  emitter.SetDoublePrecision(15);
  emitter << 3.141592653589793;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("3.14159265358979"), std::string::npos);
}

TEST_F(EmitterTest_57, FloatPrecision_57) {
  YAML::Emitter emitter;
  emitter.SetFloatPrecision(2);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("3.1"), std::string::npos);
}

TEST_F(EmitterTest_57, LocalPrecision_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::DoublePrecision(2) << 3.14159;
  emitter << 3.14159;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// Document separator tests
// =============================================================================

TEST_F(EmitterTest_57, BeginDoc_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc;
  emitter << "hello";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_57, MultipleDocuments_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc;
  emitter << "doc1";
  emitter << YAML::EndDoc;
  emitter << YAML::BeginDoc;
  emitter << "doc2";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("doc1"), std::string::npos);
  EXPECT_NE(output.find("doc2"), std::string::npos);
}

// =============================================================================
// Local value / manipulator tests
// =============================================================================

TEST_F(EmitterTest_57, LocalFlow_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_57, LocalIndent_57) {
  YAML::Emitter emitter;
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// RestoreGlobalModifiedSettings test
// =============================================================================

TEST_F(EmitterTest_57, RestoreGlobalModifiedSettings_57) {
  YAML::Emitter emitter;
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
}

// =============================================================================
// Long unsigned types
// =============================================================================

TEST_F(EmitterTest_57, WriteLongInt_57) {
  YAML::Emitter emitter;
  long long val = 9223372036854775807LL;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteUnsignedInt_57) {
  YAML::Emitter emitter;
  unsigned int val = 4294967295u;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("4294967295"), std::string::npos);
}

// =============================================================================
// Edge cases: empty string
// =============================================================================

TEST_F(EmitterTest_57, WriteEmptyString_57) {
  YAML::Emitter emitter;
  emitter << "";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_57, WriteStringWithSpecialChars_57) {
  YAML::Emitter emitter;
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// Complex nested structures
// =============================================================================

TEST_F(EmitterTest_57, ComplexNestedStructure_57) {
  YAML::Emitter emitter;
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

// =============================================================================
// Operator<< for double (the specific code in the prompt)
// =============================================================================

TEST_F(EmitterTest_57, OperatorDoublePositive_57) {
  YAML::Emitter emitter;
  emitter << 1.5;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("1.5"), std::string::npos);
}

TEST_F(EmitterTest_57, OperatorDoubleNegative_57) {
  YAML::Emitter emitter;
  emitter << -2.5;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-2.5"), std::string::npos);
}

TEST_F(EmitterTest_57, OperatorDoubleZero_57) {
  YAML::Emitter emitter;
  emitter << 0.0;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_57, OperatorDoubleVerySmall_57) {
  YAML::Emitter emitter;
  emitter.SetDoublePrecision(15);
  emitter << 1e-15;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_57, OperatorDoubleVeryLarge_57) {
  YAML::Emitter emitter;
  emitter << 1e+300;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// =============================================================================
// SetOutputCharset test
// =============================================================================

TEST_F(EmitterTest_57, SetOutputCharset_UTF8_57) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// =============================================================================
// Newline / Literal / Folded tests
// =============================================================================

TEST_F(EmitterTest_57, WriteLiteralString_57) {
  YAML::Emitter emitter;
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("|"), std::string::npos);
}

TEST_F(EmitterTest_57, WriteNewline_57) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "first";
  emitter << YAML::Newline;
  emitter << "second";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}
