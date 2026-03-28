#include <gtest/gtest.h>

#include "Stream.h"



using namespace poppler;



class BaseMemStreamTest : public ::testing::Test {

protected:

    T buffer[1024];

    Goffset start = 0;

    Goffset length = sizeof(buffer);

    Object dict;



    void SetUp() override {

        dict.dictAdd("key", Object(1));

    }



    std::unique_ptr<BaseMemStream<T>> createBaseMemStream(Goffset startA, Goffset lengthA) {

        return std::make_unique<BaseMemStream<T>>(buffer, startA, lengthA, std::move(dict));

    }

};



TEST_F(BaseMemStreamTest_2754, ConstructorInitializesMembersCorrectly_2754) {

    auto stream = createBaseMemStream(start, length);

    EXPECT_EQ(stream->getLength(), length);

}



TEST_F(BaseMemStreamTest_2754, SetPosMovesPointerCorrectlyForward_2754) {

    auto stream = createBaseMemStream(start, length);

    Goffset newPos = 10;

    stream->setPos(newPos, 1);

    EXPECT_EQ(stream->getPos(), newPos);

}



TEST_F(BaseMemStreamTest_2754, SetPosMovesPointerCorrectlyBackward_2754) {

    auto stream = createBaseMemStream(start + 10, length - 10);

    Goffset newPos = start;

    stream->setPos(newPos, -1);

    EXPECT_EQ(stream->getPos(), newPos);

}



TEST_F(BaseMemStreamTest_2754, GetStartReturnsCorrectValue_2754) {

    auto stream = createBaseMemStream(start, length);

    EXPECT_EQ(stream->getStart(), start);

}



TEST_F(BaseMemStreamTest_2754, MoveStartAdjustsStartPosition_2754) {

    auto stream = createBaseMemStream(start, length);

    Goffset delta = 10;

    stream->moveStart(delta);

    EXPECT_EQ(stream->getStart(), start + delta);

}



TEST_F(BaseMemStreamTest_2754, RewindResetsPositionToStart_2754) {

    auto stream = createBaseMemStream(start + 10, length - 10);

    stream->rewind();

    EXPECT_EQ(stream->getPos(), start);

}



TEST_F(BaseMemStreamTest_2754, CloseDoesNotThrowForValidState_2754) {

    auto stream = createBaseMemStream(start, length);

    EXPECT_NO_THROW(stream->close());

}



TEST_F(BaseMemStreamTest_2754, GetCharReturnsNextCharacter_2754) {

    buffer[0] = 'A';

    auto stream = createBaseMemStream(start, length);

    int character = stream->getChar();

    EXPECT_EQ(character, 'A');

}



TEST_F(BaseMemStreamTest_2754, LookCharPeeksNextCharacterWithoutAdvancing_2754) {

    buffer[0] = 'A';

    auto stream = createBaseMemStream(start, length);

    int character = stream->lookChar();

    EXPECT_EQ(character, 'A');

    EXPECT_EQ(stream->getPos(), start); // Position should not change

}



TEST_F(BaseMemStreamTest_2754, GetPosReturnsCurrentPosition_2754) {

    auto stream = createBaseMemStream(start, length);

    EXPECT_EQ(stream->getPos(), start);

}



TEST_F(BaseMemStreamTest_2754, UnfilteredRewindResetsPositionToStart_2754) {

    auto stream = createBaseMemStream(start + 10, length - 10);

    stream->unfilteredRewind();

    EXPECT_EQ(stream->getPos(), start);

}
