// File: tests/assertion_result_get_test_macro_name_302_test.cpp

#include <gtest/gtest.h>

#include <string>
#include <utility>

// Headers from the provided codebase
#include <catch2/catch_assertion_result.hpp>
#include <catch2/catch_assertion_info.hpp>

namespace {

using Catch::AssertionInfo;
using Catch::AssertionResult;
using Catch::AssertionResultData;
using Catch::StringRef;

// Small helper that constructs an AssertionResult with the given macro name.
// We do not touch private state; we pass data via the public constructor.
static AssertionResult MakeResultWithMacro(const char* macro_name) {
    AssertionInfo info{};
    info.macroName = StringRef(macro_name);

    AssertionResultData data{}; // Treat as opaque; default-construct and move.
    return AssertionResult(info, std::move(data));
}

// Utility to compare returned StringRef with std::string safely
static std::string ToStdString(StringRef sr) {
    return std::string(sr.c_str(), sr.size());
}

} // namespace

// -------------------- Tests --------------------

// Normal operation: returns exactly the macro name provided during construction.
TEST(AssertionResultTest_302, ReturnsProvidedMacroName_302) {
    auto ar = MakeResultWithMacro("REQUIRE");
    EXPECT_EQ(ToStdString(ar.getTestMacroName()), "REQUIRE");
}

// Boundary: empty macro name should be reflected as empty in the result.
TEST(AssertionResultTest_302, ReturnsEmptyWhenMacroNameEmpty_302) {
    auto ar = MakeResultWithMacro("");
    auto name = ar.getTestMacroName();
    EXPECT_TRUE(name.empty());
    EXPECT_EQ(ToStdString(name), "");
    EXPECT_EQ(name.size(), 0u);
}

// Boundary: handles long/special-character macro names without truncation.
TEST(AssertionResultTest_302, HandlesLongAndSpecialCharNames_302) {
    const char* long_name =
        "VERY_LONG_MACRO_NAME_WITH_SPECIALS_!@#$%^&*()-_=+[]{};:',.<>/?`~0123456789";
    auto ar = MakeResultWithMacro(long_name);
    EXPECT_EQ(ToStdString(ar.getTestMacroName()), std::string(long_name));
}

// Observable behavior: changing the original AssertionInfo (external variable)
// after construction does not affect the stored/returned macro name.
TEST(AssertionResultTest_302, UnaffectedByExternalInfoChanges_302) {
    // Build first result from one macro name
    auto ar = MakeResultWithMacro("CHECK");

    // Mutate a *separate* info object; this should not affect `ar`
    AssertionInfo other{};
    other.macroName = StringRef("REQUIRE"); // unrelated to `ar`

    EXPECT_EQ(ToStdString(ar.getTestMacroName()), "CHECK");
    // Sanity check on the separate info variable
    EXPECT_EQ(std::string(other.macroName.c_str(), other.macroName.size()), "REQUIRE");
}

// Const-correctness: method is callable on const instances and returns same result.
TEST(AssertionResultTest_302, ConstCorrectness_302) {
    const auto ar = MakeResultWithMacro("SECTION");
    const auto name = ar.getTestMacroName();
    EXPECT_EQ(ToStdString(name), "SECTION");
}
