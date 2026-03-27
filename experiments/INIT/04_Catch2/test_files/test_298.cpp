// File: assertion_result_hasExpandedExpression_tests_298.cpp
#include <gtest/gtest.h>
#include <string>

// ----- Minimal public surface needed for testing -----
// We only declare what's necessary to exercise observable behavior.
namespace Catch {
    struct AssertionInfo;          // incomplete is fine; we never use it
    struct AssertionResultData;    // incomplete is fine; we never use it

    class AssertionResult {
    public:
        AssertionResult(AssertionInfo const&, AssertionResultData&&);

        // Collaborators that hasExpandedExpression() depends on.
        bool hasExpression() const;
        std::string getExpression() const;
        std::string getExpandedExpression() const;

        // Function under test (real implementation included from the prod .cpp).
        bool hasExpandedExpression() const;
    };
} // namespace Catch

// Include the real production implementation of hasExpandedExpression()
// (treating the class as a black box).
#include "Catch2/src/catch2/catch_assertion_result.cpp"

// ----- Test seams for the collaborators -----
// These stub definitions simulate *observable* behavior via globals.
// They do NOT reimplement hasExpandedExpression() itself.
namespace Catch {
    // Controls for stubs
    static bool        g_hasExpr = false;
    static std::string g_expr;
    static std::string g_expanded;
    static int         g_getExprCalls = 0;
    static int         g_getExpandedCalls = 0;

    // Trivial ctor to allow instantiation without relying on internals.
    AssertionResult::AssertionResult(AssertionInfo const&, AssertionResultData&&) {}

    bool AssertionResult::hasExpression() const { return g_hasExpr; }

    std::string AssertionResult::getExpression() const {
        ++g_getExprCalls;
        return g_expr;
    }

    std::string AssertionResult::getExpandedExpression() const {
        ++g_getExpandedCalls;
        return g_expanded;
    }
} // namespace Catch

// ----- Test fixture -----
class AssertionResult_HasExpandedExpr_Test : public ::testing::Test {
protected:
    void SetUp() override {
        // reset seams before each test
        Catch::g_hasExpr = false;
        Catch::g_expr.clear();
        Catch::g_expanded.clear();
        Catch::g_getExprCalls     = 0;
        Catch::g_getExpandedCalls = 0;
    }

    // Helper to build an instance without touching internals
    Catch::AssertionResult makeSubject() {
        // Dummy, never used by our stubs
        static Catch::AssertionInfo* dummyInfoPtr = nullptr;
        static Catch::AssertionResultData* dummyDataPtr = nullptr;
        // Provide lvalue for rvalue parameter; body of ctor ignores it.
        return Catch::AssertionResult(*dummyInfoPtr, std::move(*dummyDataPtr));
    }
};

// ----- Tests -----

// Normal operation: when there is an expression and expanded != original -> true
TEST_F(AssertionResult_HasExpandedExpr_Test, ReturnsTrueWhenExpandedDiffers_298) {
    Catch::g_hasExpr  = true;
    Catch::g_expr     = "a == b";
    Catch::g_expanded = "1 == 2"; // different => should be considered expanded

    auto ar = makeSubject();
    EXPECT_TRUE(ar.hasExpandedExpression());
}

// Boundary: expression present but expanded text equals original -> false
TEST_F(AssertionResult_HasExpandedExpr_Test, ReturnsFalseWhenExpandedEqualsOriginal_298) {
    Catch::g_hasExpr  = true;
    Catch::g_expr     = "x";
    Catch::g_expanded = "x"; // identical

    auto ar = makeSubject();
    EXPECT_FALSE(ar.hasExpandedExpression());
}

// Boundary: empty strings (present expression, both empty) -> not expanded
TEST_F(AssertionResult_HasExpandedExpr_Test, ReturnsFalseForEmptyButPresentExpression_298) {
    Catch::g_hasExpr  = true;
    Catch::g_expr     = "";
    Catch::g_expanded = ""; // identical empties

    auto ar = makeSubject();
    EXPECT_FALSE(ar.hasExpandedExpression());
}

// Observable interaction: when hasExpression() is false, getters are not consulted
// (short-circuit behavior) and result is false.
TEST_F(AssertionResult_HasExpandedExpr_Test, ShortCircuitsWhenNoExpression_298) {
    Catch::g_hasExpr  = false;
    Catch::g_expr     = "anything";
    Catch::g_expanded = "different";

    auto ar = makeSubject();
    EXPECT_FALSE(ar.hasExpandedExpression());

    // Verify no observable calls to the getters occurred
    EXPECT_EQ(Catch::g_getExprCalls, 0);
    EXPECT_EQ(Catch::g_getExpandedCalls, 0);
}
