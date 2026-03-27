#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Stream.h"

#include "TestProjects/poppler/poppler/Object.h"



class BaseMemStreamTest : public ::testing::Test {

protected:

    Goffset start = 0;

    Goffset length = 1024;

    Object dict;

    std::unique_ptr<unsigned char[]> buf;



    void SetUp() override {

        buf = std::make_unique<unsigned char[]>(length);

        for (Goffset i = 0; i < length; ++i) {

            buf[i] = static_cast<unsigned char>(i % 256);

        }

    }



    std::unique_ptr<BaseMemStream<unsigned char>> createBaseMemStream(Goffset startA, Goffset lengthA, Object &&dictA) {

        return std::make_unique<BaseMemStream<unsigned char>>(buf.get(), startA, lengthA, std::move(dictA));

    }

};



TEST_F(BaseMemStreamTest_165, MakeSubStream_UnlimitedLength_165) {

    auto stream = createBaseMemStream(start, length, Object());

    auto subStream = stream->makeSubStream(0, false, 2048, Object());



    EXPECT_EQ(subStream->getStart(), start);

    EXPECT_EQ(subStream->getLength(), length);

}



TEST_F(BaseMemStreamTest_165, MakeSubStream_LimitedWithinBounds_165) {

    auto stream = createBaseMemStream(start, length, Object());

    auto subStream = stream->makeSubStream(256, true, 512, Object());



    EXPECT_EQ(subStream->getStart(), start + 256);

    EXPECT_EQ(subStream->getLength(), 512);

}



TEST_F(BaseMemStreamTest_165, MakeSubStream_LimitedOutsideBounds_165) {

    auto stream = createBaseMemStream(start, length, Object());

    auto subStream = stream->makeSubStream(512, true, 1024, Object());



    EXPECT_EQ(subStream->getStart(), start + 512);

    EXPECT_EQ(subStream->getLength(), length - 512);

}



TEST_F(BaseMemStreamTest_165, MakeSubStream_ZeroLength_165) {

    auto stream = createBaseMemStream(start, length, Object());

    auto subStream = stream->makeSubStream(0, true, 0, Object());



    EXPECT_EQ(subStream->getStart(), start);

    EXPECT_EQ(subStream->getLength(), 0);

}



TEST_F(BaseMemStreamTest_165, MakeSubStream_OutOfBoundsStart_165) {

    auto stream = createBaseMemStream(start, length, Object());

    auto subStream = stream->makeSubStream(length + 1, false, 2048, Object());



    EXPECT_EQ(subStream->getStart(), start);

    EXPECT_EQ(subStream->getLength(), 0);

}
