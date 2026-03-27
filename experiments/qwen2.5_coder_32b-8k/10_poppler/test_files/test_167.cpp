#include <gtest/gtest.h>

#include "Stream.h"



class BaseMemStreamTest_167 : public ::testing::Test {

protected:

    static constexpr size_t bufferSize = 1024;

    unsigned char buffer[bufferSize];

    std::unique_ptr<BaseMemStream<unsigned char>> stream;



    void SetUp() override {

        Goffset startA = 0;

        Goffset lengthA = bufferSize;

        Object dictA; // Assuming Object is default constructible

        stream.reset(new BaseMemStream<unsigned char>(buffer, startA, lengthA, std::move(dictA)));

    }

};



TEST_F(BaseMemStreamTest_167, RewindReturnsTrue_167) {

    EXPECT_TRUE(stream->rewind());

}



TEST_F(BaseMemStreamTest_167, RewindResetsBufferPointer_167) {

    stream->getChar(); // Move buffer pointer

    stream->rewind();

    EXPECT_EQ(stream->lookChar(), buffer[0]);

}
