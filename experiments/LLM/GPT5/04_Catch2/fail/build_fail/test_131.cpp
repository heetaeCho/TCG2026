// File: assertion_handler_dtor_tests_131.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the class under test (paths from the prompt)
#include "Catch2/src/catch2/internal/catch_assertion_handler.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Expectation;
using ::testing::AtMost;

namespace {

// ---- Test seam for Catch2 result capture access ----
// Many Catch2 internals obtain the active IResultCapture via a global accessor.
// We provide a controllable seam here so AssertionHandler uses our mock.
//
// If your codebase already defines Catch::getResultCapture(), keep THIS in a
// separate TU or delete it to avoid ODR clashes.
::Catch::IResultCapture* g_activeCapture = nullptr;

} // namespace

namespace Catch {
// Provide a weak/ODR-accessor seam so CUT calls land on our mock.
// Remove if your environment already supplies this.
IResultCapture& getResultCapture() {
    // Fallback to a dummy if not set, but tests will set it.
    return *g_activeCapture;
}
} // namespace Catch

// ---- Mock for the external collaborator (IResultCapture) ----
class MockResultCapture : public Catch::IResultCapture {
public:
    // We only care about handleIncomplete for these tests.
    MOCK_METHOD(void, handleIncomplete, (const Catch::AssertionInfo&), (override));

    // Provide safe defaults for other virtuals so constructing/destroying the
    // handler won't explode if it touches them. We do NOT simulate internal logic.
    MOCK_METHOD(void, notifyAssertionStarted, (const Catch::AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted, (Catch::StringRef, const Catch::SourceLineInfo&, Catch::Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(Catch::IGeneratorTracker*, acquireGeneratorTracker,
                (Catch::StringRef, const Catch::SourceLineInfo&), (override));
    MOCK_METHOD(Catch::IGeneratorTracker*, createGeneratorTracker,
                (Catch::StringRef, Catch::SourceLineInfo, Catch::Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const Catch::BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, ((const Catch::BenchmarkStats<>&)), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (const Catch::MessageInfo&), (override));
    MOCK_METHOD(void, popScopedMessage, (const Catch::MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (Catch::MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (Catch::StringRef), (override));
    MOCK_METHOD(void, handleExpr, (const Catch::AssertionInfo&, const Catch::ITransientExpression&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (const Catch::AssertionInfo&, Catch::ResultWas::OfType, std::string&&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const Catch::AssertionInfo&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleNonExpr, (const Catch::AssertionInfo&, Catch::ResultWas::OfType, Catch::AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const Catch::AssertionResult*, getLastResult, (), (override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Simple RAII helper to install/uninstall the global capture seam.
struct CaptureGuard {
    explicit CaptureGuard(Catch::IResultCapture* cap) { g_activeCapture = cap; }
    ~CaptureGuard() { g_activeCapture = nullptr; }
};

// Common dummy inputs for constructing AssertionHandler without relying on internals.
static const Catch::StringRef kMacroName = "REQUIRE";
static const Catch::StringRef kExpr      = "1 == 1";
static const Catch::SourceLineInfo kLineInfo{ "dummy_file.cpp", 123 };
static const Catch::ResultDisposition::Flags kDisp =
    static_cast<Catch::ResultDisposition::Flags>(0);

class AssertionHandlerTest_131 : public ::testing::Test {};

// 1) Normal operation: if not completed, dtor must report incomplete exactly once.
TEST_F(AssertionHandlerTest_131, DestructorCallsHandleIncompleteWhenNotCompleted_131) {
    NiceMock<MockResultCapture> mock;
    CaptureGuard guard(&mock);

    // We only assert the interaction occurs; we do not peek into private state.
    EXPECT_CALL(mock, handleIncomplete(_)).Times(1);

    {
        Catch::AssertionHandler handler(kMacroName, kLineInfo, kExpr, kDisp);
        // Intentionally do not call handler.complete();
        // Observable behavior is via destructor calling handleIncomplete.
    } // <- destructor runs here
}

// 2) Boundary: once completed, dtor must NOT report incomplete.
TEST_F(AssertionHandlerTest_131, DestructorDoesNotCallHandleIncompleteAfterComplete_131) {
    NiceMock<MockResultCapture> mock;
    CaptureGuard guard(&mock);

    EXPECT_CALL(mock, handleIncomplete(_)).Times(0);

    {
        Catch::AssertionHandler handler(kMacroName, kLineInfo, kExpr, kDisp);
        handler.complete(); // Mark as completed through the public API.
    } // <- destructor should NOT call handleIncomplete
}

// 3) Idempotency: multiple complete() calls still prevent the incomplete report.
TEST_F(AssertionHandlerTest_131, MultipleCompleteStillPreventsIncompleteReport_131) {
    NiceMock<MockResultCapture> mock;
    CaptureGuard guard(&mock);

    EXPECT_CALL(mock, handleIncomplete(_)).Times(0);

    {
        Catch::AssertionHandler handler(kMacroName, kLineInfo, kExpr, kDisp);
        handler.complete();
        handler.complete(); // Calling twice should be harmless and keep it completed.
    }
}

// 4) Smoke: invoking unrelated public methods does not *force* completion;
//    if complete() is not called, destructor should still report incomplete.
TEST_F(AssertionHandlerTest_131, OtherCallsWithoutCompleteStillReportIncomplete_131) {
    NiceMock<MockResultCapture> mock;
    CaptureGuard guard(&mock);

    EXPECT_CALL(mock, handleIncomplete(_)).Times(1);

    {
        Catch::AssertionHandler handler(kMacroName, kLineInfo, kExpr, kDisp);
        // Exercise some public APIs without assuming they toggle completion.
        // We do not assert their internals, only the destructor's observable behavior.
        handler.allowThrows();
        handler.handleUnexpectedInflightException();
        handler.handleThrowingCallSkipped();
        // No handler.complete() here.
    } // <- should still call handleIncomplete exactly once
}
