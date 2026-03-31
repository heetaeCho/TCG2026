#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

class TiffFinderTest_1637 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffFinder returns nullptr when no object has been found
TEST_F(TiffFinderTest_1637, ResultIsNullInitially_1637) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject sets result when tag and group match
TEST_F(TiffFinderTest_1637, FindObjectMatchingTagAndGroup_1637) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test that findObject does NOT set result when tag doesn't match
TEST_F(TiffFinderTest_1637, FindObjectNonMatchingTag_1637) {
    uint16_t searchTag = 0x0100;
    uint16_t objectTag = 0x0101;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(searchTag, group);

    TiffEntry entry(objectTag, group);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does NOT set result when group doesn't match
TEST_F(TiffFinderTest_1637, FindObjectNonMatchingGroup_1637) {
    uint16_t tag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId objectGroup = IfdId::ifd1Id;
    TiffFinder finder(tag, searchGroup);

    TiffEntry entry(tag, objectGroup);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject does NOT set result when neither tag nor group match
TEST_F(TiffFinderTest_1637, FindObjectNeitherMatch_1637) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that init resets the finder state
TEST_F(TiffFinderTest_1637, InitResetsState_1637) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.findObject(&entry);
    EXPECT_EQ(&entry, finder.result());

    // Re-init with different tag/group - result should be reset
    finder.init(0x0200, IfdId::ifd1Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that init allows finding a new object with new criteria
TEST_F(TiffFinderTest_1637, InitAllowsNewSearch_1637) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffEntry entry1(0x0100, IfdId::ifd0Id);
    finder.findObject(&entry1);
    EXPECT_EQ(&entry1, finder.result());

    // Re-init with new search criteria
    finder.init(0x0200, IfdId::ifd1Id);

    TiffEntry entry2(0x0200, IfdId::ifd1Id);
    finder.findObject(&entry2);
    EXPECT_EQ(&entry2, finder.result());
}

// Test visitEntry with matching object
TEST_F(TiffFinderTest_1637, VisitEntryMatching_1637) {
    uint16_t tag = 0x0110;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry(tag, group);
    finder.visitEntry(&entry);

    EXPECT_EQ(&entry, finder.result());
}

// Test visitEntry with non-matching object
TEST_F(TiffFinderTest_1637, VisitEntryNonMatching_1637) {
    TiffFinder finder(0x0110, IfdId::ifd0Id);

    TiffEntry entry(0x0111, IfdId::ifd0Id);
    finder.visitEntry(&entry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitMnEntry with matching TiffMnEntry
TEST_F(TiffFinderTest_1637, VisitMnEntryMatching_1637) {
    uint16_t tag = 0x927c;
    IfdId group = IfdId::ifd0Id;
    IfdId mnGroup = IfdId::canonId;
    TiffFinder finder(tag, group);

    TiffMnEntry mnEntry(tag, group, mnGroup);
    finder.visitMnEntry(&mnEntry);

    EXPECT_EQ(&mnEntry, finder.result());
}

// Test visitMnEntry with non-matching TiffMnEntry
TEST_F(TiffFinderTest_1637, VisitMnEntryNonMatching_1637) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffMnEntry mnEntry(0x927c, IfdId::ifd0Id, IfdId::canonId);
    finder.visitMnEntry(&mnEntry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that findObject with nullptr doesn't crash (defensive)
TEST_F(TiffFinderTest_1637, FindObjectWithNullptr_1637) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    // Passing nullptr - should not crash, result should remain null
    finder.findObject(nullptr);
    EXPECT_EQ(nullptr, finder.result());
}

// Test multiple findObject calls - first match should stick (or last match wins)
TEST_F(TiffFinderTest_1637, MultipleFindObjectCalls_1637) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffEntry entry1(tag, group);
    TiffEntry entry2(tag, group);

    finder.findObject(&entry1);
    TiffComponent* firstResult = finder.result();
    EXPECT_EQ(&entry1, firstResult);

    // Call findObject again with another matching entry
    finder.findObject(&entry2);
    TiffComponent* secondResult = finder.result();
    // The result might be the first or second - we just verify it's not null
    EXPECT_NE(nullptr, secondResult);
}

// Test with tag = 0 (boundary)
TEST_F(TiffFinderTest_1637, ZeroTag_1637) {
    TiffFinder finder(0, IfdId::ifd0Id);
    TiffEntry entry(0, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(&entry, finder.result());
}

// Test with max tag value (boundary)
TEST_F(TiffFinderTest_1637, MaxTag_1637) {
    uint16_t maxTag = 0xFFFF;
    TiffFinder finder(maxTag, IfdId::ifd0Id);
    TiffEntry entry(maxTag, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(&entry, finder.result());
}

// Test visitDataEntry with matching object
TEST_F(TiffFinderTest_1637, VisitDataEntryMatching_1637) {
    uint16_t tag = 0x0111;
    IfdId group = IfdId::ifd0Id;
    TiffFinder finder(tag, group);

    TiffDataEntry dataEntry(tag, group, 0x0117, IfdId::ifd0Id);
    finder.visitDataEntry(&dataEntry);

    EXPECT_EQ(&dataEntry, finder.result());
}

// Test visitDataEntry with non-matching object
TEST_F(TiffFinderTest_1637, VisitDataEntryNonMatching_1637) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    TiffDataEntry dataEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    finder.visitDataEntry(&dataEntry);

    EXPECT_EQ(nullptr, finder.result());
}

// Test visitBinaryElement with matching object
TEST_F(TiffFinderTest_1637, VisitBinaryElementMatching_1637) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::canonCsId;
    TiffFinder finder(tag, group);

    TiffBinaryElement elem(tag, group);
    finder.visitBinaryElement(&elem);

    EXPECT_EQ(&elem, finder.result());
}

// Test visitBinaryElement with non-matching object
TEST_F(TiffFinderTest_1637, VisitBinaryElementNonMatching_1637) {
    TiffFinder finder(0x0002, IfdId::canonCsId);

    TiffBinaryElement elem(0x0001, IfdId::canonCsId);
    finder.visitBinaryElement(&elem);

    EXPECT_EQ(nullptr, finder.result());
}
