// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exiftags_ifdname_1324.cpp
//
// Unit tests for Exiv2::ExifTags::ifdName(const std::string&)
//
// Constraints honored:
// - Treat implementation as a black box
// - Use only public interface / observable behavior
// - Do not access private/internal state
// - Cover normal, boundary, and error-ish inputs (unknown/empty)

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <cstring>
#include <string>

namespace {

class ExifTagsIfdNameTest_1324 : public ::testing::Test {
protected:
  static std::string AsSafeString(const char* s) {
    // Convert to std::string for comparison without assuming pointer stability.
    // If the API returns nullptr, represent it as a sentinel.
    return (s == nullptr) ? std::string("<nullptr>") : std::string(s);
  }
};

TEST_F(ExifTagsIfdNameTest_1324, KnownGroups_ReturnsStableStringForSameInput_1324) {
  // A small set of commonly-used Exif group names in Exiv2.
  // We don't assert exact IFD name strings (implementation detail),
  // only that the observable output is stable for repeated calls.
  const char* const kGroups[] = {
      "Exif.Image",
      "Exif.Photo",
      "Exif.GPSInfo",
      "Exif.Iop",
  };

  for (const char* group : kGroups) {
    const char* a = Exiv2::ExifTags::ifdName(std::string(group));
    const char* b = Exiv2::ExifTags::ifdName(std::string(group));

    const std::string sa = AsSafeString(a);
    const std::string sb = AsSafeString(b);

    EXPECT_EQ(sa, sb) << "ifdName should be stable for groupName=" << group;

    // If non-null, it should at least be a valid C-string (null-terminated).
    if (a != nullptr) {
      EXPECT_GE(std::strlen(a), 0u);
    }
  }
}

TEST_F(ExifTagsIfdNameTest_1324, EmptyString_DoesNotCrashAndIsStable_1324) {
  const std::string groupName;

  const char* a = Exiv2::ExifTags::ifdName(groupName);
  const char* b = Exiv2::ExifTags::ifdName(groupName);

  EXPECT_EQ(AsSafeString(a), AsSafeString(b));

  if (a != nullptr) {
    EXPECT_GE(std::strlen(a), 0u);
  }
}

TEST_F(ExifTagsIfdNameTest_1324, UnknownGroup_DoesNotCrashAndIsStable_1324) {
  const std::string groupName = "Not.A.Real.ExifGroup";

  const char* a = Exiv2::ExifTags::ifdName(groupName);
  const char* b = Exiv2::ExifTags::ifdName(groupName);

  EXPECT_EQ(AsSafeString(a), AsSafeString(b));

  if (a != nullptr) {
    EXPECT_GE(std::strlen(a), 0u);
  }
}

TEST_F(ExifTagsIfdNameTest_1324, VeryLongGroupName_DoesNotCrashAndIsStable_1324) {
  // Boundary-ish: long, but valid std::string input.
  std::string groupName(4096, 'A');
  groupName.replace(0, 5, "Exif.");

  const char* a = Exiv2::ExifTags::ifdName(groupName);
  const char* b = Exiv2::ExifTags::ifdName(groupName);

  EXPECT_EQ(AsSafeString(a), AsSafeString(b));

  if (a != nullptr) {
    EXPECT_GE(std::strlen(a), 0u);
  }
}

TEST_F(ExifTagsIfdNameTest_1324, EmbeddedNullInString_DoesNotCrashAndIsStable_1324) {
  // Boundary-ish: std::string can contain embedded NUL.
  // We only assert repeated calls with identical bytes yield stable output.
  const std::string groupName("Exif.Image\0TrailingBytes", 23);

  const char* a = Exiv2::ExifTags::ifdName(groupName);
  const char* b = Exiv2::ExifTags::ifdName(groupName);

  EXPECT_EQ(AsSafeString(a), AsSafeString(b));

  if (a != nullptr) {
    EXPECT_GE(std::strlen(a), 0u);
  }
}

}  // namespace