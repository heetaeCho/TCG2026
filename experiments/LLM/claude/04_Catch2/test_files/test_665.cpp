#include <gtest/gtest.h>
#include <string>
#include <vector>

// Include the necessary Catch2 Clara headers
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara;
using Detail::Result;

// Helper to create an Opt with a bound variable
class OptValidateTest_665 : public ::testing::Test {
protected:
    bool boolRef = false;
    std::string stringRef;
    int intRef = 0;
};

// Test: Opt with no option names should return a logic error
TEST_F(OptValidateTest_665, NoOptionNames_ReturnsLogicError_665) {
    // Create an Opt bound to a bool ref, but don't add any option names
    Opt opt(boolRef);
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "No options supplied to Opt");
}

// Test: Opt with a valid single-dash option name should validate successfully
TEST_F(OptValidateTest_665, SingleDashOptionName_ValidatesOk_665) {
    Opt opt(boolRef);
    opt["-f"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Opt with a valid double-dash option name should validate successfully
TEST_F(OptValidateTest_665, DoubleDashOptionName_ValidatesOk_665) {
    Opt opt(boolRef);
    opt["--flag"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Opt with both short and long option names should validate successfully
TEST_F(OptValidateTest_665, ShortAndLongOptionNames_ValidatesOk_665) {
    Opt opt(boolRef);
    opt["-f"]["--flag"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Opt with an empty option name should return a logic error
TEST_F(OptValidateTest_665, EmptyOptionName_ReturnsLogicError_665) {
    Opt opt(boolRef);
    opt[""];
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "Option name cannot be empty");
}

// Test: Opt with an option name not starting with '-' should return a logic error
TEST_F(OptValidateTest_665, OptionNameWithoutDashPrefix_ReturnsLogicError_665) {
    Opt opt(boolRef);
    opt["flag"];
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
#ifdef CATCH_PLATFORM_WINDOWS
    EXPECT_EQ(result.errorMessage(), "Option name must begin with '-' or '/'");
#else
    EXPECT_EQ(result.errorMessage(), "Option name must begin with '-'");
#endif
}

// Test: Opt with one valid and one invalid option name should return error
TEST_F(OptValidateTest_665, MixedValidAndInvalidNames_ReturnsLogicError_665) {
    Opt opt(boolRef);
    opt["-f"]["noprefix"];
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test: Opt with one valid and one empty option name should return error
TEST_F(OptValidateTest_665, ValidAndEmptyNames_ReturnsLogicError_665) {
    Opt opt(boolRef);
    opt["-f"][""];
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "Option name cannot be empty");
}

// Test: Opt with a single dash character as option name
TEST_F(OptValidateTest_665, SingleDashOnly_ValidatesOk_665) {
    Opt opt(boolRef);
    opt["-"];
    auto result = opt.validate();
    // A single dash starts with '-', so the name validation passes.
    // Whether ParserRefImpl::validate() accepts it depends on base implementation
    // We just verify it doesn't fail on the name prefix check
    // (it may still fail in base validate, which is acceptable)
    // At minimum, it should NOT fail with "Option name must begin with '-'"
    if (!static_cast<bool>(result)) {
        EXPECT_NE(result.errorMessage(), "Option name must begin with '-'");
    }
}

#ifdef CATCH_PLATFORM_WINDOWS
// Test: On Windows, option name starting with '/' should be valid
TEST_F(OptValidateTest_665, WindowsSlashPrefix_ValidatesOk_665) {
    Opt opt(boolRef);
    opt["/f"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}
#endif

// Test: Opt with a value reference and valid option name
TEST_F(OptValidateTest_665, ValueRefWithValidOption_ValidatesOk_665) {
    Opt opt(intRef, "value");
    opt["-n"]["--number"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Opt with a value reference but no option names
TEST_F(OptValidateTest_665, ValueRefNoOptionNames_ReturnsLogicError_665) {
    Opt opt(intRef, "value");
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "No options supplied to Opt");
}

// Test: Opt with string reference and valid option
TEST_F(OptValidateTest_665, StringRefWithValidOption_ValidatesOk_665) {
    Opt opt(stringRef, "text");
    opt["-s"]["--string"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Multiple valid option names all starting with dash
TEST_F(OptValidateTest_665, MultipleValidOptionNames_ValidatesOk_665) {
    Opt opt(boolRef);
    opt["-a"]["-b"]["-c"]["--all"]["--both"]["--combined"];
    auto result = opt.validate();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test: Option name starting with a number (no dash) should fail
TEST_F(OptValidateTest_665, OptionNameStartingWithNumber_ReturnsLogicError_665) {
    Opt opt(boolRef);
    opt["123"];
    auto result = opt.validate();
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test: Option name with special characters but starting with dash should pass name check
TEST_F(OptValidateTest_665, OptionNameWithSpecialCharsAndDash_PassesNameCheck_665) {
    Opt opt(boolRef);
    opt["-@!#"];
    auto result = opt.validate();
    // The name starts with '-', so name prefix check passes
    // Base validate may or may not accept it
    if (!static_cast<bool>(result)) {
        EXPECT_NE(result.errorMessage(), "Option name must begin with '-'");
        EXPECT_NE(result.errorMessage(), "No options supplied to Opt");
        EXPECT_NE(result.errorMessage(), "Option name cannot be empty");
    }
}
