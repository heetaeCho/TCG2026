#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using ::testing::Return;

using ::testing::_;



class MockStream : public Stream {

public:

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(StreamKind, getKind, () const, (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

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



class BaseStreamStreamTest : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<BaseStreamStream> baseStreamStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));

    }

};



TEST_F(BaseStreamStreamTest, LookChar_ReturnsBaseStreamLookChar_1490) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(42));



    int result = baseStreamStream->lookChar();

    EXPECT_EQ(result, 42);

}



TEST_F(BaseStreamStreamTest, GetKind_DelegatesToBaseStream_1490) {

    StreamKind expectedKind = streamDeflate;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(expectedKind));



    StreamKind result = baseStreamStream->getKind();

    EXPECT_EQ(result, expectedKind);

}



TEST_F(BaseStreamStreamTest, Rewind_DelegatesToBaseStream_1490) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));



    bool result = baseStreamStream->rewind();

    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest, GetChar_DelegatesToBaseStream_1490) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(42));



    int result = baseStreamStream->getChar();

    EXPECT_EQ(result, 42);

}



TEST_F(BaseStreamStreamTest, IsBinary_DelegatesToBaseStream_1490) {

    EXPECT_CALL(*mockStream, isBinary(_)).WillOnce(Return(true));



    bool result = baseStreamStream->isBinary(true);

    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest, GetUnfilteredChar_DelegatesToBaseStream_1490) {

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(42));



    int result = baseStreamStream->getUnfilteredChar();

    EXPECT_EQ(result, 42);

}



TEST_F(BaseStreamStreamTest, UnfilteredRewind_DelegatesToBaseStream_1490) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(true));



    bool result = baseStreamStream->unfilteredRewind();

    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest, GetPos_DelegatesToBaseStream_1490) {

    Goffset expectedPosition = 123;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(expectedPosition));



    Goffset result = baseStreamStream->getPos();

    EXPECT_EQ(result, expectedPosition);

}



TEST_F(BaseStreamStreamTest, SetPos_DelegatesToBaseStream_1490) {

    Goffset position = 123;

    int dir = 456;



    EXPECT_CALL(*mockStream, setPos(position, dir)).Times(1);



    baseStreamStream->setPos(position, dir);

}



TEST_F(BaseStreamStreamTest, GetBaseStream_DelegatesToBaseStream_1490) {

    BaseStream* expectedBaseStream = nullptr;

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(Return(expectedBaseStream));



    BaseStream* result = baseStreamStream->getBaseStream();

    EXPECT_EQ(result, expectedBaseStream);

}



TEST_F(BaseStreamStreamTest, GetUndecodedStream_DelegatesToBaseStream_1490) {

    Stream* expectedUndecodedStream = nullptr;

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(expectedUndecodedStream));



    Stream* result = baseStreamStream->getUndecodedStream();

    EXPECT_EQ(result, expectedUndecodedStream);

}



TEST_F(BaseStreamStreamTest, GetDict_DelegatesToBaseStream_1490) {

    Dict* expectedDict = nullptr;

    EXPECT_CALL(*mockStream, getDict()).WillOnce(Return(expectedDict));



    Dict* result = baseStreamStream->getDict();

    EXPECT_EQ(result, expectedDict);

}



TEST_F(BaseStreamStreamTest, GetDictObject_DelegatesToBaseStream_1490) {

    Object* expectedDictObject = nullptr;

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(expectedDictObject));



    Object* result = baseStreamStream->getDictObject();

    EXPECT_EQ(result, expectedDictObject);

}
