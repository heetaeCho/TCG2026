#include <gtest/gtest.h>

#include "Stream.h"

#include <gmock/gmock.h>



using ::testing::Return;

using ::testing::_;



class MockStream : public Stream {

public:

    MOCK_METHOD(const StreamKind, getKind, (), (override));

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(int, lookChar, (), (override));

    MOCK_METHOD(int, getRawChar, (), (override));

    MOCK_METHOD(void, getRawChars, (int nChars, int *buffer), (override));

    MOCK_METHOD(int, getUnfilteredChar, (), (override));

    MOCK_METHOD(bool, unfilteredRewind, (), (override));

    MOCK_METHOD(char *, getLine, (char *buf, int size), (override));

    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));

    MOCK_METHOD(Goffset, getPos, (), (override));

    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));

    MOCK_METHOD(const bool, isBinary, (bool last), (override));

    MOCK_METHOD(BaseStream *, getBaseStream, (), (override));

    MOCK_METHOD(Stream *, getUndecodedStream, (), (override));

    MOCK_METHOD(Dict *, getDict, (), (override));

    MOCK_METHOD(Object *, getDictObject, (), (override));

    MOCK_METHOD(bool, isEncrypted, (), (const override));

    MOCK_METHOD(void, getImageParams, (int *bitsPerComponent, StreamColorSpaceMode *csMode, bool *hasAlpha), (override));

    MOCK_METHOD(Stream *, getNextStream, (), (const override));

};



class FilterStreamTest_142 : public ::testing::Test {

protected:

    std::unique_ptr<MockStream> mockStream;

    std::unique_ptr<FilterStream> filterStream;



    void SetUp() override {

        mockStream = std::make_unique<MockStream>();

        filterStream = std::make_unique<FilterStream>(mockStream.get());

    }

};



TEST_F(FilterStreamTest_142, GetDictReturnsSameAsBaseStream_142) {

    Dict* expectedDict = new Dict();

    EXPECT_CALL(*mockStream, getDict()).WillOnce(Return(expectedDict));

    EXPECT_EQ(filterStream->getDict(), expectedDict);

}



TEST_F(FilterStreamTest_142, CloseDelegatesToBaseStream_142) {

    EXPECT_CALL(*mockStream, close());

    filterStream->close();

}



TEST_F(FilterStreamTest_142, SetPosDelegatesToBaseStream_142) {

    Goffset pos = 100;

    int dir = 0;

    EXPECT_CALL(*mockStream, setPos(pos, dir));

    filterStream->setPos(pos, dir);

}



TEST_F(FilterStreamTest_142, GetPosDelegatesToBaseStream_142) {

    Goffset expectedPos = 100;

    EXPECT_CALL(*mockStream, getPos()).WillOnce(Return(expectedPos));

    EXPECT_EQ(filterStream->getPos(), expectedPos);

}



TEST_F(FilterStreamTest_142, GetBaseStreamDelegatesToBaseStream_142) {

    BaseStream* expectedBaseStream = new BaseStream();

    EXPECT_CALL(*mockStream, getBaseStream()).WillOnce(Return(expectedBaseStream));

    EXPECT_EQ(filterStream->getBaseStream(), expectedBaseStream);

}



TEST_F(FilterStreamTest_142, GetUndecodedStreamDelegatesToBaseStream_142) {

    Stream* expectedUndecodedStream = new Stream();

    EXPECT_CALL(*mockStream, getUndecodedStream()).WillOnce(Return(expectedUndecodedStream));

    EXPECT_EQ(filterStream->getUndecodedStream(), expectedUndecodedStream);

}



TEST_F(FilterStreamTest_142, GetDictObjectDelegatesToBaseStream_142) {

    Object* expectedDictObject = new Object();

    EXPECT_CALL(*mockStream, getDictObject()).WillOnce(Return(expectedDictObject));

    EXPECT_EQ(filterStream->getDictObject(), expectedDictObject);

}



TEST_F(FilterStreamTest_142, GetUnfilteredCharDelegatesToBaseStream_142) {

    int expectedChar = 65;

    EXPECT_CALL(*mockStream, getUnfilteredChar()).WillOnce(Return(expectedChar));

    EXPECT_EQ(filterStream->getUnfilteredChar(), expectedChar);

}



TEST_F(FilterStreamTest_142, UnfilteredRewindDelegatesToBaseStream_142) {

    EXPECT_CALL(*mockStream, unfilteredRewind()).WillOnce(Return(true));

    EXPECT_TRUE(filterStream->unfilteredRewind());

}
