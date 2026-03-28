#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <memory>



using namespace testing;



class BaseStreamTest_126 : public Test {

protected:

    std::unique_ptr<BaseStream> baseStream;



    void SetUp() override {

        Object dictA;

        Goffset lengthA = 100;

        baseStream = std::make_unique<BaseStream>(std::move(dictA), lengthA);

    }

};



TEST_F(BaseStreamTest_126, GetBaseStreamReturnsThis_126) {

    EXPECT_EQ(baseStream->getBaseStream(), baseStream.get());

}



TEST_F(BaseStreamTest_126, CopyCreatesNewInstance_126) {

    auto copy = baseStream->copy();

    EXPECT_NE(copy.get(), baseStream.get());

}



TEST_F(BaseStreamTest_126, MakeSubStreamReturnsValidPointer_126) {

    Object dictA;

    Goffset start = 0;

    bool limited = true;

    Goffset length = 50;

    auto subStream = baseStream->makeSubStream(start, limited, length, std::move(dictA));

    EXPECT_NE(subStream.get(), nullptr);

}



TEST_F(BaseStreamTest_126, SetPosDoesNotThrowOnValidPosition_126) {

    EXPECT_NO_THROW(baseStream->setPos(50, 1));

}



TEST_F(BaseStreamTest_126, GetStartReturnsZeroInitially_126) {

    EXPECT_EQ(baseStream->getStart(), 0);

}



TEST_F(BaseStreamTest_126, MoveStartUpdatesStartPosition_126) {

    baseStream->moveStart(50);

    EXPECT_EQ(baseStream->getStart(), 50);

}



TEST_F(BaseStreamTest_126, IsBinaryReturnsFalseByDefault_126) {

    EXPECT_FALSE(baseStream->isBinary());

}



TEST_F(BaseStreamTest_126, GetUndecodedStreamReturnsThis_126) {

    EXPECT_EQ(baseStream->getUndecodedStream(), baseStream.get());

}



TEST_F(BaseStreamTest_126, GetDictObjectReturnsValidPointer_126) {

    EXPECT_NE(baseStream->getDictObject(), nullptr);

}



TEST_F(BaseStreamTest_126, GetLengthReturnsProvidedLength_126) {

    EXPECT_EQ(baseStream->getLength(), 100);

}
