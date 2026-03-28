#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <cstring>

// Include the necessary headers
#include "Stream.h"

// We need a concrete mock implementation of Stream since it's abstract
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override {}

    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(int, getRawChar, (), (override));
    MOCK_METHOD(void, getRawChars, (int nChars, int *buffer), (override));
    MOCK_METHOD(int, getUnfilteredChar, (), (override));
    MOCK_METHOD(bool, unfilteredRewind, (), (override));
    MOCK_METHOD(char*, getLine, (char *buf, int size), (override));
    MOCK_METHOD(unsigned int, discardChars, (unsigned int n), (override));
    MOCK_METHOD(Goffset, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char *indent), (override));
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(BaseStream*, getBaseStream, (), (override));
    MOCK_METHOD(Stream*, getUndecodedStream, (), (override));
    MOCK_METHOD(Dict*, getDict, (), (override));
    MOCK_METHOD(Object*, getDictObject, (), (override));

    // We need to control doGetChars behavior. doGetChars calls getChars internally
    // but since we want to control the output, we mock hasGetChars and getChars
    MOCK_METHOD(bool, hasGetChars, (), (override));
    MOCK_METHOD(int, getChars, (int nChars, unsigned char *buffer), (override));

    // Helper to set up data that will be returned by doGetChars
    void setData(const std::string &data) {
        m_data = data;
        m_pos = 0;
    }

private:
    std::string m_data;
    size_t m_pos = 0;
};

// A testable concrete stream that gives us full control over rewind and doGetChars
class TestableStream : public Stream {
public:
    TestableStream() : Stream(), m_rewindResult(true), m_pos(0) {}
    ~TestableStream() override {}

    void setRewindResult(bool result) { m_rewindResult = result; }
    void setData(const std::string &data) { m_data = data; m_pos = 0; }

    StreamKind getKind() const override { return strFile; }
    bool rewind() override { 
        if (m_rewindResult) {
            m_pos = 0;
        }
        return m_rewindResult; 
    }
    void close() override {}
    int getChar() override {
        if (m_pos < m_data.size()) {
            return (unsigned char)m_data[m_pos++];
        }
        return EOF;
    }
    int lookChar() override {
        if (m_pos < m_data.size()) {
            return (unsigned char)m_data[m_pos];
        }
        return EOF;
    }
    int getRawChar() override { return getChar(); }
    void getRawChars(int nChars, int *buffer) override {}
    int getUnfilteredChar() override { return getChar(); }
    bool unfilteredRewind() override { return rewind(); }
    char* getLine(char *buf, int size) override { return nullptr; }
    unsigned int discardChars(unsigned int n) override { return 0; }
    Goffset getPos() override { return m_pos; }
    void setPos(Goffset pos, int dir) override { m_pos = pos; }
    std::optional<std::string> getPSFilter(int psLevel, const char *indent) override { return std::nullopt; }
    bool isBinary(bool last) const override { return false; }
    BaseStream* getBaseStream() override { return nullptr; }
    Stream* getUndecodedStream() override { return this; }
    Dict* getDict() override { return nullptr; }
    Object* getDictObject() override { return nullptr; }

private:
    bool hasGetChars() override { return false; }
    int getChars(int nChars, unsigned char *buffer) override {
        int count = 0;
        while (count < nChars && m_pos < m_data.size()) {
            buffer[count++] = (unsigned char)m_data[m_pos++];
        }
        return count;
    }

    bool m_rewindResult;
    std::string m_data;
    size_t m_pos;
};

class StreamFillStringTest_120 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that fillString clears the string when rewind fails
TEST_F(StreamFillStringTest_120, FillStringClearsOnRewindFailure_120) {
    TestableStream stream;
    stream.setRewindResult(false);
    stream.setData("some data");
    
    std::string result = "pre-existing content";
    stream.fillString(result);
    
    EXPECT_TRUE(result.empty());
}

// Test that fillString works with empty data
TEST_F(StreamFillStringTest_120, FillStringWithEmptyData_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    stream.setData("");
    
    std::string result = "old content";
    stream.fillString(result);
    
    // After rewind succeeds and no data is read, the string should reflect
    // what was appended. Since doGetChars returns 0 immediately, nothing is appended.
    // But note: fillString doesn't clear 's' before appending - it only clears on rewind failure.
    // Actually looking at the code: it only clears on rewind failure. On success it just appends.
    // So the old content would remain if the implementation doesn't clear first.
    // Let's check the actual implementation:
    // It does: rewind, then while loop appending. It never clears s on success path.
    // So "old content" + nothing = "old content"
    EXPECT_EQ(result, "old content");
}

// Test that fillString reads small data correctly
TEST_F(StreamFillStringTest_120, FillStringWithSmallData_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    stream.setData("Hello, World!");
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result, "Hello, World!");
}

// Test that fillString reads data larger than buffer size (4096)
TEST_F(StreamFillStringTest_120, FillStringWithLargeData_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    // Create data larger than 4096 to test multiple iterations
    std::string largeData(10000, 'A');
    stream.setData(largeData);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 10000u);
    EXPECT_EQ(result, largeData);
}

// Test that fillString handles exactly 4096 bytes (one full buffer read)
TEST_F(StreamFillStringTest_120, FillStringWithExactBufferSize_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    std::string exactData(4096, 'B');
    stream.setData(exactData);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 4096u);
    EXPECT_EQ(result, exactData);
}

// Test that fillString handles data just over buffer size boundary
TEST_F(StreamFillStringTest_120, FillStringWithDataJustOverBufferSize_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    std::string data(4097, 'C');
    stream.setData(data);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 4097u);
    EXPECT_EQ(result, data);
}

// Test that fillString handles binary data (including null bytes)
TEST_F(StreamFillStringTest_120, FillStringWithBinaryData_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    std::string binaryData;
    binaryData.push_back('\0');
    binaryData.push_back('\x01');
    binaryData.push_back('\xFF');
    binaryData.push_back('\0');
    binaryData.push_back('A');
    stream.setData(binaryData);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result, binaryData);
}

// Test that fillString appends to existing string content when rewind succeeds
TEST_F(StreamFillStringTest_120, FillStringAppendsToExistingContent_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    stream.setData("new data");
    
    std::string result = "existing ";
    stream.fillString(result);
    
    // Based on the code, fillString does not clear the string before appending
    EXPECT_EQ(result, "existing new data");
}

// Test with single byte of data
TEST_F(StreamFillStringTest_120, FillStringWithSingleByte_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    stream.setData("X");
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result, "X");
}

// Test that fillString works with multiple buffer-size chunks
TEST_F(StreamFillStringTest_120, FillStringWithMultipleFullChunks_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    // 3 full chunks of 4096 = 12288
    std::string data(12288, 'D');
    stream.setData(data);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 12288u);
    EXPECT_EQ(result, data);
}

// Test rewind failure with non-empty string clears it
TEST_F(StreamFillStringTest_120, FillStringRewindFailureClearsNonEmptyString_120) {
    TestableStream stream;
    stream.setRewindResult(false);
    
    std::string result = "this should be cleared";
    stream.fillString(result);
    
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

// Test with data just under buffer size
TEST_F(StreamFillStringTest_120, FillStringWithDataJustUnderBufferSize_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    std::string data(4095, 'E');
    stream.setData(data);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 4095u);
    EXPECT_EQ(result, data);
}

// Test with very large data
TEST_F(StreamFillStringTest_120, FillStringWithVeryLargeData_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    // 100KB of data
    std::string data(102400, 'F');
    stream.setData(data);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), 102400u);
    EXPECT_EQ(result, data);
}

// Test that data content is preserved correctly (varied content)
TEST_F(StreamFillStringTest_120, FillStringPreservesVariedContent_120) {
    TestableStream stream;
    stream.setRewindResult(true);
    
    std::string data;
    for (int i = 0; i < 5000; i++) {
        data.push_back(static_cast<char>(i % 256));
    }
    stream.setData(data);
    
    std::string result;
    stream.fillString(result);
    
    EXPECT_EQ(result.size(), data.size());
    EXPECT_EQ(result, data);
}
