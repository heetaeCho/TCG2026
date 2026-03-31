#include <gtest/gtest.h>
#include <cstdlib>

// Declaration of the function under test
namespace Catch {
namespace Detail {
    char const* getEnv(char const* varName);
}
}

class CatchGetEnvTest_524 : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up any test environment variables before each test
    }

    void TearDown() override {
        // Unset any environment variables we may have set
#ifdef _WIN32
        _putenv_s("CATCH2_TEST_VAR_524", "");
        _putenv_s("CATCH2_TEST_EMPTY_VAR_524", "");
#else
        unsetenv("CATCH2_TEST_VAR_524");
        unsetenv("CATCH2_TEST_EMPTY_VAR_524");
#endif
    }

    void setEnvVar(const char* name, const char* value) {
#ifdef _WIN32
        _putenv_s(name, value);
#else
        setenv(name, value, 1);
#endif
    }

    void unsetEnvVar(const char* name) {
#ifdef _WIN32
        _putenv_s(name, "");
#else
        unsetenv(name);
#endif
    }
};

// Test that a non-existent environment variable returns nullptr
TEST_F(CatchGetEnvTest_524, NonExistentVariableReturnsNull_524) {
    const char* result = Catch::Detail::getEnv("CATCH2_THIS_VAR_SHOULD_NOT_EXIST_524_XYZ");
    EXPECT_EQ(result, nullptr);
}

// Test that an existing environment variable returns its value
TEST_F(CatchGetEnvTest_524, ExistingVariableReturnsValue_524) {
    setEnvVar("CATCH2_TEST_VAR_524", "hello_world");
    const char* result = Catch::Detail::getEnv("CATCH2_TEST_VAR_524");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "hello_world");
}

// Test that an empty environment variable returns an empty string (not nullptr)
TEST_F(CatchGetEnvTest_524, EmptyVariableReturnsEmptyString_524) {
    setEnvVar("CATCH2_TEST_EMPTY_VAR_524", "");
    const char* result = Catch::Detail::getEnv("CATCH2_TEST_EMPTY_VAR_524");
    // On most platforms, an empty env var returns "" not nullptr
    // However, behavior can vary on Windows with _putenv_s("name", "")
    // which may unset the variable. We test for the common case.
#ifndef _WIN32
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
#else
    // On Windows, _putenv_s with "" may unset the variable
    // So we accept either nullptr or empty string
    if (result != nullptr) {
        EXPECT_STREQ(result, "");
    }
#endif
}

// Test that a well-known environment variable (PATH) exists and is not null
TEST_F(CatchGetEnvTest_524, WellKnownVariablePATH_524) {
    const char* result = Catch::Detail::getEnv("PATH");
    // PATH should be set on virtually all systems
    EXPECT_NE(result, nullptr);
}

// Test that setting a variable and then unsetting it returns nullptr
TEST_F(CatchGetEnvTest_524, UnsetVariableReturnsNull_524) {
    setEnvVar("CATCH2_TEST_VAR_524", "some_value");
    const char* result1 = Catch::Detail::getEnv("CATCH2_TEST_VAR_524");
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "some_value");

    unsetEnvVar("CATCH2_TEST_VAR_524");
    const char* result2 = Catch::Detail::getEnv("CATCH2_TEST_VAR_524");
    EXPECT_EQ(result2, nullptr);
}

// Test with an empty variable name string
TEST_F(CatchGetEnvTest_524, EmptyVariableNameReturnsNull_524) {
    const char* result = Catch::Detail::getEnv("");
    // An empty string as a variable name should not match any env var
    EXPECT_EQ(result, nullptr);
}

// Test that the function returns correct value for a variable with special characters in value
TEST_F(CatchGetEnvTest_524, VariableWithSpecialCharactersInValue_524) {
    setEnvVar("CATCH2_TEST_VAR_524", "value with spaces & special=chars!@#$%");
    const char* result = Catch::Detail::getEnv("CATCH2_TEST_VAR_524");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "value with spaces & special=chars!@#$%");
}

// Test that updating an environment variable reflects the new value
TEST_F(CatchGetEnvTest_524, UpdatedVariableReflectsNewValue_524) {
    setEnvVar("CATCH2_TEST_VAR_524", "first_value");
    const char* result1 = Catch::Detail::getEnv("CATCH2_TEST_VAR_524");
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "first_value");

    setEnvVar("CATCH2_TEST_VAR_524", "second_value");
    const char* result2 = Catch::Detail::getEnv("CATCH2_TEST_VAR_524");
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "second_value");
}

// Test case sensitivity of environment variable names (platform dependent)
TEST_F(CatchGetEnvTest_524, CaseSensitivity_524) {
    setEnvVar("CATCH2_TEST_VAR_524", "case_test");

#ifdef _WIN32
    // Windows environment variables are case-insensitive
    const char* result = Catch::Detail::getEnv("catch2_test_var_524");
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "case_test");
#else
    // Unix-like systems are case-sensitive
    const char* result = Catch::Detail::getEnv("catch2_test_var_524");
    EXPECT_EQ(result, nullptr);
#endif
}
