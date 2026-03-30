// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_pgfimage_mimetype_1043.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/pgfimage.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

// Creates a BasicIo::UniquePtr suitable for constructing an Exiv2::PgfImage.
// Uses MemIo with an empty buffer (metadata content is irrelevant for mimeType()).
Exiv2::BasicIo::UniquePtr makeEmptyMemIo() {
  std::vector<Exiv2::byte> empty;
  return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(empty.data(), empty.size()));
}

}  // namespace

class PgfImageTest_1043 : public ::testing::Test {};

TEST_F(PgfImageTest_1043, MimeTypeReturnsExpectedString_1043) {
  Exiv2::PgfImage image(makeEmptyMemIo(), /*create=*/true);

  const std::string mime = image.mimeType();
  EXPECT_EQ("image/pgf", mime);
}

TEST_F(PgfImageTest_1043, MimeTypeIsStableAcrossRepeatedCalls_1043) {
  Exiv2::PgfImage image(makeEmptyMemIo(), /*create=*/false);

  const std::string first = image.mimeType();
  const std::string second = image.mimeType();
  const std::string third = image.mimeType();

  EXPECT_EQ("image/pgf", first);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(PgfImageTest_1043, MimeTypeCallableOnConstReference_1043) {
  Exiv2::PgfImage image(makeEmptyMemIo(), /*create=*/true);
  const Exiv2::PgfImage& cref = image;

  EXPECT_EQ("image/pgf", cref.mimeType());
}

TEST_F(PgfImageTest_1043, MimeTypeDoesNotDependOnCreateFlag_1043) {
  Exiv2::PgfImage imageCreateTrue(makeEmptyMemIo(), /*create=*/true);
  Exiv2::PgfImage imageCreateFalse(makeEmptyMemIo(), /*create=*/false);

  EXPECT_EQ("image/pgf", imageCreateTrue.mimeType());
  EXPECT_EQ("image/pgf", imageCreateFalse.mimeType());
}

TEST_F(PgfImageTest_1043, MimeTypeValueIsExactIncludingCaseAndSlash_1043) {
  Exiv2::PgfImage image(makeEmptyMemIo(), /*create=*/true);

  const std::string mime = image.mimeType();

  // Boundary-style checks on the returned observable value (no internal assumptions).
  EXPECT_FALSE(mime.empty());
  EXPECT_NE(std::string::npos, mime.find('/'));
  EXPECT_EQ("image/pgf", mime);  // exact match (case-sensitive)
}