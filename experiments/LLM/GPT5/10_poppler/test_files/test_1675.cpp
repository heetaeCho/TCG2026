// MarkedContentOutputDev_test_1675.cpp

#include <gtest/gtest.h>

#include "MarkedContentOutputDev.h"
#include "OutputDev.h" // for base-class dispatch (if available)

// NOTE: Tests are written strictly against the provided public interface and
// observable behavior. No internal state is accessed.

class MarkedContentOutputDevTest_1675 : public ::testing::Test {
protected:
  MarkedContentOutputDev dev_;
};

TEST_F(MarkedContentOutputDevTest_1675, UpsideDownReturnsTrue_1675) {
  EXPECT_TRUE(dev_.upsideDown());
}

TEST_F(MarkedContentOutputDevTest_1675, UpsideDownIsStableAcrossMultipleCalls_1675) {
  EXPECT_TRUE(dev_.upsideDown());
  EXPECT_TRUE(dev_.upsideDown());
  EXPECT_TRUE(dev_.upsideDown());
}

TEST_F(MarkedContentOutputDevTest_1675, UpsideDownWorksViaBasePointerDispatch_1675) {
  OutputDev* base = &dev_;
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->upsideDown());
}