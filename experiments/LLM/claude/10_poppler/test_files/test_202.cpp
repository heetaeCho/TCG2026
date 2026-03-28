#include <gtest/gtest.h>

// We need to include the actual header that defines EOFStream
// Based on the partial code, EOFStream has at least isBinary method
#include "Stream.h"

class EOFStreamTest_202 : public ::testing::Test {
protected:
    void SetUp() override {
        stream = new EOFStream(nullptr);
    }

    void TearDown() override {
        delete stream;
    }

    EOFStream *stream;
};

// Test that isBinary returns false with default-like argument
TEST_F(EOFStreamTest_202, IsBinaryReturnsFalseWithTrue_202) {
    EXPECT_FALSE(stream->isBinary(true));
}

// Test that isBinary returns false when called with false
TEST_F(EOFStreamTest_202, IsBinaryReturnsFalseWithFalse_202) {
    EXPECT_FALSE(stream->isBinary(false));
}

// Test that isBinary consistently returns false on multiple calls
TEST_F(EOFStreamTest_202, IsBinaryConsistentlyReturnsFalse_202) {
    EXPECT_FALSE(stream->isBinary(true));
    EXPECT_FALSE(stream->isBinary(false));
    EXPECT_FALSE(stream->isBinary(true));
}
