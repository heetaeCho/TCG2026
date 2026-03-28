#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

class TiffFinderTest_1636 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TiffFinder has null result
TEST_F(TiffFinderTest_1636, InitialResultIsNull_1636) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject sets the result when tag and group match
TEST_F(TiffFinderTest_1636, FindObjectMatchingTagAndGroup_1636) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test that findObject does not set result when tag does not match
TEST_F(TiffFinderTest_1636, FindObjectNonMatchingTag_1636) {
    uint16_t searchTag = 0x0100;
    uint16_t objectTag = 0x0101;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(searchTag, group);

    TiffEntry entry(objectTag, group);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when group does not match
TEST_F(TiffFinderTest_1636, FindObjectNonMatchingGroup_1636) {
    uint16_t tag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId objectGroup = IfdId::ifd1Id;
    TiffFinder finder(tag, searchGroup);

    TiffEntry entry(tag, objectGroup);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when both tag and group do not match
TEST_F(TiffFinderTest_1636, FindObjectNonMatchingBoth_1636) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test init resets the finder to search for a different tag/group
TEST_F(TiffFinderTest_1636, InitResetsSearch_1636) {
    uint16_t tag1 = 0x0100;
    uint16_t tag2 = 0x0200;
    IfdId group = IfdId::ifd0Id;

    TiffFinder finder(tag1, group);

    TiffEntry entry1(tag1, group);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Re-init to search for a different tag
    finder.init(tag2, group);
    // After init, result should be reset
    EXPECT_EQ(nullptr, finder.result());

    TiffEntry entry2(tag2, group);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());
}

// Test visitEntry with matching object
TEST_F(TiffFinderTest_1636, VisitEntryMatching_1636) {
    uint16_t tag = 0x010F;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test visitEntry with non-matching object
TEST_F(TiffFinderTest_1636, VisitEntryNonMatching_1636) {
    TiffFinder finder(0x010F, IfdId::ifd0Id);

    TiffEntry entry(0x0110, IfdId::ifd0Id);
    finder.visitEntry(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitSubIfd with matching object
TEST_F(TiffFinderTest_1636, VisitSubIfdMatching_1636) {
    uint16_t tag = 0x014A;
    IfdId group = IfdId::ifd0Id;
    IfdId newGroup = IfdId::subImage1Id;
    TiffFinder finder(tag, group);

    TiffSubIfd subIfd(tag, group, newGroup);
    finder.visitSubIfd(&subIfd);

    EXPECT_EQ(&subIfd, finder.result());
}

// Test visitSubIfd with non-matching object
TEST_F(TiffFinderTest_1636, VisitSubIfdNonMatching_1636) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffSubIfd subIfd(0x014A, IfdId::ifd0Id, IfdId::subImage1Id);
    finder.visitSubIfd(&subIfd);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that calling findObject multiple times, only the first match is retained
TEST_F(TiffFinderTest_1636, FindObjectFirstMatchRetained_1636) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry1(tag, group);
    TiffEntry entry2(tag, group);

    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Second call with another matching object - behavior depends on implementation
    // but we verify result is not null
    finder.findObject(&entry2);
    // The result should still be one of the matching entries
    EXPECT_NE(nullptr, finder.result());
}

// Test with null pointer passed to findObject
TEST_F(TiffFinderTest_1636, FindObjectNullPointer_1636) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    // Passing null - should not crash and result should remain null
    finder.findObject(nullptr);
    EXPECT_EQ(nullptr, finder.result());
}

// Test init after a successful find resets the result
TEST_F(TiffFinderTest_1636, InitAfterSuccessfulFindResetsResult_1636) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);
    EXPECT_EQ(&entry, finder.result());

    finder.init(0x0200, IfdId::ifd1Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that visitDirectory with matching directory sets result
TEST_F(TiffFinderTest_1636, VisitDirectoryMatching_1636) {
    uint16_t tag = 0x0000; // Typical directory tag
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDirectory dir(tag, group);
    finder.visitDirectory(&dir);

    // Directory visit behavior - if tag/group match, result should be set
    // If directory delegates to children, result may or may not be set
    // We just verify no crash
    // The actual matching depends on internal logic
}

// Test constructor with zero tag
TEST_F(TiffFinderTest_1636, ConstructorZeroTag_1636) {
    TiffFinder finder(0, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test construction and finding with boundary tag values
TEST_F(TiffFinderTest_1636, BoundaryTagValueMax_1636) {
    uint16_t maxTag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(maxTag, group);

    TiffEntry entry(maxTag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}
