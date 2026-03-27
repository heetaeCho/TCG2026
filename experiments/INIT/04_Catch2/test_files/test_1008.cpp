// File: tests/TestSpec_Matches_1008.cpp

#include <gtest/gtest.h>

#include <catch2/catch_test_spec.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_version.hpp> // optional but typically available for sanity include

// Minimal helpers to build a TestCaseInfo using public types.
// We do not rely on, or peek into, any private/internal state.
namespace {

using namespace Catch;

static TestCaseInfo makeTestCaseInfo(
    StringRef className,
    StringRef name,
    StringRef tags = StringRef{},
    SourceLineInfo line = SourceLineInfo{__FILE__, __LINE__}) {

    // NameAndTags is a public helper type in Catch2 for constructing TestCaseInfo.
    NameAndTags nat;
    nat.name = std::string{name};
    nat.tags = std::string{tags};

    // Construct via the public constructor only.
    return TestCaseInfo(className, nat, line);
}

} // namespace

// Fixture kept trivial for clarity; no touching of private state.
class TestSpecTest_1008 : public ::testing::Test {};

// [Normal / Boundary] Default-constructed TestSpec has no filters.
TEST_F(TestSpecTest_1008, HasNoFiltersByDefault_1008) {
    Catch::TestSpec spec;
    // Observable via public API only.
    // If hasFilters() is exposed as const bool hasFilters(), assert it's false.
    EXPECT_FALSE(spec.hasFilters());
}

// [Boundary] matches() on an empty TestSpec returns false for any test case.
TEST_F(TestSpecTest_1008, MatchesReturnsFalseWhenNoFilters_1008) {
    Catch::TestSpec spec;

    auto tc1 = makeTestCaseInfo("ClassA", "Alpha");
    auto tc2 = makeTestCaseInfo("ClassB", "Beta", "[tag1][fast]");
    auto tc3 = makeTestCaseInfo("", "Gamma with spaces", "[slow][!]");

    // With no filters present, there is nothing that can match; observable result is false.
    EXPECT_FALSE(spec.matches(tc1));
    EXPECT_FALSE(spec.matches(tc2));
    EXPECT_FALSE(spec.matches(tc3));
}

// [Robustness] matches() should be callable for varied inputs and not throw.
TEST_F(TestSpecTest_1008, MatchesIsNonThrowingForTypicalInputs_1008) {
    Catch::TestSpec spec;

    auto tc = makeTestCaseInfo("SomeClass", "SomeName", "[a][b][c]");
    // We don't assert noexcept on signature, but we verify it does not throw at runtime.
    EXPECT_NO_THROW({
        const bool r = spec.matches(tc);
        (void)r; // suppress unused warning
    });
}

// [Sanity] By default (no parsing performed), invalid specs are empty.
TEST_F(TestSpecTest_1008, InvalidSpecsEmptyByDefault_1008) {
    Catch::TestSpec spec;
    const auto& invalid = spec.getInvalidSpecs();
    EXPECT_TRUE(invalid.empty());
}
