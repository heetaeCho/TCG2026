#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FlateEncoder.h"
#include "Stream.h"
#include <cstring>
#include <memory>

// A simple MemStream-based test fixture to feed data into FlateEncoder
class FlateEncoderTest_1651 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a FlateEncoder from a string of bytes
    std::unique_ptr<FlateEncoder> createEncoder(const char *data, int len) {
        // We need to create a MemStream that FlateEncoder can read from.
        // MemStream takes ownership semantics vary; we manage carefully.
        char *buf = new char[len];
        memcpy(buf, data, len);
        Object dictObj;
        auto memStream = new MemStream(buf, 0, len, std::move(dictObj));
        memStream->reset();
        auto encoder = std::make_unique<FlateEncoder>(memStream);
        return encoder;
    }
};

// Test that FlateEncoder returns the correct stream kind
TEST_F(FlateEncoderTest_1651, GetKind_1651) {
    const char data[] = "Hello";
    auto encoder = createEncoder(data, 5);
    StreamKind kind = encoder->getKind();
    EXPECT_EQ(kind, strFlate);
}

// Test that isEncoder returns true
TEST_F(FlateEncoderTest_1651, IsEncoder_1651) {
    const char data[] = "Test";
    auto encoder = createEncoder(data, 4);
    EXPECT_TRUE(encoder->isEncoder());
}

// Test that isBinary returns true (compressed data is binary)
TEST_F(FlateEncoderTest_1651, IsBinary_1651) {
    const char data[] = "Binary test";
    auto encoder = createEncoder(data, 11);
    EXPECT_TRUE(encoder->isBinary());
    EXPECT_TRUE(encoder->isBinary(true));
    EXPECT_TRUE(encoder->isBinary(false));
}

// Test that getPSFilter returns empty optional (encoders typically don't support PS filters)
TEST_F(FlateEncoderTest_1651, GetPSFilter_1651) {
    const char data[] = "PS filter test";
    auto encoder = createEncoder(data, 14);
    auto result = encoder->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that lookChar does not consume the character (peeking behavior)
TEST_F(FlateEncoderTest_1651, LookCharDoesNotConsume_1651) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, 13);
    
    int first = encoder->lookChar();
    EXPECT_NE(first, EOF);
    
    int second = encoder->lookChar();
    EXPECT_EQ(first, second);
}

// Test that getChar returns the same value as lookChar and advances
TEST_F(FlateEncoderTest_1651, GetCharAdvances_1651) {
    const char data[] = "ABCDEF";
    auto encoder = createEncoder(data, 6);
    
    int peeked = encoder->lookChar();
    EXPECT_NE(peeked, EOF);
    
    int consumed = encoder->getChar();
    EXPECT_EQ(peeked, consumed);
    
    // After getChar, next lookChar should be different (next byte)
    int nextPeeked = encoder->lookChar();
    // It could be different or same depending on compression, but it should be valid
    EXPECT_NE(nextPeeked, EOF); // compressed output should have more than 1 byte
}

// Test reading all compressed data until EOF
TEST_F(FlateEncoderTest_1651, ReadUntilEOF_1651) {
    const char data[] = "Hello, this is a test of FlateEncoder compression.";
    auto encoder = createEncoder(data, static_cast<int>(strlen(data)));
    
    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        // Safety: compressed output shouldn't be unreasonably large
        ASSERT_LT(count, 100000);
    }
    
    // Compressed data should have been produced
    EXPECT_GT(count, 0);
}

// Test that after EOF, lookChar continues to return EOF
TEST_F(FlateEncoderTest_1651, AfterEOFLookCharReturnsEOF_1651) {
    const char data[] = "x";
    auto encoder = createEncoder(data, 1);
    
    // Drain all data
    while (encoder->getChar() != EOF) {
        // consume
    }
    
    EXPECT_EQ(encoder->lookChar(), EOF);
    EXPECT_EQ(encoder->lookChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test with empty input
TEST_F(FlateEncoderTest_1651, EmptyInput_1651) {
    const char data[] = "";
    auto encoder = createEncoder(data, 0);
    
    // Even with empty input, zlib may produce header/trailer bytes
    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
        ASSERT_LT(count, 100000);
    }
    // After draining, should get EOF
    EXPECT_EQ(encoder->lookChar(), EOF);
}

// Test with single byte input
TEST_F(FlateEncoderTest_1651, SingleByteInput_1651) {
    const char data[] = "A";
    auto encoder = createEncoder(data, 1);
    
    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        ASSERT_LT(count, 100000);
    }
    // Compressed output should exist (at least zlib header)
    EXPECT_GT(count, 0);
}

// Test lookChar returns value in range [0, 255]
TEST_F(FlateEncoderTest_1651, LookCharValueRange_1651) {
    const char data[] = "Some test data for range checking";
    auto encoder = createEncoder(data, static_cast<int>(strlen(data)));
    
    int ch = encoder->lookChar();
    if (ch != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
    }
}

// Test with larger input data
TEST_F(FlateEncoderTest_1651, LargerInput_1651) {
    // Create a larger buffer of repeated data
    std::string largeData(4096, 'X');
    auto encoder = createEncoder(largeData.c_str(), static_cast<int>(largeData.size()));
    
    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
        ASSERT_LT(count, 1000000);
    }
    
    // Compressed highly repetitive data should be smaller than original
    EXPECT_GT(count, 0);
    EXPECT_LT(count, static_cast<int>(largeData.size()));
}

// Test with binary data including null bytes
TEST_F(FlateEncoderTest_1651, BinaryInputWithNulls_1651) {
    char data[256];
    for (int i = 0; i < 256; i++) {
        data[i] = static_cast<char>(i);
    }
    auto encoder = createEncoder(data, 256);
    
    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        ASSERT_LT(count, 100000);
    }
    EXPECT_GT(count, 0);
}

// Test rewind functionality
TEST_F(FlateEncoderTest_1651, Rewind_1651) {
    const char data[] = "Rewind test data";
    auto encoder = createEncoder(data, static_cast<int>(strlen(data)));
    
    // Read some bytes
    std::vector<int> firstRead;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        firstRead.push_back(ch);
    }
    EXPECT_GT(firstRead.size(), 0u);
    
    // Rewind
    bool rewound = encoder->rewind();
    
    if (rewound) {
        // Read again and compare
        std::vector<int> secondRead;
        while ((ch = encoder->getChar()) != EOF) {
            secondRead.push_back(ch);
        }
        EXPECT_EQ(firstRead.size(), secondRead.size());
        for (size_t i = 0; i < std::min(firstRead.size(), secondRead.size()); i++) {
            EXPECT_EQ(firstRead[i], secondRead[i]);
        }
    }
}

// Test alternating lookChar and getChar
TEST_F(FlateEncoderTest_1651, AlternatingLookAndGet_1651) {
    const char data[] = "Alternating peek and consume";
    auto encoder = createEncoder(data, static_cast<int>(strlen(data)));
    
    for (int i = 0; i < 5; i++) {
        int peeked = encoder->lookChar();
        if (peeked == EOF) break;
        
        int consumed = encoder->getChar();
        EXPECT_EQ(peeked, consumed);
    }
}
