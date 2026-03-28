#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

// Declaration of the function under test
#include "goo/gfile.h"

class GfseekTest_42 : public ::testing::Test {
protected:
    FILE *tmpFile = nullptr;

    void SetUp() override {
        tmpFile = tmpfile();
        ASSERT_NE(tmpFile, nullptr);
        // Write some known data to the file
        const char data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        size_t written = fwrite(data, 1, strlen(data), tmpFile);
        ASSERT_EQ(written, strlen(data));
        fflush(tmpFile);
    }

    void TearDown() override {
        if (tmpFile) {
            fclose(tmpFile);
            tmpFile = nullptr;
        }
    }
};

// Test seeking to the beginning of the file with SEEK_SET
TEST_F(GfseekTest_42, SeekSetToBeginning_42) {
    int result = Gfseek(tmpFile, 0, SEEK_SET);
    EXPECT_EQ(result, 0);
    // Verify position
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 0);
}

// Test seeking to a specific offset from the beginning with SEEK_SET
TEST_F(GfseekTest_42, SeekSetToMiddle_42) {
    int result = Gfseek(tmpFile, 10, SEEK_SET);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 10);
}

// Test seeking to the end of the file with SEEK_END
TEST_F(GfseekTest_42, SeekEndToEnd_42) {
    int result = Gfseek(tmpFile, 0, SEEK_END);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 36); // strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") == 36
}

// Test seeking backwards from the end with SEEK_END
TEST_F(GfseekTest_42, SeekEndNegativeOffset_42) {
    int result = Gfseek(tmpFile, -10, SEEK_END);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 26); // 36 - 10 = 26
}

// Test seeking forward from current position with SEEK_CUR
TEST_F(GfseekTest_42, SeekCurForward_42) {
    Gfseek(tmpFile, 5, SEEK_SET);
    int result = Gfseek(tmpFile, 3, SEEK_CUR);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 8);
}

// Test seeking backward from current position with SEEK_CUR
TEST_F(GfseekTest_42, SeekCurBackward_42) {
    Gfseek(tmpFile, 20, SEEK_SET);
    int result = Gfseek(tmpFile, -5, SEEK_CUR);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 15);
}

// Test seeking with zero offset from SEEK_CUR (no movement)
TEST_F(GfseekTest_42, SeekCurZeroOffset_42) {
    Gfseek(tmpFile, 12, SEEK_SET);
    int result = Gfseek(tmpFile, 0, SEEK_CUR);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 12);
}

// Test seeking past the end of file (this is allowed on most systems)
TEST_F(GfseekTest_42, SeekBeyondEnd_42) {
    int result = Gfseek(tmpFile, 1000, SEEK_SET);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 1000);
}

// Test seeking to a negative position from SEEK_SET (should fail)
TEST_F(GfseekTest_42, SeekSetNegativeOffsetFails_42) {
    int result = Gfseek(tmpFile, -1, SEEK_SET);
    EXPECT_NE(result, 0);
}

// Test seeking before the beginning from SEEK_CUR (should fail)
TEST_F(GfseekTest_42, SeekCurBeforeBeginningFails_42) {
    Gfseek(tmpFile, 5, SEEK_SET);
    int result = Gfseek(tmpFile, -10, SEEK_CUR);
    EXPECT_NE(result, 0);
}

// Test seeking before the beginning from SEEK_END (should fail)
TEST_F(GfseekTest_42, SeekEndBeforeBeginningFails_42) {
    int result = Gfseek(tmpFile, -100, SEEK_END);
    EXPECT_NE(result, 0);
}

// Test that after seeking, reading produces correct data
TEST_F(GfseekTest_42, SeekAndReadVerify_42) {
    int result = Gfseek(tmpFile, 0, SEEK_SET);
    EXPECT_EQ(result, 0);
    char ch;
    size_t read = fread(&ch, 1, 1, tmpFile);
    EXPECT_EQ(read, 1u);
    EXPECT_EQ(ch, 'A');

    result = Gfseek(tmpFile, 25, SEEK_SET);
    EXPECT_EQ(result, 0);
    read = fread(&ch, 1, 1, tmpFile);
    EXPECT_EQ(read, 1u);
    EXPECT_EQ(ch, 'Z');
}

// Test multiple sequential seeks
TEST_F(GfseekTest_42, MultipleSequentialSeeks_42) {
    Gfseek(tmpFile, 0, SEEK_SET);
    EXPECT_EQ(ftell(tmpFile), 0);

    Gfseek(tmpFile, 10, SEEK_SET);
    EXPECT_EQ(ftell(tmpFile), 10);

    Gfseek(tmpFile, 5, SEEK_CUR);
    EXPECT_EQ(ftell(tmpFile), 15);

    Gfseek(tmpFile, -3, SEEK_CUR);
    EXPECT_EQ(ftell(tmpFile), 12);

    Gfseek(tmpFile, 0, SEEK_END);
    EXPECT_EQ(ftell(tmpFile), 36);
}

// Test seeking to exact end boundary
TEST_F(GfseekTest_42, SeekToExactFileSize_42) {
    int result = Gfseek(tmpFile, 36, SEEK_SET);
    EXPECT_EQ(result, 0);
    long pos = ftell(tmpFile);
    EXPECT_EQ(pos, 36);
    // Reading at EOF should return 0 bytes
    char ch;
    size_t read = fread(&ch, 1, 1, tmpFile);
    EXPECT_EQ(read, 0u);
}

// Test with offset zero and SEEK_SET on a fresh file position
TEST_F(GfseekTest_42, SeekSetZeroFromArbitraryPosition_42) {
    // Move to some arbitrary position first
    Gfseek(tmpFile, 20, SEEK_SET);
    EXPECT_EQ(ftell(tmpFile), 20);
    
    // Seek back to beginning
    int result = Gfseek(tmpFile, 0, SEEK_SET);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(ftell(tmpFile), 0);
}
