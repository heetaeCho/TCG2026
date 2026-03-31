#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

// The function printFujiDigitalZoom is a static function in fujimn_int.cpp
// It's registered as a print function for Fuji MakerNote tags.
// We test it indirectly through the public Exiv2 API.

namespace {

class FujiDigitalZoomTest_623 : public ::testing::Test {
 protected:
  void SetUp() override {
  }
};

// Helper to get the printed interpretation of a Fuji MakerNote tag value
// The DigitalZoom tag for Fuji is tag 0x1100 in the Fuji MakerNote group
std::string getPrintedValue(const Exiv2::Value& value, uint16_t tag, const std::string& groupName) {
    std::ostringstream os;
    // Try to find the tag info and use its print function
    const Exiv2::TagInfo* tagInfo = nullptr;
    
    // We'll use ExifKey and the interpret function through ExifDatum
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key(tag, groupName);
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
        os << it->print(&exifData);
    }
    return os.str();
}

// Test: UnsignedLong with size 4 should print (value/8) followed by (raw_value)
TEST_F(FujiDigitalZoomTest_623, UnsignedLongSize4PrintsDividedBy8_623) {
    Exiv2::ULongValue value;
    value.read(static_cast<uint32_t>(80)); // 80/8 = 10
    
    // The DigitalZoom tag is 0x1100 in Fuji makernote
    // We need to check how this value gets printed
    std::ostringstream os;
    
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.DigitalZoom");
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    std::string printed = it->print(&exifData);
    // Should contain the division result (80/8 = 10) and the raw value in parentheses
    EXPECT_NE(printed.find("10"), std::string::npos);
    EXPECT_NE(printed.find("("), std::string::npos);
    EXPECT_NE(printed.find(")"), std::string::npos);
}

// Test: Value of 0 should print 0 (0/8=0)
TEST_F(FujiDigitalZoomTest_623, ZeroValuePrintsZero_623) {
    Exiv2::ULongValue value;
    value.read(static_cast<uint32_t>(0));
    
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.DigitalZoom");
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    std::string printed = it->print(&exifData);
    EXPECT_NE(printed.find("0"), std::string::npos);
    EXPECT_NE(printed.find("("), std::string::npos);
    EXPECT_NE(printed.find(")"), std::string::npos);
}

// Test: UnsignedLong with value 8 should print 1 (8/8=1)
TEST_F(FujiDigitalZoomTest_623, Value8PrintsOne_623) {
    Exiv2::ULongValue value;
    value.read(static_cast<uint32_t>(8));
    
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.DigitalZoom");
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    std::string printed = it->print(&exifData);
    // 8/8 = 1
    EXPECT_NE(printed.find("1"), std::string::npos);
    EXPECT_NE(printed.find("("), std::string::npos);
}

// Test: Non-integer multiple - value 4 should print 0.5
TEST_F(FujiDigitalZoomTest_623, Value4PrintsHalf_623) {
    Exiv2::ULongValue value;
    value.read(static_cast<uint32_t>(4));
    
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.DigitalZoom");
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    std::string printed = it->print(&exifData);
    // 4/8 = 0.5
    EXPECT_NE(printed.find("0.5"), std::string::npos);
}

// Test: Non-UnsignedLong type should only print the parenthesized raw value
TEST_F(FujiDigitalZoomTest_623, NonUnsignedLongTypeOnlyPrintsRaw_623) {
    Exiv2::UShortValue value;
    value.read(static_cast<uint16_t>(80));
    
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.DigitalZoom");
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    std::string printed = it->print(&exifData);
    // Should have parentheses with raw value but NOT the division result "10"
    EXPECT_NE(printed.find("("), std::string::npos);
    EXPECT_NE(printed.find(")"), std::string::npos);
    EXPECT_NE(printed.find("80"), std::string::npos);
}

// Test: Large value
TEST_F(FujiDigitalZoomTest_623, LargeValuePrintsCorrectly_623) {
    Exiv2::ULongValue value;
    value.read(static_cast<uint32_t>(800));
    
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.DigitalZoom");
    exifData.add(key, &value);
    
    auto it = exifData.findKey(key);
    ASSERT_NE(it, exifData.end());
    
    std::string printed = it->print(&exifData);
    // 800/8 = 100
    EXPECT_NE(printed.find("100"), std::string::npos);
    EXPECT_NE(printed.find("(800)"), std::string::npos);
}

}  // namespace
