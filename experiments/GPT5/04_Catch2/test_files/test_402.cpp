// tests/test_composable_parser_impl_402.cpp
#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>

// Include the header that contains the implementation under test.
// (The build harness provides this path.)
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace Catch { namespace Clara { namespace Detail {

// ---- Test-only collaborators / helpers ----

// Forward-declare the derived and operand marker types we'll use in tests.
struct TestDerived_402;
struct Other_402;
struct OtherUnknown_402;

// A minimal stub for the external collaborator `Parser`.
// It records the sequence of items piped into it so we can assert ordering.
// This is a *collaborator stub*, not a simulation of internal behavior.
struct Parser {
    std::shared_ptr<std::vector<std::string>> log;

    Parser() : log(std::make_shared<std::vector<std::string>>()) {}
    explicit Parser(std::shared_ptr<std::vector<std::string>> l) : log(std::move(l)) {}

    const std::vector<std::string>& sequence() const { return *log; }

    template <typename U>
    Parser operator|(U const& u) const {
        auto l = log; // share the same buffer through the chain
        l->push_back(tag(u));
        return Parser{l};
    }

private:
    // Tag overloads let us label what flowed through the pipe without RTTI.
    static std::string tag(TestDerived_402 const&) { return "Derived"; }
    static std::string tag(Other_402 const&)       { return "Other"; }
    static std::string tag(OtherUnknown_402 const&){ return "Unknown"; }

    // Fallback for anything else (shouldn't be used in these tests)
    template <typename U>
    static std::string tag(U const&) { return "Unknown"; }
};

// A simple "DerivedT" that participates in CRTP with the class under test.
struct TestDerived_402 : ComposableParserImpl<TestDerived_402> {};

// Additional operand marker types for tests
struct Other_402 {};
struct OtherUnknown_402 {};

}}} // namespace Catch::Clara::Detail

using namespace Catch::Clara::Detail;

class ComposableParserImplTest_402 : public ::testing::Test {};

// Verifies that piping with `other` calls the collaborator in the correct order:
// Parser() | static_cast<DerivedT const&>(*this) | other
TEST_F(ComposableParserImplTest_402, PipeOrdersDerivedThenOther_402) {
    TestDerived_402 d;
    Other_402 other;

    Parser result = d | other; // uses the implementation under test

    ASSERT_EQ(result.sequence().size(), 2u);
    EXPECT_EQ(result.sequence()[0], "Derived");
    EXPECT_EQ(result.sequence()[1], "Other");
}

// Ensures the operator is `const`-correct and still preserves ordering.
TEST_F(ComposableParserImplTest_402, WorksWithConstInstance_402) {
    const TestDerived_402 d_const;
    Other_402 other;

    Parser result = d_const | other;

    ASSERT_EQ(result.sequence().size(), 2u);
    EXPECT_EQ(result.sequence()[0], "Derived");
    EXPECT_EQ(result.sequence()[1], "Other");
}

// Compile-time check: the return type of `derived | other` is exactly `Parser`.
TEST_F(ComposableParserImplTest_402, ReturnTypeIsParser_402) {
    static_assert(std::is_same<
        decltype(std::declval<const TestDerived_402&>() | std::declval<const Other_402&>()),
        Parser
    >::value, "operator| must return Parser");
    SUCCEED(); // If it compiles, we passed.
}

// Boundary-ish case: piping with an unsupported/unknown operand still preserves
// the fact that the Derived part flows first, then the Other.
TEST_F(ComposableParserImplTest_402, UnknownOtherStillPipesAfterDerived_402) {
    TestDerived_402 d;
    OtherUnknown_402 other_unknown;

    Parser result = d | other_unknown;

    ASSERT_EQ(result.sequence().size(), 2u);
    EXPECT_EQ(result.sequence()[0], "Derived");
    EXPECT_EQ(result.sequence()[1], "Unknown"); // from our collaborator stub's fallback
}

// Edge case: using the same type as both "derived" and "other" compiles and pipes twice.
// We only assert the observable order (first derived, then other).
TEST_F(ComposableParserImplTest_402, DerivedAsOtherPipesTwiceInOrder_402) {
    TestDerived_402 d;

    Parser result = d | TestDerived_402{}; // 'other' is same nominal type

    ASSERT_EQ(result.sequence().size(), 2u);
    EXPECT_EQ(result.sequence()[0], "Derived");
    EXPECT_EQ(result.sequence()[1], "Derived");
}
