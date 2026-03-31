#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <optional>
#include <string>

#include "JPEG2000Stream.h"
#include "Stream.h"

// We need a concrete Stream to pass to JPXStream's constructor.
// MemStream or a simple mock that satisfies the Stream interface.

class MockStream : public Stream {
public:
    MockStream() { }
    ~MockStream() override { }

    StreamKind getKind() const override { return strWeird; }
    void reset() override { }
    void close() override { }
    int getChar() override { return EOF; }
    int lookChar() override { return EOF; }
    bool isBinary(bool last) override { return false; }
    Goffset getPos() override { return 0; }
    GooString *getPSFilter(int psLevel, const char *indent) { return nullptr; }
    std::optional<std::string> getPSFilter(int psLevel, const char *indent, bool /*unused*/) { return std::nullopt; }
    int getUnfilteredChar() override { return EOF; }
    void unfilteredReset() override { }
    Goffset getStart() override { return 0; }
    BaseStream *getBaseStream() override { return nullptr; }
    Stream *getUndecodedStream() override { return this; }
    Dict *getDict() override { return nullptr; }
};

class JPXStreamTest_1465 : public ::testing::Test {
protected:
    std::unique_ptr<JPXStream> createJPXStream() {
        auto mockStr = std::make_unique<MockStream>();
        return std::make_unique<JPXStream>(std::move(mockStr));
    }
};

// Test that getKind returns strJPX
TEST_F(JPXStreamTest_1465, GetKindReturnsStrJPX_1465) {
    auto stream = createJPXStream();
    EXPECT_EQ(stream->getKind(), strJPX);
}

// Test that getKind returns exactly the enum value 10
TEST_F(JPXStreamTest_1465, GetKindEnumValue_1465) {
    auto stream = createJPXStream();
    EXPECT_EQ(static_cast<int>(stream->getKind()), 10);
}

// Test supportJPXtransparency default value
TEST_F(JPXStreamTest_1465, DefaultJPXTransparencySupport_1465) {
    auto stream = createJPXStream();
    // Default should be some defined value; we test after explicit set
    // Just verify it doesn't crash
    bool val = stream->supportJPXtransparency();
    (void)val;
}

// Test setSupportJPXtransparency to true
TEST_F(JPXStreamTest_1465, SetSupportJPXTransparencyTrue_1465) {
    auto stream = createJPXStream();
    stream->setSupportJPXtransparency(true);
    EXPECT_TRUE(stream->supportJPXtransparency());
}

// Test setSupportJPXtransparency to false
TEST_F(JPXStreamTest_1465, SetSupportJPXTransparencyFalse_1465) {
    auto stream = createJPXStream();
    stream->setSupportJPXtransparency(false);
    EXPECT_FALSE(stream->supportJPXtransparency());
}

// Test toggling transparency support
TEST_F(JPXStreamTest_1465, ToggleJPXTransparencySupport_1465) {
    auto stream = createJPXStream();
    stream->setSupportJPXtransparency(true);
    EXPECT_TRUE(stream->supportJPXtransparency());
    stream->setSupportJPXtransparency(false);
    EXPECT_FALSE(stream->supportJPXtransparency());
    stream->setSupportJPXtransparency(true);
    EXPECT_TRUE(stream->supportJPXtransparency());
}

// Test isBinary
TEST_F(JPXStreamTest_1465, IsBinaryReturnsTrue_1465) {
    auto stream = createJPXStream();
    EXPECT_TRUE(stream->isBinary(true));
}

// Test getPSFilter returns nullopt for psLevel 1
TEST_F(JPXStreamTest_1465, GetPSFilterReturnsNullopt_1465) {
    auto stream = createJPXStream();
    auto result = stream->getPSFilter(1, "");
    EXPECT_EQ(result, std::nullopt);
}

// Test getChar on empty/uninitialized stream returns EOF
TEST_F(JPXStreamTest_1465, GetCharOnEmptyStream_1465) {
    auto stream = createJPXStream();
    int ch = stream->getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar on empty/uninitialized stream returns EOF
TEST_F(JPXStreamTest_1465, LookCharOnEmptyStream_1465) {
    auto stream = createJPXStream();
    int ch = stream->lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test readStream with zero chars
TEST_F(JPXStreamTest_1465, ReadStreamZeroChars_1465) {
    auto stream = createJPXStream();
    unsigned char buffer[1];
    int result = stream->readStream(0, buffer);
    EXPECT_EQ(result, 0);
}

// Test readStream with buffer on empty stream
TEST_F(JPXStreamTest_1465, ReadStreamOnEmptyStream_1465) {
    auto stream = createJPXStream();
    unsigned char buffer[256] = {};
    int result = stream->readStream(256, buffer);
    // On an empty mock stream, should return 0 or EOF-equivalent
    EXPECT_GE(result, 0);
}

// Test close doesn't crash
TEST_F(JPXStreamTest_1465, CloseDoesNotCrash_1465) {
    auto stream = createJPXStream();
    EXPECT_NO_THROW(stream->close());
}

// Test rewind on empty stream
TEST_F(JPXStreamTest_1465, RewindOnEmptyStream_1465) {
    auto stream = createJPXStream();
    // rewind should not crash
    bool result = stream->rewind();
    (void)result;
}

// Test getPos
TEST_F(JPXStreamTest_1465, GetPosOnFreshStream_1465) {
    auto stream = createJPXStream();
    Goffset pos = stream->getPos();
    EXPECT_GE(pos, 0);
}

// Test getImageParams doesn't crash
TEST_F(JPXStreamTest_1465, GetImageParamsDoesNotCrash_1465) {
    auto stream = createJPXStream();
    int bitsPerComponent = 0;
    StreamColorSpaceMode csMode = streamCSNone;
    bool hasAlpha = false;
    EXPECT_NO_THROW(stream->getImageParams(&bitsPerComponent, &csMode, &hasAlpha));
}

// Test that copy constructor is deleted (compile-time check, but we verify the type trait)
TEST_F(JPXStreamTest_1465, CopyConstructorIsDeleted_1465) {
    EXPECT_FALSE(std::is_copy_constructible<JPXStream>::value);
}

// Test that copy assignment is deleted
TEST_F(JPXStreamTest_1465, CopyAssignmentIsDeleted_1465) {
    EXPECT_FALSE(std::is_copy_assignable<JPXStream>::value);
}
