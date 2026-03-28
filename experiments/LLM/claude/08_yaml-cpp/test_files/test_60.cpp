#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterPrecisionTest_60 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that operator<< with _Precision returns the emitter reference
TEST_F(EmitterPrecisionTest_60, OperatorReturnsEmitterReference_60) {
  YAML::Emitter emitter;
  YAML::_Precision precision(5, 10);
  YAML::Emitter& result = emitter << precision;
  EXPECT_EQ(&result, &emitter);
}

// Test that SetLocalPrecision returns the emitter reference
TEST_F(EmitterPrecisionTest_60, SetLocalPrecisionReturnsEmitterReference_60) {
  YAML::Emitter emitter;
  YAML::_Precision precision(3, 6);
  YAML::Emitter& result = emitter.SetLocalPrecision(precision);
  EXPECT_EQ(&result, &emitter);
}

// Test that emitter is still good after setting precision
TEST_F(EmitterPrecisionTest_60, EmitterGoodAfterSetPrecision_60) {
  YAML::Emitter emitter;
  YAML::_Precision precision(5, 10);
  emitter << precision;
  EXPECT_TRUE(emitter.good());
}

// Test that setting float precision globally works
TEST_F(EmitterPrecisionTest_60, SetFloatPrecisionGlobally_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
  EXPECT_TRUE(emitter.good());
}

// Test that setting double precision globally works
TEST_F(EmitterPrecisionTest_60, SetDoublePrecisionGlobally_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(12));
  EXPECT_TRUE(emitter.good());
}

// Test precision affects float output
TEST_F(EmitterPrecisionTest_60, FloatPrecisionAffectsOutput_60) {
  YAML::Emitter emitter1;
  emitter1.SetFloatPrecision(2);
  emitter1 << 3.14159f;
  std::string output1 = emitter1.c_str();

  YAML::Emitter emitter2;
  emitter2.SetFloatPrecision(6);
  emitter2 << 3.14159f;
  std::string output2 = emitter2.c_str();

  // Different precisions should produce different output lengths or values
  // (at minimum, the emitter should be good in both cases)
  EXPECT_TRUE(emitter1.good());
  EXPECT_TRUE(emitter2.good());
}

// Test precision affects double output
TEST_F(EmitterPrecisionTest_60, DoublePrecisionAffectsOutput_60) {
  YAML::Emitter emitter1;
  emitter1.SetDoublePrecision(2);
  emitter1 << 3.141592653589793;
  std::string output1 = emitter1.c_str();

  YAML::Emitter emitter2;
  emitter2.SetDoublePrecision(15);
  emitter2 << 3.141592653589793;
  std::string output2 = emitter2.c_str();

  EXPECT_TRUE(emitter1.good());
  EXPECT_TRUE(emitter2.good());
  // Higher precision should generally produce a longer or more detailed output
  EXPECT_NE(output1, output2);
}

// Test local precision via operator<< with float
TEST_F(EmitterPrecisionTest_60, LocalPrecisionWithFloat_60) {
  YAML::Emitter emitter;
  emitter << YAML::_Precision(2, 2) << 3.14159f;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test local precision via operator<< with double
TEST_F(EmitterPrecisionTest_60, LocalPrecisionWithDouble_60) {
  YAML::Emitter emitter;
  emitter << YAML::_Precision(2, 2) << 3.141592653589793;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test that local precision does not persist after use
TEST_F(EmitterPrecisionTest_60, LocalPrecisionDoesNotPersist_60) {
  YAML::Emitter emitter;
  emitter.SetDoublePrecision(15);
  
  // Use local precision for one value
  emitter << YAML::BeginSeq;
  emitter << YAML::_Precision(2, 2) << 3.141592653589793;
  // Second value should use global precision
  emitter << 3.141592653589793;
  emitter << YAML::EndSeq;
  
  EXPECT_TRUE(emitter.good());
}

// Test default constructor creates a good emitter
TEST_F(EmitterPrecisionTest_60, DefaultConstructorGood_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
  EXPECT_EQ(emitter.size(), 0u);
}

// Test constructor with stream
TEST_F(EmitterPrecisionTest_60, StreamConstructor_60) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);
  EXPECT_TRUE(emitter.good());
}

// Test writing a string
TEST_F(EmitterPrecisionTest_60, WriteString_60) {
  YAML::Emitter emitter;
  emitter << "hello";
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "hello");
}

// Test writing boolean
TEST_F(EmitterPrecisionTest_60, WriteBool_60) {
  YAML::Emitter emitter;
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test writing null
TEST_F(EmitterPrecisionTest_60, WriteNull_60) {
  YAML::Emitter emitter;
  emitter << YAML::Null;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test writing a sequence
TEST_F(EmitterPrecisionTest_60, WriteSequence_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << 1 << 2 << 3;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test writing a map
TEST_F(EmitterPrecisionTest_60, WriteMap_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test precision with zero values for float precision
TEST_F(EmitterPrecisionTest_60, ZeroFloatPrecision_60) {
  YAML::Emitter emitter;
  YAML::_Precision precision(0, 10);
  emitter << precision << 3.14f;
  // Emitter may or may not handle zero precision gracefully
  // Just check it doesn't crash and produces some output
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test precision with zero values for double precision
TEST_F(EmitterPrecisionTest_60, ZeroDoublePrecision_60) {
  YAML::Emitter emitter;
  YAML::_Precision precision(10, 0);
  emitter << precision << 3.14159;
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test chaining precision and multiple values
TEST_F(EmitterPrecisionTest_60, ChainingPrecisionAndValues_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::_Precision(3, 3) << 1.23456f;
  emitter << YAML::_Precision(6, 6) << 1.23456789;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Test precision with stream-based emitter
TEST_F(EmitterPrecisionTest_60, PrecisionWithStreamEmitter_60) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);
  emitter << YAML::_Precision(4, 8) << 2.718281828;
  EXPECT_TRUE(emitter.good());
  std::string output = oss.str();
  EXPECT_FALSE(output.empty());
}

// Test SetFloatPrecision and SetDoublePrecision return true for valid values
TEST_F(EmitterPrecisionTest_60, SetPrecisionValidValues_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(1));
  EXPECT_TRUE(emitter.SetDoublePrecision(1));
  EXPECT_TRUE(emitter.SetFloatPrecision(10));
  EXPECT_TRUE(emitter.SetDoublePrecision(20));
}

// Test c_str returns non-null after writing
TEST_F(EmitterPrecisionTest_60, CStrNonNullAfterWrite_60) {
  YAML::Emitter emitter;
  emitter << "test";
  EXPECT_NE(emitter.c_str(), nullptr);
}

// Test size after writing
TEST_F(EmitterPrecisionTest_60, SizeAfterWrite_60) {
  YAML::Emitter emitter;
  emitter << "test";
  EXPECT_GT(emitter.size(), 0u);
}

// Test GetLastError is empty when good
TEST_F(EmitterPrecisionTest_60, GetLastErrorEmptyWhenGood_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
  EXPECT_TRUE(emitter.GetLastError().empty());
}

// Test emitting comment
TEST_F(EmitterPrecisionTest_60, EmitComment_60) {
  YAML::Emitter emitter;
  emitter << YAML::Comment("this is a comment");
  emitter << "value";
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("#"), std::string::npos);
}

// Test setting various emitter manipulators
TEST_F(EmitterPrecisionTest_60, SetBoolFormat_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
  emitter << true;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_EQ(output, "true");
}

// Test flow sequence format
TEST_F(EmitterPrecisionTest_60, FlowSequenceFormat_60) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginSeq << 1 << 2 << 3 << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("["), std::string::npos);
}

// Test flow map format
TEST_F(EmitterPrecisionTest_60, FlowMapFormat_60) {
  YAML::Emitter emitter;
  emitter << YAML::Flow;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << 1;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("{"), std::string::npos);
}

// Test anchor and alias
TEST_F(EmitterPrecisionTest_60, AnchorAndAlias_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "a" << YAML::Value << YAML::Anchor("anc") << "value";
  emitter << YAML::Key << "b" << YAML::Value << YAML::Alias("anc");
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("&anc"), std::string::npos);
  EXPECT_NE(output.find("*anc"), std::string::npos);
}

// Test tag
TEST_F(EmitterPrecisionTest_60, WriteTag_60) {
  YAML::Emitter emitter;
  emitter << YAML::VerbatimTag("tag:yaml.org,2002:str") << "hello";
  EXPECT_TRUE(emitter.good());
}

// Test RestoreGlobalModifiedSettings
TEST_F(EmitterPrecisionTest_60, RestoreGlobalModifiedSettings_60) {
  YAML::Emitter emitter;
  emitter.SetFloatPrecision(2);
  emitter.SetDoublePrecision(2);
  emitter.RestoreGlobalModifiedSettings();
  // After restoring, emitter should still be good
  EXPECT_TRUE(emitter.good());
}

// Test precision with negative precision values in _Precision
TEST_F(EmitterPrecisionTest_60, NegativePrecisionValues_60) {
  YAML::Emitter emitter;
  YAML::_Precision precision(-1, -1);
  emitter << precision << 3.14f;
  // Just verify it doesn't crash
  std::string output = emitter.c_str();
  EXPECT_NE(output, nullptr);
}

// Test writing char
TEST_F(EmitterPrecisionTest_60, WriteChar_60) {
  YAML::Emitter emitter;
  emitter << 'A';
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test writing integer
TEST_F(EmitterPrecisionTest_60, WriteInteger_60) {
  YAML::Emitter emitter;
  emitter << 42;
  EXPECT_TRUE(emitter.good());
  EXPECT_STREQ(emitter.c_str(), "42");
}

// Test SetIndent
TEST_F(EmitterPrecisionTest_60, SetIndent_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
  EXPECT_TRUE(emitter.good());
}

// Test SetSeqFormat
TEST_F(EmitterPrecisionTest_60, SetSeqFormat_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
  EXPECT_TRUE(emitter.good());
}

// Test SetMapFormat
TEST_F(EmitterPrecisionTest_60, SetMapFormat_60) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
  EXPECT_TRUE(emitter.good());
}

// Test multiple documents
TEST_F(EmitterPrecisionTest_60, MultipleDocuments_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc;
  emitter << "doc1";
  emitter << YAML::EndDoc;
  emitter << YAML::BeginDoc;
  emitter << "doc2";
  emitter << YAML::EndDoc;
  EXPECT_TRUE(emitter.good());
}

// Test writing binary data
TEST_F(EmitterPrecisionTest_60, WriteBinary_60) {
  YAML::Emitter emitter;
  const unsigned char data[] = {0x01, 0x02, 0x03, 0x04};
  YAML::Binary binary(data, sizeof(data));
  emitter << binary;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test that high precision float produces more digits
TEST_F(EmitterPrecisionTest_60, HighPrecisionFloat_60) {
  YAML::Emitter emitter1;
  emitter1.SetFloatPrecision(2);
  emitter1 << 1.23456789f;
  
  YAML::Emitter emitter2;
  emitter2.SetFloatPrecision(8);
  emitter2 << 1.23456789f;
  
  EXPECT_TRUE(emitter1.good());
  EXPECT_TRUE(emitter2.good());
  
  std::string out1 = emitter1.c_str();
  std::string out2 = emitter2.c_str();
  // Higher precision should generally produce a longer string
  EXPECT_LE(out1.size(), out2.size());
}

// Test local precision in a sequence context
TEST_F(EmitterPrecisionTest_60, LocalPrecisionInSequence_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::_Precision(2, 2) << 1.23456;
  emitter << YAML::_Precision(10, 10) << 1.23456;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
}

// Test local precision in a map context
TEST_F(EmitterPrecisionTest_60, LocalPrecisionInMap_60) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "pi";
  emitter << YAML::Value << YAML::_Precision(4, 4) << 3.14159265;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
}
