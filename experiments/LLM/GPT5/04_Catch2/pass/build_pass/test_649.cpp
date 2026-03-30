// File: reusable_string_stream_test.cpp

#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_reusable_string_stream.hpp" // assumes real header path in your tree

using Catch::ReusableStringStream;

class ReusableStringStreamTest_649 : public ::testing::Test {};

// Verifies a just-constructed stream has no visible content.
TEST_F(ReusableStringStreamTest_649, DefaultIsEmpty_649) {
    ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
}

// Writing via operator<< with common types should be reflected in str()
TEST_F(ReusableStringStreamTest_649, OperatorShiftAppendsValues_649) {
    ReusableStringStream rss;
    rss << std::string("value=") << 42;
    EXPECT_EQ(rss.str(), "value=42");
}

// operator<< should be chainable and return *this (reference identity)
TEST_F(ReusableStringStreamTest_649, OperatorShiftReturnsSelf_649) {
    ReusableStringStream rss;
    ReusableStringStream& ref = (rss << "A");
    EXPECT_EQ(&ref, &rss);
    rss << "B";
    EXPECT_EQ(rss.str(), "AB");
}

// get() exposes an ostream that writes into the same underlying buffer
TEST_F(ReusableStringStreamTest_649, GetReturnsOstreamWritingIntoSameBuffer_649) {
    ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "hello";
    EXPECT_EQ(rss.str(), "hello");
    os << " world";
    EXPECT_EQ(rss.str(), "hello world");
}

// Setter str(const std::string&) replaces visible contents
TEST_F(ReusableStringStreamTest_649, SetterReplacesContents_649) {
    ReusableStringStream rss;
    rss << "old";
    ASSERT_EQ(rss.str(), "old");

    rss.str("new");
    EXPECT_EQ(rss.str(), "new");
}

// Setting to empty string clears visible contents
TEST_F(ReusableStringStreamTest_649, SetterEmptyClearsContents_649) {
    ReusableStringStream rss;
    rss << "data";
    ASSERT_EQ(rss.str(), "data");

    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Calling str() repeatedly should be non-destructive/idempotent
TEST_F(ReusableStringStreamTest_649, StrGetterIsIdempotent_649) {
    ReusableStringStream rss;
    rss << "repeat";
    const std::string first = rss.str();
    const std::string second = rss.str();
    EXPECT_EQ(first, "repeat");
    EXPECT_EQ(second, "repeat");
}

// Large input is preserved (boundary-ish size)
TEST_F(ReusableStringStreamTest_649, HandlesLargeString_649) {
    std::string big(10000, 'x'); // 10k chars
    ReusableStringStream rss;
    rss << big;
    EXPECT_EQ(rss.str().size(), big.size());
    EXPECT_EQ(rss.str(), big);
}
