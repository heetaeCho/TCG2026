// File: CairoOutputDev_useFillColorStop_1726_test.cc

#include <gtest/gtest.h>

#include "CairoOutputDev.h"

// The implementation is treated as a black box.
// We only assert observable behavior through the public interface.

TEST(CairoOutputDevTest_1726, UseFillColorStopReturnsTrue_1726)
{
    CairoOutputDev dev;
    EXPECT_TRUE(dev.useFillColorStop());
}

TEST(CairoOutputDevTest_1726, UseFillColorStopIsStableAcrossRepeatedCalls_1726)
{
    CairoOutputDev dev;

    // Repeated calls should remain consistent and not crash.
    EXPECT_TRUE(dev.useFillColorStop());
    EXPECT_TRUE(dev.useFillColorStop());
    EXPECT_TRUE(dev.useFillColorStop());
}

TEST(CairoOutputDevTest_1726, UseFillColorStopWorksViaBasePointerDispatch_1726)
{
    // Verify observable polymorphic behavior through the base interface.
    OutputDev *base = new CairoOutputDev();
    ASSERT_NE(base, nullptr);

    EXPECT_TRUE(base->useFillColorStop());

    delete base;
}

TEST(CairoOutputDevTest_1726, UseFillColorStopCallableOnMultipleInstances_1726)
{
    CairoOutputDev dev1;
    CairoOutputDev dev2;

    EXPECT_TRUE(dev1.useFillColorStop());
    EXPECT_TRUE(dev2.useFillColorStop());
}