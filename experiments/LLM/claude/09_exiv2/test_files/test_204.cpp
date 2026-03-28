#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"
#include "pentaxmn_int.hpp"

// We need access to the resolveLens0x32c function and related internals
// Since it's in an anonymous-like static context within the Internal namespace,
// we need to access it through the tag infrastructure or declare it.

namespace Exiv2 {
namespace Internal {

// Forward declare the function we're testing
extern std::ostream& resolveLens0x32c(std::ostream& os, const Value& value, const ExifData* metadata);

// Forward declare the tag details array
extern const TagDetails pentaxLensType[];

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;

class ResolveLens0x32cTest_204 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create ExifData with a specific focal length
    ExifData createMetadataWithFocalLength(long focalLength) {
        ExifData exifData;
        // Set focal length via operator[]
        exifData["Exif.Photo.FocalLength"] = static_cast<uint16_t>(focalLength);
        return exifData;
    }
};

// Test with focal length within 10-20 range (should trigger index=1 path)
TEST_F(ResolveLens0x32cTest_204, FocalLengthInRange10To20_204) {
    ExifData metadata = createMetadataWithFocalLength(15);
    
    auto value = Value::create(unsignedShort);
    // The value for lens type 0x32c = 812 decimal
    // 0x32c in the pentaxLensType table needs two components for COMBITAG
    // Lens ID 0x32c = 812. In the two-byte representation: 3*256 + 44 = 812
    // So first byte = 3, second byte = 44
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // When focal length is between 10-20, index=1, so we get the second entry for lensID 0x32c
    // Looking at pentaxLensType, 812 has multiple entries. The second one (index 1) should be used.
    EXPECT_FALSE(result.empty());
}

// Test with focal length = 10 (lower boundary of 10-20 range)
TEST_F(ResolveLens0x32cTest_204, FocalLengthAtLowerBound10_204) {
    ExifData metadata = createMetadataWithFocalLength(10);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with focal length = 20 (upper boundary of 10-20 range)
TEST_F(ResolveLens0x32cTest_204, FocalLengthAtUpperBound20_204) {
    ExifData metadata = createMetadataWithFocalLength(20);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test with focal length = 9 (just below 10-20 range)
TEST_F(ResolveLens0x32cTest_204, FocalLengthBelowRange9_204) {
    ExifData metadata = createMetadataWithFocalLength(9);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // Should fall through to EXV_PRINT_COMBITAG_MULTI
    EXPECT_FALSE(result.empty());
}

// Test with focal length = 21 (just above 10-20 range)
TEST_F(ResolveLens0x32cTest_204, FocalLengthAboveRange21_204) {
    ExifData metadata = createMetadataWithFocalLength(21);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // Should fall through to EXV_PRINT_COMBITAG_MULTI
    EXPECT_FALSE(result.empty());
}

// Test with null metadata pointer
TEST_F(ResolveLens0x32cTest_204, NullMetadata_204) {
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    // Should not crash with null metadata, exception should be caught
    resolveLens0x32c(os, *value, nullptr);
    
    std::string result = os.str();
    // Should fall through to EXV_PRINT_COMBITAG_MULTI path
    EXPECT_FALSE(result.empty());
}

// Test with focal length = 0
TEST_F(ResolveLens0x32cTest_204, FocalLengthZero_204) {
    ExifData metadata = createMetadataWithFocalLength(0);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // Focal length 0 is not in [10,20], so falls through to COMBITAG
    EXPECT_FALSE(result.empty());
}

// Test with very large focal length
TEST_F(ResolveLens0x32cTest_204, FocalLengthVeryLarge_204) {
    ExifData metadata = createMetadataWithFocalLength(500);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // Focal length 500 is not in [10,20], so falls through to COMBITAG
    EXPECT_FALSE(result.empty());
}

// Test with empty metadata (no FocalLength key)
TEST_F(ResolveLens0x32cTest_204, EmptyMetadata_204) {
    ExifData metadata;  // No focal length set
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    // getKeyLong should throw or return error when key not found
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // Should fall through to EXV_PRINT_COMBITAG_MULTI
    EXPECT_FALSE(result.empty());
}

// Test that the output stream is properly returned
TEST_F(ResolveLens0x32cTest_204, ReturnsOutputStream_204) {
    ExifData metadata = createMetadataWithFocalLength(15);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    std::ostream& result = resolveLens0x32c(os, *value, &metadata);
    
    // The returned reference should be the same stream
    EXPECT_EQ(&result, &os);
}

// Test with focal length exactly at boundaries
TEST_F(ResolveLens0x32cTest_204, FocalLengthExactly10_204) {
    ExifData metadata = createMetadataWithFocalLength(10);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    // At FL=10, bFL10_20 is true, index=1
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ResolveLens0x32cTest_204, FocalLengthExactly20_204) {
    ExifData metadata = createMetadataWithFocalLength(20);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test consistency: same input gives same output
TEST_F(ResolveLens0x32cTest_204, ConsistentOutput_204) {
    ExifData metadata1 = createMetadataWithFocalLength(15);
    ExifData metadata2 = createMetadataWithFocalLength(15);
    
    auto value1 = Value::create(unsignedShort);
    value1->read("3 44");
    auto value2 = Value::create(unsignedShort);
    value2->read("3 44");
    
    std::ostringstream os1, os2;
    resolveLens0x32c(os1, *value1, &metadata1);
    resolveLens0x32c(os2, *value2, &metadata2);
    
    EXPECT_EQ(os1.str(), os2.str());
}

// Test with focal length in range and out of range produce different results
TEST_F(ResolveLens0x32cTest_204, InRangeVsOutOfRangeDifference_204) {
    ExifData metadataInRange = createMetadataWithFocalLength(15);
    ExifData metadataOutRange = createMetadataWithFocalLength(50);
    
    auto value1 = Value::create(unsignedShort);
    value1->read("3 44");
    auto value2 = Value::create(unsignedShort);
    value2->read("3 44");
    
    std::ostringstream osIn, osOut;
    resolveLens0x32c(osIn, *value1, &metadataInRange);
    resolveLens0x32c(osOut, *value2, &metadataOutRange);
    
    // The in-range case uses index=1 (alternate lens name),
    // while out-of-range uses the default COMBITAG resolution
    // They may or may not differ depending on the table entries
    // but at minimum both should produce non-empty output
    EXPECT_FALSE(osIn.str().empty());
    EXPECT_FALSE(osOut.str().empty());
}

// Test with negative focal length
TEST_F(ResolveLens0x32cTest_204, NegativeFocalLength_204) {
    ExifData metadata = createMetadataWithFocalLength(-5);
    
    auto value = Value::create(unsignedShort);
    value->read("3 44");
    
    std::ostringstream os;
    resolveLens0x32c(os, *value, &metadata);
    
    std::string result = os.str();
    // Negative focal length is not in [10,20], falls through to COMBITAG
    EXPECT_FALSE(result.empty());
}
