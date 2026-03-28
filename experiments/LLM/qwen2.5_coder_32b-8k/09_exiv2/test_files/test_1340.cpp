#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    struct TagInfoMock : public TagInfo {

        MockMethod0(std::string, title_, (), const);

    };

}



using namespace testing;

using namespace Exiv2;



class ExifKeyTest_1340 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> exifKey;

    NiceMock<TagInfoMock> tagInfoMock;

};



TEST_F(ExifKeyTest_1340, TagLabel_ReturnsEmptyString_WhenTagInfoIsNull_1340) {

    exifKey = std::make_unique<ExifKey>(tagInfoMock);

    tagInfoMock.tagInfo_ = nullptr;



    EXPECT_EQ(exifKey->tagLabel(), "");

}



TEST_F(ExifKeyTest_1340, TagLabel_ReturnsEmptyString_WhenTagIsFFFF_1340) {

    exifKey = std::make_unique<ExifKey>(tagInfoMock);

    tagInfoMock.tagInfo_->tag_ = 0xffff;



    EXPECT_EQ(exifKey->tagLabel(), "");

}



TEST_F(ExifKeyTest_1340, TagLabel_ReturnsTitle_WhenTagIsValid_1340) {

    exifKey = std::make_unique<ExifKey>(tagInfoMock);

    tagInfoMock.tagInfo_->tag_ = 0xfffe;

    EXPECT_CALL(tagInfoMock, title_()).WillOnce(Return("ValidTag"));



    EXPECT_EQ(exifKey->tagLabel(), "ValidTag");

}



TEST_F(ExifKeyTest_1340, TagLabel_ReturnsLocalizedTitle_WhenTranslationFunctionIsApplied_1340) {

    exifKey = std::make_unique<ExifKey>(tagInfoMock);

    tagInfoMock.tagInfo_->tag_ = 0xfffe;

    EXPECT_CALL(tagInfoMock, title_()).WillOnce(Return("ValidTag"));



    EXPECT_EQ(exifKey->tagLabel(), _("ValidTag"));

}
