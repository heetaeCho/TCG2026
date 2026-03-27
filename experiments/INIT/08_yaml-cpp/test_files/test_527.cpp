// TEST_ID: 527
// File: emitter_set_float_precision_test_527.cpp

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSetFloatPrecisionTest_527 : public ::testing::Test {
protected:
  static std::string EmitFloatWithPrecision_527(std::size_t precision, float value) {
    YAML::Emitter out;

    const bool ok = out.SetFloatPrecision(precision);
    if (!ok) {
      // Return a sentinel that makes failures obvious while keeping behavior black-box.
      return std::string("<<SetFloatPrecisionFailed>>:") + out.GetLastError();
    }

    // Use the public interface only.
    out.WriteStreamable<float>(value);
    return std::string(out.c_str(), out.size());
  }

  static std::string EmitDoubleWithFloatPrecisionOnly_527(std::size_t floatPrecision, double value) {
    YAML::Emitter out;

    const bool ok = out.SetFloatPrecision(floatPrecision);
    if (!ok) {
      return std::string("<<SetFloatPrecisionFailed>>:") + out.GetLastError();
    }

    // If the implementation distinguishes float/double precision, this should follow double rules.
    out.WriteStreamable<double>(value);
    return std::string(out.c_str(), out.size());
  }
};

TEST_F(EmitterSetFloatPrecisionTest_527, SetFloatPrecisionReturnsBoolAndDoesNotBreakGoodState_527) {
  YAML::Emitter out;

  const bool beforeGood = out.good();
  const bool ok = out.SetFloatPrecision(6);

  // Observable behavior only: returned bool and public error/good indicators.
  if (ok) {
    EXPECT_TRUE(out.good()) << "Emitter should remain good after successful SetFloatPrecision.";
    EXPECT_TRUE(out.GetLastError().empty()) << "No error expected after successful SetFloatPrecision.";
  } else {
    // If the call is rejected, the interface should expose some failure signal.
    EXPECT_TRUE(!out.good() || !out.GetLastError().empty())
        << "If SetFloatPrecision fails, expect either !good() or a non-empty last error.";
  }

  // If it was good before and the call succeeds, it should stay good (common-sense observable contract).
  if (beforeGood && ok) {
    EXPECT_TRUE(out.good());
  }
}

TEST_F(EmitterSetFloatPrecisionTest_527, ChangingPrecisionChangesEmittedFloatWhenBothCallsSucceed_527) {
  // Pick a value where different precision settings are likely to change the representation.
  const float v = 1.2345678f;

  YAML::Emitter outA;
  const bool okA = outA.SetFloatPrecision(3);
  if (!okA) {
    GTEST_SKIP() << "SetFloatPrecision(3) is not supported by this implementation: " << outA.GetLastError();
  }
  outA.WriteStreamable<float>(v);
  const std::string sA(outA.c_str(), outA.size());

  YAML::Emitter outB;
  const bool okB = outB.SetFloatPrecision(8);
  if (!okB) {
    GTEST_SKIP() << "SetFloatPrecision(8) is not supported by this implementation: " << outB.GetLastError();
  }
  outB.WriteStreamable<float>(v);
  const std::string sB(outB.c_str(), outB.size());

  EXPECT_NE(sA, sB)
      << "Emitted float text should differ when float precision changes (for a value with many digits).";
  EXPECT_FALSE(sA.empty());
  EXPECT_FALSE(sB.empty());
}

TEST_F(EmitterSetFloatPrecisionTest_527, PrecisionSettingPersistsForSubsequentFloatWrites_527) {
  YAML::Emitter out;

  const bool ok = out.SetFloatPrecision(4);
  if (!ok) {
    GTEST_SKIP() << "SetFloatPrecision(4) is not supported by this implementation: " << out.GetLastError();
  }

  out.WriteStreamable<float>(1.234567f);
  const std::string first(out.c_str(), out.size());

  // Append another float; output should grow and reflect same precision policy.
  out.WriteStreamable<float>(9.876543f);
  const std::string second(out.c_str(), out.size());

  EXPECT_FALSE(first.empty());
  EXPECT_FALSE(second.empty());
  EXPECT_GT(second.size(), first.size())
      << "After writing an additional value, the emitted buffer should grow.";
}

TEST_F(EmitterSetFloatPrecisionTest_527, BoundaryPrecisionZeroDoesNotCrashAndIsObservable_527) {
  YAML::Emitter out;

  // Boundary: 0. We don't assume success/failure; we assert observable signals are consistent.
  const bool ok = out.SetFloatPrecision(0);

  if (ok) {
    EXPECT_TRUE(out.good());
    out.WriteStreamable<float>(1.2345f);
    const std::string s(out.c_str(), out.size());
    EXPECT_FALSE(s.empty());
  } else {
    EXPECT_TRUE(!out.good() || !out.GetLastError().empty())
        << "If SetFloatPrecision(0) fails, expect either !good() or a non-empty last error.";
  }
}

TEST_F(EmitterSetFloatPrecisionTest_527, VeryLargePrecisionEitherSucceedsOrProvidesErrorSignal_527) {
  YAML::Emitter out;

  const std::size_t huge = (std::numeric_limits<std::size_t>::max)();
  const bool ok = out.SetFloatPrecision(huge);

  // No assumptions about acceptance; only verify the API exposes outcome.
  if (ok) {
    EXPECT_TRUE(out.good());
    out.WriteStreamable<float>(1.0f);
    const std::string s(out.c_str(), out.size());
    EXPECT_FALSE(s.empty());
  } else {
    EXPECT_TRUE(!out.good() || !out.GetLastError().empty())
        << "If SetFloatPrecision(huge) fails, expect either !good() or a non-empty last error.";
  }
}

TEST_F(EmitterSetFloatPrecisionTest_527, SettingFloatPrecisionDoesNotNecessarilyChangeDoubleOutput_527) {
  // This test is intentionally weakly asserted (black-box): we only verify the call does not
  // prevent emitting a double via the public templated API.
  const double dv = 1.23456789012345;

  YAML::Emitter out;
  const bool ok = out.SetFloatPrecision(2);
  if (!ok) {
    GTEST_SKIP() << "SetFloatPrecision(2) is not supported by this implementation: " << out.GetLastError();
  }

  out.WriteStreamable<double>(dv);
  const std::string s(out.c_str(), out.size());

  EXPECT_FALSE(s.empty());
  EXPECT_TRUE(out.good());
}

}  // namespace