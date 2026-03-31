#include <gtest/gtest.h>
#include <cstring>
#include "exiv2/tags.h"
#include "tags_int.hpp"

using namespace Exiv2::Internal;

class IfdTagListTest_1357 : public ::testing::Test {
 protected:
  const TagInfo* tagList_;

  void SetUp() override {
    tagList_ = ifdTagList();
  }
};

// Test that ifdTagList returns a non-null pointer
TEST_F(IfdTagListTest_1357, ReturnsNonNull_1357) {
  ASSERT_NE(tagList_, nullptr);
}

// Test the first entry in the tag list (ProcessingSoftware, tag 11)
TEST_F(IfdTagListTest_1357, FirstEntryIsProcessingSoftware_1357) {
  EXPECT_EQ(tagList_[0].tag_, 11);
  EXPECT_STREQ(tagList_[0].name_, "ProcessingSoftware");
  EXPECT_STREQ(tagList_[0].title_, "Processing Software");
}

// Test the second entry (NewSubfileType, tag 254)
TEST_F(IfdTagListTest_1357, SecondEntryIsNewSubfileType_1357) {
  EXPECT_EQ(tagList_[1].tag_, 254);
  EXPECT_STREQ(tagList_[1].name_, "NewSubfileType");
  EXPECT_STREQ(tagList_[1].title_, "New Subfile Type");
}

// Test ImageWidth entry (tag 256)
TEST_F(IfdTagListTest_1357, ImageWidthEntry_1357) {
  EXPECT_EQ(tagList_[3].tag_, 256);
  EXPECT_STREQ(tagList_[3].name_, "ImageWidth");
  EXPECT_STREQ(tagList_[3].title_, "Image Width");
  EXPECT_EQ(tagList_[3].ifdId_, IfdId::ifd0Id);
}

// Test ImageLength entry (tag 257)
TEST_F(IfdTagListTest_1357, ImageLengthEntry_1357) {
  EXPECT_EQ(tagList_[4].tag_, 257);
  EXPECT_STREQ(tagList_[4].name_, "ImageLength");
  EXPECT_STREQ(tagList_[4].title_, "Image Length");
}

// Test BitsPerSample entry (tag 258)
TEST_F(IfdTagListTest_1357, BitsPerSampleEntry_1357) {
  EXPECT_EQ(tagList_[5].tag_, 258);
  EXPECT_STREQ(tagList_[5].name_, "BitsPerSample");
  EXPECT_EQ(tagList_[5].count_, 3);
}

// Test Compression entry (tag 259)
TEST_F(IfdTagListTest_1357, CompressionEntry_1357) {
  EXPECT_EQ(tagList_[6].tag_, 259);
  EXPECT_STREQ(tagList_[6].name_, "Compression");
  EXPECT_EQ(tagList_[6].count_, 1);
}

// Test Orientation entry (tag 274)
TEST_F(IfdTagListTest_1357, OrientationEntry_1357) {
  // Orientation is at a known position; search for it
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 274) {
      EXPECT_STREQ(tagList_[i].name_, "Orientation");
      EXPECT_STREQ(tagList_[i].title_, "Orientation");
      EXPECT_EQ(tagList_[i].count_, 1);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test Copyright entry (tag 33432)
TEST_F(IfdTagListTest_1357, CopyrightEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 33432) {
      EXPECT_STREQ(tagList_[i].name_, "Copyright");
      EXPECT_STREQ(tagList_[i].title_, "Copyright");
      EXPECT_EQ(tagList_[i].ifdId_, IfdId::ifd0Id);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test ExifTag entry (tag 34665)
TEST_F(IfdTagListTest_1357, ExifTagEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 34665) {
      EXPECT_STREQ(tagList_[i].name_, "ExifTag");
      EXPECT_STREQ(tagList_[i].title_, "Exif IFD Pointer");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test GPSTag entry (tag 34853)
TEST_F(IfdTagListTest_1357, GPSTagEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 34853) {
      EXPECT_STREQ(tagList_[i].name_, "GPSTag");
      EXPECT_STREQ(tagList_[i].title_, "GPS Info IFD Pointer");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test the last entry is the sentinel (tag 65535)
TEST_F(IfdTagListTest_1357, LastEntryIsSentinel_1357) {
  // The array has 257 entries (index 0..256), the last one is the sentinel
  EXPECT_EQ(tagList_[256].tag_, 65535);
  EXPECT_STREQ(tagList_[256].name_, "(UnknownIfdTag)");
  EXPECT_STREQ(tagList_[256].title_, "Unknown IFD tag");
}

// Test DNGVersion entry (tag 50706)
TEST_F(IfdTagListTest_1357, DNGVersionEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 50706) {
      EXPECT_STREQ(tagList_[i].name_, "DNGVersion");
      EXPECT_STREQ(tagList_[i].title_, "DNG version");
      EXPECT_EQ(tagList_[i].count_, 4);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that all non-sentinel entries have ifd0Id
TEST_F(IfdTagListTest_1357, AllEntriesHaveIfd0Id_1357) {
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    EXPECT_EQ(tagList_[i].ifdId_, IfdId::ifd0Id)
        << "Entry at index " << i << " (tag " << tagList_[i].tag_
        << ") does not have ifd0Id";
  }
}

// Test that the sentinel also has ifd0Id
TEST_F(IfdTagListTest_1357, SentinelHasIfd0Id_1357) {
  EXPECT_EQ(tagList_[256].ifdId_, IfdId::ifd0Id);
}

// Test that all entries have non-null name
TEST_F(IfdTagListTest_1357, AllEntriesHaveNonNullName_1357) {
  for (int i = 0; i <= 256; ++i) {
    EXPECT_NE(tagList_[i].name_, nullptr)
        << "Entry at index " << i << " has null name";
  }
}

// Test that all entries have non-null title
TEST_F(IfdTagListTest_1357, AllEntriesHaveNonNullTitle_1357) {
  for (int i = 0; i <= 256; ++i) {
    EXPECT_NE(tagList_[i].title_, nullptr)
        << "Entry at index " << i << " has null title";
  }
}

// Test that all entries have non-null desc
TEST_F(IfdTagListTest_1357, AllEntriesHaveNonNullDesc_1357) {
  for (int i = 0; i <= 256; ++i) {
    EXPECT_NE(tagList_[i].desc_, nullptr)
        << "Entry at index " << i << " has null desc";
  }
}

// Test the Make tag (tag 271)
TEST_F(IfdTagListTest_1357, MakeEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 271) {
      EXPECT_STREQ(tagList_[i].name_, "Make");
      EXPECT_STREQ(tagList_[i].title_, "Manufacturer");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test Model entry (tag 272)
TEST_F(IfdTagListTest_1357, ModelEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 272) {
      EXPECT_STREQ(tagList_[i].name_, "Model");
      EXPECT_STREQ(tagList_[i].title_, "Model");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test Software entry (tag 305)
TEST_F(IfdTagListTest_1357, SoftwareEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 305) {
      EXPECT_STREQ(tagList_[i].name_, "Software");
      EXPECT_STREQ(tagList_[i].title_, "Software");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test DateTime entry (tag 306)
TEST_F(IfdTagListTest_1357, DateTimeEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 306) {
      EXPECT_STREQ(tagList_[i].name_, "DateTime");
      EXPECT_EQ(tagList_[i].count_, 20);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test ExposureTime entry (tag 33434)
TEST_F(IfdTagListTest_1357, ExposureTimeEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 33434) {
      EXPECT_STREQ(tagList_[i].name_, "ExposureTime");
      EXPECT_STREQ(tagList_[i].title_, "Exposure Time");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test FNumber entry (tag 33437)
TEST_F(IfdTagListTest_1357, FNumberEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 33437) {
      EXPECT_STREQ(tagList_[i].name_, "FNumber");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that calling ifdTagList multiple times returns the same pointer (static data)
TEST_F(IfdTagListTest_1357, ConsistentPointerOnMultipleCalls_1357) {
  const TagInfo* firstCall = ifdTagList();
  const TagInfo* secondCall = ifdTagList();
  EXPECT_EQ(firstCall, secondCall);
}

// Test that tags are generally in ascending order (not strictly required,
// but the data appears to be mostly ordered)
TEST_F(IfdTagListTest_1357, TagsGenerallyAscending_1357) {
  // Just verify a few known sequential entries are in order
  // First few: 11, 254, 255, 256, 257, 258, 259
  EXPECT_LT(tagList_[0].tag_, tagList_[1].tag_);
  EXPECT_LT(tagList_[1].tag_, tagList_[2].tag_);
  EXPECT_LT(tagList_[2].tag_, tagList_[3].tag_);
  EXPECT_LT(tagList_[3].tag_, tagList_[4].tag_);
}

// Test Rating entry (tag 18246) - Windows-specific
TEST_F(IfdTagListTest_1357, RatingEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 18246) {
      EXPECT_STREQ(tagList_[i].name_, "Rating");
      EXPECT_STREQ(tagList_[i].title_, "Windows Rating");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test XPTitle entry (tag 40091) - Windows-specific
TEST_F(IfdTagListTest_1357, XPTitleEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 40091) {
      EXPECT_STREQ(tagList_[i].name_, "XPTitle");
      EXPECT_STREQ(tagList_[i].title_, "Windows Title");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test the total number of entries (256 real entries + 1 sentinel = 257)
TEST_F(IfdTagListTest_1357, TotalEntryCount_1357) {
  int count = 0;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    ++count;
  }
  EXPECT_EQ(count, 256);
}

// Test SubfileType entry (tag 255)
TEST_F(IfdTagListTest_1357, SubfileTypeEntry_1357) {
  EXPECT_EQ(tagList_[2].tag_, 255);
  EXPECT_STREQ(tagList_[2].name_, "SubfileType");
  EXPECT_STREQ(tagList_[2].title_, "Subfile Type");
}

// Test ResolutionUnit entry (tag 296)
TEST_F(IfdTagListTest_1357, ResolutionUnitEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 296) {
      EXPECT_STREQ(tagList_[i].name_, "ResolutionUnit");
      EXPECT_EQ(tagList_[i].count_, 1);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test YCbCrPositioning entry (tag 531)
TEST_F(IfdTagListTest_1357, YCbCrPositioningEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 531) {
      EXPECT_STREQ(tagList_[i].name_, "YCbCrPositioning");
      EXPECT_EQ(tagList_[i].count_, 1);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test DefaultUserCrop entry (tag 51125)
TEST_F(IfdTagListTest_1357, DefaultUserCropEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 51125) {
      EXPECT_STREQ(tagList_[i].name_, "DefaultUserCrop");
      EXPECT_EQ(tagList_[i].count_, 4);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test JXLDistance entry (tag 52553)
TEST_F(IfdTagListTest_1357, JXLDistanceEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 52553) {
      EXPECT_STREQ(tagList_[i].name_, "JXLDistance");
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test that printValue function pointers are non-null for all entries
TEST_F(IfdTagListTest_1357, AllEntriesHaveNonNullPrintFct_1357) {
  for (int i = 0; i <= 256; ++i) {
    EXPECT_NE(tagList_[i].printFct_, nullptr)
        << "Entry at index " << i << " (tag " << tagList_[i].tag_
        << ") has null printFct";
  }
}

// Test sentinel entry section
TEST_F(IfdTagListTest_1357, SentinelSectionIdNotSet_1357) {
  EXPECT_EQ(tagList_[256].sectionId_, SectionId::sectionIdNotSet);
}

// Test Artist entry (tag 315)
TEST_F(IfdTagListTest_1357, ArtistEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 315) {
      EXPECT_STREQ(tagList_[i].name_, "Artist");
      EXPECT_STREQ(tagList_[i].title_, "Artist");
      EXPECT_EQ(tagList_[i].sectionId_, SectionId::otherTags);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}

// Test ImageDescription entry (tag 270)
TEST_F(IfdTagListTest_1357, ImageDescriptionEntry_1357) {
  bool found = false;
  for (int i = 0; tagList_[i].tag_ != 65535; ++i) {
    if (tagList_[i].tag_ == 270) {
      EXPECT_STREQ(tagList_[i].name_, "ImageDescription");
      EXPECT_STREQ(tagList_[i].title_, "Image Description");
      EXPECT_EQ(tagList_[i].sectionId_, SectionId::otherTags);
      found = true;
      break;
    }
  }
  EXPECT_TRUE(found);
}
