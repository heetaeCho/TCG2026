#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

// Define the struct under test
struct FILECloser {
public:
    void operator()(FILE *f) { fclose(f); }
};

class FILECloserTest_1852 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that FILECloser can close a valid file pointer
TEST_F(FILECloserTest_1852, ClosesValidFile_1852) {
    // Create a temporary file
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);

    // Write something to ensure file is functional
    const char *data = "test data";
    size_t written = fwrite(data, 1, strlen(data), f);
    EXPECT_EQ(written, strlen(data));

    // Use FILECloser to close the file - should not crash
    FILECloser closer;
    EXPECT_NO_THROW(closer(f));
    // After this, f is closed. We can't verify directly that it's closed
    // without invoking undefined behavior, but the fact that it didn't crash
    // is the observable behavior.
}

// Test that FILECloser works with a file opened for reading
TEST_F(FILECloserTest_1852, ClosesReadOnlyFile_1852) {
    // Create a temp file, write to it, then reopen for reading
    char tmpname[] = "/tmp/filecloser_test_XXXXXX";
    int fd = mkstemp(tmpname);
    ASSERT_NE(fd, -1);
    close(fd);

    FILE *f = fopen(tmpname, "r");
    ASSERT_NE(f, nullptr);

    FILECloser closer;
    EXPECT_NO_THROW(closer(f));

    // Clean up
    remove(tmpname);
}

// Test that FILECloser works with a file opened for writing
TEST_F(FILECloserTest_1852, ClosesWriteOnlyFile_1852) {
    char tmpname[] = "/tmp/filecloser_test_w_XXXXXX";
    int fd = mkstemp(tmpname);
    ASSERT_NE(fd, -1);
    close(fd);

    FILE *f = fopen(tmpname, "w");
    ASSERT_NE(f, nullptr);

    // Write some data
    fprintf(f, "hello world");

    FILECloser closer;
    EXPECT_NO_THROW(closer(f));

    // Verify data was flushed and written by close
    FILE *verify = fopen(tmpname, "r");
    ASSERT_NE(verify, nullptr);
    char buf[64] = {};
    fgets(buf, sizeof(buf), verify);
    EXPECT_STREQ(buf, "hello world");
    fclose(verify);

    remove(tmpname);
}

// Test that FILECloser can be used with unique_ptr
TEST_F(FILECloserTest_1852, WorksWithUniquePtr_1852) {
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);

    {
        std::unique_ptr<FILE, FILECloser> filePtr(f);
        // Write to ensure file is valid
        fprintf(filePtr.get(), "unique_ptr test");
        // filePtr goes out of scope here, FILECloser should be called
    }
    // If we get here without crash, the closer worked correctly
    SUCCEED();
}

// Test that FILECloser is default constructible
TEST_F(FILECloserTest_1852, IsDefaultConstructible_1852) {
    EXPECT_TRUE(std::is_default_constructible<FILECloser>::value);
}

// Test that FILECloser is callable
TEST_F(FILECloserTest_1852, IsCallableWithFilePointer_1852) {
    EXPECT_TRUE((std::is_invocable<FILECloser, FILE*>::value));
}

// Test that FILECloser works with tmpfile
TEST_F(FILECloserTest_1852, ClosesTmpFile_1852) {
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);

    // Seek and write
    fseek(f, 0, SEEK_SET);
    const char *msg = "tmpfile content";
    fwrite(msg, 1, strlen(msg), f);

    FILECloser closer;
    EXPECT_NO_THROW(closer(f));
}

// Test multiple FILECloser instances can each close different files
TEST_F(FILECloserTest_1852, MultipleInstancesCloseMultipleFiles_1852) {
    FILE *f1 = tmpfile();
    FILE *f2 = tmpfile();
    ASSERT_NE(f1, nullptr);
    ASSERT_NE(f2, nullptr);

    FILECloser closer1;
    FILECloser closer2;

    EXPECT_NO_THROW(closer1(f1));
    EXPECT_NO_THROW(closer2(f2));
}

// Test that FILECloser flushes buffered data on close
TEST_F(FILECloserTest_1852, FlushesDataOnClose_1852) {
    char tmpname[] = "/tmp/filecloser_flush_XXXXXX";
    int fd = mkstemp(tmpname);
    ASSERT_NE(fd, -1);
    close(fd);

    FILE *f = fopen(tmpname, "w");
    ASSERT_NE(f, nullptr);

    // Write data without explicit flush
    const char *data = "buffered data test";
    fputs(data, f);

    // Close via FILECloser (which calls fclose, which flushes)
    FILECloser closer;
    closer(f);

    // Verify data was written (fclose should have flushed)
    FILE *readFile = fopen(tmpname, "r");
    ASSERT_NE(readFile, nullptr);
    char buf[64] = {};
    fgets(buf, sizeof(buf), readFile);
    EXPECT_STREQ(buf, data);
    fclose(readFile);

    remove(tmpname);
}
