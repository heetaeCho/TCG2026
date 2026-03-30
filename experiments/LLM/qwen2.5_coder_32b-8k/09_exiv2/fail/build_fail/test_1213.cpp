#include <gtest/gtest.h>

#include "exiv2/preview.hpp"



using namespace Exiv2;



class PreviewImageTest_1213 : public ::testing::Test {

protected:

    PreviewProperties properties;

    DataBuf data;

    PreviewImage previewImage;



    void SetUp() override {

        properties.extension_ = ".jpg";

        data.adopt(const_cast<byte*>((const byte*)"\xFF\xD8"), 2);

        previewImage = PreviewImage(properties, std::move(data));

    }

};



TEST_F(PreviewImageTest_1213, HeightReturnsCorrectValue_1213) {

    size_t height = previewImage.height();

    // Assuming the height is not set in the properties, it should return 0 by default

    EXPECT_EQ(height, 0);

}



TEST_F(PreviewImageTest_1213, WidthReturnsCorrectValue_1213) {

    size_t width = previewImage.width();

    // Assuming the width is not set in the properties, it should return 0 by default

    EXPECT_EQ(width, 0);

}



TEST_F(PreviewImageTest_1213, ExtensionReturnsCorrectValue_1213) {

    const std::string& extension = previewImage.extension();

    EXPECT_EQ(extension, ".jpg");

}



TEST_F(PreviewImageTest_1213, SizeReturnsCorrectValue_1213) {

    uint32_t size = previewImage.size();

    EXPECT_EQ(size, 2u);

}



TEST_F(PreviewImageTest_1213, PDataReturnsValidPointer_1213) {

    const byte* dataPtr = previewImage.pData();

    ASSERT_NE(dataPtr, nullptr);

    EXPECT_EQ(*dataPtr, static_cast<byte>(0xFF));

    EXPECT_EQ(*(dataPtr + 1), static_cast<byte>(0xD8));

}



TEST_F(PreviewImageTest_1213, CopyReturnsValidDataBuf_1213) {

    DataBuf copiedData = previewImage.copy();

    EXPECT_EQ(copiedData.size(), 2u);

    EXPECT_EQ(*copiedData.pData(), static_cast<byte>(0xFF));

    EXPECT_EQ(*(copiedData.pData() + 1), static_cast<byte>(0xD8));

}



TEST_F(PreviewImageTest_1213, WriteFileReturnsZeroForEmptyPath_1213) {

    size_t result = previewImage.writeFile("");

    EXPECT_EQ(result, 0);

}



// Assuming mimeType is not set in the properties, it should return an empty string by default

TEST_F(PreviewImageTest_1213, MimeTypeReturnsEmptyStringByDefault_1213) {

    const std::string& mimeType = previewImage.mimeType();

    EXPECT_TRUE(mimeType.empty());

}



// Assuming id is not set in the properties, it should return an empty PreviewId by default

TEST_F(PreviewImageTest_1213, IdReturnsEmptyPreviewIdByDefault_1213) {

    PreviewId id = previewImage.id();

    EXPECT_EQ(id, PreviewId{});

}
