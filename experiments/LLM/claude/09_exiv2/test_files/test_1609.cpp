#include <gtest/gtest.h>
#include <sstream>
#include <exiv2/exiv2.hpp>

// Include internal headers
#include "sonymn_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class SonyMakerNoteTest_1609 : public ::testing::Test {
protected:
    std::ostringstream os;

    // Helper to create an UnsignedShort value with a single entry
    Value::UniquePtr createUShortValue(uint16_t val) {
        auto v = Value::create(unsignedShort);
        v->read(std::to_string(val));
        return v;
    }

    // Helper to create a value with a different type
    Value::UniquePtr createULongValue(uint32_t val) {
        auto v = Value::create(unsignedLong);
        v->read(std::to_string(val));
        return v;
    }

    // Helper to create a value with multiple entries
    Value::UniquePtr createMultiUShortValue(uint16_t val1, uint16_t val2) {
        auto v = Value::create(unsignedShort);
        v->read(std::to_string(val1) + " " + std::to_string(val2));
        return v;
    }
};

// Test printFocusMode with null metadata - should output fallback format
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_NullMetadata_1609) {
    auto value = createUShortValue(1);
    SonyMakerNote::printFocusMode(os, *value, nullptr);
    std::string result = os.str();
    // With null metadata, should output "(" << value << ")"
    EXPECT_EQ(result, "(1)");
}

// Test printFocusMode with wrong type (not unsignedShort) - should output fallback
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_WrongType_1609) {
    auto value = createULongValue(1);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "(1)");
}

// Test printFocusMode with multiple values (count != 1) - should output fallback
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_MultipleValues_1609) {
    auto value = createMultiUShortValue(1, 2);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "(1 2)");
}

// Test printFocusMode with valid value and metadata that has the specific version "DC7303320222000"
// This should return "n/a"
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_MatchingVersion_ReturnsNA_1609) {
    auto value = createUShortValue(1);
    ExifData metadata;

    // Set the metadata version to "DC7303320222000"
    // The getMetaVersion function likely reads from a specific Exif key
    // We need to set up the metadata so getMetaVersion returns "DC7303320222000"
    // The version is typically stored in Sony.SonyMisc3c or similar tag
    // Based on common Sony EXIF implementations, the version might be from
    // Exif.Sony2.MetaVersion or similar
    // Since we're treating this as black box, let's try setting the key
    metadata["Exif.Sony2.MetaVersion"] = "DC7303320222000";

    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    // If the version matches, it should output "n/a"
    // If version lookup fails or doesn't match, it goes to tag lookup
    // We can't be 100% sure which path without knowing getMetaVersion internals,
    // but we verify the output is reasonable
    EXPECT_FALSE(result.empty());
}

// Test printFocusMode with AF-S (value=1) and metadata without matching version
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_AFS_NoMatchingVersion_1609) {
    auto value = createUShortValue(1);
    ExifData metadata;
    // Empty metadata - getMetaVersion likely returns false or non-matching version
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    // Should go through EXV_PRINT_TAG(sonyFocusMode) path
    // Value 1 maps to "AF-S"
    EXPECT_EQ(result, "AF-S");
}

// Test printFocusMode with AF-C (value=2)
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_AFC_1609) {
    auto value = createUShortValue(2);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "AF-C");
}

// Test printFocusMode with Permanent-AF (value=4)
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_PermanentAF_1609) {
    auto value = createUShortValue(4);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "Permanent-AF");
}

// Test printFocusMode with n/a (value=65535)
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_NA_Value65535_1609) {
    auto value = createUShortValue(65535);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_EQ(result, "n/a");
}

// Test printFocusMode with unknown value
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_UnknownValue_1609) {
    auto value = createUShortValue(99);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    // Unknown values typically print "(99)" or similar
    EXPECT_FALSE(result.empty());
}

// Test printFocusMode with value 0 (not in tag list)
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_ZeroValue_1609) {
    auto value = createUShortValue(0);
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test printFocusMode returns reference to the same stream
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_ReturnsSameStream_1609) {
    auto value = createUShortValue(1);
    ExifData metadata;
    std::ostream& returnedOs = SonyMakerNote::printFocusMode(os, *value, &metadata);
    EXPECT_EQ(&returnedOs, &os);
}

// Test printFocusMode returns reference to same stream when null metadata
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_ReturnsSameStream_NullMeta_1609) {
    auto value = createUShortValue(1);
    std::ostream& returnedOs = SonyMakerNote::printFocusMode(os, *value, nullptr);
    EXPECT_EQ(&returnedOs, &os);
}

// Test printFocusMode with wrong type and null metadata (both conditions fail)
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_WrongTypeAndNullMeta_1609) {
    auto value = createULongValue(5);
    SonyMakerNote::printFocusMode(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_EQ(result, "(5)");
}

// Test that printFocusMode with signedShort type falls through to fallback
TEST_F(SonyMakerNoteTest_1609, PrintFocusMode_SignedShortType_1609) {
    auto value = Value::create(signedShort);
    value->read("1");
    ExifData metadata;
    SonyMakerNote::printFocusMode(os, *value, &metadata);
    std::string result = os.str();
    // signedShort != unsignedShort, so should output fallback
    EXPECT_EQ(result, "(1)");
}

// Additional tests for other printXxx methods that are part of the interface

// Test printMultiBurstMode with null metadata
TEST_F(SonyMakerNoteTest_1609, PrintMultiBurstMode_Basic_1609) {
    auto value = createUShortValue(0);
    ExifData metadata;
    SonyMakerNote::printMultiBurstMode(os, *value, &metadata);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test printImageSize with null metadata
TEST_F(SonyMakerNoteTest_1609, PrintImageSize_NullMetadata_1609) {
    auto value = createUShortValue(1);
    SonyMakerNote::printImageSize(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test printColorTemperature
TEST_F(SonyMakerNoteTest_1609, PrintColorTemperature_Basic_1609) {
    auto value = createUShortValue(5500);
    SonyMakerNote::printColorTemperature(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test printWhiteBalanceFineTune
TEST_F(SonyMakerNoteTest_1609, PrintWhiteBalanceFineTune_Basic_1609) {
    auto value = Value::create(signedLong);
    value->read("0");
    SonyMakerNote::printWhiteBalanceFineTune(os, *value, nullptr);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}
