#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include "Stream.cc"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(StreamKind, getKind, (), (const, override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const, override));

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(void, setPos, (Goffset, int), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));

    MOCK_METHOD(Dict*, getDict, (), (override));

    MOCK_METHOD(Object*, getDictObject, (), (override));

};



class BaseStreamStreamTest_1487 : public Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    BaseStreamStream baseStreamStream;



    BaseStreamStreamTest_1487() 

        : mockStream(std::make_unique<MockStream>()),

          baseStreamStream(std::move(mockStream)) {}

};



TEST_F(BaseStreamStreamTest_1487, GetKind_ReturnsBaseStreamKind_1487) {

    StreamKind expectedKind = strFile;

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(expectedKind));

    

    StreamKind actualKind = baseStreamStream.getKind();

    EXPECT_EQ(actualKind, expectedKind);

}



TEST_F(BaseStreamStreamTest_1487, Rewind_DelegatesToBaseStream_1487) {

    EXPECT_CALL(*mockStream, rewind());

    

    bool result = baseStreamStream.rewind();

    EXPECT_TRUE(result); // Assuming mock returns true by default

}



TEST_F(BaseStreamStreamTest_1487, GetChar_DelegatesToBaseStream_1487) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(expectedChar));

    

    int actualChar = baseStreamStream.getChar();

    EXPECT_EQ(actualChar, expectedChar);

}



TEST_F(BaseStreamStreamTest_1487, LookChar_DelegatesToBaseStream_1487) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(expectedChar));

    

    int actualChar = baseStreamStream.lookChar();

    EXPECT_EQ(actualChar, expectedChar);

}



TEST_F(BaseStreamStreamTest_1487, IsBinary_DelegatesToBaseStream_1487) {

    bool last = true;

    bool isBinaryResult = true;

    EXPECT_CALL(*mockStream, isBinary(last)).WillOnce(Return(isBinaryResult));

    

    bool actualResult = baseStreamStream.isBinary();

    EXPECT_EQ(actualResult, isBinaryResult);

}



TEST_F(BaseStreamStreamTest_1487, GetUnfilteredChar_DelegatesToBaseStream_1487) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(expectedChar));

    

    int actualChar = baseStreamStream.getUnfilteredChar();

    EXPECT_EQ(actualChar, expectedChar);

}



TEST_F(BaseStreamStreamTest_1487, UnfilteredRewind_DelegatesToBaseStream_1487) {

    EXPECT_CALL(*mockStream, unfilteredRewind());

    

    bool result = baseStreamStream.unfilteredRewind();

    EXPECT_TRUE(result); // Assuming mock returns true by default

}



TEST_F(BaseStreamStreamTest_1487, GetPos_DelegatesToBaseStream_1487) {

    Goffset expectedPosition = 0;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(expectedPosition));

    

    Goffset actualPosition = baseStreamStream.getPos();

    EXPECT_EQ(actualPosition, expectedPosition);

}



TEST_F(BaseStreamStreamTest_1487, SetPos_DelegatesToBaseStream_1487) {

    Goffset position = 0;

    int direction = 0;

    EXPECT_CALL(*mockStream, setPos(position, direction));

    

    baseStreamStream.setPos(position, direction);

}



TEST_F(BaseStreamStreamTest_1487, GetBaseStream_DelegatesToBaseStream_1487) {

    BaseStream* expectedBaseStream = nullptr;

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(Return(expectedBaseStream));

    

    BaseStream* actualBaseStream = baseStreamStream.getBaseStream();

    EXPECT_EQ(actualBaseStream, expectedBaseStream);

}



TEST_F(BaseStreamStreamTest_1487, GetUndecodedStream_DelegatesToBaseStream_1487) {

    Stream* expectedStream = nullptr;

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(expectedStream));

    

    Stream* actualStream = baseStreamStream.getUndecodedStream();

    EXPECT_EQ(actualStream, expectedStream);

}



TEST_F(BaseStreamStreamTest_1487, GetDict_DelegatesToBaseStream_1487) {

    Dict* expectedDict = nullptr;

    EXPECT_CALL(*mockStream, getDict()).WillOnce(Return(expectedDict));

    

    Dict* actualDict = baseStreamStream.getDict();

    EXPECT_EQ(actualDict, expectedDict);

}



TEST_F(BaseStreamStreamTest_1487, GetDictObject_DelegatesToBaseStream_1487) {

    Object* expectedObject = nullptr;

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(expectedObject));

    

    Object* actualObject = baseStreamStream.getDictObject();

    EXPECT_EQ(actualObject, expectedObject);

}
