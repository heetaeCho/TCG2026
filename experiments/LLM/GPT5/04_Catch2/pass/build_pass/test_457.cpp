// File: tests/session_config_tests_457.cpp

#include <gtest/gtest.h>
#include "catch2/catch_session.hpp"

using namespace Catch;

class SessionConfigTest_457 : public ::testing::Test {
protected:
    Session s; // Fresh session per test
};

// Ensures the function’s return type is a reference (compile-time check)
TEST_F(SessionConfigTest_457, ConfigReturnsReferenceType_457) {
    static_assert(std::is_reference<decltype(std::declval<Session&>().config())>::value,
                  "Session::config() must return a reference");
    // Also compile-time: reference to Config (not a pointer or value)
    static_assert(std::is_same<decltype(std::declval<Session&>().config()), Config&>::value,
                  "Session::config() should return Config&");
}

// Verifies repeated calls return the same underlying object (observable by address)
TEST_F(SessionConfigTest_457, ConfigReturnsSameInstanceOnRepeatedCalls_457) {
    Config& first  = s.config();
    Config& second = s.config();
    EXPECT_EQ(&first, &second);
}

// The returned Config instance remains stable even after other public calls.
// (We do not assume internal behavior; we only assert that the same reference
// is still returned after interacting with the Session via its public API.)
TEST_F(SessionConfigTest_457, ConfigInstanceStableAcrossOtherPublicCalls_457) {
    Config& before = s.config();

    // Exercise other public members without assuming any internal effects.
    // We won’t depend on specific behavior or values—just call them to simulate usage.
    // If default-constructible, we can pass an empty ConfigData to useConfigData.
    // This uses only the public API; no internal state is assumed or read.
    ConfigData cd{};
    s.useConfigData(cd);
    (void)s.cli();            // const& access
    s.showHelp();             // const
    s.libIdentify();          // void

    Config& after = s.config();
    EXPECT_EQ(&before, &after);
}
