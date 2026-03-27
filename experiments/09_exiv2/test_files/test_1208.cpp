#include <gtest/gtest.h>

#include "exiv2/preview.hpp"



using namespace Exiv2;



class PreviewImageTest : public ::testing::Test {

protected:

    byte testData[10] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};

    DataBuf dataBuffer(testData, sizeof(testData));

    PreviewImage preview(dataBuffer);

};



TEST_F(PreviewImageTest_1208, pData_ReturnsValidPointer_1208) {

    EXPECT_NE(preview.pData(), nullptr);

}



TEST_F(PreviewImageTest_1208, size_ReturnsCorrectSize_1208) {

    EXPECT_EQ(preview.size(), sizeof(testData));

}



TEST_F(PreviewImageTest_1208, copy_ReturnsDataBufWithSameSize_1208) {

    DataBuf copiedData = preview.copy();

    EXPECT_EQ(copiedData.size(), preview.size());

}



TEST_F(PreviewImageTest_1208, copy_ReturnsDataBufWithDataEqual_1208) {

    DataBuf copiedData = preview.copy();

    EXPECT_TRUE(std::equal(testData, testData + sizeof(testData), copiedData.c_data()));

}



TEST_F(PreviewImageTest_1208, mimeType_DefaultConstructor_ReturnsEmptyString_1208) {

    PreviewImage defaultPreview;

    EXPECT_EQ(defaultPreview.mimeType(), "");

}



TEST_F(PreviewImageTest_1208, extension_DefaultConstructor_ReturnsEmptyString_1208) {

    PreviewImage defaultPreview;

    EXPECT_EQ(defaultPreview.extension(), "");

}



TEST_F(PreviewImageTest_1208, width_DefaultConstructor_ReturnsZero_1208) {

    PreviewImage defaultPreview;

    EXPECT_EQ(defaultPreview.width(), 0);

}



TEST_F(PreviewImageTest_1208, height_DefaultConstructor_ReturnsZero_1208) {

    PreviewImage defaultPreview;

    EXPECT_EQ(defaultPreview.height(), 0);

}



TEST_F(PreviewImageTest_1208, id_DefaultConstructor_ReturnsDefaultId_1208) {

    PreviewImage defaultPreview;

    EXPECT_EQ(defaultPreview.id(), static_cast<PreviewId>(0));

}
