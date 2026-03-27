#include <gtest/gtest.h>

#include "exiv2/preview.hpp"

#include <string>



namespace {



using namespace Exiv2;



class PreviewImageTest_1205 : public ::testing::Test {

protected:

    PreviewProperties properties;

    DataBuf data;

    PreviewImage previewImage;



    void SetUp() override {

        properties.extension_ = "jpg";

        properties.id_ = 1;

        data.alloc(10); // Allocate some dummy data

        previewImage = PreviewImage(properties, std::move(data));

    }

};



TEST_F(PreviewImageTest_1205, CopyConstructorCreatesIdenticalObject_1205) {

    PreviewImage copiedPreview(previewImage);

    EXPECT_EQ(copiedPreview.pData(), previewImage.pData());

    EXPECT_EQ(copiedPreview.size(), previewImage.size());

}



TEST_F(PreviewImageTest_1205, AssignmentOperatorCopiesPropertiesAndData_1205) {

    PreviewImage anotherPreview;

    anotherPreview = previewImage;

    EXPECT_EQ(anotherPreview.pData(), previewImage.pData());

    EXPECT_EQ(anotherPreview.size(), previewImage.size());

}



TEST_F(PreviewImageTest_1205, CopyMethodReturnsIdenticalDataBuf_1205) {

    DataBuf copiedData = previewImage.copy();

    EXPECT_NE(copiedData.c_data(), previewImage.pData()); // Different memory address

    EXPECT_EQ(copiedData.size(), previewImage.size());

}



TEST_F(PreviewImageTest_1205, SizeReturnsCorrectSize_1205) {

    EXPECT_EQ(previewImage.size(), 10u);

}



TEST_F(PreviewImageTest_1205, PDataReturnsPointerToData_1205) {

    EXPECT_NE(previewImage.pData(), nullptr);

}



TEST_F(PreviewImageTest_1205, MimeTypeReturnsEmptyStringByDefault_1205) {

    EXPECT_EQ(previewImage.mimeType().empty(), true);

}



TEST_F(PreviewImageTest_1205, ExtensionMatchesConstructedValue_1205) {

    EXPECT_EQ(previewImage.extension(), "jpg");

}



TEST_F(PreviewImageTest_1205, WidthReturnsZeroByDefault_1205) {

    EXPECT_EQ(previewImage.width(), 0u);

}



TEST_F(PreviewImageTest_1205, HeightReturnsZeroByDefault_1205) {

    EXPECT_EQ(previewImage.height(), 0u);

}



TEST_F(PreviewImageTest_1205, IdMatchesConstructedValue_1205) {

    EXPECT_EQ(previewImage.id(), 1);

}



TEST_F(PreviewImageTest_1205, WriteFileThrowsOnInvalidPath_1205) {

    EXPECT_THROW(previewImage.writeFile("/nonexistent/path/image.jpg"), Error);

}



} // namespace
