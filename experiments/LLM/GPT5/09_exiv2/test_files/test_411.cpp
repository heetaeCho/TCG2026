#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/tags.hpp"
#include "exiv2/types.hpp"
#include "exiv2/tiffcomposite_int.hpp"

namespace Exiv2 { namespace Internal {

// Mocking the external collaborator (if needed)
class MockTagInfo {
public:
    MOCK_METHOD(const TagInfo*, findTagInfo, (uint16_t tag, IfdId group), ());
};

} } // namespace Exiv2::Internal

// Test Suite for Exiv2::Internal::toTypeId function
TEST_F(TiffCompositeIntTest_411, TestToTypeId_NormalOperation_411) {
    // Test with a normal case where tag and group lead to a valid TypeId
    TiffType tiffType = TiffType::unsignedByte;
    uint16_t tag = 0x0002;
    IfdId group = IfdId::nikonAFTId;

    // Expected result
    TypeId expectedTypeId = Exiv2::signedByte;

    // Call the function
    TypeId result = Exiv2::Internal::toTypeId(tiffType, tag, group);

    // Verify that the result is as expected
    EXPECT_EQ(result, expectedTypeId);
}

TEST_F(TiffCompositeIntTest_411, TestToTypeId_InvalidTag_411) {
    // Test with an invalid tag
    TiffType tiffType = TiffType::unsignedByte;
    uint16_t tag = 0xFFFF;  // Invalid tag
    IfdId group = IfdId::nikonAFTId;

    // Expected result (no valid TypeId found)
    TypeId expectedTypeId = Exiv2::unsignedByte;

    // Call the function
    TypeId result = Exiv2::Internal::toTypeId(tiffType, tag, group);

    // Verify that the result is as expected
    EXPECT_EQ(result, expectedTypeId);
}

TEST_F(TiffCompositeIntTest_411, TestToTypeId_TagForComment_411) {
    // Test where the tag is a special "comment" tag
    TiffType tiffType = TiffType::unsignedByte;
    uint16_t tag = 0x0002;
    IfdId group = IfdId::nikonAFTId;

    // Expected result (comment type)
    TypeId expectedTypeId = Exiv2::comment;

    // Call the function
    TypeId result = Exiv2::Internal::toTypeId(tiffType, tag, group);

    // Verify that the result is as expected
    EXPECT_EQ(result, expectedTypeId);
}

TEST_F(TiffCompositeIntTest_411, TestToTypeId_TypeIsUndefined_411) {
    // Test with tiffType set to "undefined" 
    TiffType tiffType = TiffType::undefined;
    uint16_t tag = 0x0002;
    IfdId group = IfdId::nikonAFTId;

    // Expected result: should fall back to tag information
    TypeId expectedTypeId = Exiv2::signedByte;

    // Call the function
    TypeId result = Exiv2::Internal::toTypeId(tiffType, tag, group);

    // Verify that the result is as expected
    EXPECT_EQ(result, expectedTypeId);
}

TEST_F(TiffCompositeIntTest_411, TestToTypeId_UnsupportedFormat_411) {
    // Test for unsupported format (should return unsignedByte)
    TiffType tiffType = TiffType::unsignedByte;
    uint16_t tag = 0x0047;  // Tag for pentaxId
    IfdId group = IfdId::pentaxId;

    // Expected result (should fallback to signedByte)
    TypeId expectedTypeId = Exiv2::signedByte;

    // Call the function
    TypeId result = Exiv2::Internal::toTypeId(tiffType, tag, group);

    // Verify that the result is as expected
    EXPECT_EQ(result, expectedTypeId);
}

}  // namespace Exiv2::Internal