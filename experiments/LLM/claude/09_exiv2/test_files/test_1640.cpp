#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the exiv2 project
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Test fixture for TiffFinder tests
class TiffFinderTest_1640 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that TiffFinder is constructed with tag and group, and result() is initially null
TEST_F(TiffFinderTest_1640, ConstructorInitializesResultToNull_1640) {
    TiffFinder finder(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test that init resets the finder state (result becomes null again)
TEST_F(TiffFinderTest_1640, InitResetsResult_1640) {
    TiffFinder finder(0x0001, IfdId::ifd0Id);
    // After init with different tag/group, result should still be null
    finder.init(0x0002, IfdId::exifId);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test visitBinaryElement with a matching TiffBinaryElement
TEST_F(TiffFinderTest_1640, VisitBinaryElementMatchingTagAndGroup_1640) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element(tag, group);
    TiffFinder finder(tag, group);

    finder.visitBinaryElement(&element);

    // If tag and group match, result should point to the element
    EXPECT_EQ(finder.result(), &element);
}

// Test visitBinaryElement with non-matching tag
TEST_F(TiffFinderTest_1640, VisitBinaryElementNonMatchingTag_1640) {
    uint16_t searchTag = 0x0001;
    uint16_t elementTag = 0x0002;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element(elementTag, group);
    TiffFinder finder(searchTag, group);

    finder.visitBinaryElement(&element);

    // Tag doesn't match, result should be null
    EXPECT_EQ(finder.result(), nullptr);
}

// Test visitBinaryElement with non-matching group
TEST_F(TiffFinderTest_1640, VisitBinaryElementNonMatchingGroup_1640) {
    uint16_t tag = 0x0001;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId elementGroup = IfdId::exifId;

    TiffBinaryElement element(tag, elementGroup);
    TiffFinder finder(tag, searchGroup);

    finder.visitBinaryElement(&element);

    // Group doesn't match, result should be null
    EXPECT_EQ(finder.result(), nullptr);
}

// Test visitBinaryElement with both tag and group not matching
TEST_F(TiffFinderTest_1640, VisitBinaryElementNonMatchingBoth_1640) {
    TiffBinaryElement element(0x0002, IfdId::exifId);
    TiffFinder finder(0x0001, IfdId::ifd0Id);

    finder.visitBinaryElement(&element);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test visitEntry with matching entry
TEST_F(TiffFinderTest_1640, VisitEntryMatching_1640) {
    uint16_t tag = 0x0100;
    IfdId group = IfdId::ifd0Id;

    TiffEntry entry(tag, group);
    TiffFinder finder(tag, group);

    finder.visitEntry(&entry);

    EXPECT_EQ(finder.result(), &entry);
}

// Test visitEntry with non-matching entry
TEST_F(TiffFinderTest_1640, VisitEntryNonMatching_1640) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    TiffFinder finder(0x0200, IfdId::ifd0Id);

    finder.visitEntry(&entry);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test that findObject sets the result when tag and group match
TEST_F(TiffFinderTest_1640, FindObjectSetsResultOnMatch_1640) {
    uint16_t tag = 0x0010;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element(tag, group);
    TiffFinder finder(tag, group);

    finder.findObject(&element);

    EXPECT_EQ(finder.result(), &element);
}

// Test that findObject does not set result when tag doesn't match
TEST_F(TiffFinderTest_1640, FindObjectDoesNotSetResultOnMismatch_1640) {
    TiffBinaryElement element(0x0010, IfdId::ifd0Id);
    TiffFinder finder(0x0020, IfdId::ifd0Id);

    finder.findObject(&element);

    EXPECT_EQ(finder.result(), nullptr);
}

// Test init after a successful find resets the result
TEST_F(TiffFinderTest_1640, InitAfterFindResetsResult_1640) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element(tag, group);
    TiffFinder finder(tag, group);

    finder.visitBinaryElement(&element);
    EXPECT_EQ(finder.result(), &element);

    // Re-initialize with different tag/group
    finder.init(0x9999, IfdId::exifId);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test multiple visits - second matching visit after re-init
TEST_F(TiffFinderTest_1640, MultipleVisitsWithReInit_1640) {
    uint16_t tag1 = 0x0001;
    uint16_t tag2 = 0x0002;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element1(tag1, group);
    TiffBinaryElement element2(tag2, group);

    TiffFinder finder(tag1, group);
    finder.visitBinaryElement(&element1);
    EXPECT_EQ(finder.result(), &element1);

    finder.init(tag2, group);
    finder.visitBinaryElement(&element2);
    EXPECT_EQ(finder.result(), &element2);
}

// Test visiting with zero tag
TEST_F(TiffFinderTest_1640, VisitBinaryElementZeroTag_1640) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element(tag, group);
    TiffFinder finder(tag, group);

    finder.visitBinaryElement(&element);
    EXPECT_EQ(finder.result(), &element);
}

// Test visiting with max tag value
TEST_F(TiffFinderTest_1640, VisitBinaryElementMaxTag_1640) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement element(tag, group);
    TiffFinder finder(tag, group);

    finder.visitBinaryElement(&element);
    EXPECT_EQ(finder.result(), &element);
}

// Test that visiting a non-matching element does not change a previously found result
TEST_F(TiffFinderTest_1640, NonMatchingVisitDoesNotOverwriteResult_1640) {
    uint16_t tag = 0x0001;
    IfdId group = IfdId::ifd0Id;

    TiffBinaryElement matchingElement(tag, group);
    TiffBinaryElement nonMatchingElement(0x0099, group);

    TiffFinder finder(tag, group);
    finder.visitBinaryElement(&matchingElement);
    EXPECT_EQ(finder.result(), &matchingElement);

    // Visiting a non-matching element should not change the result
    finder.visitBinaryElement(&nonMatchingElement);
    EXPECT_EQ(finder.result(), &matchingElement);
}

// Test TiffBinaryElement setElDef and elDef
TEST_F(TiffFinderTest_1640, BinaryElementSetAndGetElDef_1640) {
    TiffBinaryElement element(0x0001, IfdId::ifd0Id);

    ArrayDef def = {1, ttByte, 4};
    element.setElDef(def);

    const ArrayDef* result = element.elDef();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->idx, 1u);
    EXPECT_EQ(result->tiffType, ttByte);
    EXPECT_EQ(result->count, 4u);
}

// Test TiffBinaryElement setElByteOrder and elByteOrder
TEST_F(TiffFinderTest_1640, BinaryElementSetAndGetElByteOrder_1640) {
    TiffBinaryElement element(0x0001, IfdId::ifd0Id);

    element.setElByteOrder(bigEndian);
    EXPECT_EQ(element.elByteOrder(), bigEndian);

    element.setElByteOrder(littleEndian);
    EXPECT_EQ(element.elByteOrder(), littleEndian);
}

// Test TiffBinaryElement default byte order is invalidByteOrder
TEST_F(TiffFinderTest_1640, BinaryElementDefaultByteOrder_1640) {
    TiffBinaryElement element(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(element.elByteOrder(), invalidByteOrder);
}
