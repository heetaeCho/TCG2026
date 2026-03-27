#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "Stream.h"



using namespace testing;



class FilterStreamTest : public Test {

protected:

    MockStream* mockBaseStream;

    FilterStream* filterStream;



    class MockStream : public Stream {

    public:

        MOCK_METHOD(const StreamKind, getKind, (), (override));

        MOCK_METHOD(bool, rewind, (), (override));

        MOCK_METHOD(void, close, (), (override));

        MOCK_METHOD(int, getChar, (), (override));

        MOCK_METHOD(int, lookChar, (), (override));

        MOCK_METHOD(int, getRawChar, (), (override));

        MOCK_METHOD(void, getRawChars, (int nChars, int * buffer), (override));

        MOCK_METHOD(int, getUnfilteredChar, (), (override));

        MOCK_METHOD(bool, unfilteredRewind, (), (override));

        MOCK_METHOD(char *, getLine, (char * buf, int size), (override));

        MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));

        MOCK_METHOD(Goffset, getPos, (), (override));

        MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));

        MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

        MOCK_METHOD(const bool, isBinary, (bool last), (override));

        MOCK_METHOD(BaseStream *, getBaseStream, (), (override));

        MOCK_METHOD(Stream *, getUndecodedStream, (), (override));

        MOCK_METHOD(Dict *, getDict, (), (override));

        MOCK_METHOD(Object *, getDictObject, (), (override));

        MOCK_METHOD(std::unique_ptr<Stream>, addFilters, (std::unique_ptr<Stream> stream, Dict * dict, int recursion), (static));

        MOCK_CONST_METHOD0(isEncrypted, bool(), (override));

        MOCK_METHOD(int, doGetChars, (int nChars, unsigned char * buffer), (protected));

        MOCK_METHOD(void, fillString, (std::string & s), ());

        MOCK_METHOD(void, fillGooString, (GooString * s), ());

        MOCK_METHOD(std::vector<unsigned char>, toUnsignedChars, (int initialSize, int sizeIncrement), ());

        MOCK_CONST_METHOD0(isEncoder, bool(), (override));

        MOCK_METHOD(void, getImageParams, (int *, StreamColorSpaceMode *, bool *), (override));

        MOCK_METHOD(Stream *, getNextStream, (), (const override));

        MOCK_METHOD(int, incRef, (), (private));

        MOCK_METHOD(int, decRef, (), (private));

        MOCK_METHOD(bool, hasGetChars, (), (protected));

    };



    void SetUp() override {

        mockBaseStream = new MockStream();

        filterStream = new FilterStream(mockBaseStream);

    }



    void TearDown() override {

        delete filterStream;

        delete mockBaseStream;

    }

};



TEST_F(FilterStreamTest_140, GetBaseStreamReturnsSameAsMocked_140) {

    BaseStream* expectedBaseStream = reinterpret_cast<BaseStream*>(0x12345678);

    EXPECT_CALL(*mockBaseStream, getBaseStream()).WillOnce(Return(expectedBaseStream));

    EXPECT_EQ(filterStream->getBaseStream(), expectedBaseStream);

}



TEST_F(FilterStreamTest_140, GetUndecodedStreamDelegatesToMocked_140) {

    Stream* expectedStream = reinterpret_cast<Stream*>(0x87654321);

    EXPECT_CALL(*mockBaseStream, getUndecodedStream()).WillOnce(Return(expectedStream));

    EXPECT_EQ(filterStream->getUndecodedStream(), expectedStream);

}



TEST_F(FilterStreamTest_140, GetDictDelegatesToMocked_140) {

    Dict* expectedDict = reinterpret_cast<Dict*>(0x56781234);

    EXPECT_CALL(*mockBaseStream, getDict()).WillOnce(Return(expectedDict));

    EXPECT_EQ(filterStream->getDict(), expectedDict);

}



TEST_F(FilterStreamTest_140, GetDictObjectDelegatesToMocked_140) {

    Object* expectedObject = reinterpret_cast<Object*>(0x34567812);

    EXPECT_CALL(*mockBaseStream, getDictObject()).WillOnce(Return(expectedObject));

    EXPECT_EQ(filterStream->getDictObject(), expectedObject);

}



TEST_F(FilterStreamTest_140, GetNextStreamDelegatesToMocked_140) {

    Stream* expectedStream = reinterpret_cast<Stream*>(0x21876543);

    EXPECT_CALL(*mockBaseStream, getNextStream()).WillOnce(Return(expectedStream));

    EXPECT_EQ(filterStream->getNextStream(), expectedStream);

}



TEST_F(FilterStreamTest_140, GetUnfilteredCharDelegatesToMocked_140) {

    int expectedResult = 97; // 'a'

    EXPECT_CALL(*mockBaseStream, getUnfilteredChar()).WillOnce(Return(expectedResult));

    EXPECT_EQ(filterStream->getUnfilteredChar(), expectedResult);

}



TEST_F(FilterStreamTest_140, UnfilteredRewindDelegatesToMocked_140) {

    bool expectedResult = true;

    EXPECT_CALL(*mockBaseStream, unfilteredRewind()).WillOnce(Return(expectedResult));

    EXPECT_EQ(filterStream->unfilteredRewind(), expectedResult);

}



TEST_F(FilterStreamTest_140, SetPosCallsMocked_140) {

    Goffset pos = 1024;

    int dir = 0; // Example direction

    EXPECT_CALL(*mockBaseStream, setPos(pos, dir));

    filterStream->setPos(pos, dir);

}



TEST_F(FilterStreamTest_140, GetPosDelegatesToMocked_140) {

    Goffset expectedPos = 2048;

    EXPECT_CALL(*mockBaseStream, getPos()).WillOnce(Return(expectedPos));

    EXPECT_EQ(filterStream->getPos(), expectedPos);

}



TEST_F(FilterStreamTest_140, CloseCallsMocked_140) {

    EXPECT_CALL(*mockBaseStream, close());

    filterStream->close();

}
