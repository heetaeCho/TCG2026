// File: session_run_template_tests_424.cpp

#include <gtest/gtest.h>
#include "catch2/catch_session.hpp"  // path matches the Partial Code

using Catch::Session;

// A small helper to build argv arrays with stable storage.
namespace {
struct ArgvHolder {
    std::vector<std::string> storage;
    std::vector<const char*> argv;

    ArgvHolder(std::initializer_list<const char*> init) {
        storage.reserve(init.size());
        argv.reserve(init.size());
        for (auto* s : init) {
            storage.emplace_back(s);
        }
        for (auto& s : storage) {
            argv.push_back(s.c_str());
        }
    }
};

struct WArgvHolder {
    std::vector<std::wstring> storage;
    std::vector<const wchar_t*> argv;

    WArgvHolder(std::initializer_list<const wchar_t*> init) {
        storage.reserve(init.size());
        argv.reserve(init.size());
        for (auto* s : init) {
            storage.emplace_back(s);
        }
        for (auto& s : storage) {
            argv.push_back(s.c_str());
        }
    }
};
} // namespace

class CatchSessionTest_424 : public ::testing::Test {
protected:
    Session session_;
};

// [Normal operation] If command line parses successfully (e.g., just program name),
// the template overload should forward to the zero-arg run() and return the same code.
TEST_F(CatchSessionTest_424, CharArgv_SuccessParses_PropagatesZeroArgRun_424) {
    ArgvHolder args{ "prog" };
    const int expected = session_.run(); // observable baseline
    const int rc = session_.run(static_cast<int>(args.argv.size()), args.argv.data());
    EXPECT_EQ(rc, expected);
}

// [Boundary] The template should also accept wide-character argv and behave the same
// on a simple, successfully-parsed command line.
TEST_F(CatchSessionTest_424, WCharArgv_SuccessParses_PropagatesZeroArgRun_424) {
    WArgvHolder args{ L"prog" };
    const int expected = session_.run(); // observable baseline
    const int rc = session_.run(static_cast<int>(args.argv.size()), args.argv.data());
    EXPECT_EQ(rc, expected);
}

// [Error/exceptional path, observable] If command line parsing fails (unknown flag),
// the template should return a non-zero code from applyCommandLine and NOT need to
// rely on internal state. We only assert non-zero (observable), not any specific value.
TEST_F(CatchSessionTest_424, CharArgv_InvalidOption_ReturnsNonZero_424) {
    ArgvHolder args{ "prog", "--this-option-should-not-exist-424" };
    const int rc = session_.run(static_cast<int>(args.argv.size()), args.argv.data());
    EXPECT_NE(rc, 0);
}

// [Error/exceptional path, observable] Same behavior for wide-character argv.
TEST_F(CatchSessionTest_424, WCharArgv_InvalidOption_ReturnsNonZero_424) {
    WArgvHolder args{ L"prog", L"--this-option-should-not-exist-424" };
    const int rc = session_.run(static_cast<int>(args.argv.size()), args.argv.data());
    EXPECT_NE(rc, 0);
}

// [Robustness] Passing only a program name should be safe and not trigger fatal failures.
// We assert that calling the template overload does not cause fatal conditions.
TEST_F(CatchSessionTest_424, CharArgv_NoFatalFailure_OnMinimalArgs_424) {
    ArgvHolder args{ "prog" };
    EXPECT_NO_FATAL_FAILURE({
        (void)session_.run(static_cast<int>(args.argv.size()), args.argv.data());
    });
}

// [Robustness] Wide-character minimal argv path also should not trigger fatal failures.
TEST_F(CatchSessionTest_424, WCharArgv_NoFatalFailure_OnMinimalArgs_424) {
    WArgvHolder args{ L"prog" };
    EXPECT_NO_FATAL_FAILURE({
        (void)session_.run(static_cast<int>(args.argv.size()), args.argv.data());
    });
}
