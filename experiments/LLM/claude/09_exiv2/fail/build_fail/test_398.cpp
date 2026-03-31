#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test helper class to access protected members
class TestableTiffDirectory : public TiffDirectory {
public:
    TestableTiffDirectory(uint16_t tag, IfdId group, bool hasNext)
        : TiffDirectory(tag, group, hasNext) {}

    using TiffDirectory::doSizeData;
    using TiffDirectory::doSizeImage;
    using TiffDirectory::doSize;
    using TiffDirectory::doCount;
};

class TiffDirectoryTest_398 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that doSizeData returns 0 for a default-constructed TiffDirectory with hasNext=false
TEST_F(TiffDirectoryTest_398, DoSizeDataReturnsZero_NoNext_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(0u, dir.doSizeData());
}

// Test that doSizeData returns 0 for a TiffDirectory with hasNext=true
TEST_F(TiffDirectoryTest_398, DoSizeDataReturnsZero_WithNext_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_EQ(0u, dir.doSizeData());
}

// Test hasNext returns false when constructed with hasNext=false
TEST_F(TiffDirectoryTest_398, HasNextReturnsFalse_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test hasNext returns true when constructed with hasNext=true
TEST_F(TiffDirectoryTest_398, HasNextReturnsTrue_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

// Test doSizeData with different tag values
TEST_F(TiffDirectoryTest_398, DoSizeDataReturnsZero_DifferentTags_398) {
    TestableTiffDirectory dir1(0x0000, IfdId::ifd0Id, false);
    EXPECT_EQ(0u, dir1.doSizeData());

    TestableTiffDirectory dir2(0xFFFF, IfdId::ifd0Id, false);
    EXPECT_EQ(0u, dir2.doSizeData());

    TestableTiffDirectory dir3(0x8769, IfdId::ifd0Id, true);
    EXPECT_EQ(0u, dir3.doSizeData());
}

// Test doSizeData with different IfdId groups
TEST_F(TiffDirectoryTest_398, DoSizeDataReturnsZero_DifferentGroups_398) {
    TestableTiffDirectory dir1(0x0001, IfdId::ifd1Id, false);
    EXPECT_EQ(0u, dir1.doSizeData());

    TestableTiffDirectory dir2(0x0001, IfdId::exifId, true);
    EXPECT_EQ(0u, dir2.doSizeData());
}

// Test doCount for empty directory
TEST_F(TiffDirectoryTest_398, DoCountEmptyDirectory_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(0u, dir.doCount());
}

// Test doSize for empty directory
TEST_F(TiffDirectoryTest_398, DoSizeEmptyDirectory_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    // An empty directory should have some minimal size (at least the count field)
    size_t size = dir.doSize();
    // We just verify it doesn't crash and returns a value
    EXPECT_GE(size, 0u);
}

// Test doSizeImage for empty directory
TEST_F(TiffDirectoryTest_398, DoSizeImageEmptyDirectory_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, false);
    EXPECT_EQ(0u, dir.doSizeImage());
}

// Test multiple calls to doSizeData return consistent results
TEST_F(TiffDirectoryTest_398, DoSizeDataConsistentResults_398) {
    TestableTiffDirectory dir(0x0001, IfdId::ifd0Id, true);
    EXPECT_EQ(dir.doSizeData(), dir.doSizeData());
    EXPECT_EQ(0u, dir.doSizeData());
}
