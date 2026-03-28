//===----------------------------------------------------------------------===//
// Unit tests for CairoImageOutputDev (TEST_ID=1749)
//
// File: CairoImageOutputDev_test_1749.cc
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <climits>

#include "CairoOutputDev.h"

namespace {

// Simple callback used for setImageDrawDecideCbk() API smoke coverage.
struct CallbackData_1749 {
  int calls = 0;
  int last_id = INT_MIN;
};

static bool ImgDecideCbk_1749(int img_id, void *data)
{
  auto *d = static_cast<CallbackData_1749 *>(data);
  if (d) {
    d->calls++;
    d->last_id = img_id;
  }
  // Return value meaning is unknown; choose a deterministic value.
  return true;
}

class CairoImageOutputDevTest_1749 : public ::testing::Test {
protected:
  CairoImageOutputDev dev;
};

} // namespace

TEST_F(CairoImageOutputDevTest_1749, GetNumImagesIsNonNegative_1749)
{
  const int n = dev.getNumImages();
  EXPECT_GE(n, 0);
  // Const-correctness smoke (same object, repeated call).
  EXPECT_GE(dev.getNumImages(), 0);
}

TEST_F(CairoImageOutputDevTest_1749, GetNumImagesIsStableAcrossCalls_1749)
{
  const int n1 = dev.getNumImages();
  const int n2 = dev.getNumImages();
  const int n3 = dev.getNumImages();
  EXPECT_EQ(n1, n2);
  EXPECT_EQ(n2, n3);
}

TEST_F(CairoImageOutputDevTest_1749, GetImageInRangeIsStableIfAnyImagesExist_1749)
{
  const int n = dev.getNumImages();
  if (n <= 0) {
    GTEST_SKIP() << "No images available to test in-range getImage() stability.";
  }

  // For black-box safety: do not assume non-null, only stability.
  CairoImage *p1 = nullptr;
  CairoImage *p2 = nullptr;

  ASSERT_NO_FATAL_FAILURE(p1 = dev.getImage(0));
  ASSERT_NO_FATAL_FAILURE(p2 = dev.getImage(0));
  EXPECT_EQ(p1, p2);

  // Also check last valid index.
  CairoImage *q1 = nullptr;
  CairoImage *q2 = nullptr;
  const int last = n - 1;
  ASSERT_NO_FATAL_FAILURE(q1 = dev.getImage(last));
  ASSERT_NO_FATAL_FAILURE(q2 = dev.getImage(last));
  EXPECT_EQ(q1, q2);
}

TEST_F(CairoImageOutputDevTest_1749, GetImageOutOfRangeDoesNotCrash_1749)
{
  const int n = dev.getNumImages();

  // We don't assume return value semantics (nullptr vs something else),
  // only that the public API can be called safely.
  ASSERT_NO_FATAL_FAILURE((void)dev.getImage(-1));
  ASSERT_NO_FATAL_FAILURE((void)dev.getImage(n));
  ASSERT_NO_FATAL_FAILURE((void)dev.getImage(n + 1));
  ASSERT_NO_FATAL_FAILURE((void)dev.getImage(INT_MIN));
  ASSERT_NO_FATAL_FAILURE((void)dev.getImage(INT_MAX));
}

TEST_F(CairoImageOutputDevTest_1749, SetImageDrawDecideCbkAcceptsNullAndCanBeReset_1749)
{
  // Setting to null should be supported as a boundary case.
  ASSERT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(nullptr, nullptr));
  ASSERT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(nullptr, reinterpret_cast<void *>(0x1)));

  CallbackData_1749 data;
  ASSERT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(&ImgDecideCbk_1749, &data));

  // Reset back to null again (common lifecycle behavior).
  ASSERT_NO_FATAL_FAILURE(dev.setImageDrawDecideCbk(nullptr, nullptr));

  // We intentionally do not assert callback invocation here, because the interface
  // does not guarantee when/if it is used without exercising the rendering pipeline.
  SUCCEED();
}

TEST_F(CairoImageOutputDevTest_1749, BooleanCapabilityMethodsAreDeterministic_1749)
{
  // Black-box determinism checks: same input, same result across calls.
  const bool a1 = dev.upsideDown();
  const bool a2 = dev.upsideDown();
  EXPECT_EQ(a1, a2);

  const bool b1 = dev.useDrawChar();
  const bool b2 = dev.useDrawChar();
  EXPECT_EQ(b1, b2);

  const bool c1 = dev.useTilingPatternFill();
  const bool c2 = dev.useTilingPatternFill();
  EXPECT_EQ(c1, c2);

  const bool d1 = dev.useFillColorStop();
  const bool d2 = dev.useFillColorStop();
  EXPECT_EQ(d1, d2);

  const bool e1 = dev.interpretType3Chars();
  const bool e2 = dev.interpretType3Chars();
  EXPECT_EQ(e1, e2);

  const bool f1 = dev.needNonText();
  const bool f2 = dev.needNonText();
  EXPECT_EQ(f1, f2);
}

TEST_F(CairoImageOutputDevTest_1749, UseShadedFillsDeterministicForSameTypeAndHandlesBoundaries_1749)
{
  // Same argument should produce a stable result.
  EXPECT_EQ(dev.useShadedFills(0), dev.useShadedFills(0));
  EXPECT_EQ(dev.useShadedFills(1), dev.useShadedFills(1));
  EXPECT_EQ(dev.useShadedFills(-1), dev.useShadedFills(-1));

  // Boundary/int-extreme arguments should be callable.
  ASSERT_NO_FATAL_FAILURE((void)dev.useShadedFills(INT_MIN));
  ASSERT_NO_FATAL_FAILURE((void)dev.useShadedFills(INT_MAX));
}