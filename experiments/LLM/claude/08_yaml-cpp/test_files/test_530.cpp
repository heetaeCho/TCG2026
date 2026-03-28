#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_530 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== Construction & Initial State ====================

TEST_F(EmitterTest_530, DefaultConstructor_IsGood_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_530, DefaultConstructor_EmptyOutput_530) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_530, DefaultConstructor_CStrNotNull_530) {
  YAML::Emitter emitter;
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_530, StreamConstructor_IsGood_530) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_530, DefaultConstructor_NoError_530) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.GetLastError(), "");
}

// ==================== SetLocalValue with BeginDoc/EndDoc ====================

TEST_F(EmitterTest_530, SetLocalValue_BeginDoc_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginDoc);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("---"), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_BeginDocEndDoc_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginDoc);
  emitter.SetLocalValue(YAML::EndDoc);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue with BeginSeq/EndSeq ====================

TEST_F(EmitterTest_530, SetLocalValue_BeginSeqEndSeq_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.Write(std::string("item1"));
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("item1"), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_EmptySequence_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue with BeginMap/EndMap ====================

TEST_F(EmitterTest_530, SetLocalValue_BeginMapEndMap_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::Key);
  emitter.Write(std::string("key1"));
  emitter.SetLocalValue(YAML::Value);
  emitter.Write(std::string("val1"));
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("key1"), std::string::npos);
  EXPECT_NE(output.find("val1"), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_EmptyMap_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue with Key/Value ====================

TEST_F(EmitterTest_530, SetLocalValue_KeyValue_ReturnsSelf_530) {
  YAML::Emitter emitter;
  YAML::Emitter& ref1 = emitter.SetLocalValue(YAML::Key);
  EXPECT_EQ(&ref1, &emitter);
  YAML::Emitter& ref2 = emitter.SetLocalValue(YAML::Value);
  EXPECT_EQ(&ref2, &emitter);
}

// ==================== SetLocalValue with Newline ====================

TEST_F(EmitterTest_530, SetLocalValue_Newline_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.Write(std::string("item"));
  emitter.SetLocalValue(YAML::Newline);
  emitter.Write(std::string("item2"));
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue with formatting manips ====================

TEST_F(EmitterTest_530, SetLocalValue_Flow_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::Flow);
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.Write(std::string("a"));
  emitter.Write(std::string("b"));
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("["), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_Block_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::Block);
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.Write(std::string("a"));
  emitter.Write(std::string("b"));
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("-"), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_DoubleQuoted_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::DoubleQuoted);
  emitter.Write(std::string("hello"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("\"hello\""), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_SingleQuoted_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::SingleQuoted);
  emitter.Write(std::string("hello"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("'hello'"), std::string::npos);
}

TEST_F(EmitterTest_530, SetLocalValue_LongKey_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::LongKey);
  emitter.SetLocalValue(YAML::Key);
  emitter.Write(std::string("mykey"));
  emitter.SetLocalValue(YAML::Value);
  emitter.Write(std::string("myval"));
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("?"), std::string::npos);
}

// ==================== SetLocalValue returns reference ====================

TEST_F(EmitterTest_530, SetLocalValue_ReturnsSelfReference_530) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = emitter.SetLocalValue(YAML::BeginDoc);
  EXPECT_EQ(&ref, &emitter);
}

TEST_F(EmitterTest_530, SetLocalValue_ChainingCalls_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginMap)
      .SetLocalValue(YAML::Key)
      .Write(std::string("k"))
      .SetLocalValue(YAML::Value)
      .Write(std::string("v"))
      .SetLocalValue(YAML::EndMap);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalValue with TagByKind ====================

TEST_F(EmitterTest_530, SetLocalValue_TagByKind_InSequence_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.SetLocalValue(YAML::TagByKind);
  emitter.Write(std::string("tagged"));
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
}

// ==================== Write operations ====================

TEST_F(EmitterTest_530, Write_String_530) {
  YAML::Emitter emitter;
  emitter.Write(std::string("hello world"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("hello world"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_CString_530) {
  YAML::Emitter emitter;
  const char* str = "test";
  emitter.Write(str, 4);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("test"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_Bool_True_530) {
  YAML::Emitter emitter;
  emitter.Write(true);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("true"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_Bool_False_530) {
  YAML::Emitter emitter;
  emitter.Write(false);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("false"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_Null_530) {
  YAML::Emitter emitter;
  emitter.Write(YAML::_Null());
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_Char_530) {
  YAML::Emitter emitter;
  emitter.Write('A');
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("A"), std::string::npos);
}

// ==================== Write with Anchor and Alias ====================

TEST_F(EmitterTest_530, Write_Anchor_530) {
  YAML::Emitter emitter;
  emitter.Write(YAML::_Anchor("myanchor"));
  emitter.Write(std::string("value"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&myanchor"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_Alias_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.Write(YAML::_Anchor("anc"));
  emitter.Write(std::string("val"));
  emitter.Write(YAML::_Alias("anc"));
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("*anc"), std::string::npos);
}

// ==================== Write with Tag ====================

TEST_F(EmitterTest_530, Write_Tag_530) {
  YAML::Emitter emitter;
  emitter.Write(YAML::_Tag("!mytag"));
  emitter.Write(std::string("value"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("!mytag"), std::string::npos);
}

// ==================== Write with Comment ====================

TEST_F(EmitterTest_530, Write_Comment_530) {
  YAML::Emitter emitter;
  emitter.Write(std::string("value"));
  emitter.Write(YAML::_Comment("this is a comment"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("# this is a comment"), std::string::npos);
}

// ==================== Global settings ====================

TEST_F(EmitterTest_530, SetOutputCharset_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EmitNonAscii));
}

TEST_F(EmitterTest_530, SetOutputCharset_EscapeNonAscii_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetOutputCharset(YAML::EscapeNonAscii));
}

TEST_F(EmitterTest_530, SetStringFormat_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_530, SetBoolFormat_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_530, SetNullFormat_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
  EXPECT_TRUE(emitter.SetNullFormat(YAML::UpperNull));
  EXPECT_TRUE(emitter.SetNullFormat(YAML::CamelNull));
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}

TEST_F(EmitterTest_530, SetIntBase_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

TEST_F(EmitterTest_530, SetSeqFormat_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_530, SetMapFormat_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_530, SetIndent_Valid_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_530, SetIndent_Boundary_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_530, SetPreCommentIndent_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_530, SetPostCommentIndent_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

TEST_F(EmitterTest_530, SetFloatPrecision_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_530, SetDoublePrecision_530) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

// ==================== RestoreGlobalModifiedSettings ====================

TEST_F(EmitterTest_530, RestoreGlobalModifiedSettings_530) {
  YAML::Emitter emitter;
  emitter.SetSeqFormat(YAML::Flow);
  emitter.RestoreGlobalModifiedSettings();
  // Should still be good after restoring
  EXPECT_TRUE(emitter.good());
}

// ==================== Stream output ====================

TEST_F(EmitterTest_530, StreamConstructor_OutputToStream_530) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter.Write(std::string("hello"));
  EXPECT_TRUE(emitter.good());
  // Stream should contain output
  EXPECT_NE(ss.str().find("hello"), std::string::npos);
}

// ==================== Error cases ====================

TEST_F(EmitterTest_530, EndSeqWithoutBeginSeq_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_FALSE(emitter.good());
  EXPECT_NE(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_530, EndMapWithoutBeginMap_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_FALSE(emitter.good());
  EXPECT_NE(emitter.GetLastError(), "");
}

TEST_F(EmitterTest_530, MismatchedSeqMap_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_FALSE(emitter.good());
}

TEST_F(EmitterTest_530, MismatchedMapSeq_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_FALSE(emitter.good());
}

// ==================== Complex documents ====================

TEST_F(EmitterTest_530, ComplexNestedStructure_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::Key);
  emitter.Write(std::string("sequence"));
  emitter.SetLocalValue(YAML::Value);
  emitter.SetLocalValue(YAML::BeginSeq);
  emitter.Write(std::string("item1"));
  emitter.Write(std::string("item2"));
  emitter.SetLocalValue(YAML::EndSeq);
  emitter.SetLocalValue(YAML::Key);
  emitter.Write(std::string("nested_map"));
  emitter.SetLocalValue(YAML::Value);
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::Key);
  emitter.Write(std::string("inner_key"));
  emitter.SetLocalValue(YAML::Value);
  emitter.Write(std::string("inner_val"));
  emitter.SetLocalValue(YAML::EndMap);
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("sequence"), std::string::npos);
  EXPECT_NE(output.find("item1"), std::string::npos);
  EXPECT_NE(output.find("inner_key"), std::string::npos);
}

TEST_F(EmitterTest_530, MultipleDocuments_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::BeginDoc);
  emitter.Write(std::string("doc1"));
  emitter.SetLocalValue(YAML::EndDoc);
  emitter.SetLocalValue(YAML::BeginDoc);
  emitter.Write(std::string("doc2"));
  emitter.SetLocalValue(YAML::EndDoc);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("doc1"), std::string::npos);
  EXPECT_NE(output.find("doc2"), std::string::npos);
}

// ==================== SetLocalValue on bad emitter ====================

TEST_F(EmitterTest_530, SetLocalValueOnBadEmitter_DoesNothing_530) {
  YAML::Emitter emitter;
  // Put emitter in bad state
  emitter.SetLocalValue(YAML::EndSeq);
  EXPECT_FALSE(emitter.good());
  // Further calls should return self without crashing
  YAML::Emitter& ref = emitter.SetLocalValue(YAML::BeginDoc);
  EXPECT_EQ(&ref, &emitter);
  EXPECT_FALSE(emitter.good());
}

// ==================== Bool format variations ====================

TEST_F(EmitterTest_530, Write_BoolYesNo_530) {
  YAML::Emitter emitter;
  emitter.SetBoolFormat(YAML::YesNoBool);
  emitter.Write(true);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  // Should contain some form of yes
  bool found = (output.find("yes") != std::string::npos ||
                output.find("Yes") != std::string::npos ||
                output.find("YES") != std::string::npos);
  EXPECT_TRUE(found);
}

TEST_F(EmitterTest_530, Write_BoolOnOff_530) {
  YAML::Emitter emitter;
  emitter.SetBoolFormat(YAML::OnOffBool);
  emitter.Write(true);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  bool found = (output.find("on") != std::string::npos ||
                output.find("On") != std::string::npos ||
                output.find("ON") != std::string::npos);
  EXPECT_TRUE(found);
}

// ==================== Null format variations ====================

TEST_F(EmitterTest_530, Write_NullLower_530) {
  YAML::Emitter emitter;
  emitter.SetNullFormat(YAML::LowerNull);
  emitter.Write(YAML::_Null());
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("null"), std::string::npos);
}

TEST_F(EmitterTest_530, Write_NullTilde_530) {
  YAML::Emitter emitter;
  emitter.SetNullFormat(YAML::TildeNull);
  emitter.Write(YAML::_Null());
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("~"), std::string::npos);
}

// ==================== Int base variations ====================

TEST_F(EmitterTest_530, WriteInt_Hex_530) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Hex);
  emitter.WriteIntegralType(255);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0x"), std::string::npos);
}

TEST_F(EmitterTest_530, WriteInt_Oct_530) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Oct);
  emitter.WriteIntegralType(8);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_530, WriteInt_Dec_530) {
  YAML::Emitter emitter;
  emitter.SetIntBase(YAML::Dec);
  emitter.WriteIntegralType(42);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("42"), std::string::npos);
}

// ==================== Size tracking ====================

TEST_F(EmitterTest_530, SizeIncreasesAfterWrite_530) {
  YAML::Emitter emitter;
  std::size_t before = emitter.size();
  emitter.Write(std::string("something"));
  std::size_t after = emitter.size();
  EXPECT_GT(after, before);
}

// ==================== Flow map ====================

TEST_F(EmitterTest_530, FlowMap_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::Flow);
  emitter.SetLocalValue(YAML::BeginMap);
  emitter.SetLocalValue(YAML::Key);
  emitter.Write(std::string("a"));
  emitter.SetLocalValue(YAML::Value);
  emitter.Write(std::string("b"));
  emitter.SetLocalValue(YAML::EndMap);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("{"), std::string::npos);
  EXPECT_NE(output.find("}"), std::string::npos);
}

// ==================== Binary data ====================

TEST_F(EmitterTest_530, Write_Binary_530) {
  YAML::Emitter emitter;
  std::vector<unsigned char> data = {0x00, 0x01, 0x02, 0xFF};
  emitter.Write(YAML::Binary(data.data(), data.size()));
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// ==================== SetLocalIndent ====================

TEST_F(EmitterTest_530, SetLocalIndent_530) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = emitter.SetLocalIndent(YAML::_Indent(4));
  EXPECT_EQ(&ref, &emitter);
  EXPECT_TRUE(emitter.good());
}

// ==================== SetLocalPrecision ====================

TEST_F(EmitterTest_530, SetLocalPrecision_530) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = emitter.SetLocalPrecision(YAML::_Precision(10));
  EXPECT_EQ(&ref, &emitter);
  EXPECT_TRUE(emitter.good());
}

// ==================== Float/Double writing ====================

TEST_F(EmitterTest_530, WriteStreamable_Float_530) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(3.14f);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_530, WriteStreamable_Double_530) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(2.718281828);
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("2.71"), std::string::npos);
}

// ==================== Empty string ====================

TEST_F(EmitterTest_530, Write_EmptyString_530) {
  YAML::Emitter emitter;
  emitter.Write(std::string(""));
  EXPECT_TRUE(emitter.good());
}

// ==================== Literal string format ====================

TEST_F(EmitterTest_530, SetLocalValue_Literal_530) {
  YAML::Emitter emitter;
  emitter.SetLocalValue(YAML::Literal);
  emitter.Write(std::string("line1\nline2\nline3"));
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("|"), std::string::npos);
}
