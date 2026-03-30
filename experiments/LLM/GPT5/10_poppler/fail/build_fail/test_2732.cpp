// File: print_uni_str_test_2732.cc

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Access the TU-local (static) function by including the .cc directly.
// This is a common technique for testing file-scope statics.
#include "TestProjects/poppler/utils/HtmlOutputDev.cc"

namespace {

class PrintUniStrTest_2732 : public ::testing::Test {};

TEST_F(PrintUniStrTest_2732, ReturnsEmptyWhenLenIsZero_2732)
{
    // u is not dereferenced when uLen == 0.
    const Unicode *u = nullptr;
    EXPECT_EQ(print_uni_str(u, 0u), "");
}

TEST_F(PrintUniStrTest_2732, LenOneAsciiReturnsSingleChar_2732)
{
    const Unicode u[] = { static_cast<Unicode>('A') };
    EXPECT_EQ(print_uni_str(u, 1u), "A");
}

TEST_F(PrintUniStrTest_2732, FirstCharNonAsciiBecomesQuestionMark_2732)
{
    const Unicode u[] = { static_cast<Unicode>(0x80) }; // >= 0x7F
    EXPECT_EQ(print_uni_str(u, 1u), "?");
}

TEST_F(PrintUniStrTest_2732, AppendsOnlySubsequentAsciiCharacters_2732)
{
    // First char is ASCII, subsequent include both ASCII and non-ASCII.
    const Unicode u[] = {
        static_cast<Unicode>('H'),
        static_cast<Unicode>('i'),
        static_cast<Unicode>(0x80), // skipped
        static_cast<Unicode>('!'),
        static_cast<Unicode>(0x7F), // not < 0x7F, skipped
        static_cast<Unicode>('x'),
    };

    EXPECT_EQ(print_uni_str(u, 6u), "Hi!x");
}

TEST_F(PrintUniStrTest_2732, FirstCharNonAsciiStillAllowsAppendingAsciiLater_2732)
{
    // First char becomes '?', later ASCII (<0x7F) are appended.
    const Unicode u[] = {
        static_cast<Unicode>(0x1234), // first -> '?'
        static_cast<Unicode>('A'),
        static_cast<Unicode>(0x90),   // skipped
        static_cast<Unicode>('B'),
    };

    EXPECT_EQ(print_uni_str(u, 4u), "?AB");
}

TEST_F(PrintUniStrTest_2732, BoundaryLenTwoHandlesSecondCharRules_2732)
{
    {
        const Unicode u[] = { static_cast<Unicode>('Z'), static_cast<Unicode>('9') };
        EXPECT_EQ(print_uni_str(u, 2u), "Z9");
    }
    {
        const Unicode u[] = { static_cast<Unicode>('Z'), static_cast<Unicode>(0x7F) }; // second skipped
        EXPECT_EQ(print_uni_str(u, 2u), "Z");
    }
    {
        const Unicode u[] = { static_cast<Unicode>(0x80), static_cast<Unicode>('9') }; // first '?', second appended
        EXPECT_EQ(print_uni_str(u, 2u), "?9");
    }
}

} // namespace