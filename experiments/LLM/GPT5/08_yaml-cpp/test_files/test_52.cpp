// File: test/emitter_operator_long_test_52.cpp

#include <gtest/gtest.h>

#include <climits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterOperatorLongTest_52 : public ::testing::Test {
protected:
  static std::string EmitToString(long v) {
    YAML::Emitter out;
    out << v;  // operator<<(Emitter&, long)
    const char* s = out.c_str();
    return s ? std::string(s) : std::string();
  }

  static std::string EmitToStringWithStream(long v) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out << v;
    // Prefer emitted string from emitter API (not stream), but stream is a useful cross-check.
    const char* s = out.c_str();
    if (s) return std::string(s);
    return ss.str();
  }
};

}  // namespace

TEST_F(EmitterOperatorLongTest_52, ReturnsSameEmitterReference_52) {
  YAML::Emitter out;
  YAML::Emitter& ref = (out << 123L);
  EXPECT_EQ(&ref, &out);
}

TEST_F(EmitterOperatorLongTest_52, EmitsZeroAsPlainDecimal_52) {
  const std::string emitted = EmitToString(0L);
  EXPECT_EQ(emitted, std::to_string(0L));
}

TEST_F(EmitterOperatorLongTest_52, EmitsPositiveValueAsPlainDecimal_52) {
  const long v = 42L;
  const std::string emitted = EmitToString(v);
  EXPECT_EQ(emitted, std::to_string(v));
}

TEST_F(EmitterOperatorLongTest_52, EmitsNegativeValueAsPlainDecimal_52) {
  const long v = -12345L;
  const std::string emitted = EmitToString(v);
  EXPECT_EQ(emitted, std::to_string(v));
}

TEST_F(EmitterOperatorLongTest_52, EmitsLongMaxAsPlainDecimal_52) {
  const long v = LONG_MAX;
  const std::string emitted = EmitToStringWithStream(v);
  EXPECT_EQ(emitted, std::to_string(v));
}

TEST_F(EmitterOperatorLongTest_52, EmitsLongMinAsPlainDecimal_52) {
  const long v = LONG_MIN;
  const std::string emitted = EmitToStringWithStream(v);
  EXPECT_EQ(emitted, std::to_string(v));
}

TEST_F(EmitterOperatorLongTest_52, SupportsChainingAndPreservesOrder_52) {
  YAML::Emitter out;
  out << 1L << 2L;

  const std::string s = out.c_str() ? std::string(out.c_str()) : std::string();

  // We avoid assuming exact delimiter (space/newline/etc.). We only require that
  // both token strings appear and that "1" occurs before "2".
  const std::string a = std::to_string(1L);
  const std::string b = std::to_string(2L);

  const auto pos_a = s.find(a);
  const auto pos_b = s.find(b);

  ASSERT_NE(pos_a, std::string::npos);
  ASSERT_NE(pos_b, std::string::npos);
  EXPECT_LT(pos_a, pos_b);
}

TEST_F(EmitterOperatorLongTest_52, DoesNotThrowForTypicalValues_52) {
  YAML::Emitter out;
  EXPECT_NO_THROW(out << 0L);
  EXPECT_NO_THROW(out << 999999L);
  EXPECT_NO_THROW(out << -999999L);
}
