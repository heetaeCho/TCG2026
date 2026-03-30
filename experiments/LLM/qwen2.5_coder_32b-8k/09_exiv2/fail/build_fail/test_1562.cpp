#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "asfvideo.hpp"

#include "basicio.hpp"



using namespace Exiv2;

using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



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

    MOCK_METHOD(const size_t, tell, (), (const override));

    MOCK_METHOD(const size_t, size, (), (const override));

    MOCK_METHOD(const bool, isopen, (), (const override));

    MOCK_METHOD(const int, error, (), (const override));

    MOCK_METHOD(const bool, eof, (), (const override));

    MOCK_METHOD(const std::string &, path, (), (const override));

};



class AsfVideoTest_1562 : public ::testing::Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<MockBasicIo>();

        asfVideo = std::make_unique<AsfVideo>(std::move(mockIo));

    }



    std::unique_ptr<MockBasicIo> mockIo;

    std::unique_ptr<AsfVideo> asfVideo;

};



TEST_F(AsfVideoTest_1562, ReadMetadata_SuccessfulRead_1562) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.asf"));

    EXPECT_CALL(*mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(Return(false));

    EXPECT_CALL(*mockIo, size()).WillOnce(Return(1048576));

    EXPECT_CALL(*mockIo, seek(0, BasicIo::beg)).WillOnce(Return(0));



    asfVideo->readMetadata();



    const XmpData& xmpData = asfVideo->xmpData();

    EXPECT_EQ(xmpData["Xmp.video.FileSize"].toString(), "1");

    EXPECT_EQ(xmpData["Xmp.video.MimeType"], asfVideo->mimeType());

}



TEST_F(AsfVideoTest_1562, ReadMetadata_OpenFailed_1562) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(-1));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.asf"));



    EXPECT_THROW(asfVideo->readMetadata(), Error);

}



TEST_F(AsfVideoTest_1562, ReadMetadata_NotAnImage_1562) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.asf"));

    EXPECT_CALL(*mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(Return(false));



    EXPECT_THROW(asfVideo->readMetadata(), Error);

}



TEST_F(AsfVideoTest_1562, ReadMetadata_ReadFailed_1562) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.asf"));

    EXPECT_CALL(*mockIo, error()).WillOnce(Return(1)).WillRepeatedly(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillRepeatedly(Return(false));



    EXPECT_THROW(asfVideo->readMetadata(), Error);

}



TEST_F(AsfVideoTest_1562, ReadMetadata_EndOfFile_1562) {

    EXPECT_CALL(*mockIo, open()).WillOnce(Return(0));

    EXPECT_CALL(*mockIo, path()).WillOnce(Return("test.asf"));

    EXPECT_CALL(*mockIo, error()).WillRepeatedly(Return(0));

    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(true));



    EXPECT_THROW(asfVideo->readMetadata(), Error);

}
