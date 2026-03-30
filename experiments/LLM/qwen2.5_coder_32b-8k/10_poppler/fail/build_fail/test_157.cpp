#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class CachedFileStreamTest_157 : public Test {

protected:

    std::shared_ptr<CachedFile> mockCachedFile = std::make_shared<CachedFile>();

    Goffset startA = 0;

    bool limitedA = false;

    Goffset lengthA = 1024;

    Object dictA;



    std::unique_ptr<CachedFileStream> stream;



    void SetUp() override {

        stream = std::make_unique<CachedFileStream>(mockCachedFile, startA, limitedA, lengthA, std::move(dictA));

    }

};



TEST_F(CachedFileStreamTest_157, GetKind_ReturnsCorrectStreamKind_157) {

    EXPECT_EQ(stream->getKind(), strCachedFile);

}



TEST_F(CachedFileStreamTest_157, Rewind_ReturnsTrueOnNormalOperation_157) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(CachedFileStreamTest_157, Close_DoesNotThrowException_157) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(CachedFileStreamTest_157, SetPos_DoesNotThrowExceptionWithValidPosition_157) {

    Goffset position = 512;

    int direction = 0;

    EXPECT_NO_THROW(stream->setPos(position, direction));

}



TEST_F(CachedFileStreamTest_157, MoveStart_DoesNotThrowExceptionWithPositiveDelta_157) {

    Goffset delta = 256;

    EXPECT_NO_THROW(stream->moveStart(delta));

}



TEST_F(CachedFileStreamTest_157, MoveStart_DoesNotThrowExceptionWithNegativeDelta_157) {

    Goffset delta = -256;

    EXPECT_NO_THROW(stream->moveStart(delta));

}



TEST_F(CachedFileStreamTest_157, GetChar_ReturnsNonNegativeValueOnNormalOperation_157) {

    int result = stream->getChar();

    EXPECT_GE(result, 0);

}



TEST_F(CachedFileStreamTest_157, LookChar_ReturnsNonNegativeValueOnNormalOperation_157) {

    int result = stream->lookChar();

    EXPECT_GE(result, 0);

}



TEST_F(CachedFileStreamTest_157, GetPos_ReturnsValidPositionOnNormalOperation_157) {

    Goffset position = stream->getPos();

    EXPECT_LE(position, lengthA);

}



TEST_F(CachedFileStreamTest_157, GetStart_ReturnsInitialStartPosition_157) {

    EXPECT_EQ(stream->getStart(), startA);

}



TEST_F(CachedFileStreamTest_157, GetUnfilteredChar_ReturnsNonNegativeValueOnNormalOperation_157) {

    int result = stream->getUnfilteredChar();

    EXPECT_GE(result, 0);

}



TEST_F(CachedFileStreamTest_157, UnfilteredRewind_ReturnsTrueOnNormalOperation_157) {

    EXPECT_TRUE(stream->unfilteredRewind());

}
