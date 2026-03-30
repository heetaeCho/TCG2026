#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"



using namespace Exiv2;

using ::testing::Return;



class MockImage : public Image {

public:

    MOCK_CONST_METHOD1(checkMode, AccessMode(MetadataId));

    MOCK_METHOD1(setExifData, void(const ExifData&));

    MOCK_METHOD1(setIptcData, void(const IptcData&));

    MOCK_METHOD1(setXmpPacket, void(const std::string&));

    MOCK_METHOD1(setXmpData, void(const XmpData&));

    MOCK_METHOD1(setComment, void(const std::string&));

    MOCK_METHOD1(setIccProfile, void(DataBuf&&));



    MockImage(ImageType type, uint16_t supportedMetadata) 

        : Image(type, supportedMetadata, nullptr) {}

};



class ImageTest_1072 : public ::testing::Test {

protected:

    MockImage image{ImageType::jpeg, 0};

    MockImage sourceImage{ImageType::jpeg, mdExif | mdIptc | mdXmp | mdIccProfile | mdComment};

};



TEST_F(ImageTest_1072, SetMetadata_NoWritePermissions_1072) {

    EXPECT_CALL(image, checkMode(mdExif)).WillOnce(Return(amNone));

    EXPECT_CALL(image, checkMode(mdIptc)).WillOnce(Return(amNone));

    EXPECT_CALL(image, checkMode(mdXmp)).WillOnce(Return(amNone));

    EXPECT_CALL(image, checkMode(mdIccProfile)).WillOnce(Return(amNone));

    EXPECT_CALL(image, checkMode(mdComment)).WillOnce(Return(amNone));



    image.setMetadata(sourceImage);



    // No set* calls should be made

}



TEST_F(ImageTest_1072, SetMetadata_ExifWritePermission_1072) {

    EXPECT_CALL(image, checkMode(mdExif)).WillOnce(Return(amWrite));

    EXPECT_CALL(image, setExifData(::testing::_));



    image.setMetadata(sourceImage);

}



TEST_F(ImageTest_1072, SetMetadata_IptcWritePermission_1072) {

    EXPECT_CALL(image, checkMode(mdIptc)).WillOnce(Return(amWrite));

    EXPECT_CALL(image, setIptcData(::testing::_));



    image.setMetadata(sourceImage);

}



TEST_F(ImageTest_1072, SetMetadata_XmpWritePermission_1072) {

    EXPECT_CALL(image, checkMode(mdXmp)).WillOnce(Return(amWrite));

    EXPECT_CALL(image, setXmpPacket(::testing::_));

    EXPECT_CALL(image, setXmpData(::testing::_));



    image.setMetadata(sourceImage);

}



TEST_F(ImageTest_1072, SetMetadata_IccProfileWritePermission_1072) {

    EXPECT_CALL(image, checkMode(mdIccProfile)).WillOnce(Return(amWrite));

    EXPECT_CALL(image, setIccProfile(::testing::_));



    image.setMetadata(sourceImage);

}



TEST_F(ImageTest_1072, SetMetadata_CommentWritePermission_1072) {

    EXPECT_CALL(image, checkMode(mdComment)).WillOnce(Return(amWrite));

    EXPECT_CALL(image, setComment(::testing::_));



    image.setMetadata(sourceImage);

}
