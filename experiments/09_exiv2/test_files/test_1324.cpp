#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifTagsTest : public ::testing::Test {

protected:

    ExifTags exifTags;

};



TEST_F(ExifTagsTest_1324, IfdName_NormalOperation_1324) {

    const char* ifdName = exifTags.ifdName("IFD0");

    EXPECT_TRUE(ifdName != nullptr);

}



TEST_F(ExifTagsTest_1324, IfdName_BoundaryCondition_EmptyString_1324) {

    const char* ifdName = exifTags.ifdName("");

    EXPECT_EQ(std::string(""), ifdName);

}



TEST_F(ExifTagsTest_1324, IfdName_ExceptionalCase_InvalidGroup_1324) {

    const char* ifdName = exifTags.ifdName("INVALID_GROUP");

    EXPECT_TRUE(ifdName == nullptr || std::string("") == ifdName);

}
