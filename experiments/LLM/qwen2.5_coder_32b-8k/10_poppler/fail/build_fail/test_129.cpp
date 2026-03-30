#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class BaseStreamTest_129 : public Test {

protected:

    Object dict;

    Goffset length = 1024;

    std::unique_ptr<BaseStream> baseStream;



    void SetUp() override {

        baseStream = std::make_unique<BaseStream>(std::move(dict), length);

    }

};



TEST_F(BaseStreamTest_129, GetDictObject_ReturnsNonNull_129) {

    EXPECT_NE(baseStream->getDictObject(), nullptr);

}



TEST_F(BaseStreamTest_129, Copy_ReturnsUniquePtrToBaseStream_129) {

    auto copiedStream = baseStream->copy();

    EXPECT_NE(copiedStream, nullptr);

}



TEST_F(BaseStreamTest_129, MakeSubStream_WithValidParameters_ReturnsUniquePtrToStream_129) {

    Goffset start = 0;

    bool limited = true;

    Goffset subLength = 512;

    Object subDict;



    auto subStream = baseStream->makeSubStream(start, limited, subLength, std::move(subDict));

    EXPECT_NE(subStream, nullptr);

}



TEST_F(BaseStreamTest_129, MakeSubStream_WithZeroLength_ReturnsUniquePtrToStream_129) {

    Goffset start = 0;

    bool limited = true;

    Goffset subLength = 0;

    Object subDict;



    auto subStream = baseStream->makeSubStream(start, limited, subLength, std::move(subDict));

    EXPECT_NE(subStream, nullptr);

}



TEST_F(BaseStreamTest_129, MakeSubStream_WithStartBeyondLength_ReturnsUniquePtrToStream_129) {

    Goffset start = length + 1;

    bool limited = true;

    Goffset subLength = 512;

    Object subDict;



    auto subStream = baseStream->makeSubStream(start, limited, subLength, std::move(subDict));

    EXPECT_NE(subStream, nullptr);

}



TEST_F(BaseStreamTest_129, GetStart_Default_ReturnsZero_129) {

    EXPECT_EQ(baseStream->getStart(), 0);

}



TEST_F(BaseStreamTest_129, MoveStart_IncreasesStart_129) {

    Goffset delta = 128;

    baseStream->moveStart(delta);

    EXPECT_EQ(baseStream->getStart(), delta);

}



TEST_F(BaseStreamTest_129, MoveStart_DecreasesStart_129) {

    Goffset initialDelta = 256;

    baseStream->moveStart(initialDelta);



    Goffset delta = -128;

    baseStream->moveStart(delta);

    EXPECT_EQ(baseStream->getStart(), initialDelta + delta);

}



TEST_F(BaseStreamTest_129, IsBinary_Default_ReturnsFalse_129) {

    EXPECT_FALSE(baseStream->isBinary());

}



TEST_F(BaseStreamTest_129, GetBaseStream_ReturnsSelf_129) {

    EXPECT_EQ(baseStream->getBaseStream(), baseStream.get());

}



TEST_F(BaseStreamTest_129, GetUndecodedStream_ReturnsSelf_129) {

    EXPECT_EQ(baseStream->getUndecodedStream(), baseStream.get());

}



TEST_F(BaseStreamTest_129, GetDict_ReturnsNonNull_129) {

    EXPECT_NE(baseStream->getDict(), nullptr);

}



TEST_F(BaseStreamTest_129, GetLength_ReturnsInitializedLength_129) {

    EXPECT_EQ(baseStream->getLength(), length);

}
