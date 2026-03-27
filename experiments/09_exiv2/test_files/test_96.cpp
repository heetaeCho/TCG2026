#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/matroskavideo.hpp"

#include "exiv2/basicio.hpp"

#include "exiv2/error.hpp"



using namespace Exiv2;

using ::testing::Return;

using ::testing::Throw;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class MatroskaVideoTest : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        matroskaVideo = new MatroskaVideo(std::move(mockIo));

    }



    void TearDown() override {

        delete matroskaVideo;

    }



    std::unique_ptr<MockBasicIo> mockIo;

    MatroskaVideo* matroskaVideo;

};



TEST_F(MatroskaVideoTest_96, OpenFailureThrowsException_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(1));

    EXPECT_THROW(matroskaVideo->readMetadata(), Error);

}



TEST_F(MatroskaVideoTest_96, NotMkvTypeThrowsException_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    EXPECT_THROW(matroskaVideo->readMetadata(), Error);

}



TEST_F(MatroskaVideoTest_96, ReadImageDataErrorThrowsException_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(true));

    EXPECT_THROW(matroskaVideo->readMetadata(), Error);

}



TEST_F(MatroskaVideoTest_96, ReadImageDataEofThrowsException_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(true));

    EXPECT_THROW(matroskaVideo->readMetadata(), Error);

}



TEST_F(MatroskaVideoTest_96, NormalOperationSetsXmpData_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false)).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024 * 1024)); // 1 MB

    matroskaVideo->readMetadata();

    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FileSize"].toString(), "1");

    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.MimeType"].toString(), matroskaVideo->mimeType());

}



TEST_F(MatroskaVideoTest_96, AspectRatioCalculation_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false)).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1024 * 1024)); // 1 MB

    matroskaVideo->width_ = 1920;

    matroskaVideo->height_ = 1080;

    matroskaVideo->readMetadata();

    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.AspectRatio"].toString(), "1.7777777777777777");

}



TEST_F(MatroskaVideoTest_96, EmptyFileSizeHandling_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false)).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(0)); // 0 bytes

    matroskaVideo->readMetadata();

    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FileSize"].toString(), "0");

}



TEST_F(MatroskaVideoTest_96, LargeFileSizeHandling_96) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path).WillRepeatedly(Return("test.mkv"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(false)).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(2 * 1024 * 1024 * 1024)); // 2 GB

    matroskaVideo->readMetadata();

    EXPECT_EQ(matroskaVideo->xmpData_["Xmp.video.FileSize"].toString(), "2");

}
