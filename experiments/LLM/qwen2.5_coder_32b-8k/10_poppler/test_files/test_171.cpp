#include <gtest/gtest.h>

#include "Stream.h"

#include <memory>



using namespace std;



class BaseMemStreamTest : public ::testing::Test {

protected:

    Object dict;

    Goffset start = 0;

    Goffset length = 1024;

    char buffer[1024];

    unique_ptr<BaseMemStream<char>> stream;



    void SetUp() override {

        stream = make_unique<BaseMemStream<char>>(buffer, start, length, move(dict));

    }

};



TEST_F(BaseMemStreamTest_171, SetPos_Start_171) {

    Goffset pos = 0;

    stream->setPos(pos);

    EXPECT_EQ(stream->getPos(), pos);

}



TEST_F(BaseMemStreamTest_171, SetPos_End_171) {

    Goffset pos = length - 1;

    stream->setPos(pos);

    EXPECT_EQ(stream->getPos(), pos);

}



TEST_F(BaseMemStreamTest_171, SetPos_OutOfBounds_Higher_171) {

    Goffset pos = length + 10;

    stream->setPos(pos);

    EXPECT_EQ(stream->getPos(), length);

}



TEST_F(BaseMemStreamTest_171, SetPos_OutOfBounds_Lower_171) {

    Goffset pos = -10;

    stream->setPos(pos);

    EXPECT_EQ(stream->getPos(), 0);

}



TEST_F(BaseMemStreamTest_171, SetPos_Dir_Positive_171) {

    Goffset pos = 512;

    int dir = 1;

    stream->setPos(pos, dir);

    EXPECT_EQ(stream->getPos(), pos);

}



TEST_F(BaseMemStreamTest_171, SetPos_Dir_Negative_171) {

    Goffset pos = 512;

    int dir = -1;

    stream->setPos(pos, dir);

    EXPECT_EQ(stream->getPos(), length - pos);

}



TEST_F(BaseMemStreamTest_171, SetPos_Dir_Zero_171) {

    Goffset pos = 512;

    int dir = 0;

    stream->setPos(pos, dir);

    EXPECT_EQ(stream->getPos(), pos);

}
