#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

// Declaration of the function under test
typedef long long Goffset;
extern Goffset Gftell(FILE *f);

class GftellTest_43 : public ::testing::Test {
protected:
    FILE *tmpFile = nullptr;

    void SetUp() override {
        tmpFile = tmpfile();
        ASSERT_NE(tmpFile, nullptr);
    }

    void TearDown() override {
        if (tmpFile) {
            fclose(tmpFile);
            tmpFile = nullptr;
        }
    }
};

TEST_F(GftellTest_43, ReturnsZeroForNewFile_43) {
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 0);
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterWrite_43) {
    const char *data = "Hello, World!";
    size_t len = strlen(data);
    fwrite(data, 1, len, tmpFile);
    fflush(tmpFile);

    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, static_cast<Goffset>(len));
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterSeekToBeginning_43) {
    const char *data = "Some test data";
    fwrite(data, 1, strlen(data), tmpFile);
    fflush(tmpFile);

    fseek(tmpFile, 0, SEEK_SET);
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 0);
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterSeekToMiddle_43) {
    const char *data = "0123456789";
    fwrite(data, 1, 10, tmpFile);
    fflush(tmpFile);

    fseek(tmpFile, 5, SEEK_SET);
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 5);
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterSeekToEnd_43) {
    const char *data = "0123456789";
    size_t len = strlen(data);
    fwrite(data, 1, len, tmpFile);
    fflush(tmpFile);

    fseek(tmpFile, 0, SEEK_END);
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, static_cast<Goffset>(len));
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterMultipleWrites_43) {
    const char *data1 = "Hello";
    const char *data2 = " World";
    fwrite(data1, 1, strlen(data1), tmpFile);
    fwrite(data2, 1, strlen(data2), tmpFile);
    fflush(tmpFile);

    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, static_cast<Goffset>(strlen(data1) + strlen(data2)));
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterRead_43) {
    const char *data = "ABCDEFGHIJ";
    fwrite(data, 1, 10, tmpFile);
    fflush(tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    char buf[5];
    fread(buf, 1, 5, tmpFile);

    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 5);
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterSeekFromCurrent_43) {
    const char *data = "0123456789ABCDEF";
    fwrite(data, 1, 16, tmpFile);
    fflush(tmpFile);

    fseek(tmpFile, 4, SEEK_SET);
    fseek(tmpFile, 3, SEEK_CUR);

    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 7);
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterSeekFromEnd_43) {
    const char *data = "0123456789";
    fwrite(data, 1, 10, tmpFile);
    fflush(tmpFile);

    fseek(tmpFile, -3, SEEK_END);
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 7);
}

TEST_F(GftellTest_43, EmptyFilePositionIsZero_43) {
    // No writes performed
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 0);
}

TEST_F(GftellTest_43, ReturnsCorrectPositionAfterRewind_43) {
    const char *data = "Test data for rewind";
    fwrite(data, 1, strlen(data), tmpFile);
    fflush(tmpFile);

    rewind(tmpFile);
    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, 0);
}

TEST_F(GftellTest_43, ConsistentWithFtell_43) {
    const char *data = "Consistency check";
    fwrite(data, 1, strlen(data), tmpFile);
    fflush(tmpFile);

    long stdPos = ftell(tmpFile);
    Goffset gPos = Gftell(tmpFile);
    EXPECT_EQ(gPos, static_cast<Goffset>(stdPos));
}

TEST_F(GftellTest_43, LargerDataPositionTracking_43) {
    // Write a larger block of data
    const size_t blockSize = 8192;
    char *block = new char[blockSize];
    memset(block, 'A', blockSize);

    fwrite(block, 1, blockSize, tmpFile);
    fflush(tmpFile);

    Goffset pos = Gftell(tmpFile);
    EXPECT_EQ(pos, static_cast<Goffset>(blockSize));

    delete[] block;
}
