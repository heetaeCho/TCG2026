#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// We need a concrete Stream to pass to ASCIIHexEncoder.
// MemStream or a mock can serve this purpose.
// Based on the poppler codebase, we'll use a minimal approach.

// A simple mock/stub stream for testing
class MockStream : public Stream {
public:
    MockStream() : Stream() {}
    ~MockStream() override = default;

    StreamKind getKind() const override { return strWeird; }
    void reset() override {}
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    GooString *getPSFilter(int /*psLevel*/, const char * /*indent*/) { return nullptr; }
    bool isBinary(bool /*last*/) const override { return false; }
    int getPos() override { return 0; }
    void setPos(Goffset /*pos*/, int /*dir*/) override {}
    Goffset getStart() override { return 0; }
    void moveStart(Goffset /*delta*/) override {}
    std::optional<std::string> getPSFilter(int, const char*) override { return std::nullopt; }
    void close() override {}
    bool open() { return true; }
};

class DataStream : public Stream {
public:
    DataStream(const unsigned char *data, int length) : data_(data), length_(length), pos_(0) {}
    ~DataStream() override = default;

    StreamKind getKind() const override { return strWeird; }
    void reset() override { pos_ = 0; }
    int getChar() override {
        if (pos_ < length_) return data_[pos_++];
        return EOF;
    }
    int lookChar() override {
        if (pos_ < length_) return data_[pos_];
        return EOF;
    }
    int getPos() override { return pos_; }
    void setPos(Goffset pos, int dir) override {
        if (dir >= 0) pos_ = (int)pos;
        else pos_ = length_ + (int)pos;
        if (pos_ < 0) pos_ = 0;
        if (pos_ > length_) pos_ = length_;
    }
    Goffset getStart() override { return 0; }
    void moveStart(Goffset delta) override {}
    std::optional<std::string> getPSFilter(int, const char*) override { return std::nullopt; }
    bool isBinary(bool) const override { return false; }
    void close() override {}

private:
    const unsigned char *data_;
    int length_;
    int pos_;
};

class ASCIIHexEncoderTest_208 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ASCIIHexEncoderTest_208, GetKindReturnsStrWeird_208) {
    MockStream mockStream;
    ASCIIHexEncoder encoder(&mockStream);
    EXPECT_EQ(encoder.getKind(), strWeird);
}

TEST_F(ASCIIHexEncoderTest_208, IsEncoderReturnsTrue_208) {
    MockStream mockStream;
    ASCIIHexEncoder encoder(&mockStream);
    EXPECT_TRUE(encoder.isEncoder());
}

TEST_F(ASCIIHexEncoderTest_208, IsBinaryReturnsFalse_208) {
    MockStream mockStream;
    ASCIIHexEncoder encoder(&mockStream);
    EXPECT_FALSE(encoder.isBinary(true));
    EXPECT_FALSE(encoder.isBinary(false));
}

TEST_F(ASCIIHexEncoderTest_208, GetPSFilterReturnsNullopt_208) {
    MockStream mockStream;
    ASCIIHexEncoder encoder(&mockStream);
    auto result = encoder.getPSFilter(1, "");
    // ASCIIHexEncoder likely returns nullopt for getPSFilter
    EXPECT_EQ(result, std::nullopt);
}

TEST_F(ASCIIHexEncoderTest_208, EmptyStreamReturnsEOF_208) {
    MockStream mockStream;
    ASCIIHexEncoder encoder(&mockStream);
    encoder.reset();
    // Empty stream should eventually return EOF
    // The encoder might return '>' before EOF to signal end
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
}

TEST_F(ASCIIHexEncoderTest_208, EncodesSimpleByte_208) {
    // ASCII hex encoding of byte 0xAB should produce "ab"
    const unsigned char data[] = { 0xAB };
    DataStream dataStream(data, 1);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    std::string result;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        result += (char)ch;
    }

    // The result should contain the hex representation of 0xAB followed by '>'
    // "ab>" or with possible line breaks
    EXPECT_FALSE(result.empty());
    // Should end with '>' to mark end of ASCII hex data
    EXPECT_NE(result.find('>'), std::string::npos);
}

TEST_F(ASCIIHexEncoderTest_208, EncodesZeroByte_208) {
    const unsigned char data[] = { 0x00 };
    DataStream dataStream(data, 1);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    std::string result;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        result += (char)ch;
    }

    // 0x00 should encode as "00>"
    EXPECT_NE(result.find("00"), std::string::npos);
    EXPECT_NE(result.find('>'), std::string::npos);
}

TEST_F(ASCIIHexEncoderTest_208, EncodesFFByte_208) {
    const unsigned char data[] = { 0xFF };
    DataStream dataStream(data, 1);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    std::string result;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        result += (char)ch;
    }

    EXPECT_NE(result.find("ff"), std::string::npos);
}

TEST_F(ASCIIHexEncoderTest_208, EncodesMultipleBytes_208) {
    const unsigned char data[] = { 0x48, 0x65, 0x6C }; // "Hel"
    DataStream dataStream(data, 3);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    std::string result;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        result += (char)ch;
    }

    // Should contain hex for each byte
    EXPECT_NE(result.find("48"), std::string::npos);
    EXPECT_NE(result.find("65"), std::string::npos);
    EXPECT_NE(result.find("6c"), std::string::npos);
    EXPECT_NE(result.find('>'), std::string::npos);
}

TEST_F(ASCIIHexEncoderTest_208, LookCharDoesNotAdvance_208) {
    const unsigned char data[] = { 0xAB };
    DataStream dataStream(data, 1);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    int ch1 = encoder.lookChar();
    int ch2 = encoder.lookChar();
    EXPECT_EQ(ch1, ch2);

    int ch3 = encoder.getChar();
    EXPECT_EQ(ch1, ch3);
}

TEST_F(ASCIIHexEncoderTest_208, RewindResetsEncoder_208) {
    const unsigned char data[] = { 0xDE, 0xAD };
    DataStream dataStream(data, 2);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    // Read all output
    std::string result1;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        result1 += (char)ch;
    }

    // Rewind and read again
    bool rewound = encoder.rewind();
    // rewind may or may not succeed depending on underlying stream
    if (rewound) {
        std::string result2;
        while ((ch = encoder.getChar()) != EOF) {
            result2 += (char)ch;
        }
        EXPECT_EQ(result1, result2);
    }
}

TEST_F(ASCIIHexEncoderTest_208, OutputContainsOnlyValidHexChars_208) {
    const unsigned char data[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF };
    DataStream dataStream(data, 8);
    ASCIIHexEncoder encoder(&dataStream);
    encoder.reset();

    std::string result;
    int ch;
    while ((ch = encoder.getChar()) != EOF) {
        result += (char)ch;
    }

    // All characters should be hex digits [0-9a-f], '>', or '\n' (line breaks)
    for (char c : result) {
        bool valid = (c >= '0' && c <= '9') ||
                     (c >= 'a' && c <= 'f') ||
                     (c >= 'A' && c <= 'F') ||
                     c == '>' || c == '\n' || c == '\r';
        EXPECT_TRUE(valid) << "Invalid character in output: " << (int)c;
    }
}

TEST_F(ASCIIHexEncoderTest_208, GetKindConsistency_208) {
    MockStream mockStream;
    ASCIIHexEncoder encoder(&mockStream);
    // Call multiple times to ensure consistency
    EXPECT_EQ(encoder.getKind(), strWeird);
    EXPECT_EQ(encoder.getKind(), strWeird);
    EXPECT_EQ(encoder.getKind(), strWeird);
}
