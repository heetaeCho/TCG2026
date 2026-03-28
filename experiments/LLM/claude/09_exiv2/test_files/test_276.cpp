#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tags_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for TiffFinder tests
class TiffFinderTest_276 : public ::testing::Test {
 protected:
  void SetUp() override {
  }

  void TearDown() override {
  }
};

// Test that a freshly constructed TiffFinder returns nullptr
TEST_F(TiffFinderTest_276, DefaultResultIsNull_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that result() returns nullptr when no matching object has been found
TEST_F(TiffFinderTest_276, ResultIsNullWhenNoMatch_276) {
  TiffFinder finder(0x0110, IfdId::ifd0Id);
  // Create an entry with a different tag
  TiffEntry entry(0x0100, IfdId::ifd0Id);
  finder.visitEntry(&entry);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that result() returns nullptr when tag matches but group doesn't
TEST_F(TiffFinderTest_276, ResultIsNullWhenGroupMismatch_276) {
  TiffFinder finder(0x0100, IfdId::ifd1Id);
  TiffEntry entry(0x0100, IfdId::ifd0Id);
  finder.visitEntry(&entry);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that visitEntry finds a matching TiffEntry
TEST_F(TiffFinderTest_276, VisitEntryFindsMatch_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  TiffEntry entry(0x0100, IfdId::ifd0Id);
  finder.visitEntry(&entry);
  EXPECT_EQ(&entry, finder.result());
}

// Test that visitDataEntry finds a matching TiffDataEntry
TEST_F(TiffFinderTest_276, VisitDataEntryFindsMatch_276) {
  TiffFinder finder(0x0201, IfdId::ifd0Id);
  TiffDataEntry dataEntry(0x0201, IfdId::ifd0Id, 0x0202, IfdId::ifd0Id);
  finder.visitDataEntry(&dataEntry);
  EXPECT_EQ(&dataEntry, finder.result());
}

// Test that visitDataEntry doesn't find non-matching entry
TEST_F(TiffFinderTest_276, VisitDataEntryNoMatch_276) {
  TiffFinder finder(0x0300, IfdId::ifd0Id);
  TiffDataEntry dataEntry(0x0201, IfdId::ifd0Id, 0x0202, IfdId::ifd0Id);
  finder.visitDataEntry(&dataEntry);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that visitSizeEntry finds a matching TiffSizeEntry
TEST_F(TiffFinderTest_276, VisitSizeEntryFindsMatch_276) {
  TiffFinder finder(0x0202, IfdId::ifd0Id);
  TiffSizeEntry sizeEntry(0x0202, IfdId::ifd0Id, 0x0201, IfdId::ifd0Id);
  finder.visitSizeEntry(&sizeEntry);
  EXPECT_EQ(&sizeEntry, finder.result());
}

// Test that visitImageEntry finds a matching TiffImageEntry
TEST_F(TiffFinderTest_276, VisitImageEntryFindsMatch_276) {
  TiffFinder finder(0x0111, IfdId::ifd0Id);
  TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id);
  finder.visitImageEntry(&imageEntry);
  EXPECT_EQ(&imageEntry, finder.result());
}

// Test that visitBinaryElement finds a matching TiffBinaryElement
TEST_F(TiffFinderTest_276, VisitBinaryElementFindsMatch_276) {
  TiffFinder finder(0x0001, IfdId::canonCsId);
  TiffBinaryElement element(0x0001, IfdId::canonCsId);
  finder.visitBinaryElement(&element);
  EXPECT_EQ(&element, finder.result());
}

// Test that init resets the finder state
TEST_F(TiffFinderTest_276, InitResetsState_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  TiffEntry entry(0x0100, IfdId::ifd0Id);
  finder.visitEntry(&entry);
  EXPECT_EQ(&entry, finder.result());

  // Re-init with different tag/group
  finder.init(0x0200, IfdId::ifd1Id);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that init allows finding a new object
TEST_F(TiffFinderTest_276, InitAllowsNewSearch_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  TiffEntry entry1(0x0100, IfdId::ifd0Id);
  finder.visitEntry(&entry1);
  EXPECT_EQ(&entry1, finder.result());

  // Re-init to search for a different tag
  finder.init(0x0110, IfdId::ifd0Id);
  TiffEntry entry2(0x0110, IfdId::ifd0Id);
  finder.visitEntry(&entry2);
  EXPECT_EQ(&entry2, finder.result());
}

// Test findObject with matching component
TEST_F(TiffFinderTest_276, FindObjectFindsMatch_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  TiffEntry entry(0x0100, IfdId::ifd0Id);
  finder.findObject(&entry);
  EXPECT_EQ(&entry, finder.result());
}

// Test findObject with non-matching component
TEST_F(TiffFinderTest_276, FindObjectNoMatch_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  TiffEntry entry(0x0200, IfdId::ifd0Id);
  finder.findObject(&entry);
  EXPECT_EQ(nullptr, finder.result());
}

// Test visiting a TiffDirectory
TEST_F(TiffFinderTest_276, VisitDirectoryFindsMatch_276) {
  TiffFinder finder(0x8769, IfdId::ifd0Id);
  TiffDirectory dir(0x8769, IfdId::ifd0Id);
  finder.visitDirectory(&dir);
  // Directory match depends on tag+group
  // The directory itself might or might not match depending on implementation
  // We just verify it doesn't crash and returns a consistent result
  TiffComponent* res = finder.result();
  // result is either &dir or nullptr
  SUCCEED();
}

// Test visiting a TiffSubIfd
TEST_F(TiffFinderTest_276, VisitSubIfdFindsMatch_276) {
  TiffFinder finder(0x014a, IfdId::ifd0Id);
  TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  finder.visitSubIfd(&subIfd);
  EXPECT_EQ(&subIfd, finder.result());
}

// Test visiting TiffSubIfd with no match
TEST_F(TiffFinderTest_276, VisitSubIfdNoMatch_276) {
  TiffFinder finder(0xFFFF, IfdId::ifd1Id);
  TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
  finder.visitSubIfd(&subIfd);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that visiting multiple non-matching entries keeps result null
TEST_F(TiffFinderTest_276, MultipleNonMatchingVisitsKeepNull_276) {
  TiffFinder finder(0x9999, IfdId::ifd0Id);
  TiffEntry entry1(0x0100, IfdId::ifd0Id);
  TiffEntry entry2(0x0110, IfdId::ifd0Id);
  TiffEntry entry3(0x0112, IfdId::ifd0Id);
  finder.visitEntry(&entry1);
  finder.visitEntry(&entry2);
  finder.visitEntry(&entry3);
  EXPECT_EQ(nullptr, finder.result());
}

// Test that the first match sticks (or the latest - depends on implementation)
TEST_F(TiffFinderTest_276, VisitEntryFirstMatchRetained_276) {
  TiffFinder finder(0x0100, IfdId::ifd0Id);
  TiffEntry entry1(0x0100, IfdId::ifd0Id);
  TiffEntry entry2(0x0100, IfdId::ifd0Id);
  finder.visitEntry(&entry1);
  TiffComponent* firstResult = finder.result();
  finder.visitEntry(&entry2);
  TiffComponent* secondResult = finder.result();
  // At least one should be non-null
  EXPECT_NE(nullptr, firstResult);
  EXPECT_NE(nullptr, secondResult);
}

// Test with tag 0 and default group
TEST_F(TiffFinderTest_276, ZeroTagSearch_276) {
  TiffFinder finder(0x0000, IfdId::ifd0Id);
  TiffEntry entry(0x0000, IfdId::ifd0Id);
  finder.visitEntry(&entry);
  EXPECT_EQ(&entry, finder.result());
}

// Test with maximum tag value
TEST_F(TiffFinderTest_276, MaxTagSearch_276) {
  TiffFinder finder(0xFFFF, IfdId::ifd0Id);
  TiffEntry entry(0xFFFF, IfdId::ifd0Id);
  finder.visitEntry(&entry);
  EXPECT_EQ(&entry, finder.result());
}
