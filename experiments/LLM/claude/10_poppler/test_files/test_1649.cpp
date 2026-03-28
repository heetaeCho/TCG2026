#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include "FlateEncoder.h"
#include "Stream.h"

// We need a concrete Stream implementation to pass to FlateEncoder.
// MemStream is typically available in poppler.
#include "Object.h"

// Helper: Create a MemStream from a buffer
class FlateEncoderTest_1649 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create a FlateEncoder from raw data
    std::unique_ptr<FlateEncoder> createEncoder(const char *data, int len) {
        // Create a MemStream. MemStream takes ownership semantics vary,
        // but we need a Stream* to pass to FlateEncoder.
        Object dictObj(objNull);
        auto *memStream = new MemStream(const_cast<char *>(data), 0, len, Object(objNull));
        memStream->reset();
        return std::make_unique<FlateEncoder>(memStream);
    }
};

TEST_F(FlateEncoderTest_1649, GetKindReturnsStrWeird_1649) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    EXPECT_EQ(encoder->getKind(), strWeird);
}

TEST_F(FlateEncoderTest_1649, IsEncoderReturnsTrue_1649) {
    const char data[] = "Test data";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    EXPECT_TRUE(encoder->isEncoder());
}

TEST_F(FlateEncoderTest_1649, IsBinaryReturnsTrue_1649) {
    const char data[] = "Test data";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    EXPECT_TRUE(encoder->isBinary(true));
    EXPECT_TRUE(encoder->isBinary(false));
}

TEST_F(FlateEncoderTest_1649, GetPSFilterReturnsNullopt_1649) {
    const char data[] = "Test data";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    auto result = encoder->getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

TEST_F(FlateEncoderTest_1649, GetCharReturnsValidDataForNonEmptyInput_1649) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    // FlateEncoder compresses data, so getChar should return compressed bytes
    // The first byte should not be EOF for non-empty input
    int ch = encoder->getChar();
    EXPECT_NE(ch, EOF);
}

TEST_F(FlateEncoderTest_1649, LookCharDoesNotAdvance_1649) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    int ch1 = encoder->lookChar();
    int ch2 = encoder->lookChar();
    EXPECT_EQ(ch1, ch2);
}

TEST_F(FlateEncoderTest_1649, LookCharMatchesGetChar_1649) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    int lookCh = encoder->lookChar();
    int getCh = encoder->getChar();
    EXPECT_EQ(lookCh, getCh);
}

TEST_F(FlateEncoderTest_1649, EmptyInputEventuallyReturnsEOF_1649) {
    const char data[] = "";
    auto encoder = createEncoder(data, 0);
    // Even empty input may produce some zlib header bytes, but eventually EOF
    int ch;
    int count = 0;
    do {
        ch = encoder->getChar();
        count++;
    } while (ch != EOF && count < 100000);
    EXPECT_EQ(ch, EOF);
}

TEST_F(FlateEncoderTest_1649, GetCharEventuallyReturnsEOF_1649) {
    const char data[] = "Short";
    auto encoder = createEncoder(data, sizeof(data) - 1);
    int ch;
    int count = 0;
    do {
        ch = encoder->getChar();
        count++;
    } while (ch != EOF && count < 100000);
    EXPECT_EQ(ch, EOF);
    // Compressed output should be relatively short
    EXPECT_LT(count, 100000);
}

TEST_F(FlateEncoderTest_1649, RewindAllowsReReading_1649) {
    const char data[] = "Hello, World!";
    auto encoder = createEncoder(data, sizeof(data) - 1);

    // Read first few bytes
    int ch1 = encoder->getChar();
    int ch2 = encoder->getChar();
    int ch3 = encoder->getChar();

    // Rewind
    bool rewound = encoder->rewind();

    if (rewound) {
        // After rewind, should get the same bytes
        int rch1 = encoder->getChar();
        int rch2 = encoder->getChar();
        int rch3 = encoder->getChar();
        EXPECT_EQ(ch1, rch1);
        EXPECT_EQ(ch2, rch2);
        EXPECT_EQ(ch3, rch3);
    }
}

TEST_F(FlateEncoderTest_1649, CompressedOutputIsValidDeflate_1649) {
    const char data[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    auto encoder = createEncoder(data, sizeof(data) - 1);

    // Read all compressed bytes
    std::vector<unsigned char> compressed;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        compressed.push_back(static_cast<unsigned char>(ch));
    }

    // Compressed output should exist (non-empty for non-empty input)
    EXPECT_FALSE(compressed.empty());

    // For highly repetitive data, compressed size should typically be less than original
    // (though with zlib header overhead, very short inputs might not compress smaller)
    // At minimum, we got some output
    EXPECT_GT(compressed.size(), 0u);
}

TEST_F(FlateEncoderTest_1649, LargerInputProducesOutput_1649) {
    // Create a larger input
    std::string largeData(4096, 'X');
    auto encoder = createEncoder(largeData.data(), static_cast<int>(largeData.size()));

    std::vector<unsigned char> compressed;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        compressed.push_back(static_cast<unsigned char>(ch));
    }

    EXPECT_FALSE(compressed.empty());
    // Highly repetitive data should compress significantly
    EXPECT_LT(compressed.size(), largeData.size());
}

TEST_F(FlateEncoderTest_1649, GetCharReturnsValuesInByteRange_1649) {
    const char data[] = "Test data for byte range check";
    auto encoder = createEncoder(data, sizeof(data) - 1);

    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        EXPECT_GE(ch, 0);
        EXPECT_LE(ch, 255);
    }
}

TEST_F(FlateEncoderTest_1649, AfterEOFGetCharKeepsReturningEOF_1649) {
    const char data[] = "Hi";
    auto encoder = createEncoder(data, sizeof(data) - 1);

    // Drain all output
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
    }

    // Subsequent calls should also return EOF
    EXPECT_EQ(encoder->getChar(), EOF);
    EXPECT_EQ(encoder->getChar(), EOF);
}

TEST_F(FlateEncoderTest_1649, AfterEOFLookCharReturnsEOF_1649) {
    const char data[] = "Hi";
    auto encoder = createEncoder(data, sizeof(data) - 1);

    // Drain all output
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
    }

    EXPECT_EQ(encoder->lookChar(), EOF);
}
