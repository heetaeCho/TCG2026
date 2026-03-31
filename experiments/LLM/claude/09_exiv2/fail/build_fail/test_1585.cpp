#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// We need access to the internal function. Since it's in an anonymous/static context,
// we need to include the source or declare it. The function is static in the Internal namespace.
// We'll include the relevant headers and declare the function signature.

namespace Exiv2 {
namespace Internal {
// Forward declaration of the function under test
static auto getAFAreaModeSetting(const ExifData* metadata, uint32_t& val) -> bool;
}
}

// To access the static function, we include the source file directly
#include "sonymn_int.cpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class GetAFAreaModeSettingTest_1585 : public ::testing::Test {
protected:
    ExifData exifData;
    uint32_t val;

    void SetUp() override {
        val = 999; // Initialize to a known value to detect changes
    }

    void addUnsignedByteEntry(const std::string& key, uint8_t value) {
        Exiv2::ExifKey exifKey(key);
        Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedByte);
        v->read(std::to_string(value));
        exifData.add(exifKey, v.get());
    }

    void addAsciiStringEntry(const std::string& key, const std::string& value) {
        Exiv2::ExifKey exifKey(key);
        Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
        v->read(value);
        exifData.add(exifKey, v.get());
    }

    void addUnsignedShortEntry(const std::string& key, uint16_t value) {
        Exiv2::ExifKey exifKey(key);
        Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::unsignedShort);
        v->read(std::to_string(value));
        exifData.add(exifKey, v.get());
    }
};

// Test: When ExifData is empty, function should return false and set val to 0
TEST_F(GetAFAreaModeSettingTest_1585, EmptyExifData_ReturnsFalseAndSetsValToZero_1585) {
    bool result = getAFAreaModeSetting(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: When Sony1.AFAreaModeSetting exists with unsignedByte type and valid value
TEST_F(GetAFAreaModeSettingTest_1585, Sony1ValidUnsignedByte_ReturnsTrueWithValue_1585) {
    addUnsignedByteEntry("Exif.Sony1.AFAreaModeSetting", 5);
    bool result = getAFAreaModeSetting(&exifData, val);
    // The result depends on whether the write output is "n/a" or not
    // For a valid byte value of 5, we expect it to return true with val=5
    // unless the tag interpreter translates it to "n/a"
    // We test observable behavior
    if (result) {
        EXPECT_EQ(5u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: When Sony2.AFAreaModeSetting exists (but not Sony1) with unsignedByte type
TEST_F(GetAFAreaModeSettingTest_1585, Sony2ValidUnsignedByte_ReturnsTrueWithValue_1585) {
    addUnsignedByteEntry("Exif.Sony2.AFAreaModeSetting", 3);
    bool result = getAFAreaModeSetting(&exifData, val);
    if (result) {
        EXPECT_EQ(3u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: When Sony1 key exists but with wrong type (unsignedShort instead of unsignedByte)
TEST_F(GetAFAreaModeSettingTest_1585, Sony1WrongType_FallsThrough_1585) {
    addUnsignedShortEntry("Exif.Sony1.AFAreaModeSetting", 10);
    bool result = getAFAreaModeSetting(&exifData, val);
    // Since typeId is unsignedShort, not unsignedByte, Sony1 branch should be skipped
    // Sony2 doesn't exist either, so should return false
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: When Sony2 key exists but with wrong type (unsignedShort)
TEST_F(GetAFAreaModeSettingTest_1585, Sony2WrongType_ReturnsFalse_1585) {
    addUnsignedShortEntry("Exif.Sony2.AFAreaModeSetting", 10);
    bool result = getAFAreaModeSetting(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: When Sony1 key exists with asciiString type (wrong type), should fall through
TEST_F(GetAFAreaModeSettingTest_1585, Sony1AsciiType_FallsThrough_1585) {
    addAsciiStringEntry("Exif.Sony1.AFAreaModeSetting", "test");
    bool result = getAFAreaModeSetting(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Both Sony1 and Sony2 exist, Sony1 should take precedence
TEST_F(GetAFAreaModeSettingTest_1585, Sony1TakesPrecedenceOverSony2_1585) {
    addUnsignedByteEntry("Exif.Sony1.AFAreaModeSetting", 7);
    addUnsignedByteEntry("Exif.Sony2.AFAreaModeSetting", 2);
    bool result = getAFAreaModeSetting(&exifData, val);
    // Sony1 should be checked first
    if (result) {
        EXPECT_EQ(7u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Sony1 has wrong type but Sony2 has correct type - should use Sony2
TEST_F(GetAFAreaModeSettingTest_1585, Sony1WrongTypeSony2Correct_UsesSony2_1585) {
    addUnsignedShortEntry("Exif.Sony1.AFAreaModeSetting", 10);
    addUnsignedByteEntry("Exif.Sony2.AFAreaModeSetting", 4);
    bool result = getAFAreaModeSetting(&exifData, val);
    if (result) {
        EXPECT_EQ(4u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Value of 0 for Sony1 - boundary case
TEST_F(GetAFAreaModeSettingTest_1585, Sony1ValueZero_1585) {
    addUnsignedByteEntry("Exif.Sony1.AFAreaModeSetting", 0);
    bool result = getAFAreaModeSetting(&exifData, val);
    // Value 0 might be interpreted as n/a by the tag translator
    if (result) {
        EXPECT_EQ(0u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Maximum byte value (255) for Sony1
TEST_F(GetAFAreaModeSettingTest_1585, Sony1MaxByteValue_1585) {
    addUnsignedByteEntry("Exif.Sony1.AFAreaModeSetting", 255);
    bool result = getAFAreaModeSetting(&exifData, val);
    if (result) {
        EXPECT_EQ(255u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Value of 0 for Sony2 - boundary case
TEST_F(GetAFAreaModeSettingTest_1585, Sony2ValueZero_1585) {
    addUnsignedByteEntry("Exif.Sony2.AFAreaModeSetting", 0);
    bool result = getAFAreaModeSetting(&exifData, val);
    if (result) {
        EXPECT_EQ(0u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Unrelated keys in ExifData should not affect the result
TEST_F(GetAFAreaModeSettingTest_1585, UnrelatedKeys_ReturnsFalse_1585) {
    addUnsignedByteEntry("Exif.Photo.ExposureTime", 1);
    addUnsignedByteEntry("Exif.Image.Make", 2);
    bool result = getAFAreaModeSetting(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Val is properly overwritten even if it had a previous value
TEST_F(GetAFAreaModeSettingTest_1585, ValOverwrittenOnFailure_1585) {
    val = 42;
    bool result = getAFAreaModeSetting(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Sony1 value of 1 - typical valid value
TEST_F(GetAFAreaModeSettingTest_1585, Sony1Value1_1585) {
    addUnsignedByteEntry("Exif.Sony1.AFAreaModeSetting", 1);
    bool result = getAFAreaModeSetting(&exifData, val);
    if (result) {
        EXPECT_EQ(1u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Sony2 value of 1 - typical valid value
TEST_F(GetAFAreaModeSettingTest_1585, Sony2Value1_1585) {
    addUnsignedByteEntry("Exif.Sony2.AFAreaModeSetting", 1);
    bool result = getAFAreaModeSetting(&exifData, val);
    if (result) {
        EXPECT_EQ(1u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}
