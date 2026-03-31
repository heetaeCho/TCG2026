#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffFinderTest_1632 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TiffFinder has a null result
TEST_F(TiffFinderTest_1632, InitialResultIsNull_1632) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject sets the result when tag and group match
TEST_F(TiffFinderTest_1632, FindObjectMatchingTagAndGroup_1632) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test that findObject does not set result when tag doesn't match
TEST_F(TiffFinderTest_1632, FindObjectNonMatchingTag_1632) {
    uint16_t searchTag = 0x0100;
    uint16_t objectTag = 0x0101;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(searchTag, group);

    TiffEntry entry(objectTag, group);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when group doesn't match
TEST_F(TiffFinderTest_1632, FindObjectNonMatchingGroup_1632) {
    uint16_t tag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId objectGroup = IfdId::ifd1Id;
    TiffFinder finder(tag, searchGroup);

    TiffEntry entry(tag, objectGroup);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does not set result when neither tag nor group match
TEST_F(TiffFinderTest_1632, FindObjectNonMatchingTagAndGroup_1632) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test init resets the finder to search for a different tag/group
TEST_F(TiffFinderTest_1632, InitResetsSearch_1632) {
    uint16_t tag1 = 0x0100;
    uint16_t tag2 = 0x0200;
    IfdId group = IfdId::ifd0Id;

    TiffFinder finder(tag1, group);

    TiffEntry entry1(tag1, group);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Re-init to search for a different tag
    finder.init(tag2, group);

    // After init, the previous result should be cleared
    // (result should be null since we haven't found the new tag yet)
    EXPECT_EQ(nullptr, finder.result());

    TiffEntry entry2(tag2, group);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());
}

// Test visitEntry delegates to findObject behavior
TEST_F(TiffFinderTest_1632, VisitEntryMatchingObject_1632) {
    uint16_t tag = 0x010F;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test visitEntry with non-matching object
TEST_F(TiffFinderTest_1632, VisitEntryNonMatchingObject_1632) {
    TiffFinder finder(0x010F, IfdId::ifd0Id);

    TiffEntry entry(0x0110, IfdId::ifd0Id);
    finder.visitEntry(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitDataEntry delegates to findObject behavior
TEST_F(TiffFinderTest_1632, VisitDataEntryMatchingObject_1632) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDataEntry dataEntry(tag, group);
    finder.visitDataEntry(&dataEntry);

    EXPECT_EQ(&dataEntry, finder.result());
}

// Test visitDataEntry with non-matching tag
TEST_F(TiffFinderTest_1632, VisitDataEntryNonMatchingObject_1632) {
    TiffFinder finder(0x0111, IfdId::ifd0Id);

    TiffDataEntry dataEntry(0x0112, IfdId::ifd0Id);
    finder.visitDataEntry(&dataEntry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitBinaryElement with matching parameters
TEST_F(TiffFinderTest_1632, VisitBinaryElementMatching_1632) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::canonCsId;
    TiffFinder finder(tag, group);

    TiffBinaryElement element(tag, group);
    finder.visitBinaryElement(&element);

    EXPECT_EQ(&element, finder.result());
}

// Test visitBinaryElement with non-matching parameters
TEST_F(TiffFinderTest_1632, VisitBinaryElementNonMatching_1632) {
    TiffFinder finder(0x0001, IfdId::canonCsId);

    TiffBinaryElement element(0x0002, IfdId::canonCsId);
    finder.visitBinaryElement(&element);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that once found, subsequent non-matching findObject calls don't overwrite result
TEST_F(TiffFinderTest_1632, FindObjectDoesNotOverwriteOnNonMatch_1632) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry matchingEntry(tag, group);
    finder.findObject(&matchingEntry);
    EXPECT_EQ(&matchingEntry, finder.result());

    TiffEntry nonMatchingEntry(0x0200, group);
    finder.findObject(&nonMatchingEntry);

    // Result should still be the first matching entry
    EXPECT_EQ(&matchingEntry, finder.result());
}

// Test with tag value 0 (boundary)
TEST_F(TiffFinderTest_1632, FindObjectWithZeroTag_1632) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test with maximum tag value (boundary)
TEST_F(TiffFinderTest_1632, FindObjectWithMaxTag_1632) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test multiple calls to init with subsequent searches
TEST_F(TiffFinderTest_1632, MultipleInitCalls_1632) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry1(0x0100, IfdId::ifd0Id);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    finder.init(0x0200, IfdId::ifd1Id);
    EXPECT_EQ(nullptr, finder.result());

    TiffEntry entry2(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());

    finder.init(0x0300, IfdId::exifId);
    EXPECT_EQ(nullptr, finder.result());
}
