#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_58 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction and Initial State ====================

TEST_F(EmitterTest_58, DefaultConstructor_GoodState_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_58, DefaultConstructor_EmptyOutput_58) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, DefaultConstructor_CStrNotNull_58) {
  YAML::Emitter emitter;
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_58, StreamConstructor_GoodState_58) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_58, DefaultConstructor_NoError_58) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.GetLastError(), "");
}

// ==================== Writing Scalars ====================

TEST_F(EmitterTest_58, WriteString_58) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_58, WriteCString_58) {
  YAML::Emitter emitter;
  emitter << "test";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, WriteInt_58) {
  YAML::Emitter emitter;
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_58, WriteBoolTrue_58) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, WriteBoolFalse_58) {
  YAML::Emitter emitter;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, WriteDouble_58) {
  YAML::Emitter emitter;
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, WriteFloat_58) {
  YAML::Emitter emitter;
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, WriteChar_58) {
  YAML::Emitter emitter;
  emitter << 'a';
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, WriteNull_58) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Sequences ====================

TEST_F(EmitterTest_58, BlockSequence_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << "item3";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
  EXPECT_NE(output.find("item3"), std::string::npos);
}

TEST_F(EmitterTest_58, FlowSequence_58) {
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

TEST_F(EmitterTest_58, EmptySequence_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Maps ====================

TEST_F(EmitterTest_58, BlockMap_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "John";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("John"), std::string::npos);
}

TEST_F(EmitterTest_58, FlowMap_58) {
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

TEST_F(EmitterTest_58, EmptyMap_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_58, NestedMapInSequence_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_58, NestedSequenceInMap_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items";
  emitter << YAML::Value;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Anchors and Aliases ====================

TEST_F(EmitterTest_58, Anchor_58) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("anchor1");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("anchor1"), std::string::npos);
}

TEST_F(EmitterTest_58, Alias_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("ref") << "value";
  emitter << YAML::Alias("ref");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("*ref"), std::string::npos);
}

// ==================== Tags ====================

TEST_F(EmitterTest_58, Tag_58) {
  YAML::Emitter emitter;
  emitter << YAML::LocalTag("mytype") << "value";
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_58, VerbatimTag_58) {
  YAML::Emitter emitter;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "value";
  EXPECT_TRUE(emitter.good());
}

// ==================== Comments ====================

TEST_F(EmitterTest_58, Comment_58) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("This is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("This is a comment"), std::string::npos);
}

TEST_F(EmitterTest_58, CommentInMap_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Comment("map comment");
  emitter << YAML::Key << "key" << YAML::Value << "val";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// ==================== Global Settings ====================

TEST_F(EmitterTest_58, SetStringFormat_SingleQuoted_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_58, SetStringFormat_DoubleQuoted_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_58, SetBoolFormat_TrueFalseCase_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_58, SetBoolFormat_YesNoBool_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_58, SetBoolFormat_UpperCase_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_58, SetBoolFormat_CamelCase_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("True"), std::string::npos);
}

TEST_F(EmitterTest_58, SetIntBase_Hex_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_58, SetIntBase_Oct_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_58, SetSeqFormat_Flow_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_58, SetMapFormat_Flow_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_58, SetIndent_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_58, SetIndent_MinBoundary_58) {
  YAML::Emitter emitter;
  // Indent of 2 is minimum valid
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_58, SetIndent_TooSmall_58) {
  YAML::Emitter emitter;
  // Indent of 1 should fail (minimum is 2)
  EXPECT_FALSE(emitter.SetIndent(1));
}

TEST_F(EmitterTest_58, SetPreCommentIndent_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_58, SetPostCommentIndent_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_58, SetFloatPrecision_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(4));
}

TEST_F(EmitterTest_58, SetDoublePrecision_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(10));
}

// ==================== Invalid Global Settings ====================

TEST_F(EmitterTest_58, SetStringFormat_InvalidManip_58) {
  YAML::Emitter emitter;
  // Passing a non-string-format manip should return false
  EXPECT_FALSE(emitter.SetStringFormat(YAML::Flow));
}

TEST_F(EmitterTest_58, SetBoolFormat_InvalidManip_58) {
  YAML::Emitter emitter;
  EXPECT_FALSE(emitter.SetBoolFormat(YAML::Flow));
}

TEST_F(EmitterTest_58, SetIntBase_InvalidManip_58) {
  YAML::Emitter emitter;
  EXPECT_FALSE(emitter.SetIntBase(YAML::Flow));
}

TEST_F(EmitterTest_58, SetSeqFormat_InvalidManip_58) {
  YAML::Emitter emitter;
  EXPECT_FALSE(emitter.SetSeqFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_58, SetMapFormat_InvalidManip_58) {
  YAML::Emitter emitter;
  EXPECT_FALSE(emitter.SetMapFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_58, SetNullFormat_Valid_58) {
  YAML::Emitter emitter;
  // Tilde is a valid null format
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_58, SetNullFormat_Invalid_58) {
  YAML::Emitter emitter;
  EXPECT_FALSE(emitter.SetNullFormat(YAML::Flow));
}

TEST_F(EmitterTest_58, SetOutputCharset_UTF8_58) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// ==================== Output to Stream ====================

TEST_F(EmitterTest_58, OutputToStream_58) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  // The output should be written to the stream
  std::string output = ss.str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_58, OutputToStreamMap_58) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "val";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find("key"), std::string::npos);
}

// ==================== Multiple Documents ====================

TEST_F(EmitterTest_58, MultipleDocuments_58) {
  YAML::Emitter emitter;
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

// ==================== Literal and Folded Strings ====================

TEST_F(EmitterTest_58, LiteralString_58) {
  YAML::Emitter emitter;
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("|"), std::string::npos);
}

// ==================== Binary Data ====================

TEST_F(EmitterTest_58, BinaryData_58) {
  YAML::Emitter emitter;
  std::vector<unsigned char> data = {0x01, 0x02, 0x03, 0xFF};
  emitter << YAML::Binary(data.data(), data.size());
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, EmptyBinaryData_58) {
  YAML::Emitter emitter;
  emitter << YAML::Binary(nullptr, 0);
  EXPECT_TRUE(emitter.good());
}

// ==================== Newline ====================

TEST_F(EmitterTest_58, Newline_58) {
  YAML::Emitter emitter;
  emitter << "first";
  emitter << YAML::Newline;
  emitter << "second";
  EXPECT_TRUE(emitter.good());
}

// ==================== Long Key ====================

TEST_F(EmitterTest_58, LongKey_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "long_key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== Size Method ====================

TEST_F(EmitterTest_58, SizeIncreasesWithContent_58) {
  YAML::Emitter emitter;
  std::size_t initialSize = emitter.size();
  emitter << "hello";
  EXPECT_GT(emitter.size(), initialSize);
}

// ==================== Complex Nested Structures ====================

TEST_F(EmitterTest_58, ComplexNestedStructure_58) {
  YAML::Emitter emitter;
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

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_58, RestoreGlobalModifiedSettings_58) {
  YAML::Emitter emitter;
  emitter.SetStringFormat(YAML::DoubleQuoted);
  emitter.RestoreGlobalModifiedSettings();
  // After restore, should still be good
  emitter << "test";
  EXPECT_TRUE(emitter.good());
}

// ==================== Local Value (EMITTER_MANIP via operator<<) ====================

TEST_F(EmitterTest_58, LocalManipFlow_58) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

// ==================== Local Indent ====================

TEST_F(EmitterTest_58, LocalIndent_58) {
  YAML::Emitter emitter;
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq;
  emitter << "a" << "b";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Negative/NaN values ====================

TEST_F(EmitterTest_58, NegativeInt_58) {
  YAML::Emitter emitter;
  emitter << -42;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-42"), std::string::npos);
}

TEST_F(EmitterTest_58, ZeroInt_58) {
  YAML::Emitter emitter;
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_58, LargeInt_58) {
  YAML::Emitter emitter;
  emitter << 2147483647;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("2147483647"), std::string::npos);
}

// ==================== Empty String ====================

TEST_F(EmitterTest_58, EmptyString_58) {
  YAML::Emitter emitter;
  emitter << "";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== Strings requiring quoting ====================

TEST_F(EmitterTest_58, StringWithSpecialChars_58) {
  YAML::Emitter emitter;
  emitter << "hello: world";
  EXPECT_TRUE(emitter.good());
  // Should be quoted because it contains a colon followed by space
  std::string output(emitter.c_str());
  EXPECT_GT(emitter.size(), 0u);
}

TEST_F(EmitterTest_58, StringWithNewline_58) {
  YAML::Emitter emitter;
  emitter << "line1\nline2";
  EXPECT_TRUE(emitter.good());
}

// ==================== Multiple scalars at top level ====================

TEST_F(EmitterTest_58, MultipleScalarsInSequence_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "a" << "b" << "c";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
  EXPECT_NE(output.find("c"), std::string::npos);
}

// ==================== Using SetLocalPrecision ====================

TEST_F(EmitterTest_58, SetLocalPrecision_58) {
  YAML::Emitter emitter;
  emitter << YAML::FloatPrecision(2) << 3.14159f;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_58, SetLocalDoublePrecision_58) {
  YAML::Emitter emitter;
  emitter << YAML::DoublePrecision(3) << 3.14159265358979;
  EXPECT_TRUE(emitter.good());
}

// ==================== Map with multiple entries ====================

TEST_F(EmitterTest_58, MapMultipleEntries_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key1" << YAML::Value << "val1";
  emitter << YAML::Key << "key2" << YAML::Value << "val2";
  emitter << YAML::Key << "key3" << YAML::Value << "val3";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("key2"), std::string::npos);
  EXPECT_NE(output.find("key3"), std::string::npos);
}

// ==================== Deeply nested sequences ====================

TEST_F(EmitterTest_58, DeeplyNestedSequences_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginSeq;
  emitter << 1;
  emitter << YAML::EndSeq;
  emitter << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== NullFormat Tilde ====================

TEST_F(EmitterTest_58, NullFormatTilde_58) {
  YAML::Emitter emitter;
  emitter.SetNullFormat(YAML::TildeNull);
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Chaining operator<< ====================

TEST_F(EmitterTest_58, ChainingOperator_58) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// ==================== Unsigned int ====================

TEST_F(EmitterTest_58, WriteUnsignedInt_58) {
  YAML::Emitter emitter;
  unsigned int val = 42u;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== Long long ====================

TEST_F(EmitterTest_58, WriteLongLong_58) {
  YAML::Emitter emitter;
  long long val = 1234567890123LL;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("1234567890123"), std::string::npos);
}
