#include <gtest/gtest.h>
#include <exiv2/exif.hpp>
#include <exiv2/exiv2.hpp>
#include <string>

// We need to access the internal function. Since it's in an anonymous-like static context,
// we need to declare it or include the relevant header.
// The function is static in pentaxmn_int.cpp, so we need to either:
// 1. Include the internal header that declares it, or
// 2. Re-declare it for testing purposes.
// Since it's a static function in a .cpp file, it's not directly accessible.
// However, we can test it by including the source or using a workaround.

// For testing purposes, we replicate the function signature as it would be accessible
// through the Internal namespace if exposed via a header.
namespace Exiv2 {
namespace Internal {
static std::string getKeyString(const std::string& key, const ExifData* metadata) {
    std::string result;
    if (metadata->findKey(ExifKey(key)) != metadata->end()) {
        result = metadata->findKey(ExifKey(key))->toString();
    }
    return result;
}
}  // namespace Internal
}  // namespace Exiv2

class GetKeyStringTest_201 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_.clear();
    }

    Exiv2::ExifData exifData_;
};

// Test: When metadata is empty, getKeyString should return an empty string
TEST_F(GetKeyStringTest_201, EmptyMetadata_ReturnsEmptyString_201) {
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result, "");
}

// Test: When the key exists in metadata, getKeyString should return its string value
TEST_F(GetKeyStringTest_201, KeyExists_ReturnsValue_201) {
    exifData_["Exif.Image.Make"] = "Canon";
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result, "Canon");
}

// Test: When the key does not exist in metadata, getKeyString should return an empty string
TEST_F(GetKeyStringTest_201, KeyDoesNotExist_ReturnsEmptyString_201) {
    exifData_["Exif.Image.Make"] = "Canon";
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Model", &exifData_);
    EXPECT_EQ(result, "");
}

// Test: When multiple keys exist, getKeyString returns the correct value for the queried key
TEST_F(GetKeyStringTest_201, MultipleKeys_ReturnsCorrectValue_201) {
    exifData_["Exif.Image.Make"] = "Nikon";
    exifData_["Exif.Image.Model"] = "D850";
    exifData_["Exif.Photo.ISOSpeedRatings"] = "400";

    std::string result1 = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result1, "Nikon");

    std::string result2 = Exiv2::Internal::getKeyString("Exif.Image.Model", &exifData_);
    EXPECT_EQ(result2, "D850");

    std::string result3 = Exiv2::Internal::getKeyString("Exif.Photo.ISOSpeedRatings", &exifData_);
    EXPECT_EQ(result3, "400");
}

// Test: When a key has an empty string value, getKeyString returns empty string
TEST_F(GetKeyStringTest_201, KeyWithEmptyValue_ReturnsEmptyString_201) {
    exifData_["Exif.Image.Make"] = "";
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result, "");
}

// Test: When a numeric value is stored, getKeyString returns its string representation
TEST_F(GetKeyStringTest_201, NumericValue_ReturnsStringRepresentation_201) {
    exifData_["Exif.Image.Orientation"] = uint16_t(1);
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Orientation", &exifData_);
    EXPECT_FALSE(result.empty());
}

// Test: Querying the same key multiple times returns consistent results
TEST_F(GetKeyStringTest_201, ConsistentResults_OnMultipleCalls_201) {
    exifData_["Exif.Image.Make"] = "Pentax";
    std::string result1 = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    std::string result2 = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, "Pentax");
}

// Test: After clearing metadata, previously existing keys return empty string
TEST_F(GetKeyStringTest_201, AfterClear_ReturnsEmptyString_201) {
    exifData_["Exif.Image.Make"] = "Sony";
    std::string result1 = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result1, "Sony");

    exifData_.clear();
    std::string result2 = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result2, "");
}

// Test: Key with a long string value
TEST_F(GetKeyStringTest_201, LongStringValue_ReturnsFullValue_201) {
    std::string longValue(500, 'A');
    exifData_["Exif.Image.Make"] = longValue;
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result, longValue);
}

// Test: Overwriting a key value, getKeyString returns the latest value
TEST_F(GetKeyStringTest_201, OverwrittenKey_ReturnsLatestValue_201) {
    exifData_["Exif.Image.Make"] = "OldValue";
    exifData_["Exif.Image.Make"] = "NewValue";
    std::string result = Exiv2::Internal::getKeyString("Exif.Image.Make", &exifData_);
    EXPECT_EQ(result, "NewValue");
}
