#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

namespace Exiv2 {
namespace Internal {

class TiffCopierVisitSizeEntryTest_1645 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that visitSizeEntry can be called with a valid TiffSizeEntry object
// when TiffCopier is constructed with a null root (boundary case)
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryWithNullRoot_1645) {
    PrimaryGroups primaryGroups;
    TiffCopier copier(nullptr, 0, nullptr, primaryGroups);
    
    TiffSizeEntry sizeEntry(0x0100, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    
    // visitSizeEntry calls copyObject internally.
    // With null pRoot_, copyObject should handle gracefully (no crash expected
    // if the implementation guards against null root).
    // This tests the boundary condition of null root.
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

// Test that visitSizeEntry works with a TiffDirectory as root
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryWithDirectoryRoot_1645) {
    TiffDirectory rootDir(0x0000, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&rootDir, Tag::root, nullptr, primaryGroups);
    
    TiffSizeEntry sizeEntry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    
    // Should not crash; copyObject will attempt to clone and add to tree
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

// Test visitSizeEntry with different tag/group combinations
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryDifferentTags_1645) {
    TiffDirectory rootDir(0x0000, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&rootDir, Tag::root, nullptr, primaryGroups);
    
    // Use a different tag combination
    TiffSizeEntry sizeEntry(0x0202, IfdId::ifd1Id, 0x0201, IfdId::ifd1Id);
    
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

// Test that visitSizeEntry with zero tags (boundary)
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryZeroTags_1645) {
    TiffDirectory rootDir(0x0000, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&rootDir, Tag::root, nullptr, primaryGroups);
    
    TiffSizeEntry sizeEntry(0x0000, IfdId::ifd0Id, 0x0000, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

// Test that visitSizeEntry with max uint16 tag values (boundary)
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryMaxTags_1645) {
    TiffDirectory rootDir(0x0000, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&rootDir, Tag::root, nullptr, primaryGroups);
    
    TiffSizeEntry sizeEntry(0xFFFF, IfdId::ifd0Id, 0xFFFF, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

// Test that TiffSizeEntry accessors return correct values
TEST_F(TiffCopierVisitSizeEntryTest_1645, TiffSizeEntryAccessors_1645) {
    TiffSizeEntry sizeEntry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd1Id);
    
    EXPECT_EQ(sizeEntry.dtTag(), 0x0111);
    EXPECT_EQ(sizeEntry.dtGroup(), IfdId::ifd1Id);
    EXPECT_EQ(sizeEntry.tag(), 0x0117);
}

// Test multiple calls to visitSizeEntry on same copier
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryMultipleCalls_1645) {
    TiffDirectory rootDir(0x0000, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    TiffCopier copier(&rootDir, Tag::root, nullptr, primaryGroups);
    
    TiffSizeEntry sizeEntry1(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    TiffSizeEntry sizeEntry2(0x0202, IfdId::ifd1Id, 0x0201, IfdId::ifd1Id);
    
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry1));
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry2));
}

// Test visitSizeEntry with primary groups populated
TEST_F(TiffCopierVisitSizeEntryTest_1645, VisitSizeEntryWithPrimaryGroups_1645) {
    TiffDirectory rootDir(0x0000, IfdId::ifd0Id);
    PrimaryGroups primaryGroups;
    primaryGroups.push_back(IfdId::ifd0Id);
    primaryGroups.push_back(IfdId::ifd1Id);
    TiffCopier copier(&rootDir, Tag::root, nullptr, primaryGroups);
    
    TiffSizeEntry sizeEntry(0x0117, IfdId::ifd0Id, 0x0111, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(copier.visitSizeEntry(&sizeEntry));
}

}  // namespace Internal
}  // namespace Exiv2
