#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(const StreamKind, getKind, (), (const override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(bool, isBinary, (bool), (const override));

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));

    MOCK_METHOD(Dict*, getDict, (), (override));

    MOCK_METHOD(Object*, getDictObject, (), (override));

};



class BaseStreamStreamTest_1496 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<BaseStreamStream> baseStreamStream;



    void SetUp() override {

        mockStream = std::make_unique<StrictMock<MockStream>>();

        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));

    }

};



TEST_F(BaseStreamStreamTest_1496, GetKind_ReturnsSameAsBaseStream_1496) {

    EXPECT_CALL(*mockStream, getKind()).WillOnce(Return(StreamKind::other));

    EXPECT_EQ(baseStreamStream->getKind(), StreamKind::other);

}



TEST_F(BaseStreamStreamTest_1496, Rewind_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(baseStreamStream->rewind());

}



TEST_F(BaseStreamStreamTest_1496, GetChar_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(42));

    EXPECT_EQ(baseStreamStream->getChar(), 42);

}



TEST_F(BaseStreamStreamTest_1496, LookChar_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(84));

    EXPECT_EQ(baseStreamStream->lookChar(), 84);

}



TEST_F(BaseStreamStreamTest_1496, IsBinary_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(Return(false));

    EXPECT_FALSE(baseStreamStream->isBinary(true));

}



TEST_F(BaseStreamStreamTest_1496, GetUnfilteredChar_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(123));

    EXPECT_EQ(baseStreamStream->getUnfilteredChar(), 123);

}



TEST_F(BaseStreamStreamTest_1496, UnfilteredRewind_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(true));

    EXPECT_TRUE(baseStreamStream->unfilteredRewind());

}



TEST_F(BaseStreamStreamTest_1496, GetPos_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(1024));

    EXPECT_EQ(baseStreamStream->getPos(), 1024);

}



TEST_F(BaseStreamStreamTest_1496, SetPos_DelegatesToBaseStream_1496) {

    EXPECT_CALL(*mockStream, setPos(512, 0)).WillOnce(Return());

    baseStreamStream->setPos(512, 0);

}



TEST_F(BaseStreamStreamTest_1496, GetBaseStream_DelegatesToBaseStream_1496) {

    MockStream* mockBaseStream = new StrictMock<MockStream>();

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(Return(mockBaseStream));

    EXPECT_EQ(baseStreamStream->getBaseStream(), mockBaseStream);

}



TEST_F(BaseStreamStreamTest_1496, GetUndecodedStream_DelegatesToBaseStream_1496) {

    MockStream* mockUndecodedStream = new StrictMock<MockStream>();

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(mockUndecodedStream));

    EXPECT_EQ(baseStreamStream->getUndecodedStream(), mockUndecodedStream);

}



TEST_F(BaseStreamStreamTest_1496, GetDict_DelegatesToBaseStream_1496) {

    Dict* expectedDict = new Dict();

    EXPECT_CALL(*mockStream, getDict()).WillOnce(Return(expectedDict));

    EXPECT_EQ(baseStreamStream->getDict(), expectedDict);

}



TEST_F(BaseStreamStreamTest_1496, GetDictObject_DelegatesToBaseStream_1496) {

    Object* expectedObject = new Object();

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(expectedObject));

    EXPECT_EQ(baseStreamStream->getDictObject(), expectedObject);

}
