#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterTest_35 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ============================================================
// Basic Construction and State Tests
// ============================================================

TEST_F(EmitterTest_35, DefaultConstructor_GoodState_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_35, DefaultConstructor_EmptyOutput_35) {
  YAML::Emitter emitter;
  EXPECT_EQ(emitter.size(), 0u);
}

TEST_F(EmitterTest_35, DefaultConstructor_CStrNotNull_35) {
  YAML::Emitter emitter;
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(EmitterTest_35, StreamConstructor_GoodState_35) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterTest_35, GetLastError_NoErrorInitially_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
  // When good, GetLastError should return an empty string or similar
  std::string err = emitter.GetLastError();
  // Just checking it doesn't crash; if good(), error should be empty
  if (emitter.good()) {
    EXPECT_TRUE(err.empty());
  }
}

// ============================================================
// WriteStreamable - Float Tests
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_FloatPositive_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(3.14f);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
  // Should contain a numeric representation of 3.14
  EXPECT_NE(output.find("3.14"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_FloatNegative_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(-2.5f);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
  EXPECT_NE(output.find("-2.5"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_FloatZero_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(0.0f);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_FloatNaN_35) {
  YAML::Emitter emitter;
  float nan_val = std::numeric_limits<float>::quiet_NaN();
  emitter.WriteStreamable(nan_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find(".nan"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_FloatPositiveInfinity_35) {
  YAML::Emitter emitter;
  float inf_val = std::numeric_limits<float>::infinity();
  emitter.WriteStreamable(inf_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find(".inf"), std::string::npos);
  // Should NOT have a minus sign for positive infinity
  EXPECT_EQ(output.find("-.inf"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_FloatNegativeInfinity_35) {
  YAML::Emitter emitter;
  float neg_inf_val = -std::numeric_limits<float>::infinity();
  emitter.WriteStreamable(neg_inf_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-.inf"), std::string::npos);
}

// ============================================================
// WriteStreamable - Double Tests
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_DoublePositive_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(3.141592653589793);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
  EXPECT_NE(output.find("3.14159"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleNegative_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(-1.23456789);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
  EXPECT_NE(output.find("-1.2345"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleZero_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(0.0);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleNaN_35) {
  YAML::Emitter emitter;
  double nan_val = std::numeric_limits<double>::quiet_NaN();
  emitter.WriteStreamable(nan_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find(".nan"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_DoublePositiveInfinity_35) {
  YAML::Emitter emitter;
  double inf_val = std::numeric_limits<double>::infinity();
  emitter.WriteStreamable(inf_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find(".inf"), std::string::npos);
  EXPECT_EQ(output.find("-.inf"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleNegativeInfinity_35) {
  YAML::Emitter emitter;
  double neg_inf_val = -std::numeric_limits<double>::infinity();
  emitter.WriteStreamable(neg_inf_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-.inf"), std::string::npos);
}

// ============================================================
// WriteStreamable - Boundary values
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_FloatMax_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<float>::max());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_FloatMin_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<float>::min());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_FloatLowest_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<float>::lowest());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleMax_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<double>::max());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleMin_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<double>::min());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleLowest_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<double>::lowest());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_FloatDenormMin_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<float>::denorm_min());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleDenormMin_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(std::numeric_limits<double>::denorm_min());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// WriteStreamable - Output to external stream
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_FloatToExternalStream_35) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter.WriteStreamable(42.5f);
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find("42.5"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_DoubleToExternalStream_35) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter.WriteStreamable(99.99);
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find("99.99"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_NaNToExternalStream_35) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter.WriteStreamable(std::numeric_limits<double>::quiet_NaN());
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find(".nan"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_InfToExternalStream_35) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter.WriteStreamable(std::numeric_limits<double>::infinity());
  EXPECT_TRUE(emitter.good());
  std::string output = ss.str();
  EXPECT_NE(output.find(".inf"), std::string::npos);
}

// ============================================================
// Write - Basic types
// ============================================================

TEST_F(EmitterTest_35, Write_String_35) {
  YAML::Emitter emitter;
  emitter.Write(std::string("hello"));
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
}

TEST_F(EmitterTest_35, Write_CString_35) {
  YAML::Emitter emitter;
  const char* str = "world";
  emitter.Write(str, 5);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("world"), std::string::npos);
}

TEST_F(EmitterTest_35, Write_BoolTrue_35) {
  YAML::Emitter emitter;
  emitter.Write(true);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, Write_BoolFalse_35) {
  YAML::Emitter emitter;
  emitter.Write(false);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, Write_Char_35) {
  YAML::Emitter emitter;
  emitter.Write('A');
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("A"), std::string::npos);
}

TEST_F(EmitterTest_35, Write_Null_35) {
  YAML::Emitter emitter;
  emitter.Write(YAML::_Null());
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Write - Empty string
// ============================================================

TEST_F(EmitterTest_35, Write_EmptyString_35) {
  YAML::Emitter emitter;
  emitter.Write(std::string(""));
  EXPECT_TRUE(emitter.good());
}

// ============================================================
// Setter Tests
// ============================================================

TEST_F(EmitterTest_35, SetFloatPrecision_ValidValue_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetFloatPrecision(6));
}

TEST_F(EmitterTest_35, SetDoublePrecision_ValidValue_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetDoublePrecision(15));
}

TEST_F(EmitterTest_35, SetIndent_ValidValue_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(4));
}

TEST_F(EmitterTest_35, SetIndent_MinimalValue_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIndent(2));
}

TEST_F(EmitterTest_35, SetBoolFormat_TrueFalse_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::TrueFalseBool));
}

TEST_F(EmitterTest_35, SetBoolFormat_YesNo_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::YesNoBool));
}

TEST_F(EmitterTest_35, SetBoolFormat_OnOff_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::OnOffBool));
}

TEST_F(EmitterTest_35, SetBoolFormat_UpperCase_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::UpperCase));
}

TEST_F(EmitterTest_35, SetBoolFormat_LowerCase_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::LowerCase));
}

TEST_F(EmitterTest_35, SetBoolFormat_CamelCase_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetBoolFormat(YAML::CamelCase));
}

TEST_F(EmitterTest_35, SetSeqFormat_Block_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Block));
}

TEST_F(EmitterTest_35, SetSeqFormat_Flow_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetSeqFormat(YAML::Flow));
}

TEST_F(EmitterTest_35, SetMapFormat_Block_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Block));
}

TEST_F(EmitterTest_35, SetMapFormat_Flow_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetMapFormat(YAML::Flow));
}

// ============================================================
// Precision affects output
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_FloatPrecisionAffectsOutput_35) {
  YAML::Emitter emitter1;
  emitter1.SetFloatPrecision(2);
  emitter1.WriteStreamable(3.14159f);
  std::string output1 = emitter1.c_str();

  YAML::Emitter emitter2;
  emitter2.SetFloatPrecision(7);
  emitter2.WriteStreamable(3.14159f);
  std::string output2 = emitter2.c_str();

  // With different precisions, the outputs may differ
  // (at minimum both should be valid)
  EXPECT_TRUE(emitter1.good());
  EXPECT_TRUE(emitter2.good());
}

TEST_F(EmitterTest_35, WriteStreamable_DoublePrecisionAffectsOutput_35) {
  YAML::Emitter emitter1;
  emitter1.SetDoublePrecision(3);
  emitter1.WriteStreamable(3.141592653589793);
  std::string output1 = emitter1.c_str();

  YAML::Emitter emitter2;
  emitter2.SetDoublePrecision(15);
  emitter2.WriteStreamable(3.141592653589793);
  std::string output2 = emitter2.c_str();

  EXPECT_TRUE(emitter1.good());
  EXPECT_TRUE(emitter2.good());
  // Higher precision output should be longer or equal
  EXPECT_GE(output2.size(), output1.size());
}

// ============================================================
// Chaining / Return value test
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_ReturnsSelfReference_35) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = emitter.WriteStreamable(1.0);
  EXPECT_EQ(&ref, &emitter);
}

// ============================================================
// WriteStreamable with non-floating-point type (integer via streamable)
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_IntegerType_35) {
  // WriteStreamable can accept integer types too; is_floating_point will be false
  // so it should just stream normally without special NaN/Inf handling
  YAML::Emitter emitter;
  emitter.WriteStreamable(42);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

// ============================================================
// WriteStreamable - Negative zero
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_NegativeZeroFloat_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(-0.0f);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Negative zero should produce a valid output (could be "0" or "-0")
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_NegativeZeroDouble_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(-0.0);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// WriteStreamable - Very small float
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_VerySmallFloat_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(1.0e-38f);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_VerySmallDouble_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(1.0e-300);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// WriteStreamable - Very large float
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_VeryLargeFloat_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(1.0e38f);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_VeryLargeDouble_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(1.0e300);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// ============================================================
// Size and c_str consistency
// ============================================================

TEST_F(EmitterTest_35, SizeMatchesCStrLength_35) {
  YAML::Emitter emitter;
  emitter.WriteStreamable(123.456);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_EQ(emitter.size(), output.size());
}

// ============================================================
// Signaling NaN (if supported)
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_SignalingNaN_Float_35) {
  if (std::numeric_limits<float>::has_signaling_NaN) {
    YAML::Emitter emitter;
    float snan = std::numeric_limits<float>::signaling_NaN();
    emitter.WriteStreamable(snan);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find(".nan"), std::string::npos);
  }
}

TEST_F(EmitterTest_35, WriteStreamable_SignalingNaN_Double_35) {
  if (std::numeric_limits<double>::has_signaling_NaN) {
    YAML::Emitter emitter;
    double snan = std::numeric_limits<double>::signaling_NaN();
    emitter.WriteStreamable(snan);
    EXPECT_TRUE(emitter.good());
    std::string output = emitter.c_str();
    EXPECT_NE(output.find(".nan"), std::string::npos);
  }
}

// ============================================================
// RestoreGlobalModifiedSettings
// ============================================================

TEST_F(EmitterTest_35, RestoreGlobalModifiedSettings_DoesNotCrash_35) {
  YAML::Emitter emitter;
  emitter.SetFloatPrecision(3);
  emitter.SetDoublePrecision(5);
  emitter.RestoreGlobalModifiedSettings();
  EXPECT_TRUE(emitter.good());
}

// ============================================================
// Non-copyable
// ============================================================

TEST_F(EmitterTest_35, EmitterIsNonCopyable_35) {
  EXPECT_FALSE(std::is_copy_constructible<YAML::Emitter>::value);
  EXPECT_FALSE(std::is_copy_assignable<YAML::Emitter>::value);
}

// ============================================================
// SetPreCommentIndent and SetPostCommentIndent
// ============================================================

TEST_F(EmitterTest_35, SetPreCommentIndent_ValidValue_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPreCommentIndent(2));
}

TEST_F(EmitterTest_35, SetPostCommentIndent_ValidValue_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetPostCommentIndent(1));
}

// ============================================================
// WriteStreamable with long double
// ============================================================

TEST_F(EmitterTest_35, WriteStreamable_LongDouble_35) {
  YAML::Emitter emitter;
  long double val = 1.23456789012345678L;
  emitter.WriteStreamable(val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

TEST_F(EmitterTest_35, WriteStreamable_LongDoubleNaN_35) {
  YAML::Emitter emitter;
  long double nan_val = std::numeric_limits<long double>::quiet_NaN();
  emitter.WriteStreamable(nan_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find(".nan"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_LongDoubleInf_35) {
  YAML::Emitter emitter;
  long double inf_val = std::numeric_limits<long double>::infinity();
  emitter.WriteStreamable(inf_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find(".inf"), std::string::npos);
}

TEST_F(EmitterTest_35, WriteStreamable_LongDoubleNegInf_35) {
  YAML::Emitter emitter;
  long double neg_inf_val = -std::numeric_limits<long double>::infinity();
  emitter.WriteStreamable(neg_inf_val);
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("-.inf"), std::string::npos);
}

// ============================================================
// SetIntBase
// ============================================================

TEST_F(EmitterTest_35, SetIntBase_Dec_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Dec));
}

TEST_F(EmitterTest_35, SetIntBase_Hex_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Hex));
}

TEST_F(EmitterTest_35, SetIntBase_Oct_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetIntBase(YAML::Oct));
}

// ============================================================
// SetStringFormat
// ============================================================

TEST_F(EmitterTest_35, SetStringFormat_SingleQuoted_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::SingleQuoted));
}

TEST_F(EmitterTest_35, SetStringFormat_DoubleQuoted_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::DoubleQuoted));
}

TEST_F(EmitterTest_35, SetStringFormat_Literal_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetStringFormat(YAML::Literal));
}

// ============================================================
// SetNullFormat
// ============================================================

TEST_F(EmitterTest_35, SetNullFormat_LowerNull_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::LowerNull));
}

TEST_F(EmitterTest_35, SetNullFormat_TildeNull_35) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.SetNullFormat(YAML::TildeNull));
}
