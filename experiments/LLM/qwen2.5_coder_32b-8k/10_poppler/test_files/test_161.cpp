#include <gtest/gtest.h>

#include "Stream.h"



class CachedFileStreamTest : public ::testing::Test {

protected:

    void SetUp() override {

        auto cachedFile = std::make_shared<CachedFile>();

        stream = std::make_unique<CachedFileStream>(cachedFile, 0, true, 1024, Object());

    }



    std::unique_ptr<CachedFileStream> stream;

};



TEST_F(CachedFileStreamTest_161, GetStart_ReturnsInitialPosition_161) {

    EXPECT_EQ(stream->getStart(), 0);

}



TEST_F(CachedFileStreamTest_161, Rewind_ReturnsTrueOnSuccess_161) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(CachedFileStreamTest_161, Close_DoesNotThrowException_161) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(CachedFileStreamTest_161, SetPos_DoesNotThrowException_161) {

    EXPECT_NO_THROW(stream->setPos(500, 0));

}



TEST_F(CachedFileStreamTest_161, MoveStart_PositiveDelta_ShiftsStartPosition_161) {

    Goffset initialStart = stream->getStart();

    stream->moveStart(100);

    EXPECT_EQ(stream->getStart(), initialStart + 100);

}



TEST_F(CachedFileStreamTest_161, MoveStart_NegativeDelta_ShiftsStartPosition_161) {

    Goffset initialStart = stream->getStart();

    stream->moveStart(-50);

    EXPECT_EQ(stream->getStart(), initialStart - 50);

}



TEST_F(CachedFileStreamTest_161, GetPos_ReturnsValidPosition_AfterSetPos_161) {

    stream->setPos(250, 0);

    EXPECT_EQ(stream->getPos(), 250);

}



TEST_F(CachedFileStreamTest_161, GetKind_ReturnsExpectedKind_161) {

    EXPECT_EQ(stream->getKind(), strFile);

}
