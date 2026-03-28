#include <gtest/gtest.h>
#include "Stream.h"

// We need a concrete Stream to pass to FixedLengthEncoder.
// MemStream is available in poppler's Stream.h
#include <cstring>

class FixedLengthEncoderTest_205 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a MemStream with given data
    MemStream* createMemStream(const char* data, int len) {
        // MemStream takes ownership-ish of the buffer pointer but we need it to persist
        char* buf = new char[len];
        memcpy(buf, data, len);
        Object obj;
        return new MemStream(buf, 0, len, Object(objNull));
    }
};

TEST_F(FixedLengthEncoderTest_205, GetKindReturnsStrWeird_205) {
    const char* data = "Hello World";
    int len = strlen(data);
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);

    EXPECT_EQ(encoder.getKind(), strWeird);

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, IsEncoderReturnsTrue_205) {
    const char* data = "Test";
    int len = strlen(data);
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);

    EXPECT_TRUE(encoder.isEncoder());

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, GetCharReturnsCorrectChars_205) {
    const char* data = "ABC";
    int len = 3;
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);
    encoder.rewind();

    EXPECT_EQ(encoder.getChar(), 'A');
    EXPECT_EQ(encoder.getChar(), 'B');
    EXPECT_EQ(encoder.getChar(), 'C');
    EXPECT_EQ(encoder.getChar(), EOF);

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, LookCharDoesNotAdvance_205) {
    const char* data = "XY";
    int len = 2;
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);
    encoder.rewind();

    int ch1 = encoder.lookChar();
    int ch2 = encoder.lookChar();
    EXPECT_EQ(ch1, 'X');
    EXPECT_EQ(ch2, 'X');

    // Now consume it
    int ch3 = encoder.getChar();
    EXPECT_EQ(ch3, 'X');

    int ch4 = encoder.lookChar();
    EXPECT_EQ(ch4, 'Y');

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, ZeroLengthReturnsEOFImmediately_205) {
    const char* data = "Hello";
    int len = strlen(data);
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, 0);
    encoder.rewind();

    EXPECT_EQ(encoder.getChar(), EOF);
    EXPECT_EQ(encoder.lookChar(), EOF);

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, LengthShorterThanStream_205) {
    const char* data = "ABCDEFGH";
    int dataLen = strlen(data);
    int encodeLen = 3;
    MemStream* memStr = createMemStream(data, dataLen);
    FixedLengthEncoder encoder(memStr, encodeLen);
    encoder.rewind();

    EXPECT_EQ(encoder.getChar(), 'A');
    EXPECT_EQ(encoder.getChar(), 'B');
    EXPECT_EQ(encoder.getChar(), 'C');
    EXPECT_EQ(encoder.getChar(), EOF);

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, RewindResetsPosition_205) {
    const char* data = "AB";
    int len = 2;
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);
    encoder.rewind();

    EXPECT_EQ(encoder.getChar(), 'A');
    EXPECT_EQ(encoder.getChar(), 'B');
    EXPECT_EQ(encoder.getChar(), EOF);

    // Rewind and read again
    encoder.rewind();
    EXPECT_EQ(encoder.getChar(), 'A');
    EXPECT_EQ(encoder.getChar(), 'B');
    EXPECT_EQ(encoder.getChar(), EOF);

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, IsBinaryReturnsFalse_205) {
    const char* data = "Test";
    int len = strlen(data);
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);

    // isBinary typically returns false for encoders
    EXPECT_FALSE(encoder.isBinary(true));
    EXPECT_FALSE(encoder.isBinary(false));

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, SingleCharStream_205) {
    const char* data = "Z";
    int len = 1;
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);
    encoder.rewind();

    EXPECT_EQ(encoder.lookChar(), 'Z');
    EXPECT_EQ(encoder.getChar(), 'Z');
    EXPECT_EQ(encoder.getChar(), EOF);

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, GetPSFilterReturnsNullopt_205) {
    const char* data = "Test";
    int len = strlen(data);
    MemStream* memStr = createMemStream(data, len);
    FixedLengthEncoder encoder(memStr, len);

    // Encoders typically don't have PS filters
    auto result = encoder.getPSFilter(1, "");
    // It's expected to return nullopt or empty for weird/encoder streams
    EXPECT_FALSE(result.has_value());

    delete memStr;
}

TEST_F(FixedLengthEncoderTest_205, LengthLongerThanStreamData_205) {
    const char* data = "AB";
    int dataLen = 2;
    int encodeLen = 5; // longer than actual data
    MemStream* memStr = createMemStream(data, dataLen);
    FixedLengthEncoder encoder(memStr, encodeLen);
    encoder.rewind();

    EXPECT_EQ(encoder.getChar(), 'A');
    EXPECT_EQ(encoder.getChar(), 'B');
    // After underlying stream is exhausted, should return EOF
    int ch = encoder.getChar();
    EXPECT_EQ(ch, EOF);

    delete memStr;
}
