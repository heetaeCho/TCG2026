#include <gtest/gtest.h>

#include "Stream.h"

#include "Object.h"



class BaseStreamTest_128 : public ::testing::Test {

protected:

    Object dict;

    Goffset length = 1024;

    std::unique_ptr<BaseStream> baseStream;



    void SetUp() override {

        dict.dictAdd("key", Object("value"));

        baseStream = std::make_unique<BaseStream>(std::move(dict), length);

    }

};



TEST_F(BaseStreamTest_128, GetDict_ReturnsCorrectDict_128) {

    Dict* retrievedDict = baseStream->getDict();

    EXPECT_EQ(retrievedDict->dictLookupNF("key").getNameString(), "value");

}



TEST_F(BaseStreamTest_128, SetPos_DoesNotThrowException_128) {

    EXPECT_NO_THROW(baseStream->setPos(512, 0));

}



TEST_F(BaseStreamTest_128, GetStart_ReturnsZeroByDefault_128) {

    Goffset start = baseStream->getStart();

    EXPECT_EQ(start, 0);

}



TEST_F(BaseStreamTest_128, MoveStart_IncreasesStart_128) {

    baseStream->moveStart(512);

    Goffset start = baseStream->getStart();

    EXPECT_EQ(start, 512);

}



TEST_F(BaseStreamTest_128, IsBinary_ReturnsTrueByDefault_128) {

    bool isBinary = baseStream->isBinary();

    EXPECT_TRUE(isBinary);

}



TEST_F(BaseStreamTest_128, GetBaseStream_ReturnsSelf_128) {

    BaseStream* baseStreamPtr = baseStream->getBaseStream();

    EXPECT_EQ(baseStreamPtr, baseStream.get());

}



TEST_F(BaseStreamTest_128, GetUndecodedStream_ReturnsSelf_128) {

    Stream* undecodedStream = baseStream->getUndecodedStream();

    EXPECT_EQ(undecodedStream, baseStream.get());

}



TEST_F(BaseStreamTest_128, Copy_ReturnsNewInstance_128) {

    std::unique_ptr<BaseStream> copiedStream = baseStream->copy();

    EXPECT_NE(copiedStream.get(), baseStream.get());

    EXPECT_EQ(copiedStream->getDict()->dictLookupNF("key").getNameString(), "value");

}



TEST_F(BaseStreamTest_128, GetLength_ReturnsCorrectLength_128) {

    Goffset streamLength = baseStream->getLength();

    EXPECT_EQ(streamLength, length);

}
