#include <gtest/gtest.h>
#include <cstdint>

// Include necessary headers
#include "crwimage_int.hpp"
#include "error.hpp"

namespace Exiv2 {
namespace Internal {

class CiffComponentDataLocationTest_1785 : public ::testing::Test {
protected:
    CiffComponent component;
};

// Test normal operation: tag with upper bits 0x0000 returns valueData
TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits0000_ReturnsValueData_1785) {
    // tag & 0xc000 == 0x0000
    DataLocId result = CiffComponent::dataLocation(0x0000);
    EXPECT_EQ(result, DataLocId::valueData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits0000_NonZeroLowerBits_ReturnsValueData_1785) {
    // tag = 0x1234, tag & 0xc000 == 0x0000
    DataLocId result = CiffComponent::dataLocation(0x1234);
    EXPECT_EQ(result, DataLocId::valueData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits0000_MaxLowerBits_ReturnsValueData_1785) {
    // tag = 0x3FFF, tag & 0xc000 == 0x0000
    DataLocId result = CiffComponent::dataLocation(0x3FFF);
    EXPECT_EQ(result, DataLocId::valueData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits0000_Value0001_ReturnsValueData_1785) {
    DataLocId result = CiffComponent::dataLocation(0x0001);
    EXPECT_EQ(result, DataLocId::valueData);
}

// Test normal operation: tag with upper bits 0x4000 returns directoryData
TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits4000_ReturnsDirectoryData_1785) {
    // tag & 0xc000 == 0x4000
    DataLocId result = CiffComponent::dataLocation(0x4000);
    EXPECT_EQ(result, DataLocId::directoryData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits4000_NonZeroLowerBits_ReturnsDirectoryData_1785) {
    // tag = 0x5ABC, tag & 0xc000 == 0x4000
    DataLocId result = CiffComponent::dataLocation(0x5ABC);
    EXPECT_EQ(result, DataLocId::directoryData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits4000_MaxLowerBits_ReturnsDirectoryData_1785) {
    // tag = 0x7FFF, tag & 0xc000 == 0x4000
    DataLocId result = CiffComponent::dataLocation(0x7FFF);
    EXPECT_EQ(result, DataLocId::directoryData);
}

// Test error case: tag with upper bits 0x8000 throws exception
TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits8000_ThrowsError_1785) {
    // tag & 0xc000 == 0x8000
    EXPECT_THROW(CiffComponent::dataLocation(0x8000), Error);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits8000_NonZeroLowerBits_ThrowsError_1785) {
    // tag = 0x9ABC, tag & 0xc000 == 0x8000
    EXPECT_THROW(CiffComponent::dataLocation(0x9ABC), Error);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBits8000_MaxRange_ThrowsError_1785) {
    // tag = 0xBFFF, tag & 0xc000 == 0x8000
    EXPECT_THROW(CiffComponent::dataLocation(0xBFFF), Error);
}

// Test error case: tag with upper bits 0xC000 throws exception
TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBitsC000_ThrowsError_1785) {
    // tag & 0xc000 == 0xC000
    EXPECT_THROW(CiffComponent::dataLocation(0xC000), Error);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBitsC000_NonZeroLowerBits_ThrowsError_1785) {
    // tag = 0xDEAD, tag & 0xc000 == 0xC000
    EXPECT_THROW(CiffComponent::dataLocation(0xDEAD), Error);
}

TEST_F(CiffComponentDataLocationTest_1785, TagWithUpperBitsC000_MaxValue_ThrowsError_1785) {
    // tag = 0xFFFF, tag & 0xc000 == 0xC000
    EXPECT_THROW(CiffComponent::dataLocation(0xFFFF), Error);
}

// Boundary tests
TEST_F(CiffComponentDataLocationTest_1785, TagBoundary_0x3FFF_ReturnsValueData_1785) {
    // Just below 0x4000 boundary
    DataLocId result = CiffComponent::dataLocation(0x3FFF);
    EXPECT_EQ(result, DataLocId::valueData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagBoundary_0x4000_ReturnsDirectoryData_1785) {
    // Exactly at 0x4000 boundary
    DataLocId result = CiffComponent::dataLocation(0x4000);
    EXPECT_EQ(result, DataLocId::directoryData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagBoundary_0x7FFF_ReturnsDirectoryData_1785) {
    // Just below 0x8000 boundary
    DataLocId result = CiffComponent::dataLocation(0x7FFF);
    EXPECT_EQ(result, DataLocId::directoryData);
}

TEST_F(CiffComponentDataLocationTest_1785, TagBoundary_0x8000_ThrowsError_1785) {
    // Exactly at 0x8000 boundary
    EXPECT_THROW(CiffComponent::dataLocation(0x8000), Error);
}

// Test instance method (non-static) version via object
TEST_F(CiffComponentDataLocationTest_1785, InstanceMethod_TagZero_ReturnsValueData_1785) {
    DataLocId result = component.dataLocation(0x0000);
    EXPECT_EQ(result, DataLocId::valueData);
}

TEST_F(CiffComponentDataLocationTest_1785, InstanceMethod_Tag4000_ReturnsDirectoryData_1785) {
    DataLocId result = component.dataLocation(0x4000);
    EXPECT_EQ(result, DataLocId::directoryData);
}

TEST_F(CiffComponentDataLocationTest_1785, InstanceMethod_TagC000_ThrowsError_1785) {
    EXPECT_THROW(component.dataLocation(0xC000), Error);
}

}  // namespace Internal
}  // namespace Exiv2
