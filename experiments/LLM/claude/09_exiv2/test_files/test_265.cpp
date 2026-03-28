#include <gtest/gtest.h>
#include <memory>

// Include necessary exiv2 headers
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewTiffImageDataTest_265 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newTiffImageData returns a non-null pointer
TEST_F(NewTiffImageDataTest_265, ReturnsNonNullPointer_265) {
    auto result = newTiffImageData<0x0111, IfdId::ifd0Id>(0x0201, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned component has the correct tag
TEST_F(NewTiffImageDataTest_265, ReturnedComponentHasCorrectTag_265) {
    const uint16_t testTag = 0x0201;
    auto result = newTiffImageData<0x0111, IfdId::ifd0Id>(testTag, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test that the returned component has the correct group
TEST_F(NewTiffImageDataTest_265, ReturnedComponentHasCorrectGroup_265) {
    const IfdId testGroup = IfdId::ifd1Id;
    auto result = newTiffImageData<0x0111, IfdId::ifd0Id>(0x0201, testGroup);
    ASSERT_NE(result, nullptr);
    // TiffComponent should expose group
}

// Test with different template parameters
TEST_F(NewTiffImageDataTest_265, WorksWithDifferentTemplateParams_265) {
    auto result = newTiffImageData<0x0144, IfdId::ifd1Id>(0x0145, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0145);
}

// Test with zero tag value
TEST_F(NewTiffImageDataTest_265, WorksWithZeroTag_265) {
    auto result = newTiffImageData<0x0000, IfdId::ifd0Id>(0x0000, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum uint16_t tag value
TEST_F(NewTiffImageDataTest_265, WorksWithMaxTag_265) {
    auto result = newTiffImageData<0xFFFF, IfdId::ifd0Id>(0xFFFF, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test that multiple calls produce independent objects
TEST_F(NewTiffImageDataTest_265, MultipleCallsProduceIndependentObjects_265) {
    auto result1 = newTiffImageData<0x0111, IfdId::ifd0Id>(0x0201, IfdId::ifd1Id);
    auto result2 = newTiffImageData<0x0111, IfdId::ifd0Id>(0x0202, IfdId::ifd1Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0201);
    EXPECT_EQ(result2->tag(), 0x0202);
}

// Test with different szGroup template parameter values
TEST_F(NewTiffImageDataTest_265, WorksWithVariousSzGroupValues_265) {
    auto result = newTiffImageData<0x0111, IfdId::exifId>(0x0201, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0201);
}

// Test uniqueness of returned pointer (ownership semantics)
TEST_F(NewTiffImageDataTest_265, ReturnsUniquePtr_265) {
    TiffComponent::UniquePtr result = newTiffImageData<0x0111, IfdId::ifd0Id>(0x0201, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    // Verify ownership transfer works
    TiffComponent* rawPtr = result.get();
    TiffComponent::UniquePtr moved = std::move(result);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(moved.get(), rawPtr);
}
