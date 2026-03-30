#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using ::testing::Eq;

using ::testing::_;



class CachedFileStreamTest : public ::testing::Test {

protected:

    std::shared_ptr<CachedFile> mockCachedFile = std::make_shared<CachedFile>();

    Goffset start = 0;

    bool limited = false;

    Goffset length = 1024;

    Object dict;

    

    std::unique_ptr<CachedFileStream> cachedFileStream;



    void SetUp() override {

        cachedFileStream = std::make_unique<CachedFileStream>(mockCachedFile, start, limited, length, std::move(dict));

    }

};



TEST_F(CachedFileStreamTest_159, LookCharReturnsEOFWhenBufferEmptyAndFillBufFails_159) {

    EXPECT_CALL(*cachedFileStream, fillBuf()).WillOnce(testing::Return(false));

    

    int result = cachedFileStream->lookChar();

    

    EXPECT_EQ(result, EOF);

}



TEST_F(CachedFileStreamTest_159, LookCharReturnsCurrentBufferByteWhenFillBufSucceeds_159) {

    unsigned char mockByte = 42;

    auto* bufPtr = &mockByte;

    cachedFileStream->bufPtr = bufPtr;

    EXPECT_CALL(*cachedFileStream, fillBuf()).WillOnce(testing::Return(true));

    

    int result = cachedFileStream->lookChar();

    

    EXPECT_EQ(result, static_cast<int>(mockByte) & 0xff);

}



TEST_F(CachedFileStreamTest_159, LookCharReturnsCurrentBufferByteWhenBufferNotEmpty_159) {

    unsigned char mockByte = 42;

    auto* bufPtr = &mockByte;

    cachedFileStream->bufPtr = bufPtr;

    

    int result = cachedFileStream->lookChar();

    

    EXPECT_EQ(result, static_cast<int>(mockByte) & 0xff);

}



TEST_F(CachedFileStreamTest_159, LookCharCallsFillBufWhenBufferIsEmpty_159) {

    EXPECT_CALL(*cachedFileStream, fillBuf()).WillOnce(testing::Return(false));

    

    cachedFileStream->lookChar();

}



TEST_F(CachedFileStreamTest_159, LookCharDoesNotModifyPositionOrStateWhenEOFIsReturned_159) {

    Goffset initialPos = cachedFileStream->getPos();

    EXPECT_CALL(*cachedFileStream, fillBuf()).WillOnce(testing::Return(false));

    

    int result = cachedFileStream->lookChar();

    

    EXPECT_EQ(result, EOF);

    EXPECT_EQ(cachedFileStream->getPos(), initialPos);

}
