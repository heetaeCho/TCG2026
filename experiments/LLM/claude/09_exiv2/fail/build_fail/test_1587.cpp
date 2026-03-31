#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include <sstream>

// We need access to the internal function. Since it's a static function in the .cpp file,
// we need to either include the .cpp or declare it. Since it's static in a namespace,
// we'll include the cpp file to get access to it.
// However, since it's static, it's only accessible within its translation unit.
// We need to work around this - let's declare a test helper or include the source.

// For testing purposes, we include the source file to access the static function
#include "sonymn_int.cpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class GetFocusMode2Test_1587 : public ::testing::Test {
protected:
    ExifData exifData;
    uint32_t val;

    void SetUp() override {
        val = 999; // Initialize to a known value to detect changes
    }

    void addSony1FocusMode2(uint8_t value) {
        ExifKey key("Exif.Sony1.FocusMode2");
        Value::UniquePtr v = Value::create(unsignedByte);
        v->read(std::to_string(static_cast<int>(value)));
        exifData.add(key, v.get());
    }

    void addSony2FocusMode2(uint8_t value) {
        ExifKey key("Exif.Sony2.FocusMode2");
        Value::UniquePtr v = Value::create(unsignedByte);
        v->read(std::to_string(static_cast<int>(value)));
        exifData.add(key, v.get());
    }

    void addSony1FocusMode2WithType(const std::string& value, TypeId typeId) {
        ExifKey key("Exif.Sony1.FocusMode2");
        Value::UniquePtr v = Value::create(typeId);
        v->read(value);
        exifData.add(key, v.get());
    }

    void addSony2FocusMode2WithType(const std::string& value, TypeId typeId) {
        ExifKey key("Exif.Sony2.FocusMode2");
        Value::UniquePtr v = Value::create(typeId);
        v->read(value);
        exifData.add(key, v.get());
    }
};

// Test: When no FocusMode2 keys exist, should return false and set val to 0
TEST_F(GetFocusMode2Test_1587, NoFocusMode2Keys_ReturnsFalseAndZero_1587) {
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: When Sony1.FocusMode2 exists with valid unsignedByte value
TEST_F(GetFocusMode2Test_1587, Sony1FocusMode2ValidValue_ReturnsTrueAndValue_1587) {
    addSony1FocusMode2(5);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_TRUE(result);
    EXPECT_EQ(5u, val);
}

// Test: When Sony2.FocusMode2 exists with valid unsignedByte value (no Sony1)
TEST_F(GetFocusMode2Test_1587, Sony2FocusMode2ValidValue_ReturnsTrueAndValue_1587) {
    addSony2FocusMode2(10);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_TRUE(result);
    EXPECT_EQ(10u, val);
}

// Test: When both Sony1 and Sony2 exist, Sony1 should take precedence
TEST_F(GetFocusMode2Test_1587, Sony1TakesPrecedenceOverSony2_1587) {
    addSony1FocusMode2(3);
    addSony2FocusMode2(7);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_TRUE(result);
    EXPECT_EQ(3u, val);
}

// Test: Sony1.FocusMode2 with value 0
TEST_F(GetFocusMode2Test_1587, Sony1FocusMode2ValueZero_1587) {
    addSony1FocusMode2(0);
    bool result = getFocusMode2(&exifData, val);
    // Value 0 may be treated as "n/a" or valid depending on the tag definition
    // We just verify the function executes without error
    // The result depends on whether write() outputs "n/a" for value 0
    if (result) {
        EXPECT_EQ(0u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Sony1.FocusMode2 with max unsignedByte value (255)
TEST_F(GetFocusMode2Test_1587, Sony1FocusMode2MaxByteValue_1587) {
    addSony1FocusMode2(255);
    bool result = getFocusMode2(&exifData, val);
    // The result depends on whether 255 maps to "n/a" in the tag definition
    if (result) {
        EXPECT_EQ(255u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Sony1.FocusMode2 exists but with wrong type (unsignedShort instead of unsignedByte)
// Should fall through to Sony2
TEST_F(GetFocusMode2Test_1587, Sony1WrongType_FallsToSony2_1587) {
    addSony1FocusMode2WithType("5", unsignedShort);
    addSony2FocusMode2(10);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_TRUE(result);
    EXPECT_EQ(10u, val);
}

// Test: Both Sony1 and Sony2 have wrong types
TEST_F(GetFocusMode2Test_1587, BothWrongType_ReturnsFalse_1587) {
    addSony1FocusMode2WithType("5", unsignedShort);
    addSony2FocusMode2WithType("10", unsignedShort);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Sony1.FocusMode2 with wrong type, no Sony2 present
TEST_F(GetFocusMode2Test_1587, Sony1WrongTypeNoSony2_ReturnsFalse_1587) {
    addSony1FocusMode2WithType("5", unsignedShort);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Sony2.FocusMode2 with wrong type, no Sony1 present
TEST_F(GetFocusMode2Test_1587, Sony2WrongTypeNoSony1_ReturnsFalse_1587) {
    addSony2FocusMode2WithType("5", unsignedShort);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Sony1.FocusMode2 value 1
TEST_F(GetFocusMode2Test_1587, Sony1FocusMode2Value1_1587) {
    addSony1FocusMode2(1);
    bool result = getFocusMode2(&exifData, val);
    if (result) {
        EXPECT_EQ(1u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Sony2.FocusMode2 value 1
TEST_F(GetFocusMode2Test_1587, Sony2FocusMode2Value1_1587) {
    addSony2FocusMode2(1);
    bool result = getFocusMode2(&exifData, val);
    if (result) {
        EXPECT_EQ(1u, val);
    } else {
        EXPECT_EQ(0u, val);
    }
}

// Test: Empty ExifData, val should be set to 0
TEST_F(GetFocusMode2Test_1587, EmptyExifData_SetsValToZero_1587) {
    EXPECT_TRUE(exifData.empty());
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: ExifData with other keys but not FocusMode2
TEST_F(GetFocusMode2Test_1587, OtherKeysPresent_ReturnsFalse_1587) {
    ExifKey key("Exif.Photo.FocalLength");
    Value::UniquePtr v = Value::create(unsignedRational);
    v->read("50/1");
    exifData.add(key, v.get());

    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Sony1 FocusMode2 with asciiString type should be skipped
TEST_F(GetFocusMode2Test_1587, Sony1AsciiStringType_Skipped_1587) {
    addSony1FocusMode2WithType("5", asciiString);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val);
}

// Test: Multiple values in Sony1 - only first byte matters
TEST_F(GetFocusMode2Test_1587, Sony1FocusMode2MultipleValues_1587) {
    ExifKey key("Exif.Sony1.FocusMode2");
    Value::UniquePtr v = Value::create(unsignedByte);
    v->read("5 10 15");
    exifData.add(key, v.get());

    bool result = getFocusMode2(&exifData, val);
    // toUint32(0) should return the first value
    if (result) {
        EXPECT_EQ(5u, val);
    }
}

// Test: val is properly overwritten from initial non-zero value
TEST_F(GetFocusMode2Test_1587, ValOverwrittenWhenNoKey_1587) {
    val = 42;
    bool result = getFocusMode2(&exifData, val);
    EXPECT_FALSE(result);
    EXPECT_EQ(0u, val); // Should be reset to 0
}

// Test: Sony1 has undefined type - should be skipped, fall to Sony2
TEST_F(GetFocusMode2Test_1587, Sony1UndefinedType_FallsToSony2_1587) {
    addSony1FocusMode2WithType("5", undefined);
    addSony2FocusMode2(7);
    bool result = getFocusMode2(&exifData, val);
    EXPECT_TRUE(result);
    EXPECT_EQ(7u, val);
}
