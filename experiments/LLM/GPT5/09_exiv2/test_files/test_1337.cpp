// File: test_exifkey_familyname_1337.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/tags.hpp"

namespace {

class ExifKeyTest_1337 : public ::testing::Test {
 protected:
  static void ExpectValidFamilyName(const Exiv2::ExifKey& key) {
    const char* fam = key.familyName();
    ASSERT_NE(fam, nullptr);
    EXPECT_NE(std::string(fam).size(), 0u);
  }
};

TEST_F(ExifKeyTest_1337, FamilyName_NonNullAndNonEmpty_1337) {
  Exiv2::ExifKey k(std::string("Exif.Photo.DateTimeOriginal"));
  ExpectValidFamilyName(k);
}

TEST_F(ExifKeyTest_1337, FamilyName_StableAcrossMultipleCalls_1337) {
  Exiv2::ExifKey k(std::string("Exif.Photo.DateTimeOriginal"));

  const char* f1 = k.familyName();
  const char* f2 = k.familyName();
  ASSERT_NE(f1, nullptr);
  ASSERT_NE(f2, nullptr);

  // Value should be stable across calls (string content).
  EXPECT_STREQ(f1, f2);
}

TEST_F(ExifKeyTest_1337, FamilyName_ConsistentAcrossCommonConstructors_1337) {
  // String-key constructor (common and expected to be valid in Exiv2).
  Exiv2::ExifKey fromString(std::string("Exif.Photo.DateTimeOriginal"));
  ExpectValidFamilyName(fromString);
  const std::string fam0(fromString.familyName());

  // (tag, groupName) constructor: choose a commonly used Photo group/tag.
  // If the library rejects these inputs and throws, that is observable behavior;
  // in that case we don't assert further.
  try {
    Exiv2::ExifKey fromTag(static_cast<uint16_t>(0x9003), std::string("Photo"));  // DateTimeOriginal
    ExpectValidFamilyName(fromTag);
    EXPECT_EQ(std::string(fromTag.familyName()), fam0);
  } catch (...) {
    SUCCEED() << "ExifKey(tag, groupName) threw for (0x9003, \"Photo\"); behavior is implementation-defined.";
  }
}

TEST_F(ExifKeyTest_1337, FamilyName_CopyAndAssignmentPreserveFamilyName_1337) {
  Exiv2::ExifKey original(std::string("Exif.Photo.DateTimeOriginal"));
  ExpectValidFamilyName(original);
  const std::string fam0(original.familyName());

  Exiv2::ExifKey copy(original);
  ExpectValidFamilyName(copy);
  EXPECT_EQ(std::string(copy.familyName()), fam0);

  Exiv2::ExifKey assigned(std::string("Exif.Image.Make"));
  assigned = original;
  ExpectValidFamilyName(assigned);
  EXPECT_EQ(std::string(assigned.familyName()), fam0);
}

TEST_F(ExifKeyTest_1337, FamilyName_BoundaryInputs_DoNotCrash_1337) {
  // Empty key string: may be accepted or may throw. Either is observable.
  try {
    Exiv2::ExifKey emptyKey(std::string(""));
    // If constructed, familyName should still be usable.
    ExpectValidFamilyName(emptyKey);
  } catch (...) {
    SUCCEED() << "ExifKey(\"\") threw; acceptable as observable behavior.";
  }

  // Boundary tags: may be accepted or may throw. Ensure no crash and familyName usable if constructed.
  const uint16_t tags[] = {static_cast<uint16_t>(0x0000), static_cast<uint16_t>(0xFFFF)};
  for (uint16_t t : tags) {
    try {
      Exiv2::ExifKey boundaryTag(t, std::string("Photo"));
      ExpectValidFamilyName(boundaryTag);
    } catch (...) {
      SUCCEED() << "ExifKey(" << t << ", \"Photo\") threw; acceptable as observable behavior.";
    }
  }

  // Empty group name boundary: may be accepted or may throw.
  try {
    Exiv2::ExifKey emptyGroup(static_cast<uint16_t>(0x9003), std::string(""));
    ExpectValidFamilyName(emptyGroup);
  } catch (...) {
    SUCCEED() << "ExifKey(0x9003, \"\") threw; acceptable as observable behavior.";
  }
}

}  // namespace