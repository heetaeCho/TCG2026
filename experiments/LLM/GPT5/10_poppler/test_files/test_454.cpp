// ============================================================================
// Unit tests for GfxLabColorSpace::getBlackZ()
// File: GfxLabColorSpace_getBlackZ_454_test.cc
// ============================================================================

#include <gtest/gtest.h>

#include <cmath>
#include <memory>

#include "GfxState.h"

class GfxLabColorSpaceTest_454 : public ::testing::Test {};

// Normal operation: getter can be called repeatedly and is stable.
TEST_F(GfxLabColorSpaceTest_454, GetBlackZ_IsStableAcrossRepeatedCalls_454)
{
    GfxLabColorSpace cs;

    const double z1 = cs.getBlackZ();
    const double z2 = cs.getBlackZ();

    // Observable behavior: repeated calls should return the same value.
    EXPECT_DOUBLE_EQ(z1, z2);
}

// Boundary-ish: works through a const reference (const-correctness) and returns a sane double.
TEST_F(GfxLabColorSpaceTest_454, GetBlackZ_WorksOnConstReferenceAndIsNotNaN_454)
{
    const GfxLabColorSpace cs;

    const double z = cs.getBlackZ();

    // Do not assume any specific numeric value; just ensure it's a valid double (not NaN).
    EXPECT_FALSE(std::isnan(z));
}

// Normal operation + observable external effect via interface: copy() preserves the getter value.
TEST_F(GfxLabColorSpaceTest_454, Copy_PreservesBlackZValue_454)
{
    GfxLabColorSpace cs;
    const double z = cs.getBlackZ();

    // copy() is part of the public interface; verify observable equivalence for getBlackZ().
    auto copiedBase = cs.copy();
    ASSERT_TRUE(copiedBase);

    auto *copiedLab = dynamic_cast<GfxLabColorSpace *>(copiedBase.get());
    ASSERT_NE(copiedLab, nullptr);

    EXPECT_DOUBLE_EQ(copiedLab->getBlackZ(), z);
}

// Boundary: multiple copies remain consistent and are distinct objects.
TEST_F(GfxLabColorSpaceTest_454, Copy_MultipleCopiesHaveSameBlackZAndDifferentAddresses_454)
{
    GfxLabColorSpace cs;
    const double z = cs.getBlackZ();

    auto c1 = cs.copy();
    auto c2 = cs.copy();

    ASSERT_TRUE(c1);
    ASSERT_TRUE(c2);
    EXPECT_NE(c1.get(), c2.get());

    auto *lab1 = dynamic_cast<GfxLabColorSpace *>(c1.get());
    auto *lab2 = dynamic_cast<GfxLabColorSpace *>(c2.get());
    ASSERT_NE(lab1, nullptr);
    ASSERT_NE(lab2, nullptr);

    EXPECT_DOUBLE_EQ(lab1->getBlackZ(), z);
    EXPECT_DOUBLE_EQ(lab2->getBlackZ(), z);
}