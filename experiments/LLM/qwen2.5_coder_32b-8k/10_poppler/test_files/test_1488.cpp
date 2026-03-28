#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using ::testing::Return;

using ::testing::_;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));

    MOCK_METHOD(Dict*, getDict, (), (override));

    MOCK_METHOD(Object*, getDictObject, (), (override));

};



class BaseStreamStreamTest_1488 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<BaseStreamStream> baseStreamStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));

    }

};



TEST_F(BaseStreamStreamTest_1488, RewindDelegatesToBaseStream_1488) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));



    bool result = baseStreamStream->rewind();



    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest_1488, GetKindDelegatesToBaseStream_1488) {

    StreamKind expectedKind = streamGZ;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(expectedKind));



    StreamKind result = baseStreamStream->getKind();



    EXPECT_EQ(result, expectedKind);

}



TEST_F(BaseStreamStreamTest_1488, GetCharDelegatesToBaseStream_1488) {

    int expectedResult = 65;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(expectedResult));



    int result = baseStreamStream->getChar();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, LookCharDelegatesToBaseStream_1488) {

    int expectedResult = 66;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(expectedResult));



    int result = baseStreamStream->lookChar();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, IsBinaryDelegatesToBaseStream_1488) {

    bool last = true;

    bool expectedResult = false;

    EXPECT_CALL(*mockStream, isBinary(last)).WillOnce(Return(expectedResult));



    bool result = baseStreamStream->isBinary(last);



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, GetUnfilteredCharDelegatesToBaseStream_1488) {

    int expectedResult = 67;

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(expectedResult));



    int result = baseStreamStream->getUnfilteredChar();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, UnfilteredRewindDelegatesToBaseStream_1488) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(true));



    bool result = baseStreamStream->unfilteredRewind();



    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest_1488, GetPosDelegatesToBaseStream_1488) {

    Goffset expectedResult = 1024;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(expectedResult));



    Goffset result = baseStreamStream->getPos();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, SetPosDelegatesToBaseStream_1488) {

    Goffset pos = 2048;

    int dir = 0;

    EXPECT_CALL(*mockStream, setPos(pos, dir));



    baseStreamStream->setPos(pos, dir);

}



TEST_F(BaseStreamStreamTest_1488, GetBaseStreamDelegatesToBaseStream_1488) {

    BaseStream* expectedResult = nullptr;

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(Return(expectedResult));



    BaseStream* result = baseStreamStream->getBaseStream();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, GetUndecodedStreamDelegatesToBaseStream_1488) {

    Stream* expectedResult = nullptr;

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(expectedResult));



    Stream* result = baseStreamStream->getUndecodedStream();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, GetDictDelegatesToBaseStream_1488) {

    Dict* expectedResult = nullptr;

    EXPECT_CALL(*mockStream, getDict()).WillOnce(Return(expectedResult));



    Dict* result = baseStreamStream->getDict();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1488, GetDictObjectDelegatesToBaseStream_1488) {

    Object* expectedResult = nullptr;

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(expectedResult));



    Object* result = baseStreamStream->getDictObject();



    EXPECT_EQ(result, expectedResult);

}
