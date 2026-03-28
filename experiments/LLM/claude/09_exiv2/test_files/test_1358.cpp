#include <gtest/gtest.h>
#include "exiv2/tags.h"
#include "tags_int.hpp"

namespace {

class ExifTagListTest_1358 : public ::testing::Test {
 protected:
  const Exiv2::TagInfo* tagList_ = nullptr;

  void SetUp() override {
    tagList_ = Exiv2::Internal::exifTagList();
  }
};

// Test that exifTagList returns a non-null pointer
TEST_F(ExifTagListTest_1358, ReturnsNonNull_1358) {
  ASSERT_NE(tagList_, nullptr);
}

// Test that the first entry is ExposureTime with tag 33434
TEST_F(ExifTagListTest_1358, FirstEntryIsExposureTime_1358) {
  EXPECT_EQ(tagList_[0].tag_, 33434);
  EXPECT_STREQ(tagList_[0].name_, "ExposureTime");
  EXPECT_STREQ(tagList_[0].title_, "Exposure Time");
}

// Test that the second entry is FNumber with tag 33437
TEST_F(ExifTagListTest_1358, SecondEntryIsFNumber_1358) {
  EXPECT_EQ(tagList_[1].tag_, 33437);
  EXPECT_STREQ(tagList_[1].name_, "FNumber");
  EXPECT_STREQ(tagList_[1].title_, "FNumber");
}

// Test that ExposureProgram entry exists at index 2 with tag 34850
TEST_F(ExifTagListTest_1358, ThirdEntryIsExposureProgram_1358) {
  EXPECT_EQ(tagList_[2].tag_, 34850);
  EXPECT_STREQ(tagList_[2].name_, "ExposureProgram");
}

// Test SpectralSensitivity entry
TEST_F(ExifTagListTest_1358, SpectralSensitivityEntry_1358) {
  EXPECT_EQ(tagList_[3].tag_, 34852);
  EXPECT_STREQ(tagList_[3].name_, "SpectralSensitivity");
}

// Test ISOSpeedRatings entry
TEST_F(ExifTagListTest_1358, ISOSpeedRatingsEntry_1358) {
  EXPECT_EQ(tagList_[4].tag_, 34855);
  EXPECT_STREQ(tagList_[4].name_, "ISOSpeedRatings");
}

// Test that the ExifVersion entry has the correct tag and name
TEST_F(ExifTagListTest_1358, ExifVersionEntry_1358) {
  EXPECT_EQ(tagList_[12].tag_, 36864);
  EXPECT_STREQ(tagList_[12].name_, "ExifVersion");
  EXPECT_STREQ(tagList_[12].title_, "Exif Version");
}

// Test DateTimeOriginal entry
TEST_F(ExifTagListTest_1358, DateTimeOriginalEntry_1358) {
  EXPECT_EQ(tagList_[13].tag_, 36867);
  EXPECT_STREQ(tagList_[13].name_, "DateTimeOriginal");
  EXPECT_EQ(tagList_[13].count_, 20);
}

// Test DateTimeDigitized entry
TEST_F(ExifTagListTest_1358, DateTimeDigitizedEntry_1358) {
  EXPECT_EQ(tagList_[14].tag_, 36868);
  EXPECT_STREQ(tagList_[14].name_, "DateTimeDigitized");
  EXPECT_EQ(tagList_[14].count_, 20);
}

// Test that ColorSpace entry exists
TEST_F(ExifTagListTest_1358, ColorSpaceEntry_1358) {
  // ColorSpace is at a known position in the array
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 40961) {
      EXPECT_STREQ(tagList_[i].name_, "ColorSpace");
      EXPECT_STREQ(tagList_[i].title_, "Color Space");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that PixelXDimension entry exists
TEST_F(ExifTagListTest_1358, PixelXDimensionEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 40962) {
      EXPECT_STREQ(tagList_[i].name_, "PixelXDimension");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that PixelYDimension entry exists
TEST_F(ExifTagListTest_1358, PixelYDimensionEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 40963) {
      EXPECT_STREQ(tagList_[i].name_, "PixelYDimension");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that the last entry (sentinel/unknown) has tag 65535
TEST_F(ExifTagListTest_1358, LastEntryIsUnknownSentinel_1358) {
  EXPECT_EQ(tagList_[89].tag_, 65535);
  EXPECT_STREQ(tagList_[89].name_, "(UnknownExifTag)");
  EXPECT_STREQ(tagList_[89].title_, "Unknown Exif tag");
}

// Test that all IFD IDs in the list are exifId
TEST_F(ExifTagListTest_1358, AllEntriesHaveExifIfdId_1358) {
  for (int i = 0; i < 90; ++i) {
    EXPECT_EQ(tagList_[i].ifdId_, Exiv2::IfdId::exifId)
        << "Entry " << i << " (tag " << tagList_[i].tag_ << ") has wrong IFD ID";
  }
}

// Test that tags are in non-decreasing order
TEST_F(ExifTagListTest_1358, TagsAreInNonDecreasingOrder_1358) {
  for (int i = 1; i < 90; ++i) {
    EXPECT_GE(tagList_[i].tag_, tagList_[i - 1].tag_)
        << "Tag at index " << i << " is less than tag at index " << (i - 1);
  }
}

// Test Flash entry at known position
TEST_F(ExifTagListTest_1358, FlashEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 37385) {
      EXPECT_STREQ(tagList_[i].name_, "Flash");
      EXPECT_STREQ(tagList_[i].title_, "Flash");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test FocalLength entry
TEST_F(ExifTagListTest_1358, FocalLengthEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 37386) {
      EXPECT_STREQ(tagList_[i].name_, "FocalLength");
      EXPECT_STREQ(tagList_[i].title_, "Focal Length");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test MakerNote entry
TEST_F(ExifTagListTest_1358, MakerNoteEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 37500) {
      EXPECT_STREQ(tagList_[i].name_, "MakerNote");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test UserComment entry
TEST_F(ExifTagListTest_1358, UserCommentEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 37510) {
      EXPECT_STREQ(tagList_[i].name_, "UserComment");
      EXPECT_STREQ(tagList_[i].title_, "User Comment");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test LensModel entry
TEST_F(ExifTagListTest_1358, LensModelEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42036) {
      EXPECT_STREQ(tagList_[i].name_, "LensModel");
      EXPECT_STREQ(tagList_[i].title_, "Lens Model");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test LensMake entry
TEST_F(ExifTagListTest_1358, LensMakeEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42035) {
      EXPECT_STREQ(tagList_[i].name_, "LensMake");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test Gamma entry
TEST_F(ExifTagListTest_1358, GammaEntry_1358) {
  // Gamma should be the second-to-last entry (index 88)
  EXPECT_EQ(tagList_[88].tag_, 42240);
  EXPECT_STREQ(tagList_[88].name_, "Gamma");
  EXPECT_STREQ(tagList_[88].title_, "Gamma");
}

// Test BodySerialNumber entry
TEST_F(ExifTagListTest_1358, BodySerialNumberEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42033) {
      EXPECT_STREQ(tagList_[i].name_, "BodySerialNumber");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test CameraOwnerName entry
TEST_F(ExifTagListTest_1358, CameraOwnerNameEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42032) {
      EXPECT_STREQ(tagList_[i].name_, "CameraOwnerName");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test ImageUniqueID entry with expected count of 33
TEST_F(ExifTagListTest_1358, ImageUniqueIDEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42016) {
      EXPECT_STREQ(tagList_[i].name_, "ImageUniqueID");
      EXPECT_EQ(tagList_[i].count_, 33);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that calling exifTagList multiple times returns the same pointer
TEST_F(ExifTagListTest_1358, ConsistentReturnValue_1358) {
  const Exiv2::TagInfo* list1 = Exiv2::Internal::exifTagList();
  const Exiv2::TagInfo* list2 = Exiv2::Internal::exifTagList();
  EXPECT_EQ(list1, list2);
}

// Test CompositeImage entry
TEST_F(ExifTagListTest_1358, CompositeImageEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42080) {
      EXPECT_STREQ(tagList_[i].name_, "CompositeImage");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that all entries have non-null name
TEST_F(ExifTagListTest_1358, AllEntriesHaveNonNullName_1358) {
  for (int i = 0; i < 90; ++i) {
    EXPECT_NE(tagList_[i].name_, nullptr) << "Entry " << i << " has null name";
  }
}

// Test that all entries have non-null title
TEST_F(ExifTagListTest_1358, AllEntriesHaveNonNullTitle_1358) {
  for (int i = 0; i < 90; ++i) {
    EXPECT_NE(tagList_[i].title_, nullptr) << "Entry " << i << " has null title";
  }
}

// Test OffsetTime entries
TEST_F(ExifTagListTest_1358, OffsetTimeEntries_1358) {
  bool foundOT = false, foundOTO = false, foundOTD = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 36880) {
      EXPECT_STREQ(tagList_[i].name_, "OffsetTime");
      EXPECT_EQ(tagList_[i].count_, 7);
      foundOT = true;
    } else if (tagList_[i].tag_ == 36881) {
      EXPECT_STREQ(tagList_[i].name_, "OffsetTimeOriginal");
      EXPECT_EQ(tagList_[i].count_, 7);
      foundOTO = true;
    } else if (tagList_[i].tag_ == 36882) {
      EXPECT_STREQ(tagList_[i].name_, "OffsetTimeDigitized");
      EXPECT_EQ(tagList_[i].count_, 7);
      foundOTD = true;
    }
  }
  EXPECT_TRUE(foundOT);
  EXPECT_TRUE(foundOTO);
  EXPECT_TRUE(foundOTD);
}

// Test Temperature, Humidity, Pressure, WaterDepth, Acceleration, CameraElevationAngle
TEST_F(ExifTagListTest_1358, AmbientConditionTags_1358) {
  bool foundTemp = false, foundHumid = false, foundPressure = false;
  bool foundWater = false, foundAccel = false, foundAngle = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 37888) { foundTemp = true; EXPECT_STREQ(tagList_[i].name_, "Temperature"); }
    if (tagList_[i].tag_ == 37889) { foundHumid = true; EXPECT_STREQ(tagList_[i].name_, "Humidity"); }
    if (tagList_[i].tag_ == 37890) { foundPressure = true; EXPECT_STREQ(tagList_[i].name_, "Pressure"); }
    if (tagList_[i].tag_ == 37891) { foundWater = true; EXPECT_STREQ(tagList_[i].name_, "WaterDepth"); }
    if (tagList_[i].tag_ == 37892) { foundAccel = true; EXPECT_STREQ(tagList_[i].name_, "Acceleration"); }
    if (tagList_[i].tag_ == 37893) { foundAngle = true; EXPECT_STREQ(tagList_[i].name_, "CameraElevationAngle"); }
  }
  EXPECT_TRUE(foundTemp);
  EXPECT_TRUE(foundHumid);
  EXPECT_TRUE(foundPressure);
  EXPECT_TRUE(foundWater);
  EXPECT_TRUE(foundAccel);
  EXPECT_TRUE(foundAngle);
}

// Test FlashpixVersion entry
TEST_F(ExifTagListTest_1358, FlashpixVersionEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 40960) {
      EXPECT_STREQ(tagList_[i].name_, "FlashpixVersion");
      EXPECT_EQ(tagList_[i].count_, 4);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test InteroperabilityTag entry
TEST_F(ExifTagListTest_1358, InteroperabilityTagEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 40965) {
      EXPECT_STREQ(tagList_[i].name_, "InteroperabilityTag");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test RelatedSoundFile entry has count 13
TEST_F(ExifTagListTest_1358, RelatedSoundFileEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 40964) {
      EXPECT_STREQ(tagList_[i].name_, "RelatedSoundFile");
      EXPECT_EQ(tagList_[i].count_, 13);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test LensSpecification entry has count 4
TEST_F(ExifTagListTest_1358, LensSpecificationEntry_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42034) {
      EXPECT_STREQ(tagList_[i].name_, "LensSpecification");
      EXPECT_EQ(tagList_[i].count_, 4);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test new Exif 3.0 tags: ImageTitle, Photographer, ImageEditor
TEST_F(ExifTagListTest_1358, Exif30NewTags_1358) {
  bool foundTitle = false, foundPhotographer = false, foundEditor = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42038) { foundTitle = true; EXPECT_STREQ(tagList_[i].name_, "ImageTitle"); }
    if (tagList_[i].tag_ == 42039) { foundPhotographer = true; EXPECT_STREQ(tagList_[i].name_, "Photographer"); }
    if (tagList_[i].tag_ == 42040) { foundEditor = true; EXPECT_STREQ(tagList_[i].name_, "ImageEditor"); }
  }
  EXPECT_TRUE(foundTitle);
  EXPECT_TRUE(foundPhotographer);
  EXPECT_TRUE(foundEditor);
}

// Test firmware and software tags
TEST_F(ExifTagListTest_1358, FirmwareAndSoftwareTags_1358) {
  bool foundFW = false, foundRAW = false, foundImgEdit = false, foundMeta = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 42041) { foundFW = true; EXPECT_STREQ(tagList_[i].name_, "CameraFirmware"); }
    if (tagList_[i].tag_ == 42042) { foundRAW = true; EXPECT_STREQ(tagList_[i].name_, "RAWDevelopingSoftware"); }
    if (tagList_[i].tag_ == 42043) { foundImgEdit = true; EXPECT_STREQ(tagList_[i].name_, "ImageEditingSoftware"); }
    if (tagList_[i].tag_ == 42044) { foundMeta = true; EXPECT_STREQ(tagList_[i].name_, "MetadataEditingSoftware"); }
  }
  EXPECT_TRUE(foundFW);
  EXPECT_TRUE(foundRAW);
  EXPECT_TRUE(foundImgEdit);
  EXPECT_TRUE(foundMeta);
}

// Test SubjectArea entry has count -1 (variable)
TEST_F(ExifTagListTest_1358, SubjectAreaVariableCount_1358) {
  bool found = false;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ == 37396) {
      EXPECT_STREQ(tagList_[i].name_, "SubjectArea");
      EXPECT_EQ(tagList_[i].count_, -1);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test total number of known distinct tags
TEST_F(ExifTagListTest_1358, TotalTagCount_1358) {
  // The array has 90 entries (indices 0-89), with last being sentinel
  int count = 0;
  for (int i = 0; i < 90; ++i) {
    if (tagList_[i].tag_ != 65535) {
      count++;
    }
  }
  EXPECT_EQ(count, 89);  // 89 real tags + 1 sentinel = 90 total
}

}  // namespace
