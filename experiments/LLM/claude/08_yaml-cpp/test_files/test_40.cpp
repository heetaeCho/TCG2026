#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_40 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// Basic construction and initial state tests

TEST_F(EmitterTest_40, DefaultConstructor_GoodState_40) {
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_40, DefaultConstructor_EmptyOutput_40) {
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_40, DefaultConstructor_CStrNotNull_40) {
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_40, DefaultConstructor_NoError_40) {
  EXPECT_EQ(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_40, StreamConstructor_GoodState_40) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  EXPECT_TRUE(e.good());
}

TEST_F(EmitterTest_40, StreamConstructor_WritesToStream_40) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << "hello";
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// Write string tests

TEST_F(EmitterTest_40, WriteString_SimpleString_40) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteString_EmptyString_40) {
  emitter << std::string("");
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_40, WriteString_StdString_40) {
  std::string s = "world";
  emitter << s;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("world"), std::string::npos);
}

// Write bool tests

TEST_F(EmitterTest_40, WriteBool_True_40) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteBool_False_40) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("false"), std::string::npos);
}

// Write char tests

TEST_F(EmitterTest_40, WriteChar_SingleChar_40) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("A"), std::string::npos);
}

// Write unsigned char via inline operator<<

TEST_F(EmitterTest_40, WriteUnsignedChar_40) {
  unsigned char uc = 'B';
  emitter << uc;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("B"), std::string::npos);
}

// Write integral types

TEST_F(EmitterTest_40, WriteInt_40) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteNegativeInt_40) {
  emitter << -7;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-7"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteLongLong_40) {
  emitter << static_cast<long long>(123456789012345LL);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("123456789012345"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteZero_40) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

// Write floating point

TEST_F(EmitterTest_40, WriteFloat_40) {
  emitter << 3.14f;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteDouble_40) {
  emitter << 2.718281828;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("2.71828"), std::string::npos);
}

// Write Null

TEST_F(EmitterTest_40, WriteNull_40) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// Sequence tests

TEST_F(EmitterTest_40, WriteBlockSequence_40) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteFlowSequence_40) {
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteEmptySequence_40) {
  emitter << YAML::BeginSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Map tests

TEST_F(EmitterTest_40, WriteBlockMap_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "John";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteFlowMap_40) {
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteEmptyMap_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// Nested structures

TEST_F(EmitterTest_40, WriteNestedMapInSequence_40) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "val";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_40, WriteNestedSequenceInMap_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "list";
  emitter << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// Anchor and Alias

TEST_F(EmitterTest_40, WriteAnchor_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "item";
  emitter << YAML::Value << YAML::Anchor("anchor1") << "value1";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&anchor1"), std::string::npos);
}

TEST_F(EmitterTest_40, WriteAlias_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "item1";
  emitter << YAML::Value << YAML::Anchor("anc") << "data";
  emitter << YAML::Key << "item2";
  emitter << YAML::Value << YAML::Alias("anc");
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("*anc"), std::string::npos);
}

// Tag

TEST_F(EmitterTest_40, WriteTag_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "tagged";
  emitter << YAML::Value << YAML::Tag("!mytag") << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// Comment

TEST_F(EmitterTest_40, WriteComment_40) {
  emitter << YAML::Comment("This is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("# This is a comment"), std::string::npos);
}

// Binary

TEST_F(EmitterTest_40, WriteBinary_40) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Literal and other string formats

TEST_F(EmitterTest_40, WriteLiteralString_40) {
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("|"), std::string::npos);
}

// SetBoolFormat

TEST_F(EmitterTest_40, SetBoolFormat_UpperCase_40) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_40, SetBoolFormat_CamelCase_40) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("False"), std::string::npos);
}

TEST_F(EmitterTest_40, SetBoolFormat_LongBool_40) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

// SetIntBase

TEST_F(EmitterTest_40, SetIntBase_Hex_40) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_40, SetIntBase_Oct_40) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

// SetSeqFormat

TEST_F(EmitterTest_40, SetSeqFormat_Flow_40) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_40, SetSeqFormat_Block_40) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-"), std::string::npos);
}

// SetMapFormat

TEST_F(EmitterTest_40, SetMapFormat_Flow_40) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  emitter << YAML::BeginMap << YAML::Key << "k" << YAML::Value << "v" << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_40, SetMapFormat_Block_40) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
  emitter << YAML::BeginMap << YAML::Key << "k" << YAML::Value << "v" << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// SetIndent

TEST_F(EmitterTest_40, SetIndent_Valid_40) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_40, SetIndent_MinBoundary_40) {
  EXPECT_TRUE(emitter.SetIndent(2));
}

// SetFloatPrecision and SetDoublePrecision

TEST_F(EmitterTest_40, SetFloatPrecision_40) {
  EXPECT_TRUE(emitter.SetFloatPrecision(3));
}

TEST_F(EmitterTest_40, SetDoublePrecision_40) {
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// SetPreCommentIndent and SetPostCommentIndent

TEST_F(EmitterTest_40, SetPreCommentIndent_40) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_40, SetPostCommentIndent_40) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// SetOutputCharset

TEST_F(EmitterTest_40, SetOutputCharset_UTF8_40) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// SetStringFormat

TEST_F(EmitterTest_40, SetStringFormat_SingleQuoted_40) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_40, SetStringFormat_DoubleQuoted_40) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// SetNullFormat

TEST_F(EmitterTest_40, SetNullFormat_Tilde_40) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_40, SetNullFormat_UpperNull_40) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("NULL"), std::string::npos);
}

TEST_F(EmitterTest_40, SetNullFormat_CamelNull_40) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("Null"), std::string::npos);
}

TEST_F(EmitterTest_40, SetNullFormat_TildeNull_40) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// size() reflects output

TEST_F(EmitterTest_40, SizeIncreasesAfterWrite_40) {
  std::size_t before = emitter.size();
  emitter << "test";
  EXPECT_GT(emitter.size(), before);
}

// Multiple scalars at top level (YAML doc behavior)

TEST_F(EmitterTest_40, WriteMultipleDocuments_40) {
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

// Complex nested structure

TEST_F(EmitterTest_40, ComplexNestedStructure_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "people";
  emitter << YAML::Value;
  emitter << YAML::BeginSeq;
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
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("Alice"), std::string::npos);
  EXPECT_NE(output.find("Bob"), std::string::npos);
}

// SetLocalValue

TEST_F(EmitterTest_40, SetLocalValue_Flow_40) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Write with char* and size

TEST_F(EmitterTest_40, WriteCharPtrWithSize_40) {
  const char* data = "hello world";
  emitter.Write(data, 5);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

// RestoreGlobalModifiedSettings

TEST_F(EmitterTest_40, RestoreGlobalModifiedSettings_40) {
  emitter.SetBoolFormat(YAML::UpperCase);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  // After restore, should be back to default (lowercase)
  EXPECT_NE(output.find("true"), std::string::npos);
}

// Verify stream output matches c_str output

TEST_F(EmitterTest_40, StreamOutputMatchesCStr_40) {
  std::stringstream ss;
  YAML::Emitter e(ss);
  e << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(e.good());
  EXPECT_EQ(std::string(e.c_str()), ss.str());
}

// Edge: Write special characters in strings

TEST_F(EmitterTest_40, WriteStringWithSpecialChars_40) {
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_40, WriteStringWithNewline_40) {
  emitter << "line1\nline2";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Write LongKey

TEST_F(EmitterTest_40, WriteLongKey_40) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "longkeyname" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("longkeyname"), std::string::npos);
}

// Verify Newline manipulation

TEST_F(EmitterTest_40, WriteNewline_40) {
  emitter << YAML::BeginSeq;
  emitter << "a";
  emitter << YAML::Newline;
  emitter << "b";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Boundary: SetIndent with 1 (may fail since minimum is typically 2)

TEST_F(EmitterTest_40, SetIndent_TooSmall_40) {
  bool result = emitter.SetIndent(1);
  // Implementation may reject indent < 2
  // We just verify it doesn't crash and returns a bool
  (void)result;
}

// Boundary: SetIndent with 0

TEST_F(EmitterTest_40, SetIndent_Zero_40) {
  bool result = emitter.SetIndent(0);
  (void)result;
  // Should not crash
}

// Verify that passing invalid EMITTER_MANIP to wrong setter returns false

TEST_F(EmitterTest_40, SetSeqFormat_InvalidManip_40) {
  // Passing a bool format to seq format setter should return false
  bool result = emitter.SetSeqFormat(YAML::UpperCase);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_40, SetMapFormat_InvalidManip_40) {
  bool result = emitter.SetMapFormat(YAML::UpperCase);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_40, SetBoolFormat_InvalidManip_40) {
  bool result = emitter.SetBoolFormat(YAML::Flow);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_40, SetIntBase_InvalidManip_40) {
  bool result = emitter.SetIntBase(YAML::Flow);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_40, SetStringFormat_InvalidManip_40) {
  bool result = emitter.SetStringFormat(YAML::Flow);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_40, SetNullFormat_InvalidManip_40) {
  bool result = emitter.SetNullFormat(YAML::Flow);
  EXPECT_FALSE(result);
}
