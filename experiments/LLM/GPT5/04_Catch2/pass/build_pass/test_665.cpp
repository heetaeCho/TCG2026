// File: test_opt_validate_665.cpp
#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Opt;

namespace {

// Utility to assert that a substring exists in a string (portable & clear)
static void ExpectContains(const std::string& haystack, const std::string& needle) {
    ASSERT_NE(haystack.find(needle), std::string::npos)
        << "Expected to find substring: \"" << needle << "\" in: \"" << haystack << "\"";
}

} // namespace

// No option names provided -> logic error
TEST(ClaraOptValidateTest_665, NoNames_ReturnsLogicError_665) {
    bool flag = false;
    Opt opt(flag);

    auto result = opt.validate();

    EXPECT_FALSE(result) << "Validation should fail when no option names were supplied.";
    ExpectContains(result.errorMessage(), "No options supplied to Opt");
}

// Empty option name -> specific logic error
TEST(ClaraOptValidateTest_665, EmptyName_ReturnsLogicError_665) {
    bool flag = false;
    Opt opt(flag);

    opt[""]; // add an empty option name
    auto result = opt.validate();

    EXPECT_FALSE(result) << "Validation should fail when an empty option name is present.";
    ExpectContains(result.errorMessage(), "Option name cannot be empty");
}

// Name without the required prefix -> platform-specific error message
TEST(ClaraOptValidateTest_665, InvalidPrefix_ReturnsLogicError_665) {
    bool flag = false;
    Opt opt(flag);

    opt["x"]; // does not start with '-' (or '/' on Windows)
    auto result = opt.validate();

    EXPECT_FALSE(result) << "Validation should fail for names without the required prefix.";
#ifdef CATCH_PLATFORM_WINDOWS
    ExpectContains(result.errorMessage(), "Option name must begin with '-' or '/'");
#else
    ExpectContains(result.errorMessage(), "Option name must begin with '-'");
#endif
}

// Single valid dash-prefixed name -> ok
TEST(ClaraOptValidateTest_665, DashPrefixedName_PassesValidation_665) {
    bool flag = false;
    Opt opt(flag);

    opt["-x"];
    auto result = opt.validate();

    EXPECT_TRUE(result) << "Dash-prefixed option should validate successfully.";
}

// Slash-prefixed name -> ok on Windows, error elsewhere
TEST(ClaraOptValidateTest_665, SlashPrefixedName_WindowsBehavior_665) {
    bool flag = false;
    Opt opt(flag);

    opt["/x"];
    auto result = opt.validate();

#ifdef CATCH_PLATFORM_WINDOWS
    EXPECT_TRUE(result) << "On Windows, slash-prefixed options are allowed.";
#else
    EXPECT_FALSE(result) << "On non-Windows platforms, slash-prefixed options are not allowed.";
    ExpectContains(result.errorMessage(), "Option name must begin with '-'");
#endif
}

// Multiple valid names -> ok
TEST(ClaraOptValidateTest_665, MultipleValidNames_PassesValidation_665) {
    bool flag = false;
    Opt opt(flag);

#ifdef CATCH_PLATFORM_WINDOWS
    opt["-a"]["/b"]["-long"];
#else
    opt["-a"]["-b"]["-long"];
#endif

    auto result = opt.validate();
    EXPECT_TRUE(result) << "All valid option names should validate successfully.";
}

// Mixed valid and invalid names -> fails (observable through validate() only)
TEST(ClaraOptValidateTest_665, MixedValidAndInvalidNames_FailsValidation_665) {
    bool flag = false;
    Opt opt(flag);

#ifdef CATCH_PLATFORM_WINDOWS
    opt["-good"]["bad"];  // "bad" lacks required '-' or '/'
    auto result = opt.validate();
    EXPECT_FALSE(result);
    ExpectContains(result.errorMessage(), "Option name must begin with '-' or '/'");
#else
    opt["-good"]["bad"];  // "bad" lacks required '-'
    auto result = opt.validate();
    EXPECT_FALSE(result);
    ExpectContains(result.errorMessage(), "Option name must begin with '-'");
#endif
}
