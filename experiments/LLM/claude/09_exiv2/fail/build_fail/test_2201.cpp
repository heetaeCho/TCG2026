#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/tags.hpp"
#include "tiffimage_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// A minimal concrete TiffHeaderBase for testing
class TestTiffHeader : public TiffHeaderBase {
 public:
  TestTiffHeader(ByteOrder byteOrder = littleEndian)
      : TiffHeaderBase(0x4949, 8, byteOrder, 8) {}
};

// A dummy FindEncoderFct
static const EncoderFct* dummyFindEncoder(const std::string& /*make*/,
                                           uint32_t /*tag*/,
                                           IfdId /*group*/) {
  return nullptr;
}

class TiffEncoderTest_2201 : public ::testing::Test {
 protected:
  void SetUp() override {
    header_ = std::make_unique<TestTiffHeader>(littleEndian);
  }

  std::unique_ptr<TestTiffHeader> header_;
};

// Test: TiffEncoder can be constructed with empty metadata and null root
TEST_F(TiffEncoderTest_2201, ConstructWithEmptyData_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  // pRoot can be nullptr
  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  // Verify the encoder is created and has expected byte order
  EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

// Test: TiffEncoder reports correct byte order from header (big endian)
TEST_F(TiffEncoderTest_2201, ByteOrderBigEndian_2201) {
  auto headerBE = std::make_unique<TestTiffHeader>(bigEndian);
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, headerBE.get(), dummyFindEncoder);

  EXPECT_EQ(encoder.byteOrder(), bigEndian);
}

// Test: TiffEncoder initial dirty state is false
TEST_F(TiffEncoderTest_2201, InitialDirtyStateFalse_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffEncoder setDirty changes dirty state
TEST_F(TiffEncoderTest_2201, SetDirtyTrue_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  encoder.setDirty(true);
  EXPECT_TRUE(encoder.dirty());
}

// Test: TiffEncoder setDirty can toggle back to false
TEST_F(TiffEncoderTest_2201, SetDirtyToggle_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  encoder.setDirty(true);
  EXPECT_TRUE(encoder.dirty());
  encoder.setDirty(false);
  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffEncoder initial writeMethod is wmNonIntrusive
TEST_F(TiffEncoderTest_2201, InitialWriteMethod_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

// Test: TiffEncoder with ExifData containing Exif.Image.Make
TEST_F(TiffEncoderTest_2201, ConstructWithMakeTag_2201) {
  ExifData exifData;
  ExifKey makeKey("Exif.Image.Make");
  Value::UniquePtr val = Value::create(asciiString);
  val->read("TestMake");
  exifData.add(makeKey, val.get());

  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  // Should not crash; make_ should be set internally
  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_EQ(encoder.byteOrder(), littleEndian);
  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffEncoder constructed as new image
TEST_F(TiffEncoderTest_2201, ConstructAsNewImage_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, true,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_EQ(encoder.byteOrder(), littleEndian);
  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffEncoder with non-empty IPTC data
TEST_F(TiffEncoderTest_2201, ConstructWithIptcData_2201) {
  ExifData exifData;
  IptcData iptcData;
  // Add an IPTC entry
  IptcKey iptcKey("Iptc.Application2.Caption");
  Value::UniquePtr val = Value::create(string);
  val->read("Test caption");
  iptcData.add(iptcKey, val.get());

  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffEncoder with non-empty XMP data
TEST_F(TiffEncoderTest_2201, ConstructWithXmpData_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  xmpData["Xmp.dc.title"] = "Test Title";

  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffFinder construction and initial result is null
TEST(TiffFinderTest_2201, InitialResultIsNull_2201) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  EXPECT_EQ(finder.result(), nullptr);
}

// Test: TiffFinder init resets state
TEST(TiffFinderTest_2201, InitResetsState_2201) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  finder.init(0x0110, IfdId::ifd1Id);
  EXPECT_EQ(finder.result(), nullptr);
}

// Test: TiffVisitor go returns true by default
TEST(TiffVisitorTest_2201, GoDefaultsTrue_2201) {
  // We need a concrete visitor. TiffFinder is a concrete subclass.
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  EXPECT_TRUE(finder.go(GoEvent::geTraverse));
  EXPECT_TRUE(finder.go(GoEvent::geKnownMakernote));
}

// Test: TiffVisitor setGo changes go state
TEST(TiffVisitorTest_2201, SetGoChangesState_2201) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  finder.setGo(GoEvent::geTraverse, false);
  EXPECT_FALSE(finder.go(GoEvent::geTraverse));
}

// Test: TiffVisitor setGo can re-enable
TEST(TiffVisitorTest_2201, SetGoReEnable_2201) {
  TiffFinder finder(0x010f, IfdId::ifd0Id);
  finder.setGo(GoEvent::geTraverse, false);
  EXPECT_FALSE(finder.go(GoEvent::geTraverse));
  finder.setGo(GoEvent::geTraverse, true);
  EXPECT_TRUE(finder.go(GoEvent::geTraverse));
}

// Test: TiffEncoder with multiple ExifData entries
TEST_F(TiffEncoderTest_2201, ConstructWithMultipleExifEntries_2201) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "Canon";
  exifData["Exif.Image.Model"] = "EOS 5D";
  exifData["Exif.Photo.ISOSpeedRatings"] = uint16_t(100);

  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_EQ(encoder.byteOrder(), littleEndian);
  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffEncoder byte order matches little endian header
TEST_F(TiffEncoderTest_2201, ByteOrderMatchesHeader_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  auto headerLE = std::make_unique<TestTiffHeader>(littleEndian);
  TiffEncoder encoderLE(exifData, iptcData, xmpData, nullptr, false,
                        primaryGroups, headerLE.get(), dummyFindEncoder);
  EXPECT_EQ(encoderLE.byteOrder(), littleEndian);

  auto headerBE = std::make_unique<TestTiffHeader>(bigEndian);
  TiffEncoder encoderBE(exifData, iptcData, xmpData, nullptr, false,
                        primaryGroups, headerBE.get(), dummyFindEncoder);
  EXPECT_EQ(encoderBE.byteOrder(), bigEndian);
}

// Test: TiffEncoder with empty Make string in ExifData (key exists but empty value)
TEST_F(TiffEncoderTest_2201, ConstructWithEmptyMakeString_2201) {
  ExifData exifData;
  exifData["Exif.Image.Make"] = "";

  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_FALSE(encoder.dirty());
}

// Test: TiffHeaderBase basic interface
TEST(TiffHeaderBaseTest_2201, BasicProperties_2201) {
  TestTiffHeader header(littleEndian);
  EXPECT_EQ(header.byteOrder(), littleEndian);
  EXPECT_EQ(header.offset(), 8u);
  EXPECT_EQ(header.size(), 8u);
}

// Test: TiffHeaderBase setByteOrder
TEST(TiffHeaderBaseTest_2201, SetByteOrder_2201) {
  TestTiffHeader header(littleEndian);
  EXPECT_EQ(header.byteOrder(), littleEndian);
  header.setByteOrder(bigEndian);
  EXPECT_EQ(header.byteOrder(), bigEndian);
}

// Test: TiffHeaderBase setOffset
TEST(TiffHeaderBaseTest_2201, SetOffset_2201) {
  TestTiffHeader header(littleEndian);
  header.setOffset(16);
  EXPECT_EQ(header.offset(), 16u);
}

// Test: TiffHeaderBase isImageTag default returns false
TEST(TiffHeaderBaseTest_2201, IsImageTagDefault_2201) {
  TestTiffHeader header(littleEndian);
  PrimaryGroups pg;
  EXPECT_FALSE(header.isImageTag(0x0100, IfdId::ifd0Id, pg));
}

// Test: Multiple setDirty calls
TEST_F(TiffEncoderTest_2201, MultipleDirtyCalls_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  for (int i = 0; i < 10; ++i) {
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
  }
}

// Test: TiffEncoder with PrimaryGroups containing entries
TEST_F(TiffEncoderTest_2201, ConstructWithPrimaryGroups_2201) {
  ExifData exifData;
  IptcData iptcData;
  XmpData xmpData;
  PrimaryGroups primaryGroups;
  primaryGroups.push_back(IfdId::ifd0Id);
  primaryGroups.push_back(IfdId::ifd1Id);

  TiffEncoder encoder(exifData, iptcData, xmpData, nullptr, false,
                      primaryGroups, header_.get(), dummyFindEncoder);

  EXPECT_EQ(encoder.byteOrder(), littleEndian);
  EXPECT_FALSE(encoder.dirty());
}
