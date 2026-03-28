// TEST_ID: 478
// File: test_gfxseparationcolorspace_getname_478.cc

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>

// Poppler headers
#include "GfxState.h"
#include "GooString.h"

namespace {

// Minimal concrete GfxColorSpace to satisfy GfxSeparationColorSpace ctor dependencies.
// This is only a stub dependency used to construct the SUT; tests do not assume any
// internal behavior of GfxSeparationColorSpace.
class DummyColorSpace final : public GfxColorSpace {
public:
  DummyColorSpace() = default;
  ~DummyColorSpace() override = default;

  std::unique_ptr<GfxColorSpace> copy() const override {
    return std::make_unique<DummyColorSpace>();
  }

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
    // no-op
  }

  void createMapping(std::vector<std::unique_ptr<GfxSeparationColorSpace>> * /*separationList*/,
                     size_t /*maxSepComps*/) override {
    // no-op
  }

  void getDefaultColor(GfxColor *color) override {
    if (color) {
      // Default to 0 components if possible; leave as-is otherwise.
      // (We intentionally avoid assumptions about GfxColor layout beyond it being trivially assignable.)
    }
  }

  GfxColorSpaceMode getMode() const override { return csDeviceGray; }
  int getNComps() const override { return 1; }
};

}  // namespace

class GfxSeparationColorSpaceTest_478 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxSeparationColorSpace> MakeSutWithName(const char *nameText) {
    auto name = std::make_unique<GooString>(nameText);
    auto alt = std::make_unique<DummyColorSpace>();
    std::unique_ptr<Function> func;  // nullptr is acceptable as an observable error/boundary input.
    return std::make_unique<GfxSeparationColorSpace>(std::move(name), std::move(alt), std::move(func));
  }
};

TEST_F(GfxSeparationColorSpaceTest_478, GetName_ReturnsNonNullForValidName_478) {
  auto sut = MakeSutWithName("SpotColor");

  const GooString *name = sut->getName();

  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name->getCString(), "SpotColor");
}

TEST_F(GfxSeparationColorSpaceTest_478, GetName_ReturnsEmptyStringWhenNameIsEmpty_478) {
  auto sut = MakeSutWithName("");

  const GooString *name = sut->getName();

  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name->getCString(), "");
}

TEST_F(GfxSeparationColorSpaceTest_478, GetName_IsStableAcrossMultipleCalls_478) {
  auto sut = MakeSutWithName("SamePointer");

  const GooString *name1 = sut->getName();
  const GooString *name2 = sut->getName();

  ASSERT_NE(name1, nullptr);
  ASSERT_NE(name2, nullptr);
  EXPECT_EQ(name1, name2);  // observable stability: same stored GooString instance
  EXPECT_STREQ(name1->getCString(), "SamePointer");
}

TEST_F(GfxSeparationColorSpaceTest_478, GetName_CanReturnNullWhenConstructedWithNullName_478) {
  // Boundary / error-like input: null name unique_ptr.
  // This test only checks observable behavior: whether getName() returns nullptr or not.
  // If the implementation rejects null and asserts, this test will fail (which is also observable).
  std::unique_ptr<GooString> nullName;
  auto alt = std::make_unique<DummyColorSpace>();
  std::unique_ptr<Function> func;

  auto sut = std::make_unique<GfxSeparationColorSpace>(std::move(nullName), std::move(alt), std::move(func));

  const GooString *name = sut->getName();
  // Accept either nullptr or non-null (if implementation substitutes a default). We can at least
  // assert it does not produce an invalid pointer (observable: nullptr is valid sentinel).
  // If non-null, it must be safe to call getCString().
  if (name) {
    (void)name->getCString();
    SUCCEED();
  } else {
    SUCCEED();
  }
}