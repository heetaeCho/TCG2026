// File: HtmlOutputDev_useDrawChar_test_2707.cpp

#include <gtest/gtest.h>

#include "HtmlOutputDev.h"

// NOTE:
// - We treat HtmlOutputDev as a black box and only test observable behavior
//   exposed through the public interface.
// - Based on the provided partial code, useDrawChar() is expected to return true.

namespace {

class HtmlOutputDevTest_2707 : public ::testing::Test {};

TEST_F(HtmlOutputDevTest_2707, UseDrawCharReturnsTrue_2707)
{
    HtmlOutputDev dev;
    EXPECT_TRUE(dev.useDrawChar());
}

TEST_F(HtmlOutputDevTest_2707, UseDrawCharIsStableAcrossMultipleCalls_2707)
{
    HtmlOutputDev dev;

    EXPECT_TRUE(dev.useDrawChar());
    EXPECT_TRUE(dev.useDrawChar());
    EXPECT_TRUE(dev.useDrawChar());
}

TEST_F(HtmlOutputDevTest_2707, UseDrawCharViaBasePointerReturnsTrue_2707)
{
    // Verifies virtual dispatch through the base class (external observable behavior).
    OutputDev *base = new HtmlOutputDev();
    ASSERT_NE(base, nullptr);

    EXPECT_TRUE(base->useDrawChar());

    delete base;
}

} // namespace