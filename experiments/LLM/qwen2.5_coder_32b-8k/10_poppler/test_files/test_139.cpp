#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class MockStream : public Stream {

public:

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));

    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));

    MOCK_METHOD(Dict*, getDict, (), (override));

    MOCK_METHOD(Object*, getDictObject, (), (override));

    MOCK_METHOD(Stream*, getNextStream, (), (const, override));

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

};



class FilterStreamTest_139 : public Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<FilterStream> filterStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        filterStream = std::make_unique<FilterStream>(mockStream.get());

    }

};



TEST_F(FilterStreamTest_139, GetPos_ReturnsSameAsStr_139) {

    Goffset expectedPos = 42;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(expectedPos));

    EXPECT_EQ(filterStream->getPos(), expectedPos);

}



TEST_F(FilterStreamTest_139, Close_DelegatesToUnderlyingStream_139) {

    EXPECT_CALL(*mockStream, close());

    filterStream->close();

}



TEST_F(FilterStreamTest_139, SetPos_DelegatesToUnderlyingStream_139) {

    Goffset pos = 42;

    int dir = 0;

    EXPECT_CALL(*mockStream, setPos(pos, dir));

    filterStream->setPos(pos, dir);

}



TEST_F(FilterStreamTest_139, GetBaseStream_DelegatesToUnderlyingStream_139) {

    BaseStream* expectedBaseStream = nullptr;

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(Return(expectedBaseStream));

    EXPECT_EQ(filterStream->getBaseStream(), expectedBaseStream);

}



TEST_F(FilterStreamTest_139, GetUndecodedStream_DelegatesToUnderlyingStream_139) {

    Stream* expectedUndecodedStream = nullptr;

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(expectedUndecodedStream));

    EXPECT_EQ(filterStream->getUndecodedStream(), expectedUndecodedStream);

}



TEST_F(FilterStreamTest_139, GetDict_DelegatesToUnderlyingStream_139) {

    Dict* expectedDict = nullptr;

    EXPECT_CALL(*mockStream, getDict()).WillOnce(Return(expectedDict));

    EXPECT_EQ(filterStream->getDict(), expectedDict);

}



TEST_F(FilterStreamTest_139, GetDictObject_DelegatesToUnderlyingStream_139) {

    Object* expectedDictObject = nullptr;

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(expectedDictObject));

    EXPECT_EQ(filterStream->getDictObject(), expectedDictObject);

}



TEST_F(FilterStreamTest_139, GetNextStream_DelegatesToUnderlyingStream_139) {

    Stream* expectedNextStream = nullptr;

    EXPECT_CALL(*mockStream, getNextStream()).WillOnce(Return(expectedNextStream));

    EXPECT_EQ(filterStream->getNextStream(), expectedNextStream);

}



TEST_F(FilterStreamTest_139, GetUnfilteredChar_DelegatesToUnderlyingStream_139) {

    int expectedChar = 42;

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(filterStream->getUnfilteredChar(), expectedChar);

}



TEST_F(FilterStreamTest_139, UnfilteredRewind_DelegatesToUnderlyingStream_139) {

    bool expectedResult = true;

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(expectedResult));

    EXPECT_EQ(filterStream->unfilteredRewind(), expectedResult);

}
