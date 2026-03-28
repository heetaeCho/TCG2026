#include <gtest/gtest.h>
#include <memory>

// Include necessary Exiv2 headers
#include "makernote_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewSigmaMn2Test_1529 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that newSigmaMn2 returns a non-null pointer
TEST_F(NewSigmaMn2Test_1529, ReturnsNonNullPointer_1529) {
    auto result = newSigmaMn2(0x927c, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
}

// Test with typical Sigma makernote tag
TEST_F(NewSigmaMn2Test_1529, CreatesWithTypicalMakernoteTag_1529) {
    uint16_t tag = 0x927c;  // Standard MakerNote tag
    auto result = newSigmaMn2(tag, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
    // Verify the tag is stored correctly via the public interface
    EXPECT_EQ(result->tag(), tag);
}

// Test with zero tag value
TEST_F(NewSigmaMn2Test_1529, CreatesWithZeroTag_1529) {
    uint16_t tag = 0x0000;
    auto result = newSigmaMn2(tag, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with maximum uint16_t tag value (boundary)
TEST_F(NewSigmaMn2Test_1529, CreatesWithMaxTag_1529) {
    uint16_t tag = 0xFFFF;
    auto result = newSigmaMn2(tag, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test with different group IDs
TEST_F(NewSigmaMn2Test_1529, CreatesWithDifferentGroupIds_1529) {
    auto result = newSigmaMn2(0x927c, IfdId::ifd0Id, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
}

// Test that multiple calls create distinct objects
TEST_F(NewSigmaMn2Test_1529, MultipleCallsCreateDistinctObjects_1529) {
    auto result1 = newSigmaMn2(0x927c, IfdId::exifId, IfdId::sigmaMnId);
    auto result2 = newSigmaMn2(0x927c, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
}

// Test that the returned object has the correct mnGroup
TEST_F(NewSigmaMn2Test_1529, CorrectMnGroup_1529) {
    auto result = newSigmaMn2(0x927c, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
    // The mnGroup should be accessible through the TiffIfdMakernote interface
    EXPECT_EQ(result->mnGroup(), IfdId::sigmaMnId);
}

// Test with tag value 1 (boundary near minimum)
TEST_F(NewSigmaMn2Test_1529, CreatesWithTagValueOne_1529) {
    uint16_t tag = 0x0001;
    auto result = newSigmaMn2(tag, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), tag);
}

// Test ownership semantics - unique_ptr should be movable
TEST_F(NewSigmaMn2Test_1529, OwnershipTransfer_1529) {
    auto result = newSigmaMn2(0x927c, IfdId::exifId, IfdId::sigmaMnId);
    ASSERT_NE(result, nullptr);
    auto moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    ASSERT_NE(moved, nullptr);
    EXPECT_EQ(moved->tag(), 0x927c);
}
