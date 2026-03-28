#include <gtest/gtest.h>
#include <cstdint>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewTiffSubIfdTest_259 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that newTiffSubIfd returns a non-null pointer
TEST_F(NewTiffSubIfdTest_259, ReturnsNonNullPointer_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned TiffComponent has the correct tag
TEST_F(NewTiffSubIfdTest_259, ReturnsComponentWithCorrectTag_259) {
    const uint16_t testTag = 0x014a;
    auto result = newTiffSubIfd<IfdId::ifd1Id>(testTag, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), testTag);
}

// Test that the returned TiffComponent has the correct group
TEST_F(NewTiffSubIfdTest_259, ReturnsComponentWithCorrectGroup_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::ifd0Id);
}

// Test with different template parameter (newGroup)
TEST_F(NewTiffSubIfdTest_259, WorksWithDifferentNewGroup_259) {
    auto result = newTiffSubIfd<IfdId::exifId>(0x8769, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x8769);
    EXPECT_EQ(result->group(), IfdId::ifd0Id);
}

// Test with tag value of zero (boundary)
TEST_F(NewTiffSubIfdTest_259, WorksWithZeroTag_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0x0000, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value (boundary)
TEST_F(NewTiffSubIfdTest_259, WorksWithMaxTag_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0xFFFF, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test with different group parameter
TEST_F(NewTiffSubIfdTest_259, WorksWithDifferentGroup_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::exifId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::exifId);
}

// Test that the result is a TiffSubIfd by checking dynamic cast
TEST_F(NewTiffSubIfdTest_259, ReturnsTiffSubIfdType_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    TiffSubIfd* subIfd = dynamic_cast<TiffSubIfd*>(result.get());
    EXPECT_NE(subIfd, nullptr);
}

// Test that the TiffSubIfd's newGroup is set correctly
TEST_F(NewTiffSubIfdTest_259, SubIfdHasCorrectNewGroup_259) {
    auto result = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    TiffSubIfd* subIfd = dynamic_cast<TiffSubIfd*>(result.get());
    ASSERT_NE(subIfd, nullptr);
    EXPECT_EQ(subIfd->newGroup(), IfdId::ifd1Id);
}

// Test creating multiple instances with same parameters
TEST_F(NewTiffSubIfdTest_259, MultipleInstancesAreIndependent_259) {
    auto result1 = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::ifd0Id);
    auto result2 = newTiffSubIfd<IfdId::ifd1Id>(0x014a, IfdId::ifd0Id);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), result2->tag());
    EXPECT_EQ(result1->group(), result2->group());
}

// Test with gpsId as newGroup
TEST_F(NewTiffSubIfdTest_259, WorksWithGpsNewGroup_259) {
    auto result = newTiffSubIfd<IfdId::gpsId>(0x8825, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x8825);
    EXPECT_EQ(result->group(), IfdId::ifd0Id);
    TiffSubIfd* subIfd = dynamic_cast<TiffSubIfd*>(result.get());
    ASSERT_NE(subIfd, nullptr);
    EXPECT_EQ(subIfd->newGroup(), IfdId::gpsId);
}
