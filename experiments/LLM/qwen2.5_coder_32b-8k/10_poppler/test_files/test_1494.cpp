#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Eq;



class MockStream : public Stream {

public:

    MOCK_METHOD(const StreamKind, getKind, (), (const, override));

    MOCK_METHOD(bool, rewind, (), (override));

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



class BaseStreamStreamTest : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    BaseStreamStream* baseStreamStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        baseStreamStream = new BaseStreamStream(std::move(mockStream));

    }



    void TearDown() override {

        delete baseStreamStream;

    }

};



TEST_F(BaseStreamStreamTest_1494, GetPos_DelegatesToBaseStream_1494) {

    Goffset expectedPos = 1024;

    EXPECT_CALL(*mockStream, getBaseStream())

        .WillOnce([]() { return new MockStream(); });

    EXPECT_CALL(*(static_cast<MockStream*>(baseStreamStream->getBaseStream())), getPos())

        .WillOnce(Return(expectedPos));



    Goffset pos = baseStreamStream->getPos();



    EXPECT_EQ(pos, expectedPos);

}



TEST_F(BaseStreamStreamTest_1494, Rewind_DelegatesToBaseStream_1494) {

    bool expectedResult = true;

    EXPECT_CALL(*mockStream, rewind())

        .WillOnce(Return(expectedResult));



    bool result = baseStreamStream->rewind();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1494, GetChar_DelegatesToBaseStream_1494) {

    int expectedChar = 'A';

    EXPECT_CALL(*mockStream, getChar())

        .WillOnce(Return(expectedChar));



    int result = baseStreamStream->getChar();



    EXPECT_EQ(result, expectedChar);

}



TEST_F(BaseStreamStreamTest_1494, LookChar_DelegatesToBaseStream_1494) {

    int expectedChar = 'B';

    EXPECT_CALL(*mockStream, lookChar())

        .WillOnce(Return(expectedChar));



    int result = baseStreamStream->lookChar();



    EXPECT_EQ(result, expectedChar);

}



TEST_F(BaseStreamStreamTest_1494, IsBinary_DelegatesToBaseStream_1494) {

    bool expectedResult = true;

    EXPECT_CALL(*mockStream, isBinary(true))

        .WillOnce(Return(expectedResult));



    bool result = baseStreamStream->isBinary();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1494, GetUnfilteredChar_DelegatesToBaseStream_1494) {

    int expectedChar = 'C';

    EXPECT_CALL(*mockStream, getUnfilteredChar())

        .WillOnce(Return(expectedChar));



    int result = baseStreamStream->getUnfilteredChar();



    EXPECT_EQ(result, expectedChar);

}



TEST_F(BaseStreamStreamTest_1494, UnfilteredRewind_DelegatesToBaseStream_1494) {

    bool expectedResult = true;

    EXPECT_CALL(*mockStream, unfilteredRewind())

        .WillOnce(Return(expectedResult));



    bool result = baseStreamStream->unfilteredRewind();



    EXPECT_EQ(result, expectedResult);

}



TEST_F(BaseStreamStreamTest_1494, SetPos_DelegatesToBaseStream_1494) {

    Goffset pos = 2048;

    int dir = 0;

    EXPECT_CALL(*mockStream, setPos(Eq(pos), Eq(dir)))

        .WillOnce([]() {});



    baseStreamStream->setPos(pos, dir);

}



TEST_F(BaseStreamStreamTest_1494, GetBaseStream_ReturnsBaseStream_1494) {

    MockStream* expectedBaseStream = new MockStream();

    EXPECT_CALL(*mockStream, getBaseStream())

        .WillOnce(Return(expectedBaseStream));



    BaseStream* result = baseStreamStream->getBaseStream();



    EXPECT_EQ(result, expectedBaseStream);

}



TEST_F(BaseStreamStreamTest_1494, GetUndecodedStream_DelegatesToBaseStream_1494) {

    MockStream* expectedUndecodedStream = new MockStream();

    EXPECT_CALL(*mockStream, getUndecodedStream())

        .WillOnce(Return(expectedUndecodedStream));



    Stream* result = baseStreamStream->getUndecodedStream();



    EXPECT_EQ(result, expectedUndecodedStream);

}



TEST_F(BaseStreamStreamTest_1494, GetDict_DelegatesToBaseStream_1494) {

    Dict* expectedDict = nullptr;

    EXPECT_CALL(*mockStream, getDict())

        .WillOnce(Return(expectedDict));



    Dict* result = baseStreamStream->getDict();



    EXPECT_EQ(result, expectedDict);

}



TEST_F(BaseStreamStreamTest_1494, GetDictObject_DelegatesToBaseStream_1494) {

    Object* expectedDictObject = nullptr;

    EXPECT_CALL(*mockStream, getDictObject())

        .WillOnce(Return(expectedDictObject));



    Object* result = baseStreamStream->getDictObject();



    EXPECT_EQ(result, expectedDictObject);

}
