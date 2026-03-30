// SPDX-License-Identifier: GPL-2.0-or-later
// File: ASCIIHexStream_getKind_tests_179.cpp

#include <gtest/gtest.h>

#include "poppler/Stream.h"

// These tests treat ASCIIHexStream as a black box and only verify behavior
// observable through the public interface.

class ASCIIHexStreamTest_179 : public ::testing::Test {};

TEST_F(ASCIIHexStreamTest_179, GetKindReturnsAsciiHex_ForTypicalValues_179)
{
    // Normal operation: regardless of constructor argument, getKind() should
    // report the ASCIIHex stream kind.
    ASCIIHexStream s0(0);
    EXPECT_EQ(strASCIIHex, s0.getKind());

    ASCIIHexStream sA('A');
    EXPECT_EQ(strASCIIHex, sA.getKind());

    ASCIIHexStream s1(1);
    EXPECT_EQ(strASCIIHex, s1.getKind());
}

TEST_F(ASCIIHexStreamTest_179, GetKindReturnsAsciiHex_ForBoundaryLikeValues_179)
{
    // Boundary conditions for the int constructor parameter.
    ASCIIHexStream sNeg1(-1);
    EXPECT_EQ(strASCIIHex, sNeg1.getKind());

    ASCIIHexStream sMaxByte(255);
    EXPECT_EQ(strASCIIHex, sMaxByte.getKind());

    ASCIIHexStream sLarge(1 << 20);
    EXPECT_EQ(strASCIIHex, sLarge.getKind());
}

TEST_F(ASCIIHexStreamTest_179, GetKindCallableOnConstObject_179)
{
    // Const-correctness / observable behavior through const interface.
    const ASCIIHexStream s(0);
    EXPECT_EQ(strASCIIHex, s.getKind());
}