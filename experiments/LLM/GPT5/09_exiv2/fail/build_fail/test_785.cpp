// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 785
//
// Unit tests for Exiv2::ExifParser::encode (black-box behavior tests)
//
// File under test: ./TestProjects/exiv2/src/exif.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstring>
#include <string>
#include <vector>

#include "exiv2/error.hpp"
#include "exiv2/exif.hpp"

namespace {

class ExifParserTest_785 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reduce noise from warnings during tests; we explicitly capture them when needed.
    prevLevel_ = Exiv2::LogMsg::level();
    prevHandler_ = Exiv2::LogMsg::handler();
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::mute);
  }

  void TearDown() override {
    Exiv2::LogMsg::setHandler(prevHandler_);
    Exiv2::LogMsg::setLevel(prevLevel_);
  }

  static bool HasKey(const Exiv2::ExifData& exif, const char* keyStr) {
    return exif.findKey(Exiv2::ExifKey(keyStr)) != exif.end();
  }

  static void SetString(Exiv2::ExifData& exif, const char* keyStr, const std::string& v) {
    exif[keyStr] = v;
  }

  static void SetU32(Exiv2::ExifData& exif, const char* keyStr, uint32_t v) {
    exif[keyStr] = v;
  }

  Exiv2::LogMsg::Level prevLevel_{};
  Exiv2::LogMsg::Handler prevHandler_{};
};

TEST_F(ExifParserTest_785, EncodeRemovesFilteredIfd0Tags_ButKeepsOthers_785) {
  Exiv2::ExifData exif;

  // One tag listed in filteredIfd0Tags (should be removed)
  SetU32(exif, "Exif.Image.PhotometricInterpretation", 2u);
  ASSERT_TRUE(HasKey(exif, "Exif.Image.PhotometricInterpretation"));

  // A "normal" tag not listed (should remain)
  SetString(exif, "Exif.Image.Make", "UnitTestMake");
  ASSERT_TRUE(HasKey(exif, "Exif.Image.Make"));

  Exiv2::Blob blob;
  const std::array<Exiv2::byte, 8> data{{0, 0, 0, 0, 0, 0, 0, 0}};

  EXPECT_NO_THROW({
    (void)Exiv2::ExifParser::encode(blob, data.data(), data.size(), Exiv2::littleEndian, exif);
  });

  EXPECT_FALSE(HasKey(exif, "Exif.Image.PhotometricInterpretation"));
  EXPECT_TRUE(HasKey(exif, "Exif.Image.Make"));
  EXPECT_FALSE(blob.empty());  // Should have produced some encoded output.
}

TEST_F(ExifParserTest_785, EncodeWithEmptyExifDataDoesNotThrow_AndProducesBlob_785) {
  Exiv2::ExifData exif;
  EXPECT_TRUE(exif.empty());

  Exiv2::Blob blob;
  const std::array<Exiv2::byte, 8> data{{0, 0, 0, 0, 0, 0, 0, 0}};

  EXPECT_NO_THROW({
    (void)Exiv2::ExifParser::encode(blob, data.data(), data.size(), Exiv2::littleEndian, exif);
  });

  EXPECT_FALSE(blob.empty());
}

TEST_F(ExifParserTest_785, EncodeLargePreviewLengthRemovesAssociatedPreviewTags_785) {
  Exiv2::ExifData exif;

  // These keys are part of the filtered preview-tag set in the implementation.
  SetU32(exif, "Exif.Minolta.ThumbnailLength", 40000u);  // > 32768 triggers removal in that group
  SetU32(exif, "Exif.Minolta.ThumbnailOffset", 123u);
  SetString(exif, "Exif.Minolta.Thumbnail", "dummy");

  ASSERT_TRUE(HasKey(exif, "Exif.Minolta.ThumbnailLength"));
  ASSERT_TRUE(HasKey(exif, "Exif.Minolta.ThumbnailOffset"));
  ASSERT_TRUE(HasKey(exif, "Exif.Minolta.Thumbnail"));

  // Add additional content to increase the likelihood we exercise the "large EXIF" path.
  // (Black-box: we don't assume how sizes are computed, only that very large values can
  // lead to the implementation choosing its size-reduction behavior.)
  SetString(exif, "Exif.Photo.UserComment", std::string(80000, 'A'));

  Exiv2::Blob blob;
  const std::array<Exiv2::byte, 8> data{{0, 0, 0, 0, 0, 0, 0, 0}};

  EXPECT_NO_THROW({
    (void)Exiv2::ExifParser::encode(blob, data.data(), data.size(), Exiv2::littleEndian, exif);
  });

  // Observable behavior: preview tags should not remain when the implementation decides
  // they are too large to encode.
  EXPECT_FALSE(HasKey(exif, "Exif.Minolta.ThumbnailLength"));
  EXPECT_FALSE(HasKey(exif, "Exif.Minolta.ThumbnailOffset"));
  EXPECT_FALSE(HasKey(exif, "Exif.Minolta.Thumbnail"));

  EXPECT_FALSE(blob.empty());
}

TEST_F(ExifParserTest_785, EncodeRemovesVeryLargeTagsFromExifData_WhenSizeReductionApplies_785) {
  Exiv2::ExifData exif;

  // Make a tag value intentionally very large (the implementation has an observable cleanup
  // that removes tags above a certain size during size-reduction encoding).
  SetString(exif, "Exif.Photo.UserComment", std::string(90000, 'B'));
  ASSERT_TRUE(HasKey(exif, "Exif.Photo.UserComment"));

  Exiv2::Blob blob;
  const std::array<Exiv2::byte, 8> data{{0, 0, 0, 0, 0, 0, 0, 0}};

  EXPECT_NO_THROW({
    (void)Exiv2::ExifParser::encode(blob, data.data(), data.size(), Exiv2::littleEndian, exif);
  });

  // Observable effect: if size-reduction cleanup runs, this oversize tag should be removed.
  // (If the implementation didn't need size reduction for some reason, this expectation could
  // fail; however, the test uses a very large payload to strongly exercise that path.)
  EXPECT_FALSE(HasKey(exif, "Exif.Photo.UserComment"));

  EXPECT_FALSE(blob.empty());
}

TEST_F(ExifParserTest_785, EncodeEmitsWarningsViaLogHandler_WhenDroppingPreviewTags_785) {
  Exiv2::ExifData exif;

  // Trigger preview-tag dropping behavior (and thus warnings) by setting a large length.
  SetU32(exif, "Exif.Olympus.ThumbnailLength", 50000u);
  SetU32(exif, "Exif.Olympus.ThumbnailOffset", 7u);
  SetString(exif, "Exif.Olympus.Thumbnail", "dummy");

  // Increase chance we take the branch that evaluates preview-tag filtering and warnings.
  SetString(exif, "Exif.Photo.UserComment", std::string(90000, 'C'));

  // Capture warnings through the LogMsg handler.
  struct Capture {
    static void Handler(int level, const char* s) {
      (void)level;
      if (self_) {
        ++self_->count;
        if (s) self_->msgs.emplace_back(s);
      }
    }
    static inline Capture* self_ = nullptr;

    int count = 0;
    std::vector<std::string> msgs;
  } cap;

  Capture::self_ = &cap;
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
  Exiv2::LogMsg::setHandler(&Capture::Handler);

  Exiv2::Blob blob;
  const std::array<Exiv2::byte, 8> data{{0, 0, 0, 0, 0, 0, 0, 0}};

  EXPECT_NO_THROW({
    (void)Exiv2::ExifParser::encode(blob, data.data(), data.size(), Exiv2::littleEndian, exif);
  });

  // Observable external interaction: dropping preview tags should produce at least one warning.
  EXPECT_GE(cap.count, 1);

  Capture::self_ = nullptr;
}

}  // namespace