// File: tests/repeater_tests_896.cpp
#include <gtest/gtest.h>
#include <atomic>
#include <stdexcept>

// Include the amalgamated Catch2 header that provides the template declaration
#include "Catch2/extras/catch_amalgamated.hpp"

// We only depend on the *interface* of Catch::Benchmark::Detail::repeater<Fun>:
//   template <typename Fun> struct repeater { public: void operator()(int k) const; }
// The tests below observe behavior only via effects of calling Fun::operator().

namespace {

struct CountingFun {
    static std::atomic<int> counter;
    void operator()() const {
        ++counter;
    }
};
std::atomic<int> CountingFun::counter{0};

struct ThrowingFun {
    void operator()() const {
        throw std::runtime_error("boom");
    }
};

// Fixture to reset static counters between tests
class RepeaterTest_896 : public ::testing::Test {
protected:
    void SetUp() override {
        CountingFun::counter = 0;
    }
};

} // namespace

// Normal operation: k = 1 calls the functor exactly once
TEST_F(RepeaterTest_896, CallsFunctorOnceWhenKIsOne_896) {
    const Catch::Benchmark::Detail::repeater<CountingFun> rep;
    rep(1);
    EXPECT_EQ(CountingFun::counter.load(), 1);
}

// Normal operation: k = 5 calls the functor exactly five times
TEST_F(RepeaterTest_896, CallsFunctorKTimes_896) {
    const Catch::Benchmark::Detail::repeater<CountingFun> rep;
    rep(5);
    EXPECT_EQ(CountingFun::counter.load(), 5);
}

// Boundary: k = 0 should result in zero calls (no observable increments)
TEST_F(RepeaterTest_896, ZeroIterationsDoesNothing_896) {
    const Catch::Benchmark::Detail::repeater<CountingFun> rep;
    rep(0);
    EXPECT_EQ(CountingFun::counter.load(), 0);
}

// Boundary: negative k — we do not assert internal logic, but we can assert that
// no calls to the functor are *observably* made (i.e., no increments and no throw)
TEST_F(RepeaterTest_896, NegativeKMakesNoObservableCalls_896) {
    const Catch::Benchmark::Detail::repeater<CountingFun> rep;
    EXPECT_NO_THROW(rep(-3));
    EXPECT_EQ(CountingFun::counter.load(), 0);
}

// Exceptional behavior propagation: if Fun::operator() throws, calling with k>0
// should surface an exception on invocation. For k==0 there should be no throw.
TEST_F(RepeaterTest_896, PropagatesExceptionsFromFunctorWhenKPositive_896) {
    const Catch::Benchmark::Detail::repeater<ThrowingFun> rep;

    // k == 0: no calls => no throw
    EXPECT_NO_THROW(rep(0));

    // k > 0: at least one call => expect throw (exact count is not asserted)
    EXPECT_THROW(rep(1), std::runtime_error);
}

// Larger input (still quick): verifies repeated observable effect without re-implementing logic
TEST_F(RepeaterTest_896, HandlesModerateIterationCounts_896) {
    const Catch::Benchmark::Detail::repeater<CountingFun> rep;
    const int k = 1000; // keep small enough for fast unit tests
    rep(k);
    EXPECT_EQ(CountingFun::counter.load(), k);
}

// Const-correctness: operator() must be callable on a const instance
TEST_F(RepeaterTest_896, OperatorCallableOnConstInstance_896) {
    const Catch::Benchmark::Detail::repeater<CountingFun> rep;
    rep(2);
    EXPECT_EQ(CountingFun::counter.load(), 2);
}
