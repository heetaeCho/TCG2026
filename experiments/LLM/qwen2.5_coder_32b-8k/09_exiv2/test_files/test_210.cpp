#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/gifimage.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(void, read, (byte* data, size_t nbytes), (override));

    MOCK_METHOD(void, write, (const byte* data, size_t nbytes), (override));

    MOCK_METHOD(void, seek, (long offset, Position pos), (override));

    MOCK_METHOD(long, tell, (), (override));

    MOCK_METHOD(void, close, (), (override));

};



class GifImageTest_210 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    std::unique_ptr<GifImage> gif_image;



    void SetUp() override {

        mock_io = std::make_unique<MockBasicIo>();

        gif_image = std::make_unique<GifImage>(std::move(mock_io));

    }

};



TEST_F(GifImageTest_210, MimeTypeReturnsCorrectValue_210) {

    EXPECT_EQ(gif_image->mimeType(), "image/gif");

}



TEST_F(GifImageTest_210, SetExifDataDoesNotThrowOnValidInput_210) {

    ExifData exif_data;

    EXPECT_NO_THROW(gif_image->setExifData(exif_data));

}



TEST_F(GifImageTest_210, SetIptcDataDoesNotThrowOnValidInput_210) {

    IptcData iptc_data;

    EXPECT_NO_THROW(gif_image->setIptcData(iptc_data));

}



TEST_F(GifImageTest_210, SetCommentDoesNotThrowOnValidInput_210) {

    EXPECT_NO_THROW(gif_image->setComment("Sample comment"));

}



TEST_F(GifImageTest_210, ReadMetadataDoesNotThrow_210) {

    EXPECT_CALL(*mock_io, seek(_, _)).Times(1);

    EXPECT_CALL(*mock_io, read(_, _)).Times(1);

    EXPECT_NO_THROW(gif_image->readMetadata());

}



TEST_F(GifImageTest_210, WriteMetadataDoesNotThrow_210) {

    EXPECT_CALL(*mock_io, seek(_, _)).Times(1);

    EXPECT_CALL(*mock_io, write(_, _)).Times(1);

    EXPECT_NO_THROW(gif_image->writeMetadata());

}
