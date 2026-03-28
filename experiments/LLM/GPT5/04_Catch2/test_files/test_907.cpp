// File: tests/benchmark_resolution_tests_907.cpp
#include <gtest/gtest.h>
#include <vector>
#include <chrono>

// Include the header under test
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::resolution;

// A controllable fake clock to drive observable behavior of resolution<Clock>(k)
// Provides std::chrono-compatible types and a deterministic now().
struct TestClock907 {
    using rep        = long long;
    using period     = std::nano;
    using duration   = std::chrono::duration<rep, period>;
    using time_point = std::chrono::time_point<TestClock907>;
    static constexpr bool is_steady = true;

    // Resets the sequence of *intervals* (deltas) between consecutive time points.
    // The clock will return a sequence of k+1 time points:
    //   t0 = epoch
    //   t1 = t0 + deltas[0]
    //   t2 = t1 + deltas[1]
    //   ...
    static void reset(const std::vector<rep>& next_deltas_ns) {
        deltas_ = next_deltas_ns;
        cumulative_ = 0;
        calls_ = 0;
    }

    static time_point now() {
        // On first call return epoch + 0; after that add the next delta.
        if (calls_ > 0) {
            // If calls_ == number of already returned points,
            // we add the (calls_-1)-th delta to cumulative.
            size_t idx = static_cast<size_t>(calls_ - 1);
            if (idx < deltas_.size()) {
                cumulative_ += deltas_[idx];
            }
        }
        ++calls_;
        return time_point(duration(cumulative_));
    }

    static size_t calls() { return calls_; }

private:
    static inline std::vector<rep> deltas_{};
    static inline rep cumulative_{0};
    static inline size_t calls_{0};
};

class ResolutionTest_907 : public ::testing::Test {
protected:
    // Helper that runs resolution<TestClock907>(k) after seeding the clock with deltas.
    // `deltas` must have size == k; each entry is in nanoseconds.
    static std::vector<double> Run(int k, const std::vector<long long>& deltas) {
        TestClock907::reset(deltas);
        return resolution<TestClock907>(k);
    }
};

// ----- Tests -----

// Boundary: k == 0 → returns empty vector, and should still call now() exactly once (k+1).
TEST_F(ResolutionTest_907, ReturnsEmptyForZeroK_907) {
    const int k = 0;
    auto out = Run(k, /*deltas=*/{});
    EXPECT_TRUE(out.empty());
    EXPECT_EQ(TestClock907::calls(), static_cast<size_t>(k + 1)); // one call to seed t0
}

// Normal operation: size equals k and values equal provided deltas (in ns) cast to double.
TEST_F(ResolutionTest_907, ProducesKElementsAndCorrectDeltas_907) {
    const int k = 3;
    // Intervals in nanoseconds: [5, 10, 15]
    std::vector<long long> deltas = {5, 10, 15};
    auto out = Run(k, deltas);

    ASSERT_EQ(out.size(), static_cast<size_t>(k));
    EXPECT_DOUBLE_EQ(out[0], static_cast<double>(deltas[0]));
    EXPECT_DOUBLE_EQ(out[1], static_cast<double>(deltas[1]));
    EXPECT_DOUBLE_EQ(out[2], static_cast<double>(deltas[2]));
}

// Interaction verification: Clock::now() is invoked exactly k+1 times.
TEST_F(ResolutionTest_907, CallsClockNowKPlusOneTimes_907) {
    const int k = 4;
    std::vector<long long> deltas = {1, 1, 1, 1}; // exact values don't matter for call count
    auto out = Run(k, deltas);

    ASSERT_EQ(out.size(), static_cast<size_t>(k));
    EXPECT_EQ(TestClock907::calls(), static_cast<size_t>(k + 1));
}

// Edge behavior: non-monotonic time points produce negative deltas; verify values are preserved.
TEST_F(ResolutionTest_907, SupportsNegativeDeltas_907) {
    const int k = 3;
    // Time goes forward by +7, then backward by -5, then forward by +2 → deltas should mirror these.
    std::vector<long long> deltas = {7, -5, 2};
    auto out = Run(k, deltas);

    ASSERT_EQ(out.size(), static_cast<size_t>(k));
    EXPECT_DOUBLE_EQ(out[0], static_cast<double>(7));
    EXPECT_DOUBLE_EQ(out[1], static_cast<double>(-5));
    EXPECT_DOUBLE_EQ(out[2], static_cast<double>(2));
}
