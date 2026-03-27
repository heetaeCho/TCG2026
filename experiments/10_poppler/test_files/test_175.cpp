#include <gtest/gtest.h>

#include "Stream.h"



class BaseMemStreamTest : public ::testing::Test {

protected:

    unsigned char buffer[16384];

    Object dummyDict;

    std::unique_ptr<BaseMemStream<unsigned char>> stream;



    void SetUp() override {

        stream = std::make_unique<BaseMemStream<unsigned char>>(buffer, 0, sizeof(buffer), std::move(dummyDict));

    }

};



TEST_F(BaseMemStreamTest_175, RewindReturnsTrue_175) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(BaseMemStreamTest_175, UnfilteredRewindCallsRewind_175) {

    EXPECT_TRUE(stream->unfilteredRewind());

}



TEST_F(BaseMemStreamTest_175, RewindTwiceIsIdempotent_175) {

    stream->rewind();

    EXPECT_TRUE(stream->rewind());

}
