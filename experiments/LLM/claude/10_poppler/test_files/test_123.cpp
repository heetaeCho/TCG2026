#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// Since Stream is abstract with many pure virtual methods, we need a concrete
// subclass for testing. We'll create a minimal test double that only overrides
// what's needed to instantiate.
class ConcreteTestStream : public Stream {
public:
    ConcreteTestStream() : Stream() {}
    ~ConcreteTestStream() override {}

    StreamKind getKind() const override { return streamFile; }
    void close() override {}
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    int getRawChar() override { return EOF; }
    void getRawChars(int nChars, int *buffer) override {}
    int getUnfilteredChar() override { return EOF; }
    bool unfilteredRewind() override { return false; }
    Goffset getPos() override { return 0; }
    void setPos(Goffset pos, int dir) override {}
    bool isBinary(bool last) const override { return false; }
    BaseStream *getBaseStream() override { return nullptr; }
    Stream *getUndecodedStream() override { return this; }
    Dict *getDict() override { return nullptr; }
    Object *getDictObject() override { return nullptr; }
    bool rewind() override { return true; }
};

// Test fixture
class StreamTest_123 : public ::testing::Test {
protected:
    void SetUp() override {
        stream = std::make_unique<ConcreteTestStream>();
    }

    void TearDown() override {
        stream.reset();
    }

    std::unique_ptr<ConcreteTestStream> stream;
};

// Test that isEncoder returns false by default for base Stream
TEST_F(StreamTest_123, IsEncoderReturnsFalseByDefault_123) {
    EXPECT_FALSE(stream->isEncoder());
}

// Test that getChar returns EOF for our concrete implementation
TEST_F(StreamTest_123, GetCharReturnsEOF_123) {
    EXPECT_EQ(stream->getChar(), EOF);
}

// Test that lookChar returns EOF for our concrete implementation
TEST_F(StreamTest_123, LookCharReturnsEOF_123) {
    EXPECT_EQ(stream->lookChar(), EOF);
}

// Test that getRawChar returns EOF
TEST_F(StreamTest_123, GetRawCharReturnsEOF_123) {
    EXPECT_EQ(stream->getRawChar(), EOF);
}

// Test that getUnfilteredChar returns EOF
TEST_F(StreamTest_123, GetUnfilteredCharReturnsEOF_123) {
    EXPECT_EQ(stream->getUnfilteredChar(), EOF);
}

// Test that unfilteredRewind returns false for our concrete stream
TEST_F(StreamTest_123, UnfilteredRewindReturnsFalse_123) {
    EXPECT_FALSE(stream->unfilteredRewind());
}

// Test that rewind returns true for our concrete stream
TEST_F(StreamTest_123, RewindReturnsTrue_123) {
    EXPECT_TRUE(stream->rewind());
}

// Test that getPos returns 0 initially
TEST_F(StreamTest_123, GetPosReturnsZero_123) {
    EXPECT_EQ(stream->getPos(), 0);
}

// Test that isBinary returns false
TEST_F(StreamTest_123, IsBinaryReturnsFalse_123) {
    EXPECT_FALSE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
}

// Test that getBaseStream returns nullptr
TEST_F(StreamTest_123, GetBaseStreamReturnsNull_123) {
    EXPECT_EQ(stream->getBaseStream(), nullptr);
}

// Test that getUndecodedStream returns the stream itself
TEST_F(StreamTest_123, GetUndecodedStreamReturnsSelf_123) {
    EXPECT_EQ(stream->getUndecodedStream(), stream.get());
}

// Test that getDict returns nullptr
TEST_F(StreamTest_123, GetDictReturnsNull_123) {
    EXPECT_EQ(stream->getDict(), nullptr);
}

// Test that getDictObject returns nullptr
TEST_F(StreamTest_123, GetDictObjectReturnsNull_123) {
    EXPECT_EQ(stream->getDictObject(), nullptr);
}

// Test that getKind returns the expected kind
TEST_F(StreamTest_123, GetKindReturnsExpected_123) {
    EXPECT_EQ(stream->getKind(), streamFile);
}

// Test getNextStream returns nullptr by default (base implementation)
TEST_F(StreamTest_123, GetNextStreamReturnsNull_123) {
    EXPECT_EQ(stream->getNextStream(), nullptr);
}

// Test discardChars - should be able to call with 0
TEST_F(StreamTest_123, DiscardCharsZero_123) {
    unsigned int discarded = stream->discardChars(0);
    EXPECT_EQ(discarded, 0u);
}

// Test discardChars with a positive number - since getChar returns EOF,
// it should discard 0 characters
TEST_F(StreamTest_123, DiscardCharsWhenEOF_123) {
    unsigned int discarded = stream->discardChars(10);
    EXPECT_EQ(discarded, 0u);
}

// Test getLine when stream is at EOF
TEST_F(StreamTest_123, GetLineAtEOF_123) {
    char buf[256];
    char *result = stream->getLine(buf, sizeof(buf));
    // When at EOF, getLine should return nullptr
    EXPECT_EQ(result, nullptr);
}

// Test doGetChars with 0 chars
TEST_F(StreamTest_123, DoGetCharsZero_123) {
    unsigned char buffer[16];
    int result = stream->doGetChars(0, buffer);
    EXPECT_EQ(result, 0);
}

// Test toUnsignedChars when stream is empty (returns EOF immediately)
TEST_F(StreamTest_123, ToUnsignedCharsEmpty_123) {
    auto result = stream->toUnsignedChars();
    EXPECT_TRUE(result.empty());
}

// Test fillString when stream is empty
TEST_F(StreamTest_123, FillStringEmpty_123) {
    std::string s;
    stream->fillString(s);
    EXPECT_TRUE(s.empty());
}

// Test close doesn't crash
TEST_F(StreamTest_123, CloseDoesNotCrash_123) {
    EXPECT_NO_FATAL_FAILURE(stream->close());
}

// Test setPos doesn't crash
TEST_F(StreamTest_123, SetPosDoesNotCrash_123) {
    EXPECT_NO_FATAL_FAILURE(stream->setPos(0, 0));
    EXPECT_NO_FATAL_FAILURE(stream->setPos(100, 0));
    EXPECT_NO_FATAL_FAILURE(stream->setPos(0, -1));
}

// Test getImageParams with default implementation doesn't crash
TEST_F(StreamTest_123, GetImageParamsDoesNotCrash_123) {
    int bitsPerComponent = 0;
    StreamColorSpaceMode csMode = streamCSNone;
    bool hasAlpha = false;
    EXPECT_NO_FATAL_FAILURE(stream->getImageParams(&bitsPerComponent, &csMode, &hasAlpha));
}

// Test toUnsignedChars with custom initial size
TEST_F(StreamTest_123, ToUnsignedCharsCustomSize_123) {
    auto result = stream->toUnsignedChars(1024, 1024);
    EXPECT_TRUE(result.empty());
}

// Test doGetChars when stream is at EOF
TEST_F(StreamTest_123, DoGetCharsAtEOF_123) {
    unsigned char buffer[64];
    int result = stream->doGetChars(10, buffer);
    // Since getChar returns EOF, no chars should be read
    EXPECT_EQ(result, 0);
}

// Encoder subclass to test isEncoder override
class EncoderTestStream : public ConcreteTestStream {
public:
    bool isEncoder() const override { return true; }
};

TEST_F(StreamTest_123, EncoderStreamReturnsTrue_123) {
    EncoderTestStream encoderStream;
    EXPECT_TRUE(encoderStream.isEncoder());
}

// Test getPSFilter returns empty optional by default
TEST_F(StreamTest_123, GetPSFilterReturnsEmpty_123) {
    auto result = stream->getPSFilter(1, "");
    // Default implementation likely returns nullopt
    EXPECT_FALSE(result.has_value());
}
