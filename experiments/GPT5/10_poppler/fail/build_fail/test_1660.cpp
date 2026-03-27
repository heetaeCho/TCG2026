// PreScanOutputDev_isMonochrome_1660_test.cc
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>
#include <vector>

// Poppler headers
#include "PSOutputDev.h"       // for PSLevel
#include "PreScanOutputDev.h"  // class under test

class PreScanOutputDevTest_1660 : public ::testing::Test {};

// Compile-time/interface test: return type and const-qualification are part of observable API.
TEST_F(PreScanOutputDevTest_1660, IsMonochromeIsConstAndReturnsBool_1660) {
  static_assert(
      std::is_same_v<decltype(std::declval<const PreScanOutputDev&>().isMonochrome()), bool>,
      "PreScanOutputDev::isMonochrome() must be callable on const and return bool");
}

// Normal operation: object can be constructed and queried; repeated queries are stable for the same object.
TEST_F(PreScanOutputDevTest_1660, IsMonochromeRepeatedCallsAreStable_1660) {
  PreScanOutputDev dev(static_cast<PSLevel>(0));

  const bool first = dev.isMonochrome();
  const bool second = dev.isMonochrome();

  EXPECT_EQ(first, second);
}

// Boundary/variation: constructing with several PSLevel values should allow querying without throwing,
// and results should be stable per-instance.
TEST_F(PreScanOutputDevTest_1660, IsMonochromeAcrossSeveralLevelsDoesNotThrowAndIsStablePerInstance_1660) {
  const std::vector<int> levels = {0, 1, 2, 3};

  for (int lvl : levels) {
    PreScanOutputDev dev(static_cast<PSLevel>(lvl));
    EXPECT_NO_THROW({
      const bool a = dev.isMonochrome();
      const bool b = dev.isMonochrome();
      EXPECT_EQ(a, b);
    });
  }
}

// Exceptional/error-ish inputs (if representable): even atypical PSLevel values should not break querying.
// This does not assume any specific true/false outcome.
TEST_F(PreScanOutputDevTest_1660, IsMonochromeWithOutOfRangeLevelValuesCanBeQueried_1660) {
  const std::vector<int> levels = {-1, 999, 0x7fffffff};

  for (int lvl : levels) {
    EXPECT_NO_THROW({
      PreScanOutputDev dev(static_cast<PSLevel>(lvl));
      (void)dev.isMonochrome();
    });
  }
}