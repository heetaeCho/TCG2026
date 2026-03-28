#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include <sstream>
#include <string>

class EmitterTest_526 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// Test that a freshly constructed Emitter is in a good state
TEST_F(EmitterTest_526, DefaultConstructorIsGood_526) {
  EXPECT_TRUE(emitter.good());
}

// Test that c_str returns non-null for a default emitter
TEST_F(EmitterTest_526, DefaultCStrNotNull_526) {
  EXPECT_NE(nullptr, emitter.c_str());
}

// Test that size is 0 for a default emitter
TEST_F(EmitterTest_526, DefaultSizeIsZero_526) {
  EXPECT_EQ(0u, emitter.size());
}

// Test that GetLastError returns empty string when no error
TEST_F(EmitterTest_526, DefaultNoError_526) {
  EXPECT_TRUE(emitter.GetLastError().empty());
}

// Test SetPostCommentIndent returns true for a valid value
TEST_F(EmitterTest_526, SetPostCommentIndentReturnsTrue_526) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(2));
}

// Test SetPostCommentIndent with value 0
TEST_F(EmitterTest_526, SetPostCommentIndentZero_526) {
  bool result = emitter.SetPostCommentIndent(0);
  // The emitter should still be good regardless of whether 0 is accepted
  // We just verify it doesn't crash and returns a bool
  (void)result;
  EXPECT_TRUE(emitter.good());
}

// Test SetPostCommentIndent with value 1
TEST_F(EmitterTest_526, SetPostCommentIndentOne_526) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// Test SetPostCommentIndent with a large value
TEST_F(EmitterTest_526, SetPostCommentIndentLargeValue_526) {
  bool result = emitter.SetPostCommentIndent(100);
  (void)result;
  EXPECT_TRUE(emitter.good());
}

// Test SetPreCommentIndent returns true
TEST_F(EmitterTest_526, SetPreCommentIndentReturnsTrue_526) {
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

// Test SetIndent returns true for valid indent
TEST_F(EmitterTest_526, SetIndentReturnsTrue_526) {
  EXPECT_TRUE(emitter.SetIndent(4));
}

// Test SetIndent with minimum valid indent (2)
TEST_F(EmitterTest_526, SetIndentMinimum_526) {
  EXPECT_TRUE(emitter.SetIndent(2));
}

// Test SetIndent with 1 (may be rejected as too small)
TEST_F(EmitterTest_526, SetIndentTooSmall_526) {
  bool result = emitter.SetIndent(1);
  // Some implementations reject indent < 2
  (void)result;
  // Emitter should still be in good state
  EXPECT_TRUE(emitter.good());
}

// Test SetOutputCharset
TEST_F(EmitterTest_526, SetOutputCharsetUtf8_526) {
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

// Test SetStringFormat
TEST_F(EmitterTest_526, SetStringFormatSingleQuoted_526) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

// Test SetStringFormat with DoubleQuoted
TEST_F(EmitterTest_526, SetStringFormatDoubleQuoted_526) {
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

// Test SetBoolFormat
TEST_F(EmitterTest_526, SetBoolFormatTrueFalse_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

// Test SetBoolFormat with YesNoBool
TEST_F(EmitterTest_526, SetBoolFormatYesNo_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

// Test SetBoolFormat with OnOffBool
TEST_F(EmitterTest_526, SetBoolFormatOnOff_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

// Test SetNullFormat
TEST_F(EmitterTest_526, SetNullFormatLowerNull_526) {
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

// Test SetIntBase
TEST_F(EmitterTest_526, SetIntBaseHex_526) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

// Test SetIntBase with Oct
TEST_F(EmitterTest_526, SetIntBaseOct_526) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

// Test SetIntBase with Dec
TEST_F(EmitterTest_526, SetIntBaseDec_526) {
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

// Test SetSeqFormat with Flow
TEST_F(EmitterTest_526, SetSeqFormatFlow_526) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

// Test SetSeqFormat with Block
TEST_F(EmitterTest_526, SetSeqFormatBlock_526) {
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

// Test SetMapFormat with Flow
TEST_F(EmitterTest_526, SetMapFormatFlow_526) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// Test SetMapFormat with Block
TEST_F(EmitterTest_526, SetMapFormatBlock_526) {
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

// Test SetFloatPrecision
TEST_F(EmitterTest_526, SetFloatPrecision_526) {
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

// Test SetDoublePrecision
TEST_F(EmitterTest_526, SetDoublePrecision_526) {
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// Test writing a simple string
TEST_F(EmitterTest_526, WriteString_526) {
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test writing a boolean true
TEST_F(EmitterTest_526, WriteBoolTrue_526) {
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test writing a boolean false
TEST_F(EmitterTest_526, WriteBoolFalse_526) {
  emitter << false;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test writing an integer
TEST_F(EmitterTest_526, WriteInteger_526) {
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

// Test writing a float
TEST_F(EmitterTest_526, WriteFloat_526) {
  emitter << 3.14f;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test writing a double
TEST_F(EmitterTest_526, WriteDouble_526) {
  emitter << 3.14159;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test writing Null
TEST_F(EmitterTest_526, WriteNull_526) {
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test writing a sequence
TEST_F(EmitterTest_526, WriteSequence_526) {
  emitter << YAML::BeginSeq;
  emitter << "item1";
  emitter << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("item2"), std::string::npos);
}

// Test writing a map
TEST_F(EmitterTest_526, WriteMap_526) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "name";
  emitter << YAML::Value << "test";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("name"), std::string::npos);
  EXPECT_NE(output.find("test"), std::string::npos);
}

// Test writing a comment
TEST_F(EmitterTest_526, WriteComment_526) {
  emitter << YAML::Comment("this is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("this is a comment"), std::string::npos);
}

// Test SetPostCommentIndent affects comment formatting
TEST_F(EmitterTest_526, SetPostCommentIndentAffectsOutput_526) {
  emitter.SetPostCommentIndent(3);
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key1";
  emitter << YAML::Value << YAML::Comment("comment") << "val1";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// Test writing an anchor
TEST_F(EmitterTest_526, WriteAnchor_526) {
  emitter << YAML::Anchor("anchor1");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("anchor1"), std::string::npos);
}

// Test writing an alias
TEST_F(EmitterTest_526, WriteAlias_526) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("anc") << "value";
  emitter << YAML::Alias("anc");
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("anc"), std::string::npos);
}

// Test writing a tag
TEST_F(EmitterTest_526, WriteTag_526) {
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
}

// Test writing to an ostream
TEST_F(EmitterTest_526, WriteToOstream_526) {
  std::ostringstream os;
  YAML::Emitter out(os);
  out << "hello";
  EXPECT_TRUE(out.good());
  EXPECT_NE(os.str().find("hello"), std::string::npos);
}

// Test writing a char
TEST_F(EmitterTest_526, WriteChar_526) {
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("A"), std::string::npos);
}

// Test nested sequences
TEST_F(EmitterTest_526, NestedSequences_526) {
  emitter << YAML::BeginSeq;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2;
  emitter << YAML::EndSeq;
  emitter << YAML::BeginSeq;
  emitter << 3 << 4;
  emitter << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Test nested maps
TEST_F(EmitterTest_526, NestedMaps_526) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "outer";
  emitter << YAML::Value;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "inner" << YAML::Value << "value";
  emitter << YAML::EndMap;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}

// Test flow sequence format
TEST_F(EmitterTest_526, FlowSequence_526) {
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

// Test flow map format
TEST_F(EmitterTest_526, FlowMap_526) {
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
}

// Test RestoreGlobalModifiedSettings
TEST_F(EmitterTest_526, RestoreGlobalModifiedSettings_526) {
  emitter.SetStringFormat(YAML::SingleQuoted);
  emitter.RestoreGlobalModifiedSettings();
  // Emitter should still be good after restoring
  EXPECT_TRUE(emitter.good());
}

// Test SetLocalValue
TEST_F(EmitterTest_526, SetLocalValue_526) {
  emitter << YAML::BeginSeq;
  emitter << YAML::Flow << YAML::BeginSeq << 1 << 2 << YAML::EndSeq;
  emitter << YAML::BeginSeq << 3 << 4 << YAML::EndSeq;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Test SetLocalIndent
TEST_F(EmitterTest_526, SetLocalIndent_526) {
  emitter << YAML::Indent(4);
  emitter << YAML::BeginSeq << "a" << "b" << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Test SetLocalPrecision for floats
TEST_F(EmitterTest_526, SetLocalPrecisionFloat_526) {
  emitter << YAML::FloatPrecision(3);
  emitter << 3.14159f;
  EXPECT_TRUE(emitter.good());
}

// Test SetLocalPrecision for doubles
TEST_F(EmitterTest_526, SetLocalPrecisionDouble_526) {
  emitter << YAML::DoublePrecision(10);
  emitter << 3.141592653589793;
  EXPECT_TRUE(emitter.good());
}

// Test writing binary data
TEST_F(EmitterTest_526, WriteBinary_526) {
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  emitter << YAML::Binary(data, sizeof(data));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test writing an empty string
TEST_F(EmitterTest_526, WriteEmptyString_526) {
  emitter << "";
  EXPECT_TRUE(emitter.good());
}

// Test that setting an invalid format for SetBoolFormat returns false
TEST_F(EmitterTest_526, SetBoolFormatInvalidValue_526) {
  // Flow is not a valid bool format
  bool result = emitter.SetBoolFormat(YAML::Flow);
  EXPECT_FALSE(result);
}

// Test that setting an invalid format for SetSeqFormat returns false
TEST_F(EmitterTest_526, SetSeqFormatInvalidValue_526) {
  // TrueFalseBool is not a valid seq format
  bool result = emitter.SetSeqFormat(YAML::TrueFalseBool);
  EXPECT_FALSE(result);
}

// Test that setting an invalid format for SetMapFormat returns false
TEST_F(EmitterTest_526, SetMapFormatInvalidValue_526) {
  bool result = emitter.SetMapFormat(YAML::TrueFalseBool);
  EXPECT_FALSE(result);
}

// Test that SetOutputCharset with invalid value returns false
TEST_F(EmitterTest_526, SetOutputCharsetInvalidValue_526) {
  bool result = emitter.SetOutputCharset(YAML::Flow);
  EXPECT_FALSE(result);
}

// Test that SetStringFormat with invalid value returns false
TEST_F(EmitterTest_526, SetStringFormatInvalidValue_526) {
  bool result = emitter.SetStringFormat(YAML::TrueFalseBool);
  EXPECT_FALSE(result);
}

// Test that SetIntBase with invalid value returns false
TEST_F(EmitterTest_526, SetIntBaseInvalidValue_526) {
  bool result = emitter.SetIntBase(YAML::Flow);
  EXPECT_FALSE(result);
}

// Test multiple SetPostCommentIndent calls
TEST_F(EmitterTest_526, MultipleSetPostCommentIndent_526) {
  EXPECT_TRUE(emitter.SetPostCommentIndent(2));
  EXPECT_TRUE(emitter.SetPostCommentIndent(4));
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
  EXPECT_TRUE(emitter.good());
}

// Test writing a long key in a map
TEST_F(EmitterTest_526, LongKey_526) {
  emitter << YAML::BeginMap;
  emitter << YAML::LongKey;
  emitter << YAML::Key << "long_key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("long_key"), std::string::npos);
}

// Test emitter with document markers
TEST_F(EmitterTest_526, BeginEndDoc_526) {
  emitter << YAML::BeginDoc;
  emitter << "value";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("---"), std::string::npos);
}

// Test multiple documents
TEST_F(EmitterTest_526, MultipleDocuments_526) {
  emitter << YAML::BeginDoc;
  emitter << "doc1";
  emitter << YAML::EndDoc;
  emitter << YAML::BeginDoc;
  emitter << "doc2";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
}

// Test writing a negative integer
TEST_F(EmitterTest_526, WriteNegativeInteger_526) {
  emitter << -42;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-42"), std::string::npos);
}

// Test writing zero
TEST_F(EmitterTest_526, WriteZero_526) {
  emitter << 0;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

// Test Emitter copy constructor is deleted (compile-time check conceptual)
// We can't really test deleted constructors at runtime, so we test assignment doesn't compile
// by verifying that a new emitter is independent
TEST_F(EmitterTest_526, IndependentEmitters_526) {
  YAML::Emitter e1;
  YAML::Emitter e2;
  e1 << "hello";
  e2 << "world";
  std::string out1 = e1.c_str();
  std::string out2 = e2.c_str();
  EXPECT_NE(out1, out2);
}

// Test SetPostCommentIndent and then emit a comment to verify it works in context
TEST_F(EmitterTest_526, SetPostCommentIndentWithComment_526) {
  emitter.SetPostCommentIndent(1);
  emitter << YAML::BeginSeq;
  emitter << YAML::Comment("test comment");
  emitter << "item";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("test comment"), std::string::npos);
  EXPECT_NE(output.find("item"), std::string::npos);
}

// Test setting bool format to UpperCase
TEST_F(EmitterTest_526, SetBoolFormatUpperCase_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

// Test setting bool format to CamelCase
TEST_F(EmitterTest_526, SetBoolFormatCamelCase_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

// Test setting bool format to LongBool
TEST_F(EmitterTest_526, SetBoolFormatLongBool_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

// Test setting bool format to ShortBool
TEST_F(EmitterTest_526, SetBoolFormatShortBool_526) {
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
}

// Test hex int output
TEST_F(EmitterTest_526, HexIntOutput_526) {
  emitter.SetIntBase(YAML::Hex);
  emitter << 255;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Should contain hex representation
  EXPECT_NE(output.find("0x"), std::string::npos);
}

// Test oct int output
TEST_F(EmitterTest_526, OctIntOutput_526) {
  emitter.SetIntBase(YAML::Oct);
  emitter << 8;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}
