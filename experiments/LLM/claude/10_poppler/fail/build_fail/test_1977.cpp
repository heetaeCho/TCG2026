#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal stubs needed to compile
// We need to work with the StreamBitReader class from Hints.cc

// Since we need Stream class for the constructor, we'll need to include the appropriate headers
// Based on the poppler project structure:
#include "config.h"
#include "Object.h"
#include "Stream.h"

// Include the header that contains StreamBitReader
// Since StreamBitReader is defined in Hints.cc, we may need to include it directly
// or recreate the minimal interface. Given the constraints, we'll work with what's available.

// Based on the known dependencies, StreamBitReader is defined in Hints.cc
// We need to include or forward-declare it. Since it's in a .cc file, we may need
// to include it directly for testing purposes.
#include "Hints.h"

// If StreamBitReader is not exported via Hints.h, we include the .cc file directly
// This is a common pattern for testing internal classes
#ifndef STREAM_BIT_READER_DEFINED
#include "Hints.cc"
#define STREAM_BIT_READER_DEFINED
#endif

// Helper: Create a MemStream for testing
class StreamBitReaderTest_1977 : public ::testing::Test {
protected:
    // Helper to create a StreamBitReader from raw bytes
    std::unique_ptr<char[]> createBuffer(const std::vector<unsigned char> &bytes) {
        auto buf = std::make_unique<char[]>(bytes.size());
        for (size_t i = 0; i < bytes.size(); i++) {
            buf[i] = static_cast<char>(bytes[i]);
        }
        return buf;
    }
};

// Test that atEOF returns false initially on a non-empty stream
TEST_F(StreamBitReaderTest_1977, AtEOF_InitiallyFalseOnNonEmptyStream_1977) {
    unsigned char data[] = { 0xAB, 0xCD };
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 2, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    EXPECT_FALSE(reader.atEOF());
}

// Test that atEOF returns true on an empty stream after attempting to read
TEST_F(StreamBitReaderTest_1977, AtEOF_TrueOnEmptyStreamAfterRead_1977) {
    unsigned char data[] = {};
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 0, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    // Try to read - should hit EOF
    reader.readBit();
    EXPECT_TRUE(reader.atEOF());
}

// Test reading a single bit from a known byte
TEST_F(StreamBitReaderTest_1977, ReadBit_ReadsSingleBit_1977) {
    unsigned char data[] = { 0x80 }; // 10000000 in binary
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    unsigned int bit = reader.readBit();
    // The first bit of 0x80 should be 1
    EXPECT_EQ(bit, 1u);
}

// Test reading multiple individual bits
TEST_F(StreamBitReaderTest_1977, ReadBit_ReadsMultipleBitsCorrectly_1977) {
    unsigned char data[] = { 0xA5 }; // 10100101 in binary
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    
    // Read all 8 bits of 0xA5 = 10100101
    EXPECT_EQ(reader.readBit(), 1u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
    EXPECT_EQ(reader.readBit(), 0u);
    EXPECT_EQ(reader.readBit(), 1u);
}

// Test reading bits with readBits
TEST_F(StreamBitReaderTest_1977, ReadBits_ReadsNBitsCorrectly_1977) {
    unsigned char data[] = { 0xFF }; // 11111111
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    unsigned int val = reader.readBits(8);
    EXPECT_EQ(val, 0xFFu);
}

// Test reading partial bits with readBits
TEST_F(StreamBitReaderTest_1977, ReadBits_ReadsPartialByte_1977) {
    unsigned char data[] = { 0xF0 }; // 11110000
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    unsigned int val = reader.readBits(4);
    EXPECT_EQ(val, 0xFu); // First 4 bits of 0xF0 = 1111 = 15
}

// Test reading bits across byte boundaries
TEST_F(StreamBitReaderTest_1977, ReadBits_AcrossByteBoundary_1977) {
    unsigned char data[] = { 0x0F, 0xF0 }; // 00001111 11110000
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 2, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    // Skip first 4 bits (0000)
    reader.readBits(4);
    // Read next 8 bits across boundary: 1111 1111
    unsigned int val = reader.readBits(8);
    EXPECT_EQ(val, 0xFFu);
}

// Test resetInputBits
TEST_F(StreamBitReaderTest_1977, ResetInputBits_ResetsBufferedBits_1977) {
    unsigned char data[] = { 0xAB, 0xCD };
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 2, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    // Read 4 bits (partially consume first byte)
    reader.readBits(4);
    // Reset input bits - should discard remaining buffered bits
    reader.resetInputBits();
    // After reset, next read should start from next byte boundary
    // This test verifies resetInputBits doesn't crash and can continue reading
    EXPECT_FALSE(reader.atEOF());
}

// Test reading 1 bit with readBits
TEST_F(StreamBitReaderTest_1977, ReadBits_SingleBit_1977) {
    unsigned char data[] = { 0x80 }; // 10000000
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    unsigned int val = reader.readBits(1);
    EXPECT_EQ(val, 1u);
}

// Test reading from a multi-byte stream
TEST_F(StreamBitReaderTest_1977, ReadBits_MultiByteRead_1977) {
    unsigned char data[] = { 0x12, 0x34, 0x56, 0x78 };
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 4, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    unsigned int val = reader.readBits(16);
    EXPECT_EQ(val, 0x1234u);
}

// Test that atEOF transitions correctly after reading all data
TEST_F(StreamBitReaderTest_1977, AtEOF_TransitionsAfterReadingAllData_1977) {
    unsigned char data[] = { 0xFF };
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    EXPECT_FALSE(reader.atEOF());
    
    // Read all 8 bits
    reader.readBits(8);
    // At this point we may or may not be at EOF until we try to read more
    // Try to read one more bit to trigger EOF detection
    reader.readBit();
    EXPECT_TRUE(reader.atEOF());
}

// Test reading zero-value bytes
TEST_F(StreamBitReaderTest_1977, ReadBits_ZeroValueByte_1977) {
    unsigned char data[] = { 0x00 };
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    unsigned int val = reader.readBits(8);
    EXPECT_EQ(val, 0u);
}

// Test reading alternating bit pattern
TEST_F(StreamBitReaderTest_1977, ReadBit_AlternatingPattern_1977) {
    unsigned char data[] = { 0xAA }; // 10101010
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(reader.readBit(), 1u) << "Bit " << (2*i) << " should be 1";
        EXPECT_EQ(reader.readBit(), 0u) << "Bit " << (2*i+1) << " should be 0";
    }
}

// Test mixed readBit and readBits calls
TEST_F(StreamBitReaderTest_1977, MixedReadBitAndReadBits_1977) {
    unsigned char data[] = { 0xB5 }; // 10110101
    auto obj = Object(new MemStream(reinterpret_cast<char *>(data), 0, 1, Object(objNull)));
    Stream *str = obj.getStream();
    str->reset();
    
    StreamBitReader reader(str);
    // Read first bit: 1
    EXPECT_EQ(reader.readBit(), 1u);
    // Read next 3 bits: 011 = 3
    EXPECT_EQ(reader.readBits(3), 3u);
    // Read remaining 4 bits: 0101 = 5
    EXPECT_EQ(reader.readBits(4), 5u);
}
