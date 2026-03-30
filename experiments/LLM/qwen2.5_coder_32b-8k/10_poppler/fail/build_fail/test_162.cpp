#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class CachedFileStreamTest_162 : public Test {

protected:

    std::shared_ptr<CachedFile> mockCachedFile;

    CachedFileStream* stream;



    void SetUp() override {

        mockCachedFile = std::make_shared<NiceMock<StrictMock<CachedFile>>>();

        stream = new CachedFileStream(mockCachedFile, 0, false, 16384, Object());

    }



    void TearDown() override {

        delete stream;

    }

};



TEST_F(CachedFileStreamTest_162, GetUnfilteredChar_DelegatesToGetChar_162) {

    EXPECT_CALL(*mockCachedFile, getChar()).WillOnce(Return(42));

    int result = stream->getUnfilteredChar();

    EXPECT_EQ(result, 42);

}



TEST_F(CachedFileStreamTest_162, Rewind_ReturnsTrueOnSuccess_162) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(CachedFileStreamTest_162, Close_DoesNotThrow_162) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(CachedFileStreamTest_162, GetKind_ReturnsExpectedType_162) {

    StreamKind kind = stream->getKind();

    EXPECT_EQ(kind, strFile);

}



TEST_F(CachedFileStreamTest_162, GetChar_ReturnsValueFromBuffer_162) {

    EXPECT_CALL(*mockCachedFile, getChar()).WillOnce(Return(42));

    int result = stream->getChar();

    EXPECT_EQ(result, 42);

}



TEST_F(CachedFileStreamTest_162, LookChar_ReturnsValueWithoutAdvancing_162) {

    EXPECT_CALL(*mockCachedFile, lookChar()).WillOnce(Return(43));

    int result = stream->lookChar();

    EXPECT_EQ(result, 43);

}



TEST_F(CachedFileStreamTest_162, GetPos_ReturnsCurrentPosition_162) {

    Goffset position = 0;

    EXPECT_CALL(*mockCachedFile, getPos()).WillOnce(Return(position));

    Goffset result = stream->getPos();

    EXPECT_EQ(result, position);

}



TEST_F(CachedFileStreamTest_162, GetStart_ReturnsStartPosition_162) {

    Goffset start = 0;

    EXPECT_CALL(*mockCachedFile, getStart()).WillOnce(Return(start));

    Goffset result = stream->getStart();

    EXPECT_EQ(result, start);

}



TEST_F(CachedFileStreamTest_162, UnfilteredRewind_ReturnsTrueOnSuccess_162) {

    EXPECT_TRUE(stream->unfilteredRewind());

}
