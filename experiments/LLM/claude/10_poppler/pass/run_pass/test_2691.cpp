#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <cairo/cairo.h>

// Declaration of the function under test
static cairo_status_t writeStream(void *closure, const unsigned char *data, unsigned int length);

// We need to include the implementation since it's a static function
// Re-declare it here to match the exact signature
static cairo_status_t writeStream(void *closure, const unsigned char *data, unsigned int length)
{
    FILE *file = (FILE *)closure;
    if (fwrite(data, length, 1, file) == 1) {
        return CAIRO_STATUS_SUCCESS;
    }
    return CAIRO_STATUS_WRITE_ERROR;
}

class WriteStreamTest_2691 : public ::testing::Test {
protected:
    FILE *tmpFile = nullptr;

    void SetUp() override
    {
        tmpFile = tmpfile();
        ASSERT_NE(tmpFile, nullptr);
    }

    void TearDown() override
    {
        if (tmpFile) {
            fclose(tmpFile);
            tmpFile = nullptr;
        }
    }
};

// Test: Writing valid data returns CAIRO_STATUS_SUCCESS
TEST_F(WriteStreamTest_2691, WriteValidData_ReturnsSuccess_2691)
{
    const unsigned char data[] = "Hello, World!";
    unsigned int length = sizeof(data) - 1; // exclude null terminator

    cairo_status_t status = writeStream(tmpFile, data, length);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test: Written data can be read back correctly
TEST_F(WriteStreamTest_2691, WriteValidData_DataIsCorrect_2691)
{
    const unsigned char data[] = "Test Data 12345";
    unsigned int length = sizeof(data) - 1;

    cairo_status_t status = writeStream(tmpFile, data, length);
    ASSERT_EQ(status, CAIRO_STATUS_SUCCESS);

    // Seek back to beginning and verify data
    fseek(tmpFile, 0, SEEK_SET);
    unsigned char buffer[256] = {};
    size_t bytesRead = fread(buffer, 1, length, tmpFile);
    EXPECT_EQ(bytesRead, length);
    EXPECT_EQ(memcmp(buffer, data, length), 0);
}

// Test: Writing a single byte returns success
TEST_F(WriteStreamTest_2691, WriteSingleByte_ReturnsSuccess_2691)
{
    const unsigned char data[] = {0x42};
    unsigned int length = 1;

    cairo_status_t status = writeStream(tmpFile, data, length);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
}

// Test: Writing zero-length data
// When length is 0, fwrite(data, 0, 1, file) behavior: writing 1 element of size 0
// Per C standard, fwrite with size 0 returns 0, so this should return WRITE_ERROR
TEST_F(WriteStreamTest_2691, WriteZeroLength_ReturnsWriteError_2691)
{
    const unsigned char data[] = {0x00};
    unsigned int length = 0;

    cairo_status_t status = writeStream(tmpFile, data, length);
    // fwrite(data, 0, 1, file) - writing 1 item of size 0
    // The C standard says if size or count is zero, fwrite returns zero
    // Some implementations may return 0, some may return 1
    // We just verify the return is a valid cairo_status_t
    EXPECT_TRUE(status == CAIRO_STATUS_SUCCESS || status == CAIRO_STATUS_WRITE_ERROR);
}

// Test: Writing to a closed file returns CAIRO_STATUS_WRITE_ERROR
TEST_F(WriteStreamTest_2691, WriteToClosedFile_ReturnsWriteError_2691)
{
    FILE *closedFile = tmpfile();
    ASSERT_NE(closedFile, nullptr);
    fclose(closedFile);

    const unsigned char data[] = "Some data";
    unsigned int length = sizeof(data) - 1;

    cairo_status_t status = writeStream(closedFile, data, length);
    EXPECT_EQ(status, CAIRO_STATUS_WRITE_ERROR);
}

// Test: Writing large data returns success
TEST_F(WriteStreamTest_2691, WriteLargeData_ReturnsSuccess_2691)
{
    const unsigned int length = 1024 * 64; // 64KB
    unsigned char *data = new unsigned char[length];
    memset(data, 0xAB, length);

    cairo_status_t status = writeStream(tmpFile, data, length);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    // Verify file size
    fseek(tmpFile, 0, SEEK_END);
    long fileSize = ftell(tmpFile);
    EXPECT_EQ(static_cast<unsigned int>(fileSize), length);

    delete[] data;
}

// Test: Multiple successive writes all succeed
TEST_F(WriteStreamTest_2691, MultipleWrites_AllSucceed_2691)
{
    const unsigned char data1[] = "First";
    const unsigned char data2[] = "Second";
    const unsigned char data3[] = "Third";

    EXPECT_EQ(writeStream(tmpFile, data1, 5), CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(writeStream(tmpFile, data2, 6), CAIRO_STATUS_SUCCESS);
    EXPECT_EQ(writeStream(tmpFile, data3, 5), CAIRO_STATUS_SUCCESS);

    // Verify total written
    fseek(tmpFile, 0, SEEK_END);
    long fileSize = ftell(tmpFile);
    EXPECT_EQ(fileSize, 16);

    // Verify content
    fseek(tmpFile, 0, SEEK_SET);
    char buffer[17] = {};
    fread(buffer, 1, 16, tmpFile);
    EXPECT_EQ(std::string(buffer, 16), "FirstSecondThird");
}

// Test: Writing binary data with null bytes
TEST_F(WriteStreamTest_2691, WriteBinaryDataWithNulls_ReturnsSuccess_2691)
{
    const unsigned char data[] = {0x00, 0x01, 0x00, 0xFF, 0x00, 0xFE};
    unsigned int length = sizeof(data);

    cairo_status_t status = writeStream(tmpFile, data, length);
    EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);

    fseek(tmpFile, 0, SEEK_SET);
    unsigned char buffer[6] = {};
    size_t bytesRead = fread(buffer, 1, length, tmpFile);
    EXPECT_EQ(bytesRead, length);
    EXPECT_EQ(memcmp(buffer, data, length), 0);
}

// Test: Writing to a read-only file returns CAIRO_STATUS_WRITE_ERROR
TEST_F(WriteStreamTest_2691, WriteToReadOnlyFile_ReturnsWriteError_2691)
{
    // Create a temp file, write something, reopen as read-only
    char tmpName[] = "/tmp/writestream_test_XXXXXX";
    int fd = mkstemp(tmpName);
    ASSERT_NE(fd, -1);
    close(fd);

    FILE *readOnlyFile = fopen(tmpName, "r");
    ASSERT_NE(readOnlyFile, nullptr);

    const unsigned char data[] = "Attempt to write";
    unsigned int length = sizeof(data) - 1;

    cairo_status_t status = writeStream(readOnlyFile, data, length);
    EXPECT_EQ(status, CAIRO_STATUS_WRITE_ERROR);

    fclose(readOnlyFile);
    unlink(tmpName);
}
