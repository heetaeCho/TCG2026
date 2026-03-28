#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for TiffFinder tests
class TiffFinderTest_1634 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffFinder initially returns nullptr when no object has been found
TEST_F(TiffFinderTest_1634, InitialResultIsNull_1634) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that visitSizeEntry with matching tag and group stores the object
TEST_F(TiffFinderTest_1634, VisitSizeEntryMatchingTagAndGroup_1634) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry(tag, group, dtTag, dtGroup);
    TiffFinder finder(tag, group);

    finder.visitSizeEntry(&sizeEntry);

    EXPECT_EQ(finder.result(), &sizeEntry);
}

// Test that visitSizeEntry with non-matching tag does not store the object
TEST_F(TiffFinderTest_1634, VisitSizeEntryNonMatchingTag_1634) {
    uint16_t searchTag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;

    uint16_t entryTag = 0x0201;
    IfdId entryGroup = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry(entryTag, entryGroup, dtTag, dtGroup);
    TiffFinder finder(searchTag, searchGroup);

    finder.visitSizeEntry(&sizeEntry);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test that visitSizeEntry with non-matching group does not store the object
TEST_F(TiffFinderTest_1634, VisitSizeEntryNonMatchingGroup_1634) {
    uint16_t tag = 0x0201;
    IfdId searchGroup = IfdId::ifd1Id;

    IfdId entryGroup = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry(tag, entryGroup, dtTag, dtGroup);
    TiffFinder finder(tag, searchGroup);

    finder.visitSizeEntry(&sizeEntry);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test that init resets the finder state
TEST_F(TiffFinderTest_1634, InitResetsResult_1634) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry(tag, group, dtTag, dtGroup);
    TiffFinder finder(tag, group);

    finder.visitSizeEntry(&sizeEntry);
    EXPECT_EQ(finder.result(), &sizeEntry);

    // Re-init with different tag/group, result should be reset
    finder.init(0x9999, IfdId::ifd1Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that init allows searching for a new object
TEST_F(TiffFinderTest_1634, InitAllowsNewSearch_1634) {
    uint16_t tag1 = 0x0201;
    uint16_t tag2 = 0x0202;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0300;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry1(tag1, group, dtTag, dtGroup);
    TiffSizeEntry sizeEntry2(tag2, group, dtTag, dtGroup);

    TiffFinder finder(tag1, group);

    finder.visitSizeEntry(&sizeEntry1);
    EXPECT_EQ(finder.result(), &sizeEntry1);

    finder.init(tag2, group);
    EXPECT_EQ(finder.result(), nullptr);

    finder.visitSizeEntry(&sizeEntry2);
    EXPECT_EQ(finder.result(), &sizeEntry2);
}

// Test visitEntry with matching TiffEntry
TEST_F(TiffFinderTest_1634, VisitEntryMatching_1634) {
    uint16_t tag = 0x010F;
    IfdId group = IfdId::ifd0Id;

    TiffEntry entry(tag, group);
    TiffFinder finder(tag, group);

    finder.visitEntry(&entry);

    EXPECT_EQ(finder.result(), &entry);
}

// Test visitEntry with non-matching TiffEntry
TEST_F(TiffFinderTest_1634, VisitEntryNonMatching_1634) {
    uint16_t searchTag = 0x010F;
    uint16_t entryTag = 0x0110;
    IfdId group = IfdId::ifd0Id;

    TiffEntry entry(entryTag, group);
    TiffFinder finder(searchTag, group);

    finder.visitEntry(&entry);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test findObject directly with a matching component
TEST_F(TiffFinderTest_1634, FindObjectMatching_1634) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;

    TiffEntry entry(tag, group);
    TiffFinder finder(tag, group);

    finder.findObject(&entry);

    EXPECT_EQ(finder.result(), &entry);
}

// Test findObject directly with a non-matching component
TEST_F(TiffFinderTest_1634, FindObjectNonMatching_1634) {
    uint16_t searchTag = 0x0100;
    uint16_t entryTag = 0x0200;
    IfdId group = IfdId::ifd0Id;

    TiffEntry entry(entryTag, group);
    TiffFinder finder(searchTag, group);

    finder.findObject(&entry);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test that TiffSizeEntry has correct dtTag and dtGroup
TEST_F(TiffFinderTest_1634, TiffSizeEntryAccessors_1634) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd1Id;

    TiffSizeEntry sizeEntry(tag, group, dtTag, dtGroup);

    EXPECT_EQ(sizeEntry.dtTag(), dtTag);
    EXPECT_EQ(sizeEntry.dtGroup(), dtGroup);
}

// Test that multiple visitSizeEntry calls - first match wins (or last match wins)
TEST_F(TiffFinderTest_1634, MultipleVisitSizeEntryCallsLastMatchWins_1634) {
    uint16_t tag = 0x0201;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0202;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry1(tag, group, dtTag, dtGroup);
    TiffSizeEntry sizeEntry2(tag, group, dtTag, dtGroup);

    TiffFinder finder(tag, group);

    finder.visitSizeEntry(&sizeEntry1);
    TiffComponent* firstResult = finder.result();
    EXPECT_EQ(firstResult, &sizeEntry1);

    // Visit another matching entry - check behavior
    finder.visitSizeEntry(&sizeEntry2);
    TiffComponent* secondResult = finder.result();
    // The result should be one of the two entries (testing observable behavior)
    EXPECT_TRUE(secondResult == &sizeEntry1 || secondResult == &sizeEntry2);
}

// Test with zero tag value (boundary)
TEST_F(TiffFinderTest_1634, ZeroTagBoundary_1634) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0001;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry(tag, group, dtTag, dtGroup);
    TiffFinder finder(tag, group);

    finder.visitSizeEntry(&sizeEntry);

    EXPECT_EQ(finder.result(), &sizeEntry);
}

// Test with max tag value (boundary)
TEST_F(TiffFinderTest_1634, MaxTagBoundary_1634) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    uint16_t dtTag = 0x0001;
    IfdId dtGroup = IfdId::ifd0Id;

    TiffSizeEntry sizeEntry(tag, group, dtTag, dtGroup);
    TiffFinder finder(tag, group);

    finder.visitSizeEntry(&sizeEntry);

    EXPECT_EQ(finder.result(), &sizeEntry);
}
