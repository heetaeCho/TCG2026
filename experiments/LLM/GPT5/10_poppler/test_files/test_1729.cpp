// CairoOutputDev_supportJPXtransparency_1729_test.cc
#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// NOTE:
// - Treat CairoOutputDev as a black box.
// - Only test observable behavior from the public interface.
// - No assumptions about internal state or other methods.

TEST(CairoOutputDevTest_1729, SupportJPXTransparencyReturnsTrue_1729)
{
    CairoOutputDev dev;
    EXPECT_TRUE(dev.supportJPXtransparency());
}

TEST(CairoOutputDevTest_1729, SupportJPXTransparencyIsStableAcrossMultipleCalls_1729)
{
    CairoOutputDev dev;

    EXPECT_TRUE(dev.supportJPXtransparency());
    EXPECT_TRUE(dev.supportJPXtransparency());
    EXPECT_TRUE(dev.supportJPXtransparency());
}

TEST(CairoOutputDevTest_1729, SupportJPXTransparencyWorksViaOutputDevPolymorphism_1729)
{
    CairoOutputDev dev;

    // Verify observable behavior through the base interface (override dispatch).
    OutputDev *base = &dev;
    ASSERT_NE(base, nullptr);
    EXPECT_TRUE(base->supportJPXtransparency());
}