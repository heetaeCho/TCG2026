#include <gtest/gtest.h>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

class TiffFinderTest_1631 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TiffFinder has null result
TEST_F(TiffFinderTest_1631, InitialResultIsNull_1631) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject sets result when tag and group match
TEST_F(TiffFinderTest_1631, FindObjectMatchingTagAndGroup_1631) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test that findObject does not set result when tag doesn't match
TEST_F(TiffFinderTest_1631, FindObjectNonMatchingTag_1631) {
    uint16_t searchTag = 0x0100;
    uint16_t entryTag = 0x0101;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(searchTag, group);

    TiffEntry entry(entryTag, group);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when group doesn't match
TEST_F(TiffFinderTest_1631, FindObjectNonMatchingGroup_1631) {
    uint16_t tag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId entryGroup = IfdId::ifd1Id;
    TiffFinder finder(tag, searchGroup);

    TiffEntry entry(tag, entryGroup);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when neither tag nor group match
TEST_F(TiffFinderTest_1631, FindObjectNonMatchingTagAndGroup_1631) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitEntry with matching tag and group
TEST_F(TiffFinderTest_1631, VisitEntryMatchingTagAndGroup_1631) {
    uint16_t tag = 0x0110;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test visitEntry with non-matching entry
TEST_F(TiffFinderTest_1631, VisitEntryNonMatching_1631) {
    TiffFinder finder(0x0110, IfdId::ifd0Id);

    TiffEntry entry(0x0111, IfdId::ifd0Id);
    finder.visitEntry(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test init resets the finder to search for a different tag/group
TEST_F(TiffFinderTest_1631, InitResetsSearch_1631) {
    uint16_t tag1 = 0x0100;
    uint16_t tag2 = 0x0200;
    IfdId group = IfdId::ifd0Id;

    TiffFinder finder(tag1, group);

    TiffEntry entry1(tag1, group);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Re-initialize to search for a different tag
    finder.init(tag2, group);
    EXPECT_EQ(nullptr, finder.result());

    TiffEntry entry2(tag2, group);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());
}

// Test that init clears a previously found result
TEST_F(TiffFinderTest_1631, InitClearsPreviousResult_1631) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);
    EXPECT_NE(nullptr, finder.result());

    finder.init(0x9999, IfdId::ifd1Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test with tag value of 0
TEST_F(TiffFinderTest_1631, ZeroTagSearch_1631) {
    TiffFinder finder(0x0000, IfdId::ifd0Id);

    TiffEntry entry(0x0000, IfdId::ifd0Id);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test with max uint16 tag value
TEST_F(TiffFinderTest_1631, MaxTagSearch_1631) {
    TiffFinder finder(0xFFFF, IfdId::ifd0Id);

    TiffEntry entry(0xFFFF, IfdId::ifd0Id);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test that multiple findObject calls - first match sticks (or last match wins)
TEST_F(TiffFinderTest_1631, MultipleFindObjectCalls_1631) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry1(tag, group);
    TiffEntry entry2(tag, group);

    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Call findObject again with another matching entry
    finder.findObject(&entry2);
    // The result should still be one of them - we check it's not null
    EXPECT_NE(nullptr, finder.result());
}

// Test findObject with non-matching then matching
TEST_F(TiffFinderTest_1631, FindObjectNonMatchingThenMatching_1631) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry nonMatchEntry(0x0200, group);
    finder.findObject(&nonMatchEntry);
    EXPECT_EQ(nullptr, finder.result());

    TiffEntry matchEntry(tag, group);
    finder.findObject(&matchEntry);
    EXPECT_EQ(&matchEntry, finder.result());
}

// Test visitDirectory with a TiffDirectory
TEST_F(TiffFinderTest_1631, VisitDirectoryNonMatching_1631) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffDirectory dir(0x0200, IfdId::ifd1Id);
    finder.visitDirectory(&dir);

    // If the directory doesn't match tag/group, result should be null
    // (Directory might also recurse into children, but with an empty directory, no match)
    // We just verify no crash and result behavior
}

// Test visiting a TiffBinaryElement
TEST_F(TiffFinderTest_1631, VisitBinaryElementMatching_1631) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffBinaryElement element(tag, group);
    finder.visitBinaryElement(&element);

    EXPECT_EQ(&element, finder.result());
}

// Test visiting a TiffBinaryElement non-matching
TEST_F(TiffFinderTest_1631, VisitBinaryElementNonMatching_1631) {
    TiffFinder finder(0x0001, IfdId::ifd0Id);

    TiffBinaryElement element(0x0002, IfdId::ifd0Id);
    finder.visitBinaryElement(&element);

    EXPECT_EQ(nullptr, finder.result());
}
