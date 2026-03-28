#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <string>

// We need access to the internal getKeyLong function.
// Since it's a static function in the .cpp file, we cannot directly call it from outside.
// However, we can declare it as extern or include the source. Since the function is static
// and in an anonymous/internal namespace, we need to work around this.
// 
// One approach: declare the function signature and link against it.
// But since it's static, it has internal linkage. We'll need to include the source file
// or use a different approach.
//
// For testing purposes, we'll re-declare the function or include the cpp file to get access.

// Include the implementation file to access the static function
// This is a common technique for testing static/internal functions
namespace Exiv2 {
namespace Internal {
static long getKeyLong(const std::string& key, const ExifData* metadata, int which);
}
}

// We need to include the actual implementation
#include "minoltamn_int.cpp"

namespace {

class GetKeyLongTest_1012 : public ::testing::Test {
protected:
    void SetUp() override {
        metadata_ = std::make_unique<Exiv2::ExifData>();
    }

    std::unique_ptr<Exiv2::ExifData> metadata_;
};

// Test: Key not found in metadata returns -1
TEST_F(GetKeyLongTest_1012, KeyNotFound_ReturnsNegativeOne_1012) {
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, -1);
}

// Test: Key found with integer value returns that value
TEST_F(GetKeyLongTest_1012, KeyFoundWithIntegerValue_ReturnsValue_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1024);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 1024);
}

// Test: Key found with zero value returns 0
TEST_F(GetKeyLongTest_1012, KeyFoundWithZeroValue_ReturnsZero_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(0);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 0);
}

// Test: Key found with value 1 returns 1
TEST_F(GetKeyLongTest_1012, KeyFoundWithValueOne_ReturnsOne_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 1);
}

// Test: Key found with large value
TEST_F(GetKeyLongTest_1012, KeyFoundWithLargeValue_ReturnsValue_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(65535);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 65535);
}

// Test: Empty metadata returns -1
TEST_F(GetKeyLongTest_1012, EmptyMetadata_ReturnsNegativeOne_1012) {
    EXPECT_TRUE(metadata_->empty());
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, -1);
}

// Test: Multiple keys in metadata, correct one is found
TEST_F(GetKeyLongTest_1012, MultipleKeys_CorrectKeyFound_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1024);
    (*metadata_)["Exif.Image.ImageLength"] = static_cast<uint32_t>(768);
    
    long widthResult = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    long heightResult = Exiv2::Internal::getKeyLong("Exif.Image.ImageLength", metadata_.get(), 0);
    
    EXPECT_EQ(widthResult, 1024);
    EXPECT_EQ(heightResult, 768);
}

// Test: Different 'which' parameter (component index)
TEST_F(GetKeyLongTest_1012, WhichParameterZero_ReturnsFirstComponent_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(2048);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 2048);
}

// Test: Key with signed integer value
TEST_F(GetKeyLongTest_1012, KeyFoundWithSignedValue_ReturnsValue_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<int32_t>(500);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 500);
}

// Test: Key with uint16_t value
TEST_F(GetKeyLongTest_1012, KeyFoundWithUint16Value_ReturnsValue_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint16_t>(256);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 256);
}

// Test: Key with int16_t value
TEST_F(GetKeyLongTest_1012, KeyFoundWithInt16Value_ReturnsValue_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<int16_t>(128);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 128);
}

// Test: Using a Rational value
TEST_F(GetKeyLongTest_1012, KeyFoundWithRationalValue_ReturnsTruncatedValue_1012) {
    (*metadata_)["Exif.Photo.FNumber"] = Exiv2::Rational(56, 10);
    long result = Exiv2::Internal::getKeyLong("Exif.Photo.FNumber", metadata_.get(), 0);
    // 56/10 = 5.6, truncated to long = 5
    EXPECT_EQ(result, 5);
}

// Test: Key not present among other keys returns -1
TEST_F(GetKeyLongTest_1012, KeyNotPresentAmongOthers_ReturnsNegativeOne_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint32_t>(1024);
    (*metadata_)["Exif.Image.ImageLength"] = static_cast<uint32_t>(768);
    
    long result = Exiv2::Internal::getKeyLong("Exif.Photo.ExposureTime", metadata_.get(), 0);
    EXPECT_EQ(result, -1);
}

// Test: Boundary - maximum uint16_t value
TEST_F(GetKeyLongTest_1012, BoundaryMaxUint16_ReturnsCorrectValue_1012) {
    (*metadata_)["Exif.Image.ImageWidth"] = static_cast<uint16_t>(65535);
    long result = Exiv2::Internal::getKeyLong("Exif.Image.ImageWidth", metadata_.get(), 0);
    EXPECT_EQ(result, 65535);
}

// Test: Rational that results in exact integer
TEST_F(GetKeyLongTest_1012, RationalExactInteger_ReturnsExactValue_1012) {
    (*metadata_)["Exif.Photo.FNumber"] = Exiv2::Rational(80, 10);
    long result = Exiv2::Internal::getKeyLong("Exif.Photo.FNumber", metadata_.get(), 0);
    EXPECT_EQ(result, 8);
}

}  // namespace
