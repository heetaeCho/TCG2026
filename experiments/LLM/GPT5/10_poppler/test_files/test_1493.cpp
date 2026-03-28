#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Stream.h"

class StreamMock : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int* buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char* buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char* indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));
    MOCK_METHOD(std::unique_ptr<Stream>, addFilters, (std::unique_ptr<Stream> stream, Dict* dict, int recursion), (static, override));
    MOCK_METHOD(bool, isEncrypted, (), (override));
};

class BaseStreamStreamTest_1493 : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up mock stream and BaseStreamStream instance
        streamMock = std::make_unique<StreamMock>();
        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(streamMock));
    }

    std::unique_ptr<StreamMock> streamMock;
    std::unique_ptr<BaseStreamStream> baseStreamStream;
};

TEST_F(BaseStreamStreamTest_1493, UnfilteredRewind_Success_1493) {
    EXPECT_CALL(*streamMock, unfilteredRewind())
        .WillOnce(testing::Return(true));

    bool result = baseStreamStream->unfilteredRewind();

    EXPECT_TRUE(result);
}

TEST_F(BaseStreamStreamTest_1493, UnfilteredRewind_Failure_1493) {
    EXPECT_CALL(*streamMock, unfilteredRewind())
        .WillOnce(testing::Return(false));

    bool result = baseStreamStream->unfilteredRewind();

    EXPECT_FALSE(result);
}

TEST_F(BaseStreamStreamTest_1493, GetPos_Valid_1493) {
    Goffset expectedPos = 100;
    EXPECT_CALL(*streamMock, getPos())
        .WillOnce(testing::Return(expectedPos));

    Goffset result = baseStreamStream->getPos();

    EXPECT_EQ(result, expectedPos);
}

TEST_F(BaseStreamStreamTest_1493, SetPos_Valid_1493) {
    Goffset pos = 50;
    int direction = 1;

    EXPECT_CALL(*streamMock, setPos(pos, direction))
        .Times(1);

    baseStreamStream->setPos(pos, direction);
}

TEST_F(BaseStreamStreamTest_1493, GetKind_Valid_1493) {
    StreamKind expectedKind = StreamKind::kKindOther;
    EXPECT_CALL(*streamMock, getKind())
        .WillOnce(testing::Return(expectedKind));

    StreamKind result = baseStreamStream->getKind();

    EXPECT_EQ(result, expectedKind);
}

TEST_F(BaseStreamStreamTest_1493, GetBaseStream_Valid_1493) {
    BaseStream* expectedBaseStream = nullptr;
    EXPECT_CALL(*streamMock, getBaseStream())
        .WillOnce(testing::Return(expectedBaseStream));

    BaseStream* result = baseStreamStream->getBaseStream();

    EXPECT_EQ(result, expectedBaseStream);
}

TEST_F(BaseStreamStreamTest_1493, GetUndecodedStream_Valid_1493) {
    Stream* expectedStream = nullptr;
    EXPECT_CALL(*streamMock, getUndecodedStream())
        .WillOnce(testing::Return(expectedStream));

    Stream* result = baseStreamStream->getUndecodedStream();

    EXPECT_EQ(result, expectedStream);
}

TEST_F(BaseStreamStreamTest_1493, IsEncrypted_True_1493) {
    EXPECT_CALL(*streamMock, isEncrypted())
        .WillOnce(testing::Return(true));

    bool result = baseStreamStream->isEncrypted();

    EXPECT_TRUE(result);
}

TEST_F(BaseStreamStreamTest_1493, IsEncrypted_False_1493) {
    EXPECT_CALL(*streamMock, isEncrypted())
        .WillOnce(testing::Return(false));

    bool result = baseStreamStream->isEncrypted();

    EXPECT_FALSE(result);
}