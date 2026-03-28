// File: tests/optimized_away_error_tests_983.cpp

#include <gtest/gtest.h>
#include <exception>
#include <cstring>

// Try common include locations for the amalgamated Catch2 header that declares the exception.
// Adjust include path as needed in your build.
#if __has_include(<catch_amalgamated.hpp>)
  #include <catch_amalgamated.hpp>
#elif __has_include(<Catch2/catch_amalgamated.hpp>)
  #include <Catch2/catch_amalgamated.hpp>
#else
  // Fall back to the main Catch2 header if your tree exposes it this way.
  #if __has_include(<catch2/catch_all.hpp>)
    #include <catch2/catch_all.hpp>
  #endif
#endif

namespace {
using OAError = Catch::Benchmark::Detail::optimized_away_error;
constexpr const char* kExpectedMsg =
    "could not measure benchmark, maybe it was optimized away";
}  // namespace

// Verifies the exact message returned by what().
TEST(OptimizedAwayErrorTest_983, WhatReturnsExactMessage_983) {
    OAError e;
    // Observable behavior: exact, stable message
    EXPECT_STREQ(kExpectedMsg, e.what());
    // Also verify it is a properly formed C-string (non-empty and length matches)
    EXPECT_GT(std::strlen(e.what()), 0u);
    EXPECT_EQ(std::strlen(e.what()), std::strlen(kExpectedMsg));
}

// Verifies the message when accessed polymorphically via std::exception.
TEST(OptimizedAwayErrorTest_983, PolymorphicWhatViaStdException_983) {
    OAError e;
    const std::exception& base = e; // upcast
    EXPECT_STREQ(kExpectedMsg, base.what());
}

// Verifies the noexcept/throwing behavior in observable ways.
TEST(OptimizedAwayErrorTest_983, WhatIsNoThrowAndNoexcept_983) {
    OAError e;
    // Runtime: must not throw
    EXPECT_NO_THROW({ (void)e.what(); });
    // Compile-time: what() is declared noexcept
    static_assert(noexcept(e.what()), "what() must be noexcept");
}

// Verifies stability across multiple calls (observable behavior).
TEST(OptimizedAwayErrorTest_983, WhatIsStableAcrossCalls_983) {
    OAError e;
    const char* first = e.what();
    const char* second = e.what();

    // At minimum, the contents should match the expected message each time.
    EXPECT_STREQ(kExpectedMsg, first);
    EXPECT_STREQ(kExpectedMsg, second);

    // Many std::exception implementations return the same pointer each time.
    // We don't *require* pointer identity, but if it is the same, this assertion passes.
    // If your implementation returns a different buffer each call, the following line
    // can be relaxed to only check content equality (already done above).
    EXPECT_EQ(first, second);
}
