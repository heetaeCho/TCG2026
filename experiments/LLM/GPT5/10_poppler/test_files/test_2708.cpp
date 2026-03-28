// HtmlOutputDev_interpretType3Chars_test_2708.cpp

#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

class HtmlOutputDevTest_2708 : public ::testing::Test {};

TEST_F(HtmlOutputDevTest_2708, InterpretType3CharsReturnsFalse_2708)
{
    HtmlOutputDev dev;
    EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(HtmlOutputDevTest_2708, InterpretType3CharsIsDeterministicAcrossCalls_2708)
{
    HtmlOutputDev dev;

    // Normal + boundary-ish: repeated calls should be stable and side-effect free (observable via return).
    for (int i = 0; i < 100; ++i) {
        EXPECT_FALSE(dev.interpretType3Chars()) << "Iteration: " << i;
    }
}

TEST_F(HtmlOutputDevTest_2708, InterpretType3CharsIndependentAcrossInstances_2708)
{
    HtmlOutputDev dev1;
    HtmlOutputDev dev2;

    EXPECT_FALSE(dev1.interpretType3Chars());
    EXPECT_FALSE(dev2.interpretType3Chars());
}