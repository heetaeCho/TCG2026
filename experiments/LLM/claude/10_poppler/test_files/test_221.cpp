#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <memory>
#include <vector>
#include <cstring>

// We need a concrete Stream implementation to feed into RunLengthEncoder.
// MemStream is available in poppler's Stream.h

class RunLengthEncoderTest_221 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a MemStream from data buffer
    // Note: MemStream takes ownership semantics vary; we keep data alive
    std::unique_ptr<MemStream> createMemStream(const char* data, int len) {
        // MemStream(char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        char* buf = new char[len];
        memcpy(buf, data, len);
        Object dictObj;
        auto ms = std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
        return ms;
    }

    // We need to track allocated buffers for cleanup
    std::vector<char*> allocatedBuffers;
};

TEST_F(RunLengthEncoderTest_221, GetCharReturnsEOFForEmptyStream_221) {
    // Empty input stream should eventually return EOF
    const char data[] = "";
    Object dictObj;
    char* buf = new char[1];
    buf[0] = '\0';
    auto memStream = std::make_unique<MemStream>(buf, 0, 0, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    // For an empty stream, the encoder should produce an end-of-data marker (128) then EOF
    // Run-length encoding of empty data: just EOD marker
    int ch;
    bool gotEOF = false;
    for (int i = 0; i < 10; i++) {
        ch = encoder.getChar();
        if (ch == EOF) {
            gotEOF = true;
            break;
        }
    }
    EXPECT_TRUE(gotEOF);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, GetCharEncodesSmallData_221) {
    // A small stream with distinct bytes
    const char data[] = {0x41, 0x42, 0x43}; // "ABC"
    char* buf = new char[3];
    memcpy(buf, data, 3);
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 3, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    // Collect all output bytes until EOF
    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) break; // safety
    }

    // Output should be non-empty (encoded data + EOD marker 128)
    EXPECT_FALSE(output.empty());
    // Last meaningful byte before EOF should be the EOD marker (128)
    EXPECT_EQ(output.back(), 128);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, GetCharEncodesRepeatedBytes_221) {
    // Stream with repeated bytes - should compress as a run
    char* buf = new char[10];
    memset(buf, 0x55, 10);
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 10, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) break;
    }

    EXPECT_FALSE(output.empty());
    // For a run of 10 identical bytes, RLE should encode as:
    // (257-10) = 247, 0x55, then EOD (128)
    // So output should be: 247, 0x55, 128
    ASSERT_GE(output.size(), 3u);
    EXPECT_EQ(output[0], 247); // 257 - 10 = 247
    EXPECT_EQ(output[1], 0x55);
    EXPECT_EQ(output.back(), 128); // EOD
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, LookCharDoesNotAdvance_221) {
    const char data[] = {0x41, 0x42, 0x43};
    char* buf = new char[3];
    memcpy(buf, data, 3);
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 3, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    int first = encoder.lookChar();
    int second = encoder.lookChar();
    EXPECT_EQ(first, second);

    int third = encoder.getChar();
    EXPECT_EQ(first, third);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, GetKindReturnsCorrectKind_221) {
    char* buf = new char[1];
    buf[0] = 'A';
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 1, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());

    EXPECT_EQ(encoder.getKind(), strWeird);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, IsBinaryReturnsTrue_221) {
    char* buf = new char[1];
    buf[0] = 'A';
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 1, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());

    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, IsEncoderReturnsTrue_221) {
    char* buf = new char[1];
    buf[0] = 'A';
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 1, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());

    EXPECT_TRUE(encoder.isEncoder());
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, GetPSFilterReturnsNone_221) {
    char* buf = new char[1];
    buf[0] = 'A';
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 1, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());

    auto result = encoder.getPSFilter(1, "");
    // Encoders typically return nullopt for PS filters
    EXPECT_FALSE(result.has_value());
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, RewindAllowsReReading_221) {
    const char data[] = {0x41, 0x42, 0x43};
    char* buf = new char[3];
    memcpy(buf, data, 3);
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 3, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    // Read all output
    std::vector<int> output1;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output1.push_back(ch);
        if (output1.size() > 1000) break;
    }

    // Rewind and read again
    EXPECT_TRUE(encoder.reset());

    std::vector<int> output2;
    while ((ch = encoder.getChar()) != EOF) {
        output2.push_back(ch);
        if (output2.size() > 1000) break;
    }

    EXPECT_EQ(output1, output2);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, SingleByteInput_221) {
    char* buf = new char[1];
    buf[0] = 0x99;
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 1, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128); // EOD marker
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, AlternatingBytes_221) {
    // Alternating bytes - no runs, should use literal encoding
    char* buf = new char[6];
    for (int i = 0; i < 6; i++) {
        buf[i] = (i % 2 == 0) ? 0xAA : 0xBB;
    }
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 6, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, LargeRunOf128Bytes_221) {
    // 128 identical bytes - maximum run length for RLE
    const int len = 128;
    char* buf = new char[len];
    memset(buf, 0x77, len);
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128); // EOD
    // A run of 128: length code = 257 - 128 = 129, then the byte
    EXPECT_EQ(output[0], 129);
    EXPECT_EQ(output[1], 0x77);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, LargeRunExceeding128Bytes_221) {
    // 200 identical bytes - should be split into multiple runs
    const int len = 200;
    char* buf = new char[len];
    memset(buf, 0x33, len);
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, len, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 2000) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128); // EOD
    // First run: 128 bytes => code 129, byte 0x33
    EXPECT_EQ(output[0], 129);
    EXPECT_EQ(output[1], 0x33);
    // Second run: 72 bytes => code 257-72 = 185, byte 0x33
    EXPECT_EQ(output[2], 185);
    EXPECT_EQ(output[3], 0x33);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, MixedRunsAndLiterals_221) {
    // Mix: 5 distinct bytes followed by 5 identical bytes
    char* buf = new char[10];
    buf[0] = 1; buf[1] = 2; buf[2] = 3; buf[3] = 4; buf[4] = 5;
    buf[5] = 0xAA; buf[6] = 0xAA; buf[7] = 0xAA; buf[8] = 0xAA; buf[9] = 0xAA;
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 10, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128); // EOD
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, GetCharReturnsUnsignedValues_221) {
    // Ensure getChar returns values in 0-255 range (unsigned)
    char* buf = new char[3];
    buf[0] = (char)0xFF;
    buf[1] = (char)0x80;
    buf[2] = (char)0x00;
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 3, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    // All non-EOF values should be in [0, 255]
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
    }
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, ConsecutiveEOFCalls_221) {
    char* buf = new char[1];
    buf[0] = 'X';
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 1, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    // Exhaust the stream
    while (encoder.getChar() != EOF) {}

    // Multiple EOF calls should consistently return EOF
    EXPECT_EQ(encoder.getChar(), EOF);
    EXPECT_EQ(encoder.getChar(), EOF);
    EXPECT_EQ(encoder.getChar(), EOF);
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, TwoByteSameInput_221) {
    // Two identical bytes
    char* buf = new char[2];
    buf[0] = 0x42;
    buf[1] = 0x42;
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 2, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 100) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128); // EOD marker
    delete[] buf;
}

TEST_F(RunLengthEncoderTest_221, TwoByteDifferentInput_221) {
    // Two different bytes
    char* buf = new char[2];
    buf[0] = 0x42;
    buf[1] = 0x43;
    Object dictObj;
    auto memStream = std::make_unique<MemStream>(buf, 0, 2, std::move(dictObj));
    RunLengthEncoder encoder(memStream.get());
    encoder.reset();

    std::vector<int> output;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 100) break;
    }

    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.back(), 128); // EOD marker
    delete[] buf;
}
