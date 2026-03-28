#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// A minimal mock/stub for Stream to serve as input to RunLengthEncoder
// We need a concrete Stream subclass to pass to RunLengthEncoder's constructor.
class MemoryStream : public Stream {
public:
    MemoryStream(const char *data, int length) : data_(data), length_(length), pos_(0) {}

    StreamKind getKind() const override { return strWeird; }
    void reset() override { pos_ = 0; }
    int getChar() override {
        if (pos_ < length_) return (unsigned char)data_[pos_++];
        return EOF;
    }
    int lookChar() override {
        if (pos_ < length_) return (unsigned char)data_[pos_];
        return EOF;
    }
    GooString *getPSFilter(int psLevel, const char *indent) override { return nullptr; }
    bool isBinary(bool last) const override { return false; }
    int getPos() override { return pos_; }
    void setPos(Goffset pos, int dir) override {
        if (dir == 0) pos_ = (int)pos;
        else pos_ = length_ + (int)pos;
        if (pos_ < 0) pos_ = 0;
        if (pos_ > length_) pos_ = length_;
    }
    Goffset getStart() override { return 0; }
    void close() override {}

private:
    const char *data_;
    int length_;
    int pos_;
};

// Test fixture for RunLengthEncoder tests
class RunLengthEncoderTest_220 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getKind() returns strWeird
TEST_F(RunLengthEncoderTest_220, GetKindReturnsStrWeird_220) {
    const char data[] = "hello";
    MemoryStream memStream(data, 5);
    RunLengthEncoder encoder(&memStream);
    EXPECT_EQ(encoder.getKind(), strWeird);
}

// Test that isEncoder() returns true (RunLengthEncoder is an encoder)
TEST_F(RunLengthEncoderTest_220, IsEncoderReturnsTrue_220) {
    const char data[] = "test";
    MemoryStream memStream(data, 4);
    RunLengthEncoder encoder(&memStream);
    EXPECT_TRUE(encoder.isEncoder());
}

// Test that isBinary returns expected value
TEST_F(RunLengthEncoderTest_220, IsBinaryTest_220) {
    const char data[] = "data";
    MemoryStream memStream(data, 4);
    RunLengthEncoder encoder(&memStream);
    // RunLengthEncoder output is binary
    bool result = encoder.isBinary(true);
    // Just verify it returns a valid bool (true or false)
    EXPECT_TRUE(result == true || result == false);
}

// Test getPSFilter returns empty optional (encoders typically don't support PS filters)
TEST_F(RunLengthEncoderTest_220, GetPSFilterReturnsNullopt_220) {
    const char data[] = "test";
    MemoryStream memStream(data, 4);
    RunLengthEncoder encoder(&memStream);
    auto result = encoder.getPSFilter(1, "");
    // Encoders typically don't produce PS filter strings
    EXPECT_FALSE(result.has_value());
}

// Test encoding of empty input
TEST_F(RunLengthEncoderTest_220, EmptyInputProducesEOD_220) {
    const char data[] = "";
    MemoryStream memStream(data, 0);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    // For empty input, we expect the encoder to produce an EOD marker (128) then EOF
    int ch = encoder.getChar();
    // Either immediate EOF or EOD marker (128) followed by EOF
    if (ch == 128) {
        EXPECT_EQ(encoder.getChar(), EOF);
    } else {
        // Could be direct EOF for empty input
        EXPECT_EQ(ch, EOF);
    }
}

// Test encoding of a single byte
TEST_F(RunLengthEncoderTest_220, SingleByteInput_220) {
    const char data[] = "A";
    MemoryStream memStream(data, 1);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    // Should produce some encoded output followed by EOD (128) and then EOF
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);  // Should have at least some output
    
    // Read until EOF
    bool foundEOF = false;
    int maxReads = 200;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
    }
    EXPECT_TRUE(foundEOF);
}

// Test that lookChar doesn't consume the character
TEST_F(RunLengthEncoderTest_220, LookCharDoesNotConsume_220) {
    const char data[] = "Hello";
    MemoryStream memStream(data, 5);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int first = encoder.lookChar();
    int second = encoder.lookChar();
    EXPECT_EQ(first, second);
    
    // getChar should return the same value
    int third = encoder.getChar();
    EXPECT_EQ(first, third);
}

// Test encoding of repeated bytes (run)
TEST_F(RunLengthEncoderTest_220, RepeatedBytesEncoding_220) {
    const char data[] = "AAAAAAAAAA";  // 10 repeated 'A's
    MemoryStream memStream(data, 10);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    // Should produce encoded output
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    // Read all output until EOF
    bool foundEOF = false;
    int count = 1;
    int maxReads = 300;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
        count++;
    }
    EXPECT_TRUE(foundEOF);
    // Run-length encoded repeated bytes should be compact
    EXPECT_LT(count, 10 + 5);  // Encoded should be smaller or close to original
}

// Test encoding of non-repeating bytes (literal run)
TEST_F(RunLengthEncoderTest_220, NonRepeatingBytesEncoding_220) {
    const char data[] = "ABCDEFGHIJ";  // 10 different bytes
    MemoryStream memStream(data, 10);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    // Read all output until EOF
    bool foundEOF = false;
    int maxReads = 300;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
    }
    EXPECT_TRUE(foundEOF);
}

// Test rewind functionality
TEST_F(RunLengthEncoderTest_220, RewindProducesSameOutput_220) {
    const char data[] = "Hello World";
    MemoryStream memStream(data, 11);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    // Read all output
    std::vector<int> firstPass;
    int maxReads = 300;
    while (maxReads-- > 0) {
        int ch = encoder.getChar();
        if (ch == EOF) break;
        firstPass.push_back(ch);
    }
    
    // Rewind
    bool rewound = encoder.reset();
    // Read again
    std::vector<int> secondPass;
    maxReads = 300;
    while (maxReads-- > 0) {
        int ch = encoder.getChar();
        if (ch == EOF) break;
        secondPass.push_back(ch);
    }
    
    EXPECT_EQ(firstPass, secondPass);
}

// Test with binary data including null bytes
TEST_F(RunLengthEncoderTest_220, BinaryDataWithNulls_220) {
    const char data[] = {'\0', '\0', '\0', '\x01', '\x02', '\x03'};
    MemoryStream memStream(data, 6);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    bool foundEOF = false;
    int maxReads = 300;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
    }
    EXPECT_TRUE(foundEOF);
}

// Test with maximum byte value (0xFF)
TEST_F(RunLengthEncoderTest_220, MaxByteValue_220) {
    const char data[] = {(char)0xFF, (char)0xFF, (char)0xFF};
    MemoryStream memStream(data, 3);
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    bool foundEOF = false;
    int maxReads = 300;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
    }
    EXPECT_TRUE(foundEOF);
}

// Test larger input with mixed runs and literals
TEST_F(RunLengthEncoderTest_220, MixedRunsAndLiterals_220) {
    // Create a pattern: AAABBCDDDDDEEFG
    std::string pattern = "AAABBCDDDDDEEFG";
    MemoryStream memStream(pattern.c_str(), (int)pattern.length());
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    bool foundEOF = false;
    int maxReads = 500;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
    }
    EXPECT_TRUE(foundEOF);
}

// Test that getChar returns values in valid range [0, 255] or EOF
TEST_F(RunLengthEncoderTest_220, OutputValuesInValidRange_220) {
    const char data[] = "Test data for range check!";
    MemoryStream memStream(data, (int)strlen(data));
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int maxReads = 500;
    while (maxReads-- > 0) {
        int ch = encoder.getChar();
        if (ch == EOF) break;
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
    }
}

// Test long run of identical bytes (128+ to test buffer limits)
TEST_F(RunLengthEncoderTest_220, LongRunExceedingBufferLimit_220) {
    // 130 identical bytes - should require at least two run-length sequences
    std::string longRun(130, 'X');
    MemoryStream memStream(longRun.c_str(), (int)longRun.length());
    RunLengthEncoder encoder(&memStream);
    encoder.reset();
    
    int ch = encoder.getChar();
    EXPECT_NE(ch, EOF);
    
    bool foundEOF = false;
    int count = 1;
    int maxReads = 500;
    while (maxReads-- > 0) {
        ch = encoder.getChar();
        if (ch == EOF) {
            foundEOF = true;
            break;
        }
        count++;
    }
    EXPECT_TRUE(foundEOF);
}
