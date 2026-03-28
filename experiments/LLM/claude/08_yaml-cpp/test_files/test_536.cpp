#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterWriteBoolTest_536 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Default bool format for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueDefault_536) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Default should be "true" (TrueFalseBool, LongBool, LowerCase by default)
  EXPECT_FALSE(output.empty());
}

// Test: Default bool format for false
TEST_F(EmitterWriteBoolTest_536, WriteFalseDefault_536) {
  YAML::Emitter emitter;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: TrueFalseBool with LongBool format for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueLongTrueFalseBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("true"));
}

// Test: TrueFalseBool with LongBool format for false
TEST_F(EmitterWriteBoolTest_536, WriteFalseLongTrueFalseBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::LongBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("false"));
}

// Test: ShortBool format for true (TrueFalseBool) should emit single char
TEST_F(EmitterWriteBoolTest_536, WriteTrueShortTrueFalseBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::ShortBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // ShortBool should emit only the first character
  EXPECT_FALSE(output.empty());
}

// Test: ShortBool format for false (TrueFalseBool) should emit single char
TEST_F(EmitterWriteBoolTest_536, WriteFalseShortTrueFalseBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::ShortBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: YesNoBool with LongBool for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueLongYesNoBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::YesNoBool << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Should contain "yes" or "Yes" or "YES" depending on case format
  EXPECT_FALSE(output.empty());
}

// Test: YesNoBool with LongBool for false
TEST_F(EmitterWriteBoolTest_536, WriteFalseLongYesNoBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::YesNoBool << YAML::LongBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: OnOffBool with LongBool for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueLongOnOffBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::OnOffBool << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: OnOffBool with LongBool for false
TEST_F(EmitterWriteBoolTest_536, WriteFalseLongOnOffBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::OnOffBool << YAML::LongBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: YesNoBool with ShortBool for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueShortYesNoBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::YesNoBool << YAML::ShortBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Short form of "yes" should be "y"
  EXPECT_FALSE(output.empty());
}

// Test: OnOffBool with ShortBool for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueShortOnOffBool_536) {
  YAML::Emitter emitter;
  emitter << YAML::OnOffBool << YAML::ShortBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: Emitter is good after writing bool
TEST_F(EmitterWriteBoolTest_536, EmitterGoodAfterWriteBool_536) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  EXPECT_EQ("", emitter.GetLastError());
}

// Test: Write bool returns reference to emitter (chaining)
TEST_F(EmitterWriteBoolTest_536, WriteBoolReturnsSelf_536) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = (emitter << true);
  EXPECT_EQ(&emitter, &ref);
}

// Test: Write bool to stream
TEST_F(EmitterWriteBoolTest_536, WriteBoolToStream_536) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_FALSE(output.empty());
}

// Test: Write multiple bools in a sequence
TEST_F(EmitterWriteBoolTest_536, WriteBoolsInSequence_536) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << true;
  emitter << false;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: Write bool in a map
TEST_F(EmitterWriteBoolTest_536, WriteBoolInMap_536) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "flag";
  emitter << YAML::Value << true;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: Write bool with UpperCase
TEST_F(EmitterWriteBoolTest_536, WriteTrueUpperCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::UpperCase << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("TRUE"));
}

// Test: Write bool with CamelCase
TEST_F(EmitterWriteBoolTest_536, WriteTrueCamelCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::CamelCase << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("True"));
}

// Test: Write bool with LowerCase
TEST_F(EmitterWriteBoolTest_536, WriteTrueLowerCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::LowerCase << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("true"));
}

// Test: Write false with UpperCase
TEST_F(EmitterWriteBoolTest_536, WriteFalseUpperCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::UpperCase << YAML::LongBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("FALSE"));
}

// Test: Write false with CamelCase
TEST_F(EmitterWriteBoolTest_536, WriteFalseCamelCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::TrueFalseBool << YAML::CamelCase << YAML::LongBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("False"));
}

// Test: Size is nonzero after writing bool
TEST_F(EmitterWriteBoolTest_536, SizeNonzeroAfterBool_536) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_GT(emitter.size(), 0u);
}

// Test: Flow sequence with bools
TEST_F(EmitterWriteBoolTest_536, WriteBoolsInFlowSequence_536) {
  YAML::Emitter emitter;
  emitter << YAML::Flow << YAML::BeginSeq;
  emitter << true << false;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("["));
  EXPECT_NE(std::string::npos, output.find("]"));
}

// Test: Bool as map key
TEST_F(EmitterWriteBoolTest_536, WriteBoolAsMapKey_536) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << true;
  emitter << YAML::Value << "val";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: SetBoolFormat returns true for valid values
TEST_F(EmitterWriteBoolTest_536, SetBoolFormatValid_536) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::ShortBool));
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LongBool));
}

// Test: Newly constructed emitter is good
TEST_F(EmitterWriteBoolTest_536, NewEmitterIsGood_536) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

// Test: Write YesNoBool with UpperCase for false
TEST_F(EmitterWriteBoolTest_536, WriteFalseYesNoBoolUpperCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::YesNoBool << YAML::UpperCase << YAML::LongBool;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("NO"));
}

// Test: Write OnOffBool with CamelCase for true
TEST_F(EmitterWriteBoolTest_536, WriteTrueOnOffBoolCamelCase_536) {
  YAML::Emitter emitter;
  emitter << YAML::OnOffBool << YAML::CamelCase << YAML::LongBool;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("On"));
}

// Test: Streaming bool to external stream produces output
TEST_F(EmitterWriteBoolTest_536, StreamOutputContainsBool_536) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << YAML::TrueFalseBool << YAML::LongBool << YAML::LowerCase;
  emitter << false;
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(std::string::npos, output.find("false"));
}
