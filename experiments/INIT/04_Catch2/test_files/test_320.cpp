// File: generators_get_tests_320.cpp
#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include <vector>

// Adjust include path if needed for your project layout.
#include "Catch2/src/catch2/generators/catch_generators.hpp"

namespace {

template <typename G, typename T>
std::vector<T> CollectAll(G& gen) {
    // Only uses the public interface: get() and next()
    std::vector<T> out;
    out.push_back(gen.get());
    while (gen.next()) {
        out.push_back(gen.get());
    }
    return out;
}

} // namespace

// ---------- Compile-time interface checks (no internal logic assumed) ----------
static_assert(std::is_same<
                  decltype(std::declval<Catch::Generators::Generators<int> const>().get()),
                  int const&>::value,
              "get() must return T const&");

// ------------------------------ Tests ------------------------------

TEST(GeneratorsGetTest_320, ReturnsFirstValueInitially_320) {
    // Normal operation: constructed with multiple values, get() returns the first.
    Catch::Generators::Generators<int> gen{1, 2, 3};
    EXPECT_EQ(gen.get(), 1);
}

TEST(GeneratorsGetTest_320, GetDoesNotAdvanceState_320) {
    // Calling get() repeatedly without next() should keep returning the same observable value.
    Catch::Generators::Generators<int> gen{10, 20};
    const int& a = gen.get();
    const int& b = gen.get();
    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 10);

    // Because get() returns a const&, the referenced object identity should remain stable
    // (observable by comparing addresses of the references).
    EXPECT_EQ(&a, &b);
}

TEST(GeneratorsGetTest_320, NextTraversesValuesThenStops_320) {
    // Normal iteration behavior across provided values.
    Catch::Generators::Generators<int> gen{5, 6, 7};
    // Collect using only get()/next() to assert observable sequence.
    auto observed = CollectAll<decltype(gen), int>(gen);
    std::vector<int> expected{5, 6, 7};
    EXPECT_EQ(observed, expected);

    // Boundary: After the generator reports completion (last next() returned false),
    // further next() calls should remain false (idempotent completion).
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
}

TEST(GeneratorsGetTest_320, SingleValueBoundary_320) {
    // Boundary case: single element.
    Catch::Generators::Generators<int> gen{42};
    EXPECT_EQ(gen.get(), 42);
    // With a single value, advancing should immediately indicate completion.
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next()); // remain completed
}

TEST(GeneratorsGetTest_320, WorksWithNonTrivialType_String_320) {
    // Ensure get() works for non-trivial types by observable behavior only.
    Catch::Generators::Generators<std::string> gen{std::string("alpha"), std::string("beta")};
    EXPECT_EQ(gen.get(), "alpha");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "beta");
    EXPECT_FALSE(gen.next());
}

TEST(GeneratorsGetTest_320, ReferenceStabilityAcrossMultipleGets_320) {
    // More explicit reference stability check (observable & non-invasive):
    Catch::Generators::Generators<std::string> gen{std::string("x"), std::string("y")};

    auto const& r1 = gen.get();
    auto const& r2 = gen.get();
    EXPECT_EQ(r1, "x");
    EXPECT_EQ(r2, "x");
    EXPECT_EQ(&r1, &r2);  // same object reference until next() is called

    // After advancing, the observable value changes
    ASSERT_TRUE(gen.next());
    auto const& r3 = gen.get();
    EXPECT_EQ(r3, "y");
    // Not asserting address relationship across different logical positions:
    // we only assert the observable value changed after next().
}

TEST(GeneratorsGetTest_320, SequenceMatchesInsertionOrder_320) {
    // Normal operation: verify observable sequence equals the order of construction parameters.
    Catch::Generators::Generators<int> gen{3, 1, 4, 1, 5};
    auto observed = CollectAll<decltype(gen), int>(gen);
    std::vector<int> expected{3, 1, 4, 1, 5};
    EXPECT_EQ(observed, expected);
}
