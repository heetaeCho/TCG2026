// TEST_ID: 530
//
// Unit tests for GfxImageColorMap::isOk()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include "GfxState.h"
#include "Object.h"

#include <memory>
#include <utility>

namespace {

class GfxImageColorMapTest_530 : public ::testing::Test {
protected:
  // Creates a color map using the (int bitsA, Object* decode, int&& colorSpaceA) ctor.
  // We intentionally avoid asserting semantics of colorSpaceA values; tests focus on observable behavior.
  static std::unique_ptr<GfxImageColorMap> MakeWithIntColorSpace(int bits, Object *decode, int colorSpaceId) {
    int cs = colorSpaceId;
    return std::make_unique<GfxImageColorMap>(bits, decode, std::move(cs));
  }

  static Object MakeNullObject() {
    // Poppler's Object supports constructing a null object via objNull in most versions.
    // If your tree differs, adjust this helper (tests themselves remain black-box).
    return Object(objNull);
  }
};

} // namespace

TEST_F(GfxImageColorMapTest_530, IsOk_IsConstAndStableAcrossCalls_530) {
  Object decode = MakeNullObject();
  auto cm = MakeWithIntColorSpace(/*bits=*/8, &decode, /*colorSpaceId=*/0);
  ASSERT_NE(cm, nullptr);

  const bool first = cm->isOk();
  // Stability: repeated calls should not change the observable result.
  EXPECT_EQ(first, cm->isOk());
  EXPECT_EQ(first, cm->isOk());
}

TEST_F(GfxImage