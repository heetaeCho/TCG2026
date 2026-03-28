#include <gtest/gtest.h>
#include <glib.h>
#include <cstdio>
#include <cstring>
#include <cerrno>

// We need to declare the function under test since it's static in the source file.
// To test a static function, we include the source or redeclare it.
// Since save_helper is static, we need to include the .cc file to access it.
// This is a common technique for testing static functions.

// Include the implementation file to get access to the static function
// We need the poppler headers for this to compile
#include "poppler-media.cc"

class SaveHelperTest_2038 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file for testing
        tmpfile_path_ = g_strdup("test_save_helper_2038_XXXXXX");
        int fd = g_mkstemp(tmpfile_path_);
        ASSERT_NE(fd, -1);
        close(fd);
    }

    void TearDown() override {
        if (tmpfile_path_) {
            g_unlink(tmpfile_path_);
            g_free(tmpfile_path_);
            tmpfile_path_ = nullptr;
        }
    }

    gchar *tmpfile_path_ = nullptr;
};

// Test normal operation: writing data successfully
TEST_F(SaveHelperTest_2038, WriteDataSuccessfully_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    const gchar *data = "Hello, World!";
    gsize count = strlen(data);
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    fclose(f);

    // Verify the data was actually written
    f = fopen(tmpfile_path_, "rb");
    ASSERT_NE(f, nullptr);
    char buf[256] = {0};
    size_t bytes_read = fread(buf, 1, sizeof(buf), f);
    fclose(f);

    EXPECT_EQ(bytes_read, count);
    EXPECT_STREQ(buf, data);
}

// Test writing zero bytes
TEST_F(SaveHelperTest_2038, WriteZeroBytes_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    const gchar *data = "";
    gsize count = 0;
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    fclose(f);
}

// Test writing a single byte
TEST_F(SaveHelperTest_2038, WriteSingleByte_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    const gchar data[] = "A";
    gsize count = 1;
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    fclose(f);

    // Verify
    f = fopen(tmpfile_path_, "rb");
    ASSERT_NE(f, nullptr);
    char buf[8] = {0};
    size_t bytes_read = fread(buf, 1, sizeof(buf), f);
    fclose(f);

    EXPECT_EQ(bytes_read, 1u);
    EXPECT_EQ(buf[0], 'A');
}

// Test writing binary data including null bytes
TEST_F(SaveHelperTest_2038, WriteBinaryData_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    const gchar data[] = {'\x00', '\x01', '\x02', '\xFF', '\xFE'};
    gsize count = sizeof(data);
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    fclose(f);

    // Verify
    f = fopen(tmpfile_path_, "rb");
    ASSERT_NE(f, nullptr);
    char buf[16] = {0};
    size_t bytes_read = fread(buf, 1, sizeof(buf), f);
    fclose(f);

    EXPECT_EQ(bytes_read, count);
    EXPECT_EQ(memcmp(buf, data, count), 0);
}

// Test writing to a closed file (should fail)
TEST_F(SaveHelperTest_2038, WriteToClosedFile_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);
    fclose(f);

    const gchar *data = "Some data";
    gsize count = strlen(data);
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    // Writing to a closed file should fail
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test writing large data
TEST_F(SaveHelperTest_2038, WriteLargeData_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    gsize count = 1024 * 1024; // 1 MB
    gchar *data = (gchar *)g_malloc(count);
    memset(data, 'X', count);
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    fclose(f);

    // Verify file size
    f = fopen(tmpfile_path_, "rb");
    ASSERT_NE(f, nullptr);
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fclose(f);

    EXPECT_EQ(static_cast<gsize>(file_size), count);

    g_free(data);
}

// Test multiple sequential writes
TEST_F(SaveHelperTest_2038, MultipleWrites_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    GError *error = nullptr;

    const gchar *data1 = "Hello";
    gboolean result1 = save_helper(data1, strlen(data1), f, &error);
    EXPECT_TRUE(result1);
    EXPECT_EQ(error, nullptr);

    const gchar *data2 = ", ";
    gboolean result2 = save_helper(data2, strlen(data2), f, &error);
    EXPECT_TRUE(result2);
    EXPECT_EQ(error, nullptr);

    const gchar *data3 = "World!";
    gboolean result3 = save_helper(data3, strlen(data3), f, &error);
    EXPECT_TRUE(result3);
    EXPECT_EQ(error, nullptr);

    fclose(f);

    // Verify concatenated result
    f = fopen(tmpfile_path_, "rb");
    ASSERT_NE(f, nullptr);
    char buf[256] = {0};
    size_t bytes_read = fread(buf, 1, sizeof(buf), f);
    fclose(f);

    EXPECT_EQ(bytes_read, strlen("Hello, World!"));
    EXPECT_STREQ(buf, "Hello, World!");
}

// Test that error is set with proper domain on failure
TEST_F(SaveHelperTest_2038, ErrorDomainIsGFileError_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);
    fclose(f);

    const gchar *data = "test data";
    gsize count = strlen(data);
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    if (!result) {
        ASSERT_NE(error, nullptr);
        EXPECT_EQ(error->domain, G_FILE_ERROR);
        EXPECT_NE(error->message, nullptr);
        g_error_free(error);
    }
}

// Test writing to a read-only file
TEST_F(SaveHelperTest_2038, WriteToReadOnlyFile_2038) {
    FILE *f = fopen(tmpfile_path_, "rb");
    ASSERT_NE(f, nullptr);

    const gchar *data = "test";
    gsize count = strlen(data);
    GError *error = nullptr;

    gboolean result = save_helper(data, count, f, &error);

    // Writing to a read-only file should fail
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    if (error) {
        EXPECT_EQ(error->domain, G_FILE_ERROR);
        g_error_free(error);
    }

    fclose(f);
}

// Test with null error pointer (should not crash)
TEST_F(SaveHelperTest_2038, NullErrorPointer_2038) {
    FILE *f = fopen(tmpfile_path_, "wb");
    ASSERT_NE(f, nullptr);

    const gchar *data = "test data";
    gsize count = strlen(data);

    // Passing NULL for error should still work for successful case
    gboolean result = save_helper(data, count, f, nullptr);

    EXPECT_TRUE(result);

    fclose(f);
}
