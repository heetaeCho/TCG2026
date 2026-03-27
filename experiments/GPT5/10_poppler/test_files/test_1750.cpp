//===----------------------------------------------------------------------===//
// CairoImageOutputDev_getImage_getNumImages_tests_1750.cc
// Unit tests for CairoImageOutputDev public interface (black-box).
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

namespace {

class CairoImageOutputDevTest_1750 : public ::testing::Test {
protected:
  CairoImageOutputDevTest_1750() = default;
  ~CairoImageOutputDevTest_1750() override = default;
};

// A simple callback function to pass into setImageDrawDecideCbk.
// (Not a mock: signature is a plain C function pointer.)
static bool AlwaysTrueCbk_1750(int /*img_id*/, void * /*data*/) { return true; }
static bool AlwaysFalseCbk_1750(int /*img_id*/, void * /*data*/) { return false; }

TEST_F(CairoImageOutputDevTest_1750, DefaultNumImagesIsNonNegative_1750) {
  CairoImageOutputDev dev;
  const int n = dev.getNumImages();
  EXPECT_GE(n, 0);
}

TEST_F(CairoImageOutputDevTest_1750, DefaultNumImagesIsStableAcrossRepeatedCalls_1750) {
  CairoImageOutputDev dev;

  const int n1 = dev.getNumImages();
  const int n2 = dev.getNumImages();
  const int n3 = dev.getNumImages();

  EXPECT_EQ(n1, n2);
  EXPECT_EQ(n2, n3);
  EXPECT_GE(n1, 0);
}

TEST_F(CairoImageOutputDevTest_1750, SetImageDrawDecideCbkAcceptsNullptrs_1750) {
  CairoImageOutputDev dev;

  const int before = dev.getNumImages();

  // Boundary / error-ish input: nullptr callback and nullptr data.
  EXPECT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(nullptr, nullptr));

  // Observable behavior: should not corrupt the externally visible count.
  const int after = dev.getNumImages();
  EXPECT_EQ(before, after);
  EXPECT_GE(after, 0);
}

TEST_F(CairoImageOutputDevTest_1750, SetImageDrawDecideCbkCanBeReplacedMultipleTimes_1750) {
  CairoImageOutputDev dev;

  const int before = dev.getNumImages();

  // Boundary: set multiple times with different callbacks and data pointers.
  int dummy1 = 1;
  int dummy2 = 2;

  EXPECT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(&AlwaysTrueCbk_1750, &dummy1));
  EXPECT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(&AlwaysFalseCbk_1750, &dummy2));
  EXPECT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(nullptr, &dummy1));
  EXPECT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(&AlwaysTrueCbk_1750, nullptr));

  // Observable behavior: count remains well-defined and unchanged by callback wiring alone.
  const int after = dev.getNumImages();
  EXPECT_EQ(before, after);
  EXPECT_GE(after, 0);
}

} // namespace