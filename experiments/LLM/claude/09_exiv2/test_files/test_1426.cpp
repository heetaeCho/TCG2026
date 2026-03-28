#include <gtest/gtest.h>
#include <string>

// Include necessary headers from exiv2
#include "exiv2/tags.hpp"
#include "tags_int.hpp"

namespace {

using Exiv2::Internal::tagList;

// ============================================================
// Normal operation tests
// ============================================================

TEST(TagListTest_1426, ReturnsNonNullForImage_1426) {
  const Exiv2::TagInfo* result = tagList("Image");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForThumbnail_1426) {
  const Exiv2::TagInfo* result = tagList("Thumbnail");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForPhoto_1426) {
  const Exiv2::TagInfo* result = tagList("Photo");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForGPSInfo_1426) {
  const Exiv2::TagInfo* result = tagList("GPSInfo");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForIop_1426) {
  const Exiv2::TagInfo* result = tagList("Iop");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForMpfInfo_1426) {
  const Exiv2::TagInfo* result = tagList("MpfInfo");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForImage2_1426) {
  const Exiv2::TagInfo* result = tagList("Image2");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForImage3_1426) {
  const Exiv2::TagInfo* result = tagList("Image3");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForCanon_1426) {
  const Exiv2::TagInfo* result = tagList("Canon");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForCanonCs_1426) {
  const Exiv2::TagInfo* result = tagList("CanonCs");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForNikon3_1426) {
  const Exiv2::TagInfo* result = tagList("Nikon3");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForOlympus_1426) {
  const Exiv2::TagInfo* result = tagList("Olympus");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForPanasonic_1426) {
  const Exiv2::TagInfo* result = tagList("Panasonic");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForPentax_1426) {
  const Exiv2::TagInfo* result = tagList("Pentax");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSigma_1426) {
  const Exiv2::TagInfo* result = tagList("Sigma");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSony1_1426) {
  const Exiv2::TagInfo* result = tagList("Sony1");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForFujifilm_1426) {
  const Exiv2::TagInfo* result = tagList("Fujifilm");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForMinolta_1426) {
  const Exiv2::TagInfo* result = tagList("Minolta");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForCasio_1426) {
  const Exiv2::TagInfo* result = tagList("Casio");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSamsung2_1426) {
  const Exiv2::TagInfo* result = tagList("Samsung2");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSubImage1_1426) {
  const Exiv2::TagInfo* result = tagList("SubImage1");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForPanasonicRaw_1426) {
  const Exiv2::TagInfo* result = tagList("PanasonicRaw");
  EXPECT_NE(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForMakerNote_1426) {
  const Exiv2::TagInfo* result = tagList("MakerNote");
  EXPECT_NE(result, nullptr);
}

// ============================================================
// Tests for the "Unknown" group which has nullptr tagList_
// ============================================================

TEST(TagListTest_1426, ReturnsNullForUnknown_1426) {
  const Exiv2::TagInfo* result = tagList("Unknown");
  EXPECT_EQ(result, nullptr);
}

// ============================================================
// Boundary / Error condition tests
// ============================================================

TEST(TagListTest_1426, ReturnsNullForEmptyString_1426) {
  const Exiv2::TagInfo* result = tagList("");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForNonExistentGroup_1426) {
  const Exiv2::TagInfo* result = tagList("NonExistentGroup");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForGarbageString_1426) {
  const Exiv2::TagInfo* result = tagList("!@#$%^&*()");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForCaseSensitiveMismatchLowercase_1426) {
  // "image" instead of "Image"
  const Exiv2::TagInfo* result = tagList("image");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForCaseSensitiveMismatchUppercase_1426) {
  // "IMAGE" instead of "Image"
  const Exiv2::TagInfo* result = tagList("IMAGE");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForPartialGroupName_1426) {
  const Exiv2::TagInfo* result = tagList("Imag");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForGroupNameWithTrailingSpace_1426) {
  const Exiv2::TagInfo* result = tagList("Image ");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForGroupNameWithLeadingSpace_1426) {
  const Exiv2::TagInfo* result = tagList(" Image");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForLastIFDItem_1426) {
  // "(Last IFD item)" has nullptr tagList_
  const Exiv2::TagInfo* result = tagList("(Last IFD item)");
  EXPECT_EQ(result, nullptr);
}

TEST(TagListTest_1426, ReturnsNullForVeryLongString_1426) {
  std::string longName(10000, 'A');
  const Exiv2::TagInfo* result = tagList(longName);
  EXPECT_EQ(result, nullptr);
}

// ============================================================
// Consistency tests - calling multiple times returns same result
// ============================================================

TEST(TagListTest_1426, ConsistentResultsForSameGroup_1426) {
  const Exiv2::TagInfo* result1 = tagList("Image");
  const Exiv2::TagInfo* result2 = tagList("Image");
  EXPECT_EQ(result1, result2);
}

TEST(TagListTest_1426, DifferentGroupsCanReturnDifferentTagLists_1426) {
  const Exiv2::TagInfo* imageResult = tagList("Image");
  const Exiv2::TagInfo* photoResult = tagList("Photo");
  // Both should be non-null
  EXPECT_NE(imageResult, nullptr);
  EXPECT_NE(photoResult, nullptr);
  // Photo (Exif) and Image (IFD) may differ, but the key point is both are valid
}

// ============================================================
// Tests for groups sharing the same tagList function
// ============================================================

TEST(TagListTest_1426, ImageAndThumbnailShareSameTagList_1426) {
  // Both "Image" and "Thumbnail" use &ifdTagList
  const Exiv2::TagInfo* imageResult = tagList("Image");
  const Exiv2::TagInfo* thumbnailResult = tagList("Thumbnail");
  EXPECT_NE(imageResult, nullptr);
  EXPECT_NE(thumbnailResult, nullptr);
  EXPECT_EQ(imageResult, thumbnailResult);
}

TEST(TagListTest_1426, Image2AndImage3ShareSameTagList_1426) {
  const Exiv2::TagInfo* img2 = tagList("Image2");
  const Exiv2::TagInfo* img3 = tagList("Image3");
  EXPECT_NE(img2, nullptr);
  EXPECT_NE(img3, nullptr);
  EXPECT_EQ(img2, img3);
}

TEST(TagListTest_1426, Sony1AndSony2ShareSameTagList_1426) {
  const Exiv2::TagInfo* sony1 = tagList("Sony1");
  const Exiv2::TagInfo* sony2 = tagList("Sony2");
  EXPECT_NE(sony1, nullptr);
  EXPECT_NE(sony2, nullptr);
  EXPECT_EQ(sony1, sony2);
}

TEST(TagListTest_1426, OlympusAndOlympus2ShareSameTagList_1426) {
  const Exiv2::TagInfo* oly1 = tagList("Olympus");
  const Exiv2::TagInfo* oly2 = tagList("Olympus2");
  EXPECT_NE(oly1, nullptr);
  EXPECT_NE(oly2, nullptr);
  EXPECT_EQ(oly1, oly2);
}

TEST(TagListTest_1426, PentaxAndPentaxDngShareSameTagList_1426) {
  const Exiv2::TagInfo* pentax = tagList("Pentax");
  const Exiv2::TagInfo* pentaxDng = tagList("PentaxDng");
  EXPECT_NE(pentax, nullptr);
  EXPECT_NE(pentaxDng, nullptr);
  EXPECT_EQ(pentax, pentaxDng);
}

// ============================================================
// Additional maker note groups
// ============================================================

TEST(TagListTest_1426, ReturnsNonNullForNikonVr_1426) {
  EXPECT_NE(tagList("NikonVr"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForNikonLd1_1426) {
  EXPECT_NE(tagList("NikonLd1"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSony2Fp_1426) {
  EXPECT_NE(tagList("Sony2Fp"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSonyMisc1_1426) {
  EXPECT_NE(tagList("SonyMisc1"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSonySInfo1_1426) {
  EXPECT_NE(tagList("SonySInfo1"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSony2010e_1426) {
  EXPECT_NE(tagList("Sony2010e"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForNikonPreview_1426) {
  EXPECT_NE(tagList("NikonPreview"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSamsungPreview_1426) {
  EXPECT_NE(tagList("SamsungPreview"), nullptr);
}

TEST(TagListTest_1426, ReturnsNonNullForSamsungPictureWizard_1426) {
  EXPECT_NE(tagList("SamsungPictureWizard"), nullptr);
}

}  // namespace
