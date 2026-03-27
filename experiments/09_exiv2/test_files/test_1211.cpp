#include <gtest/gtest.h>

#include "exiv2/preview.hpp"



using namespace Exiv2;



class PreviewImageTest : public ::testing::Test {

protected:

    PreviewProperties properties;

    DataBuf data;

    PreviewImage image;



    void SetUp() override {

        properties.extension_ = ".jpg";

        image = PreviewImage(properties, std::move(data));

    }

};



TEST_F(PreviewImageTest_1211, Extension_ReturnsCorrectValue_1211) {

    EXPECT_EQ(image.extension(), ".jpg");

}



TEST_F(PreviewImageTest_1211, Copy_ReturnsValidDataBuf_1211) {

    DataBuf copy = image.copy();

    EXPECT_TRUE(copy.pData() != nullptr);

}



TEST_F(PreviewImageTest_1211, PData_ReturnsNonNulPointer_1211) {

    EXPECT_TRUE(image.pData() != nullptr);

}



TEST_F(PreviewImageTest_1211, Size_ReturnsZeroForEmptyData_1211) {

    EXPECT_EQ(image.size(), 0u);

}



TEST_F(PreviewImageTest_1211, WriteFile_ReturnsFileSize_1211) {

    std::string testFilePath = "testfile.jpg";

    size_t fileSize = image.writeFile(testFilePath);

    EXPECT_TRUE(fileSize >= 0);

    remove(testFilePath.c_str()); // Clean up the file

}



TEST_F(PreviewImageTest_1211, MimeType_ReturnsEmptyString_1211) {

    EXPECT_EQ(image.mimeType(), "");

}



TEST_F(PreviewImageTest_1211, Width_ReturnsZeroForNoImageData_1211) {

    EXPECT_EQ(image.width(), 0u);

}



TEST_F(PreviewImageTest_1211, Height_ReturnsZeroForNoImageData_1211) {

    EXPECT_EQ(image.height(), 0u);

}



TEST_F(PreviewImageTest_1211, Id_ReturnsDefaultConstructedId_1211) {

    PreviewId id = image.id();

    EXPECT_EQ(id, PreviewId{});

}
