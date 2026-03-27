#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include <memory>



using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, good, (), (const override));

    MOCK_METHOD(size_t, read, (byte* data, size_t n), (override));

    MOCK_METHOD(size_t, write, (const byte* data, size_t n), (override));

    MOCK_METHOD(void, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(int64_t, tell, (), (const override));

    MOCK_METHOD(uint32_t, size, (), (const override));

    MOCK_METHOD(void, truncate, (uint32_t size), (override));

};



class ImageTest_1090 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<Image> image;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        image = std::make_unique<Image>(ImageType::jpeg, 0x7fff, std::move(mockIo));

    }

};



TEST_F(ImageTest_1090, PixelWidthReturnsDefaultValue_1090) {

    EXPECT_EQ(image->pixelWidth(), 0u);

}



TEST_F(ImageTest_1090, PixelHeightReturnsDefaultValue_1090) {

    EXPECT_EQ(image->pixelHeight(), 0u);

}



TEST_F(ImageTest_1090, CommentReturnsEmptyStringByDefault_1090) {

    EXPECT_EQ(image->comment(), "");

}



TEST_F(ImageTest_1090, IccProfileNotDefinedByDefault_1090) {

    EXPECT_FALSE(image->iccProfileDefined());

}



TEST_F(ImageTest_1090, WriteXmpFromPacketReturnsDefaultValue_1090) {

    EXPECT_FALSE(image->writeXmpFromPacket());

}



TEST_F(ImageTest_1090, CheckModeAlwaysSupportedForExifMetadata_1090) {

    EXPECT_EQ(image->checkMode(MetadataId::exif), AccessMode::rw);

}



TEST_F(ImageTest_1090, GoodReturnsTrueIfMockIoIsGood_1090) {

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(image->good());

}



TEST_F(ImageTest_1090, GoodReturnsFalseIfMockIoIsNotGood_1090) {

    EXPECT_CALL(*mockIo, good()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(image->good());

}



// Boundary conditions and exceptional/error cases

TEST_F(ImageTest_1090, ReadMetadataDoesNotThrowException_1090) {

    EXPECT_NO_THROW(image->readMetadata());

}



TEST_F(ImageTest_1090, WriteMetadataDoesNotThrowException_1090) {

    EXPECT_NO_THROW(image->writeMetadata());

}



TEST_F(ImageTest_1090, SetAndGetExifDataDoesNotThrowException_1090) {

    ExifData exifData;

    EXPECT_NO_THROW(image->setExifData(exifData));

    EXPECT_NO_THROW(image->exifData());

}



TEST_F(ImageTest_1090, SetAndGetIptcDataDoesNotThrowException_1090) {

    IptcData iptcData;

    EXPECT_NO_THROW(image->setIptcData(iptcData));

    EXPECT_NO_THROW(image->iptcData());

}



TEST_F(ImageTest_1090, SetAndGetXmpPacketDoesNotThrowException_1090) {

    std::string xmpPacket = "";

    EXPECT_NO_THROW(image->setXmpPacket(xmpPacket));

    EXPECT_NO_THROW(image->xmpPacket());

}



TEST_F(ImageTest_1090, SetAndGetXmpDataDoesNotThrowException_1090) {

    XmpData xmpData;

    EXPECT_NO_THROW(image->setXmpData(xmpData));

    EXPECT_NO_THROW(image->xmpData());

}



TEST_F(ImageTest_1090, SetAndGetCommentDoesNotThrowException_1090) {

    std::string comment = "Sample Comment";

    EXPECT_NO_THROW(image->setComment(comment));

    EXPECT_EQ(image->comment(), comment);

}
