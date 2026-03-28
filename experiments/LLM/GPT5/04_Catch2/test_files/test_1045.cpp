// File: tests/TestSpecParser_test_1045.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <type_traits>

// Catch2 headers (public interfaces only)
#include <catch2/internal/catch_test_spec_parser.hpp>
#include <catch2/interfaces/catch_interfaces_tag_alias_registry.hpp>
#include <catch2/catch_test_case_info.hpp> // for observable matching (if used)
#include <catch2/catch_version.hpp>        // not required, but keeps CI envs happy

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

namespace {

// Minimal mock of the external collaborator.
// We assert that calling `testSpec()` itself does not interact with the tag alias registry.
class MockTagAliasRegistry final : public Catch::ITagAliasRegistry {
public:
    MOCK_METHOD(Catch::TagAlias const*, find, (std::string const&), (const, override));
};

struct TestSpecParserFixture_1045 : public ::testing::Test {
    StrictMock<MockTagAliasRegistry> mockAliases; // strict to catch unintended calls

    // Helper to build a parser bound to our mock registry
    Catch::TestSpecParser makeParser() {
        return Catch::TestSpecParser(mockAliases);
    }
};

} // namespace

// --- Normal operation: calling testSpec() without prior parse returns a TestSpec object.
TEST_F(TestSpecParserFixture_1045, ReturnsA_TestSpec_Object_1045) {
    auto parser = makeParser();

    // No alias lookups are expected purely from testSpec() call.
    // (StrictMock will fail the test if testSpec() performs any find() call.)
    EXPECT_NO_THROW({
        Catch::TestSpec spec = parser.testSpec();
        (void)spec; // silence unused warning; presence/constructibility is the observable here
    });
}

// --- Boundary: calling testSpec() multiple times should be safe (no crashes, no extra alias lookups).
TEST_F(TestSpecParserFixture_1045, MultipleCallsAreSafe_1045) {
    auto parser = makeParser();

    EXPECT_NO_THROW({
        Catch::TestSpec s1 = parser.testSpec();
        Catch::TestSpec s2 = parser.testSpec();
        (void)s1;
        (void)s2;
    });
}

// --- Normal operation with prior parse(): the returned TestSpec should reflect that
// parsing happened in some observable way. We keep observations conservative:
// 1) testSpec() itself should not query aliases.
// 2) Parsing a plain name should not require alias expansion, so we set no expectations.
TEST_F(TestSpecParserFixture_1045, AfterParsingAName_testSpecCompletesPendingFilter_1045) {
    auto parser = makeParser();

    // Parse a simple name fragment; alias registry should not be consulted for plain names.
    // If the underlying parse() consulted aliases here, the StrictMock would fail this test.
    parser.parse("SomeUniqueTestName_1045"); // public API call

    // Obtain the spec; again, no alias lookups should occur during testSpec()
    Catch::TestSpec spec = parser.testSpec();

    // Observable behavior (without peeking into internals):
    // If Catch2's public API is available, we can check whether spec "does something"
    // For the most conservative check that compiles everywhere, assert it is a valid object.
    // Optionally, if TestSpec exposes a public "hasFilters()" (available in Catch2 v3),
    // this is an observable, black-box check:
#if defined(CATCH_VERSION_MAJOR) && (CATCH_VERSION_MAJOR >= 3)
    // Many environments expose hasFilters(); if not available in your tree, feel free to drop this.
    // We expect that after parsing a non-empty name, the constructed TestSpec has at least one filter.
    // This verifies "addFilter()" was considered before returning.
    EXPECT_TRUE(spec.hasFilters()) << "Expected non-empty spec after parsing a name.";
#endif
}

// --- Boundary: parsing empty input then calling testSpec() should be okay (no alias lookups,
// and spec should be usable). If hasFilters() is available, we expect it to be false.
TEST_F(TestSpecParserFixture_1045, EmptyParseThen_testSpec_ProducesUsableSpec_1045) {
    auto parser = makeParser();

    parser.parse(""); // public, observable input; should not need aliases
    Catch::TestSpec spec = parser.testSpec();

#if defined(CATCH_VERSION_MAJOR) && (CATCH_VERSION_MAJOR >= 3)
    EXPECT_FALSE(spec.hasFilters()) << "Empty parse should not create filters.";
#endif
}

// --- Verification of external interactions:
// Prove that aliases are *not* consulted solely by calling testSpec().
// (We simulate a prior parse that would *normally* use aliases only when tags are present.)
// Here we only assert that testSpec() adds no *additional* lookups.
TEST_F(TestSpecParserFixture_1045, testSpec_DoesNotQueryAliases_1045) {
    auto parser = makeParser();

    // No expectations set -> StrictMock ensures that testSpec() itself does not call find().
    // If your codebase’s parse() consults aliases for name-only inputs, avoid calling parse() here.
    Catch::TestSpec spec = parser.testSpec();
    (void)spec;
}

// --- Exceptional/robustness: moving returned TestSpec should be well-defined and not throw.
// We do not assume anything about its contents.
TEST_F(TestSpecParserFixture_1045, ReturnedTestSpecIsMovable_1045) {
    auto parser = makeParser();

    Catch::TestSpec s1 = parser.testSpec();
    // Move-construct and move-assign: observable property (type trait + runtime no-throw path)
    static_assert(std::is_move_constructible<Catch::TestSpec>::value, "TestSpec should be move-constructible");
    static_assert(std::is_move_assignable<Catch::TestSpec>::value,    "TestSpec should be move-assignable");

    EXPECT_NO_THROW({
        Catch::TestSpec s2 = std::move(s1);
        Catch::TestSpec s3 = parser.testSpec();
        s2 = std::move(s3);
        (void)s2;
    });
}

// --- Idempotency-ish observable: calling testSpec() twice after a single parse() call.
// We avoid asserting *what* the second spec means; we only assert calls are safe and
// produce independently movable objects without extra alias lookups.
TEST_F(TestSpecParserFixture_1045, ParseOnce_TwoCallsToTestSpec_AreSafe_1045) {
    auto parser = makeParser();

    parser.parse("AnotherName_1045");

    EXPECT_NO_THROW({
        Catch::TestSpec first = parser.testSpec();
        Catch::TestSpec second = parser.testSpec();
        (void)first;
        (void)second;
    });
}
