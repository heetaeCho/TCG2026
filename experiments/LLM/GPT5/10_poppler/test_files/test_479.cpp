//===----------------------------------------------------------------------===//
// Unit tests for GfxSeparationColorSpace::getAlt()
// File: GfxSeparationColorSpace_getAlt_test.cpp
// TEST_ID: 479
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"
#include "goo/GooString.h"

// NOTE:
// We treat GfxSeparationColorSpace as a black box. These tests only validate
// observable behavior of getAlt() via the public interface.
// We provide minimal concrete test doubles for abstract dependencies.

namespace {

// A minimal concrete GfxColorSpace implementation for testing pointer plumbing.
// This is an external collaborator used only to satisfy construction and to
// provide a stable object address for getAlt() to return.
class DummyColorSpace final : public GfxColorSpace {
public:
  ~DummyColorSpace() override = default;

  // Provide minimal, do-nothing implementations required by the base interface.
  // (These should not be relied on by the tests; they just satisfy linkage.)
  const std::unique_ptr<GfxColorSpace> copy() override
  {
    return std::make_unique<DummyColorSpace>();
  }

  GfxColorSpaceMode getMode() const override { return csDeviceGray; }
  int getNComps() const override { return 1; }

  void getGray(const GfxColor *, GfxGray *) override {}
  void getRGB(const GfxColor *, GfxRGB *) override {}
  void getCMYK(const GfxColor *, GfxCMYK *) override {}
  void getDeviceN(const GfxColor *, GfxColor *) override {}

  void getDefaultColor(GfxColor *) override {}

  void createMapping(std::vector<GfxSeparationColorSpace *> *, size_t) override {}
  bool isNonMarking() const override { return false; }
};

std::unique_ptr<GfxSeparationColorSpace>
makeSep(std::unique_ptr<GfxColorSpace> alt)
{
  // Name and Function are not relevant to getAlt() behavior in these tests.
  auto name = std::make_unique<GooString>("TestSep");
  std::unique_ptr<Function> func; // nullptr
  return std::make_unique<GfxSeparationColorSpace>(std::move(name), std::move(alt), std::move(func));
}

class GfxSeparationColorSpaceTest_479 : public ::testing::Test {};

} // namespace

TEST_F(GfxSeparationColorSpaceTest_479, ReturnsExactAltPointer_479)
{
  auto alt = std::make_unique<DummyColorSpace>();
  GfxColorSpace *expected = alt.get();

  auto sep = makeSep(std::move(alt));
  ASSERT_NE(sep, nullptr);

  EXPECT_EQ(sep->getAlt(), expected);
}

TEST_F(GfxSeparationColorSpaceTest_479, RepeatedCallsReturnSamePointer_479)
{
  auto alt = std::make_unique<DummyColorSpace>();
  GfxColorSpace *expected = alt.get();

  auto sep = makeSep(std::move(alt));
  ASSERT_NE(sep, nullptr);

  GfxColorSpace *p1 = sep->getAlt();
  GfxColorSpace *p2 = sep->getAlt();
  GfxColorSpace *p3 = sep->getAlt();

  EXPECT_EQ(p1, expected);
  EXPECT_EQ(p2, expected);
  EXPECT_EQ(p3, expected);
}

TEST_F(GfxSeparationColorSpaceTest_479, ReturnsNullWhenAltIsNull_479)
{
  // Boundary condition: construct with a null alt colorspace.
  auto sep = makeSep(nullptr);
  ASSERT_NE(sep, nullptr);

  EXPECT_EQ(sep->getAlt(), nullptr);
}

TEST_F(GfxSeparationColorSpaceTest_479, GetAltDoesNotTransferOwnership_479)
{
  auto alt = std::make_unique<DummyColorSpace>();
  GfxColorSpace *expected = alt.get();

  auto sep = makeSep(std::move(alt));
  ASSERT_NE(sep, nullptr);

  // Observable behavior: calling getAlt() should not invalidate the stored alt pointer.
  (void)sep->getAlt();
  EXPECT_EQ(sep->getAlt(), expected);
}