#include <gtest/gtest.h>

#include "Stream.h"

#include <memory>



class MockStream : public Stream {

public:

    MOCK_METHOD(const StreamKind, getKind, (), (const, override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

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



TEST_F(BaseStreamStreamTest, GetUndecodedStream_ReturnsUnderlyingStream_1497) {

    auto* expectedStream = reinterpret_cast<Stream*>(0x1234);

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(::testing::Return(expectedStream));



    Stream* result = baseStreamStream->getUndecodedStream();



    EXPECT_EQ(result, expectedStream);

}



TEST_F(BaseStreamStreamTest, GetBaseStream_ReturnsUnderlyingBaseStream_1497) {

    auto* expectedBaseStream = reinterpret_cast<BaseStream*>(0x5678);

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(::testing::Return(expectedBaseStream));



    BaseStream* result = baseStreamStream->getBaseStream();



    EXPECT_EQ(result, expectedBaseStream);

}



TEST_F(BaseStreamStreamTest, Rewind_DelegatesToUnderlyingStream_1497) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(::testing::Return(true));



    bool result = baseStreamStream->rewind();



    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest, GetChar_DelegatesToUnderlyingStream_1497) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(::testing::Return(expectedChar));



    int result = baseStreamStream->getChar();



    EXPECT_EQ(result, expectedChar);

}



TEST_F(BaseStreamStreamTest, LookChar_DelegatesToUnderlyingStream_1497) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(::testing::Return(expectedChar));



    int result = baseStreamStream->lookChar();



    EXPECT_EQ(result, expectedChar);

}



TEST_F(BaseStreamStreamTest, GetUnfilteredChar_DelegatesToUnderlyingStream_1497) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(::testing::Return(expectedChar));



    int result = baseStreamStream->getUnfilteredChar();



    EXPECT_EQ(result, expectedChar);

}



TEST_F(BaseStreamStreamTest, UnfilteredRewind_DelegatesToUnderlyingStream_1497) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(::testing::Return(true));



    bool result = baseStreamStream->unfilteredRewind();



    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest, GetPos_DelegatesToUnderlyingStream_1497) {

    Goffset expectedPosition = 1024;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(::testing::Return(expectedPosition));



    Goffset result = baseStreamStream->getPos();



    EXPECT_EQ(result, expectedPosition);

}



TEST_F(BaseStreamStreamTest, SetPos_DelegatesToUnderlyingStream_1497) {

    Goffset position = 1024;

    int direction = 0;



    EXPECT_CALL(*mockStream, setPos(position, direction));



    baseStreamStream->setPos(position, direction);

}



TEST_F(BaseStreamStreamTest, GetDict_DelegatesToUnderlyingStream_1497) {

    Dict* expectedDict = reinterpret_cast<Dict*>(0x89AB);

    EXPECT_CALL(*mockStream, getDict()).WillOnce(::testing::Return(expectedDict));



    Dict* result = baseStreamStream->getDict();



    EXPECT_EQ(result, expectedDict);

}



TEST_F(BaseStreamStreamTest, GetDictObject_DelegatesToUnderlyingStream_1497) {

    Object* expectedObject = reinterpret_cast<Object*>(0xCDEF);

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(::testing::Return(expectedObject));



    Object* result = baseStreamStream->getDictObject();



    EXPECT_EQ(result, expectedObject);

}
