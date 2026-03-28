// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 132
//
// Unit tests for BaseSeekInputStream::getKind() (black-box via public interface)

#include <gtest/gtest.h>

#include "Stream.h" // ./TestProjects/poppler/poppler/Stream.h

class BaseSeekInputStreamTest_132 : public ::testing::Test {};

// Normal operation: getKind() returns the expected StreamKind.
TEST_F(BaseSeekInputStreamTest_132, GetKindReturnsWeird_132)
{
    BaseSeekInputStream s;
    EXPECT_EQ(s.getKind(), strWeird);
}

// Boundary-ish: callable on const instances (const-correctness observable via compilation & runtime).
TEST_F(BaseSeekInputStreamTest_132, GetKindWorksOnConstObject_132)
{
    const BaseSeekInputStream s;
    EXPECT_EQ(s.getKind(), strWeird);
}

// Boundary-ish: repeated calls are stable/consistent.
TEST_F(BaseSeekInputStreamTest_132, GetKindIsStableAcrossMultipleCalls_132)
{
    BaseSeekInputStream s;

    const StreamKind k1 = s.getKind();
    const StreamKind k2 = s.getKind();
    const StreamKind k3 = s.getKind();

    EXPECT_EQ(k1, strWeird);
    EXPECT_EQ(k2, strWeird);
    EXPECT_EQ(k3, strWeird);
    EXPECT_EQ(k1, k2);
    EXPECT_EQ(k2, k3);
}