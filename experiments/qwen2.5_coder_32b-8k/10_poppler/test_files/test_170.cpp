#include <gtest/gtest.h>

#include "Stream.h"



class BaseMemStreamTest_170 : public ::testing::Test {

protected:

    char buffer[32768];

    BaseMemStream<char> stream;



    BaseMemStreamTest_170() 

        : stream(buffer, 0, sizeof(buffer), Object()) {}

};



TEST_F(BaseMemStreamTest_170, InitialPositionIsZero_170) {

    EXPECT_EQ(stream.getPos(), 0);

}



TEST_F(BaseMemStreamTest_170, SetPositionAndGetPositionConsistent_170) {

    stream.setPos(5000);

    EXPECT_EQ(stream.getPos(), 5000);



    stream.setPos(16384);

    EXPECT_EQ(stream.getPos(), 16384);

}



TEST_F(BaseMemStreamTest_170, RewindResetsPositionToStart_170) {

    stream.setPos(5000);

    stream.rewind();

    EXPECT_EQ(stream.getPos(), 0);

}



TEST_F(BaseMemStreamTest_170, SetPositionBeyondBufferEndDoesNotChangePosition_170) {

    Goffset initialPosition = stream.getPos();

    stream.setPos(sizeof(buffer) + 100);

    EXPECT_EQ(stream.getPos(), initialPosition);

}



TEST_F(BaseMemStreamTest_170, GetCharAtInitialPositionReturnsEOF_170) {

    int result = stream.getChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(BaseMemStreamTest_170, LookCharAtInitialPositionReturnsEOF_170) {

    int result = stream.lookChar();

    EXPECT_EQ(result, EOF);

}
