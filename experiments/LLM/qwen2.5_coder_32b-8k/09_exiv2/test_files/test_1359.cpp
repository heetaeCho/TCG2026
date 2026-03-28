#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/tags_int.cpp"



namespace Exiv2 {

    namespace Internal {

        struct TagInfo;

        const TagInfo* gpsTagList();

    }

}



using namespace Exiv2::Internal;



TEST_F(GPSTagListTest_1359, ReturnsNonNullPointer_1359) {

    EXPECT_NE(gpsTagList(), nullptr);

}



TEST_F(GPSTagListTest_1359, CorrectNumberOfTags_1359) {

    const TagInfo* tags = gpsTagList();

    int count = 0;

    while (tags[count].tag_ != 65535) {

        ++count;

    }

    EXPECT_EQ(count, 32);

}



TEST_F(GPSTagListTest_1359, FirstTagProperties_1359) {

    const TagInfo* tags = gpsTagList();

    EXPECT_EQ(tags[0].tag_, 0);

    EXPECT_STREQ(tags[0].name_, "GPSVersionID");

    EXPECT_STREQ(tags[0].title_, "GPS Version ID");

    EXPECT_STREQ(tags[0].description_, "Indicates the version of <GPSInfoIFD>. The version is given as 2.0.0.0. This tag is mandatory when <GPSInfo> tag is present. (Note: The <GPSVersionID> tag is given in bytes, unlike the <ExifVersion> tag. When the version is 2.0.0.0, the tag value is 02000000.H).");

    // Additional checks can be added for other fields if needed

}



TEST_F(GPSTagListTest_1359, LastTagProperties_1359) {

    const TagInfo* tags = gpsTagList();

    int count = 0;

    while (tags[count].tag_ != 65535) {

        ++count;

    }

    EXPECT_EQ(tags[count - 1].tag_, 65535);

    EXPECT_STREQ(tags[count - 1].name_, "(UnknownGpsTag)");

    EXPECT_STREQ(tags[count - 1].title_, "Unknown GPSInfo tag");

    EXPECT_STREQ(tags[count - 1].description_, "Unknown GPSInfo tag");

    // Additional checks can be added for other fields if needed

}



TEST_F(GPSTagListTest_1359, BoundaryTagProperties_1359) {

    const TagInfo* tags = gpsTagList();

    EXPECT_EQ(tags[15].tag_, 15);

    EXPECT_STREQ(tags[15].name_, "GPSTrack");

    EXPECT_STREQ(tags[15].title_, "GPS Track");

    EXPECT_STREQ(tags[15].description_, "Indicates the direction of GPS receiver movement. The range of values is from 0.00 to 359.99.");

    // Additional checks can be added for other fields if needed

}



TEST_F(GPSTagListTest_1359, InvalidTagAccess_1359) {

    const TagInfo* tags = gpsTagList();

    int count = 0;

    while (tags[count].tag_ != 65535) {

        ++count;

    }

    EXPECT_EQ(tags[count].tag_, 65535);

}
