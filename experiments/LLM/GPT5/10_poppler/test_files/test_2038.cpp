#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>
#include <cstdio>
#include <cerrno>

extern "C" {
    gboolean save_helper(const gchar *buf, gsize count, gpointer data, GError **error);
}

class SaveHelperTest_2038 : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code for the tests (if any). 
        // For example, creating a temporary file to test the function on.
        temp_file = std::tmpfile();
        ASSERT_NE(temp_file, nullptr); // Ensure the file is successfully created
    }

    void TearDown() override {
        // Cleanup code after tests
        if (temp_file) {
            fclose(temp_file);
        }
    }

    FILE* temp_file;
};

// Test case for normal operation (when data is successfully written to file)
TEST_F(SaveHelperTest_2038, SaveHelper_Success_2038) {
    const gchar *data = "Hello, Poppler!";
    gsize count = strlen(data);
    GError* error = nullptr;

    // Call the function
    gboolean result = save_helper(data, count, temp_file, &error);

    // Check if the function returned TRUE, indicating success
    EXPECT_TRUE(result);

    // Verify that the content has been written correctly to the file
    fseek(temp_file, 0, SEEK_SET); // Reset file pointer to the beginning
    char buf[256];
    size_t bytes_read = fread(buf, 1, count, temp_file);
    buf[bytes_read] = '\0'; // Null-terminate the read data
    EXPECT_STREQ(buf, data); // Compare the read data with the original data
}

// Test case for error scenario (if fwrite fails)
TEST_F(SaveHelperTest_2038, SaveHelper_ErrorWriting_2038) {
    const gchar *data = "Hello, Poppler!";
    gsize count = strlen(data);
    GError* error = nullptr;

    // Simulate an error by passing a NULL file pointer
    gboolean result = save_helper(data, count, nullptr, &error);

    // Expect failure since no valid file is provided
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    EXPECT_EQ(error->code, G_FILE_ERROR_FAILED); // Check if the error is related to the file failure
    g_clear_error(&error); // Clear error after validation
}

// Test case for boundary condition: Writing zero bytes
TEST_F(SaveHelperTest_2038, SaveHelper_ZeroBytes_2038) {
    const gchar *data = "";
    gsize count = 0;
    GError* error = nullptr;

    // Expect success when writing zero bytes
    gboolean result = save_helper(data, count, temp_file, &error);
    EXPECT_TRUE(result);

    // Verify nothing was written
    fseek(temp_file, 0, SEEK_SET); // Reset file pointer
    char buf[256];
    size_t bytes_read = fread(buf, 1, count, temp_file);
    EXPECT_EQ(bytes_read, 0); // Nothing should have been read
}

// Test case for boundary condition: Writing to a file with a NULL pointer for data
TEST_F(SaveHelperTest_2038, SaveHelper_NullData_2038) {
    const gchar *data = nullptr;
    gsize count = 0;
    GError* error = nullptr;

    // Expect failure when data is NULL
    gboolean result = save_helper(data, count, temp_file, &error);
    EXPECT_FALSE(result);
    EXPECT_NE(error, nullptr);
    EXPECT_EQ(error->code, G_FILE_ERROR_FAILED);
    g_clear_error(&error); // Clear error after validation
}

// Test case for boundary condition: Writing a very large amount of data
TEST_F(SaveHelperTest_2038, SaveHelper_LargeData_2038) {
    const gchar *data = "A";
    gsize count = 1000000; // One million characters
    GError* error = nullptr;

    // Create a large buffer with repeated data
    gchar* large_data = new gchar[count + 1];
    memset(large_data, 'A', count);
    large_data[count] = '\0'; // Null-terminate

    // Call the function with the large data
    gboolean result = save_helper(large_data, count, temp_file, &error);

    // Expect success for large data
    EXPECT_TRUE(result);

    // Verify that the data has been written to the file
    fseek(temp_file, 0, SEEK_SET); // Reset file pointer
    char* buf = new char[count + 1];
    size_t bytes_read = fread(buf, 1, count, temp_file);
    buf[bytes_read] = '\0'; // Null-terminate the read data
    EXPECT_STREQ(buf, large_data); // Compare the written data with the expected data

    delete[] large_data;
    delete[] buf;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}