// File: locationToString_test_2685.cc
//
// Unit tests for locationToString(KeyLocation) in ./TestProjects/poppler/utils/pdfsig.cc
// Constraints:
// - Treat implementation as black box (test only observable outputs).
// - No access to private/internal state.
// - Include normal, boundary, and error/exception-like cases (as observable).
//
// Note: locationToString() is declared `static` in pdfsig.cc (internal linkage).
// To test it without changing production code, we include the .cc into this test TU.
// If pdfsig.cc defines a `main`, we rename it to avoid conflicts with gtest main.

#include <gtest/gtest.h>

#include <string>

// Dependency that defines KeyLocation.
#include "TestProjects/poppler/poppler/CertificateInfo.h"

// Avoid potential `main` symbol conflicts if pdfsig.cc is a tool with its own main().
#define main poppler_pdfsig_tool_main_2685
// Some projects also use `wmain` on Windows; rename defensively.
#define wmain poppler_pdfsig_tool_wmain_2685

// Pull in the internal-linkage function into this translation unit.
#include "TestProjects/poppler/utils/pdfsig.cc"

#undef wmain
#undef main

namespace {

class LocationToStringTest_2685 : public ::testing::Test {};

TEST_F(LocationToStringTest_2685, UnknownReturnsEmptyString_2685)
{
    const std::string out = locationToString(KeyLocation::Unknown);
    EXPECT_TRUE(out.empty());
}

TEST_F(LocationToStringTest_2685, OtherReturnsOtherTag_2685)
{
    EXPECT_EQ(locationToString(KeyLocation::Other), "(Other)");
}

TEST_F(LocationToStringTest_2685, ComputerReturnsComputerTag_2685)
{
    EXPECT_EQ(locationToString(KeyLocation::Computer), "(Computer)");
}

TEST_F(LocationToStringTest_2685, HardwareTokenReturnsHardwareTokenTag_2685)
{
    EXPECT_EQ(locationToString(KeyLocation::HardwareToken), "(Hardware Token)");
}

TEST_F(LocationToStringTest_2685, InvalidEnumNegativeReturnsEmptyString_2685)
{
    // Boundary / error-like case: value outside the defined enum set.
    const auto invalid = static_cast<KeyLocation>(-1);
    const std::string out = locationToString(invalid);
    EXPECT_TRUE(out.empty());
}

TEST_F(LocationToStringTest_2685, InvalidEnumLargeReturnsEmptyString_2685)
{
    // Boundary / error-like case: value outside the defined enum set.
    const auto invalid = static_cast<KeyLocation>(999);
    const std::string out = locationToString(invalid);
    EXPECT_TRUE(out.empty());
}

} // namespace