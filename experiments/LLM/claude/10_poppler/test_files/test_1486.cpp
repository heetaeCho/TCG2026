#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Stream.h"
#include "Object.h"

// We need access to the static function. Since it's defined as static in Stream.cc,
// we need to either include the .cc or declare it extern. Given the test setup,
// we'll declare it as an extern or include the implementation.
// For testing purposes, we replicate the declaration since the function is static
// and may need to be tested via a wrapper or by including the .cc file.

// If the function is not accessible directly, we include the cc file
// (common practice for testing static/internal functions)
namespace {
#include "Stream.cc"
}

class WrapEOFStreamTest_1486 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that wrapping a non-EOFStream produces an EOFStream
TEST_F(WrapEOFStreamTest_1486, NonEOFStreamGetsWrapped_1486) {
    // Create a simple MemStream or similar non-EOF stream
    // MemStream is a concrete Stream subclass
    const char data[] = "hello";
    auto baseStream = std::make_unique<MemStream>(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    Stream *originalPtr = baseStream.get();
    auto result = wrapEOFStream(std::move(baseStream));
    
    ASSERT_NE(result, nullptr);
    // The result should be an EOFStream wrapping the original
    EXPECT_NE(dynamic_cast<EOFStream *>(result.get()), nullptr);
    // The original pointer should no longer be the top-level stream
    EXPECT_NE(result.get(), originalPtr);
}

// Test that wrapping an EOFStream returns the same EOFStream (no double-wrapping)
TEST_F(WrapEOFStreamTest_1486, EOFStreamNotDoubleWrapped_1486) {
    const char data[] = "test";
    auto baseStream = std::make_unique<MemStream>(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    auto eofStream = std::make_unique<EOFStream>(std::move(baseStream));
    
    EOFStream *originalEOFPtr = eofStream.get();
    auto result = wrapEOFStream(std::move(eofStream));
    
    ASSERT_NE(result, nullptr);
    // Should return the same EOFStream, not wrap it again
    EXPECT_EQ(dynamic_cast<EOFStream *>(result.get()), originalEOFPtr);
}

// Test that the result is always an EOFStream regardless of input type
TEST_F(WrapEOFStreamTest_1486, ResultIsAlwaysEOFStream_1486) {
    const char data[] = "abc";
    auto baseStream = std::make_unique<MemStream>(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    auto result = wrapEOFStream(std::move(baseStream));
    
    ASSERT_NE(result, nullptr);
    EXPECT_NE(dynamic_cast<EOFStream *>(result.get()), nullptr);
}

// Test wrapping an already-wrapped EOFStream multiple times doesn't accumulate layers
TEST_F(WrapEOFStreamTest_1486, MultipleWrapsDoNotAccumulate_1486) {
    const char data[] = "xyz";
    auto baseStream = std::make_unique<MemStream>(const_cast<char *>(data), 0, sizeof(data) - 1, Object(objNull));
    
    auto result1 = wrapEOFStream(std::move(baseStream));
    EOFStream *firstWrapPtr = dynamic_cast<EOFStream *>(result1.get());
    ASSERT_NE(firstWrapPtr, nullptr);
    
    auto result2 = wrapEOFStream(std::move(result1));
    EOFStream *secondWrapPtr = dynamic_cast<EOFStream *>(result2.get());
    ASSERT_NE(secondWrapPtr, nullptr);
    
    // Should be the same pointer - no additional wrapping
    EXPECT_EQ(firstWrapPtr, secondWrapPtr);
}

// Test with empty data MemStream
TEST_F(WrapEOFStreamTest_1486, EmptyStreamGetsWrapped_1486) {
    const char data[] = "";
    auto baseStream = std::make_unique<MemStream>(const_cast<char *>(data), 0, 0, Object(objNull));
    
    auto result = wrapEOFStream(std::move(baseStream));
    
    ASSERT_NE(result, nullptr);
    EXPECT_NE(dynamic_cast<EOFStream *>(result.get()), nullptr);
}
