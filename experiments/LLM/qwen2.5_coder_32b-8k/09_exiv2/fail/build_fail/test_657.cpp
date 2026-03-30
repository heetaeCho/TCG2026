#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/quicktimevideo.hpp"

#include "exiv2/basicio.hpp"



namespace Exiv2 {



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte * data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo & src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte * buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte * buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo & src), (override));

    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t offset, Position pos, ErrorCode err), (override));

    MOCK_METHOD(byte *, mmap, (bool isWriteable), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(size_t, tell, (), (const, override));

    MOCK_METHOD(size_t, size, (), (const, override));

    MOCK_METHOD(bool, isopen, (), (const, override));

    MOCK_METHOD(int, error, (), (const, override));

    MOCK_METHOD(bool, eof, (), (const, override));

    MOCK_METHOD(const std::string &, path, (), (const, override));

};



class QuickTimeVideoTest_657 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        quickTimeVideo = std::make_unique<QuickTimeVideo>(std::move(mockIo), 10);

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<QuickTimeVideo> quickTimeVideo;

};



TEST_F(QuickTimeVideoTest_657, ReadMetadata_SuccessfulRead_657) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, size()).WillRepeatedly(testing::Return(1024));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(testing::Return("test.mp4"));

    EXPECT_CALL(*mockIo, error()).WillRepeatedly(testing::Return(0));

    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(testing::Return(false));



    quickTimeVideo->readMetadata();



    EXPECT_EQ(quickTimeVideo->xmpData_["Xmp.video.FileSize"].toFloat(), 1.0);

}



TEST_F(QuickTimeVideoTest_657, ReadMetadata_OpenFailed_657) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(-1));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(testing::Return("test.mp4"));



    EXPECT_THROW(quickTimeVideo->readMetadata(), Error);

}



TEST_F(QuickTimeVideoTest_657, ReadMetadata_NotQTimeType_657) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(testing::Return("test.mp4"));

    EXPECT_CALL(*mockIo, error()).WillRepeatedly(testing::Return(false));

    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(testing::Return(false));



    EXPECT_THROW(quickTimeVideo->readMetadata(), Error);

}



TEST_F(QuickTimeVideoTest_657, ReadMetadata_ErrorReadingImageData_657) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(testing::Return("test.mp4"));

    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(true));

    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(false));



    EXPECT_THROW(quickTimeVideo->readMetadata(), Error);

}



TEST_F(QuickTimeVideoTest_657, ReadMetadata_EofReadingImageData_657) {

    EXPECT_CALL(*mockIo, open()).WillOnce(testing::Return(0));

    EXPECT_CALL(*mockIo, path()).WillRepeatedly(testing::Return("test.mp4"));

    EXPECT_CALL(*mockIo, error()).WillOnce(testing::Return(false));

    EXPECT_CALL(*mockIo, eof()).WillOnce(testing::Return(true));



    EXPECT_THROW(quickTimeVideo->readMetadata(), Error);

}



}  // namespace Exiv2
