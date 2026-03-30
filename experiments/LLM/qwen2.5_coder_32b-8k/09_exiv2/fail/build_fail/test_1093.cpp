#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/image.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(std::string, read, (size_t), (override));

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    MOCK_METHOD(void, seek, (int64_t, PositionFrom), (override));

    MOCK_METHOD(int64_t, tell, (), (const, override));

    MOCK_METHOD(bool, good, (), (const, override));

};



class ImageTest : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<Image> image;



    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        image = std::make_unique<Image>(jpeg, 0x1f, std::move(mockIo));

    }

};



TEST_F(ImageTest_1093, IoReturnsReferenceToInternalBuffer_1093) {

    BasicIo& ioRef = image->io();

    EXPECT_EQ(&ioRef, mockIo.get());

}



TEST_F(ImageTest_1093, ReadMetadataDoesNotThrowOnValidInput_1093) {

    EXPECT_NO_THROW(image->readMetadata());

}



TEST_F(ImageTest_1093, WriteMetadataDoesNotThrowOnValidInput_1093) {

    EXPECT_NO_THROW(image->writeMetadata());

}



TEST_F(ImageTest_1093, SetExifDataSetsDataCorrectly_1093) {

    ExifData exifData;

    image->setExifData(exifData);

    // Assuming we can verify by retrieving the data back (if possible)

    EXPECT_EQ(image->exifData(), exifData);

}



TEST_F(ImageTest_1093, ClearExifDataResetsData_1093) {

    ExifData exifData;

    image->setExifData(exifData);

    image->clearExifData();

    EXPECT_TRUE(image->exifData().empty());

}



TEST_F(ImageTest_1093, SetIptcDataSetsDataCorrectly_1093) {

    IptcData iptcData;

    image->setIptcData(iptcData);

    // Assuming we can verify by retrieving the data back (if possible)

    EXPECT_EQ(image->iptcData(), iptcData);

}



TEST_F(ImageTest_1093, ClearIptcDataResetsData_1093) {

    IptcData iptcData;

    image->setIptcData(iptcData);

    image->clearIptcData();

    EXPECT_TRUE(image->iptcData().empty());

}



TEST_F(ImageTest_1093, SetXmpPacketSetsDataCorrectly_1093) {

    std::string xmpPacket = "testXMP";

    image->setXmpPacket(xmpPacket);

    // Assuming we can verify by retrieving the data back (if possible)

    EXPECT_EQ(image->xmpPacket(), xmpPacket);

}



TEST_F(ImageTest_1093, ClearXmpPacketResetsData_1093) {

    std::string xmpPacket = "testXMP";

    image->setXmpPacket(xmpPacket);

    image->clearXmpPacket();

    EXPECT_TRUE(image->xmpPacket().empty());

}



TEST_F(ImageTest_1093, SetCommentSetsDataCorrectly_1093) {

    std::string comment = "testComment";

    image->setComment(comment);

    // Assuming we can verify by retrieving the data back (if possible)

    EXPECT_EQ(image->comment(), comment);

}



TEST_F(ImageTest_1093, ClearCommentResetsData_1093) {

    std::string comment = "testComment";

    image->setComment(comment);

    image->clearComment();

    EXPECT_TRUE(image->comment().empty());

}



TEST_F(ImageTest_1093, SetIccProfileSetsDataCorrectly_1093) {

    DataBuf iccProfile(reinterpret_cast<byte*>("testICC"), 7);

    image->setIccProfile(std::move(iccProfile), true);

    // Assuming we can verify by retrieving the data back (if possible)

    EXPECT_TRUE(image->iccProfileDefined());

}



TEST_F(ImageTest_1093, ClearIccProfileResetsData_1093) {

    DataBuf iccProfile(reinterpret_cast<byte*>("testICC"), 7);

    image->setIccProfile(std::move(iccProfile), true);

    image->clearIccProfile();

    EXPECT_FALSE(image->iccProfileDefined());

}



TEST_F(ImageTest_1093, SetMetadataSetsDataCorrectly_1093) {

    auto otherImage = std::make_unique<Image>(jpeg, 0x1f, std::move(mockIo));

    image->setMetadata(*otherImage);

    // Assuming we can verify by retrieving the data back (if possible)

    EXPECT_EQ(image->exifData(), otherImage->exifData());

}



TEST_F(ImageTest_1093, ClearMetadataResetsAllData_1093) {

    ExifData exifData;

    IptcData iptcData;

    XmpData xmpData;

    std::string comment = "testComment";

    DataBuf iccProfile(reinterpret_cast<byte*>("testICC"), 7);



    image->setExifData(exifData);

    image->setIptcData(iptcData);

    image->setXmpData(xmpData);

    image->setComment(comment);

    image->setIccProfile(std::move(iccProfile), true);



    image->clearMetadata();



    EXPECT_TRUE(image->exifData().empty());

    EXPECT_TRUE(image->iptcData().empty());

    EXPECT_TRUE(image->xmpPacket().empty());

    EXPECT_TRUE(image->comment().empty());

    EXPECT_FALSE(image->iccProfileDefined());

}



TEST_F(ImageTest_1093, PixelWidthReturnsDefaultValue_1093) {

    EXPECT_EQ(image->pixelWidth(), 0);

}



TEST_F(ImageTest_1093, PixelHeightReturnsDefaultValue_1093) {

    EXPECT_EQ(image->pixelHeight(), 0);

}



TEST_F(ImageTest_1093, GoodReturnsTrueWhenIoIsGood_1093) {

    EXPECT_CALL(*mockIo, good()).WillOnce(Return(true));

    EXPECT_TRUE(image->good());

}



TEST_F(ImageTest_1093, GoodReturnsFalseWhenIoIsNotGood_1093) {

    EXPECT_CALL(*mockIo, good()).WillOnce(Return(false));

    EXPECT_FALSE(image->good());

}



TEST_F(ImageTest_1093, SupportsMetadataReturnsTrueForSupportedTypes_1093) {

    image = std::make_unique<Image>(jpeg, 0x1f, std::move(mockIo)); // 0x1f supports Exif

    EXPECT_TRUE(image->supportsMetadata(metadataExif));

}



TEST_F(ImageTest_1093, SupportsMetadataReturnsFalseForUnsupportedTypes_1093) {

    image = std::make_unique<Image>(jpeg, 0x00, std::move(mockIo)); // 0x00 supports nothing

    EXPECT_FALSE(image->supportsMetadata(metadataExif));

}



TEST_F(ImageTest_1093, ByteOrderReturnsDefaultValue_1093) {

    EXPECT_EQ(image->byteOrder(), invalidByteOrder);

}
