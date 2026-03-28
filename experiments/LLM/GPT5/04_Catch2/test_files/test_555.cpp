// File: tests/assertion_handler_unexpected_inflight_exception_555.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::StrictMock;

namespace Catch {

// ---- Mock for IResultCapture (only methods we observe are mocked) ----
class MockResultCapture : public IResultCapture {
public:
    // We only need to observe this one method
    MOCK_METHOD(void, handleUnexpectedInflightException,
                (const AssertionInfo& info, std::string&& message, AssertionReaction& reaction), (override));

    // Provide benign defaults for pure virtuals we do not use in these tests.
    // Using GMock's GTEST_DISALLOW_COPY_AND_ASSIGN_ style stubs would be noisy; we provide minimal overrides.
    void notifyAssertionStarted(const AssertionInfo&) override {}
    bool sectionStarted(StringRef, const SourceLineInfo&, Counts&) override { return true; }
    void sectionEnded(SectionEndInfo&&) override {}
    void sectionEndedEarly(SectionEndInfo&&) override {}
    IGeneratorTracker* acquireGeneratorTracker(StringRef, const SourceLineInfo&) override { return nullptr; }
    IGeneratorTracker* createGeneratorTracker(StringRef, SourceLineInfo, Generators::GeneratorBasePtr&&) override { return nullptr; }
    void benchmarkPreparing(StringRef) override {}
    void benchmarkStarting(const BenchmarkInfo&) override {}
    void benchmarkEnded(const BenchmarkStats<>&) override {}
    void benchmarkFailed(StringRef) override {}
    void pushScopedMessage(const MessageInfo&) override {}
    void popScopedMessage(const MessageInfo&) override {}
    void emplaceUnscopedMessage(MessageBuilder&&) override {}
    void handleFatalErrorCondition(StringRef) override {}
    void handleExpr(const AssertionInfo&, const ITransientExpression&, AssertionReaction&) override {}
    void handleMessage(const AssertionInfo&, ResultWas::OfType, std::string&&, AssertionReaction&) override {}
    void handleUnexpectedExceptionNotThrown(const AssertionInfo&, AssertionReaction&) override {}
    void handleIncomplete(const AssertionInfo&) override {}
    void handleNonExpr(const AssertionInfo&, ResultWas::OfType, AssertionReaction&) override {}
    bool lastAssertionPassed() override { return true; }
    void assertionPassed() override {}
    const std::string getCurrentTestName() override { static std::string n = "gtest"; return n; }
    const AssertionResult* getLastResult() override { return nullptr; }
    void exceptionEarlyReported() override {}
    ~MockResultCapture() override = default;
};

// ---- A small test fixture to construct AssertionHandler with known inputs ----
class AssertionHandler_UnexpectedInflight_Test_555 : public ::testing::Test {
protected:
    StrictMock<MockResultCapture> mockCapture;

    // Helper to build an AssertionHandler with known info.
    // The real codebase's AssertionHandler owns/uses an IResultCapture internally.
    // In Catch2, this is typically wired up via internal plumbing; here we assume
    // the build under test wires our mock appropriately (as in the production codebase).
    AssertionHandler makeHandler() {
        // Minimal plausible arguments. We do not rely on any internal behavior;
        // the test only observes the interaction with IResultCapture.
        StringRef macro = StringRef("REQUIRE");
        SourceLineInfo lineInfo{ "fake_file.cpp", 123 };
        StringRef capturedExpr = StringRef("some expression");
        auto flags = ResultDisposition::Normal;

        // The production AssertionHandler constructor is used per provided interface.
        // We are not inspecting internals or states—only the call-out it performs.
        return AssertionHandler(macro, lineInfo, capturedExpr, flags);
    }
};

} // namespace Catch

// -------------------------------------------------------------------------------------
// Tests
// -------------------------------------------------------------------------------------

// Verifies that calling handleUnexpectedInflightException forwards to IResultCapture exactly once.
// We do not assert on parameter contents beyond existence (black-box behavior).
TEST_F(Catch::AssertionHandler_UnexpectedInflight_Test_555,
       ForwardsToResultCaptureOnce_555) {
    auto handler = makeHandler();

    // Expect that result capture will be told about the unexpected inflight exception once.
    EXPECT_CALL(mockCapture, handleUnexpectedInflightException(_, _, _))
        .Times(1);

    // Exercise
    handler.handleUnexpectedInflightException();
}

// Verifies that handleUnexpectedInflightException does not throw (observable behavior).
TEST_F(Catch::AssertionHandler_UnexpectedInflight_Test_555,
       DoesNotThrow_555) {
    auto handler = makeHandler();

    // Since we are only testing observable behavior, ensure no exceptions escape.
    EXPECT_CALL(mockCapture, handleUnexpectedInflightException(_, _, _))
        .Times(1);

    EXPECT_NO_THROW(handler.handleUnexpectedInflightException());
}

// Verifies delegation also occurs when an actual exception is currently active.
// We do NOT assert the translated message contents (implementation detail).
TEST_F(Catch::AssertionHandler_UnexpectedInflight_Test_555,
       DelegatesWithActiveException_555) {
    auto handler = makeHandler();

    // We only check that the delegation happens; message content is an internal detail.
    EXPECT_CALL(mockCapture, handleUnexpectedInflightException(_, _, _))
        .Times(1);

    try {
        throw std::runtime_error("boom");
    } catch (...) {
        // Under the hood, translateActiveException() will produce some message.
        // We treat it as an opaque string and only verify the call occurs.
        handler.handleUnexpectedInflightException();
    }
}
