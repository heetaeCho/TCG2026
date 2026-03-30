// TEST_ID: 535
//
// Unit tests for GfxImageColorMap::getDecodeHigh(int)
//
// Constraints followed:
// - Treat implementation as a black box (only observe via public API).
// - No access to private state.
// - Use only public constructors / methods.
// - Verify observable behavior via getDecodeLow/getDecodeHigh/isOk/copy.
// - No mocking needed (no external collaborators exposed by this interface).

#include <gtest/gtest.h>

#include <memory>
#include <vector>

// Poppler headers (paths may vary slightly by build; these are typical for poppler)
#include "GfxState.h"
#include "Object.h"

// -------------------------
// Small compatibility helpers
// -------------------------

namespace {

template <typename T>
Object makeNumberObject(T v) {
  Object o;
#if defined(POPPLER_HAS_CPP_NUMBER_OBJECT_CTORS)
  o = Object(v);
#else
  // Most poppler versions provide these init helpers.
  // Prefer double to cover both int/real decode values.
  o.initReal(static_cast<double>(v));
#endif
  return o;
}

Object makeDecodeArrayObject(const std::vector<double> &vals) {
  Object decode;

  // Different Poppler versions have different ways to create arrays.
  // We'll try a few common patterns via preprocessor checks when available,
  // otherwise use the most common initArray() + getArray() + add().
#if defined(POPPLER_OBJECT_INITARRAY_TAKES_XREF)
  decode.initArray(nullptr);
#else
  decode.initArray();
#endif

  Array *arr = decode.getArray();
  EXPECT_NE(arr, nullptr) << "Failed to create decode Array Object";

  for (double v : vals) {
    Object num = makeNumberObject(v);

#if defined(POPPLER_ARRAY_ADD_TAKES_RVALUE_OBJECT)
    arr->add(std::move(num));
#else
    arr->add(num);
#endif
  }

  return decode;
}

std::unique_ptr<GfxColorSpace> makeDeviceGrayCS() {
  // Many poppler versions expose these as concrete classes with trivial ctors.
  // If your version instead uses factories, adjust here accordingly.
  return std::make_unique<GfxDeviceGrayColorSpace>();
}

std::unique_ptr<GfxColorSpace> makeDeviceRGBCS() {
  return std::make_unique<GfxDeviceRGBColorSpace>();
}

} // namespace

// -------------------------
// Tests
// -------------------------

class GfxImageColorMapTest_535 : public ::testing::Test {
protected:
  // Helper to construct a map using the (bits, decode, unique_ptr<CS>) ctor.
  static std::unique_ptr<GfxImageColorMap> makeMap(
      int bits,
      Object *decode,
      std::unique_ptr<GfxColorSpace> &&cs) {
    return std::make_unique<GfxImageColorMap>(bits, decode, std::move(cs));
  }
};

TEST_F(GfxImageColorMapTest_535, Gray_DefaultDecodeHighIsOne_535) {
  // Decode array for Gray has 2 entries: [low, high]
  Object decode = makeDecodeArrayObject({0.0, 1.0});
  auto map = makeMap(8, &decode, makeDeviceGrayCS());

  ASSERT_NE(map, nullptr);
  EXPECT_TRUE(map->isOk());

  // Observable: getDecodeHigh(0) should match the "high" decode value.
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(0), 1.0);
  // And low should match.
  EXPECT_DOUBLE_EQ(map->getDecodeLow(0), 0.0);
}

TEST_F(GfxImageColorMapTest_535, Gray_CustomDecodeLowAndHighMatchInput_535) {
  Object decode = makeDecodeArrayObject({0.2, 0.8});
  auto map = makeMap(8, &decode, makeDeviceGrayCS());

  ASSERT_NE(map, nullptr);
  ASSERT_TRUE(map->isOk());

  EXPECT_DOUBLE_EQ(map->getDecodeLow(0), 0.2);
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(0), 0.8);
}

TEST_F(GfxImageColorMapTest_535, RGB_DecodeHighMatchesEachComponent_535) {
  // RGB decode array: [Rlow, Rhigh, Glow, Ghigh, Blow, Bhigh]
  Object decode = makeDecodeArrayObject({0.0, 0.5, 0.1, 0.9, -1.0, 2.0});
  auto map = makeMap(8, &decode, makeDeviceRGBCS());

  ASSERT_NE(map, nullptr);
  ASSERT_TRUE(map->isOk());
  ASSERT_EQ(map->getNumPixelComps(), 3);

  EXPECT_DOUBLE_EQ(map->getDecodeLow(0), 0.0);
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(0), 0.5);

  EXPECT_DOUBLE_EQ(map->getDecodeLow(1), 0.1);
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(1), 0.9);

  EXPECT_DOUBLE_EQ(map->getDecodeLow(2), -1.0);
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(2), 2.0);
}

TEST_F(GfxImageColorMapTest_535, DecodeHigh_LastComponentBoundary_RGB_535) {
  Object decode = makeDecodeArrayObject({-0.25, 0.25, 10.0, 20.0, 3.14, 6.28});
  auto map = makeMap(1, &decode, makeDeviceRGBCS());

  ASSERT_NE(map, nullptr);
  ASSERT_TRUE(map->isOk());

  const int last = map->getNumPixelComps() - 1;
  ASSERT_GE(last, 0);

  // Boundary: last valid index should be usable and stable.
  EXPECT_DOUBLE_EQ(map->getDecodeLow(last), 3.14);
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(last), 6.28);
}

TEST_F(GfxImageColorMapTest_535, Copy_PreservesDecodeLowAndHigh_535) {
  Object decode = makeDecodeArrayObject({0.3, 0.7});
  auto map = makeMap(8, &decode, makeDeviceGrayCS());

  ASSERT_NE(map, nullptr);
  ASSERT_TRUE(map->isOk());

  std::unique_ptr<GfxImageColorMap> copied(map->copy());
  ASSERT_NE(copied, nullptr);
  EXPECT_TRUE(copied->isOk());

  // Observable behavior: copied instance should report same decode values.
  EXPECT_DOUBLE_EQ(copied->getDecodeLow(0), map->getDecodeLow(0));
  EXPECT_DOUBLE_EQ(copied->getDecodeHigh(0), map->getDecodeHigh(0));
}

TEST_F(GfxImageColorMapTest_535, DecodeHigh_EqualsLowWhenHighEqualsLow_535) {
  // Boundary-ish numeric case: zero range (low == high)
  Object decode = makeDecodeArrayObject({0.42, 0.42});
  auto map = makeMap(8, &decode, makeDeviceGrayCS());

  ASSERT_NE(map, nullptr);
  ASSERT_TRUE(map->isOk());

  EXPECT_DOUBLE_EQ(map->getDecodeLow(0), 0.42);
  EXPECT_DOUBLE_EQ(map->getDecodeHigh(0), 0.42);
}