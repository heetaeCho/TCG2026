#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffSubIfdTest_392 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly created TiffSubIfd with no IFDs has size 0
// doSize() returns ifds_.size() * 4, so with empty ifds_ it should be 0
TEST_F(TiffSubIfdTest_392, NewSubIfdHasZeroSize_392) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    // size() should delegate to doSize() which returns ifds_.size() * 4
    // With no children added, ifds_ should be empty
    EXPECT_EQ(subIfd.size(), 0u);
}

// Test construction with different tag values
TEST_F(TiffSubIfdTest_392, ConstructionWithDifferentTags_392) {
    TiffSubIfd subIfd1(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd1.tag(), 0x014a);

    TiffSubIfd subIfd2(0x0100, IfdId::ifd0Id, IfdId::subImage2Id);
    EXPECT_EQ(subIfd2.tag(), 0x0100);
}

// Test that group is correctly set
TEST_F(TiffSubIfdTest_392, ConstructionSetsGroup_392) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.group(), IfdId::ifd0Id);
}

// Test adding a child increases size by 4 (each IFD pointer is 4 bytes)
TEST_F(TiffSubIfdTest_392, AddChildIncreasesSize_392) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    // Create a child TiffComponent to add
    auto child = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage1Id);
    subIfd.addChild(child);
    
    // After adding one child, doSize should return 1 * 4 = 4
    EXPECT_EQ(subIfd.size(), 4u);
}

// Test adding multiple children
TEST_F(TiffSubIfdTest_392, AddMultipleChildrenIncreasesSize_392) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    auto child1 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage1Id);
    auto child2 = std::make_shared<TiffDirectory>(0x014a, IfdId::subImage2Id);
    
    subIfd.addChild(child1);
    subIfd.addChild(child2);
    
    // After adding two children, doSize should return 2 * 4 = 8
    EXPECT_EQ(subIfd.size(), 8u);
}

// Test that tag 0 is valid
TEST_F(TiffSubIfdTest_392, ZeroTagConstruction_392) {
    TiffSubIfd subIfd(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.tag(), 0x0000);
    EXPECT_EQ(subIfd.size(), 0u);
}

// Test with max uint16 tag value
TEST_F(TiffSubIfdTest_392, MaxTagConstruction_392) {
    TiffSubIfd subIfd(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.tag(), 0xFFFF);
}

// Test that size remains consistent when no modifications are made
TEST_F(TiffSubIfdTest_392, SizeConsistentOnMultipleCalls_392) {
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    EXPECT_EQ(subIfd.size(), subIfd.size());
}
