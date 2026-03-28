// ReusableStringStream_test.cpp
#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_reusable_string_stream.hpp"

using Catch::ReusableStringStream;

class ReusableStringStreamTest_1 : public ::testing::Test {};

// [Normal] Writing a single string is reflected by str()
TEST_F(ReusableStringStreamTest_1, WriteString_UpdatesStr_1) {
    ReusableStringStream rss;
    rss << std::string("hello");
    EXPECT_EQ(rss.str(), "hello");
}

// [Normal] Chaining operator<< returns the same object (chainability) and appends
TEST_F(ReusableStringStreamTest_1, Chainability_ReturnsSelfAndAppends_1) {
    ReusableStringStream rss;

    // operator<< should return a reference to the same object, enabling chaining
    ReusableStringStream& ref = (rss << "a");
    EXPECT_EQ(&ref, &rss);   // same object

    rss << "bc" << 123 << 'X';
    EXPECT_EQ(rss.str(), "abc123X");
}

// [Boundary] Setting content via str(<new>) replaces the buffer; further writes append
TEST_F(ReusableStringStreamTest_1, SetStr_ReplacesThenAppends_1) {
    ReusableStringStream rss;

    rss << "pre";
    EXPECT_EQ(rss.str(), "pre");

    rss.str(std::string("reset"));
    EXPECT_EQ(rss.str(), "reset");  // replaced

    rss << "_after";
    EXPECT_EQ(rss.str(), "reset_after"); // appended after replace
}

// [Boundary] Setting to empty clears; writing after works normally
TEST_F(ReusableStringStreamTest_1, SetEmptyThenWrite_1) {
    ReusableStringStream rss;

    rss << "something";
    EXPECT_EQ(rss.str(), "something");

    rss.str(std::string());          // set to empty
    EXPECT_EQ(rss.str(), "");        // now empty

    rss << "x";
    EXPECT_EQ(rss.str(), "x");       // subsequent writes work
}

// [Normal] Inserting heterogeneous types behaves like standard ostream
TEST_F(ReusableStringStreamTest_1, InsertVariousTypes_1) {
    ReusableStringStream rss;

    const char* cstr = "num=";
    rss << cstr << 42 << ", dbl=" << 3.5 << ", chr=" << 'Z';
    EXPECT_EQ(rss.str(), "num=42, dbl=3.5, chr=Z");
}

// [Exceptional/Robustness] Common insertions do not throw
TEST_F(ReusableStringStreamTest_1, Insertions_NoThrow_1) {
    ReusableStringStream rss;
    EXPECT_NO_THROW(rss << "alpha");
    EXPECT_NO_THROW(rss << 100);
    EXPECT_NO_THROW(rss << 'q');
    EXPECT_NO_THROW(rss << 1.2345);
    EXPECT_EQ(rss.str(), "alpha100q1.2345");
}
