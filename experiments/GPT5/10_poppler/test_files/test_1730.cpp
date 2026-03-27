// CairoOutputDev_setPrinting_1730_test.cc

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

class CairoOutputDevTest_1730 : public ::testing::Test {
protected:
  CairoOutputDev dev;
};

TEST_F(CairoOutputDevTest_1730, SetPrintingAcceptsFalse_1730) {
  // Normal operation: callable with false.
  EXPECT_NO_THROW(dev.setPrinting(false));
}

TEST_F(CairoOutputDevTest_1730, SetPrintingAcceptsTrue_1730) {
  // Normal operation: callable with true.
  EXPECT_NO_THROW(dev.setPrinting(true));
}

TEST_F(CairoOutputDevTest_1730, SetPrintingIsCallableRepeatedly_1730) {
  // Boundary-ish: repeated toggling should remain safe/usable through the public interface.
  EXPECT_NO_THROW(dev.setPrinting(false));
  EXPECT_NO_THROW(dev.setPrinting(true));
  EXPECT_NO_THROW(dev.setPrinting(true));   // idempotent call
  EXPECT_NO_THROW(dev.setPrinting(false));
  EXPECT_NO_THROW(dev.setPrinting(false));  // idempotent call
}

TEST_F(CairoOutputDevTest_1730, SetPrintingDoesNotCrashOnRapidSequence_1730) {
  // Stress-ish: many calls; we only assert the operation is safe through the interface.
  EXPECT_NO_THROW({
    for (int i = 0; i < 1000; ++i) {
      dev.setPrinting((i % 2) == 0);
    }
  });
}