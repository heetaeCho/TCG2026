// File: tests/OutputFilter_test_8.cpp
#include <gtest/gtest.h>
#include <streambuf>  // for std::char_traits
#include "JsonBox/OutputFilter.h"

namespace {

using Traits = std::char_traits<char>; // used only to obtain a valid EOF value

// Basic sanity: underflow() should return EOF.
TEST(OutputFilterTest_8, UnderflowReturnsEOF_8) {
    JsonBox::OutputFilter filter;
    auto value = filter.underflow();
    EXPECT_EQ(value, Traits::eof());
}

// Idempotence: repeated calls should keep returning EOF.
TEST(OutputFilterTest_8, UnderflowRepeatedCallsReturnEOF_8) {
    JsonBox::OutputFilter filter;
    EXPECT_EQ(filter.underflow(), Traits::eof());
    EXPECT_EQ(filter.underflow(), Traits::eof());
    EXPECT_EQ(filter.underflow(), Traits::eof());
}

} // namespace
