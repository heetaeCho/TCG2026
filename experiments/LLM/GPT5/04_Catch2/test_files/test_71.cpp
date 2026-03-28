// File: stream_end_stop_tests_71.cpp
#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <type_traits>

#include <catch2/internal/catch_stream_end_stop.hpp>

using Catch::StreamEndStop;

// Normal operation with an lvalue primitive: returns same reference and value
TEST(StreamEndStopTest_71, ReturnsSameReferenceForIntLvalue_71) {
    int x = 123;
    const int& r = x + StreamEndStop{};
    // Same address => same object (no copy constructed)
    ASSERT_EQ(&r, &x);
    EXPECT_EQ(r, 123);

    // Type-level check: expression yields const int&
    static_assert(std::is_same<decltype(x + StreamEndStop{}), const int&>::value,
                  "operator+ must return const T&");
}

// Normal operation with std::string lvalue: aliasing and value preserved
TEST(StreamEndStopTest_71, ReturnsSameReferenceForStdString_71) {
    std::string s = "hello";
    const std::string& rs = s + StreamEndStop{};
    ASSERT_EQ(&rs, &s);                 // aliasing
    EXPECT_EQ(rs, "hello");             // value preserved

    // Mutate the original; the const ref must observe the change (aliasing evidence)
    s[0] = 'H';
    EXPECT_EQ(rs, "Hello");
}

// Boundary-ish usage with rvalue: lifetime extension via const reference
TEST(StreamEndStopTest_71, WorksWithRvalueLifetimeExtension_71) {
    const std::string& rr = std::string("abc") + StreamEndStop{};
    EXPECT_EQ(rr, "abc");  // valid because of lifetime extension of the temporary
}

// Supports move-only types (e.g., std::unique_ptr) without copying
TEST(StreamEndStopTest_71, SupportsMoveOnlyTypes_NoCopy_71) {
    auto up = std::make_unique<int>(5);
    const auto& rup = up + StreamEndStop{};
    // Same object, no copies implied by interface
    ASSERT_EQ(&rup, &up);
    // The managed pointer is unchanged
    ASSERT_NE(rup.get(), nullptr);
    EXPECT_EQ(*rup, 5);
}

// Constexpr usability: operator is constexpr per signature and should work in constant expressions
TEST(StreamEndStopTest_71, UsableInConstexpr_71) {
    constexpr int cx = 7;
    // Use result in a constant expression; reads const glvalue of a constexpr object
    constexpr int cy = (cx + StreamEndStop{});
    static_assert(cy == 7, "constexpr use should preserve value");
    EXPECT_EQ(cy, 7);
}
