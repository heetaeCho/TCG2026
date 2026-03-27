#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockBaseStream : public Stream {

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



class BaseStreamStreamTest_1492 : public Test {

protected:

    std::unique_ptr<MockBaseStream> mockBaseStream;

    BaseStreamStream* baseStreamStream;



    void SetUp() override {

        mockBaseStream = std::make_unique<MockBaseStream>();

        baseStreamStream = new BaseStreamStream(std::move(mockBaseStream));

    }



    void TearDown() override {

        delete baseStreamStream;

    }

};



TEST_F(BaseStreamStreamTest_1492, GetUnfilteredChar_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getBaseStream())

               .WillOnce(Return(mockBaseStream.get()));

    EXPECT_CALL(*mockBaseStream, getUnfilteredChar())

               .WillOnce(Return(42));



    int result = baseStreamStream->getUnfilteredChar();

    EXPECT_EQ(result, 42);

}



TEST_F(BaseStreamStreamTest_1492, Rewind_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getBaseStream())

               .WillOnce(Return(mockBaseStream.get()));

    EXPECT_CALL(*mockBaseStream, rewind())

               .WillOnce(Return(true));



    bool result = baseStreamStream->rewind();

    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest_1492, GetChar_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getChar())

               .WillOnce(Return(42));



    int result = baseStreamStream->getChar();

    EXPECT_EQ(result, 42);

}



TEST_F(BaseStreamStreamTest_1492, LookChar_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, lookChar())

               .WillOnce(Return(42));



    int result = baseStreamStream->lookChar();

    EXPECT_EQ(result, 42);

}



TEST_F(BaseStreamStreamTest_1492, IsBinary_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, isBinary(true))

               .WillOnce(Return(true));



    bool result = baseStreamStream->isBinary();

    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest_1492, UnfilteredRewind_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, unfilteredRewind())

               .WillOnce(Return(true));



    bool result = baseStreamStream->unfilteredRewind();

    EXPECT_TRUE(result);

}



TEST_F(BaseStreamStreamTest_1492, GetPos_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getPos())

               .WillOnce(Return(static_cast<Goffset>(42)));



    Goffset result = baseStreamStream->getPos();

    EXPECT_EQ(result, static_cast<Goffset>(42));

}



TEST_F(BaseStreamStreamTest_1492, SetPos_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, setPos(static_cast<Goffset>(42), 0));



    baseStreamStream->setPos(static_cast<Goffset>(42), 0);

}



TEST_F(BaseStreamStreamTest_1492, GetBaseStream_ReturnsBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getBaseStream())

               .WillOnce(Return(mockBaseStream.get()));



    BaseStream* result = baseStreamStream->getBaseStream();

    EXPECT_EQ(result, mockBaseStream.get());

}



TEST_F(BaseStreamStreamTest_1492, GetUndecodedStream_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getUndecodedStream())

               .WillOnce(Return(mockBaseStream.get()));



    Stream* result = baseStreamStream->getUndecodedStream();

    EXPECT_EQ(result, mockBaseStream.get());

}



TEST_F(BaseStreamStreamTest_1492, GetDict_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getDict())

               .WillOnce(Return(static_cast<Dict*>(nullptr)));



    Dict* result = baseStreamStream->getDict();

    EXPECT_EQ(result, static_cast<Dict*>(nullptr));

}



TEST_F(BaseStreamStreamTest_1492, GetDictObject_DelegatesToBaseStream_1492) {

    EXPECT_CALL(*mockBaseStream, getDictObject())

               .WillOnce(Return(static_cast<Object*>(nullptr)));



    Object* result = baseStreamStream->getDictObject();

    EXPECT_EQ(result, static_cast<Object*>(nullptr));

}
