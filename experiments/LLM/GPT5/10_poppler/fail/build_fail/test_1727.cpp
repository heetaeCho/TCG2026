// CairoOutputDev_interpretType3Chars_test_1727.cpp

#include <gtest/gtest.h>

#include "CairoOutputDev.h" // ./TestProjects/poppler/poppler/CairoOutputDev.h

TEST(CairoOutputDevTest_1727, InterpretType3CharsReturnsFalse_1727)
{
    CairoOutputDev dev;
    EXPECT_FALSE(dev.interpretType3Chars());
}

TEST(CairoOutputDevTest_1727, InterpretType3CharsReturnsFalseViaBasePointer_1727)
{
    CairoOutputDev dev;
    OutputDev *base = &dev; // Verify observable behavior through the public interface polymorphically.
    ASSERT_NE(base, nullptr);
    EXPECT_FALSE(base->interpretType3Chars());
}

TEST(CairoOutputDevTest_1727, InterpretType3CharsIsStableAcrossMultipleCalls_1727)
{
    CairoOutputDev dev;

    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
}