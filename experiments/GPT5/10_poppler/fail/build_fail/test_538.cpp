// TEST_ID: 538
// File: gfx_image_color_map_use_device_n_line_test_538.cpp

#include <gtest/gtest.h>

#include "poppler/GfxState.h"
#include "poppler/Object.h"

namespace {

// A controllable concrete GfxColorSpace used only as an external collaborator
// passed into GfxImageColorMap (black-box testing of GfxImageColorMap behavior).
class FakeColorSpace final : public GfxColorSpace {
public:
  explicit FakeColorSpace(bool useDeviceNLine) : useDeviceNLine_(useDeviceNLine) {}
  ~FakeColorSpace() override = default;

  // --- Required/commonly-pure virtuals in Poppler (provide safe stubs) ---
  std::unique_ptr<GfxColorSpace> copy() const override {
    return std::make_unique<FakeColorSpace>(useDeviceNLine_);
  }

  GfxColorSpaceMode getMode() const override {
    // Avoid coupling to specific enum constants.
    return static_cast<GfxColorSpaceMode>(0);
  }

  int getNComps() const override { return 1; }

  void getDefaultColor(GfxColor *color) const override {
    // Conservative default initialization without assuming layout.
    std::memset(color, 0, sizeof(*color));
  }

  // --- Behavior under test: ---
  bool useGetDeviceNLine() const override { return useDeviceNLine_; }

private:
  bool useDeviceNLine_;
};

class GfxImageColorMapTest_538 : public ::testing::Test {
protected:
  Object MakeNullDecodeObject() {
    Object decode;
    // Most Poppler builds provide initNull(); if not available, default Object
    // is still typically safe for "no decode" semantics.
#if defined(__cpp_if_consteval) || 1
    decode.initNull();
#endif
    return decode;
  }
};

} // namespace

TEST_F(GfxImageColorMapTest_538, UseDeviceNLineReturnsTrueWhenColorSpaceRequestsIt_538) {
  Object decode = MakeNullDecodeObject();
  auto cs = std::make_unique<FakeColorSpace>(true);

  GfxImageColorMap cm(/*bitsA=*/8, &decode, std::move(cs));

  EXPECT_TRUE(cm.useDeviceNLine());
}

TEST_F(GfxImageColorMapTest_538, UseDeviceNLineReturnsFalseWhenColorSpaceDoesNotRequestIt_538) {
  Object decode = MakeNullDecodeObject();
  auto cs = std::make_unique<FakeColorSpace>(false);

  GfxImageColorMap cm(/*bitsA=*/8, &decode, std::move(cs));

  EXPECT_FALSE(cm.useDeviceNLine());
}

TEST_F(GfxImageColorMapTest_538, UseDeviceNLineUnaffectedByBitsBoundaryLow_538) {
  Object decode = MakeNullDecodeObject();
  auto cs = std::make_unique<FakeColorSpace>(true);

  GfxImageColorMap cm(/*bitsA=*/1, &decode, std::move(cs));

  EXPECT_TRUE(cm.useDeviceNLine());
}

TEST_F(GfxImageColorMapTest_538, UseDeviceNLineUnaffectedByBitsBoundaryHigh_538) {
  Object decode = MakeNullDecodeObject();
  auto cs = std::make_unique<FakeColorSpace>(false);

  GfxImageColorMap cm(/*bitsA=*/16, &decode, std::move(cs));

  EXPECT_FALSE(cm.useDeviceNLine());
}