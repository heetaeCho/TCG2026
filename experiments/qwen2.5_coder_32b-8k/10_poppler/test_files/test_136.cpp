#include <gtest/gtest.h>

#include "Stream.h"



class BaseSeekInputStreamTest : public ::testing::Test {

protected:

    BaseSeekInputStream* stream;



    void SetUp() override {

        stream = new BaseSeekInputStream(0, false, 1024, Object());

    }



    void TearDown() override {

        delete stream;

    }

};



TEST_F(BaseSeekInputStreamTest_136, GetStartReturnsInitialValue_136) {

    EXPECT_EQ(stream->getStart(), 0);

}



TEST_F(BaseSeekInputStreamTest_136, RewindDoesNotChangeStart_136) {

    Goffset initialStart = stream->getStart();

    stream->rewind();

    EXPECT_EQ(stream->getStart(), initialStart);

}



TEST_F(BaseSeekInputStreamTest_136, CloseDoesNotChangeStart_136) {

    Goffset initialStart = stream->getStart();

    stream->close();

    EXPECT_EQ(stream->getStart(), initialStart);

}



TEST_F(BaseSeekInputStreamTest_136, MoveStartUpdatesStart_136) {

    stream->moveStart(10);

    EXPECT_EQ(stream->getStart(), 10);



    stream->moveStart(-5);

    EXPECT_EQ(stream->getStart(), 5);

}
