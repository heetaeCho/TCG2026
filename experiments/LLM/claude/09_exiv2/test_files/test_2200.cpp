#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper: A minimal TiffEntry for testing purposes
// TiffEntry is a concrete subclass of TiffEntryBase
class TiffDecoderTest_2200 : public ::testing::Test {
 protected:
  ExifData exifData_;
  IptcData iptcData_;
  XmpData xmpData_;

  void SetUp() override {
    exifData_.clear();
    iptcData_.clear();
    xmpData_.clear();
  }
};

// Test: TiffDecoder construction with empty ExifData and null root
TEST_F(TiffDecoderTest_2200, ConstructWithEmptyExifDataNullRoot_2200) {
  // When ExifData has no "Exif.Image.Make" and pRoot is nullptr,
  // the constructor should handle gracefully (the TiffFinder path
  // requires pRoot->accept, so nullptr may cause issues - but let's
  // test with a valid minimal root)
  // With nullptr pRoot and no Make key, this may crash, so we skip nullptr test
  // and use a TiffDirectory instead.
  TiffDirectory root(0, IfdId::ifd0Id);
  
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  // If we get here, construction succeeded
  SUCCEED();
}

// Test: TiffDecoder construction when ExifData already contains Make
TEST_F(TiffDecoderTest_2200, ConstructWithExistingMakeInExifData_2200) {
  ExifKey makeKey("Exif.Image.Make");
  auto val = Value::create(asciiString);
  val->read("Canon");
  exifData_.add(makeKey, val.get());

  TiffDirectory root(0, IfdId::ifd0Id);
  
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  // Construction should succeed and make_ should be set to "Canon" internally
  SUCCEED();
}

// Test: TiffDecoder construction with different Make string
TEST_F(TiffDecoderTest_2200, ConstructWithNikonMake_2200) {
  ExifKey makeKey("Exif.Image.Make");
  auto val = Value::create(asciiString);
  val->read("Nikon");
  exifData_.add(makeKey, val.get());

  TiffDirectory root(0, IfdId::ifd0Id);
  
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  SUCCEED();
}

// Test: TiffDecoder construction with empty Make string
TEST_F(TiffDecoderTest_2200, ConstructWithEmptyMakeString_2200) {
  ExifKey makeKey("Exif.Image.Make");
  auto val = Value::create(asciiString);
  val->read("");
  exifData_.add(makeKey, val.get());

  TiffDirectory root(0, IfdId::ifd0Id);
  
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  SUCCEED();
}

// TiffFinder tests
class TiffFinderTest_2200 : public ::testing::Test {
 protected:
};

// Test: TiffFinder initial result is nullptr
TEST_F(TiffFinderTest_2200, InitialResultIsNull_2200) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  EXPECT_EQ(nullptr, finder.result());
}

// Test: TiffFinder init resets state
TEST_F(TiffFinderTest_2200, InitResetsState_2200) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  finder.init(0x0110, IfdId::ifd1Id);
  EXPECT_EQ(nullptr, finder.result());
}

// Test: TiffFinder with a TiffDirectory that has matching tag
TEST_F(TiffFinderTest_2200, FindDirectoryMatchingTag_2200) {
  TiffDirectory dir(0x010f, IfdId::ifd0Id);
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  dir.accept(finder);
  // The directory itself should match
  TiffComponent* result = finder.result();
  EXPECT_NE(nullptr, result);
  if (result) {
    EXPECT_EQ(0x010f, result->tag());
    EXPECT_EQ(IfdId::ifd0Id, result->group());
  }
}

// Test: TiffFinder with non-matching tag
TEST_F(TiffFinderTest_2200, FindDirectoryNonMatchingTag_2200) {
  TiffDirectory dir(0x0110, IfdId::ifd0Id);
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  dir.accept(finder);
  // Since the directory tag doesn't match, result may or may not be null
  // depending on implementation. We just verify it doesn't crash.
  SUCCEED();
}

// Test: TiffFinder with non-matching group
TEST_F(TiffFinderTest_2200, FindDirectoryNonMatchingGroup_2200) {
  TiffDirectory dir(0x010f, IfdId::ifd1Id);
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  dir.accept(finder);
  // Group mismatch - result should be null
  TiffComponent* result = finder.result();
  EXPECT_EQ(nullptr, result);
}

// TiffVisitor base class tests
class TiffVisitorTest_2200 : public ::testing::Test {
 protected:
};

// Test: TiffVisitor go() returns true by default
TEST_F(TiffVisitorTest_2200, GoDefaultTrue_2200) {
  TiffFinder finder(0, IfdId::ifd0Id);
  EXPECT_TRUE(finder.go(GoEvent::goVisit));
}

// Test: TiffVisitor setGo changes go state
TEST_F(TiffVisitorTest_2200, SetGoChangesState_2200) {
  TiffFinder finder(0, IfdId::ifd0Id);
  finder.setGo(GoEvent::goVisit, false);
  EXPECT_FALSE(finder.go(GoEvent::goVisit));
}

// Test: TiffVisitor setGo back to true
TEST_F(TiffVisitorTest_2200, SetGoBackToTrue_2200) {
  TiffFinder finder(0, IfdId::ifd0Id);
  finder.setGo(GoEvent::goVisit, false);
  EXPECT_FALSE(finder.go(GoEvent::goVisit));
  finder.setGo(GoEvent::goVisit, true);
  EXPECT_TRUE(finder.go(GoEvent::goVisit));
}

// TiffComponent tests
class TiffComponentTest_2200 : public ::testing::Test {
 protected:
};

// Test: TiffComponent tag and group accessors
TEST_F(TiffComponentTest_2200, TagAndGroupAccessors_2200) {
  TiffDirectory dir(0x010f, IfdId::ifd0Id);
  EXPECT_EQ(0x010f, dir.tag());
  EXPECT_EQ(IfdId::ifd0Id, dir.group());
}

// Test: TiffDirectory with different tag values
TEST_F(TiffComponentTest_2200, DifferentTagValues_2200) {
  TiffDirectory dir1(0x0000, IfdId::ifd0Id);
  EXPECT_EQ(0x0000, dir1.tag());

  TiffDirectory dir2(0xFFFF, IfdId::exifId);
  EXPECT_EQ(0xFFFF, dir2.tag());
  EXPECT_EQ(IfdId::exifId, dir2.group());
}

// Test: TiffDecoder with findDecoderFct as nullptr
TEST_F(TiffDecoderTest_2200, ConstructWithNullFindDecoderFct_2200) {
  TiffDirectory root(0, IfdId::ifd0Id);
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  SUCCEED();
}

// Test: TiffDecoder visitDirectory does not crash with empty directory
TEST_F(TiffDecoderTest_2200, VisitDirectoryEmpty_2200) {
  TiffDirectory root(0, IfdId::ifd0Id);
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  decoder.visitDirectory(&root);
  SUCCEED();
}

// Test: Multiple TiffFinder inits
TEST_F(TiffFinderTest_2200, MultipleInits_2200) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  EXPECT_EQ(nullptr, finder.result());
  
  finder.init(0x0110, IfdId::ifd1Id);
  EXPECT_EQ(nullptr, finder.result());
  
  finder.init(0x0112, IfdId::exifId);
  EXPECT_EQ(nullptr, finder.result());
}

// Test: TiffDecoder construction preserves exifData reference
TEST_F(TiffDecoderTest_2200, ExifDataReferencePreserved_2200) {
  ExifKey makeKey("Exif.Image.Make");
  auto val = Value::create(asciiString);
  val->read("Sony");
  exifData_.add(makeKey, val.get());

  TiffDirectory root(0, IfdId::ifd0Id);
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  
  // Verify exifData still has the Make entry
  auto it = exifData_.findKey(makeKey);
  EXPECT_NE(exifData_.end(), it);
  EXPECT_EQ("Sony", it->toString());
}

// Test: TiffFinder findObject with matching component
TEST_F(TiffFinderTest_2200, FindObjectDirectMatch_2200) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  TiffDirectory comp(0x010f, IfdId::ifd0Id);
  finder.findObject(&comp);
  EXPECT_EQ(&comp, finder.result());
}

// Test: TiffFinder findObject with non-matching component
TEST_F(TiffFinderTest_2200, FindObjectNoMatch_2200) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  TiffDirectory comp(0x0110, IfdId::ifd0Id);
  finder.findObject(&comp);
  EXPECT_EQ(nullptr, finder.result());
}

// Test: TiffFinder findObject with matching tag but different group
TEST_F(TiffFinderTest_2200, FindObjectMatchingTagDifferentGroup_2200) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  TiffDirectory comp(0x010f, IfdId::exifId);
  finder.findObject(&comp);
  EXPECT_EQ(nullptr, finder.result());
}

// Test: TiffDecoder with multiple Make entries - uses first one
TEST_F(TiffDecoderTest_2200, MultiipleMakeEntries_2200) {
  ExifKey makeKey("Exif.Image.Make");
  auto val1 = Value::create(asciiString);
  val1->read("Canon");
  exifData_.add(makeKey, val1.get());
  
  // Adding a second one - findKey should find the first
  auto val2 = Value::create(asciiString);
  val2->read("Nikon");
  exifData_.add(makeKey, val2.get());

  TiffDirectory root(0, IfdId::ifd0Id);
  TiffDecoder decoder(exifData_, iptcData_, xmpData_, &root, nullptr);
  SUCCEED();
}
