// File: assertion_handler_handle_message_552_tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include Catch2 interfaces that define the types used by the SUT forwarder
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_assertion_handler.hpp"

using ::testing::_;
using ::testing::ByRef;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::StrEq;

namespace Catch {

// ===== Test seam to inject mock IResultCapture =====
// Many Catch2 internals retrieve the active result capture via a free function.
// We provide a test override here so AssertionHandler resolves to our mock.
static IResultCapture* g_mockCapture_552 = nullptr;

// If your Catch2 version already provides this symbol, mark this as weak or link
// these tests in a TU that wins resolution. Most build systems will prefer this
// definition from the test when linking the test binary.
IResultCapture& getResultCapture() {
    return *g_mockCapture_552;
}

} // namespace Catch

// ===== GMock of IResultCapture =====
class MockResultCapture_552 : public Catch::IResultCapture {
public:
    // Provide concrete (no-op) overrides for all pure-virtuals we don't care about
    // and a MOCK_METHOD for handleMessage that we verify.
    ~MockResultCapture_552() override = default;

    // We only mock handleMessage (the one exercised by AssertionHandler::handleMessage)
    MOCK_METHOD(void, handleMessage,
        (const Catch::AssertionInfo&,
         Catch::ResultWas::OfType,
         std::string&&,
         Catch::AssertionReaction&),
        (override));

    // The rest: minimal, do-nothing overrides to satisfy the vtable
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
    void handleUnexpectedExceptionNotThrown(const Catch::AssertionInfo&, Catch::AssertionReaction&) override {}
    void handleUnexpectedInflightException(const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&) override {}
    void handleIncomplete(const Catch::AssertionInfo&) override {}
    void handleNonExpr(const Catch::AssertionInfo&, Catch::ResultWas::OfType, Catch::AssertionReaction&) override {}
    bool lastAssertionPassed() override { return true; }
    void assertionPassed() override {}
    const std::string getCurrentTestName() override { static std::string n = "test"; return n; }
    const Catch::AssertionResult* getLastResult() override { return nullptr; }
    void exceptionEarlyReported() override {}
};

// ===== Test fixture =====
class AssertionHandlerHandleMessageTest_552 : public ::testing::Test {
protected:
    MockResultCapture_552 mock_;
    void SetUp() override {
        Catch::g_mockCapture_552 = &mock_;
    }
    void TearDown() override {
        Catch::g_mockCapture_552 = nullptr;
    }

    // Helper to build a minimal AssertionHandler under test.
    // We use arbitrary, valid inputs — we do not assert their internal usage.
    Catch::AssertionHandler makeHandler() {
        // Minimal arguments based on the public constructor signature
        const Catch::StringRef macroName = "REQUIRE";
        const Catch::SourceLineInfo lineInfo{__FILE__, __LINE__};
        const Catch::StringRef capturedExpr = "1 == 1";
        const Catch::ResultDisposition::Flags disp = Catch::ResultDisposition::Normal;
        return Catch::AssertionHandler(macroName, lineInfo, capturedExpr, disp);
    }
};

// ========== Tests ==========

// Normal operation: forwards type + message to IResultCapture::handleMessage
TEST_F(AssertionHandlerHandleMessageTest_552, ForwardsMessageAndType_Normal_552) {
    auto handler = makeHandler();

    const Catch::ResultWas::OfType type = Catch::ResultWas::Info;
    std::string msg = "hello world";

    EXPECT_CALL(mock_, handleMessage(_, type, StrEq("hello world"), _))
        .Times(1);

    handler.handleMessage(type, std::move(msg));
    // We do NOT assert on msg after move (moved-from state is unspecified).
}

// Boundary: empty message should still be forwarded
TEST_F(AssertionHandlerHandleMessageTest_552, ForwardsEmptyMessage_552) {
    auto handler = makeHandler();

    const Catch::ResultWas::OfType type = Catch::ResultWas::Warning;
    std::string msg;

    EXPECT_CALL(mock_, handleMessage(_, type, StrEq(""), _))
        .Times(1);

    handler.handleMessage(type, std::move(msg));
}

// Boundary: large / unicode message is forwarded intact
TEST_F(AssertionHandlerHandleMessageTest_552, ForwardsLargeUnicodeMessage_552) {
    auto handler = makeHandler();

    const Catch::ResultWas::OfType type = Catch::ResultWas::ExplicitFailure;
    std::string msg(4096, 'x'); // large payload
    msg.replace(100, 4, u8"한글😊"); // sprinkle some unicode

    // Capture the expected content before move
    const std::string expected = msg;

    EXPECT_CALL(mock_, handleMessage(_, type, StrEq(expected), _))
        .Times(1);

    handler.handleMessage(type, std::move(msg));
}

// Sanity: multiple calls are independently forwarded (no internal accumulation tested)
TEST_F(AssertionHandlerHandleMessageTest_552, ForwardsAcrossMultipleCalls_552) {
    auto handler = makeHandler();

    EXPECT_CALL(mock_, handleMessage(_, Catch::ResultWas::Info, StrEq("a"), _)).Times(1);
    EXPECT_CALL(mock_, handleMessage(_, Catch::ResultWas::Warning, StrEq("b"), _)).Times(1);

    std::string a = "a";
    handler.handleMessage(Catch::ResultWas::Info, std::move(a));

    std::string b = "b";
    handler.handleMessage(Catch::ResultWas::Warning, std::move(b));
}

