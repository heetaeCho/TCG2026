#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/quicktimevideo.hpp"

#include "exiv2/basicio.hpp"



using namespace testing;

using namespace Exiv2;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte *data, size_t wcount), (override));

    MOCK_METHOD(size_t, write, (BasicIo &src), (override));

    MOCK_METHOD(int, putb, (byte data), (override));

    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));

    MOCK_METHOD(size_t, read, (byte *buf, size_t rcount), (override));

    MOCK_METHOD(void, readOrThrow, (byte *buf, size_t rcount, ErrorCode err), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo &src), (override));

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

    MOCK_METHOD(void, populateFakeData, (), (override));

};



class QuickTimeVideoTest : public Test {

protected:

    void SetUp() override {

        mockIo = std::make_unique<StrictMock<MockBasicIo>>();

        video = new Exiv2::QuickTimeVideo(std::move(mockIo), 10);

    }



    void TearDown() override {

        delete video;

    }



    std::unique_ptr<MockBasicIo> mockIo;

    Exiv2::QuickTimeVideo* video;

};



TEST_F(QuickTimeVideoTest_658, DecodeBlock_NormalOperation_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x0C", 4); // Size = 12

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x08", 4); // Additional data

        return rcount;

    });



    video->decodeBlock(0, "other");

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_Size1_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x01", 4); // Size = 1 (special case)

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, read(_, 8)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x00\x00\x00\x00\x14", 8); // Extended size = 20

        return rcount;

    });



    video->decodeBlock(0, "other");

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_Size0FromMeta_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x00", 4); // Size = 0

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x14", 4); // Additional data

        return rcount;

    });



    video->decodeBlock(0, "meta");

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_EOF_Reached_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x0C", 4); // Size = 12

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(true));



    video->decodeBlock(0, "other");

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_SizeLessThanHeader_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x00\x07", 4); // Size = 7 (less than header)

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));



    EXPECT_THROW(video->decodeBlock(0, "other"), Exiv2::Error);

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_SizeExceedsIOSize_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\x00\x00\x10\x00", 4); // Size = 4096

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    ON_CALL(*mockIo, tell()).WillByDefault(Return(0));

    ON_CALL(*mockIo, size()).WillByDefault(Return(1024));



    EXPECT_THROW(video->decodeBlock(0, "other"), Exiv2::Error);

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_SizeExceedsMaxSizeT_658) {

    EXPECT_CALL(*mockIo, read(_, 4)).WillOnce([](byte *buf, size_t rcount){

        memcpy(buf, "\xFF\xFF\xFF\xFF", 4); // Size = UINT32_MAX

        return rcount;

    });



    EXPECT_CALL(*mockIo, eof()).WillOnce(Return(false));

    ON_CALL(*mockIo, tell()).WillByDefault(Return(0));



    EXPECT_THROW(video->decodeBlock(0, "other"), Exiv2::Error);

}



TEST_F(QuickTimeVideoTest_658, DecodeBlock_MaxRecursionDepthReached_658) {

    EXPECT_THROW(video->decodeBlock(10, "other"), Exiv2::Error);

}
