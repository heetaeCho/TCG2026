// SPDX-License-Identifier: GPL-2.0-or-later
//
// TEST_ID: 2197
//
// Unit tests for Exiv2::OrfImage constructor behavior (black-box via public interface)

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/orfimage.hpp>

namespace {

class OrfImageTest_2197 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr makeIo() {
    // Use a concrete BasicIo implementation from Exiv2 (no internal logic assumptions).
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo);
  }
};

TEST_F(OrfImageTest_2197, ConstructorCreateFalseDoesNotThrow_2197) {
  EXPECT_NO_THROW({
    auto io = makeIo();
    Exiv2::OrfImage img(std::move(io), /*create=*/false);
    (void)img.good();  // observable API call should be safe
  });
}

TEST_F(OrfImageTest_2197, ConstructorCreateTrueDoesNotThrow_2197) {
  EXPECT_NO_THROW({
    auto io = makeIo();
    Exiv2::OrfImage img(std::move(io), /*create=*/true);
    (void)img.good();  // observable API call should be safe
  });
}

TEST_F(OrfImageTest_2197, ImageTypeIsOrf_2197) {
  auto io = makeIo();
  Exiv2::OrfImage img(std::move(io), /*create=*/false);

  // Observable state via public API.
  EXPECT_EQ(img.imageType(), Exiv2::ImageType::orf);
}

TEST_F(OrfImageTest_2197, SupportsExpectedMetadataIds_2197) {
  auto io = makeIo();
  Exiv2::OrfImage img(std::move(io), /*create=*/false);

  // Constructor advertises support for Exif/Iptc/Xmp (observable via supportsMetadata()).
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdExif));
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdIptc));
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdXmp));
}

TEST_F(OrfImageTest_2197, DoesNotReportSupportForOtherMetadataIds_2197) {
  auto io = makeIo();
  Exiv2::OrfImage img(std::move(io), /*create=*/false);

  // Boundary/negative checks for other ids (only observable behavior asserted).
  EXPECT_FALSE(img.supportsMetadata(Exiv2::mdNone));
  EXPECT_FALSE(img.supportsMetadata(Exiv2::mdComment));
  EXPECT_FALSE(img.supportsMetadata(Exiv2::mdIccProfile));
}

TEST_F(OrfImageTest_2197, IoAccessorIsCallableAfterConstruction_2197) {
  auto io = makeIo();
  Exiv2::OrfImage img(std::move(io), /*create=*/false);

  // Verify publicly observable interaction: io() accessor is callable.
  EXPECT_NO_THROW({
    const Exiv2::BasicIo& ref = img.io();
    (void)ref;
  });
}

}  // namespace