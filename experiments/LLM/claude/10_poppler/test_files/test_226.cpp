#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"
#include <memory>
#include <string>
#include <cstring>

// We need a concrete Stream to pass to LZWEncoder.
// MemStream is available in poppler's Stream.h
class LZWEncoderTest_226 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<LZWEncoder> createEncoder(const char* data, int len) {
        // We need to create a MemStream as the underlying stream.
        // MemStream takes ownership concerns vary; we manage buffer lifetime.
        buf_ = std::string(data, len);
        Object dictObj;
        // MemStream(const char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
        auto memStream = new MemStream(buf_.data(), 0, buf_.size(), Object(objNull));
        return std::make_unique<LZWEncoder>(memStream);
    }

    std::string buf_;
};

TEST_F(LZWEncoderTest_226, GetKindReturnsStrWeird_226) {
    auto encoder = createEncoder("hello", 5);
    EXPECT_EQ(encoder->getKind(), strWeird);
}

TEST_F(LZWEncoderTest_226, IsEncoderReturnsTrue_226) {
    auto encoder = createEncoder("test", 4);
    EXPECT_TRUE(encoder->isEncoder());
}

TEST_F(LZWEncoderTest_226, IsBinaryReturnsTrue_226) {
    auto encoder = createEncoder("test", 4);
    EXPECT_TRUE(encoder->isBinary(true));
    EXPECT_TRUE(encoder->isBinary(false));
}

TEST_F(LZWEncoderTest_226, GetPSFilterReturnsNullopt_226) {
    auto encoder = createEncoder("data", 4);
    auto result = encoder->getPSFilter(1, "");
    // LZW encoder likely doesn't have a PS filter representation
    // We just check it doesn't crash; the value may or may not be nullopt
    // Based on typical encoder behavior, it should return nullopt
    EXPECT_FALSE(result.has_value());
}

TEST_F(LZWEncoderTest_226, RewindSucceeds_226) {
    auto encoder = createEncoder("hello", 5);
    EXPECT_TRUE(encoder->rewind());
}

TEST_F(LZWEncoderTest_226, GetCharReturnsValidBytes_226) {
    auto encoder = createEncoder("A", 1);
    // After encoding "A", we should get some bytes (LZW encoded)
    int ch = encoder->getChar();
    // LZW encoding should produce at least one byte
    EXPECT_NE(ch, EOF);
}

TEST_F(LZWEncoderTest_226, LookCharDoesNotConsume_226) {
    auto encoder = createEncoder("hello", 5);
    int first = encoder->lookChar();
    int second = encoder->lookChar();
    // lookChar should return the same value without consuming
    EXPECT_EQ(first, second);
}

TEST_F(LZWEncoderTest_226, LookCharMatchesGetChar_226) {
    auto encoder = createEncoder("hello world", 11);
    int looked = encoder->lookChar();
    int got = encoder->getChar();
    EXPECT_EQ(looked, got);
}

TEST_F(LZWEncoderTest_226, EmptyInputProducesOutput_226) {
    // Even empty input should produce LZW clear code and EOD
    auto encoder = createEncoder("", 0);
    // LZW should still produce at least clear code + EOD code
    int ch = encoder->getChar();
    // Even for empty, LZW encoder produces some bytes (clear + EOD)
    EXPECT_NE(ch, EOF);
}

TEST_F(LZWEncoderTest_226, ReadEntireEncodedStream_226) {
    const char* input = "ABABABABABABABAB";
    auto encoder = createEncoder(input, strlen(input));

    std::vector<unsigned char> encoded;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        encoded.push_back(static_cast<unsigned char>(ch));
        // Safety: LZW should not produce infinite output
        if (encoded.size() > 10000) {
            FAIL() << "Encoded output too large, possible infinite loop";
            break;
        }
    }
    // The encoded data should be non-empty
    EXPECT_GT(encoded.size(), 0u);
}

TEST_F(LZWEncoderTest_226, RewindResetsStream_226) {
    auto encoder = createEncoder("test data", 9);

    // Read some bytes
    std::vector<int> firstRead;
    for (int i = 0; i < 3; i++) {
        firstRead.push_back(encoder->getChar());
    }

    // Rewind
    EXPECT_TRUE(encoder->rewind());

    // Read same bytes again
    std::vector<int> secondRead;
    for (int i = 0; i < 3; i++) {
        secondRead.push_back(encoder->getChar());
    }

    EXPECT_EQ(firstRead, secondRead);
}

TEST_F(LZWEncoderTest_226, LargeInputEncoding_226) {
    // Test with a larger input
    std::string largeInput(1000, 'X');
    auto encoder = createEncoder(largeInput.data(), largeInput.size());

    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
        if (count > 100000) {
            FAIL() << "Too many bytes produced";
            break;
        }
    }
    // Repeated data should compress well
    EXPECT_GT(count, 0);
    EXPECT_LT(count, 1000); // Should compress since it's all the same character
}

TEST_F(LZWEncoderTest_226, AllByteValuesInput_226) {
    // Test with all possible byte values
    std::string allBytes(256, '\0');
    for (int i = 0; i < 256; i++) {
        allBytes[i] = static_cast<char>(i);
    }
    auto encoder = createEncoder(allBytes.data(), allBytes.size());

    int count = 0;
    while (encoder->getChar() != EOF) {
        count++;
        if (count > 100000) {
            FAIL() << "Too many bytes produced";
            break;
        }
    }
    EXPECT_GT(count, 0);
}

TEST_F(LZWEncoderTest_226, SingleByteInput_226) {
    auto encoder = createEncoder("\x00", 1);
    
    std::vector<int> output;
    int ch;
    while ((ch = encoder->getChar()) != EOF) {
        output.push_back(ch);
        if (output.size() > 1000) {
            FAIL() << "Excessive output";
            break;
        }
    }
    EXPECT_GT(output.size(), 0u);
}

TEST_F(LZWEncoderTest_226, MultipleRewinds_226) {
    auto encoder = createEncoder("abc", 3);

    for (int round = 0; round < 3; round++) {
        EXPECT_TRUE(encoder->rewind());
        int first = encoder->getChar();
        EXPECT_NE(first, EOF);
    }
}
