#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <cstring>
#include "Stream.h"

// A mock/fake Stream subclass for testing toUnsignedChars
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override {}

    // Control test behavior
    bool rewindSuccess = true;
    std::vector<unsigned char> streamData;
    size_t readPos = 0;

    StreamKind getKind() const override { return strWeird; }

    bool rewind() override {
        if (!rewindSuccess) return false;
        readPos = 0;
        return true;
    }

    void close() override {}

    int getChar() override {
        if (readPos < streamData.size()) {
            return streamData[readPos++];
        }
        return EOF;
    }

    int lookChar() override {
        if (readPos < streamData.size()) {
            return streamData[readPos];
        }
        return EOF;
    }

    int getRawChar() override { return getChar(); }
    void getRawChars(int nChars, int *buffer) override {}
    int getUnfilteredChar() override { return getChar(); }
    bool unfilteredRewind() override { return rewind(); }

    char *getLine(char *buf, int size) override { return nullptr; }
    unsigned int discardChars(unsigned int n) override { return 0; }

    Goffset getPos() override { return static_cast<Goffset>(readPos); }
    void setPos(Goffset pos, int dir) override { readPos = static_cast<size_t>(pos); }

    std::optional<std::string> getPSFilter(int psLevel, const char *indent) override { return std::nullopt; }
    bool isBinary(bool last) const override { return false; }
    BaseStream *getBaseStream() override { return nullptr; }
    Stream *getUndecodedStream() override { return this; }
    Dict *getDict() override { return nullptr; }
    Object *getDictObject() override { return nullptr; }

protected:
    int getChars(int nChars, unsigned char *buffer) override {
        int count = 0;
        while (count < nChars && readPos < streamData.size()) {
            buffer[count++] = streamData[readPos++];
        }
        return count;
    }

    bool hasGetChars() override { return true; }
};

class StreamToUnsignedCharsTest_122 : public ::testing::Test {
protected:
    MockStream stream;
};

// Test: Empty stream returns empty vector
TEST_F(StreamToUnsignedCharsTest_122, EmptyStreamReturnsEmptyVector_122) {
    stream.streamData.clear();
    auto result = stream.toUnsignedChars();
    EXPECT_TRUE(result.empty());
}

// Test: Rewind failure returns empty vector
TEST_F(StreamToUnsignedCharsTest_122, RewindFailureReturnsEmpty_122) {
    stream.rewindSuccess = false;
    stream.streamData = {1, 2, 3};
    auto result = stream.toUnsignedChars();
    EXPECT_TRUE(result.empty());
}

// Test: Small data that fits within initial size
TEST_F(StreamToUnsignedCharsTest_122, SmallDataFitsInInitialBuffer_122) {
    stream.streamData = {10, 20, 30, 40, 50};
    auto result = stream.toUnsignedChars();
    ASSERT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
    EXPECT_EQ(result[3], 40);
    EXPECT_EQ(result[4], 50);
}

// Test: Data exactly fills the initial buffer size
TEST_F(StreamToUnsignedCharsTest_122, DataExactlyFillsInitialBuffer_122) {
    int initialSize = 100;
    stream.streamData.resize(initialSize);
    for (int i = 0; i < initialSize; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i % 256);
    }
    auto result = stream.toUnsignedChars(initialSize, 50);
    ASSERT_EQ(result.size(), static_cast<size_t>(initialSize));
    for (int i = 0; i < initialSize; i++) {
        EXPECT_EQ(result[i], static_cast<unsigned char>(i % 256));
    }
}

// Test: Data requires one buffer expansion
TEST_F(StreamToUnsignedCharsTest_122, DataRequiresOneExpansion_122) {
    int initialSize = 50;
    int sizeIncrement = 50;
    int totalData = 75;  // More than initial, less than initial + increment
    stream.streamData.resize(totalData);
    for (int i = 0; i < totalData; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i % 256);
    }
    auto result = stream.toUnsignedChars(initialSize, sizeIncrement);
    ASSERT_EQ(result.size(), static_cast<size_t>(totalData));
    for (int i = 0; i < totalData; i++) {
        EXPECT_EQ(result[i], static_cast<unsigned char>(i % 256));
    }
}

// Test: Data requires multiple buffer expansions
TEST_F(StreamToUnsignedCharsTest_122, DataRequiresMultipleExpansions_122) {
    int initialSize = 32;
    int sizeIncrement = 32;
    int totalData = 150;
    stream.streamData.resize(totalData);
    for (int i = 0; i < totalData; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i % 256);
    }
    auto result = stream.toUnsignedChars(initialSize, sizeIncrement);
    ASSERT_EQ(result.size(), static_cast<size_t>(totalData));
    for (int i = 0; i < totalData; i++) {
        EXPECT_EQ(result[i], static_cast<unsigned char>(i % 256));
    }
}

// Test: Single byte stream
TEST_F(StreamToUnsignedCharsTest_122, SingleByteStream_122) {
    stream.streamData = {0xFF};
    auto result = stream.toUnsignedChars();
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0xFF);
}

// Test: Default parameters work correctly
TEST_F(StreamToUnsignedCharsTest_122, DefaultParametersWork_122) {
    stream.streamData.resize(100);
    for (size_t i = 0; i < 100; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i);
    }
    auto result = stream.toUnsignedChars();
    ASSERT_EQ(result.size(), 100u);
}

// Test: Custom initial size of 1 with increment of 1
TEST_F(StreamToUnsignedCharsTest_122, VerySmallInitialSizeAndIncrement_122) {
    stream.streamData = {0xAA, 0xBB, 0xCC};
    auto result = stream.toUnsignedChars(1, 1);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 0xAA);
    EXPECT_EQ(result[1], 0xBB);
    EXPECT_EQ(result[2], 0xCC);
}

// Test: Data with all zeros
TEST_F(StreamToUnsignedCharsTest_122, AllZeroData_122) {
    stream.streamData.resize(200, 0);
    auto result = stream.toUnsignedChars(100, 100);
    ASSERT_EQ(result.size(), 200u);
    for (auto b : result) {
        EXPECT_EQ(b, 0u);
    }
}

// Test: Data with all 0xFF bytes
TEST_F(StreamToUnsignedCharsTest_122, AllMaxByteData_122) {
    stream.streamData.resize(50, 0xFF);
    auto result = stream.toUnsignedChars(10, 10);
    ASSERT_EQ(result.size(), 50u);
    for (auto b : result) {
        EXPECT_EQ(b, 0xFF);
    }
}

// Test: Result vector is properly sized (no extra bytes)
TEST_F(StreamToUnsignedCharsTest_122, ResultVectorProperlyTrimmed_122) {
    int initialSize = 4096;
    stream.streamData = {1, 2, 3};
    auto result = stream.toUnsignedChars(initialSize);
    // The result should be trimmed to actual data size, not the buffer size
    EXPECT_EQ(result.size(), 3u);
}

// Test: Large data stream
TEST_F(StreamToUnsignedCharsTest_122, LargeDataStream_122) {
    int dataSize = 10000;
    stream.streamData.resize(dataSize);
    for (int i = 0; i < dataSize; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i % 256);
    }
    auto result = stream.toUnsignedChars(1024, 1024);
    ASSERT_EQ(result.size(), static_cast<size_t>(dataSize));
    for (int i = 0; i < dataSize; i++) {
        EXPECT_EQ(result[i], static_cast<unsigned char>(i % 256));
    }
}

// Test: Data size exactly at boundary of initial + one increment
TEST_F(StreamToUnsignedCharsTest_122, DataExactlyFillsAfterOneIncrement_122) {
    int initialSize = 50;
    int sizeIncrement = 50;
    int totalData = 100;  // Exactly initial + increment
    stream.streamData.resize(totalData);
    for (int i = 0; i < totalData; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i % 256);
    }
    auto result = stream.toUnsignedChars(initialSize, sizeIncrement);
    ASSERT_EQ(result.size(), static_cast<size_t>(totalData));
}

// Test: Calling toUnsignedChars multiple times gives same result (rewind works)
TEST_F(StreamToUnsignedCharsTest_122, MultipleCallsGiveSameResult_122) {
    stream.streamData = {5, 10, 15, 20, 25};
    auto result1 = stream.toUnsignedChars();
    auto result2 = stream.toUnsignedChars();
    EXPECT_EQ(result1, result2);
}

// Test: Binary data preservation
TEST_F(StreamToUnsignedCharsTest_122, BinaryDataPreservation_122) {
    // Include all byte values 0-255
    stream.streamData.resize(256);
    for (int i = 0; i < 256; i++) {
        stream.streamData[i] = static_cast<unsigned char>(i);
    }
    auto result = stream.toUnsignedChars(128, 128);
    ASSERT_EQ(result.size(), 256u);
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(result[i], static_cast<unsigned char>(i));
    }
}
