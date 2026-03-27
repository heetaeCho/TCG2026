#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/riffvideo.hpp"

#include "exiv2/basicio.hpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class MockBasicIo : public BasicIo {

public:

    MOCK_METHOD(int, open, (), (override));

    MOCK_METHOD(int, close, (), (override));

    MOCK_METHOD(size_t, write, (const byte*, size_t), (override));

    MOCK_METHOD(size_t, write, (BasicIo&), (override));

    MOCK_METHOD(int, putb, (byte), (override));

    MOCK_METHOD(DataBuf, read, (size_t), (override));

    MOCK_METHOD(size_t, read, (byte*, size_t), (override));

    MOCK_METHOD(void, readOrThrow, (byte*, size_t, ErrorCode), (override));

    MOCK_METHOD(int, getb, (), (override));

    MOCK_METHOD(void, transfer, (BasicIo&), (override));

    MOCK_METHOD(int, seek, (int64_t, Position), (override));

    MOCK_METHOD(void, seekOrThrow, (int64_t, Position, ErrorCode), (override));

    MOCK_METHOD(byte*, mmap, (bool), (override));

    MOCK_METHOD(int, munmap, (), (override));

    MOCK_METHOD(const size_t, tell, (), (const, override));

    MOCK_METHOD(const size_t, size, (), (const, override));

    MOCK_METHOD(const bool, isopen, (), (const, override));

    MOCK_METHOD(const int, error, (), (const, override));

    MOCK_METHOD(const bool, eof, (), (const, override));

    MOCK_METHOD(const std::string&, path, (), (const, override));

};



class RiffVideoTest_81 : public ::testing::Test {

protected:

    void SetUp() override {

        ioMock = std::make_unique<MockBasicIo>();

        riffVideo = new RiffVideo(std::move(ioMock));

    }



    void TearDown() override {

        delete riffVideo;

    }



    RiffVideo* riffVideo;

    std::unique_ptr<MockBasicIo> ioMock;

};



TEST_F(RiffVideoTest_81, DecodeBlocksReadsList_81) {

    EXPECT_CALL(*ioMock, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*ioMock, tell()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, size()).WillOnce(Return(256));



    HeaderReader header(ioMock);

    EXPECT_CALL(header, getId()).WillOnce(Return(CHUNK_ID_LIST));

    

    EXPECT_CALL(*ioMock, seek(_, _)).Times(1); // Simulate reading the list

    EXPECT_CALL(*ioMock, read(_)).Times(AtLeast(1)); // Simulate reading data



    riffVideo->decodeBlocks();

}



TEST_F(RiffVideoTest_81, DecodeBlocksReadsChunk_81) {

    EXPECT_CALL(*ioMock, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*ioMock, tell()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, size()).WillOnce(Return(256));



    HeaderReader header(ioMock);

    EXPECT_CALL(header, getId()).WillOnce(Return("CHNK_ID"));



    EXPECT_CALL(*ioMock, seek(_, _)).Times(1); // Simulate reading the chunk

    EXPECT_CALL(*ioMock, read(_)).Times(AtLeast(1)); // Simulate reading data



    riffVideo->decodeBlocks();

}



TEST_F(RiffVideoTest_81, DecodeBlocksEndOfFile_81) {

    EXPECT_CALL(*ioMock, eof()).WillOnce(Return(true));

    EXPECT_CALL(*ioMock, tell()).WillOnce(Return(0));

    EXPECT_CALL(*ioMock, size()).WillOnce(Return(256));



    riffVideo->decodeBlocks();

}



TEST_F(RiffVideoTest_81, DecodeBlocksAtEndOfFile_81) {

    EXPECT_CALL(*ioMock, eof()).WillOnce(Return(false)).WillOnce(Return(true));

    EXPECT_CALL(*ioMock, tell()).WillOnce(Return(256));

    EXPECT_CALL(*ioMock, size()).WillOnce(Return(256));



    riffVideo->decodeBlocks();

}
