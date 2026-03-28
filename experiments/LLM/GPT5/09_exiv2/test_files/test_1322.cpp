// =================================================================================================
// TEST_ID: 1322
// File: test_exiftags_sectionname_1322.cpp
// Unit tests for Exiv2::ExifTags::sectionName(const ExifKey&)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstring>   // std::strcmp
#include <string>    // std::string

#include <exiv2/tags.hpp>

namespace {

// Helper that compares C-strings safely and gives nicer ASSERT messages.
void ExpectCStringEq(const char* actual, const char* expected) {
  ASSERT_NE(actual, nullptr);
  ASSERT_NE(expected, nullptr);
  EXPECT_STREQ(actual, expected);
}

class ExifTagsSectionNameTest_1322 : public ::testing::Test {
 protected:
  static const char* SectionName(const Exiv2::ExifKey& key) {
    // ExifTags is documented as a static class; call the static API.
    return Exiv2::ExifTags::sectionName(key);
  }
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation: known GPS tags should map to the "GPS" section
// -------------------------------------------------------------------------------------------------

TEST_F(ExifTagsSectionNameTest_1322, ReturnsGpsForGpsLatitude_1322) {
  const Exiv2::ExifKey key("Exif.GPSInfo.GPSLatitude");

  const char* section = SectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STRNE(section, "");  // Non-empty observable output
  ExpectCStringEq(section, "GPS");
}

TEST_F(ExifTagsSectionNameTest_1322, ReturnsGpsForGpsVersionId_1322) {
  const Exiv2::ExifKey key("Exif.GPSInfo.GPSVersionID");

  const char* section = SectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STRNE(section, "");
  ExpectCStringEq(section, "GPS");
}

// -------------------------------------------------------------------------------------------------
// Boundary / error-like: unknown tag in a valid group should fall back to "(UnknownSection)"
// -------------------------------------------------------------------------------------------------

TEST_F(ExifTagsSectionNameTest_1322, UnknownTagFallsBackToUnknownSection_1322) {
  // Use a well-known group name ("GPSInfo") but an extremely unlikely tag value.
  // The observable behavior we can assert: the API returns a valid section name string,
  // and (for unknown tags) it should fall back to the "(UnknownSection)" section.
  const Exiv2::ExifKey key(static_cast<uint16_t>(0xFFFF), std::string("GPSInfo"));

  const char* section = SectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STRNE(section, "");
  ExpectCStringEq(section, "(UnknownSection)");
}

// -------------------------------------------------------------------------------------------------
// Normal operation: a common Exif tag in the Exif IFD should map to the "DateTime" section
// -------------------------------------------------------------------------------------------------

TEST_F(ExifTagsSectionNameTest_1322, ReturnsDateTimeForDateTimeOriginal_1322) {
  const Exiv2::ExifKey key("Exif.Photo.DateTimeOriginal");

  const char* section = SectionName(key);
  ASSERT_NE(section, nullptr);
  EXPECT_STRNE(section, "");
  // Observable expectation: DateTimeOriginal is part of the DateTime section in Exiv2 tag metadata.
  ExpectCStringEq(section, "DateTime");
}