#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for TiffDirectory tests
class TiffDirectoryTest_245 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that hasNext() returns true when constructed with hasNext = true
TEST_F(TiffDirectoryTest_245, HasNextReturnsTrueWhenConstructedWithTrue_245) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

// Test that hasNext() returns false when constructed with hasNext = false
TEST_F(TiffDirectoryTest_245, HasNextReturnsFalseWhenConstructedWithFalse_245) {
    TiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test hasNext with different tag values - boundary tag 0x0000
TEST_F(TiffDirectoryTest_245, HasNextWithZeroTag_245) {
    TiffDirectory dir(0x0000, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

// Test hasNext with max tag value
TEST_F(TiffDirectoryTest_245, HasNextWithMaxTag_245) {
    TiffDirectory dir(0xFFFF, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test that hasNext is consistent across multiple calls
TEST_F(TiffDirectoryTest_245, HasNextIsConsistentAcrossMultipleCalls_245) {
    TiffDirectory dirWithNext(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dirWithNext.hasNext());
    EXPECT_TRUE(dirWithNext.hasNext());
    EXPECT_TRUE(dirWithNext.hasNext());

    TiffDirectory dirWithoutNext(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dirWithoutNext.hasNext());
    EXPECT_FALSE(dirWithoutNext.hasNext());
    EXPECT_FALSE(dirWithoutNext.hasNext());
}

// Test with different IfdId groups - hasNext should still reflect constructor parameter
TEST_F(TiffDirectoryTest_245, HasNextWithDifferentGroups_245) {
    TiffDirectory dir1(0x0001, IfdId::ifd1Id, true);
    EXPECT_TRUE(dir1.hasNext());

    TiffDirectory dir2(0x0001, IfdId::ifd1Id, false);
    EXPECT_FALSE(dir2.hasNext());
}

// Test that two directories created with different hasNext values are independent
TEST_F(TiffDirectoryTest_245, TwoDirectoriesIndependent_245) {
    TiffDirectory dirTrue(0x0001, IfdId::ifd0Id, true);
    TiffDirectory dirFalse(0x0001, IfdId::ifd0Id, false);

    EXPECT_TRUE(dirTrue.hasNext());
    EXPECT_FALSE(dirFalse.hasNext());
}
