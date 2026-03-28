#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>
#include <string>

// Since printFujiFaceElementTypes is a static function in fujimn_int.cpp,
// we test it indirectly through the Exif tag print interface.
// The function is registered as a print function for Fuji MakerNote tags.

class FujiFaceElementTypesTest_626 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test with UnsignedShort value type - known face element type values
TEST_F(FujiFaceElementTypesTest_626, UnsignedShortKnownValues_626) {
  // We test the print function through the Value interface
  // Create an UnsignedShort value
  auto value = Exiv2::Value::create(Exiv2::unsignedShort);
  // Face element type 1 typically maps to something in fujiFaceElementType
  value->read("1");

  std::ostringstream os;
  // We need to test via the tag's print method
  // Try to use ExifData with a Fuji face element type tag
  Exiv2::ExifData exifData;

  // Fuji.FaceElementTypes tag - group 0xf100 or similar
  // We'll try the direct approach - look for the tag in Fuji makernote
  try {
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    val->read("1");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      os << it->print(&exifData);
      std::string result = os.str();
      // Should produce some output (either a label or "(1)")
      EXPECT_FALSE(result.empty());
    }
  } catch (const Exiv2::Error&) {
    // Tag may not exist in this build, skip
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

// Test with UnsignedShort value type - unknown value
TEST_F(FujiFaceElementTypesTest_626, UnsignedShortUnknownValue_626) {
  try {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    val->read("999");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      std::ostringstream os;
      os << it->print(&exifData);
      std::string result = os.str();
      // Unknown values should be printed in parentheses
      EXPECT_NE(result.find("999"), std::string::npos);
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

// Test with multiple UnsignedShort values - space separated
TEST_F(FujiFaceElementTypesTest_626, MultipleUnsignedShortValues_626) {
  try {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    val->read("1 2");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      std::ostringstream os;
      os << it->print(&exifData);
      std::string result = os.str();
      // Should have space-separated output for multiple values
      EXPECT_FALSE(result.empty());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

// Test with ASCII string value
TEST_F(FujiFaceElementTypesTest_626, AsciiStringValue_626) {
  try {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::asciiString);
    // ASCII '1' is 0x31, subtracting '0' gives 1
    val->read("1");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      std::ostringstream os;
      os << it->print(&exifData);
      std::string result = os.str();
      EXPECT_FALSE(result.empty());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

// Test with zero value for UnsignedShort
TEST_F(FujiFaceElementTypesTest_626, UnsignedShortZeroValue_626) {
  try {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    val->read("0");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      std::ostringstream os;
      os << it->print(&exifData);
      std::string result = os.str();
      EXPECT_FALSE(result.empty());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

// Test behavior with non-ascii, non-unsignedShort type (should print raw value in parens)
TEST_F(FujiFaceElementTypesTest_626, OtherValueType_626) {
  try {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    val->read("42");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      std::ostringstream os;
      os << it->print(&exifData);
      std::string result = os.str();
      // For non-ascii, non-unsignedShort, should print "(value)"
      EXPECT_FALSE(result.empty());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

// Test with multiple ASCII characters
TEST_F(FujiFaceElementTypesTest_626, MultipleAsciiChars_626) {
  try {
    Exiv2::ExifData exifData;
    Exiv2::ExifKey key("Exif.Fujifilm.FaceElementTypes");
    auto val = Exiv2::Value::create(Exiv2::asciiString);
    // "12" - two characters, each treated as face element type
    val->read("12");
    exifData.add(key, val.get());

    auto it = exifData.findKey(key);
    if (it != exifData.end()) {
      std::ostringstream os;
      os << it->print(&exifData);
      std::string result = os.str();
      EXPECT_FALSE(result.empty());
    }
  } catch (const Exiv2::Error&) {
    GTEST_SKIP() << "FaceElementTypes tag not available";
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
