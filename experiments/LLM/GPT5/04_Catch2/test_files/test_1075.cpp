// File: tests/jsonobjectwriter_ctor_indent_1075_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Include the public interface (path from your tree)
#include "Catch2/src/catch2/internal/catch_jsonwriter.hpp"

namespace {

class JsonObjectWriterTest_1075 : public ::testing::Test {};

TEST_F(JsonObjectWriterTest_1075, ConstructorWithIndent_WritesOpeningBrace_1075) {
    std::ostringstream oss;

    // Act: construct with indent = 0
    Catch::JsonObjectWriter writer(oss, static_cast<std::uint64_t>(0));

    // Assert: immediately writes a single '{'
    EXPECT_EQ(oss.str(), "{");
}

TEST_F(JsonObjectWriterTest_1075, ConstructorWithLargeIndent_WritesOpeningBraceOnly_1075) {
    std::ostringstream oss;

    // Act: construct with a large indent value (boundary-ish)
    Catch::JsonObjectWriter writer(oss, std::numeric_limits<std::uint64_t>::max());

    // Assert: still only writes a single '{'
    EXPECT_EQ(oss.str(), "{");
}

TEST_F(JsonObjectWriterTest_1075, StreamRemainsGoodAfterConstruction_1075) {
    std::ostringstream oss;

    // Act
    Catch::JsonObjectWriter writer(oss, 42);

    // Assert: stream state remains good after the constructor's write
    EXPECT_TRUE(oss.good());
    // And content is exactly a single '{'
    EXPECT_EQ(oss.str(), "{");
}

} // namespace
