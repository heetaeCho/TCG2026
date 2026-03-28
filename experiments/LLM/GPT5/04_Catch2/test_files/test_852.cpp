// File: tests/test_assertion_or_benchmark_result_isAssertion_852.cpp

#include <gtest/gtest.h>

// Prefer including the real header; fall back to a forward declaration shim
// so this test file remains easy to drop into various setups.
#if __has_include("catch2/reporters/catch_reporter_cumulative_base.hpp")
  #include "catch2/reporters/catch_reporter_cumulative_base.hpp"
#else
  // Minimal forward decls to compile the tests if full headers aren't available.
  namespace Catch {
    template <typename...> struct BenchmarkStats {};
    struct AssertionStats {};
    template <typename T> class Optional; // Only forward-declared; real defs assumed in TU.
    namespace Detail {
      class AssertionOrBenchmarkResult {
      public:
        AssertionOrBenchmarkResult(AssertionStats const&);
        AssertionOrBenchmarkResult(BenchmarkStats<> const&);
        bool isAssertion() const;
      };
    } // namespace Detail
  }   // namespace Catch
#endif

// If the project doesn't expose constructors for the stats types or they
// require params, the real headers will provide them. Here we assume default
//-constructible or otherwise constructible per the interface.
namespace {
  // Helper makers keep tests readable without assuming internal details.
  inline Catch::AssertionStats makeAssertionStats() {
    return Catch::AssertionStats{};
  }
  inline Catch::BenchmarkStats<> makeBenchmarkStats() {
    return Catch::BenchmarkStats<>{};
  }
}

using Catch::Detail::AssertionOrBenchmarkResult;

// ========================= TESTS =========================

// Normal operation: Constructed from AssertionStats => isAssertion() is true
TEST(AssertionOrBenchmarkResultTest_852, ConstructWithAssertion_IsAssertionTrue_852) {
  auto a = makeAssertionStats();
  AssertionOrBenchmarkResult result{a};
  EXPECT_TRUE(result.isAssertion());
}

// Normal operation: Constructed from BenchmarkStats => isAssertion() is false
TEST(AssertionOrBenchmarkResultTest_852, ConstructWithBenchmark_IsAssertionFalse_852) {
  auto b = makeBenchmarkStats();
  AssertionOrBenchmarkResult result{b};
  EXPECT_FALSE(result.isAssertion());
}

// Boundary-ish check: Copy-constructed instance preserves observable behavior
TEST(AssertionOrBenchmarkResultTest_852, CopyConstructedFromAssertion_RemainsAssertion_852) {
  auto a = makeAssertionStats();
  AssertionOrBenchmarkResult original{a};
  AssertionOrBenchmarkResult copy = original; // copy-construct
  EXPECT_TRUE(copy.isAssertion());
}

// Boundary-ish check: Move-constructed instance preserves observable behavior
TEST(AssertionOrBenchmarkResultTest_852, MoveConstructedFromBenchmark_RemainsNonAssertion_852) {
  auto b = makeBenchmarkStats();
  AssertionOrBenchmarkResult original{b};
  AssertionOrBenchmarkResult moved = std::move(original); // move-construct
  EXPECT_FALSE(moved.isAssertion());
}

// Idempotence/const-correctness: Multiple calls should consistently reflect state
TEST(AssertionOrBenchmarkResultTest_852, MultipleCalls_ReturnConsistentResult_852) {
  auto a = makeAssertionStats();
  const AssertionOrBenchmarkResult result{a};
  EXPECT_TRUE(result.isAssertion());
  EXPECT_TRUE(result.isAssertion()); // repeat to ensure no hidden mutation
}
