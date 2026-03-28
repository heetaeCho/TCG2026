// SPDX-License-Identifier: MIT
//
// Unit tests for GfxRGB::operator==
// File under test: ./TestProjects/poppler/poppler/GfxState.h
//
// Constraints respected:
// - Treat implementation as black box (only use public fields + operator== observable result)
// - No private state access (none exists here)
// - Boundary-ish coverage via representative component values (including extremes / negatives if type allows)

#include <gtest/gtest.h>

#include "poppler/GfxState.h"

namespace {

class GfxRGBTest_396 : public ::testing::Test {};

static GfxRGB MakeRGB(GfxColorComp r, GfxColorComp g, GfxColorComp b)
{
    GfxRGB c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

TEST_F(GfxRGBTest_396, EqualWhenAllComponentsMatch_396)
{
    const auto a = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));
    const auto b = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a); // symmetry observable through interface
}

TEST_F(GfxRGBTest_396, NotEqualWhenRDiffers_396)
{
    const auto a = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));
    const auto b = MakeRGB(static_cast<GfxColorComp>(9), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST_F(GfxRGBTest_396, NotEqualWhenGDiffers_396)
{
    const auto a = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));
    const auto b = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(9), static_cast<GfxColorComp>(3));

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST_F(GfxRGBTest_396, NotEqualWhenBDiffers_396)
{
    const auto a = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));
    const auto b = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(9));

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST_F(GfxRGBTest_396, NotEqualWhenMultipleComponentsDiffer_396)
{
    const auto a = MakeRGB(static_cast<GfxColorComp>(1), static_cast<GfxColorComp>(2), static_cast<GfxColorComp>(3));
    const auto b = MakeRGB(static_cast<GfxColorComp>(9), static_cast<GfxColorComp>(8), static_cast<GfxColorComp>(7));

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST_F(GfxRGBTest_396, ReflexiveAlwaysEqualToSelf_396)
{
    const auto a = MakeRGB(static_cast<GfxColorComp>(4), static_cast<GfxColorComp>(5), static_cast<GfxColorComp>(6));
    EXPECT_TRUE(a == a);
}

TEST_F(GfxRGBTest_396, HandlesDefaultInitializedValuesWhenSetExplicitly_396)
{
    // We avoid relying on default initialization semantics by explicitly assigning.
    const auto a = MakeRGB(static_cast<GfxColorComp>(0), static_cast<GfxColorComp>(0), static_cast<GfxColorComp>(0));
    const auto b = MakeRGB(static_cast<GfxColorComp>(0), static_cast<GfxColorComp>(0), static_cast<GfxColorComp>(0));

    EXPECT_TRUE(a == b);
}

TEST_F(GfxRGBTest_396, BoundaryLikeValuesExtremesRepresentable_396)
{
    // We don't assume GfxColorComp's exact underlying type/range.
    // These values are chosen to be broadly representable for common integer/fixed-point types.
    const auto low  = MakeRGB(static_cast<GfxColorComp>(-1), static_cast<GfxColorComp>(-1), static_cast<GfxColorComp>(-1));
    const auto low2 = MakeRGB(static_cast<GfxColorComp>(-1), static_cast<GfxColorComp>(-1), static_cast<GfxColorComp>(-1));
    const auto high = MakeRGB(static_cast<GfxColorComp>(255), static_cast<GfxColorComp>(255), static_cast<GfxColorComp>(255));

    EXPECT_TRUE(low == low2);
    EXPECT_FALSE(low == high);
}

} // namespace