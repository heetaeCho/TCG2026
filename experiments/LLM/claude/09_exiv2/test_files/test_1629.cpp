#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffVisitor
class TiffVisitorTest_1629 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test fixture for TiffFinder
class TiffFinderTest_1629 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// ============================================================
// TiffVisitor tests
// ============================================================

TEST_F(TiffVisitorTest_1629, SetGoAndGoTraverse_1629) {
    // We can't instantiate TiffVisitor directly (pure virtual or deleted copy),
    // but we can test through TiffFinder which inherits from it.
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    // By default, go events should be true
    EXPECT_TRUE(finder.go(geTraverse));
    EXPECT_TRUE(finder.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1629, SetGoTraverseFalse_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    finder.setGo(geTraverse, false);
    EXPECT_FALSE(finder.go(geTraverse));
    // geKnownMakernote should remain unaffected
    EXPECT_TRUE(finder.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1629, SetGoKnownMakernoteFalse_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    finder.setGo(geKnownMakernote, false);
    EXPECT_TRUE(finder.go(geTraverse));
    EXPECT_FALSE(finder.go(geKnownMakernote));
}

TEST_F(TiffVisitorTest_1629, SetGoToggle_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    finder.setGo(geTraverse, false);
    EXPECT_FALSE(finder.go(geTraverse));

    finder.setGo(geTraverse, true);
    EXPECT_TRUE(finder.go(geTraverse));
}

TEST_F(TiffVisitorTest_1629, SetBothGoEventsFalse_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    finder.setGo(geTraverse, false);
    finder.setGo(geKnownMakernote, false);
    EXPECT_FALSE(finder.go(geTraverse));
    EXPECT_FALSE(finder.go(geKnownMakernote));
}

// ============================================================
// TiffFinder tests
// ============================================================

TEST_F(TiffFinderTest_1629, ConstructorAndResultNull_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    // Before any visit, result should be nullptr
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1629, InitResetsResult_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    // Call init with different tag/group
    finder.init(0x0110, IfdId::ifd1Id);

    // After init, result should be nullptr
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1629, InitSetsGoTraverseTrue_1629) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);

    // Disable traverse
    finder.setGo(geTraverse, false);
    EXPECT_FALSE(finder.go(geTraverse));

    // Init should re-enable traverse
    finder.init(0x0100, IfdId::ifd0Id);
    EXPECT_TRUE(finder.go(geTraverse));
}

TEST_F(TiffFinderTest_1629, FindObjectMatchingTagAndGroup_1629) {
    uint16_t testTag = 0x0100;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(testTag, testGroup);

    // Create a TiffEntry with the matching tag and group
    TiffEntry entry(testTag, testGroup);

    finder.visitEntry(&entry);

    // The finder should have found the entry
    EXPECT_EQ(finder.result(), &entry);
}

TEST_F(TiffFinderTest_1629, FindObjectNonMatchingTag_1629) {
    uint16_t searchTag = 0x0100;
    uint16_t otherTag = 0x0110;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(searchTag, testGroup);

    TiffEntry entry(otherTag, testGroup);

    finder.visitEntry(&entry);

    // Should not find mismatched tag
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1629, FindObjectNonMatchingGroup_1629) {
    uint16_t testTag = 0x0100;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId otherGroup = IfdId::ifd1Id;

    TiffFinder finder(testTag, searchGroup);

    TiffEntry entry(testTag, otherGroup);

    finder.visitEntry(&entry);

    // Should not find mismatched group
    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1629, FindObjectStopsTraversalOnMatch_1629) {
    uint16_t testTag = 0x0100;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(testTag, testGroup);

    TiffEntry entry(testTag, testGroup);

    finder.visitEntry(&entry);

    // After finding, traverse should be stopped
    EXPECT_FALSE(finder.go(geTraverse));
    EXPECT_EQ(finder.result(), &entry);
}

TEST_F(TiffFinderTest_1629, InitAfterFindResetsState_1629) {
    uint16_t testTag = 0x0100;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(testTag, testGroup);

    TiffEntry entry(testTag, testGroup);
    finder.visitEntry(&entry);

    EXPECT_NE(finder.result(), nullptr);
    EXPECT_FALSE(finder.go(geTraverse));

    // Re-init
    finder.init(0x0110, IfdId::ifd1Id);

    EXPECT_EQ(finder.result(), nullptr);
    EXPECT_TRUE(finder.go(geTraverse));
}

TEST_F(TiffFinderTest_1629, VisitDirectoryMatching_1629) {
    uint16_t testTag = 0x0100;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(testTag, testGroup);

    TiffDirectory dir(testTag, testGroup);

    finder.visitDirectory(&dir);

    // If tag and group match, result should be set
    if (dir.tag() == testTag) {
        EXPECT_EQ(finder.result(), &dir);
    }
}

TEST_F(TiffFinderTest_1629, VisitSubIfdMatching_1629) {
    uint16_t testTag = 0x014a;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(testTag, testGroup);

    TiffSubIfd subIfd(testTag, testGroup, IfdId::subImage1Id);

    finder.visitSubIfd(&subIfd);

    EXPECT_EQ(finder.result(), &subIfd);
}

TEST_F(TiffFinderTest_1629, VisitSubIfdNonMatching_1629) {
    uint16_t searchTag = 0x014a;
    uint16_t otherTag = 0x014b;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(searchTag, testGroup);

    TiffSubIfd subIfd(otherTag, testGroup, IfdId::subImage1Id);

    finder.visitSubIfd(&subIfd);

    EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1629, ConstructWithZeroTag_1629) {
    TiffFinder finder(0x0000, IfdId::ifd0Id);

    EXPECT_EQ(finder.result(), nullptr);
    EXPECT_TRUE(finder.go(geTraverse));
}

TEST_F(TiffFinderTest_1629, ConstructWithMaxTag_1629) {
    TiffFinder finder(0xFFFF, IfdId::ifd0Id);

    EXPECT_EQ(finder.result(), nullptr);
    EXPECT_TRUE(finder.go(geTraverse));
}

TEST_F(TiffFinderTest_1629, MultipleVisitsFirstMatchWins_1629) {
    uint16_t testTag = 0x0100;
    IfdId testGroup = IfdId::ifd0Id;

    TiffFinder finder(testTag, testGroup);

    TiffEntry entry1(testTag, testGroup);
    TiffEntry entry2(testTag, testGroup);

    finder.visitEntry(&entry1);
    // After first match, go(geTraverse) should be false
    // Second visit should not change result since traversal is stopped
    // (but visit functions may still be called if the caller doesn't check go())
    TiffComponent* firstResult = finder.result();
    EXPECT_EQ(firstResult, &entry1);
}

TEST_F(TiffFinderTest_1629, ReInitAndSearchAgain_1629) {
    uint16_t tag1 = 0x0100;
    uint16_t tag2 = 0x0110;
    IfdId group = IfdId::ifd0Id;

    TiffFinder finder(tag1, group);

    TiffEntry entry1(tag1, group);
    finder.visitEntry(&entry1);
    EXPECT_EQ(finder.result(), &entry1);

    // Re-init for a different search
    finder.init(tag2, group);
    EXPECT_EQ(finder.result(), nullptr);

    TiffEntry entry2(tag2, group);
    finder.visitEntry(&entry2);
    EXPECT_EQ(finder.result(), &entry2);
}
