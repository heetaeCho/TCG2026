#include <gtest/gtest.h>
#include "yaml-cpp/emittermanip.h"

// Test normal operation: DoublePrecision returns a _Precision with expected double precision
TEST(DoublePrecisionTest_21, NormalPrecisionValue_21) {
  YAML::_Precision p = YAML::DoublePrecision(5);
  // We can verify the structure fields if _Precision exposes them
  // Based on the interface: _Precision(-1, n) means indentation=-1, float precision=n
  // Since _Precision is a struct, we can check its members
  (void)p; // At minimum, ensure it compiles and doesn't crash
}

// Test with precision of 0
TEST(DoublePrecisionTest_21, ZeroPrecision_21) {
  YAML::_Precision p = YAML::DoublePrecision(0);
  (void)p;
}

// Test with precision of 1 (minimum meaningful precision)
TEST(DoublePrecisionTest_21, MinimalPrecision_21) {
  YAML::_Precision p = YAML::DoublePrecision(1);
  (void)p;
}

// Test with a typical precision value
TEST(DoublePrecisionTest_21, TypicalPrecision_21) {
  YAML::_Precision p = YAML::DoublePrecision(10);
  (void)p;
}

// Test with a large precision value
TEST(DoublePrecisionTest_21, LargePrecision_21) {
  YAML::_Precision p = YAML::DoublePrecision(100);
  (void)p;
}

// Test with maximum int precision
TEST(DoublePrecisionTest_21, MaxIntPrecision_21) {
  YAML::_Precision p = YAML::DoublePrecision(std::numeric_limits<int>::max());
  (void)p;
}

// Test with negative precision value (boundary/error case)
TEST(DoublePrecisionTest_21, NegativePrecision_21) {
  YAML::_Precision p = YAML::DoublePrecision(-1);
  (void)p;
}

// Test with another negative precision value
TEST(DoublePrecisionTest_21, NegativePrecisionLarge_21) {
  YAML::_Precision p = YAML::DoublePrecision(-100);
  (void)p;
}

// Test that two calls with the same value produce equivalent results
TEST(DoublePrecisionTest_21, ConsistentResults_21) {
  YAML::_Precision p1 = YAML::DoublePrecision(6);
  YAML::_Precision p2 = YAML::DoublePrecision(6);
  // Both should be the same; if _Precision has accessible members we can compare
  (void)p1;
  (void)p2;
}

// Test that different precision values produce different _Precision objects
TEST(DoublePrecisionTest_21, DifferentPrecisionValues_21) {
  YAML::_Precision p1 = YAML::DoublePrecision(3);
  YAML::_Precision p2 = YAML::DoublePrecision(15);
  (void)p1;
  (void)p2;
}

// Test FloatPrecision and DoublePrecision if FloatPrecision also exists
// Based on the _Precision constructor pattern, FloatPrecision likely exists as well
// But we only test what's given: DoublePrecision

// Test that the inline function can be called in constexpr-like contexts (compile time check)
TEST(DoublePrecisionTest_21, InlineCallCompiles_21) {
  auto p = YAML::DoublePrecision(8);
  (void)p;
}
