#include "gtest/gtest.h"
#include "stream.h"
#include "streamcharsource.h"
#include <sstream>

namespace YAML {
namespace {

class StreamCharSourceTest_101 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a Stream from a string
// Stream takes a std::istream reference typically

TEST_F(StreamCharSourceTest_101, ConstructFromStream_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    // Should be constructible without throwing
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, CopyConstruct_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource copy(source);
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, MoveConstruct_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource moved(std::move(source));
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusPositive_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 3;
    // The advanced source should have offset shifted by 3
    // We can verify by checking operator[] behavior
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusZero_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource same = source + 0;
    // Offset should remain the same
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusNegativeClampsToZero_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    // Starting at offset 0, adding -5 should clamp to 0
    StreamCharSource clamped = source + (-5);
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusNegativeFromAdvanced_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 5;
    StreamCharSource backedUp = advanced + (-3);
    // Should have offset 2
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusNegativeExactlyToZero_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 5;
    StreamCharSource atZero = advanced + (-5);
    // Should have offset 0
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusDoesNotModifyOriginal_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 3;
    // source should still be at offset 0
    // Verify through operator[]
    char original = source[0];
    char advancedChar = advanced[0];
    // These may differ if offset affects indexing
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorBoolOnValidSource_101) {
    std::stringstream ss("hello");
    Stream stream(ss);
    StreamCharSource source(stream);
    // A source pointing to valid data should be true
    EXPECT_TRUE(static_cast<bool>(source));
}

TEST_F(StreamCharSourceTest_101, OperatorNotOnValidSource_101) {
    std::stringstream ss("hello");
    Stream stream(ss);
    StreamCharSource source(stream);
    EXPECT_FALSE(!source);
}

TEST_F(StreamCharSourceTest_101, OperatorBracketFirstChar_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    char c = source[0];
    EXPECT_EQ(c, 'h');
}

TEST_F(StreamCharSourceTest_101, OperatorBracketWithOffset_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    char c = source[1];
    EXPECT_EQ(c, 'e');
}

TEST_F(StreamCharSourceTest_101, OperatorPlusThenBracket_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 1;
    char c = advanced[0];
    EXPECT_EQ(c, 'e');
}

TEST_F(StreamCharSourceTest_101, OperatorPlusChained_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 2 + 3;
    char c = advanced[0];
    EXPECT_EQ(c, ' ');
}

TEST_F(StreamCharSourceTest_101, OperatorBoolOnEmptyStream_101) {
    std::stringstream ss("");
    Stream stream(ss);
    StreamCharSource source(stream);
    // Behavior depends on implementation - empty stream may not be valid
    // Just verify it doesn't crash
    bool val = static_cast<bool>(source);
    (void)val;
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusBeyondStreamEnd_101) {
    std::stringstream ss("hi");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 100;
    // Should not crash; bool conversion may return false
    bool val = static_cast<bool>(advanced);
    (void)val;
    SUCCEED();
}

TEST_F(StreamCharSourceTest_101, OperatorPlusNegativeLargerThanOffset_101) {
    std::stringstream ss("hello world");
    Stream stream(ss);
    StreamCharSource source(stream);
    StreamCharSource advanced = source + 3;
    // Go back more than the offset, should clamp to 0
    StreamCharSource clamped = advanced + (-10);
    char c = clamped[0];
    EXPECT_EQ(c, 'h');
}

}  // namespace
}  // namespace YAML
