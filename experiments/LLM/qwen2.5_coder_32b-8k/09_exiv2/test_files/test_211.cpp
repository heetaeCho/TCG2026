#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/gifimage.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::_;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(std::string, path, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

};



class GifImageTest_211 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io_;

    std::unique_ptr<GifImage> gif_image_;



    void SetUp() override {

        mock_io_ = std::make_unique<MockBasicIo>();

        gif_image_ = std::make_unique<GifImage>(std::move(mock_io_));

    }

};



TEST_F(GifImageTest_211, ReadMetadata_SuccessfulRead_211) {

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*mock_io_, read(_, 4)).WillOnce([](byte* buf, size_t rcount) {

        std::memcpy(buf, "\x01\x00\x02\x00", 4); // width=1, height=2

        return rcount;

    });

    EXPECT_CALL(*mock_io_, eof()).WillOnce(Return(false));

    EXPECT_CALL(*mock_io_, error()).WillRepeatedly(Return(0));



    gif_image_->readMetadata();



    EXPECT_EQ(gif_image_->pixelWidth(), 1);

    EXPECT_EQ(gif_image_->pixelHeight(), 2);

}



TEST_F(GifImageTest_211, ReadMetadata_FileOpenFailed_211) {

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mock_io_, path()).WillOnce(Return("test.gif"));



    EXPECT_THROW(gif_image_->readMetadata(), Error);

}



TEST_F(GifImageTest_211, ReadMetadata_NotAGifFile_211) {

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*mock_io_, read(_, 4)).WillOnce([](byte* buf, size_t rcount) {

        std::memcpy(buf, "NotGIF", rcount);

        return rcount;

    });



    EXPECT_THROW(gif_image_->readMetadata(), Error);

}



TEST_F(GifImageTest_211, ReadMetadata_ReadFailure_211) {

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*mock_io_, read(_, 4)).WillOnce(Return(3));



    EXPECT_THROW(gif_image_->readMetadata(), Error);

}



TEST_F(GifImageTest_211, ReadMetadata_EndOfFileReached_211) {

    EXPECT_CALL(*mock_io_, open()).WillOnce(Return(0));

    EXPECT_CALL(*mock_io_, isopen()).WillOnce(Return(true));

    EXPECT_CALL(*mock_io_, read(_, 4)).WillOnce(Return(0));



    EXPECT_THROW(gif_image_->readMetadata(), Error);

}
