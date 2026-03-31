#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffFinder tests
class TiffFinderTest_1633 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TiffFinder returns nullptr when no search has been done
TEST_F(TiffFinderTest_1633, InitialResultIsNull_1633) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject sets the result when tag and group match
TEST_F(TiffFinderTest_1633, FindObjectMatchingTagAndGroup_1633) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test that findObject does not set result when tag does not match
TEST_F(TiffFinderTest_1633, FindObjectNonMatchingTag_1633) {
    uint16_t searchTag = 0x0100;
    uint16_t otherTag = 0x0101;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(searchTag, group);

    TiffEntry entry(otherTag, group);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when group does not match
TEST_F(TiffFinderTest_1633, FindObjectNonMatchingGroup_1633) {
    uint16_t tag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId otherGroup = IfdId::ifd1Id;
    TiffFinder finder(tag, searchGroup);

    TiffEntry entry(tag, otherGroup);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that init resets the finder to search for a different tag/group
TEST_F(TiffFinderTest_1633, InitResetsSearch_1633) {
    uint16_t tag1 = 0x0100;
    uint16_t tag2 = 0x0101;
    IfdId group = IfdId::ifd0Id;

    TiffFinder finder(tag1, group);

    // First, find an object with tag1
    TiffEntry entry1(tag1, group);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Now re-init to search for tag2
    finder.init(tag2, group);
    // After init, result should be reset
    EXPECT_EQ(nullptr, finder.result());

    // Find with tag2
    TiffEntry entry2(tag2, group);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());
}

// Test visitEntry delegates to findObject logic
TEST_F(TiffFinderTest_1633, VisitEntryMatchingObject_1633) {
    uint16_t tag = 0x010F;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test visitEntry with non-matching does not set result
TEST_F(TiffFinderTest_1633, VisitEntryNonMatchingObject_1633) {
    uint16_t tag = 0x010F;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(0x0110, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitImageEntry with matching tag and group
TEST_F(TiffFinderTest_1633, VisitImageEntryMatching_1633) {
    uint16_t tag = 0x0111; // StripOffsets
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffImageEntry imageEntry(tag, group);
    finder.visitImageEntry(&imageEntry);

    EXPECT_EQ(&imageEntry, finder.result());
}

// Test visitImageEntry with non-matching tag
TEST_F(TiffFinderTest_1633, VisitImageEntryNonMatching_1633) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffImageEntry imageEntry(0x0112, group);
    finder.visitImageEntry(&imageEntry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitDataEntry with matching object
TEST_F(TiffFinderTest_1633, VisitDataEntryMatching_1633) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDataEntry dataEntry(tag, group);
    finder.visitDataEntry(&dataEntry);

    EXPECT_EQ(&dataEntry, finder.result());
}

// Test visitDataEntry with non-matching object
TEST_F(TiffFinderTest_1633, VisitDataEntryNonMatching_1633) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDataEntry dataEntry(0x0202, group);
    finder.visitDataEntry(&dataEntry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitSizeEntry with matching object
TEST_F(TiffFinderTest_1633, VisitSizeEntryMatching_1633) {
    uint16_t tag = 0x0202;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffSizeEntry sizeEntry(tag, group);
    finder.visitSizeEntry(&sizeEntry);

    EXPECT_EQ(&sizeEntry, finder.result());
}

// Test that once a match is found, subsequent non-matching calls don't overwrite result
TEST_F(TiffFinderTest_1633, FoundResultNotOverwrittenByNonMatch_1633) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry matchingEntry(tag, group);
    finder.findObject(&matchingEntry);
    EXPECT_EQ(&matchingEntry, finder.result());

    // Now try to find with a non-matching entry
    TiffEntry nonMatchingEntry(0x0101, group);
    finder.findObject(&nonMatchingEntry);

    // Result should still be the first match (or possibly overwritten to null depending on impl)
    // Since we treat as black box, we just check it's either still the match or null
    // Most likely the finder keeps the first match
    TiffComponent* res = finder.result();
    // The result should still be the matching entry since the second didn't match
    EXPECT_EQ(&matchingEntry, res);
}

// Test boundary: tag value 0
TEST_F(TiffFinderTest_1633, TagValueZero_1633) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test boundary: maximum tag value
TEST_F(TiffFinderTest_1633, TagValueMax_1633) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test multiple inits and searches
TEST_F(TiffFinderTest_1633, MultipleInitAndSearch_1633) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry1(0x0100, IfdId::ifd0Id);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    finder.init(0x0200, IfdId::ifd1Id);
    EXPECT_EQ(nullptr, finder.result());

    TiffEntry entry2(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());

    finder.init(0x0300, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}
