// File: CairoImageOutputDev_setImageDrawDecideCbk_1748_test.cc

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// NOTE:
// We treat CairoImageOutputDev as a black box. The only observable behaviors available
// through the public interface here are:
//  - Construction/destruction
//  - setImageDrawDecideCbk(...) being callable
//  - getNumImages()/getImage(i) being callable (as a sanity check that callback-setting
//    does not mutate externally visible image state by itself).

namespace {

class CairoImageOutputDevTest_1748 : public ::testing::Test {
protected:
  CairoImageOutputDevTest_1748() = default;
  ~CairoImageOutputDevTest_1748() override = default;
};

// Simple C-style callbacks to pass as function pointers.
bool DecideAlwaysTrue_1748(int /*img_id*/, void * /*data*/) { return true; }
bool DecideAlwaysFalse_1748(int /*img_id*/, void * /*data*/) { return false; }

TEST_F(CairoImageOutputDevTest_1748, SetCallbackAcceptsNullCallbackAndNullData_1748) {
  CairoImageOutputDev dev;

  // Should be safe to clear callback/data.
  dev.setImageDrawDecideCbk(nullptr, nullptr);

  // Sanity: callback setting alone should not change image count.
  EXPECT_GE(dev.getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1748, SetCallbackAcceptsNonNullCallbackWithNullData_1748) {
  CairoImageOutputDev dev;

  const int before = dev.getNumImages();
  dev.setImageDrawDecideCbk(&DecideAlwaysTrue_1748, nullptr);

  // Observable sanity: setting callback shouldn't itself create images.
  EXPECT_EQ(dev.getNumImages(), before);
}

TEST_F(CairoImageOutputDevTest_1748, SetCallbackAcceptsNullCallbackWithNonNullData_1748) {
  CairoImageOutputDev dev;

  const int before = dev.getNumImages();
  int userData = 123;
  dev.setImageDrawDecideCbk(nullptr, &userData);

  // Observable sanity: setting callback/data shouldn't itself create images.
  EXPECT_EQ(dev.getNumImages(), before);
}

TEST_F(CairoImageOutputDevTest_1748, SetCallbackCanBeReplacedMultipleTimes_1748) {
  CairoImageOutputDev dev;

  const int before = dev.getNumImages();

  int data1 = 1;
  int data2 = 2;

  dev.setImageDrawDecideCbk(&DecideAlwaysTrue_1748, &data1);
  dev.setImageDrawDecideCbk(&DecideAlwaysFalse_1748, &data2);
  dev.setImageDrawDecideCbk(nullptr, nullptr);  // clear again

  // Still should not change visible image count merely by swapping callbacks.
  EXPECT_EQ(dev.getNumImages(), before);
}

TEST_F(CairoImageOutputDevTest_1748, GetImageOutOfRangeReturnsNullOrSafeValue_1748) {
  CairoImageOutputDev dev;

  const int n = dev.getNumImages();
  ASSERT_GE(n, 0);

  // Boundary: querying an out-of-range index should be safe.
  // We don't assume what "safe" is beyond "does not crash"; if it returns nullptr,
  // that's an acceptable observable outcome.
  EXPECT_NO_FATAL_FAILURE({
    CairoImage *img = dev.getImage(n);  // out of range (valid last index would be n-1)
    (void)img;
  });

  // Also test a clearly invalid negative index if the API accepts int.
  EXPECT_NO_FATAL_FAILURE({
    CairoImage *img = dev.getImage(-1);
    (void)img;
  });
}

} // namespace