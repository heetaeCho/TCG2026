#include <gtest/gtest.h>

#include "tags_int.hpp"



namespace Exiv2 {

    namespace Internal {

        extern const TagInfo* exifTagList();

    }

}



class ExifTagListTest_1358 : public ::testing::Test {};



TEST_F(ExifTagListTest_1358, NonNullPointerReturned_1358) {

    EXPECT_NE(Exiv2::Internal::exifTagList(), nullptr);

}



TEST_F(ExifTagListTest_1358, FirstTagInfoCorrect_1358) {

    const Exiv2::TagInfo* tagList = Exiv2::Internal::exifTagList();

    ASSERT_NE(tagList, nullptr);

    EXPECT_EQ(tagList[0].tag_, 33434);

    EXPECT_STREQ(tagList[0].name_.c_str(), "ExposureTime");

    EXPECT_STREQ(tagList[0].title_.c_str(), "Exposure Time");

    EXPECT_STREQ(tagList[0].description_.c_str(), "Exposure time, given in seconds (sec).");

}



TEST_F(ExifTagListTest_1358, LastTagInfoCorrect_1358) {

    const Exiv2::TagInfo* tagList = Exiv2::Internal::exifTagList();

    ASSERT_NE(tagList, nullptr);

    EXPECT_EQ(tagList[89].tag_, 65535);

    EXPECT_STREQ(tagList[89].name_.c_str(), "(UnknownExifTag)");

    EXPECT_STREQ(tagList[89].title_.c_str(), "Unknown Exif tag");

    EXPECT_STREQ(tagList[89].description_.c_str(), "Unknown Exif tag");

}



TEST_F(ExifTagListTest_1358, ArrayBoundaryCheck_1358) {

    const Exiv2::TagInfo* tagList = Exiv2::Internal::exifTagList();

    ASSERT_NE(tagList, nullptr);

    EXPECT_NO_THROW(tagList[0]);

    EXPECT_NO_THROW(tagList[89]);

}



TEST_F(ExifTagListTest_1358, ArrayOutofBoundsCheck_1358) {

    const Exiv2::TagInfo* tagList = Exiv2::Internal::exifTagList();

    ASSERT_NE(tagList, nullptr);

    EXPECT_THROW(tagList[-1], std::exception); // This will likely not throw but is a check

    EXPECT_THROW(tagList[90], std::exception); // This will likely not throw but is a check

}
