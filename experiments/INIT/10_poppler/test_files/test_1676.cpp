// MarkedContentOutputDev_test_1676.cc
#include <gtest/gtest.h>

#include <climits>

#include "MarkedContentOutputDev.h"
#include "Object.h"      // Object
#include "OutputDev.h"   // OutputDev

namespace {

class MarkedContentOutputDevTest_1676 : public ::testing::Test {
protected:
  static Object MakeNullObject() {
    Object obj;
    obj.initNull();
    return obj;
  }
};

TEST_F(MarkedContentOutputDevTest_1676, UseDrawCharReturnsTrue_1676) {
  Object stmObj = MakeNullObject();
  MarkedContentOutputDev dev(0, stmObj);

  EXPECT_TRUE(dev.useDrawChar());
}

TEST_F(MarkedContentOutputDevTest_1676, UseDrawCharIsStableAcrossCalls_1676) {
  Object stmObj = MakeNullObject();
  MarkedContentOutputDev dev(0, stmObj);

  EXPECT_TRUE(dev.useDrawChar());
  EXPECT_TRUE(dev.useDrawChar());
  EXPECT_TRUE(dev.useDrawChar());
}

TEST_F(MarkedContentOutputDevTest_1676, UseDrawCharViaBasePointer_1676) {
  Object stmObj = MakeNullObject();
  MarkedContentOutputDev dev(0, stmObj);

  OutputDev *base = &dev;
  EXPECT_TRUE(base->useDrawChar());
}

TEST_F(MarkedContentOutputDevTest_1676, UseDrawCharForBoundaryMcidValues_1676) {
  Object stmObj1 = MakeNullObject();
  Object stmObj2 = MakeNullObject();
  Object stmObj3 = MakeNullObject();

  MarkedContentOutputDev devZero(0, stmObj1);
  MarkedContentOutputDev devNegative(-1, stmObj2);
  MarkedContentOutputDev devMax(INT_MAX, stmObj3);

  EXPECT_TRUE(devZero.useDrawChar());
  EXPECT_TRUE(devNegative.useDrawChar());
  EXPECT_TRUE(devMax.useDrawChar());
}

}  // namespace