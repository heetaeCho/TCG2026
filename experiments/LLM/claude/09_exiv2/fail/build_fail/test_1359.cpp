#include <gtest/gtest.h>
#include "exiv2/tags.h"
#include "tags_int.hpp"

namespace {

class GpsTagListTest_1359 : public ::testing::Test {
 protected:
  const Exiv2::TagInfo* tagList_;

  void SetUp() override {
    tagList_ = Exiv2::Internal::gpsTagList();
  }
};

// Test that gpsTagList returns a non-null pointer
TEST_F(GpsTagListTest_1359, ReturnsNonNull_1359) {
  ASSERT_NE(tagList_, nullptr);
}

// Test the first entry: GPSVersionID (tag 0)
TEST_F(GpsTagListTest_1359, FirstEntryIsGPSVersionID_1359) {
  EXPECT_EQ(tagList_[0].tag_, 0);
  EXPECT_STREQ(tagList_[0].name_, "GPSVersionID");
  EXPECT_STREQ(tagList_[0].title_, "GPS Version ID");
  EXPECT_EQ(tagList_[0].ifdId_, Exiv2::Internal::IfdId::gpsId);
  EXPECT_EQ(tagList_[0].sectionId_, Exiv2::Internal::SectionId::gpsTags);
  EXPECT_EQ(tagList_[0].typeId_, Exiv2::unsignedByte);
  EXPECT_EQ(tagList_[0].count_, 4);
}

// Test GPSLatitudeRef (tag 1)
TEST_F(GpsTagListTest_1359, SecondEntryIsGPSLatitudeRef_1359) {
  EXPECT_EQ(tagList_[1].tag_, 1);
  EXPECT_STREQ(tagList_[1].name_, "GPSLatitudeRef");
  EXPECT_STREQ(tagList_[1].title_, "GPS Latitude Reference");
  EXPECT_EQ(tagList_[1].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[1].count_, 2);
}

// Test GPSLatitude (tag 2)
TEST_F(GpsTagListTest_1359, ThirdEntryIsGPSLatitude_1359) {
  EXPECT_EQ(tagList_[2].tag_, 2);
  EXPECT_STREQ(tagList_[2].name_, "GPSLatitude");
  EXPECT_STREQ(tagList_[2].title_, "GPS Latitude");
  EXPECT_EQ(tagList_[2].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[2].count_, 3);
}

// Test GPSLongitudeRef (tag 3)
TEST_F(GpsTagListTest_1359, FourthEntryIsGPSLongitudeRef_1359) {
  EXPECT_EQ(tagList_[3].tag_, 3);
  EXPECT_STREQ(tagList_[3].name_, "GPSLongitudeRef");
  EXPECT_EQ(tagList_[3].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[3].count_, 2);
}

// Test GPSLongitude (tag 4)
TEST_F(GpsTagListTest_1359, FifthEntryIsGPSLongitude_1359) {
  EXPECT_EQ(tagList_[4].tag_, 4);
  EXPECT_STREQ(tagList_[4].name_, "GPSLongitude");
  EXPECT_EQ(tagList_[4].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[4].count_, 3);
}

// Test GPSAltitudeRef (tag 5)
TEST_F(GpsTagListTest_1359, SixthEntryIsGPSAltitudeRef_1359) {
  EXPECT_EQ(tagList_[5].tag_, 5);
  EXPECT_STREQ(tagList_[5].name_, "GPSAltitudeRef");
  EXPECT_EQ(tagList_[5].typeId_, Exiv2::unsignedByte);
  EXPECT_EQ(tagList_[5].count_, 1);
}

// Test GPSAltitude (tag 6)
TEST_F(GpsTagListTest_1359, SeventhEntryIsGPSAltitude_1359) {
  EXPECT_EQ(tagList_[6].tag_, 6);
  EXPECT_STREQ(tagList_[6].name_, "GPSAltitude");
  EXPECT_EQ(tagList_[6].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[6].count_, 1);
}

// Test GPSTimeStamp (tag 7)
TEST_F(GpsTagListTest_1359, EighthEntryIsGPSTimeStamp_1359) {
  EXPECT_EQ(tagList_[7].tag_, 7);
  EXPECT_STREQ(tagList_[7].name_, "GPSTimeStamp");
  EXPECT_EQ(tagList_[7].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[7].count_, 3);
}

// Test GPSSatellites (tag 8)
TEST_F(GpsTagListTest_1359, NinthEntryIsGPSSatellites_1359) {
  EXPECT_EQ(tagList_[8].tag_, 8);
  EXPECT_STREQ(tagList_[8].name_, "GPSSatellites");
  EXPECT_EQ(tagList_[8].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[8].count_, 0);
}

// Test GPSStatus (tag 9)
TEST_F(GpsTagListTest_1359, TenthEntryIsGPSStatus_1359) {
  EXPECT_EQ(tagList_[9].tag_, 9);
  EXPECT_STREQ(tagList_[9].name_, "GPSStatus");
  EXPECT_EQ(tagList_[9].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[9].count_, 2);
}

// Test GPSMeasureMode (tag 10)
TEST_F(GpsTagListTest_1359, EleventhEntryIsGPSMeasureMode_1359) {
  EXPECT_EQ(tagList_[10].tag_, 10);
  EXPECT_STREQ(tagList_[10].name_, "GPSMeasureMode");
  EXPECT_EQ(tagList_[10].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[10].count_, 2);
}

// Test GPSDOP (tag 11)
TEST_F(GpsTagListTest_1359, TwelfthEntryIsGPSDOP_1359) {
  EXPECT_EQ(tagList_[11].tag_, 11);
  EXPECT_STREQ(tagList_[11].name_, "GPSDOP");
  EXPECT_EQ(tagList_[11].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[11].count_, 1);
}

// Test GPSSpeedRef (tag 12)
TEST_F(GpsTagListTest_1359, ThirteenthEntryIsGPSSpeedRef_1359) {
  EXPECT_EQ(tagList_[12].tag_, 12);
  EXPECT_STREQ(tagList_[12].name_, "GPSSpeedRef");
  EXPECT_EQ(tagList_[12].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[12].count_, 2);
}

// Test GPSSpeed (tag 13)
TEST_F(GpsTagListTest_1359, FourteenthEntryIsGPSSpeed_1359) {
  EXPECT_EQ(tagList_[13].tag_, 13);
  EXPECT_STREQ(tagList_[13].name_, "GPSSpeed");
  EXPECT_EQ(tagList_[13].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[13].count_, 1);
}

// Test GPSTrackRef (tag 14)
TEST_F(GpsTagListTest_1359, FifteenthEntryIsGPSTrackRef_1359) {
  EXPECT_EQ(tagList_[14].tag_, 14);
  EXPECT_STREQ(tagList_[14].name_, "GPSTrackRef");
  EXPECT_EQ(tagList_[14].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[14].count_, 2);
}

// Test GPSTrack (tag 15)
TEST_F(GpsTagListTest_1359, SixteenthEntryIsGPSTrack_1359) {
  EXPECT_EQ(tagList_[15].tag_, 15);
  EXPECT_STREQ(tagList_[15].name_, "GPSTrack");
  EXPECT_EQ(tagList_[15].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[15].count_, 1);
}

// Test GPSImgDirectionRef (tag 16)
TEST_F(GpsTagListTest_1359, SeventeenthEntryIsGPSImgDirectionRef_1359) {
  EXPECT_EQ(tagList_[16].tag_, 16);
  EXPECT_STREQ(tagList_[16].name_, "GPSImgDirectionRef");
  EXPECT_EQ(tagList_[16].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[16].count_, 2);
}

// Test GPSImgDirection (tag 17)
TEST_F(GpsTagListTest_1359, EighteenthEntryIsGPSImgDirection_1359) {
  EXPECT_EQ(tagList_[17].tag_, 17);
  EXPECT_STREQ(tagList_[17].name_, "GPSImgDirection");
  EXPECT_EQ(tagList_[17].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[17].count_, 1);
}

// Test GPSMapDatum (tag 18)
TEST_F(GpsTagListTest_1359, NineteenthEntryIsGPSMapDatum_1359) {
  EXPECT_EQ(tagList_[18].tag_, 18);
  EXPECT_STREQ(tagList_[18].name_, "GPSMapDatum");
  EXPECT_EQ(tagList_[18].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[18].count_, 0);
}

// Test GPSDestLatitudeRef (tag 19)
TEST_F(GpsTagListTest_1359, TwentiethEntryIsGPSDestLatitudeRef_1359) {
  EXPECT_EQ(tagList_[19].tag_, 19);
  EXPECT_STREQ(tagList_[19].name_, "GPSDestLatitudeRef");
  EXPECT_EQ(tagList_[19].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[19].count_, 2);
}

// Test GPSDestLatitude (tag 20)
TEST_F(GpsTagListTest_1359, TwentyFirstEntryIsGPSDestLatitude_1359) {
  EXPECT_EQ(tagList_[20].tag_, 20);
  EXPECT_STREQ(tagList_[20].name_, "GPSDestLatitude");
  EXPECT_EQ(tagList_[20].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[20].count_, 3);
}

// Test GPSDestLongitudeRef (tag 21)
TEST_F(GpsTagListTest_1359, TwentySecondEntryIsGPSDestLongitudeRef_1359) {
  EXPECT_EQ(tagList_[21].tag_, 21);
  EXPECT_STREQ(tagList_[21].name_, "GPSDestLongitudeRef");
  EXPECT_EQ(tagList_[21].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[21].count_, 2);
}

// Test GPSDestLongitude (tag 22)
TEST_F(GpsTagListTest_1359, TwentyThirdEntryIsGPSDestLongitude_1359) {
  EXPECT_EQ(tagList_[22].tag_, 22);
  EXPECT_STREQ(tagList_[22].name_, "GPSDestLongitude");
  EXPECT_EQ(tagList_[22].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[22].count_, 3);
}

// Test GPSDestBearingRef (tag 23)
TEST_F(GpsTagListTest_1359, TwentyFourthEntryIsGPSDestBearingRef_1359) {
  EXPECT_EQ(tagList_[23].tag_, 23);
  EXPECT_STREQ(tagList_[23].name_, "GPSDestBearingRef");
  EXPECT_EQ(tagList_[23].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[23].count_, 2);
}

// Test GPSDestBearing (tag 24)
TEST_F(GpsTagListTest_1359, TwentyFifthEntryIsGPSDestBearing_1359) {
  EXPECT_EQ(tagList_[24].tag_, 24);
  EXPECT_STREQ(tagList_[24].name_, "GPSDestBearing");
  EXPECT_EQ(tagList_[24].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[24].count_, 1);
}

// Test GPSDestDistanceRef (tag 25)
TEST_F(GpsTagListTest_1359, TwentySixthEntryIsGPSDestDistanceRef_1359) {
  EXPECT_EQ(tagList_[25].tag_, 25);
  EXPECT_STREQ(tagList_[25].name_, "GPSDestDistanceRef");
  EXPECT_EQ(tagList_[25].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[25].count_, 2);
}

// Test GPSDestDistance (tag 26)
TEST_F(GpsTagListTest_1359, TwentySeventhEntryIsGPSDestDistance_1359) {
  EXPECT_EQ(tagList_[26].tag_, 26);
  EXPECT_STREQ(tagList_[26].name_, "GPSDestDistance");
  EXPECT_EQ(tagList_[26].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[26].count_, 1);
}

// Test GPSProcessingMethod (tag 27)
TEST_F(GpsTagListTest_1359, TwentyEighthEntryIsGPSProcessingMethod_1359) {
  EXPECT_EQ(tagList_[27].tag_, 27);
  EXPECT_STREQ(tagList_[27].name_, "GPSProcessingMethod");
  EXPECT_EQ(tagList_[27].typeId_, Exiv2::comment);
  EXPECT_EQ(tagList_[27].count_, 0);
}

// Test GPSAreaInformation (tag 28)
TEST_F(GpsTagListTest_1359, TwentyNinthEntryIsGPSAreaInformation_1359) {
  EXPECT_EQ(tagList_[28].tag_, 28);
  EXPECT_STREQ(tagList_[28].name_, "GPSAreaInformation");
  EXPECT_EQ(tagList_[28].typeId_, Exiv2::comment);
  EXPECT_EQ(tagList_[28].count_, 0);
}

// Test GPSDateStamp (tag 29)
TEST_F(GpsTagListTest_1359, ThirtiethEntryIsGPSDateStamp_1359) {
  EXPECT_EQ(tagList_[29].tag_, 29);
  EXPECT_STREQ(tagList_[29].name_, "GPSDateStamp");
  EXPECT_EQ(tagList_[29].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[29].count_, 11);
}

// Test GPSDifferential (tag 30)
TEST_F(GpsTagListTest_1359, ThirtyFirstEntryIsGPSDifferential_1359) {
  EXPECT_EQ(tagList_[30].tag_, 30);
  EXPECT_STREQ(tagList_[30].name_, "GPSDifferential");
  EXPECT_EQ(tagList_[30].typeId_, Exiv2::unsignedShort);
  EXPECT_EQ(tagList_[30].count_, 1);
}

// Test GPSHPositioningError (tag 31)
TEST_F(GpsTagListTest_1359, ThirtySecondEntryIsGPSHPositioningError_1359) {
  EXPECT_EQ(tagList_[31].tag_, 31);
  EXPECT_STREQ(tagList_[31].name_, "GPSHPositioningError");
  EXPECT_EQ(tagList_[31].typeId_, Exiv2::unsignedRational);
  EXPECT_EQ(tagList_[31].count_, 1);
}

// Test the sentinel/terminator entry (tag 65535)
TEST_F(GpsTagListTest_1359, LastEntryIsSentinel_1359) {
  EXPECT_EQ(tagList_[32].tag_, 65535);
  EXPECT_STREQ(tagList_[32].name_, "(UnknownGpsTag)");
  EXPECT_STREQ(tagList_[32].title_, "Unknown GPSInfo tag");
  EXPECT_EQ(tagList_[32].typeId_, Exiv2::asciiString);
  EXPECT_EQ(tagList_[32].count_, -1);
}

// Test that all entries have gpsId as their IFD ID
TEST_F(GpsTagListTest_1359, AllEntriesHaveGpsIfdId_1359) {
  for (int i = 0; i < 33; ++i) {
    EXPECT_EQ(tagList_[i].ifdId_, Exiv2::Internal::IfdId::gpsId)
        << "Entry at index " << i << " does not have gpsId";
  }
}

// Test that all entries have gpsTags as their section ID
TEST_F(GpsTagListTest_1359, AllEntriesHaveGpsSectionId_1359) {
  for (int i = 0; i < 33; ++i) {
    EXPECT_EQ(tagList_[i].sectionId_, Exiv2::Internal::SectionId::gpsTags)
        << "Entry at index " << i << " does not have gpsTags section";
  }
}

// Test that tag numbers are sequential from 0 to 31 (first 32 entries)
TEST_F(GpsTagListTest_1359, TagNumbersAreSequential_1359) {
  for (int i = 0; i < 32; ++i) {
    EXPECT_EQ(tagList_[i].tag_, static_cast<uint16_t>(i))
        << "Entry at index " << i << " has unexpected tag number";
  }
}

// Test that the function returns the same pointer on multiple calls (it's a static array)
TEST_F(GpsTagListTest_1359, ReturnsSamePointerOnMultipleCalls_1359) {
  const Exiv2::TagInfo* first = Exiv2::Internal::gpsTagList();
  const Exiv2::TagInfo* second = Exiv2::Internal::gpsTagList();
  EXPECT_EQ(first, second);
}

// Test that all name fields are non-null
TEST_F(GpsTagListTest_1359, AllNamesAreNonNull_1359) {
  for (int i = 0; i < 33; ++i) {
    EXPECT_NE(tagList_[i].name_, nullptr)
        << "Entry at index " << i << " has null name";
  }
}

// Test that all title fields are non-null
TEST_F(GpsTagListTest_1359, AllTitlesAreNonNull_1359) {
  for (int i = 0; i < 33; ++i) {
    EXPECT_NE(tagList_[i].title_, nullptr)
        << "Entry at index " << i << " has null title";
  }
}

// Test that all desc fields are non-null
TEST_F(GpsTagListTest_1359, AllDescsAreNonNull_1359) {
  for (int i = 0; i < 33; ++i) {
    EXPECT_NE(tagList_[i].desc_, nullptr)
        << "Entry at index " << i << " has null desc";
  }
}

// Test total count of entries is 33 (32 real tags + 1 sentinel)
TEST_F(GpsTagListTest_1359, TotalEntryCount_1359) {
  int count = 0;
  while (tagList_[count].tag_ != 65535) {
    ++count;
  }
  // 32 real entries before the sentinel
  EXPECT_EQ(count, 32);
}

}  // namespace
