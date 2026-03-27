#include <gtest/gtest.h>

#include "Stream.h"



class BaseMemStreamTest_166 : public ::testing::Test {

protected:

    std::unique_ptr<BaseMemStream<char>> stream;



    void SetUp() override {

        char buffer[1024] = {0};

        Object dict; // Assuming Object is a valid type in the context

        stream = std::make_unique<BaseMemStream<char>>(buffer, 0, sizeof(buffer), std::move(dict));

    }

};



TEST_F(BaseMemStreamTest_166, GetKind_ReturnsStrWeird_166) {

    EXPECT_EQ(stream->getKind(), strWeird);

}



TEST_F(BaseMemStreamTest_166, Rewind_ReturnsTrue_166) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(BaseMemStreamTest_166, Close_DoesNotThrow_166) {

    EXPECT_NO_THROW(stream->close());

}



TEST_F(BaseMemStreamTest_166, GetChar_ReturnsEOF_WhenEmpty_166) {

    EXPECT_EQ(stream->getChar(), EOF);

}



TEST_F(BaseMemStreamTest_166, LookChar_ReturnsEOF_WhenEmpty_166) {

    EXPECT_EQ(stream->lookChar(), EOF);

}



TEST_F(BaseMemStreamTest_166, GetPos_ReturnsZero_AfterInitialization_166) {

    EXPECT_EQ(stream->getPos(), 0);

}



TEST_F(BaseMemStreamTest_166, SetPos_DoesNotThrow_WhenValidPosition_166) {

    EXPECT_NO_THROW(stream->setPos(0));

}



TEST_F(BaseMemStreamTest_166, GetStart_ReturnsZero_AfterInitialization_166) {

    EXPECT_EQ(stream->getStart(), 0);

}



TEST_F(BaseMemStreamTest_166, MoveStart_DoesNotThrow_WhenValidDelta_166) {

    EXPECT_NO_THROW(stream->moveStart(0));

}



TEST_F(BaseMemStreamTest_166, GetUnfilteredChar_ReturnsEOF_WhenEmpty_166) {

    EXPECT_EQ(stream->getUnfilteredChar(), EOF);

}



TEST_F(BaseMemStreamTest_166, UnfilteredRewind_ReturnsTrue_166) {

    EXPECT_TRUE(stream->unfilteredRewind());

}
