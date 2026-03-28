// catch_main_test_550.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include <cstring>

// --------------------
// Test-side fakes/mocks for external collaborators (allowed by constraints)
// --------------------
namespace Catch {

// Global knobs/recorders used by our test-side fake Session
namespace TestShim550 {
    static int last_argc = -1;
    static const char* const* last_argv = nullptr;
    static int next_return_code = 0;
}

// Minimal type declarations to satisfy the CUT (do not reimplement internal logic)
namespace Detail { struct NonCopyable {}; template <typename T> using unique_ptr = T*; }
struct ConfigData {};
struct Config {};
namespace Clara { struct Parser {}; }

// Fake Session that records args and returns a controlled code.
// This substitutes as an external collaborator, which is permitted.
class Session : private Detail::NonCopyable {
public:
    Session() = default;
    // Only the overload used by the CUT needs to be observable
    int run(int argc, char* argv[]) {
        TestShim550::last_argc = argc;
        TestShim550::last_argv = const_cast<const char* const*>(argv);
        return TestShim550::next_return_code;
    }
    // The rest are dummies to satisfy linkage (never used by the CUT in these tests)
    int run() { return TestShim550::next_return_code; }
    template<typename CharT>
    int run(int argc, CharT const* const argv[]) {
        TestShim550::last_argc = argc;
        TestShim550::last_argv = reinterpret_cast<const char* const*>(argv);
        return TestShim550::next_return_code;
    }
};

// Leak detector type used by the CUT. We expose construction/dtor as observable side effects.
static int g_leak_ctor_count_550 = 0;
static int g_leak_dtor_count_550 = 0;

struct LeakDetector {
    LeakDetector() { ++g_leak_ctor_count_550; }
    ~LeakDetector() { ++g_leak_dtor_count_550; }
};

} // namespace Catch

// --------------------
// Include the CUT while renaming its 'main' to avoid conflict with gtest's main
// --------------------
#define main catch2_main_under_test_550
// The prompt shows a very compacted single-line file; include it directly.
// If your include path differs, adjust accordingly:
#include "Catch2/src/catch2/internal/catch_main.cpp"
#undef main

// --------------------
// Test Fixture
// --------------------
class CatchMainTest_550 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset recorders before each test
        Catch::TestShim550::last_argc = -1;
        Catch::TestShim550::last_argv = nullptr;
        Catch::TestShim550::next_return_code = 0;
    }
};

// --------------------
// Tests (names include TEST_ID = 550 as required)
// --------------------

// Verifies: main forwards return code from Catch::Session::run
TEST_F(CatchMainTest_550, ReturnsRunResult_550) {
    Catch::TestShim550::next_return_code = 123;

    // Prepare argv
    const char* arg0 = "prog";
    const char* arg1 = "--list-tests";
    // Google Test expects char*, not const char*
    char* argv_local[] = { const_cast<char*>(arg0), const_cast<char*>(arg1), nullptr };
    int argc_local = 2;

    int rc = catch2_main_under_test_550(argc_local, argv_local);

    EXPECT_EQ(rc, 123);
}

// Verifies: main forwards argc/argv to Catch::Session::run accurately
TEST_F(CatchMainTest_550, ForwardsArguments_550) {
    Catch::TestShim550::next_return_code = 0;

    const char* arg0 = "prog";
    const char* arg1 = "-r";
    const char* arg2 = "xml";
    char* argv_local[] = {
        const_cast<char*>(arg0),
        const_cast<char*>(arg1),
        const_cast<char*>(arg2),
        nullptr
    };
    int argc_local = 3;

    (void)catch2_main_under_test_550(argc_local, argv_local);

    ASSERT_EQ(Catch::TestShim550::last_argc, 3);
    ASSERT_NE(Catch::TestShim550::last_argv, nullptr);
    EXPECT_STREQ(Catch::TestShim550::last_argv[0], arg0);
    EXPECT_STREQ(Catch::TestShim550::last_argv[1], arg1);
    EXPECT_STREQ(Catch::TestShim550::last_argv[2], arg2);
}

// Boundary: argc=0, argv=nullptr should be passed through and handled by Session::run
TEST_F(CatchMainTest_550, ZeroArgsBoundary_550) {
    Catch::TestShim550::next_return_code = 7;

    int rc = catch2_main_under_test_550(0, nullptr);

    EXPECT_EQ(rc, 7);
    EXPECT_EQ(Catch::TestShim550::last_argc, 0);
    EXPECT_EQ(Catch::TestShim550::last_argv, nullptr);
}

// Observable side effect: LeakDetector should be constructed at program startup
// We cannot force startup here, but including the CUT defines a global LeakDetector
// that constructs before any test code runs. We validate construction happened
// (i.e., ctor count >= 1). We do not depend on exact counts beyond "at least once".
TEST_F(CatchMainTest_550, LeakDetectorConstructed_550) {
    // The global object in the CUT should have run its constructor already.
    // We only assert construction (not destruction) because destruction happens at process exit.
    EXPECT_GE(Catch::g_leak_ctor_count_550, 1) << "LeakDetector should be constructed via global in CUT";
}

// --------------------
// Provide a gtest runner main (link WITHOUT gtest_main)
// --------------------
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
