#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class BaseMemStreamTest : public ::testing::Test {

protected:

    static constexpr Goffset bufferLength = 10;

    unsigned char buffer[bufferLength] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BaseMemStream<unsigned char> stream;



    BaseMemStreamTest() : stream(buffer, 0, bufferLength, Object()) {}

};



TEST_F(BaseMemStreamTest_168, GetCharReadsCharactersInOrder_168) {

    for (unsigned char i = 0; i < bufferLength; ++i) {

        EXPECT_EQ(stream.getChar(), i);

    }

}



TEST_F(BaseMemStreamTest_168, GetCharReturnsEOFAfterBufferEnd_168) {

    for (unsigned char i = 0; i <= bufferLength; ++i) {

        stream.getChar();

    }

    EXPECT_EQ(stream.getChar(), EOF);

}



TEST_F(BaseMemStreamTest_168, RewindResetsPosition_168) {

    for (int i = 0; i < 5; ++i) {

        stream.getChar();

    }

    stream.rewind();

    EXPECT_EQ(stream.getChar(), 0);

}



TEST_F(BaseMemStreamTest_168, GetPosTracksPositionCorrectly_168) {

    for (unsigned char i = 0; i < bufferLength; ++i) {

        EXPECT_EQ(stream.getPos(), static_cast<Goffset>(i));

        stream.getChar();

    }

}



TEST_F(BaseMemStreamTest_168, SetPosMovesToSpecifiedPosition_168) {

    stream.setPos(5);

    EXPECT_EQ(stream.getChar(), 5);

}



TEST_F(BaseMemStreamTest_168, MoveStartAdjustsBufferStart_168) {

    stream.moveStart(3);

    EXPECT_EQ(stream.getChar(), 3);

}



TEST_F(BaseMemStreamTest_168, GetUnfilteredCharReadsCharactersInOrder_168) {

    for (unsigned char i = 0; i < bufferLength; ++i) {

        EXPECT_EQ(stream.getUnfilteredChar(), i);

    }

}



TEST_F(BaseMemStreamTest_168, UnfilteredRewindResetsPosition_168) {

    for (int i = 0; i < 5; ++i) {

        stream.getUnfilteredChar();

    }

    stream.unfilteredRewind();

    EXPECT_EQ(stream.getUnfilteredChar(), 0);

}
