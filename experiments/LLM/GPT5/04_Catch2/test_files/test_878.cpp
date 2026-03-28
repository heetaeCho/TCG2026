// File: tests/version_ostream_878.test.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <limits>

#include "catch2/catch_version.hpp"

using Catch::Version;

class VersionOstreamTest_878 : public ::testing::Test {};

// [Normal] No branch name -> "major.minor.patch"
TEST_F(VersionOstreamTest_878, StreamsVersionWithoutBranch_878) {
    Version v(1u, 2u, 3u, "", 0u);

    std::ostringstream os;
    os << v;

    EXPECT_EQ(os.str(), "1.2.3");
}

// [Normal] With branch name -> "major.minor.patch-branch.build"
TEST_F(VersionOstreamTest_878, StreamsVersionWithBranch_878) {
    Version v(1u, 2u, 3u, "alpha", 4u);

    std::ostringstream os;
    os << v;

    EXPECT_EQ(os.str(), "1.2.3-alpha.4");
}

// [Boundary] All zero components, empty branch -> "0.0.0"
TEST_F(VersionOstreamTest_878, StreamsZeroesWithoutBranch_878) {
    Version v(0u, 0u, 0u, "", 0u);

    std::ostringstream os;
    os << v;

    EXPECT_EQ(os.str(), "0.0.0");
}

// [Boundary] Large values and single-char branch name
TEST_F(VersionOstreamTest_878, StreamsLargeValuesWithBranch_878) {
    const unsigned int U = std::numeric_limits<unsigned int>::max();
    Version v(U, U, U, "x", U);

    std::ostringstream os;
    os << v;

    // Expect "<U>.<U>.<U>-x.<U>"
    std::ostringstream expect;
    expect << U << "." << U << "." << U << "-x." << U;

    EXPECT_EQ(os.str(), expect.str());
}

// [Observable interaction] operator<< returns the same stream to allow chaining
TEST_F(VersionOstreamTest_878, StreamReturnAllo​wsChaining_878) {
    Version v(1u, 0u, 0u, "", 0u);

    std::ostringstream os;
    std::ostream& ref = (os << v);
    // Same object returned?
    EXPECT_EQ(&ref, static_cast<std::ostream*>(&os));

    // Chaining should append further content
    (os << v) << 'X';
    EXPECT_EQ(os.str(), "1.0.01.0.0X");
}

// [Boundary] Empty-string vs non-empty branch toggles suffix presence
TEST_F(VersionOstreamTest_878, BranchPresenceTogglesSuffix_878) {
    Version noBranch(3u, 4u, 5u, "", 99u);
    Version withBranch(3u, 4u, 5u, "dev", 99u);

    std::ostringstream os1, os2;
    os1 << noBranch;
    os2 << withBranch;

    EXPECT_EQ(os1.str(), "3.4.5");
    EXPECT_EQ(os2.str(), "3.4.5-dev.99");
}
