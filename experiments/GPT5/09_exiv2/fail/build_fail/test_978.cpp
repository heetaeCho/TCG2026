// ============================================================================
// Unit tests for Exiv2::MrwImage::mimeType()
// File: mrwimage_test_978.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <string>

#include "exiv2/mrwimage.hpp"

namespace {

// NOTE: We intentionally only test observable behavior via the public interface.
// The provided implementation for this prompt exposes mimeType() and returns a
// constant string. We avoid relying on any internal state or other methods.

TEST(MrwImageTest_978, MimeTypeReturnsExpectedValue_978) {
  const Exiv2::MrwImage image;
  EXPECT_EQ(std::string("image/x-minolta-mrw"), image.mimeType());
}

TEST(MrwImageTest_978, MimeTypeIsStableAcrossMultipleCalls_978) {
  const Exiv2::MrwImage image;

  const std::string first = image.mimeType();
  const std::string second = image.mimeType();
  const std::string third = image.mimeType();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_EQ(std::string("image/x-minolta-mrw"), third);
}

TEST(MrwImageTest_978, MimeTypeIsNonEmpty_978) {
  const Exiv2::MrwImage image;
  EXPECT_FALSE(image.mimeType().empty());
}

TEST(MrwImageTest_978, MimeTypeLooksLikeMimeFormat_978) {
  const Exiv2::MrwImage image;
  const std::string mt = image.mimeType();

  // Boundary-ish/format checks that don't assume implementation details:
  // - Contains one '/' separating type/subtype
  // - Starts with "image/"
  const auto slashPos = mt.find('/');
  ASSERT_NE(std::string::npos, slashPos);
  EXPECT_EQ(0u, mt.find("image/"));
  EXPECT_GT(mt.size(), slashPos + 1);
}

}  // namespace