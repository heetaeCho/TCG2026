#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

class NewTiffBinaryElementTest_416 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newTiffBinaryElement returns a non-null pointer
TEST_F(NewTiffBinaryElementTest_416, ReturnsNonNullPointer_416) {
    auto result = newTiffBinaryElement(0x0001, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned object has the correct tag
TEST_F(NewTiffBinaryElementTest_416, ReturnsCorrectTag_416) {
    const uint16_t expectedTag = 0x0001;
    auto result = newTiffBinaryElement(expectedTag, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test that the returned object has the correct group
TEST_F(NewTiffBinaryElementTest_416, ReturnsCorrectGroup_416) {
    const IfdId expectedGroup = IfdId::ifd0Id;
    auto result = newTiffBinaryElement(0x0001, expectedGroup);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), expectedGroup);
}

// Test with tag value of zero
TEST_F(NewTiffBinaryElementTest_416, TagZero_416) {
    auto result = newTiffBinaryElement(0x0000, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value
TEST_F(NewTiffBinaryElementTest_416, MaxTagValue_416) {
    const uint16_t maxTag = 0xFFFF;
    auto result = newTiffBinaryElement(maxTag, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), maxTag);
}

// Test with different group IDs
TEST_F(NewTiffBinaryElementTest_416, DifferentGroupExifId_416) {
    auto result = newTiffBinaryElement(0x0010, IfdId::exifId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0010);
    EXPECT_EQ(result->group(), IfdId::exifId);
}

// Test with different group - GPS
TEST_F(NewTiffBinaryElementTest_416, DifferentGroupGpsId_416) {
    auto result = newTiffBinaryElement(0x0020, IfdId::gpsId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0020);
    EXPECT_EQ(result->group(), IfdId::gpsId);
}

// Test that two calls return independent objects
TEST_F(NewTiffBinaryElementTest_416, ReturnsIndependentObjects_416) {
    auto result1 = newTiffBinaryElement(0x0001, IfdId::ifd0Id);
    auto result2 = newTiffBinaryElement(0x0002, IfdId::exifId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
    EXPECT_EQ(result1->group(), IfdId::ifd0Id);
    EXPECT_EQ(result2->group(), IfdId::exifId);
}

// Test with ifd1Id group
TEST_F(NewTiffBinaryElementTest_416, Ifd1Group_416) {
    auto result = newTiffBinaryElement(0x0100, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0100);
    EXPECT_EQ(result->group(), IfdId::ifd1Id);
}

// Test that ownership is properly transferred via unique_ptr
TEST_F(NewTiffBinaryElementTest_416, OwnershipTransfer_416) {
    TiffComponent::UniquePtr result = newTiffBinaryElement(0x0050, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    TiffComponent* rawPtr = result.get();
    TiffComponent::UniquePtr movedResult = std::move(result);
    EXPECT_EQ(result, nullptr);
    EXPECT_EQ(movedResult.get(), rawPtr);
}
