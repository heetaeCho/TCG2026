// File: ./TestProjects/yaml-cpp/test/emitter_set_double_precision_test_528.cpp

#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterSetDoublePrecisionTest_528 : public ::testing::Test {
 protected:
  static std::string DumpEmitter(const YAML::Emitter& e) {
    const char* p = e.c_str();
    if (!p) return std::string();
    return std::string(p, e.size());
  }
};

TEST_F(EmitterSetDoublePrecisionTest_528, CommonPrecisionsReturnTrue_528) {
  YAML::Emitter emitter;

  // "Normal operation": common precision values should be accepted.
  EXPECT_TRUE(emitter.SetDoublePrecision(1u));
  EXPECT_TRUE(emitter.good()) << emitter.GetLastError();

  EXPECT_TRUE(emitter.SetDoublePrecision(6u));
  EXPECT_TRUE(emitter.good()) << emitter.GetLastError();

  EXPECT_TRUE(emitter.SetDoublePrecision(15u));
  EXPECT_TRUE(emitter.good()) << emitter.GetLastError();
}

TEST_F(EmitterSetDoublePrecisionTest_528, ZeroPrecisionIsHandledGracefully_528) {
  YAML::Emitter emitter;

  bool ok1 = emitter.SetDoublePrecision(0u);
  bool ok2 = emitter.SetDoublePrecision(0u);

  // Boundary: calling with 0 should be deterministic and not destabilize the emitter.
  EXPECT_EQ(ok1, ok2);

  if (!ok1) {
    // If the API reports failure, it should be observable via either good() or GetLastError().
    EXPECT_TRUE(!emitter.good() || !emitter.GetLastError().empty());
  }
}

TEST_F(EmitterSetDoublePrecisionTest_528, VeryLargePrecisionDoesNotCrashAndReportsStatus_528) {
  YAML::Emitter emitter;

  const std::size_t huge = static_cast<std::size_t>(1000u);
  bool ok = emitter.SetDoublePrecision(huge);

  // Error/exceptional case (observable): if it fails, there should be some observable error state.
  if (!ok) {
    EXPECT_TRUE(!emitter.good() || !emitter.GetLastError().empty());
  }

  // Regardless of ok/fail, subsequent public calls should remain safe.
  // (We don't assert output semantics here—just that the interface remains usable.)
  (void)emitter.c_str();
  (void)emitter.size();
  (void)emitter.good();
  (void)emitter.GetLastError();
}

TEST_F(EmitterSetDoublePrecisionTest_528, DifferentPrecisionsCanChangeStreamedDoubleOutput_528) {
  // This test verifies observable behavior (output difference) without asserting a specific format.
  // We only assert if both SetDoublePrecision calls succeed.

  const double value = 1.234567890123456;  // chosen to have many significant digits

  YAML::Emitter low;
  YAML::Emitter high;

  const bool low_ok = low.SetDoublePrecision(2u);
  const bool high_ok = high.SetDoublePrecision(15u);

  if (!low_ok || !high_ok) {
    // If the environment/implementation rejects these settings, we can't test output difference.
    // Still verify failure is observable for whichever failed.
    if (!low_ok) {
      EXPECT_TRUE(!low.good() || !low.GetLastError().empty());
    }
    if (!high_ok) {
      EXPECT_TRUE(!high.good() || !high.GetLastError().empty());
    }
    GTEST_SKIP() << "SetDoublePrecision did not accept requested precisions; skipping output comparison.";
  }

  low.WriteStreamable(value);
  high.WriteStreamable(value);

  const std::string low_s = DumpEmitter(low);
  const std::string high_s = DumpEmitter(high);

  // With different precision settings, the emitted representations should be observably different.
  EXPECT_NE(low_s, high_s);

  // Basic consistency checks on public API:
  EXPECT_EQ(low_s.size(), low.size());
  EXPECT_EQ(high_s.size(), high.size());
}

TEST_F(EmitterSetDoublePrecisionTest_528, CallingSetDoublePrecisionRepeatedlyIsStable_528) {
  YAML::Emitter emitter;

  const std::size_t p = 10u;
  const bool a = emitter.SetDoublePrecision(p);
  const bool b = emitter.SetDoublePrecision(p);
  const bool c = emitter.SetDoublePrecision(p);

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);

  if (!a) {
    EXPECT_TRUE(!emitter.good() || !emitter.GetLastError().empty());
  }
}

}  // namespace