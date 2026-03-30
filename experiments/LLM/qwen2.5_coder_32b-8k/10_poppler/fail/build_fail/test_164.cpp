#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseMemStreamTest : public Test {

protected:

    Goffset start = 0;

    Goffset length = 1024;

    unsigned char buffer[1024] = {0};

    Object dict;

    std::unique_ptr<BaseMemStream<unsigned char>> stream;



    void SetUp() override {

        stream = std::make_unique<BaseMemStream<unsigned char>>(buffer, start, length, std::move(dict));

    }

};



TEST_F(BaseMemStreamTest_164, CopyCreatesNewInstance_164) {

    auto copy = stream->copy();

    EXPECT_NE(copy.get(), stream.get());

    EXPECT_EQ(copy->getLength(), stream->getLength());

}



TEST_F(BaseMemStreamTest_164, GetLengthReturnsCorrectValue_164) {

    EXPECT_EQ(stream->getLength(), length);

}



TEST_F(BaseMemStreamTest_164, SetPosDoesNotThrowForValidPosition_164) {

    EXPECT_NO_THROW(stream->setPos(512, 0));

}



TEST_F(BaseMemStreamTest_164, SetPosThrowsForNegativePosition_164) {

    EXPECT_THROW(stream->setPos(-1, 0), std::runtime_error);

}



TEST_F(BaseMemStreamTest_164, GetStartReturnsInitialValue_164) {

    EXPECT_EQ(stream->getStart(), start);

}



TEST_F(BaseMemStreamTest_164, MoveStartUpdatesStartPosition_164) {

    stream->moveStart(256);

    EXPECT_EQ(stream->getStart(), 256);

}



TEST_F(BaseMemStreamTest_164, RewindResetsPositionToStart_164) {

    stream->setPos(512, 0);

    stream->rewind();

    EXPECT_EQ(stream->getPos(), start);

}



TEST_F(BaseMemStreamTest_164, CloseDoesNotThrow_164) {

    EXPECT_NO_THROW(stream->close());

}
