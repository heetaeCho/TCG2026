#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseMemStreamTest : public Test {

protected:

    static constexpr Goffset initialStart = 0;

    static constexpr Goffset initialLength = 1024;

    static constexpr Goffset initialBufSize = 16384;

    char buffer[initialBufSize];

    Object dummyDict;



    BaseMemStream<char> stream{buffer, initialStart, initialLength, std::move(dummyDict)};



    void SetUp() override {

        // Reset the buffer pointer to initial state after each test

        stream.moveStart(0);

    }

};



TEST_F(BaseMemStreamTest_173, MoveStartReducesLengthNormally_173) {

    Goffset delta = 10;

    stream.moveStart(delta);

    EXPECT_EQ(stream.getLength(), initialLength - delta);

}



TEST_F(BaseMemStreamTest_173, MoveStartUpdatesStartCorrectly_173) {

    Goffset delta = 20;

    stream.moveStart(delta);

    EXPECT_EQ(stream.getStart(), initialStart + delta);

}



TEST_F(BaseMemStreamTest_173, MoveStartWithZeroDeltaDoesNothing_173) {

    Goffset delta = 0;

    stream.moveStart(delta);

    EXPECT_EQ(stream.getLength(), initialLength);

    EXPECT_EQ(stream.getStart(), initialStart);

}



TEST_F(BaseMemStreamTest_173, MoveStartToFullLengthReducesLengthToZero_173) {

    Goffset delta = initialLength;

    stream.moveStart(delta);

    EXPECT_EQ(stream.getLength(), 0);

}



TEST_F(BaseMemStreamTest_173, MoveStartBeyondLengthDoesNotGoNegative_173) {

    Goffset delta = initialLength + 10;

    stream.moveStart(delta);

    EXPECT_EQ(stream.getLength(), 0);

}
