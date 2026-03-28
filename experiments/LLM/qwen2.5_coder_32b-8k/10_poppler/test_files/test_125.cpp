#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseStreamTest_125 : public ::testing::Test {

protected:

    Object dict;

    Goffset length = 0;

    std::unique_ptr<BaseStream> baseStream;



    void SetUp() override {

        baseStream = std::make_unique<BaseStream>(std::move(dict), length);

    }

};



TEST_F(BaseStreamTest_125, IsBinary_ReturnsTrueWhenLastIsTrue_125) {

    EXPECT_TRUE(baseStream->isBinary(true));

}



TEST_F(BaseStreamTest_125, IsBinary_ReturnsFalseWhenLastIsFalse_125) {

    EXPECT_FALSE(baseStream->isBinary(false));

}



TEST_F(BaseStreamTest_125, Copy_ReturnsNewInstance_125) {

    auto copy = baseStream->copy();

    EXPECT_NE(copy.get(), baseStream.get());

}



TEST_F(BaseStreamTest_125, GetStart_DefaultValueIsZero_125) {

    EXPECT_EQ(baseStream->getStart(), 0);

}



TEST_F(BaseStreamTest_125, MoveStart_IncrementsStartPosition_125) {

    Goffset delta = 10;

    baseStream->moveStart(delta);

    EXPECT_EQ(baseStream->getStart(), delta);

}



TEST_F(BaseStreamTest_125, GetLength_ReturnsInitialLength_125) {

    EXPECT_EQ(baseStream->getLength(), length);

}



// Assuming getBaseStream and getUndecodedStream are non-virtual and return this

// If they are not, additional setup will be needed for mocking or further testing

TEST_F(BaseStreamTest_125, GetBaseStream_ReturnsSelf_125) {

    EXPECT_EQ(baseStream->getBaseStream(), baseStream.get());

}



TEST_F(BaseStreamTest_125, GetUndecodedStream_ReturnsSelf_125) {

    EXPECT_EQ(baseStream->getUndecodedStream(), baseStream.get());

}



// Assuming getDict and getDictObject are non-virtual and return a valid pointer

// If they are not, additional setup will be needed for mocking or further testing

TEST_F(BaseStreamTest_125, GetDict_ReturnsNonEmptyPointer_125) {

    EXPECT_NE(baseStream->getDict(), nullptr);

}



TEST_F(BaseStreamTest_125, GetDictObject_ReturnsNonEmptyPointer_125) {

    EXPECT_NE(baseStream->getDictObject(), nullptr);

}

```


