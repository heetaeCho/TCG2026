#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseStreamTest_127 : public Test {

protected:

    Object dict;

    Goffset length = 0;

    std::unique_ptr<BaseStream> baseStream;



    void SetUp() override {

        dict.initNull();

        baseStream.reset(new BaseStream(std::move(dict), length));

    }

};



TEST_F(BaseStreamTest_127, GetUndecodedStream_ReturnsSelf_127) {

    EXPECT_EQ(baseStream->getUndecodedStream(), baseStream.get());

}



TEST_F(BaseStreamTest_127, Copy_ReturnsNewInstance_127) {

    auto copy = baseStream->copy();

    EXPECT_NE(copy.get(), baseStream.get());

    EXPECT_EQ(copy->getLength(), baseStream->getLength());

}



TEST_F(BaseStreamTest_127, MakeSubStream_ReturnsValidStream_127) {

    Goffset start = 0;

    bool limited = true;

    Goffset subLength = 100;

    auto subStream = baseStream->makeSubStream(start, limited, subLength, Object());

    EXPECT_NE(subStream.get(), nullptr);

}



TEST_F(BaseStreamTest_127, SetPos_DoesNotThrow_127) {

    Goffset pos = 0;

    int dir = 1;

    EXPECT_NO_THROW(baseStream->setPos(pos, dir));

}



TEST_F(BaseStreamTest_127, GetStart_ReturnsZero_127) {

    EXPECT_EQ(baseStream->getStart(), 0);

}



TEST_F(BaseStreamTest_127, MoveStart_DoesNotThrow_127) {

    Goffset delta = 10;

    EXPECT_NO_THROW(baseStream->moveStart(delta));

}



TEST_F(BaseStreamTest_127, IsBinary_ReturnsFalseByDefault_127) {

    EXPECT_FALSE(baseStream->isBinary());

}



TEST_F(BaseStreamTest_127, GetBaseStream_ReturnsSelf_127) {

    EXPECT_EQ(baseStream->getBaseStream(), baseStream.get());

}



TEST_F(BaseStreamTest_127, GetDict_ReturnsNonNull_127) {

    EXPECT_NE(baseStream->getDict(), nullptr);

}



TEST_F(BaseStreamTest_127, GetDictObject_ReturnsNonNull_127) {

    EXPECT_NE(baseStream->getDictObject(), nullptr);

}



TEST_F(BaseStreamTest_127, GetFileName_ReturnsNullByDefault_127) {

    EXPECT_EQ(baseStream->getFileName(), nullptr);

}



TEST_F(BaseStreamTest_127, GetLength_ReturnsZero_127) {

    EXPECT_EQ(baseStream->getLength(), 0);

}
