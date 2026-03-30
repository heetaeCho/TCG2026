#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseStreamTest_130 : public Test {

protected:

    std::unique_ptr<BaseStream> baseStream;



    void SetUp() override {

        Object dict; // Assuming Object has a default constructor

        Goffset length = 0;

        baseStream = std::make_unique<BaseStream>(std::move(dict), length);

    }

};



TEST_F(BaseStreamTest_130, GetFileName_ReturnsNullptr_130) {

    EXPECT_EQ(baseStream->getFileName(), nullptr);

}



TEST_F(BaseStreamTest_130, Copy_ReturnsNewInstance_130) {

    auto copy = baseStream->copy();

    EXPECT_NE(copy.get(), baseStream.get());

}



TEST_F(BaseStreamTest_130, MakeSubStream_ReturnsNewInstance_130) {

    Object dict; // Assuming Object has a default constructor

    Goffset start = 0;

    bool limited = false;

    Goffset length = 0;



    auto subStream = baseStream->makeSubStream(start, limited, length, std::move(dict));

    EXPECT_NE(subStream.get(), nullptr);

}



TEST_F(BaseStreamTest_130, SetPos_DoesNotThrow_130) {

    Goffset pos = 0;

    int dir = 0;



    EXPECT_NO_THROW(baseStream->setPos(pos, dir));

}



TEST_F(BaseStreamTest_130, GetStart_ReturnsZeroByDefault_130) {

    EXPECT_EQ(baseStream->getStart(), static_cast<Goffset>(0));

}



TEST_F(BaseStreamTest_130, MoveStart_DoesNotThrow_130) {

    Goffset delta = 0;



    EXPECT_NO_THROW(baseStream->moveStart(delta));

}



TEST_F(BaseStreamTest_130, IsBinary_ReturnsFalseByDefault_130) {

    EXPECT_FALSE(baseStream->isBinary());

}



TEST_F(BaseStreamTest_130, GetBaseStream_ReturnsSelf_130) {

    EXPECT_EQ(baseStream->getBaseStream(), baseStream.get());

}



TEST_F(BaseStreamTest_130, GetUndecodedStream_ReturnsSelf_130) {

    EXPECT_EQ(baseStream->getUndecodedStream(), baseStream.get());

}



TEST_F(BaseStreamTest_130, GetDict_ReturnsNonNullPointer_130) {

    EXPECT_NE(baseStream->getDict(), nullptr);

}



TEST_F(BaseStreamTest_130, GetDictObject_ReturnsNonNullPointer_130) {

    EXPECT_NE(baseStream->getDictObject(), nullptr);

}



TEST_F(BaseStreamTest_130, GetLength_ReturnsZeroByDefault_130) {

    EXPECT_EQ(baseStream->getLength(), static_cast<Goffset>(0));

}
