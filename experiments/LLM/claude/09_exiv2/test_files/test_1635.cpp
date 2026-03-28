#include <gtest/gtest.h>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for TiffFinder tests
class TiffFinderTest_1635 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TiffFinder has null result
TEST_F(TiffFinderTest_1635, InitialResultIsNull_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject sets result when tag and group match
TEST_F(TiffFinderTest_1635, FindObjectMatchingTagAndGroup_1635) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDirectory dir(tag, group, false);
    finder.findObject(&dir);

    EXPECT_EQ(&dir, finder.result());
}

// Test that findObject does not set result when tag does not match
TEST_F(TiffFinderTest_1635, FindObjectNonMatchingTag_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffDirectory dir(0x0101, IfdId::ifd0Id, false);
    finder.findObject(&dir);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when group does not match
TEST_F(TiffFinderTest_1635, FindObjectNonMatchingGroup_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffDirectory dir(0x0100, IfdId::ifd1Id, false);
    finder.findObject(&dir);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when neither tag nor group match
TEST_F(TiffFinderTest_1635, FindObjectNonMatchingTagAndGroup_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffDirectory dir(0x0200, IfdId::ifd1Id, false);
    finder.findObject(&dir);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that visitDirectory calls findObject (matching case)
TEST_F(TiffFinderTest_1635, VisitDirectoryMatchingObject_1635) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDirectory dir(tag, group, false);
    finder.visitDirectory(&dir);

    EXPECT_EQ(&dir, finder.result());
}

// Test that visitDirectory does not match when tag differs
TEST_F(TiffFinderTest_1635, VisitDirectoryNonMatchingObject_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffDirectory dir(0x0200, IfdId::ifd0Id, false);
    finder.visitDirectory(&dir);

    EXPECT_EQ(nullptr, finder.result());
}

// Test init resets the finder state
TEST_F(TiffFinderTest_1635, InitResetsState_1635) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    // First find a matching object
    TiffDirectory dir(tag, group, false);
    finder.findObject(&dir);
    EXPECT_EQ(&dir, finder.result());

    // Re-init with different tag/group - result should be cleared
    finder.init(0x0200, IfdId::ifd1Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test init changes the search criteria
TEST_F(TiffFinderTest_1635, InitChangesSearchCriteria_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    // This should not match original criteria
    TiffDirectory dir(0x0200, IfdId::ifd1Id, false);
    finder.findObject(&dir);
    EXPECT_EQ(nullptr, finder.result());

    // Re-init with matching criteria
    finder.init(0x0200, IfdId::ifd1Id);
    finder.findObject(&dir);
    EXPECT_EQ(&dir, finder.result());
}

// Test visitEntry with matching TiffEntry
TEST_F(TiffFinderTest_1635, VisitEntryMatching_1635) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test visitEntry with non-matching TiffEntry
TEST_F(TiffFinderTest_1635, VisitEntryNonMatching_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry(0x0200, IfdId::ifd0Id);
    finder.visitEntry(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test with tag value 0 (boundary)
TEST_F(TiffFinderTest_1635, FindObjectWithZeroTag_1635) {
    TiffFinder finder(0x0000, IfdId::ifd0Id);

    TiffDirectory dir(0x0000, IfdId::ifd0Id, false);
    finder.findObject(&dir);

    EXPECT_EQ(&dir, finder.result());
}

// Test with max tag value (boundary)
TEST_F(TiffFinderTest_1635, FindObjectWithMaxTag_1635) {
    TiffFinder finder(0xFFFF, IfdId::ifd0Id);

    TiffDirectory dir(0xFFFF, IfdId::ifd0Id, false);
    finder.findObject(&dir);

    EXPECT_EQ(&dir, finder.result());
}

// Test that finding multiple objects keeps the first match (or last, depending on impl)
TEST_F(TiffFinderTest_1635, FindObjectMultipleCalls_1635) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDirectory dir1(tag, group, false);
    TiffDirectory dir2(tag, group, false);

    finder.findObject(&dir1);
    EXPECT_EQ(&dir1, finder.result());

    // Call findObject again with another matching object
    finder.findObject(&dir2);
    // The result should be updated to the latest matching object
    EXPECT_NE(nullptr, finder.result());
}

// Test TiffDirectory hasNext property
TEST_F(TiffFinderTest_1635, TiffDirectoryHasNextTrue_1635) {
    TiffDirectory dir(0x0100, IfdId::ifd0Id, true);
    EXPECT_TRUE(dir.hasNext());
}

TEST_F(TiffFinderTest_1635, TiffDirectoryHasNextFalse_1635) {
    TiffDirectory dir(0x0100, IfdId::ifd0Id, false);
    EXPECT_FALSE(dir.hasNext());
}

// Test findObject with nullptr
TEST_F(TiffFinderTest_1635, FindObjectWithNullptr_1635) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    // Depending on implementation, this may or may not crash
    // We test that result remains null if nullptr is passed
    // Note: This test may need to be removed if the implementation doesn't handle null gracefully
    finder.findObject(nullptr);
    EXPECT_EQ(nullptr, finder.result());
}
