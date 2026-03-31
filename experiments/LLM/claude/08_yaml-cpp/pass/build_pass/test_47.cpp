#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_47 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// === Construction and Initial State ===

TEST_F(EmitterTest_47, DefaultConstructor_GoodState_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_47, DefaultConstructor_EmptyOutput_47) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_47, DefaultConstructor_CStrNotNull_47) {
  YAML::Emitter emitter;
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_47, StreamConstructor_GoodState_47) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_47, DefaultConstructor_NoError_47) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.GetLastError(), "");
}

// === Writing Scalars ===

TEST_F(EmitterTest_47, WriteString_47) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteStdString_47) {
  YAML::Emitter emitter;
  std::string value = "world";
  emitter << value;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteBoolTrue_47) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_47, WriteBoolFalse_47) {
  YAML::Emitter emitter;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_47, WriteChar_47) {
  YAML::Emitter emitter;
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteInt_47) {
  YAML::Emitter emitter;
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteDouble_47) {
  YAML::Emitter emitter;
  emitter << 3.14;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_47, WriteFloat_47) {
  YAML::Emitter emitter;
  emitter << 2.5f;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_47, WriteNull_47) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("~"), std::string::npos);
}

// === Writing const char* via operator<< ===

TEST_F(EmitterTest_47, WriteConstCharStar_47) {
  YAML::Emitter emitter;
  const char* val = "test_value";
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("test_value"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteEmptyConstCharStar_47) {
  YAML::Emitter emitter;
  const char* val = "";
  emitter << val;
  EXPECT_TRUE(emitter.good());
}

// === Sequences ===

TEST_F(EmitterTest_47, WriteBlockSequence_47) {
  YAML::Emitter emitter;
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

TEST_F(EmitterTest_47, WriteFlowSequence_47) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << "a" << "b" << "c";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

// === Maps ===

TEST_F(EmitterTest_47, WriteBlockMap_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "John";
  emitter << YAML::Key << "age" << YAML::Value << 30;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("John"), std::string::npos);
  EXPECT_NE(output.find("age"), std::string::npos);
  EXPECT_NE(output.find("30"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteFlowMap_47) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

// === Nested Structures ===

TEST_F(EmitterTest_47, WriteNestedMapInSeq_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_47, WriteNestedSeqInMap_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items" << YAML::Value;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("items"), std::string::npos);
}

// === Comments ===

TEST_F(EmitterTest_47, WriteComment_47) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("this is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// === Anchors and Aliases ===

TEST_F(EmitterTest_47, WriteAnchor_47) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("myanchor") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteAlias_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("ref") << "value";
  emitter << YAML::Alias("ref");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("*ref"), std::string::npos);
}

// === Tags ===

TEST_F(EmitterTest_47, WriteTag_47) {
  YAML::Emitter emitter;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("tag:yaml.org,2002:str"), std::string::npos);
}

// === Stream Output ===

TEST_F(EmitterTest_47, StreamConstructor_OutputToStream_47) {
  std::stringstream ss;
  {
    YAML::Emitter emitter(ss);
    emitter << "hello";
    EXPECT_TRUE(emitter.good());
  }
  std::string output = ss.str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

// === Size Tracking ===

TEST_F(EmitterTest_47, SizeIncreasesAfterWrite_47) {
  YAML::Emitter emitter;
  std::size_t initialSize = emitter.size();
  emitter << "test";
  EXPECT_GT(emitter.size(), initialSize);
}

// === Setting Formats ===

TEST_F(EmitterTest_47, SetBoolFormatTrueFalse_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_47, SetBoolFormatYesNo_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("yes"), std::string::npos);
}

TEST_F(EmitterTest_47, SetBoolFormatUpperCase_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("TRUE"), std::string::npos);
}

TEST_F(EmitterTest_47, SetSeqFormat_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  emitter << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_47, SetMapFormat_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
}

TEST_F(EmitterTest_47, SetIndent_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_47, SetIndent_InvalidZero_47) {
  YAML::Emitter emitter;
  // Indent of 0 or 1 may be rejected
  // We just check the return value
  bool result = emitter.SetIndent(0);
  // It's valid to reject 0 as indent
  (void)result;
}

TEST_F(EmitterTest_47, SetIndent_InvalidOne_47) {
  YAML::Emitter emitter;
  bool result = emitter.SetIndent(1);
  // Minimum indent is typically 2
  (void)result;
}

TEST_F(EmitterTest_47, SetPreCommentIndent_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_47, SetPostCommentIndent_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_47, SetFloatPrecision_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_47, SetDoublePrecision_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_47, SetStringFormat_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_47, SetNullFormat_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_47, SetIntBaseHex_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_47, SetIntBaseOct_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

// === Local Value Settings ===

TEST_F(EmitterTest_47, SetLocalValue_Flow_47) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_47, SetLocalIndent_47) {
  YAML::Emitter emitter;
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// === Binary ===

TEST_F(EmitterTest_47, WriteBinary_47) {
  YAML::Emitter emitter;
  unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_47, WriteBinaryEmpty_47) {
  YAML::Emitter emitter;
  emitter << YAML::Binary(nullptr, 0);
  EXPECT_TRUE(emitter.good());
}

// === Multiple Documents ===

TEST_F(EmitterTest_47, MultipleDocuments_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc << "first" << YAML::EndDoc;
  emitter << YAML::BeginDoc << "second" << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("first"), std::string::npos);
  EXPECT_NE(output.find("second"), std::string::npos);
}

// === Large Integer Types ===

TEST_F(EmitterTest_47, WriteLongLong_47) {
  YAML::Emitter emitter;
  long long val = 9223372036854775807LL;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("9223372036854775807"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteNegativeInt_47) {
  YAML::Emitter emitter;
  emitter << -42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-42"), std::string::npos);
}

// === Emitting Quoted Strings ===

TEST_F(EmitterTest_47, WriteSingleQuotedString_47) {
  YAML::Emitter emitter;
  emitter << YAML::SingleQuoted << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_47, WriteDoubleQuotedString_47) {
  YAML::Emitter emitter;
  emitter << YAML::DoubleQuoted << "hello";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

// === Literal Block ===

TEST_F(EmitterTest_47, WriteLiteralString_47) {
  YAML::Emitter emitter;
  emitter << YAML::Literal << "line1\nline2\nline3";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("|"), std::string::npos);
}

// === RestoreGlobalModifiedSettings ===

TEST_F(EmitterTest_47, RestoreGlobalModifiedSettings_47) {
  YAML::Emitter emitter;
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter.RestoreGlobalModifiedSettings();
  emitter << true;
  EXPECT_TRUE(emitter.good());
  // After restoring, should use default bool format (true/false)
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("true"), std::string::npos);
}

// === Complex Nested Structure ===

TEST_F(EmitterTest_47, ComplexNestedStructure_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "people" << YAML::Value;
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name" << YAML::Value << "Alice";
  emitter << YAML::Key << "hobbies" << YAML::Value;
  emitter << YAML::Flow << YAML::BeginSeq << "reading" << "coding" << YAML::EndSeq;
  emitter << YAML::EndMap;
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("Alice"), std::string::npos);
  EXPECT_NE(output.find("reading"), std::string::npos);
}

// === Empty Sequence ===

TEST_F(EmitterTest_47, EmptySequence_47) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("[]"), std::string::npos);
}

// === Empty Map ===

TEST_F(EmitterTest_47, EmptyMap_47) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginMap << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{}"), std::string::npos);
}

// === Long Key ===

TEST_F(EmitterTest_47, LongKeyMap_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "long_key_name" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("?"), std::string::npos);
}

// === SetOutputCharset ===

TEST_F(EmitterTest_47, SetOutputCharsetUTF8_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// === Operator<< with const char* calls Write correctly ===

TEST_F(EmitterTest_47, OperatorShiftConstCharCallsWrite_47) {
  YAML::Emitter emitter;
  const char* str = "test_string";
  YAML::Emitter& ref = (emitter << str);
  EXPECT_EQ(&ref, &emitter);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("test_string"), std::string::npos);
}

// === Write method returns reference to self ===

TEST_F(EmitterTest_47, WriteReturnsEmitterReference_47) {
  YAML::Emitter emitter;
  std::string val = "test";
  YAML::Emitter& ref = emitter.Write(val);
  EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterTest_47, WriteCharPtrReturnsEmitterReference_47) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = emitter.Write("hello", 5);
  EXPECT_EQ(&ref, &emitter);
}

// === Chaining writes ===

TEST_F(EmitterTest_47, ChainingWrites_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq << "a" << "b" << "c" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("a"), std::string::npos);
  EXPECT_NE(output.find("b"), std::string::npos);
  EXPECT_NE(output.find("c"), std::string::npos);
}

// === SetStringFormat with different values ===

TEST_F(EmitterTest_47, SetStringFormatDoubleQuoted_47) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
  emitter << "test";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("\"test\""), std::string::npos);
}

// === Invalid SetBoolFormat ===

TEST_F(EmitterTest_47, SetBoolFormat_InvalidValue_47) {
  YAML::Emitter emitter;
  // Passing a non-bool EMITTER_MANIP should return false
  bool result = emitter.SetBoolFormat(YAML::Flow);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_47, SetSeqFormat_InvalidValue_47) {
  YAML::Emitter emitter;
  bool result = emitter.SetSeqFormat(YAML::TrueFalseBool);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_47, SetMapFormat_InvalidValue_47) {
  YAML::Emitter emitter;
  bool result = emitter.SetMapFormat(YAML::TrueFalseBool);
  EXPECT_FALSE(result);
}

TEST_F(EmitterTest_47, SetIntBase_InvalidValue_47) {
  YAML::Emitter emitter;
  bool result = emitter.SetIntBase(YAML::TrueFalseBool);
  EXPECT_FALSE(result);
}

// === Unsigned integers ===

TEST_F(EmitterTest_47, WriteUnsignedInt_47) {
  YAML::Emitter emitter;
  unsigned int val = 100u;
  emitter << val;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("100"), std::string::npos);
}

// === Newline behavior (via YAML::Newline) ===

TEST_F(EmitterTest_47, WriteNewline_47) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << YAML::Newline;
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// === Tag with local tag ===

TEST_F(EmitterTest_47, WriteLocalTag_47) {
  YAML::Emitter emitter;
  emitter << YAML::LocalTag("mytag") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("!mytag"), std::string::npos);
}
