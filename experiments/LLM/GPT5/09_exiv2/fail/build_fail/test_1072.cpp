// ============================================================================
// Test file for Exiv2::Image::setMetadata
// File: ./TestProjects/exiv2/src/image_setMetadata_test_1072.cpp
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <cstdint>
#include <memory>
#include <string>

namespace {

using ::testing::Eq;

class SpyImage : public Exiv2::Image {
 public:
  explicit SpyImage(uint16_t supportedMetadata)
      : Exiv2::Image(
            /*type*/ static_cast<Exiv2::ImageType>(0),
            /*supportedMetadata*/ supportedMetadata,
            /*io*/ std::make_unique<Exiv2::MemIo>()) {}

  // Call counters / observed values
  int setExifCalls = 0;
  int setIptcCalls = 0;
  int setXmpPacketCalls = 0;
  int setXmpDataCalls = 0;
  int setIccProfileCalls = 0;
  int setCommentCalls = 0;

  const Exiv2::ExifData* lastExifPtr = nullptr;
  const Exiv2::IptcData* lastIptcPtr = nullptr;
  const Exiv2::XmpData* lastXmpDataPtr = nullptr;

  std::string lastXmpPacket;
  std::string lastComment;

  // Note: keep DataBuf by value to observe "a call happened" without relying on internals.
  Exiv2::DataBuf lastIccProfile;

  void setExifData(const Exiv2::ExifData& exifData) override {
    ++setExifCalls;
    lastExifPtr = &exifData;
  }

  void setIptcData(const Exiv2::IptcData& iptcData) override {
    ++setIptcCalls;
    lastIptcPtr = &iptcData;
  }

  void setXmpPacket(const std::string& xmpPacket) override {
    ++setXmpPacketCalls;
    lastXmpPacket = xmpPacket;
  }

  void setXmpData(const Exiv2::XmpData& xmpData) override {
    ++setXmpDataCalls;
    lastXmpDataPtr = &xmpData;
  }

  void setIccProfile(Exiv2::DataBuf&& iccProfile, bool /*bTestValid*/) override {
    ++setIccProfileCalls;
    lastIccProfile = std::move(iccProfile);
  }

  void setComment(const std::string& comment) override {
    ++setCommentCalls;
    lastComment = comment;
  }
};

class ImageSetMetadataTest_1072 : public ::testing::Test {
 protected:
  static constexpr uint16_t kAll =
      static_cast<uint16_t>(Exiv2::mdExif | Exiv2::mdIptc | Exiv2::mdXmp | Exiv2::mdIccProfile |
                            Exiv2::mdComment);

  static void PopulateSource(SpyImage& src) {
    // Use only public APIs; keep contents simple.
    src.setComment("hello-comment");
    src.setXmpPacket("<xmp>packet</xmp>");

    // ExifData / IptcData: use default containers (no assumptions about parsing/serialization).
    Exiv2::ExifData exif;
    Exiv2::IptcData iptc;
    src.setExifData(exif);
    src.setIptcData(iptc);

    // XmpData: default object.
    Exiv2::XmpData xmp;
    src.setXmpData(xmp);

    // ICC profile: append some bytes through public API (avoids relying on DataBuf internals).
    const uint8_t bytes[] = {0x01, 0x02, 0x03, 0x04};
    src.appendIccProfile(bytes, sizeof(bytes), /*bTestValid*/ false);
  }
};

// The TEST_ID is 1072
TEST_F(ImageSetMetadataTest_1072, CopiesAllSupportedMetadataWhenWritable_1072) {
  SpyImage src(ImageSetMetadataTest_1072::kAll);
  SpyImage dst(ImageSetMetadataTest_1072::kAll);

  PopulateSource(src);

  // Reset destination observation (it should be called by setMetadata).
  dst.setExifCalls = dst.setIptcCalls = dst.setXmpPacketCalls = dst.setXmpDataCalls =
      dst.setIccProfileCalls = dst.setCommentCalls = 0;

  dst.setMetadata(src);

  // We only assert observable interactions: which virtual setters were invoked.
  EXPECT_THAT(dst.setExifCalls, Eq(1));
  EXPECT_THAT(dst.setIptcCalls, Eq(1));
  EXPECT_THAT(dst.setXmpPacketCalls, Eq(1));
  EXPECT_THAT(dst.setXmpDataCalls, Eq(1));
  EXPECT_THAT(dst.setIccProfileCalls, Eq(1));
  EXPECT_THAT(dst.setCommentCalls, Eq(1));

  // For string-copied fields, compare values (purely observable behavior).
  EXPECT_THAT(dst.lastXmpPacket, Eq(src.xmpPacket()));
  EXPECT_THAT(dst.lastComment, Eq(src.comment()));
}

// The TEST_ID is 1072
TEST_F(ImageSetMetadataTest_1072, DoesNothingWhenNoMetadataIsSupported_1072) {
  SpyImage src(ImageSetMetadataTest_1072::kAll);
  SpyImage dst(static_cast<uint16_t>(Exiv2::mdNone));

  PopulateSource(src);

  dst.setMetadata(src);

  EXPECT_THAT(dst.setExifCalls, Eq(0));
  EXPECT_THAT(dst.setIptcCalls, Eq(0));
  EXPECT_THAT(dst.setXmpPacketCalls, Eq(0));
  EXPECT_THAT(dst.setXmpDataCalls, Eq(0));
  EXPECT_THAT(dst.setIccProfileCalls, Eq(0));
  EXPECT_THAT(dst.setCommentCalls, Eq(0));
}

// The TEST_ID is 1072
TEST_F(ImageSetMetadataTest_1072, CopiesOnlySubsetOfSupportedMetadata_1072) {
  SpyImage src(ImageSetMetadataTest_1072::kAll);

  const uint16_t subset =
      static_cast<uint16_t>(Exiv2::mdExif | Exiv2::mdComment);  // intentionally small subset
  SpyImage dst(subset);

  PopulateSource(src);

  dst.setMetadata(src);

  EXPECT_THAT(dst.setExifCalls, Eq(1));
  EXPECT_THAT(dst.setCommentCalls, Eq(1));

  EXPECT_THAT(dst.setIptcCalls, Eq(0));
  EXPECT_THAT(dst.setXmpPacketCalls, Eq(0));
  EXPECT_THAT(dst.setXmpDataCalls, Eq(0));
  EXPECT_THAT(dst.setIccProfileCalls, Eq(0));

  EXPECT_THAT(dst.lastComment, Eq(src.comment()));
}

// The TEST_ID is 1072
TEST_F(ImageSetMetadataTest_1072, CopiesEmptyStringsWhenSupported_1072) {
  SpyImage src(ImageSetMetadataTest_1072::kAll);
  SpyImage dst(static_cast<uint16_t>(Exiv2::mdXmp | Exiv2::mdComment));

  // Explicitly set empty values via public API.
  src.setComment("");
  src.setXmpPacket("");

  dst.setMetadata(src);

  EXPECT_THAT(dst.setCommentCalls, Eq(1));
  EXPECT_THAT(dst.setXmpPacketCalls, Eq(1));
  EXPECT_THAT(dst.lastComment, Eq(std::string()));
  EXPECT_THAT(dst.lastXmpPacket, Eq(std::string()));
}

// The TEST_ID is 1072
TEST_F(ImageSetMetadataTest_1072, SelfAssignmentIsSafeAndInvokesSettersAccordingToMode_1072) {
  SpyImage img(ImageSetMetadataTest_1072::kAll);

  PopulateSource(img);

  // Observe calls triggered by self-copy; behavior should be well-defined via public interface:
  // it may re-set its own metadata, but must not crash.
  img.setExifCalls = img.setIptcCalls = img.setXmpPacketCalls = img.setXmpDataCalls =
      img.setIccProfileCalls = img.setCommentCalls = 0;

  EXPECT_NO_THROW(img.setMetadata(img));

  // We expect that if writable for those metadata IDs, the corresponding setters are invoked.
  // (We don't assert exact internal state changes.)
  EXPECT_THAT(img.setExifCalls, Eq(1));
  EXPECT_THAT(img.setIptcCalls, Eq(1));
  EXPECT_THAT(img.setXmpPacketCalls, Eq(1));
  EXPECT_THAT(img.setXmpDataCalls, Eq(1));
  EXPECT_THAT(img.setIccProfileCalls, Eq(1));
  EXPECT_THAT(img.setCommentCalls, Eq(1));
}

}  // namespace