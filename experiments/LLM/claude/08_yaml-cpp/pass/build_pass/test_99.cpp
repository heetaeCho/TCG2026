#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "stream.h"
#include "streamcharsource.h"

#include <sstream>
#include <string>

namespace YAML {

class StreamCharSourceTest_99 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a Stream from a string
// Stream typically wraps an istream
TEST_F(StreamCharSourceTest_99, ConstructFromStream_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    // If construction succeeds without crash, basic construction works
    SUCCEED();
}

TEST_F(StreamCharSourceTest_99, CopyConstruct_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    StreamCharSource copy(source);
    SUCCEED();
}

TEST_F(StreamCharSourceTest_99, MoveConstruct_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    StreamCharSource moved(std::move(source));
    SUCCEED();
}

TEST_F(StreamCharSourceTest_99, BoolOperatorOnValidStream_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    // A stream with content should be truthy
    EXPECT_TRUE(static_cast<bool>(source));
}

TEST_F(StreamCharSourceTest_99, NotOperatorOnValidStream_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    // A valid stream source should not be "not"
    EXPECT_FALSE(!source);
}

TEST_F(StreamCharSourceTest_99, BoolOperatorOnEmptyStream_99) {
    std::istringstream input("");
    Stream stream(input);
    StreamCharSource source(stream);
    // An empty stream may or may not be valid depending on implementation
    // We just check consistency between bool and !
    bool boolVal = static_cast<bool>(source);
    bool notVal = !source;
    EXPECT_EQ(boolVal, !notVal);
}

TEST_F(StreamCharSourceTest_99, NotOperatorConsistentWithBool_99) {
    std::istringstream input("test");
    Stream stream(input);
    StreamCharSource source(stream);
    bool boolResult = static_cast<bool>(source);
    bool notResult = !source;
    EXPECT_NE(boolResult, notResult);
}

TEST_F(StreamCharSourceTest_99, SubscriptOperatorFirstChar_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        char c = source[0];
        EXPECT_EQ(c, 'h');
    }
}

TEST_F(StreamCharSourceTest_99, SubscriptOperatorSecondChar_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        char c = source[1];
        EXPECT_EQ(c, 'e');
    }
}

TEST_F(StreamCharSourceTest_99, SubscriptOperatorMultipleChars_99) {
    std::istringstream input("abcdef");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        EXPECT_EQ(source[0], 'a');
        EXPECT_EQ(source[1], 'b');
        EXPECT_EQ(source[2], 'c');
        EXPECT_EQ(source[3], 'd');
    }
}

TEST_F(StreamCharSourceTest_99, PlusOperatorReturnsOffsetSource_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        const StreamCharSource offset = source + 1;
        // After offset by 1, index 0 should give 'e'
        EXPECT_EQ(offset[0], 'e');
    }
}

TEST_F(StreamCharSourceTest_99, PlusOperatorWithLargerOffset_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        const StreamCharSource offset = source + 3;
        EXPECT_EQ(offset[0], 'l');
    }
}

TEST_F(StreamCharSourceTest_99, PlusOperatorZeroOffset_99) {
    std::istringstream input("hello");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        const StreamCharSource offset = source + 0;
        EXPECT_EQ(offset[0], 'h');
    }
}

TEST_F(StreamCharSourceTest_99, PlusOperatorChained_99) {
    std::istringstream input("abcdefgh");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        const StreamCharSource offset1 = source + 2;
        const StreamCharSource offset2 = offset1 + 3;
        EXPECT_EQ(offset2[0], 'f');
    }
}

TEST_F(StreamCharSourceTest_99, SingleCharacterStream_99) {
    std::istringstream input("x");
    Stream stream(input);
    StreamCharSource source(stream);
    if (static_cast<bool>(source)) {
        EXPECT_EQ(source[0], 'x');
    }
}

}  // namespace YAML
