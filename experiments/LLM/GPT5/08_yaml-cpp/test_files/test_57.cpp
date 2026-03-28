// File: test/emitter_operator_double_test_57.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class OperatorDoubleTest_57 : public ::testing::Test {
 protected:
  static std::string ToString(YAML::Emitter& e) {
    const char* s = e.c_str();
    return s ? std::string(s) : std::string();
  }
};

}  // namespace

TEST_F(OperatorDoubleTest_57, ReturnsSameEmitterReference_57) {
  YAML::Emitter emitter;

  YAML::Emitter& ref = (emitter << 1.25);

  EXPECT_EQ(&ref, &emitter);
}

TEST_F(OperatorDoubleTest_57, ProducesSomeOutputAndIsUsableAfterInsertion_57) {
  YAML::Emitter emitter;

  emitter << 1.5;

  EXPECT_GE(emitter.size(), 1u);
  EXPECT_NE(emitter.c_str(), nullptr);
  // If the library reports errors, this should normally still be good after writing a scalar.
  EXPECT_TRUE(emitter.good()) << "Emitter reported error: " << emitter.GetLastError();
}

TEST_F(OperatorDoubleTest_57, OutputContainsReasonableScalarForSimpleValue_57) {
  YAML::Emitter emitter;

  emitter << 1.5;

  const std::string out = ToString(emitter);
  EXPECT_FALSE(out.empty());

  // Avoid asserting exact formatting; just ensure the obvious token appears.
  // (YAML scalar emission for 1.5 should typically contain "1.5" somewhere.)
  EXPECT_NE(out.find("1.5"), std::string::npos) << "Output was: " << out;
}

TEST_F(OperatorDoubleTest_57, ChainingTwoInsertionsAppendsMoreContent_57) {
  YAML::Emitter emitter;

  emitter << 1.0;
  const std::size_t size_after_first = emitter.size();

  (emitter << 2.0);

  EXPECT_GE(emitter.size(), size_after_first);
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(OperatorDoubleTest_57, OperatorMatchesWriteStreamableObservableOutput_57) {
  // The operator<< overload is defined inline as WriteStreamable(v).
  // This test only checks observable equivalence (string output + status), not internal behavior.
  YAML::Emitter via_op;
  YAML::Emitter via_call;

  via_op << 3.125;
  via_call.WriteStreamable(3.125);

  EXPECT_EQ(ToString(via_op), ToString(via_call));
  EXPECT_EQ(via_op.size(), via_call.size());
  EXPECT_EQ(via_op.good(), via_call.good());
}

TEST_F(OperatorDoubleTest_57, HandlesNegativeAndZeroValues_57) {
  YAML::Emitter emitter;

  emitter << -0.0;
  const std::string out1 = ToString(emitter);

  emitter << -42.5;
  const std::string out2 = ToString(emitter);

  EXPECT_FALSE(out1.empty());
  EXPECT_FALSE(out2.empty());
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(OperatorDoubleTest_57, DoesNotCrashOnNonFiniteValues_57) {
  YAML::Emitter emitter;

  const double inf = std::numeric_limits<double>::infinity();
  const double nan = std::numeric_limits<double>::quiet_NaN();

  // We avoid asserting exact text ("inf"/".inf"/"nan"/".nan") since formatting is implementation-defined.
  // The core observable behavior we require: no crash, emitter remains in a valid queryable state.
  emitter << inf;
  EXPECT_NE(emitter.c_str(), nullptr);

  emitter << -inf;
  EXPECT_NE(emitter.c_str(), nullptr);

  emitter << nan;
  EXPECT_NE(emitter.c_str(), nullptr);
}

TEST_F(OperatorDoubleTest_57, WritingToBadStreamYieldsObservableErrorOrNoGrowth_57) {
  std::ostringstream oss;
  oss.setstate(std::ios::badbit);

  YAML::Emitter emitter(oss);

  const std::size_t before = emitter.size();
  emitter << 1.0;
  const std::size_t after = emitter.size();

  // Different implementations may either mark the emitter bad, or simply not emit/grow.
  // We only assert something observable and conservative.
  EXPECT_TRUE(!emitter.good() || after == before || !emitter.GetLastError().empty());
}
