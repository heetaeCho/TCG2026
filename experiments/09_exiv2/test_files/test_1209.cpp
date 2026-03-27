#include <gtest/gtest.h>

#include "exiv2/preview.hpp"

#include <string>



namespace Exiv2 {

    class PreviewImage;

}



class PreviewImageTest_1209 : public ::testing::Test {

protected:

    Exiv2::PreviewImage previewImage;



    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(PreviewImageTest_1209, Size_ReturnsZeroForDefaultConstructor_1209) {

    EXPECT_EQ(previewImage.size(), 0U);

}



TEST_F(PreviewImageTest_1209, Size_ReturnsCorrectSizeAfterCopyAssignment_1209) {

    Exiv2::DataBuf data(reinterpret_cast<const byte*>("test"), 4);

    Exiv2::PreviewImage anotherPreview(data);

    previewImage = anotherPreview;

    EXPECT_EQ(previewImage.size(), 4U);

}



TEST_F(PreviewImageTest_1209, Size_ReturnsCorrectSizeAfterCopy_1209) {

    Exiv2::DataBuf data(reinterpret_cast<const byte*>("test"), 4);

    Exiv2::PreviewImage anotherPreview(data);

    auto copiedPreview = anotherPreview.copy();

    EXPECT_EQ(copiedPreview.size(), 4U);

}



TEST_F(PreviewImageTest_1209, pData_ReturnsNullptrForDefaultConstructor_1209) {

    EXPECT_EQ(previewImage.pData(), nullptr);

}



TEST_F(PreviewImageTest_1209, pData_ReturnsValidPointerAfterCopyAssignment_1209) {

    Exiv2::DataBuf data(reinterpret_cast<const byte*>("test"), 4);

    Exiv2::PreviewImage anotherPreview(data);

    previewImage = anotherPreview;

    EXPECT_NE(previewImage.pData(), nullptr);

}



TEST_F(PreviewImageTest_1209, writeFile_ReturnsZeroForDefaultConstructor_1209) {

    std::string path = "testfile.bin";

    EXPECT_EQ(previewImage.writeFile(path), 0U);

}



TEST_F(PreviewImageTest_1209, mimeType_ReturnsEmptyStringForDefaultConstructor_1209) {

    EXPECT_TRUE(previewImage.mimeType().empty());

}



TEST_F(PreviewImageTest_1209, extension_ReturnsEmptyStringForDefaultConstructor_1209) {

    EXPECT_TRUE(previewImage.extension().empty());

}



TEST_F(PreviewImageTest_1209, width_ReturnsZeroForDefaultConstructor_1209) {

    EXPECT_EQ(previewImage.width(), 0U);

}



TEST_F(PreviewImageTest_1209, height_ReturnsZeroForDefaultConstructor_1209) {

    EXPECT_EQ(previewImage.height(), 0U);

}
