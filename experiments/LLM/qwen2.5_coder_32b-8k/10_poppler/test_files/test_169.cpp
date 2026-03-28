#include <gtest/gtest.h>

#include "Stream.h"



class BaseMemStreamTest_169 : public ::testing::Test {

protected:

    unsigned char buffer[4] = {0x1A, 0x2B, 0x3C, 0x4D};

    std::unique_ptr<BaseMemStream<unsigned char>> stream;



    void SetUp() override {

        Object dict;

        stream.reset(new BaseMemStream<unsigned char>(buffer, 0, sizeof(buffer), std::move(dict)));

    }

};



TEST_F(BaseMemStreamTest_169, LookChar_ReturnsFirstCharacter_169) {

    EXPECT_EQ(stream->lookChar(), 0x1A);

}



TEST_F(BaseMemStreamTest_169, LookChar_DoesNotAdvancePointer_169) {

    stream->lookChar();

    EXPECT_EQ(stream->getPos(), 0);

}



TEST_F(BaseMemStreamTest_169, LookChar_ReturnsEOFAtEnd_169) {

    for (int i = 0; i < sizeof(buffer); ++i) {

        stream->getChar();

    }

    EXPECT_EQ(stream->lookChar(), EOF);

}



TEST_F(BaseMemStreamTest_169, Rewind_ResetsPosition_169) {

    stream->getChar();

    EXPECT_EQ(stream->getPos(), 1);

    stream->rewind();

    EXPECT_EQ(stream->getPos(), 0);

}



TEST_F(BaseMemStreamTest_169, GetChar_ReturnsCharactersInOrder_169) {

    for (int i = 0; i < sizeof(buffer); ++i) {

        EXPECT_EQ(stream->getChar(), buffer[i]);

    }

}



TEST_F(BaseMemStreamTest_169, GetChar_ReturnsEOFAfterEnd_169) {

    for (int i = 0; i <= sizeof(buffer); ++i) {

        stream->getChar();

    }

    EXPECT_EQ(stream->getChar(), EOF);

}
