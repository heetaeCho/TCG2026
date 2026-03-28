#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "makernote_int.hpp"
#include "tiffimage_int.hpp"
#include "exiv2/exiv2.hpp"

#include <cstring>

namespace {

// Helper to create a TiffComponent tree that has an Exif.Image.Model tag
// with the given model string, so getExifModel(pRoot) returns it.
class TiffRootWithModel {
 public:
  explicit TiffRootWithModel(const std::string& model) {
    // Build a minimal Exif image in memory with the given Model tag
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Model"] = model;

    // Create an image in memory and set exif data
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv);
    image->setExifData(exifData);
    image->writeMetadata();

    // Re-read via TiffParser to build TiffComponent tree
    Exiv2::DataBuf buf = image->io().read(image->io().size());
    image->io().seek(0, Exiv2::BasicIo::beg);

    // We'll use a simpler approach: create a TiffDirectory manually
    // Actually, for the purpose of this test, we need a pRoot that 
    // getExifModel can extract the model from.
    
    // The simplest approach: build a real TIFF tree from an image buffer
    image_ = std::move(image);
  }

  // We can't easily get a TiffComponent* from a standard Exiv2 image.
  // So we take an alternative approach: test with nullptr which should
  // give us an empty model string.
  Exiv2::Image::UniquePtr image_;
};

}  // namespace

using namespace Exiv2::Internal;

// Test with nullptr pRoot - getExifModel should return empty string,
// which doesn't start with any of the prefixes, so should return 0
TEST(Sony2FpSelectorTest_1540, NullRootReturnsZero_1540) {
  int result = sony2FpSelector(0, nullptr, 0, nullptr);
  EXPECT_EQ(result, 0);
}

// Test with nullptr pRoot and various tag values - tag is unused
TEST(Sony2FpSelectorTest_1540, DifferentTagValuesWithNullRoot_1540) {
  EXPECT_EQ(sony2FpSelector(0x0000, nullptr, 0, nullptr), 0);
  EXPECT_EQ(sony2FpSelector(0xFFFF, nullptr, 0, nullptr), 0);
  EXPECT_EQ(sony2FpSelector(0x1234, nullptr, 0, nullptr), 0);
}

// Test with nullptr pRoot and non-null pData - pData is unused
TEST(Sony2FpSelectorTest_1540, NonNullDataWithNullRoot_1540) {
  const Exiv2::byte data[] = {0x01, 0x02, 0x03};
  int result = sony2FpSelector(0, data, sizeof(data), nullptr);
  EXPECT_EQ(result, 0);
}

// Test with nullptr pRoot and various sizes - size is unused
TEST(Sony2FpSelectorTest_1540, DifferentSizesWithNullRoot_1540) {
  EXPECT_EQ(sony2FpSelector(0, nullptr, 0, nullptr), 0);
  EXPECT_EQ(sony2FpSelector(0, nullptr, 100, nullptr), 0);
  EXPECT_EQ(sony2FpSelector(0, nullptr, SIZE_MAX, nullptr), 0);
}

// Verify that the return value is either 0 or -1 (the only documented values)
TEST(Sony2FpSelectorTest_1540, ReturnValueIsZeroOrMinusOne_1540) {
  int result = sony2FpSelector(0, nullptr, 0, nullptr);
  EXPECT_TRUE(result == 0 || result == -1);
}

// Test consistency - calling multiple times with same args gives same result
TEST(Sony2FpSelectorTest_1540, ConsistentResults_1540) {
  int result1 = sony2FpSelector(42, nullptr, 10, nullptr);
  int result2 = sony2FpSelector(42, nullptr, 10, nullptr);
  EXPECT_EQ(result1, result2);
}

// Test that all three unused parameters truly don't affect the result when pRoot is null
TEST(Sony2FpSelectorTest_1540, UnusedParamsDontAffectResultNullRoot_1540) {
  const Exiv2::byte data1[] = {0xFF};
  const Exiv2::byte data2[] = {0x00, 0x01, 0x02, 0x03, 0x04};
  
  int r1 = sony2FpSelector(0, nullptr, 0, nullptr);
  int r2 = sony2FpSelector(100, data1, 1, nullptr);
  int r3 = sony2FpSelector(65535, data2, 5, nullptr);
  
  // All should return the same since pRoot is nullptr in all cases
  EXPECT_EQ(r1, r2);
  EXPECT_EQ(r2, r3);
}

// Boundary: tag = 0
TEST(Sony2FpSelectorTest_1540, TagZero_1540) {
  int result = sony2FpSelector(0, nullptr, 0, nullptr);
  EXPECT_EQ(result, 0);
}

// Boundary: tag = max uint16
TEST(Sony2FpSelectorTest_1540, TagMaxUint16_1540) {
  int result = sony2FpSelector(UINT16_MAX, nullptr, 0, nullptr);
  EXPECT_EQ(result, 0);
}
