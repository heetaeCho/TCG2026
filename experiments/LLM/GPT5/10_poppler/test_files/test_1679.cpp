// MarkedContentOutputDev_test_1679.cpp
#include <gtest/gtest.h>

#include "MarkedContentOutputDev.h"
#include "Object.h"
#include "OutputDev.h"

namespace {

class MarkedContentOutputDevTest_1679 : public ::testing::Test {
protected:
  // Helper to create a minimal Object usable for construction.
  static Object MakeMinimalStreamObject() {
    Object o;
    // Default-constructed Object in Poppler is typically a null object.
    // We don't depend on internal semantics beyond it being constructible/passable.
    return o;
  }
};

TEST_F(MarkedContentOutputDevTest_1679, NeedCharCountReturnsFalse_1679) {
  Object stmObj = MakeMinimalStreamObject();
  MarkedContentOutputDev dev(/*mcidA=*/0, stmObj);

  EXPECT_FALSE(dev.needCharCount());
}

TEST_F(MarkedContentOutputDevTest_1679, NeedCharCountStableAcrossRepeatedCalls_1679) {
  Object stmObj = MakeMinimalStreamObject();
  MarkedContentOutputDev dev(/*mcidA=*/1, stmObj);

  for (int i = 0; i < 10; ++i) {
    EXPECT_FALSE(dev.needCharCount()) << "Iteration " << i;
  }
}

TEST_F(MarkedContentOutputDevTest_1679, NeedCharCountViaBasePointerReturnsFalse_1679) {
  Object stmObj = MakeMinimalStreamObject();
  auto *dev = new MarkedContentOutputDev(/*mcidA=*/42, stmObj);

  OutputDev *base = dev; // verify virtual dispatch through OutputDev
  EXPECT_FALSE(base->needCharCount());

  delete dev;
}

TEST_F(MarkedContentOutputDevTest_1679, NeedCharCountWorksForDifferentMcidValues_1679) {
  Object stmObj = MakeMinimalStreamObject();

  MarkedContentOutputDev dev0(/*mcidA=*/0, stmObj);
  MarkedContentOutputDev devNeg(/*mcidA=*/-1, stmObj);
  MarkedContentOutputDev devLarge(/*mcidA=*/2147483647, stmObj);

  EXPECT_FALSE(dev0.needCharCount());
  EXPECT_FALSE(devNeg.needCharCount());
  EXPECT_FALSE(devLarge.needCharCount());
}

} // namespace