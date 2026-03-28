// TEST_ID: 480
// File: GfxSeparationColorSpace_getFunc_ut_480.cpp

#include <gtest/gtest.h>

#include <memory>

#include "poppler/GfxState.h"
#include "poppler/Function.h"
#include "goo/GooString.h"

namespace {

// GfxSeparationColorSpace requires an alternate color space; using a concrete one from GfxState.h.
static std::unique_ptr<GfxColorSpace> MakeAltColorSpace()
{
    return std::make_unique<GfxDeviceRGBColorSpace>();
}

static std::unique_ptr<GooString> MakeName(const char *s)
{
    return std::make_unique<GooString>(s);
}

class GfxSeparationColorSpaceTest_480 : public ::testing::Test
{
};

TEST_F(GfxSeparationColorSpaceTest_480, GetFuncReturnsSamePointerWhenProvided_480)
{
    // Arrange
    auto name = MakeName("SpotColor");
    auto alt = MakeAltColorSpace();

    // Use a real concrete Function implementation (IdentityFunction).
    auto funcOwner = std::make_unique<IdentityFunction>();
    Function *rawFunc = funcOwner.release(); // ownership semantics are managed by the class under test.

    GfxSeparationColorSpace cs(std::move(name), std::move(alt), rawFunc);

    // Act
    const Function *got = cs.getFunc();

    // Assert
    EXPECT_EQ(got, rawFunc);
}

TEST_F(GfxSeparationColorSpaceTest_480, GetFuncReturnsNullptrWhenConstructedWithNull_480)
{
    // Arrange
    auto name = MakeName("SpotColor");
    auto alt = MakeAltColorSpace();

    GfxSeparationColorSpace cs(std::move(name), std::move(alt), nullptr);

    // Act / Assert
    EXPECT_EQ(cs.getFunc(), nullptr);
}

TEST_F(GfxSeparationColorSpaceTest_480, GetFuncCallableOnConstObject_480)
{
    // Arrange
    auto name = MakeName("SpotColor");
    auto alt = MakeAltColorSpace();
    auto funcOwner = std::make_unique<IdentityFunction>();
    Function *rawFunc = funcOwner.release();

    const GfxSeparationColorSpace cs(std::move(name), std::move(alt), rawFunc);

    // Act
    const Function *got = cs.getFunc();

    // Assert
    EXPECT_EQ(got, rawFunc);
}

TEST_F(GfxSeparationColorSpaceTest_480, GetFuncIsStableAcrossMultipleCalls_480)
{
    // Arrange
    auto name = MakeName("SpotColor");
    auto alt = MakeAltColorSpace();
    auto funcOwner = std::make_unique<IdentityFunction>();
    Function *rawFunc = funcOwner.release();

    GfxSeparationColorSpace cs(std::move(name), std::move(alt), rawFunc);

    // Act
    const Function *got1 = cs.getFunc();
    const Function *got2 = cs.getFunc();
    const Function *got3 = cs.getFunc();

    // Assert
    EXPECT_EQ(got1, rawFunc);
    EXPECT_EQ(got2, rawFunc);
    EXPECT_EQ(got3, rawFunc);
    EXPECT_EQ(got1, got2);
    EXPECT_EQ(got2, got3);
}

} // namespace