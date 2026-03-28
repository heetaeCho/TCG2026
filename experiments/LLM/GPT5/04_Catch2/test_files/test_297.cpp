// File: tests/assertion_result_getExpressionInMacro_297_test.cpp

#include <gtest/gtest.h>

#include "catch2/catch_assertion_result.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {

using namespace Catch;

class AssertionResultGetExpressionInMacroTest_297 : public ::testing::Test {
protected:
    static AssertionResult MakeResult(const char* macroName, const char* capturedExpr) {
        AssertionInfo info{};
        info.macroName = StringRef(macroName);
        info.capturedExpression = StringRef(capturedExpr);

        AssertionResultData data{}; // Treat as opaque; constructed with default state
        return AssertionResult(info, std::move(data));
    }
};

// [Normal] When macro name is non-empty, it wraps the expression with `MACRO( <expr> )` including spaces.
TEST_F(AssertionResultGetExpressionInMacroTest_297, WrapsExpressionWithMacroName_297) {
    auto ar = MakeResult("REQUIRE", "x > 0");
    EXPECT_EQ(ar.getExpressionInMacro(), std::string("REQUIRE( x > 0 )"));
}

// [Normal] When macro name is empty, it returns just the captured expression with no added parentheses/spaces.
TEST_F(AssertionResultGetExpressionInMacroTest_297, ReturnsCapturedExpressionWhenMacroNameEmpty_297) {
    auto ar = MakeResult("", "a == b");
    EXPECT_EQ(ar.getExpressionInMacro(), std::string("a == b"));
}

// [Boundary] Empty captured expression but non-empty macro -> still formats with spaces: "MACRO(  )".
TEST_F(AssertionResultGetExpressionInMacroTest_297, HandlesEmptyCapturedExpression_297) {
    auto ar = MakeResult("CHECK", "");
    EXPECT_EQ(ar.getExpressionInMacro(), std::string("CHECK(  )"));
}

// [Boundary] Both macro and expression empty -> returns empty string.
TEST_F(AssertionResultGetExpressionInMacroTest_297, HandlesBothEmpty_297) {
    auto ar = MakeResult("", "");
    EXPECT_EQ(ar.getExpressionInMacro(), std::string(""));
}

// [Internationalization] Works with UTF-8 macro names and expressions.
TEST_F(AssertionResultGetExpressionInMacroTest_297, SupportsUtf8Text_297) {
    auto ar = MakeResult("테스트", "값 == 변수");
    EXPECT_EQ(ar.getExpressionInMacro(), std::string("테스트( 값 == 변수 )"));
}

// [Preservation] Preserves whitespace inside the captured expression; does not trim.
TEST_F(AssertionResultGetExpressionInMacroTest_297, PreservesWhitespaceInExpression_297) {
    auto ar = MakeResult("ASSERT", "  a + b  ");
    EXPECT_EQ(ar.getExpressionInMacro(), std::string("ASSERT(   a + b   )"));
}

} // namespace
