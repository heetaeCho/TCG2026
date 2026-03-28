#include <gtest/gtest.h>
#include "InMemoryFile.h"
#include <cstdio>
#include <cstring>
#include <vector>

class InMemoryFileTest_2636 : public ::testing::Test {
protected:
    InMemoryFile file;
};

// Test that a newly constructed InMemoryFile has an empty buffer
TEST_F(InMemoryFileTest_2636, InitialBufferIsEmpty_2636) {
    const std::vector<char> &buf = file.getBuffer();
    EXPECT_TRUE(buf.empty());
}

// Test that opening the file for writing returns a non-null FILE pointer
TEST_F(InMemoryFileTest_2636, OpenForWriteReturnsValidFilePointer_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);
    fclose(fp);
}

// Test that opening the file for reading returns a non-null FILE pointer
TEST_F(InMemoryFileTest_2636, OpenForReadReturnsValidFilePointer_2636) {
    FILE *fp = file.open("r");
    ASSERT_NE(fp, nullptr);
    fclose(fp);
}

// Test that writing data through the FILE pointer populates the buffer
TEST_F(InMemoryFileTest_2636, WriteDataPopulatesBuffer_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    const char *testData = "Hello, World!";
    size_t len = strlen(testData);
    size_t written = fwrite(testData, 1, len, fp);
    fflush(fp);

    EXPECT_EQ(written, len);

    const std::vector<char> &buf = file.getBuffer();
    EXPECT_EQ(buf.size(), len);
    EXPECT_EQ(std::string(buf.begin(), buf.end()), std::string(testData));

    fclose(fp);
}

// Test that multiple writes append data correctly
TEST_F(InMemoryFileTest_2636, MultipleWritesAppendData_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    const char *part1 = "Hello, ";
    const char *part2 = "World!";
    fwrite(part1, 1, strlen(part1), fp);
    fwrite(part2, 1, strlen(part2), fp);
    fflush(fp);

    const std::vector<char> &buf = file.getBuffer();
    std::string result(buf.begin(), buf.end());
    EXPECT_EQ(result, "Hello, World!");

    fclose(fp);
}

// Test writing and then reading back data
TEST_F(InMemoryFileTest_2636, WriteAndReadBack_2636) {
    FILE *fp = file.open("w+");
    ASSERT_NE(fp, nullptr);

    const char *testData = "Test data for read back";
    size_t len = strlen(testData);
    fwrite(testData, 1, len, fp);
    fflush(fp);

    // Seek back to beginning and read
    fseek(fp, 0, SEEK_SET);

    char readBuf[128] = {};
    size_t readCount = fread(readBuf, 1, len, fp);
    EXPECT_EQ(readCount, len);
    EXPECT_EQ(std::string(readBuf, readCount), std::string(testData));

    fclose(fp);
}

// Test seeking to different positions
TEST_F(InMemoryFileTest_2636, SeekToVariousPositions_2636) {
    FILE *fp = file.open("w+");
    ASSERT_NE(fp, nullptr);

    const char *testData = "ABCDEFGHIJ";
    size_t len = strlen(testData);
    fwrite(testData, 1, len, fp);
    fflush(fp);

    // Seek to beginning
    int ret = fseek(fp, 0, SEEK_SET);
    EXPECT_EQ(ret, 0);

    char c;
    fread(&c, 1, 1, fp);
    EXPECT_EQ(c, 'A');

    // Seek to position 5 from start
    fseek(fp, 5, SEEK_SET);
    fread(&c, 1, 1, fp);
    EXPECT_EQ(c, 'F');

    // Seek to end
    fseek(fp, 0, SEEK_END);
    long pos = ftell(fp);
    EXPECT_EQ(pos, static_cast<long>(len));

    // Seek backwards from current position
    fseek(fp, -3, SEEK_CUR);
    fread(&c, 1, 1, fp);
    EXPECT_EQ(c, 'H');

    fclose(fp);
}

// Test writing zero bytes
TEST_F(InMemoryFileTest_2636, WriteZeroBytes_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    size_t written = fwrite("data", 1, 0, fp);
    fflush(fp);

    EXPECT_EQ(written, 0u);
    EXPECT_TRUE(file.getBuffer().empty());

    fclose(fp);
}

// Test writing a single byte
TEST_F(InMemoryFileTest_2636, WriteSingleByte_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    char byte = 'X';
    size_t written = fwrite(&byte, 1, 1, fp);
    fflush(fp);

    EXPECT_EQ(written, 1u);
    const std::vector<char> &buf = file.getBuffer();
    ASSERT_EQ(buf.size(), 1u);
    EXPECT_EQ(buf[0], 'X');

    fclose(fp);
}

// Test writing a large amount of data
TEST_F(InMemoryFileTest_2636, WriteLargeData_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    const size_t largeSize = 1024 * 1024; // 1MB
    std::vector<char> largeData(largeSize, 'A');
    size_t written = fwrite(largeData.data(), 1, largeSize, fp);
    fflush(fp);

    EXPECT_EQ(written, largeSize);
    const std::vector<char> &buf = file.getBuffer();
    EXPECT_EQ(buf.size(), largeSize);

    fclose(fp);
}

// Test buffer content after close and re-check
TEST_F(InMemoryFileTest_2636, BufferPersistsAfterClose_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    const char *testData = "Persistent data";
    fwrite(testData, 1, strlen(testData), fp);
    fflush(fp);
    fclose(fp);

    const std::vector<char> &buf = file.getBuffer();
    std::string result(buf.begin(), buf.end());
    EXPECT_EQ(result, "Persistent data");
}

// Test reading from an empty file
TEST_F(InMemoryFileTest_2636, ReadFromEmptyFile_2636) {
    FILE *fp = file.open("r");
    ASSERT_NE(fp, nullptr);

    char readBuf[128] = {};
    size_t readCount = fread(readBuf, 1, 10, fp);
    EXPECT_EQ(readCount, 0u);

    fclose(fp);
}

// Test fprintf-like operations
TEST_F(InMemoryFileTest_2636, FprintfWritesToBuffer_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    int ret = fprintf(fp, "Number: %d", 42);
    fflush(fp);

    EXPECT_GT(ret, 0);
    const std::vector<char> &buf = file.getBuffer();
    std::string result(buf.begin(), buf.end());
    EXPECT_EQ(result, "Number: 42");

    fclose(fp);
}

// Test writing binary data with null bytes
TEST_F(InMemoryFileTest_2636, WriteBinaryDataWithNulls_2636) {
    FILE *fp = file.open("w");
    ASSERT_NE(fp, nullptr);

    char binaryData[] = {'A', '\0', 'B', '\0', 'C'};
    size_t written = fwrite(binaryData, 1, 5, fp);
    fflush(fp);

    EXPECT_EQ(written, 5u);
    const std::vector<char> &buf = file.getBuffer();
    ASSERT_EQ(buf.size(), 5u);
    EXPECT_EQ(buf[0], 'A');
    EXPECT_EQ(buf[1], '\0');
    EXPECT_EQ(buf[2], 'B');
    EXPECT_EQ(buf[3], '\0');
    EXPECT_EQ(buf[4], 'C');

    fclose(fp);
}

// Test that getBuffer returns a reference to the same internal data
TEST_F(InMemoryFileTest_2636, GetBufferReturnsSameReference_2636) {
    const std::vector<char> &buf1 = file.getBuffer();
    const std::vector<char> &buf2 = file.getBuffer();
    EXPECT_EQ(&buf1, &buf2);
}

// Test overwriting data by seeking back and writing
TEST_F(InMemoryFileTest_2636, SeekBackAndOverwrite_2636) {
    FILE *fp = file.open("w+");
    ASSERT_NE(fp, nullptr);

    const char *testData = "ABCDE";
    fwrite(testData, 1, 5, fp);
    fflush(fp);

    // Seek to position 2 and overwrite
    fseek(fp, 2, SEEK_SET);
    const char *overwrite = "XY";
    fwrite(overwrite, 1, 2, fp);
    fflush(fp);

    const std::vector<char> &buf = file.getBuffer();
    ASSERT_EQ(buf.size(), 5u);
    EXPECT_EQ(buf[0], 'A');
    EXPECT_EQ(buf[1], 'B');
    EXPECT_EQ(buf[2], 'X');
    EXPECT_EQ(buf[3], 'Y');
    EXPECT_EQ(buf[4], 'E');

    fclose(fp);
}
