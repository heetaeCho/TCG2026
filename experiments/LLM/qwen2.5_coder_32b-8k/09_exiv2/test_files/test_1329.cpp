#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/tags.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::HasSubstr;



class ExifTagsTest_1329 : public ::testing::Test {

protected:

    std::ostringstream os;

};



TEST_F(ExifTagsTest_1329, TaglistOutputsData_1329) {

    ExifTags exifTags;

    exifTags.taglist(os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(ExifTagsTest_1329, TaglistContainsExpectedFormat_1329) {

    ExifTags exifTags;

    exifTags.taglist(os);

    EXPECT_THAT(os.str(), HasSubstr("TagInfo"));

}



TEST_F(ExifTagsTest_1329, TaglistBoundaryConditionEmptyOutput_1329) {

    // Assuming no tags would be an edge case, which is unlikely but testing for completeness

    ExifTags exifTags;

    exifTags.taglist(os);

    EXPECT_NE(os.str().find("0xffff"), std::string::npos); // End marker should exist

}



// No exceptional/error cases are directly observable from the provided interface



```


