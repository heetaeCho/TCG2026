#include <gtest/gtest.h>

#include "Stream.h"



using namespace std;



class CachedFileStreamTest : public ::testing::Test {

protected:

    std::shared_ptr<CachedFile> mockCachedFile;

    std::unique_ptr<CachedFileStream> stream;



    void SetUp() override {

        mockCachedFile = make_shared<CachedFile>();

        stream = make_unique<CachedFileStream>(mockCachedFile, 0, false, 1024, Object());

    }

};



TEST_F(CachedFileStreamTest_158, GetCharReturnsEOFWhenNoDataAvailable_158) {

    EXPECT_CALL(*mockCachedFile, someMethod()) // Placeholder for actual expected call

        .WillOnce(::testing::Return(false));   // Assuming fillBuf() returns false



    int result = stream->getChar();

    EXPECT_EQ(result, EOF);

}



TEST_F(CachedFileStreamTest_158, GetCharReturnsValidCharacterWhenDataAvailable_158) {

    int expectedChar = 0x42; // Example character

    mockCachedFile->setData(expectedChar); // Assuming a method to set data for testing



    int result = stream->getChar();

    EXPECT_EQ(result, expectedChar);

}



TEST_F(CachedFileStreamTest_158, GetCharAdvancesBufferPointerAfterRead_158) {

    int firstChar = 0x42;

    int secondChar = 0x43;

    mockCachedFile->setData(firstChar, secondChar); // Assuming a method to set multiple data for testing



    EXPECT_EQ(stream->getChar(), firstChar);

    EXPECT_EQ(stream->getChar(), secondChar);

}



TEST_F(CachedFileStreamTest_158, RewindResetsBufferPointer_158) {

    int firstChar = 0x42;

    mockCachedFile->setData(firstChar); // Assuming a method to set data for testing



    stream->getChar(); // Read one character

    EXPECT_TRUE(stream->rewind());



    EXPECT_EQ(stream->getChar(), firstChar);

}



TEST_F(CachedFileStreamTest_158, CloseDoesNotCrash_158) {

    EXPECT_NO_THROW(stream->close());

}

```


