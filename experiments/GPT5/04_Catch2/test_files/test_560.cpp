// File: handleExceptionMatchExpr_tests_560.cpp
#include <gtest/gtest.h>
#include <string>

//
// Minimal surface needed for testing the forwarding behavior.
// We do NOT reimplement internal logic; we only provide a collaborator
// endpoint (the matcher-overload) to observe calls.
//

namespace Catch {

struct AssertionHandler {
    // Empty shell: we do not depend on internal state/behavior.
};

namespace Matchers {
// Minimal type representing the result of Equals(str)
struct Equals {
    std::string expected;
    explicit Equals(const std::string& s) : expected(s) {}
};
} // namespace Matchers

// ---------- Collaborator overload we want to observe ----------
// This is the overload that the function-under-test should call.
// We record the arguments for verification in tests.
namespace TestProbe_560 {
    inline int call_count = 0;
    inline const AssertionHandler* last_handler_ptr = nullptr;
    inline std::string last_expected;

    inline void reset() {
        call_count = 0;
        last_handler_ptr = nullptr;
        last_expected.clear();
    }
}

inline void handleExceptionMatchExpr( AssertionHandler& handler,
                                      Matchers::Equals const& eq ) {
    using namespace TestProbe_560;
    ++call_count;
    last_handler_ptr = &handler;
    last_expected = eq.expected;
}

// ---------- Function under test (from the provided partial code) ----------
inline void handleExceptionMatchExpr( AssertionHandler& handler,
                                      std::string const& str ) {
    handleExceptionMatchExpr( handler, Matchers::Equals( str ) );
}

} // namespace Catch


// -------------------------- Tests --------------------------

class HandleExceptionMatchExprTest_560 : public ::testing::Test {
protected:
    void SetUp() override { Catch::TestProbe_560::reset(); }
};

TEST_F(HandleExceptionMatchExprTest_560, ForwardsToMatcherOverload_WithSameString_560) {
    Catch::AssertionHandler handler;
    Catch::handleExceptionMatchExpr(handler, std::string("boom"));

    EXPECT_EQ(Catch::TestProbe_560::call_count, 1);
    EXPECT_EQ(Catch::TestProbe_560::last_handler_ptr, &handler);
    EXPECT_EQ(Catch::TestProbe_560::last_expected, "boom");
}

TEST_F(HandleExceptionMatchExprTest_560, ForwardsEmptyStringBoundary_560) {
    Catch::AssertionHandler handler;
    Catch::handleExceptionMatchExpr(handler, std::string{});

    EXPECT_EQ(Catch::TestProbe_560::call_count, 1);
    EXPECT_EQ(Catch::TestProbe_560::last_handler_ptr, &handler);
    EXPECT_TRUE(Catch::TestProbe_560::last_expected.empty());
}

TEST_F(HandleExceptionMatchExprTest_560, ForwardsUnicodeStringBoundary_560) {
    Catch::AssertionHandler handler;
    const std::string unicode = u8"예외: ⚠️";
    Catch::handleExceptionMatchExpr(handler, unicode);

    EXPECT_EQ(Catch::TestProbe_560::call_count, 1);
    EXPECT_EQ(Catch::TestProbe_560::last_handler_ptr, &handler);
    EXPECT_EQ(Catch::TestProbe_560::last_expected, unicode);
}

TEST_F(HandleExceptionMatchExprTest_560, MultipleCallsAccumulateAndKeepLatestArgs_560) {
    Catch::AssertionHandler handlerA;
    Catch::AssertionHandler handlerB;

    Catch::handleExceptionMatchExpr(handlerA, "first");
    Catch::handleExceptionMatchExpr(handlerB, "second");

    EXPECT_EQ(Catch::TestProbe_560::call_count, 2);
    EXPECT_EQ(Catch::TestProbe_560::last_handler_ptr, &handlerB);
    EXPECT_EQ(Catch::TestProbe_560::last_expected, "second");
}
