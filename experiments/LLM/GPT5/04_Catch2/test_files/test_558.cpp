// File: tests/assertion_handler_unexpected_exception_not_thrown_558.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/catch_tostring.hpp"
#include "catch2/catch_test_macros.hpp"

using ::testing::A;
using ::testing::_;
using ::testing::StrictMock;

namespace Catch {

// --- Test seam: ensure AssertionHandler grabs our mock from here in its ctor.
// In Catch2, AssertionHandler typically acquires IResultCapture via a global accessor.
// We provide a definition that returns our test-installed mock.

static IResultCapture* g_resultCaptureForTests_558 = nullptr;

// Forward-declare the accessor typically used inside AssertionHandler's ctor.
// Our definition here will be picked up at link-time by the test build.
IResultCapture& getResultCapture() {
    return *g_resultCaptureForTests_558;
}

} // namespace Catch

// Minimal strict mock for IResultCapture, limited to the method under test.
class MockResultCapture_558 : public Catch::IResultCapture {
public:
    // We only mock the interaction that is observable from handleUnexpectedExceptionNotThrown
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown,
                (const Catch::AssertionInfo& info, Catch::AssertionReaction& reaction), (override));

    // Provide default (noop) implementations for other pure virtuals to satisfy interface.
    // Using GMock's nice trick: declare but do not use; however the interface is wide, so we stub them.
    // These can be left unmocked because test never calls them.
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
    void handleUnexpectedInflightException(const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&) override {}
    void handleIncomplete(const Catch::AssertionInfo&) override {}
    void handleNonExpr(const Catch::AssertionInfo&, Catch::ResultWas::OfType, Catch::AssertionReaction&) override {}
    bool lastAssertionPassed() override { return true; }
    void assertionPassed() override {}
    const std::string getCurrentTestName() override { return {}; }
    const Catch::AssertionResult* getLastResult() override { return nullptr; }
    void exceptionEarlyReported() override {}
};

// Test fixture wires the mock into the accessor seam.
class AssertionHandlerUnexpectedNotThrownTest_558 : public ::testing::Test {
protected:
    StrictMock<MockResultCapture_558> mock_;

    void SetUp() override {
        Catch::g_resultCaptureForTests_558 = &mock_;
    }
    void TearDown() override {
        Catch::g_resultCaptureForTests_558 = nullptr;
    }

    // Helper to construct the SUT with arbitrary, but well-formed inputs.
    Catch::AssertionHandler makeHandler() {
        const Catch::StringRef macroName{"REQUIRE_THROWS_NOTHROW"};
        const Catch::SourceLineInfo lineInfo{__FILE__, __LINE__};
        const Catch::StringRef captured{"some_call()"};
        const auto disposition = Catch::ResultDisposition::Normal;
        return Catch::AssertionHandler{macroName, lineInfo, captured, disposition};
    }
};

// Verifies that the handler forwards to IResultCapture with the (opaque) AssertionInfo and Reaction.
// We do not assert field contents — we only validate the observable interaction.
TEST_F(AssertionHandlerUnexpectedNotThrownTest_558, ForwardsToResultCaptureOnce_558) {
    auto handler = makeHandler();

    EXPECT_CALL(mock_,
        handleUnexpectedExceptionNotThrown(
            A<const Catch::AssertionInfo&>(),
            A<Catch::AssertionReaction&>()))
        .Times(1);

    // Act
    handler.handleUnexpectedExceptionNotThrown();
}

// A slightly stronger check that the same call can be made safely multiple times (idempotence not assumed),
// but at least that each call results in a corresponding forwarded interaction.
TEST_F(AssertionHandlerUnexpectedNotThrownTest_558, MultipleCallsEachForwardOnce_558) {
    auto handler = makeHandler();

    EXPECT_CALL(mock_,
        handleUnexpectedExceptionNotThrown(
            A<const Catch::AssertionInfo&>(),
            A<Catch::AssertionReaction&>()))
        .Times(2);

    // Act
    handler.handleUnexpectedExceptionNotThrown();
    handler.handleUnexpectedExceptionNotThrown();
}

