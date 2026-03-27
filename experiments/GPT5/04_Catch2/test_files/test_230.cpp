// handle_exception_match_expr_tests_230.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <ostream>

using ::testing::_;
using ::testing::Exactly;

// ------------------ Minimal public-facing interfaces (stubs) ------------------
namespace Catch {

// Minimal ITransientExpression interface that MatchExpr will implement.
struct ITransientExpression {
    virtual ~ITransientExpression() = default;
    virtual void streamReconstructedExpression(std::ostream&) const = 0;
};

// A very small StringRef substitute just to match constructor signatures if needed.
// (Not used directly in these tests but included to stay close to the provided deps.)
struct StringRef {
    const char* data{nullptr};
};

// Lightweight stand-in for the String matcher type required by the function under test.
// We do not assert on its internals; it is only forwarded through.
struct StringMatcher {};

// translateActiveException stub we can control in tests.
static std::string g_translatedMessage;
inline std::string translateActiveException() {
    return g_translatedMessage;
}

// Minimal MatchExpr<T,MatcherT> that models ITransientExpression.
// We do not expose internals to tests; it's only important that it *is* an ITE.
template <typename ArgT, typename MatcherT>
class MatchExpr : public ITransientExpression {
public:
    MatchExpr(ArgT&&, MatcherT const&) {}
    void streamReconstructedExpression(std::ostream&) const override {}
};

// Minimal AssertionHandler exposing a virtual handleExpr that we can mock.
class AssertionHandler {
public:
    virtual ~AssertionHandler() = default;
    virtual void handleExpr(ITransientExpression const& expr) { (void)expr; }
};

// --------------- Function under test (from provided snippet) ------------------
inline void handleExceptionMatchExpr(AssertionHandler& handler,
                                     StringMatcher const& matcher) {
    std::string exceptionMessage = Catch::translateActiveException();
    MatchExpr<std::string, StringMatcher const&> expr(std::move(exceptionMessage), matcher);
    handler.handleExpr(expr);
}

} // namespace Catch

// ------------------------------- Test Doubles ---------------------------------
namespace {
class MockAssertionHandler : public Catch::AssertionHandler {
public:
    MOCK_METHOD(void, handleExpr, (Catch::ITransientExpression const& expr), (override));
};
} // namespace

// ---------------------------------- Tests -------------------------------------

// Verifies that when an exception message is available, the handler receives exactly one
// call to handleExpr with some ITransientExpression.
TEST(HandleExceptionMatchExprTest_230, CallsHandleExprOnceWhenExceptionActive_230) {
    // Arrange
    MockAssertionHandler handler;
    Catch::StringMatcher matcher;
    Catch::g_translatedMessage = "boom! something happened";

    EXPECT_CALL(handler, handleExpr(_)).Times(Exactly(1));

    // Act & Assert (no throw expected)
    ASSERT_NO_THROW(Catch::handleExceptionMatchExpr(handler, matcher));
}

// Verifies boundary behavior when the translated message is empty
// (e.g., unusual/edge translation result). Still must call handleExpr once.
TEST(HandleExceptionMatchExprTest_230, CallsHandleExprOnceWithEmptyTranslatedMessage_230) {
    // Arrange
    MockAssertionHandler handler;
    Catch::StringMatcher matcher;
    Catch::g_translatedMessage.clear(); // empty boundary case

    EXPECT_CALL(handler, handleExpr(_)).Times(Exactly(1));

    // Act & Assert
    ASSERT_NO_THROW(Catch::handleExceptionMatchExpr(handler, matcher));
}
