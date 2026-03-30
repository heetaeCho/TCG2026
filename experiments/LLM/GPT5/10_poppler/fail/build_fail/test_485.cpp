// TEST_ID: 485
// File: gfxdevicencolorspace_getalt_test.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "GfxState.h"

// A minimal concrete GfxColorSpace for testing ownership/return semantics.
// We intentionally keep behavior trivial: tests only observe pointer identity via getAlt().
class DummyColorSpaceForGetAlt_485 final : public GfxColorSpace {
public:
  DummyColorSpaceForGetAlt_485() = default;
  ~DummyColorSpaceForGetAlt_485() override = default;

  // --- GfxColorSpace interface ---
  std::unique_ptr<GfxColorSpace> copy() const override {
    return std::make_unique<DummyColorSpaceForGetAlt_485>();
  }

  // Return a valid value without relying on internal enums; 0 is acceptable for an enum type.
  GfxColorSpaceMode getMode() const override {
    return static_cast<GfxColorSpaceMode>(0);
  }

  int getNComps() const override { return 1; }

  void getGray(const GfxColor * /*color*/, GfxGray *gray) override {
    if (gray) {
      *gray = 0;
    }
  }

  void getRGB(const GfxColor * /*color*/, GfxRGB *rgb) override {
    if (rgb) {
      rgb->r = 0;
      rgb->g = 0;
      rgb->b = 0;
    }
  }

  void getCMYK(const GfxColor * /*color*/, GfxCMYK *cmyk) override {
    if (cmyk) {
      cmyk->c = 0;
      cmyk->m = 0;
      cmyk->y = 0;
      cmyk->k = 0;
    }
  }

  void getDeviceN(const GfxColor * /*color*/, GfxColor * /*deviceN*/) override {
    // No-op (not needed for pointer-identity tests).
  }

  void getDefaultColor(GfxColor *color) override {
    if (!color) {
      return;
    }
    // Set first component to 0; if there are more components in the struct, we avoid assumptions.
    // This is purely to satisfy interface usage.
    color->c[0] = 0;
  }

  void createMapping(std::vector<std::unique_ptr<GfxSeparationColorSpace>> * /*separationList*/,
                     size_t /*maxSepComps*/) override {
    // No-op.
  }
};

class GfxDeviceNColorSpaceTest_485 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxDeviceNColorSpace> MakeDeviceNWithAlt(
      GfxColorSpace *&altRawOut) {
    // Provide a non-null alt color space so behavior is observable via pointer identity.
    auto alt = std::make_unique<DummyColorSpaceForGetAlt_485>();
    altRawOut = alt.get();

    // Use the constructor that takes rvalue names + alt + func + separation CS list.
    // Keep other dependencies minimal and observable only through public API.
    std::vector<std::string> names;
    names.emplace_back("C0");

    std::unique_ptr<Function> func; // nullptr
    std::vector<std::unique_ptr<GfxSeparationColorSpace>> seps; // empty

    return std::make_unique<GfxDeviceNColorSpace>(1, std::move(names), std::move(alt),
                                                  std::move(func), std::move(seps));
  }
};

TEST_F(GfxDeviceNColorSpaceTest_485, GetAltReturnsSamePointerProvidedAtConstruction_485) {
  GfxColorSpace *altRaw = nullptr;
  auto cs = MakeDeviceNWithAlt(altRaw);

  ASSERT_NE(altRaw, nullptr);
  EXPECT_EQ(cs->getAlt(), altRaw);
}

TEST_F(GfxDeviceNColorSpaceTest_485, GetAltIsStableAcrossMultipleCalls_485) {
  GfxColorSpace *altRaw = nullptr;
  auto cs = MakeDeviceNWithAlt(altRaw);

  ASSERT_NE(altRaw, nullptr);
  auto *p1 = cs->getAlt();
  auto *p2 = cs->getAlt();
  EXPECT_EQ(p1, altRaw);
  EXPECT_EQ(p2, altRaw);
  EXPECT_EQ(p1, p2);
}

TEST_F(GfxDeviceNColorSpaceTest_485, GetAltDoesNotChangeAfterUnrelatedCalls_485) {
  GfxColorSpace *altRaw = nullptr;
  auto cs = MakeDeviceNWithAlt(altRaw);

  ASSERT_NE(altRaw, nullptr);

  // Call other public methods (observable-only requirement: we don't inspect internals).
  EXPECT_EQ(cs->getNComps(), 1);

  GfxColor defaultColor;
  cs->getDefaultColor(&defaultColor);

  // Verify getAlt is unaffected.
  EXPECT_EQ(cs->getAlt(), altRaw);
}

TEST_F(GfxDeviceNColorSpaceTest_485, GetAltPointerMatchesCopyIndependently_485) {
  // This test verifies that getAlt() on a copied colorspace is still a valid pointer
  // (observable: non-null) and that original getAlt remains stable.
  // We do NOT assume whether copy shares or deep-copies the alt colorspace.
  GfxColorSpace *altRaw = nullptr;
  auto cs = MakeDeviceNWithAlt(altRaw);

  ASSERT_NE(altRaw, nullptr);
  EXPECT_EQ(cs->getAlt(), altRaw);

  auto copied = cs->copy();
  ASSERT_NE(copied, nullptr);

  // copy() returns a GfxColorSpace; ensure it can be downcasted to GfxDeviceNColorSpace
  // (if copy preserves dynamic type). If not, we still validate the original remains valid.
  auto *copiedDevN = dynamic_cast<GfxDeviceNColorSpace *>(copied.get());
  if (copiedDevN) {
    EXPECT_NE(copiedDevN->getAlt(), nullptr);
  }

  // Original remains unchanged.
  EXPECT_EQ(cs->getAlt(), altRaw);
}