// tests/assertion_handler_handleExceptionThrownAsExpected_556.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/internal/catch_assertion_handler.hpp"
#include "Catch2/src/catch2/internal/catch_result_type.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"

using ::testing::_;
using ::testing::Exactly;

// ---- Link seam for Catch2's result capture ---------------------------------
// Many Catch2 components acquire IResultCapture via a free function.
// We provide a definition here so AssertionHandler resolves to our mock.
namespace Catch {
    // Forward declared below; set in tests.
    static IResultCapture* g_resultCapture_for_tests = nullptr;

    // If AssertionHandler's ctor grabs a reference via this function,
    // it will bind to our mock.
    IResultCapture& getResultCapture() {
        return *g_resultCapture_for_tests;
    }
} // namespace Catch

// ---- Minimal nice mock for IResultCapture's observable interaction ----------
class MockResultCapture : public Catch::IResultCapture {
public:
    // We only care about this one observable call for these tests.
    MOCK_METHOD(void, handleNonExpr,
        (const Catch::AssertionInfo&,
         Catch::ResultWas::OfType,
         Catch::AssertionReaction&),
        (override));

    // Provide do-nothing overrides for other virtuals to keep linker happy.
    // (Signatures mirror the interface; bodies are empty.)
    void notifyAssertionStarted(const Catch::AssertionInfo&) override {}
    bool sectionStarted(Catch::StringRef, const Catch::SourceLineInfo&, Catch::Counts&) override { return true; }
    void sectionEnded(Catch::SectionEndInfo&&) override {}
    void sectionEndedEarly(Catch::SectionEndInfo&&) override {}
    Catch::IGeneratorTracker* acquireGeneratorTracker(Catch::StringRef, const Catch::SourceLineInfo&) override { return nullptr; }
    Catch::IGeneratorTracker* createGeneratorTracker(Catch::StringRef, Catch::SourceLineInfo, Catch::Generators::GeneratorBasePtr&&) override { return nullptr; }
    void benchmarkPreparing(Catch::StringRef) override {}
    void benchmarkStarting(const Catch::BenchmarkInfo&) override {}
    void benchmarkEnded(const Catch::BenchmarkStats<>&) override {}
    void benchmarkFailed(Catch::StringRef) override {}
    void pushScopedMessage(const Catch::MessageInfo&) override {}
    void popScopedMessage(const Catch::MessageInfo&) override {}
    void emplaceUnscopedMessage(Catch::MessageBuilder&&) override {}
    void handleFatalErrorCondition(Catch::StringRef) override {}
    void handleExpr(const Catch::AssertionInfo&, const Catch::ITransientExpression&, Catch::AssertionReaction&) override {}
    void handleMessage(const Catch::AssertionInfo&, Catch::ResultWas::OfType, std::string&&, Catch::AssertionReaction&) override {}
    void handleUnexpectedExceptionNotThrown(const Catch::AssertionInfo&, Catch::AssertionReaction&) override {}
    void handleUnexpectedInflightException(const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&) override {}
    void handleIncomplete(const Catch::AssertionInfo&) override {}
    bool lastAssertionPassed() override { return false; }
    void assertionPassed() override {}
    const std::string getCurrentTestName() override { return {}; }
    const Catch::AssertionResult* getLastResult() override { return nullptr; }
    void exceptionEarlyReported() override {}
};

// A simple fixture to manage the global seam.
class AssertionHandler_HandleExceptionThrownAsExpected_556 : public ::testing::Test {
protected:
    void SetUp() override {
        Catch::g_resultCapture_for_tests = &mock_;
    }
    void TearDown() override {
        Catch::g_resultCapture_for_tests = nullptr;
    }
    MockResultCapture mock_;
};

// -- Test 1: verifies collaborator interaction with ResultWas::Ok -------------
TEST_F(AssertionHandler_HandleExceptionThrownAsExpected_556,
       CallsHandleNonExprWithOk_556) {
    using namespace Catch;

    // Arrange: minimal inputs to construct AssertionHandler.
    StringRef macroName("REQUIRE_THROWS");
    SourceLineInfo lineInfo{ __FILE__, static_cast<std::size_t>(__LINE__) };
    StringRef capturedExpr("someThrowingCall()");
    ResultDisposition::Flags disposition = ResultDisposition::Normal;

    // Expect: IResultCapture::handleNonExpr is called exactly once,
    // with result type Ok; other parameters are treated as black-box.
    EXPECT_CALL(mock_, handleNonExpr(_, ResultWas::Ok, _)).Times(Exactly(1));

    // Act
    AssertionHandler handler(macroName, lineInfo, capturedExpr, disposition);
    ASSERT_NO_THROW(handler.handleExceptionThrownAsExpected()); // observable: no exception thrown
}

// -- Test 2: safety — calling the method itself must not throw ----------------
TEST_F(AssertionHandler_HandleExceptionThrownAsExpected_556,
       DoesNotThrow_556) {
    using namespace Catch;

    StringRef macroName("REQUIRE_THROWS");
    SourceLineInfo lineInfo{ __FILE__, static_cast<std::size_t>(__LINE__) };
    StringRef capturedExpr("x()");
    ResultDisposition::Flags disposition = ResultDisposition::Normal;

    // We still expect the notification to the collaborator.
    EXPECT_CALL(mock_, handleNonExpr(_, ResultWas::Ok, _)).Times(Exactly(1));

    AssertionHandler handler(macroName, lineInfo, capturedExpr, disposition);
    EXPECT_NO_THROW(handler.handleExceptionThrownAsExpected());
}
