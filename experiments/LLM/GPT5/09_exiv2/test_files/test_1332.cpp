// File: test_exifkey_impl_decomposekey_1332.cpp
// TEST_ID: 1332

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>   // Exiv2::ExifKey
#include <exiv2/tags.hpp>   // Exiv2::IfdId

#include <cstdint>
#include <string>

namespace {

class ExifKeyImplTest_1332 : public ::testing::Test {
 protected:
  static void ExpectInvalidKey_1332(const std::string& key) {
    Exiv2::ExifKey::Impl impl;
    try {
      impl.decomposeKey(key);
      FAIL() << "Expected Exiv2::Error(kerInvalidKey) for key: " << key;
    } catch (const Exiv2::Error& e) {
      EXPECT_EQ(Exiv2::ErrorCode::kerInvalidKey, e.code()) << "key: " << key;
    }
  }
};

TEST_F(ExifKeyImplTest_1332, DecomposeKey_ValidExifPhotoKey_SetsPublicOutputs_1332) {
  Exiv2::ExifKey::Impl impl;

  // A commonly valid Exif key in Exiv2.
  const std::string input = "Exif.Photo.DateTimeOriginal";

  ASSERT_NO_THROW(impl.decomposeKey(input));

  // Observable public state (provided in prompt).
  EXPECT_NE(nullptr, impl.tagInfo_);
  EXPECT_NE(0u, impl.tag_);
  EXPECT_NE(Exiv2::IfdId::ifdIdNotSet, impl.ifdId_);
  EXPECT_EQ("Photo", impl.groupName_);

  // Implementation constructs a normalized key string: family.group.tagName()
  // For this input, it should remain the same.
  EXPECT_EQ("Exif.Photo.DateTimeOriginal", impl.key_);
}

TEST_F(ExifKeyImplTest_1332, DecomposeKey_MissingFirstDot_ThrowsInvalidKey_1332) {
  // No '.' at all
  ExpectInvalidKey_1332("ExifPhotoDateTimeOriginal");
}

TEST_F(ExifKeyImplTest_1332, DecomposeKey_MissingSecondDot_ThrowsInvalidKey_1332) {
  // Only one '.' -> missing group/tag split
  ExpectInvalidKey_1332("Exif.Photo");
}

TEST_F(ExifKeyImplTest_1332, DecomposeKey_EmptyGroup_ThrowsInvalidKey_1332) {
  // Empty group between dots
  ExpectInvalidKey_1332("Exif..DateTimeOriginal");
}

TEST_F(ExifKeyImplTest_1332, DecomposeKey_EmptyTagToken_ThrowsInvalidKey_1332) {
  // Empty tag after second dot
  ExpectInvalidKey_1332("Exif.Photo.");
}

TEST_F(ExifKeyImplTest_1332, DecomposeKey_UnknownTagName_ThrowsInvalidKey_1332) {
  // Tag name that should not exist -> tagInfo() expected to be null -> invalid key.
  ExpectInvalidKey_1332("Exif.Photo.ThisTagDoesNotExist");
}

TEST_F(ExifKeyImplTest_1332, DecomposeKey_WrongFamilyPrefix_ThrowsInvalidKey_1332) {
  // Family prefix doesn't match ExifKey's familyName_.
  ExpectInvalidKey_1332("Iptc.Photo.DateTimeOriginal");
}

}  // namespace