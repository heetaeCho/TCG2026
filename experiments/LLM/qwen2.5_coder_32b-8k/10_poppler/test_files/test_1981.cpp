#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CachedFile.h"



using ::testing::Return;

using ::testing::_;



class MockCachedFile : public CachedFile {

public:

    MOCK_METHOD(size_t, writeData, (const char *ptr, size_t size), (override));

};



class MockChunksVector : public std::vector<int> {

public:

    using std::vector<int>::vector;

};



class MockChunksArray {

public:

    int data[10];

};



class CachedFileWriterTest_1981 : public ::testing::Test {

protected:

    void SetUp() override {

        mockCachedFile = new MockCachedFile();

        chunksVector = new MockChunksVector();

        chunksArray = new MockChunksArray();



        writerFromVector = new CachedFileWriter(mockCachedFile, chunksVector);

        writerFromArray = new CachedFileWriter(mockCachedFile, chunksArray->data);

    }



    void TearDown() override {

        delete writerFromVector;

        delete writerFromArray;

        delete mockCachedFile;

        delete chunksVector;

        delete chunksArray;

    }



    MockCachedFile *mockCachedFile;

    MockChunksVector *chunksVector;

    MockChunksArray *chunksArray;

    CachedFileWriter *writerFromVector;

    CachedFileWriter *writerFromArray;

};



TEST_F(CachedFileWriterTest_1981, WriteDelegatesToCachedFile_NormalOperation_1981) {

    const char* data = "Hello";

    size_t dataSize = 5;



    EXPECT_CALL(*mockCachedFile, writeData(data, dataSize)).WillOnce(Return(dataSize));



    size_t result = writerFromVector->write(data, dataSize);

    EXPECT_EQ(result, dataSize);

}



TEST_F(CachedFileWriterTest_1981, WriteDelegatesToCachedFile_ZeroSize_1981) {

    const char* data = "Hello";

    size_t dataSize = 0;



    EXPECT_CALL(*mockCachedFile, writeData(data, dataSize)).WillOnce(Return(0));



    size_t result = writerFromVector->write(data, dataSize);

    EXPECT_EQ(result, 0);

}



TEST_F(CachedFileWriterTest_1981, WriteDelegatesToCachedFile_LargeSize_1981) {

    const char* data = "A very large string that might test boundary conditions in the underlying implementation";

    size_t dataSize = strlen(data);



    EXPECT_CALL(*mockCachedFile, writeData(data, dataSize)).WillOnce(Return(dataSize));



    size_t result = writerFromVector->write(data, dataSize);

    EXPECT_EQ(result, dataSize);

}



TEST_F(CachedFileWriterTest_1981, WriteDelegatesToCachedFile_ErrorHandling_1981) {

    const char* data = "Error";

    size_t dataSize = 5;



    EXPECT_CALL(*mockCachedFile, writeData(data, dataSize)).WillOnce(Return(0));



    size_t result = writerFromVector->write(data, dataSize);

    EXPECT_EQ(result, 0);

}
