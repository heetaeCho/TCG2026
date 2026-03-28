// tests/getenv_getEnv_tests_524.cpp
#include <gtest/gtest.h>
#include <cstdlib>
#include <string>

// Only declare the interface we're testing (no reimplementation).
namespace Catch { namespace Detail {
    char const* getEnv(char const* varName);
}}

// Cross-platform helpers to set/unset environment variables for the tests.
// They affect the process environment (observable by std::getenv).
static void SetEnvVar(const char* name, const char* value) {
#if defined(_MSC_VER)
    // On MSVC, _putenv_s(name, "") removes the variable.
    // Non-empty sets/overwrites it.
    _putenv_s(name, value);
#else
    // POSIX: setenv overwrites when the 3rd arg is 1.
    ::setenv(name, value, 1);
#endif
}

static void UnsetEnvVar(const char* name) {
#if defined(_MSC_VER)
    // Empty value removes the variable on MSVC CRT.
    _putenv_s(name, "");
#else
    ::unsetenv(name);
#endif
}

class GetEnvTest_524 : public ::testing::Test {
protected:
    const std::string kVar = "CATCH2_TEST_ENV_524";
    void SetUp() override { UnsetEnvVar(kVar.c_str()); }
    void TearDown() override { UnsetEnvVar(kVar.c_str()); }
};

// --- Tests ---

// Verifies: when the variable does not exist, getEnv returns nullptr.
TEST_F(GetEnvTest_524, ReturnsNullptrWhenVarMissing_524) {
    const char* v = Catch::Detail::getEnv(kVar.c_str());
    EXPECT_EQ(v, nullptr);
}

// Verifies: when the variable exists with a non-empty value, getEnv returns a non-null C string equal to that value.
TEST_F(GetEnvTest_524, ReturnsValueWhenVarSet_524) {
    SetEnvVar(kVar.c_str(), "hello-world");
    const char* v = Catch::Detail::getEnv(kVar.c_str());
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, "hello-world");
}

// Verifies: subsequent changes to the environment variable are observable via getEnv.
TEST_F(GetEnvTest_524, ReflectsUpdatedValue_524) {
    SetEnvVar(kVar.c_str(), "first");
    const char* v1 = Catch::Detail::getEnv(kVar.c_str());
    ASSERT_NE(v1, nullptr);
    EXPECT_STREQ(v1, "first");

    SetEnvVar(kVar.c_str(), "second");
    const char* v2 = Catch::Detail::getEnv(kVar.c_str());
    ASSERT_NE(v2, nullptr);
    EXPECT_STREQ(v2, "second");
}

// Verifies boundary behavior for empty values.
// POSIX: empty string value is returned (non-null, equals "").
// MSVC CRT: setting empty removes the variable, so getEnv returns nullptr.
TEST_F(GetEnvTest_524, EmptyValueBehavior_524) {
    SetEnvVar(kVar.c_str(), "");
    const char* v = Catch::Detail::getEnv(kVar.c_str());
#if defined(_MSC_VER)
    // On Windows/MSVC, empty value means "unset".
    EXPECT_EQ(v, nullptr);
#else
    ASSERT_NE(v, nullptr);
    EXPECT_STREQ(v, "");
#endif
}

// Verifies: after unsetting the variable explicitly, getEnv returns nullptr.
TEST_F(GetEnvTest_524, ReturnsNullptrAfterUnset_524) {
    SetEnvVar(kVar.c_str(), "something");
    ASSERT_NE(Catch::Detail::getEnv(kVar.c_str()), nullptr);

    UnsetEnvVar(kVar.c_str());
    EXPECT_EQ(Catch::Detail::getEnv(kVar.c_str()), nullptr);
}
