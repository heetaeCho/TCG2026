#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffFinderTest_1638 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that TiffFinder result is null when no object has been visited
TEST_F(TiffFinderTest_1638, ResultIsNullInitially_1638) {
    TiffFinder finder(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that visitIfdMakernote finds an object when tag and group match
TEST_F(TiffFinderTest_1638, VisitIfdMakernoteFindsMatchingObject_1638) {
    uint16_t tag = 0x927c;
    IfdId group = IfdId::exifId;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote(tag, group, mnGroup, nullptr, false);
    TiffFinder finder(tag, group);

    finder.visitIfdMakernote(&makernote);

    EXPECT_EQ(&makernote, finder.result());
}

// Test that visitIfdMakernote does not find an object when tag doesn't match
TEST_F(TiffFinderTest_1638, VisitIfdMakernoteDoesNotFindWhenTagMismatch_1638) {
    uint16_t objectTag = 0x927c;
    uint16_t searchTag = 0x0001;
    IfdId group = IfdId::exifId;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote(objectTag, group, mnGroup, nullptr, false);
    TiffFinder finder(searchTag, group);

    finder.visitIfdMakernote(&makernote);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that visitIfdMakernote does not find an object when group doesn't match
TEST_F(TiffFinderTest_1638, VisitIfdMakernoteDoesNotFindWhenGroupMismatch_1638) {
    uint16_t tag = 0x927c;
    IfdId objectGroup = IfdId::exifId;
    IfdId searchGroup = IfdId::ifd0Id;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote(tag, objectGroup, mnGroup, nullptr, false);
    TiffFinder finder(tag, searchGroup);

    finder.visitIfdMakernote(&makernote);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that visitIfdMakernote does not find when both tag and group mismatch
TEST_F(TiffFinderTest_1638, VisitIfdMakernoteDoesNotFindWhenBothMismatch_1638) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::olympusId, nullptr, false);
    TiffFinder finder(0x0001, IfdId::ifd0Id);

    finder.visitIfdMakernote(&makernote);

    EXPECT_EQ(nullptr, finder.result());
}

// Test that init resets the finder state
TEST_F(TiffFinderTest_1638, InitResetsFinderState_1638) {
    uint16_t tag = 0x927c;
    IfdId group = IfdId::exifId;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote(tag, group, mnGroup, nullptr, false);
    TiffFinder finder(tag, group);

    finder.visitIfdMakernote(&makernote);
    EXPECT_EQ(&makernote, finder.result());

    // Re-init with different tag/group should reset result
    finder.init(0x0001, IfdId::ifd0Id);
    EXPECT_EQ(nullptr, finder.result());
}

// Test that init allows finding a new object after reset
TEST_F(TiffFinderTest_1638, InitAllowsNewSearch_1638) {
    uint16_t tag1 = 0x927c;
    uint16_t tag2 = 0x0100;
    IfdId group1 = IfdId::exifId;
    IfdId group2 = IfdId::exifId;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote1(tag1, group1, mnGroup, nullptr, false);
    TiffIfdMakernote makernote2(tag2, group2, mnGroup, nullptr, false);

    TiffFinder finder(tag1, group1);
    finder.visitIfdMakernote(&makernote1);
    EXPECT_EQ(&makernote1, finder.result());

    finder.init(tag2, group2);
    finder.visitIfdMakernote(&makernote2);
    EXPECT_EQ(&makernote2, finder.result());
}

// Test visiting multiple objects, first match should be retained (or last, depending on implementation)
TEST_F(TiffFinderTest_1638, VisitMultipleObjectsMatchingFirst_1638) {
    uint16_t tag = 0x927c;
    IfdId group = IfdId::exifId;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote1(tag, group, mnGroup, nullptr, false);
    TiffIfdMakernote makernote2(tag, group, mnGroup, nullptr, false);

    TiffFinder finder(tag, group);
    finder.visitIfdMakernote(&makernote1);
    
    TiffComponent* firstResult = finder.result();
    EXPECT_NE(nullptr, firstResult);
    
    // Visit second matching object
    finder.visitIfdMakernote(&makernote2);
    TiffComponent* secondResult = finder.result();
    EXPECT_NE(nullptr, secondResult);
}

// Test visiting non-matching then matching object
TEST_F(TiffFinderTest_1638, VisitNonMatchingThenMatching_1638) {
    uint16_t searchTag = 0x927c;
    IfdId searchGroup = IfdId::exifId;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote nonMatching(0x0001, IfdId::ifd0Id, mnGroup, nullptr, false);
    TiffIfdMakernote matching(searchTag, searchGroup, mnGroup, nullptr, false);

    TiffFinder finder(searchTag, searchGroup);
    finder.visitIfdMakernote(&nonMatching);
    EXPECT_EQ(nullptr, finder.result());

    finder.visitIfdMakernote(&matching);
    EXPECT_EQ(&matching, finder.result());
}

// Test boundary: tag value 0
TEST_F(TiffFinderTest_1638, BoundaryTagZero_1638) {
    uint16_t tag = 0x0000;
    IfdId group = IfdId::ifd0Id;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote(tag, group, mnGroup, nullptr, false);
    TiffFinder finder(tag, group);

    finder.visitIfdMakernote(&makernote);
    EXPECT_EQ(&makernote, finder.result());
}

// Test boundary: max tag value
TEST_F(TiffFinderTest_1638, BoundaryTagMax_1638) {
    uint16_t tag = 0xFFFF;
    IfdId group = IfdId::ifd0Id;
    IfdId mnGroup = IfdId::olympusId;

    TiffIfdMakernote makernote(tag, group, mnGroup, nullptr, false);
    TiffFinder finder(tag, group);

    finder.visitIfdMakernote(&makernote);
    EXPECT_EQ(&makernote, finder.result());
}
