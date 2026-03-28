// =================================================================================================
// TEST_ID: 967
// File: test_pngimage_mimetype_967.cpp
// Unit tests for Exiv2::PngImage (partial interface)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>
#include <type_traits>

// The prompt shows the implementation lives in ./TestProjects/exiv2/src/pngimage.cpp
// and the public class is Exiv2::PngImage with:
//   std::string mimeType() const { return "image/png"; }
//
// We only test observable behavior from the provided interface.
// No assumptions about any other methods/constructors.

#include "exiv2/pngimage.hpp"  // Expected to provide Exiv2::PngImage declaration.

namespace {

class PngImageTest_967 : public ::testing::Test {};

}  // namespace

TEST_F(PngImageTest_967, MimeTypeReturnsImagePng_967) {
  Exiv2::PngImage png;
  const std::string mt = png.mimeType();
  EXPECT_EQ("image/png", mt);
}

TEST_F(PngImageTest_967, MimeTypeStableAcrossMultipleCalls_967) {
  Exiv2::PngImage png;

  const std::string mt1 = png.mimeType();
  const std::string mt2 = png.mimeType();
  const std::string mt3 = png.mimeType();

  EXPECT_EQ("image/png", mt1);
  EXPECT_EQ(mt1, mt2);
  EXPECT_EQ(mt2, mt3);
}

TEST_F(PngImageTest_967, MimeTypeWorksThroughConstReference_967) {
  Exiv2::PngImage png;
  const Exiv2::PngImage& cref = png;

  const std::string mt = cref.mimeType();
  EXPECT_EQ("image/png", mt);
}

TEST_F(PngImageTest_967, MimeTypeReturnTypeIsStdString_967) {
  // Boundary/contract-style check: return type is exactly std::string.
  static_assert(std::is_same_v<decltype(std::declval<const Exiv2::PngImage&>().mimeType()), std::string>,
                "PngImage::mimeType() must return std::string");
  SUCCEED();
}

TEST_F(PngImageTest_967, MimeTypeNonEmptyAndLooksLikeMime_967) {
  Exiv2::PngImage png;
  const std::string mt = png.mimeType();

  ASSERT_FALSE(mt.empty());
  // Minimal, non-invasive boundary checks on the returned string.
  EXPECT_NE(std::string::npos, mt.find('/'));
  EXPECT_EQ(0u, mt.find("image/"));
}