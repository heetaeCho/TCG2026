#include <gtest/gtest.h>

#include "Stream.h"



class BaseSeekInputStreamTest : public ::testing::Test {

protected:

    Goffset start = 0;

    bool limited = false;

    Goffset length = 1024;

    Object dict;



    std::unique_ptr<BaseSeekInputStream> stream;



    void SetUp() override {

        stream.reset(new BaseSeekInputStream(start, limited, length, std::move(dict)));

    }

};



TEST_F(BaseSeekInputStreamTest_137, GetUnfilteredChar_ReturnsGetCharResult_137) {

    int expected = stream->getChar();

    int actual = stream->getUnfilteredChar();

    EXPECT_EQ(expected, actual);

}



TEST_F(BaseSeekInputStreamTest_137, Rewind_ResetsPositionToStart_137) {

    Goffset initialPos = stream->getPos();

    stream->setPos(100, 0); // Move position to 100

    EXPECT_NE(initialPos, stream->getPos());

    stream->rewind();

    EXPECT_EQ(initialPos, stream->getPos());

}



TEST_F(BaseSeekInputStreamTest_137, Close_DoesNotThrowException_137) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(BaseSeekInputStreamTest_137, SetPos_MovesPositionToGivenValue_137) {

    Goffset newPos = 500;

    stream->setPos(newPos, 0);

    EXPECT_EQ(newPos, stream->getPos());

}



TEST_F(BaseSeekInputStreamTest_137, GetStart_ReturnsInitialStartValue_137) {

    EXPECT_EQ(start, stream->getStart());

}



TEST_F(BaseSeekInputStreamTest_137, GetKind_ReturnsValidStreamKind_137) {

    StreamKind kind = stream->getKind();

    // Assuming StreamKind is an enum and has some valid values

    EXPECT_TRUE(kind >= 0 && kind < static_cast<StreamKind>(StreamKind::MAX_STREAM_KIND));

}



TEST_F(BaseSeekInputStreamTest_137, GetChar_ReturnsValidCharacter_137) {

    int character = stream->getChar();

    // Assuming getChar() returns a valid ASCII character

    EXPECT_TRUE(character >= 0 && character <= 255);

}



TEST_F(BaseSeekInputStreamTest_137, LookChar_ReturnsNextCharacterWithoutAdvancingPosition_137) {

    Goffset initialPos = stream->getPos();

    int expected = stream->getChar(); // Read the next char

    int actual = stream->lookChar();   // Peek the same character again

    EXPECT_EQ(expected, actual);

    EXPECT_EQ(initialPos, stream->getPos());

}



TEST_F(BaseSeekInputStreamTest_137, UnfilteredRewind_ResetsPositionToStart_137) {

    Goffset initialPos = stream->getPos();

    stream->setPos(100, 0); // Move position to 100

    EXPECT_NE(initialPos, stream->getPos());

    stream->unfilteredRewind();

    EXPECT_EQ(initialPos, stream->getPos());

}



TEST_F(BaseSeekInputStreamTest_137, BoundaryCondition_SetPos_OutOfBounds_137) {

    Goffset outOfBoundsPos = length + 100;

    stream->setPos(outOfBoundsPos, 0);

    // Assuming setPos with out-of-bounds position does not throw and sets to end

    EXPECT_EQ(length, stream->getPos());

}
