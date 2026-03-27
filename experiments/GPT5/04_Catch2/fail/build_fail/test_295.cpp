// File: tests/assertion_result_hasMessage_295_tests.cpp
#include <gtest/gtest.h>
#include <string>
#include <utility>

// Catch2 public headers (paths follow standard Catch2 v3 layout)
// Adjust include paths if your project uses different ones.
#include <catch2/catch_assertion_result.hpp>
#include <catch2/catch_assertion_info.hpp>
#include <catch2/catch_result_type.hpp>
#include <catch2/catch_user_config.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_lazy_expr.hpp>

namespace {

using namespace Catch;

struct AssertionResultTest_295 : ::testing::Test {
    // Helper to build a minimal, valid AssertionInfo for constructing AssertionResult.
    static AssertionInfo MakeInfo() {
        // Use simple, inert values; they should not affect hasMessage() behavior.
        const StringRef macroName = StringRef("TEST_MACRO");
        const SourceLineInfo lineInfo{StringRef("file.cpp"), 123};
        const StringRef capturedExpr = StringRef("x == y");
        auto flags = ResultDisposition::Normal;
        return AssertionInfo{ macroName, lineInfo, capturedExpr, flags };
    }

    // Helper to construct AssertionResult with a specific message.
    static AssertionResult MakeResultWithMessage(const std::string& msg) {
        LazyExpression lazyExpr{};                             // value is irrelevant to hasMessage()
        AssertionResultData data{ ResultWas::Ok, lazyExpr };   // result type is irrelevant here
        data.message = msg;                                    // this is what hasMessage() inspects
        return AssertionResult{ MakeInfo(), std::move(data) };
    }
};

// --- Tests ---

// Normal case: non-empty message should be reported as present.
TEST_F(AssertionResultTest_295, HasMessage_ReturnsTrue_ForNonEmptyMessage_295) {
    auto ar = MakeResultWithMessage("something went wrong");
    EXPECT_TRUE(ar.hasMessage());
}

// Boundary: empty string should be reported as no message.
TEST_F(AssertionResultTest_295, HasMessage_ReturnsFalse_ForEmptyMessage_295) {
    auto ar = MakeResultWithMessage("");
    EXPECT_FALSE(ar.hasMessage());
}

// Boundary: whitespace-only is still a non-empty string -> treated as "has message".
TEST_F(AssertionResultTest_295, HasMessage_ReturnsTrue_ForWhitespaceOnlyMessage_295) {
    auto ar = MakeResultWithMessage("   ");
    EXPECT_TRUE(ar.hasMessage());
}

// Robustness: other fields (result type / lazy expression) do not affect observable hasMessage() behavior.
TEST_F(AssertionResultTest_295, HasMessage_IgnoresOtherResultFields_295) {
    // Start with empty message -> false
    {
        LazyExpression lazy{};
        AssertionResultData data{ ResultWas::Ok, lazy };
        data.message = "";
        AssertionResult ar{ MakeInfo(), std::move(data) };
        EXPECT_FALSE(ar.hasMessage());
    }

    // Change result type but keep non-empty message -> true
    {
        LazyExpression lazy{};
        AssertionResultData data{ ResultWas::ExpressionFailed, lazy };
        data.message = "msg";
        AssertionResult ar{ MakeInfo(), std::move(data) };
        EXPECT_TRUE(ar.hasMessage());
    }
}

// Const-correctness: hasMessage() is const, so calling it on a const object should work.
TEST_F(AssertionResultTest_295, HasMessage_IsConstCallable_295) {
    const auto ar = MakeResultWithMessage("const check");
    EXPECT_TRUE(ar.hasMessage());
}

} // namespace
