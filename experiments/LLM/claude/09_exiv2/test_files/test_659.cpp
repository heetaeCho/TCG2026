#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <string>

// We need access to the readString function. Since it's a static function in
// quicktimevideo.cpp, we need to either include it or replicate the declaration.
// For testing purposes, we'll use MemIo which is a concrete implementation of BasicIo.

// Include MemIo
#include <exiv2/basicio.hpp>

// Since readString is a static function in quicktimevideo.cpp, it's not directly
// accessible from outside. We need to declare it or include the source.
// For this test, we'll include the source file to get access to the static function.
// This is a common pattern for testing static/internal functions.

// Forward declaration won't work for static functions, so we include the cpp
// However, this may cause issues with duplicate symbols. An alternative approach
// is to test through a wrapper or to directly include the relevant code.

// We'll re-declare the function signature and test it by including the source.
// Note: In practice, this would be done via a test-friendly wrapper or by making
// the function non-static with internal linkage exposed for testing.

namespace Exiv2 {
    static std::string readString(BasicIo& io, size_t size);
}

// Include the implementation to get the static function
#include "quicktimevideo.cpp"

class ReadStringTest_659 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test reading a normal string
TEST_F(ReadStringTest_659, ReadsNormalString_659) {
    const std::string testData = "Hello, World!";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result = Exiv2::readString(io, 5);
    EXPECT_EQ(result, "Hello");
}

// Test reading entire content
TEST_F(ReadStringTest_659, ReadsEntireContent_659) {
    const std::string testData = "Test";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result = Exiv2::readString(io, 4);
    EXPECT_EQ(result, "Test");
}

// Test reading zero-length string
TEST_F(ReadStringTest_659, ReadsEmptyString_659) {
    const std::string testData = "SomeData";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result = Exiv2::readString(io, 0);
    EXPECT_EQ(result, "");
}

// Test reading single character
TEST_F(ReadStringTest_659, ReadsSingleCharacter_659) {
    const std::string testData = "A";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result = Exiv2::readString(io, 1);
    EXPECT_EQ(result, "A");
}

// Test that reading more than available throws an error (corrupt metadata)
TEST_F(ReadStringTest_659, ThrowsOnSizeLargerThanAvailable_659) {
    const std::string testData = "Short";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    EXPECT_THROW(Exiv2::readString(io, testData.size() + 1), Exiv2::Error);
}

// Test reading after seeking partway through
TEST_F(ReadStringTest_659, ReadsFromCurrentPosition_659) {
    const std::string testData = "Hello, World!";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    // Seek to position 7
    io.seek(7, Exiv2::BasicIo::beg);
    
    std::string result = Exiv2::readString(io, 6);
    EXPECT_EQ(result, "World!");
}

// Test that io position advances after read
TEST_F(ReadStringTest_659, AdvancesIOPosition_659) {
    const std::string testData = "ABCDEFGHIJ";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result1 = Exiv2::readString(io, 3);
    EXPECT_EQ(result1, "ABC");
    EXPECT_EQ(io.tell(), 3u);
    
    std::string result2 = Exiv2::readString(io, 3);
    EXPECT_EQ(result2, "DEF");
    EXPECT_EQ(io.tell(), 6u);
}

// Test reading string with embedded null bytes - readString reads raw bytes
// but toString may stop at null
TEST_F(ReadStringTest_659, ReadsStringWithNullByte_659) {
    const char testData[] = "AB\0CD";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData), 5);
    
    std::string result = Exiv2::readString(io, 5);
    // toString with char* will stop at first null
    EXPECT_EQ(result, "AB");
}

// Test reading at exact boundary (size equals remaining bytes)
TEST_F(ReadStringTest_659, ReadsExactRemainingBytes_659) {
    const std::string testData = "ExactFit";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    // Seek partway
    io.seek(5, Exiv2::BasicIo::beg);
    
    // Read exactly the remaining 3 bytes
    std::string result = Exiv2::readString(io, 3);
    EXPECT_EQ(result, "Fit");
}

// Test that requesting size exceeding remaining bytes after seek throws
TEST_F(ReadStringTest_659, ThrowsWhenSizeExceedsRemainingAfterSeek_659) {
    const std::string testData = "Short";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    io.seek(3, Exiv2::BasicIo::beg);
    
    // Only 2 bytes remaining, requesting 3
    EXPECT_THROW(Exiv2::readString(io, 3), Exiv2::Error);
}

// Test reading binary data that looks like a string
TEST_F(ReadStringTest_659, ReadsBinaryDataAsString_659) {
    const Exiv2::byte testData[] = {0x48, 0x69, 0x21}; // "Hi!"
    Exiv2::MemIo io(testData, 3);
    
    std::string result = Exiv2::readString(io, 3);
    EXPECT_EQ(result, "Hi!");
}

// Test with a larger buffer
TEST_F(ReadStringTest_659, ReadsLargerString_659) {
    std::string testData(1000, 'X');
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result = Exiv2::readString(io, 1000);
    EXPECT_EQ(result, testData);
    EXPECT_EQ(result.size(), 1000u);
}

// Test that the result is null-terminated (string behavior)
TEST_F(ReadStringTest_659, ResultIsProperString_659) {
    const std::string testData = "ProperString";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    std::string result = Exiv2::readString(io, 6);
    EXPECT_EQ(result, "Proper");
    EXPECT_EQ(result.length(), 6u);
}

// Test sequential reads consume the stream properly
TEST_F(ReadStringTest_659, SequentialReadsWork_659) {
    const std::string testData = "AABBCCDD";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    EXPECT_EQ(Exiv2::readString(io, 2), "AA");
    EXPECT_EQ(Exiv2::readString(io, 2), "BB");
    EXPECT_EQ(Exiv2::readString(io, 2), "CC");
    EXPECT_EQ(Exiv2::readString(io, 2), "DD");
}

// Test that after reading all bytes, further read of size > 0 throws
TEST_F(ReadStringTest_659, ThrowsAfterAllBytesConsumed_659) {
    const std::string testData = "End";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    Exiv2::readString(io, 3); // consume all
    EXPECT_THROW(Exiv2::readString(io, 1), Exiv2::Error);
}

// Test reading zero bytes after consuming all is fine
TEST_F(ReadStringTest_659, ReadZeroAfterAllConsumed_659) {
    const std::string testData = "Done";
    Exiv2::MemIo io(reinterpret_cast<const Exiv2::byte*>(testData.c_str()), testData.size());
    
    Exiv2::readString(io, 4); // consume all
    std::string result = Exiv2::readString(io, 0);
    EXPECT_EQ(result, "");
}
