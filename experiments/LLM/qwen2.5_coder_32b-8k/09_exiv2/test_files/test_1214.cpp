#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/preview.hpp"



using namespace Exiv2;



class PreviewImageTest : public ::testing::Test {

protected:

    PreviewProperties properties;

    DataBuf previewData;

    PreviewImage* previewImage;



    void SetUp() override {

        properties.id_ = 123;

        properties.extension_ = "jpg";

        previewData.adopt(const_cast<byte*>((const byte*)"sampledata"), 10);

        previewImage = new PreviewImage(properties, std::move(previewData));

    }



    void TearDown() override {

        delete previewImage;

    }

};



TEST_F(PreviewImageTest_1214, IdReturnsCorrectValue_1214) {

    EXPECT_EQ(previewImage->id(), 123);

}



TEST_F(PreviewImageTest_1214, ExtensionReturnsCorrectValue_1214) {

    EXPECT_EQ(previewImage->extension(), "jpg");

}



TEST_F(PreviewImageTest_1214, CopyCreatesNewDataBuf_1214) {

    DataBuf copiedData = previewImage->copy();

    EXPECT_NE(copiedData.pData(), previewImage->pData());

    EXPECT_EQ(copiedData.size(), previewImage->size());

}



TEST_F(PreviewImageTest_1214, PDataReturnsValidPointer_1214) {

    const byte* dataPtr = previewImage->pData();

    EXPECT_NE(dataPtr, nullptr);

}



TEST_F(PreviewImageTest_1214, SizeReturnsCorrectSize_1214) {

    EXPECT_EQ(previewImage->size(), 10u);

}



// Assuming writeFile writes the file correctly and returns the number of bytes written

// Since we cannot verify file content or existence in a unit test without mocking filesystem,

// we assume it returns the size of the data if successful.

TEST_F(PreviewImageTest_1214, WriteFileReturnsCorrectSize_1214) {

    std::string tempPath = "tempfile.jpg";

    EXPECT_EQ(previewImage->writeFile(tempPath), 10u);

}



// Assuming mimeType returns a valid MIME type string

TEST_F(PreviewImageTest_1214, MimeTypeReturnsValidString_1214) {

    EXPECT_FALSE(previewImage->mimeType().empty());

}



// Assuming width and height return non-zero values for a valid preview image

TEST_F(PreviewImageTest_1214, WidthAndHeightReturnNonZeroValues_1214) {

    EXPECT_GT(previewImage->width(), 0u);

    EXPECT_GT(previewImage->height(), 0u);

}



// Assuming operator= copies properties and data correctly

TEST_F(PreviewImageTest_1214, OperatorEqualsCopiesPropertiesAndData_1214) {

    PreviewImage anotherPreview(properties, DataBuf());

    anotherPreview = *previewImage;

    EXPECT_EQ(anotherPreview.id(), previewImage->id());

    EXPECT_EQ(anotherPreview.extension(), previewImage->extension());

    EXPECT_NE(anotherPreview.pData(), previewImage->pData());

    EXPECT_EQ(anotherPreview.size(), previewImage->size());

}



// Assuming operator= is self-assignment safe

TEST_F(PreviewImageTest_1214, OperatorEqualsHandlesSelfAssignment_1214) {

    *previewImage = *previewImage;

    EXPECT_EQ(previewImage->id(), 123);

}
