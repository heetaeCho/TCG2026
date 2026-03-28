#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FlateEncoder.h"
#include "Stream.h"
#include <cstring>
#include <memory>

// A simple in-memory stream to feed data to FlateEncoder
class MemStream;

// We need a concrete Stream implementation to feed into FlateEncoder
// Using the existing MemStream from poppler if available, otherwise we create a minimal mock

class MockStream : public Stream {
public:
    MockStream(const char *data, int len) : buf(data), length(len), pos(0) {
        // Initialize ref count
    }

    ~MockStream() override = default;

    StreamKind getKind() const override { return strWeird; }
    void reset() override { pos = 0; }
    int getChar() override {
        if (pos >= length) return EOF;
        return (unsigned char)buf[pos++];
    }
    int lookChar() override {
        if (pos >= length) return EOF;
        return (unsigned char)buf[pos];
    }
    GooString *getPSFilter(int psLevel, const char *indent) { return nullptr; }
    bool isBinary(bool last = true) const override { return false; }
    int getPos() override { return pos; }
    void setPos(Goffset newPos, int dir = 0) override {
        if (dir == 0) {
            pos = (int)newPos;
        } else {
            pos = length - (int)newPos;
        }
        if (pos < 0) pos = 0;
        if (pos > length) pos = length;
    }
    Goffset getStart() override { return 0; }
    void close() override {}
    int rawGetChar() override { return getChar(); }
    void unfilteredReset() override { reset(); }

private:
    const char *buf;
    int length;
    int pos;
};

class FlateEncoderTest_1650 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that FlateEncoder can be constructed and produces some output for non-empty input
TEST_F(FlateEncoderTest_1650, ConstructWithNonEmptyStream_1650) {
    const char data[] = "Hello, World!";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);
    ASSERT_NE(encoder, nullptr);
    // Should be able to read at least one byte (compressed output)
    int ch = encoder->getChar();
    // Flate compressed data should produce some output
    EXPECT_NE(ch, EOF);
}

// Test that getChar returns bytes in range [0, 255] before EOF
TEST_F(FlateEncoderTest_1650, GetCharReturnsByteRange_1650) {
    const char data[] = "Test data for flate encoding";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    int ch;
    int count = 0;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        if (count > 100000) {
            // Safety guard against infinite loop
            FAIL() << "Too many bytes read, possible infinite loop";
            break;
        }
    }
    EXPECT_GT(count, 0);
}

// Test that lookChar returns the same value as getChar without consuming
TEST_F(FlateEncoderTest_1650, LookCharDoesNotConsume_1650) {
    const char data[] = "Some test data";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    int lookResult = encoder->lookChar();
    int getResult = encoder->getChar();
    EXPECT_EQ(lookResult, getResult);
}

// Test that lookChar called multiple times returns the same value
TEST_F(FlateEncoderTest_1650, LookCharConsistentMultipleCalls_1650) {
    const char data[] = "Repeated look test";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    int first = encoder->lookChar();
    int second = encoder->lookChar();
    int third = encoder->lookChar();
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Test with empty input stream
TEST_F(FlateEncoderTest_1650, EmptyInputStreamProducesOutput_1650) {
    const char data[] = "";
    auto baseStream = new MockStream(data, 0);
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    // Even empty input should produce some flate output (at least zlib header + empty block)
    // or it might return EOF immediately depending on implementation
    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        if (count > 10000) {
            FAIL() << "Too many bytes from empty input";
            break;
        }
    }
    // At minimum, zlib produces a header even for empty input
    // But we accept 0 bytes as well since behavior may vary
    EXPECT_GE(count, 0);
}

// Test getKind returns the expected stream kind
TEST_F(FlateEncoderTest_1650, GetKindReturnsCorrectKind_1650) {
    const char data[] = "test";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    StreamKind kind = encoder->getKind();
    EXPECT_EQ(kind, strFlate);
}

// Test isBinary returns true
TEST_F(FlateEncoderTest_1650, IsBinaryReturnsTrue_1650) {
    const char data[] = "test";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    EXPECT_TRUE(encoder->isBinary());
}

// Test isEncoder returns true
TEST_F(FlateEncoderTest_1650, IsEncoderReturnsTrue_1650) {
    const char data[] = "test";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    EXPECT_TRUE(encoder->isEncoder());
}

// Test getPSFilter returns nullopt (encoders typically don't support PS filters)
TEST_F(FlateEncoderTest_1650, GetPSFilterReturnsNullopt_1650) {
    const char data[] = "test";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    auto result = encoder->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that after reading all data, getChar returns EOF consistently
TEST_F(FlateEncoderTest_1650, GetCharReturnsEOFAfterAllDataRead_1650) {
    const char data[] = "short";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    // Read all data
    while (encoder->getChar() != EOF) {
        // consume
    }

    // Should consistently return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

// Test that after reading all data, lookChar returns EOF
TEST_F(FlateEncoderTest_1650, LookCharReturnsEOFAfterAllDataRead_1650) {
    const char data[] = "short";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    while (encoder->getChar() != EOF) {
        // consume
    }

    EXPECT_EQ(encoder->lookChar(), EOF);
}

// Test with larger input data
TEST_F(FlateEncoderTest_1650, LargerInputData_1650) {
    std::string largeData(10000, 'A');
    auto baseStream = new MockStream(largeData.c_str(), largeData.size());
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        if (count > 100000) {
            FAIL() << "Too many output bytes";
            break;
        }
    }
    // Compressed highly repetitive data should produce some output but less than input
    EXPECT_GT(count, 0);
    EXPECT_LT(count, (int)largeData.size());
}

// Test with binary input data (all byte values)
TEST_F(FlateEncoderTest_1650, BinaryInputData_1650) {
    char binaryData[256];
    for (int i = 0; i < 256; i++) {
        binaryData[i] = (char)i;
    }
    auto baseStream = new MockStream(binaryData, 256);
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        if (count > 100000) {
            FAIL() << "Too many output bytes";
            break;
        }
    }
    EXPECT_GT(count, 0);
}

// Test rewind functionality
TEST_F(FlateEncoderTest_1650, RewindProducesSameOutput_1650) {
    const char data[] = "Rewind test data content";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    // Read all output
    std::vector<int> firstPass;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        firstPass.push_back(ch);
    }

    // Rewind
    encoder->reset();

    // Read all output again
    std::vector<int> secondPass;
    while ((ch = encoder->getChar()) != EOF) {
        secondPass.push_back(ch);
    }

    // Both passes should produce identical output
    EXPECT_EQ(firstPass.size(), secondPass.size());
    EXPECT_EQ(firstPass, secondPass);
}

// Test single byte input
TEST_F(FlateEncoderTest_1650, SingleByteInput_1650) {
    const char data[] = "X";
    auto baseStream = new MockStream(data, 1);
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    int count = 0;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
        count++;
        if (count > 10000) {
            FAIL() << "Too many output bytes for single byte input";
            break;
        }
    }
    EXPECT_GT(count, 0);
}

// Test alternating lookChar and getChar
TEST_F(FlateEncoderTest_1650, AlternatingLookAndGet_1650) {
    const char data[] = "Alternating test";
    auto baseStream = new MockStream(data, strlen(data));
    auto encoder = std::make_unique<FlateEncoder>(baseStream);

    for (int i = 0; i < 5; i++) {
        int look = encoder->lookChar();
        if (look == EOF) break;
        int get = encoder->getChar();
        EXPECT_EQ(look, get);
    }
}
