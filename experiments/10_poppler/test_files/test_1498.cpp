#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(const StreamKind, getKind, (), (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(bool, isBinary, (bool last), (const, override));

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

    std::unique_ptr<MockStream> mockStream = std::make_unique<MockStream>();

    std::unique_ptr<BaseStreamStream> baseStreamStream;



    void SetUp() override {

        baseStreamStream = std::make_unique<BaseStreamStream>(std::move(mockStream));

    }

};



TEST_F(BaseStreamStreamTest_1498, GetDictReturnsBaseStreamDict_1498) {

    Dict mockDict;

    EXPECT_CALL(*mockStream, getBaseStream())

        .WillOnce(Return(new BaseStream(Object(), 0)));



    EXPECT_CALL(*(baseStreamStream->getBaseStream()), getDict())

        .WillOnce(Return(&mockDict));



    EXPECT_EQ(baseStreamStream->getDict(), &mockDict);

}



TEST_F(BaseStreamStreamTest_1498, RewindCallsBaseStreamRewind_1498) {

    EXPECT_CALL(*mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(baseStreamStream->rewind());

}



TEST_F(BaseStreamStreamTest_1498, GetCharDelegatesToBaseStream_1498) {

    EXPECT_CALL(*mockStream, getChar()).WillOnce(Return(42));

    EXPECT_EQ(baseStreamStream->getChar(), 42);

}



TEST_F(BaseStreamStreamTest_1498, LookCharDelegatesToBaseStream_1498) {

    EXPECT_CALL(*mockStream, lookChar()).WillOnce(Return(42));

    EXPECT_EQ(baseStreamStream->lookChar(), 42);

}



TEST_F(BaseStreamStreamTest_1498, IsBinaryDelegatesToBaseStream_1498) {

    EXPECT_CALL(*mockStream, isBinary(true)).WillOnce(Return(true));

    EXPECT_TRUE(baseStreamStream->isBinary());

}



TEST_F(BaseStreamStreamTest_1498, GetUnfilteredCharDelegatesToBaseStream_1498) {

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(42));

    EXPECT_EQ(baseStreamStream->getUnfilteredChar(), 42);

}



TEST_F(BaseStreamStreamTest_1498, UnfilteredRewindCallsBaseStreamUnfilteredRewind_1498) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(true));

    EXPECT_TRUE(baseStreamStream->unfilteredRewind());

}



TEST_F(BaseStreamStreamTest_1498, GetPosDelegatesToBaseStream_1498) {

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(Goffset(1024)));

    EXPECT_EQ(baseStreamStream->getPos(), Goffset(1024));

}



TEST_F(BaseStreamStreamTest_1498, SetPosDelegatesToBaseStream_1498) {

    EXPECT_CALL(*mockStream, setPos(Goffset(512), 1)).WillOnce(Return());

    baseStreamStream->setPos(Goffset(512), 1);

}



TEST_F(BaseStreamStreamTest_1498, GetBaseStreamReturnsOriginalStream_1498) {

    EXPECT_EQ(baseStreamStream->getBaseStream(), mockStream.get());

}



TEST_F(BaseStreamStreamTest_1498, GetUndecodedStreamDelegatesToBaseStream_1498) {

    Stream* expectedStream = new Stream();

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(expectedStream));

    EXPECT_EQ(baseStreamStream->getUndecodedStream(), expectedStream);

}



TEST_F(BaseStreamStreamTest_1498, GetDictObjectDelegatesToBaseStream_1498) {

    Object* mockObject = new Object();

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(mockObject));

    EXPECT_EQ(baseStreamStream->getDictObject(), mockObject);

}
