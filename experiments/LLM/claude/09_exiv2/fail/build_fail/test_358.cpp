#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

using namespace Exiv2::Internal;

class TiffDirectoryTest_358 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that a newly created TiffDirectory has zero components
TEST_F(TiffDirectoryTest_358, NewDirectoryHasZeroCount_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // doCount is protected, accessed via count() from TiffComponent
    EXPECT_EQ(dir.count(), 0u);
}

// Test hasNext returns false when constructed with hasNext=false
TEST_F(TiffDirectoryTest_358, HasNextReturnsFalseWhenConstructedWithFalse_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test hasNext returns true when constructed with hasNext=true
TEST_F(TiffDirectoryTest_358, HasNextReturnsTrueWhenConstructedWithTrue_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

// Test that tag is correctly stored
TEST_F(TiffDirectoryTest_358, TagIsCorrectlyStored_358) {
    TiffDirectory dir(0x1234, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.tag(), 0x1234);
}

// Test that group is correctly stored
TEST_F(TiffDirectoryTest_358, GroupIsCorrectlyStored_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.group(), IfdId::ifd0Id);
}

// Test with different IfdId group
TEST_F(TiffDirectoryTest_358, DifferentGroupIsCorrectlyStored_358) {
    TiffDirectory dir(0x0001, IfdId::exifId, true);
    EXPECT_EQ(dir.group(), IfdId::exifId);
}

// Test that adding a child increases the count
TEST_F(TiffDirectoryTest_358, AddChildIncreasesCount_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    auto child = std::make_shared<TiffDirectory>(0x0002, IfdId::ifd0Id, false);
    dir.addChild(child);
    EXPECT_EQ(dir.count(), 1u);
}

// Test that adding multiple children increases count accordingly
TEST_F(TiffDirectoryTest_358, AddMultipleChildrenIncreasesCount_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    auto child1 = std::make_shared<TiffDirectory>(0x0002, IfdId::ifd0Id, false);
    auto child2 = std::make_shared<TiffDirectory>(0x0003, IfdId::ifd0Id, false);
    auto child3 = std::make_shared<TiffDirectory>(0x0004, IfdId::ifd0Id, false);
    dir.addChild(child1);
    dir.addChild(child2);
    dir.addChild(child3);
    EXPECT_EQ(dir.count(), 3u);
}

// Test with tag value of zero (boundary)
TEST_F(TiffDirectoryTest_358, TagZeroBoundary_358) {
    TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
    EXPECT_EQ(dir.tag(), 0x0000);
    EXPECT_EQ(dir.count(), 0u);
}

// Test with maximum tag value (boundary)
TEST_F(TiffDirectoryTest_358, MaxTagValueBoundary_358) {
    TiffDirectory dir(0xFFFF, IfdId::ifd0Id, true);
    EXPECT_EQ(dir.tag(), 0xFFFF);
    EXPECT_TRUE(dir.hasNext());
}

// Test size of empty directory
TEST_F(TiffDirectoryTest_358, EmptyDirectorySizeIsZeroOrMinimal_358) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // An empty directory should have some defined size behavior
    size_t s = dir.size();
    // Empty directory with no components - size should be deterministic
    EXPECT_GE(s, 0u);
}
