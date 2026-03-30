// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1192
//
// Unit tests for internal helper: Exiv2::skipBox(uint32_t)
//
// Note:
// skipBox() is defined as a file-scope `static` function inside bmffimage.cpp.
// To test it as a black box without re-implementing it, we include the .cpp
// directly so the test is compiled in the same translation unit.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

// Make sure this relative path matches your test build layout.
#include "../src/bmffimage.cpp"

namespace {

class SkipBoxTest_1192 : public ::testing::Test {};

TEST_F(SkipBoxTest_1192, ReturnsTrueForZero_1192) {
  EXPECT_TRUE(Exiv2::skipBox(0u));
}

TEST_F(SkipBoxTest_1192, ReturnsTrueForMdatTagValue_1192) {
  // TAG::mdat is provided by bmffimage.cpp; if it changes, this test will follow.
  EXPECT_TRUE(Exiv2::skipBox(static_cast<uint32_t>(TAG::mdat)));
}

TEST_F(SkipBoxTest_1192, ReturnsFalseForTypicalNonSkippedTags_1192) {
  // A few representative non-zero, non-mdat tags from the provided TAG enum.
  EXPECT_FALSE(Exiv2::skipBox(static_cast<uint32_t>(TAG::ftyp)));
  EXPECT_FALSE(Exiv2::skipBox(static_cast<uint32_t>(TAG::moov)));
  EXPECT_FALSE(Exiv2::skipBox(static_cast<uint32_t>(TAG::meta)));
  EXPECT_FALSE(Exiv2::skipBox(static_cast<uint32_t>(TAG::uuid)));
}

TEST_F(SkipBoxTest_1192, ReturnsFalseForSmallNonZeroValues_1192) {
  // Boundary-ish values near 0 that are not 0.
  EXPECT_FALSE(Exiv2::skipBox(1u));
  EXPECT_FALSE(Exiv2::skipBox(2u));
  EXPECT_FALSE(Exiv2::skipBox(3u));
}

TEST_F(SkipBoxTest_1192, ReturnsFalseForMaxUint32WhenNotMdat_1192) {
  const uint32_t v = std::numeric_limits<uint32_t>::max();
  if (v == static_cast<uint32_t>(TAG::mdat)) {
    // Defensive: if TAG::mdat ever equals UINT32_MAX, the helper should skip it.
    EXPECT_TRUE(Exiv2::skipBox(v));
  } else {
    EXPECT_FALSE(Exiv2::skipBox(v));
  }
}

TEST_F(SkipBoxTest_1192, MdatIsTheOnlyNonZeroValueThatIsSkippedAmongSampledTags_1192) {
  // Verify that among a sampled set of known TAGs, only mdat is skipped (and 0).
  const uint32_t sampled[] = {
      static_cast<uint32_t>(TAG::ftyp), static_cast<uint32_t>(TAG::avif),
      static_cast<uint32_t>(TAG::heic), static_cast<uint32_t>(TAG::moov),
      static_cast<uint32_t>(TAG::meta), static_cast<uint32_t>(TAG::iloc),
      static_cast<uint32_t>(TAG::exif), static_cast<uint32_t>(TAG::uuid),
      static_cast<uint32_t>(TAG::mdat),
  };

  for (uint32_t box : sampled) {
    const bool skipped = Exiv2::skipBox(box);
    if (box == static_cast<uint32_t>(TAG::mdat)) {
      EXPECT_TRUE(skipped) << "Expected TAG::mdat to be skipped";
    } else {
      EXPECT_FALSE(skipped) << "Expected tag not to be skipped: " << box;
    }
  }
}

}  // namespace