// File: tests/Chronometer_runs_tests_892.cpp

#include <gtest/gtest.h>

// Include the amalgamated header exposing Catch::Benchmark::Chronometer
#include "Catch2/extras/catch_amalgamated.hpp"

// Minimal stub to satisfy the constructor dependency. This does not
// re-implement or simulate any internal behavior; it's just a concrete
// type so we can pass a reference to the Chronometer ctor.
namespace Catch { namespace Benchmark { namespace Detail {
struct ChronometerConcept {};
}}} // namespace Catch::Benchmark::Detail

using Catch::Benchmark::Chronometer;
using Catch::Benchmark::Detail::ChronometerConcept;

class ChronometerTest_892 : public ::testing::Test {
protected:
    ChronometerConcept meter_; // dummy collaborator instance
};

// Normal operation: repeats = 0
TEST_F(ChronometerTest_892, RunsReturnsZeroWhenConstructedWithZero_892) {
    Chronometer c(meter_, /*repeats_=*/0);
    EXPECT_EQ(c.runs(), 0);
}

// Normal operation: small positive repeats
TEST_F(ChronometerTest_892, RunsReturnsPositiveWhenConstructedWithPositive_892) {
    Chronometer c1(meter_, 1);
    EXPECT_EQ(c1.runs(), 1);

    Chronometer c2(meter_, 5);
    EXPECT_EQ(c2.runs(), 5);
}

// Boundary-ish: larger positive repeats
TEST_F(ChronometerTest_892, RunsReturnsLargePositiveValue_892) {
    Chronometer c(meter_, 1000000);
    EXPECT_EQ(c.runs(), 1000000);
}

// Exceptional/boundary (observable via return): negative input is preserved if allowed by interface
TEST_F(ChronometerTest_892, RunsPreservesNegativeWhenConstructedWithNegative_892) {
    Chronometer c(meter_, -1);
    EXPECT_EQ(c.runs(), -1);
}
