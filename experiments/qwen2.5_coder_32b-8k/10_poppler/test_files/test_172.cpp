#include <gtest/gtest.h>

#include "Stream.h"



class BaseMemStreamTest_172 : public ::testing::Test {

protected:

    char buffer[16384];

    Object dict;

    std::unique_ptr<BaseMemStream<char>> stream;



    void SetUp() override {

        stream = std::make_unique<BaseMemStream<char>>(buffer, 0, sizeof(buffer), std::move(dict));

    }

};



TEST_F(BaseMemStreamTest_172, GetStartReturnsInitialValue_172) {

    EXPECT_EQ(stream->getStart(), 0);

}



TEST_F(BaseMemStreamTest_172, MoveStartUpdatesStartPosition_172) {

    stream->moveStart(100);

    EXPECT_EQ(stream->getStart(), 100);

}



TEST_F(BaseMemStreamTest_172, RewindReturnsTrue_172) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(BaseMemStreamTest_172, CloseDoesNotThrowException_172) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(BaseMemStreamTest_172, GetCharReturnsEOFWhenEmpty_172) {

    stream = std::make_unique<BaseMemStream<char>>(buffer, 0, 0, std::move(dict));

    EXPECT_EQ(stream->getChar(), EOF);

}



TEST_F(BaseMemStreamTest_172, LookCharReturnsEOFWhenEmpty_172) {

    stream = std::make_unique<BaseMemStream<char>>(buffer, 0, 0, std::move(dict));

    EXPECT_EQ(stream->lookChar(), EOF);

}



TEST_F(BaseMemStreamTest_172, GetPosReturnsInitialPosition_172) {

    EXPECT_EQ(stream->getPos(), 0);

}



TEST_F(BaseMemStreamTest_172, SetPosDoesNotThrowException_172) {

    EXPECT_NO_THROW(stream->setPos(10));

}



TEST_F(BaseMemStreamTest_172, GetUnfilteredCharReturnsEOFWhenEmpty_172) {

    stream = std::make_unique<BaseMemStream<char>>(buffer, 0, 0, std::move(dict));

    EXPECT_EQ(stream->getUnfilteredChar(), EOF);

}



TEST_F(BaseMemStreamTest_172, UnfilteredRewindReturnsTrue_172) {

    EXPECT_TRUE(stream->unfilteredRewind());

}
