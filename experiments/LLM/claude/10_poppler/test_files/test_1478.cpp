#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "JArithmeticDecoder.h"
#include "Stream.h"

// Test fixture for JArithmeticDecoder
class JArithmeticDecoderTest_1478 : public ::testing::Test {
protected:
    void SetUp() override {
        decoder = new JArithmeticDecoder();
    }

    void TearDown() override {
        delete decoder;
    }

    JArithmeticDecoder *decoder;
};

// Test that a newly constructed decoder exists without crashing
TEST_F(JArithmeticDecoderTest_1478, ConstructorDoesNotCrash_1478) {
    ASSERT_NE(decoder, nullptr);
}

// Test that resetByteCounter sets the byte counter to 0
TEST_F(JArithmeticDecoderTest_1478, ResetByteCounterSetsToZero_1478) {
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test that getByteCounter returns 0 after reset
TEST_F(JArithmeticDecoderTest_1478, GetByteCounterAfterReset_1478) {
    decoder->resetByteCounter();
    unsigned int count = decoder->getByteCounter();
    EXPECT_EQ(count, 0u);
}

// Test that multiple resets still result in zero byte counter
TEST_F(JArithmeticDecoderTest_1478, MultipleResetsStillZero_1478) {
    decoder->resetByteCounter();
    decoder->resetByteCounter();
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test that copy constructor is deleted (compile-time check is implicit;
// we just verify the object can be used normally)
TEST_F(JArithmeticDecoderTest_1478, ObjectUsableAfterConstruction_1478) {
    decoder->resetByteCounter();
    EXPECT_EQ(decoder->getByteCounter(), 0u);
}

// Test getReadPastEndOfStream initial state - should be false for a fresh decoder
TEST_F(JArithmeticDecoderTest_1478, ReadPastEndOfStreamInitiallyFalse_1478) {
    EXPECT_FALSE(decoder->getReadPastEndOfStream());
}

// Test that getReadPastEndOfStream is false after reset
TEST_F(JArithmeticDecoderTest_1478, ReadPastEndOfStreamAfterReset_1478) {
    decoder->resetByteCounter();
    // Just checking it doesn't crash and returns a valid bool
    bool val = decoder->getReadPastEndOfStream();
    // Initial state should be false based on the default member initializer
    EXPECT_FALSE(val);
}

// Test that getByteCounter returns unsigned int (boundary: zero is minimum)
TEST_F(JArithmeticDecoderTest_1478, ByteCounterIsUnsigned_1478) {
    decoder->resetByteCounter();
    unsigned int counter = decoder->getByteCounter();
    EXPECT_GE(counter, 0u);
}

// Test creating and destroying multiple decoders
TEST_F(JArithmeticDecoderTest_1478, MultipleDecodersIndependent_1478) {
    JArithmeticDecoder *decoder2 = new JArithmeticDecoder();
    
    decoder->resetByteCounter();
    decoder2->resetByteCounter();
    
    EXPECT_EQ(decoder->getByteCounter(), 0u);
    EXPECT_EQ(decoder2->getByteCounter(), 0u);
    
    delete decoder2;
}

// Test that cleanup can be called without prior start (should not crash)
TEST_F(JArithmeticDecoderTest_1478, CleanupWithoutStartDoesNotCrash_1478) {
    // This tests that cleanup is safe to call even without a stream set
    // It may or may not do anything, but should not crash
    decoder->cleanup();
    SUCCEED();
}

// Test resetByteCounter followed by getByteCounter consistency
TEST_F(JArithmeticDecoderTest_1478, ResetThenGetConsistency_1478) {
    decoder->resetByteCounter();
    unsigned int first = decoder->getByteCounter();
    unsigned int second = decoder->getByteCounter();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, 0u);
}
