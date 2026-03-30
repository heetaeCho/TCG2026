// tests/assertion_handler_handleexpr_template_132_tests.cpp
#include <gtest/gtest.h>
#include <cstddef>
#include <string>

//
// Minimal public-facing stand-ins to exercise the interface, not internals.
//
namespace Catch {

// Forward-declared/externally-defined in real code; minimal shell for tests.
struct ITransientExpression {
    virtual ~ITransientExpression() = default;
};

struct StringRef {
    const char* s;
    constexpr StringRef(const char* v = "") : s(v) {}
};

struct SourceLineInfo {
    const char* file;
    std::size_t line;
    constexpr SourceLineInfo(const char* f = "", std::size_t l = 0) : file(f), line(l) {}
};

namespace ResultDisposition {
    enum Flags : int { Normal = 0 };
}

// A tiny unary expr we can recognize/track in tests.
struct DummyUnaryExpr : ITransientExpression {};

// Minimal ExprLhs<T> that exposes makeUnaryExpr(), as required by the template.
template <typename T>
struct ExprLhs {
    const ITransientExpression* ue;
    explicit ExprLhs(const ITransientExpression& u) : ue(&u) {}
    const ITransientExpression& makeUnaryExpr() const { return *ue; }
};

// Class under test — only the template overload’s body is relevant.
// The non-template handleExpr is declared here and defined below as a stub/spy.
class AssertionHandler {
public:
    AssertionHandler(StringRef, SourceLineInfo const&, StringRef, ResultDisposition::Flags) {}

    void handleExpr(ITransientExpression const& expr); // stubbed definition below

    // -------- Target of testing (copied exactly from the given partial code) --------
    template <typename T>
    constexpr void handleExpr(ExprLhs<T> const& expr) {
        handleExpr(expr.makeUnaryExpr());
    }
    // --------------------------------------------------------------------------------
};

} // namespace Catch

//
// Spy state for observing calls to the non-template overload.
//
static int g_handleExpr_calls_132 = 0;
static const Catch::ITransientExpression* g_lastExpr_ptr_132 = nullptr;

namespace Catch {

// Test stub to observe interaction from the template overload.
// This does not simulate internal class logic; it only records that the overload
// was invoked and with which ITransientExpression object.
void AssertionHandler::handleExpr(ITransientExpression const& expr) {
    ++g_handleExpr_calls_132;
    g_lastExpr_ptr_132 = &expr;
}

} // namespace Catch

//
// Test fixture to reset spy state between tests.
//
class AssertionHandlerHandleExprTemplateTest_132 : public ::testing::Test {
protected:
    void SetUp() override {
        g_handleExpr_calls_132 = 0;
        g_lastExpr_ptr_132 = nullptr;
    }
};

//
// Tests
//

// Verifies: Calling the template overload forwards exactly once to the
// non-template overload with the precise object returned by makeUnaryExpr().
TEST_F(AssertionHandlerHandleExprTemplateTest_132,
       ForwardsToNonTemplateWithExactUnaryExpr_132) {
    using namespace Catch;

    DummyUnaryExpr unary;                       // object we expect to be forwarded
    ExprLhs<int> lhs(unary);                    // T is arbitrary here
    AssertionHandler h(StringRef("MACRO"),
                       SourceLineInfo("file.cpp", 42),
                       StringRef("x == 1"),
                       ResultDisposition::Normal);

    h.handleExpr(lhs);

    EXPECT_EQ(g_handleExpr_calls_132, 1);
    EXPECT_EQ(g_lastExpr_ptr_132, &unary) << "Template must forward the exact unary expr instance";
}

// Verifies: T can vary freely — the template overload should still forward correctly.
TEST_F(AssertionHandlerHandleExprTemplateTest_132,
       WorksForDifferentTemplateArgumentTypes_132) {
    using namespace Catch;

    DummyUnaryExpr unaryA;
    ExprLhs<std::string> lhsA(unaryA);

    AssertionHandler h(StringRef("MACRO"),
                       SourceLineInfo("other.cpp", 7),
                       StringRef("y > 0"),
                       ResultDisposition::Normal);

    h.handleExpr(lhsA);

    EXPECT_EQ(g_handleExpr_calls_132, 1);
    EXPECT_EQ(g_lastExpr_ptr_132, &unaryA);
}

// Verifies: Repeated calls keep forwarding; last forwarded object is latest unary expr.
TEST_F(AssertionHandlerHandleExprTemplateTest_132,
       MultipleCallsForwardEachTimeAndUpdateLastExpr_132) {
    using namespace Catch;

    DummyUnaryExpr unary1;
    DummyUnaryExpr unary2;
    ExprLhs<double> lhs1(unary1);
    ExprLhs<long>   lhs2(unary2);

    AssertionHandler h(StringRef("MACRO"),
                       SourceLineInfo("multi.cpp", 99),
                       StringRef("z != 0"),
                       ResultDisposition::Normal);

    h.handleExpr(lhs1);
    h.handleExpr(lhs2);

    EXPECT_EQ(g_handleExpr_calls_132, 2);
    EXPECT_EQ(g_lastExpr_ptr_132, &unary2) << "Last call should forward the second unary expr";
}
