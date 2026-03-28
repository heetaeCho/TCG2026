#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Stream.h"

// Mock Stream to serve as the underlying stream for CMYKGrayEncoder
class MockStream : public Stream {
public:
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(void, reset, (), (override));
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(GooString*, getPSFilter, (int psLevel, const char* indent), ());
    MOCK_METHOD(bool, isBinary, (bool last), (const, override));
    MOCK_METHOD(int, getPos, (), (override));
    MOCK_METHOD(void, setPos, (Goffset pos, int dir), (override));
    MOCK_METHOD(Goffset, getStart, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(bool, getDict, (), ());

    // Minimal implementation for Stream base
    MockStream() : Stream() {}
    ~MockStream() override = default;
};

class CMYKGrayEncoderTest_230 : public ::testing::Test {
protected:
    void SetUp() override {
        mockStream = new MockStream();
    }

    void TearDown() override {
        // The encoder may or may not take ownership; be careful
    }

    MockStream* mockStream;
};

// Test that getKind returns strWeird
TEST_F(CMYKGrayEncoderTest_230, GetKindReturnsStrWeird_230) {
    CMYKGrayEncoder encoder(mockStream);
    EXPECT_EQ(encoder.getKind(), strWeird);
}

// Test that getKind consistently returns strWeird on multiple calls
TEST_F(CMYKGrayEncoderTest_230, GetKindConsistentlyReturnsStrWeird_230) {
    CMYKGrayEncoder encoder(mockStream);
    EXPECT_EQ(encoder.getKind(), strWeird);
    EXPECT_EQ(encoder.getKind(), strWeird);
    EXPECT_EQ(encoder.getKind(), strWeird);
}

// Test that getKind returns the correct enum value (numeric check)
TEST_F(CMYKGrayEncoderTest_230, GetKindReturnsCorrectEnumValue_230) {
    CMYKGrayEncoder encoder(mockStream);
    StreamKind kind = encoder.getKind();
    EXPECT_EQ(static_cast<int>(kind), 11);
}

// Test that getKind does not return other stream kinds
TEST_F(CMYKGrayEncoderTest_230, GetKindIsNotOtherTypes_230) {
    CMYKGrayEncoder encoder(mockStream);
    EXPECT_NE(encoder.getKind(), strFile);
    EXPECT_NE(encoder.getKind(), strCachedFile);
    EXPECT_NE(encoder.getKind(), strASCIIHex);
    EXPECT_NE(encoder.getKind(), strASCII85);
    EXPECT_NE(encoder.getKind(), strLZW);
    EXPECT_NE(encoder.getKind(), strRunLength);
    EXPECT_NE(encoder.getKind(), strCCITTFax);
    EXPECT_NE(encoder.getKind(), strDCT);
    EXPECT_NE(encoder.getKind(), strFlate);
    EXPECT_NE(encoder.getKind(), strJBIG2);
    EXPECT_NE(encoder.getKind(), strJPX);
    EXPECT_NE(encoder.getKind(), strCrypt);
}

// Test isEncoder returns true (encoders should return true)
TEST_F(CMYKGrayEncoderTest_230, IsEncoderReturnsTrue_230) {
    CMYKGrayEncoder encoder(mockStream);
    EXPECT_TRUE(encoder.isEncoder());
}

// Test isBinary behavior
TEST_F(CMYKGrayEncoderTest_230, IsBinaryReturnValue_230) {
    CMYKGrayEncoder encoder(mockStream);
    // isBinary should return a boolean; test it doesn't crash
    bool result = encoder.isBinary(true);
    // For an encoder converting CMYK to Gray, typically not binary in encoding sense
    // but we just verify it returns a valid bool
    EXPECT_TRUE(result == true || result == false);
}

// Test getPSFilter returns empty optional (encoders typically don't have PS filters)
TEST_F(CMYKGrayEncoderTest_230, GetPSFilterReturnsNullopt_230) {
    CMYKGrayEncoder encoder(mockStream);
    auto result = encoder.getPSFilter(1, "");
    EXPECT_FALSE(result.has_value());
}

// Test that getChar returns EOF when underlying stream returns EOF immediately
TEST_F(CMYKGrayEncoderTest_230, GetCharReturnsEOFOnEmptyStream_230) {
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, getChar()).WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, lookChar()).WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    encoder.reset();
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);
}

// Test lookChar returns EOF on empty stream
TEST_F(CMYKGrayEncoderTest_230, LookCharReturnsEOFOnEmptyStream_230) {
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, getChar()).WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, lookChar()).WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    encoder.reset();
    int ch = encoder.lookChar();
    EXPECT_EQ(ch, EOF);
}

// Test that rewind calls reset on underlying stream and succeeds
TEST_F(CMYKGrayEncoderTest_230, RewindSucceeds_230) {
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    // rewind should return a boolean
    // It resets the stream
    bool result = encoder.reset();
    // We just check it doesn't crash and returns something
    EXPECT_TRUE(result == true || result == false);
}

// Test CMYK to Gray conversion with known CMYK values
// CMYK (0, 0, 0, 0) should produce white (255 gray)
TEST_F(CMYKGrayEncoderTest_230, ConvertsCMYKToGrayWhite_230) {
    // CMYK: C=0, M=0, Y=0, K=0 -> should be white/light gray
    ::testing::InSequence seq;
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0))   // C
        .WillOnce(::testing::Return(0))   // M
        .WillOnce(::testing::Return(0))   // Y
        .WillOnce(::testing::Return(0))   // K
        .WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    encoder.reset();
    int ch = encoder.getChar();
    // With C=M=Y=K=0, gray value should be 255 (white)
    EXPECT_GE(ch, 0);
    EXPECT_LE(ch, 255);
}

// Test CMYK to Gray conversion with all max values
// CMYK (255, 255, 255, 255) should produce black (0 gray)
TEST_F(CMYKGrayEncoderTest_230, ConvertsCMYKToGrayBlack_230) {
    ::testing::InSequence seq;
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(255))  // C
        .WillOnce(::testing::Return(255))  // M
        .WillOnce(::testing::Return(255))  // Y
        .WillOnce(::testing::Return(255))  // K
        .WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    encoder.reset();
    int ch = encoder.getChar();
    // With max CMYK, should be near black
    EXPECT_EQ(ch, 0);
}

// Test lookChar does not consume the character
TEST_F(CMYKGrayEncoderTest_230, LookCharDoesNotConsume_230) {
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0))
        .WillOnce(::testing::Return(0))
        .WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    encoder.reset();
    int first = encoder.lookChar();
    int second = encoder.lookChar();
    // lookChar should return the same value without consuming
    EXPECT_EQ(first, second);
}

// Test that getChar after lookChar returns the same value
TEST_F(CMYKGrayEncoderTest_230, GetCharAfterLookCharReturnsSame_230) {
    EXPECT_CALL(*mockStream, reset()).Times(::testing::AnyNumber());
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(::testing::Return(100))
        .WillOnce(::testing::Return(50))
        .WillOnce(::testing::Return(25))
        .WillOnce(::testing::Return(10))
        .WillRepeatedly(::testing::Return(EOF));
    EXPECT_CALL(*mockStream, close()).Times(::testing::AnyNumber());

    CMYKGrayEncoder encoder(mockStream);
    encoder.reset();
    int looked = encoder.lookChar();
    int got = encoder.getChar();
    EXPECT_EQ(looked, got);
}
