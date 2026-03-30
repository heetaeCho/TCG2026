// File: assertion_handler_handleExpr_tests_551.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ostream>

// ---- Minimal forward declarations matching the provided interfaces ----
namespace Catch {

struct SourceLineInfo {
    const char* file = "";
    std::size_t line = 0;
    SourceLineInfo(const char* f = "", std::size_t l = 0) : file(f), line(l) {}
};

class StringRef {
public:
    const char* data_;
    explicit StringRef(const char* s = "") : data_(s) {}
    const char* c_str() const { return data_; }
};

struct AssertionInfo {
    StringRef macroName;
    SourceLineInfo lineInfo;
    StringRef capturedExpression;
    int resultDisposition{}; // placeholder
};

struct AssertionReaction {  // opaque to tests; we don't depend on its internals
};

namespace ResultDisposition {
    enum Flags {
        Normal = 0
    };
}

class ITransientExpression {
public:
    // The real interface has ctors and helpers; we only need a vfunc to be concrete-constructible
    virtual ~ITransientExpression() = default;
    virtual void streamReconstructedExpression(std::ostream&) const {}
};

class IResultCapture {
public:
    virtual ~IResultCapture() = default;
    virtual void handleExpr(const AssertionInfo& info,
                            const ITransientExpression& expr,
                            AssertionReaction& reaction) = 0;
};

// --- SUT under test ----------------------------------------------------
// Forward-declare the class as per provided header.
class AssertionHandler {
public:
    AssertionHandler(StringRef, const SourceLineInfo&, StringRef, ResultDisposition::Flags);
    void handleExpr(const ITransientExpression& expr);
    void complete();
    bool allowThrows() const;
};

// In many Catch2 builds, AssertionHandler consults a global accessor for IResultCapture.
// Provide a test seam so handler delegates into our mock. If the production object uses
// a member capture instead, these symbols are harmless.
extern IResultCapture* g_resultCapture_test_seam;
IResultCapture*& getResultCaptureTestSeam();
} // namespace Catch

// Define the seam symbols:
namespace Catch {
IResultCapture* g_resultCapture_test_seam = nullptr;
IResultCapture*& getResultCaptureTestSeam() { return g_resultCapture_test_seam; }
} // namespace Catch

// ---- Mock types --------------------------------------------------------
namespace Catch {
class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, handleExpr,
                (const AssertionInfo&,
                 const ITransientExpression&,
                 AssertionReaction&),
                (override));
};
} // namespace Catch

// A simple concrete transient expression for passing through the API
class DummyExpr_551 final : public Catch::ITransientExpression {
public:
    explicit DummyExpr_551(const char* txt = "") : text_(txt) {}
    void streamReconstructedExpression(std::ostream&) const override {}
private:
    const char* text_;
};

// ---- Test fixture ------------------------------------------------------
class AssertionHandlerTest_551 : public ::testing::Test {
protected:
    void SetUp() override {
        // Install our mock into the global seam
        Catch::getResultCaptureTestSeam() = &mock_;
    }
    void TearDown() override {
        Catch::getResultCaptureTestSeam() = nullptr;
    }

    // Helper to create a default-constructed handler using only public ctor
    Catch::AssertionHandler makeHandler() {
        return Catch::AssertionHandler(
            Catch::StringRef("REQUIRE"),
            Catch::SourceLineInfo("test.cpp", 123),
            Catch::StringRef("x == 42"),
            Catch::ResultDisposition::Normal);
    }

    Catch::MockResultCapture mock_;
};

// ---- Tests -------------------------------------------------------------

// Verifies that AssertionHandler::handleExpr forwards the exact expr reference
// to the external IResultCapture collaborator.
TEST_F(AssertionHandlerTest_551, DelegatesToResultCapture_551) {
    using ::testing::_;
    using ::testing::Ref;

    Catch::AssertionHandler handler = makeHandler();
    DummyExpr_551 expr("dummy");

    EXPECT_CALL(mock_, handleExpr(_, Ref(static_cast<const Catch::ITransientExpression&>(expr)), _))
        .Times(1);

    // Act
    handler.handleExpr(expr);
}

// Verifies that multiple calls are forwarded (no internal caching/short-circuiting is assumed).
TEST_F(AssertionHandlerTest_551, MultipleCallsAreForwarded_551) {
    using ::testing::_;
    using ::testing::Ref;

    Catch::AssertionHandler handler = makeHandler();
    DummyExpr_551 expr("again");

    EXPECT_CALL(mock_, handleExpr(_, Ref(static_cast<const Catch::ITransientExpression&>(expr)), _))
        .Times(2);

    handler.handleExpr(expr);
    handler.handleExpr(expr);
}

// Verifies that handleExpr accepts different expression instances and forwards each one.
TEST_F(AssertionHandlerTest_551, ForwardsDifferentExprInstances_551) {
    using ::testing::_;
    using ::testing::Ref;

    Catch::AssertionHandler handler = makeHandler();
    DummyExpr_551 exprA("A");
    DummyExpr_551 exprB("B");

    {
        ::testing::InSequence s;
        EXPECT_CALL(mock_, handleExpr(_, Ref(static_cast<const Catch::ITransientExpression&>(exprA)), _));
        EXPECT_CALL(mock_, handleExpr(_, Ref(static_cast<const Catch::ITransientExpression&>(exprB)), _));
    }

    handler.handleExpr(exprA);
    handler.handleExpr(exprB);
}

// Sanity check: calling handleExpr does not throw under normal conditions.
TEST_F(AssertionHandlerTest_551, NoThrowOnHandleExpr_551) {
    Catch::AssertionHandler handler = makeHandler();
    DummyExpr_551 expr("safe");

    EXPECT_NO_THROW(handler.handleExpr(expr));
}
