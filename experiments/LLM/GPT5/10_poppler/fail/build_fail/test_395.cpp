// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for: clearGfxColor(GfxColor*)
// File under test: ./TestProjects/poppler/poppler/GfxState.h

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iterator>

#include "poppler/GfxState.h"

namespace {

class ClearGfxColorTest_395 : public ::testing::Test {};

TEST_F(ClearGfxColorTest_395, ClearsAllComponentsToZero_395)
{
    GfxColor color;

    // Make the buffer non-zero (byte-wise) so we can verify it gets cleared.
    std::memset(&color, 0xFF, sizeof(color));

    clearGfxColor(&color);

    for (const auto &comp : color.c) {
        EXPECT_EQ(comp, 0) << "Expected all GfxColor components to be cleared to 0";
    }
}

TEST_F(ClearGfxColorTest_395, LeavesAlreadyZeroColorUnchanged_395)
{
    GfxColor color;
    std::memset(&color, 0, sizeof(color));

    clearGfxColor(&color);

    for (const auto &comp : color.c) {
        EXPECT_EQ(comp, 0);
    }
}

TEST_F(ClearGfxColorTest_395, ClearsEvenWhenOnlySomeComponentsNonZero_395)
{
    GfxColor color;
    std::memset(&color, 0, sizeof(color));

    // Set a few scattered components to non-zero values (without assuming component count).
    if (std::size(color.c) > 0) {
        color.c[0] = static_cast<decltype(color.c[0])>(1);
    }
    if (std::size(color.c) > 1) {
        color.c[1] = static_cast<decltype(color.c[1])>(2);
    }
    if (std::size(color.c) > 2) {
        color.c[std::size(color.c) - 1] = static_cast<decltype(color.c[0])>(3);
    }

    clearGfxColor(&color);

    for (const auto &comp : color.c) {
        EXPECT_EQ(comp, 0);
    }
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ClearGfxColorTest_395, DiesOnNullPointer_395)
{
    // Exceptional/error case: passing nullptr is invalid; observable behavior is a crash.
    EXPECT_DEATH(clearGfxColor(nullptr), "");
}
#endif

} // namespace