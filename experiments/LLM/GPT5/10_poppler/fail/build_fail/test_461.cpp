// -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// The TEST_ID is 461
//
// Unit tests for GfxICCBasedColorSpace::getAlt()
// File: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"

// A minimal concrete GfxColorSpace to use as the alt colorspace in tests.
// This is *not* re-implementing GfxICCBasedColorSpace internals; it is only a test double
// to satisfy the interface and observe lifetime behavior.
class DummyColorSpace_461 final : public GfxColorSpace {
public:
  static int dtorCount;

  DummyColorSpace_461() = default;
  DummyColorSpace_461(const DummyColorSpace_461 &) = default;
  DummyColorSpace_461 &operator=(const DummyColorSpace_461 &) = default;

  ~DummyColorSpace_461() override { ++dtorCount; }

  const std::unique_ptr<GfxColorSpace> copy() override
  {
    return std::make_unique<DummyColorSpace_461>(*this);
  }

  void getGray(const GfxColor * /*color*/, GfxGray * /*gray*/) override { }
  void getRGB(const GfxColor * /*color*/, GfxRGB * /*rgb*/) override { }
  void getCMYK(const GfxColor * /*color*/, GfxCMYK * /*cmyk*/) override { }
  void getDeviceN(const GfxColor * /*color*/, GfxColor * /*deviceN*/) override { }

  void getRGBLine(unsigned char * /*in*/, unsigned int * /*out*/, int /*length*/) override { }
  void getRGBLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override { }
  void getRGBXLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override { }
  void getCMYKLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override { }
  void getDeviceNLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override { }

  bool useGetRGBLine() override { return false; }
  bool useGetCMYKLine() override { return false; }
  bool useGetDeviceNLine() override { return false; }

  void getDefaultColor(GfxColor * /*color*/) override { }
  void getDefaultRanges(double * /*decodeLow*/, double * /*decodeRange*/, int /*maxImgPixel*/) override { }

  GfxColorSpaceMode getMode() const override
  {
    // Return a valid enum value if 0 is not meaningful in your build; tests do not depend on it.
    return static_cast<GfxColorSpaceMode>(0);
  }

  int getNComps() const override { return 0; }
};

int DummyColorSpace_461::dtorCount = 0;

class GfxICCBasedColorSpaceTest_461 : public ::testing::Test {
protected:
  void SetUp() override { DummyColorSpace_461::dtorCount = 0; }
};

// Normal operation: getAlt() returns the same pointer as was provided via the unique_ptr constructor.
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltReturnsProvidedAltPointer_461)
{
  auto alt = std::make_unique<DummyColorSpace_461>();
  GfxColorSpace *expected = alt.get();

  // iccProfileStream pointer is not used by these tests; nullptr should be acceptable per signature.
  GfxICCBasedColorSpace cs(/*nCompsA=*/3, std::move(alt), /*iccProfileStreamA=*/nullptr);

  EXPECT_EQ(cs.getAlt(), expected);
  EXPECT_NE(cs.getAlt(), nullptr);
}

// Boundary: alt passed as nullptr should yield nullptr from getAlt().
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltReturnsNullWhenAltIsNull_461)
{
  std::unique_ptr<GfxColorSpace> alt; // null

  GfxICCBasedColorSpace cs(/*nCompsA=*/1, std::move(alt), /*iccProfileStreamA=*/nullptr);

  EXPECT_EQ(cs.getAlt(), nullptr);
}

// Boundary/consistency: repeated calls return the same pointer value.
TEST_F(GfxICCBasedColorSpaceTest_461, GetAltIsStableAcrossMultipleCalls_461)
{
  auto alt = std::make_unique<DummyColorSpace_461>();
  GfxColorSpace *expected = alt.get();

  GfxICCBasedColorSpace cs(/*nCompsA=*/4, std::move(alt), /*iccProfileStreamA=*/nullptr);

  GfxColorSpace *p1 = cs.getAlt();
  GfxColorSpace *p2 = cs.getAlt();
  GfxColorSpace *p3 = cs.getAlt();

  EXPECT_EQ(p1, expected);
  EXPECT_EQ(p2, expected);
  EXPECT_EQ(p3, expected);
}

// Observable lifetime behavior: providing an alt colorspace transfers ownership into GfxICCBasedColorSpace;
// the alt object should be destroyed when GfxICCBasedColorSpace is destroyed (observable via Dummy dtor count).
TEST_F(GfxICCBasedColorSpaceTest_461, AltIsDestroyedWhenOwnerIsDestroyed_461)
{
  EXPECT_EQ(DummyColorSpace_461::dtorCount, 0);

  {
    auto alt = std::make_unique<DummyColorSpace_461>();
    EXPECT_EQ(DummyColorSpace_461::dtorCount, 0);

    GfxICCBasedColorSpace cs(/*nCompsA=*/3, std::move(alt), /*iccProfileStreamA=*/nullptr);
    EXPECT_NE(cs.getAlt(), nullptr);

    // Alt should not be destroyed while cs is alive.
    EXPECT_EQ(DummyColorSpace_461::dtorCount, 0);
  }

  // After cs is destroyed, the owned alt should have been destroyed exactly once.
  EXPECT_EQ(DummyColorSpace_461::dtorCount, 1);
}