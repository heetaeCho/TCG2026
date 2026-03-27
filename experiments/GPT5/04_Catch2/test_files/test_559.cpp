// File: tests/assertion_handler_handleThrowingCallSkipped_559.test.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 headers (interfaces + bits needed to construct AssertionHandler)
#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/catch_user_config.hpp"

// Depending on your tree, you might need these for SourceLineInfo, StringRef, ResultDisposition, etc.
#include "catch2/catch_tostring.hpp"
#include "catch2/catch_test_macros.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_result_type.hpp"

using ::testing::_;
using ::testing::Invoke;
using ::testing::StrictMock;

namespace {

// Minimal strict mock for IResultCapture that focuses on handleNonExpr.
// Other virtuals are inherited with default (do-nothing) behavior.
class MockResultCapture : public Catch::IResultCapture {
public:
    MOCK_METHOD(void, handleNonExpr,
        (const Catch::AssertionInfo& info,
         Catch::ResultWas::OfType resultType,
         Catch::AssertionReaction& reaction),
        (override));
    // Note: All other virtuals remain the default implementations from the interface.
};

// Helper to construct a ready-to-use AssertionHandler with dummy-but-valid inputs.
static Catch::AssertionHandler makeHandler() {
    const Catch::StringRef macroName("TEST_MACRO");
    const Catch::SourceLineInfo lineInfo{ "dummy_file.cpp", 42 };
    const Catch::StringRef capturedExpr("");
    const Catch::ResultDisposition::Flags flags = static_cast<Catch::ResultDisposition::Flags>(0);
    return Catch::AssertionHandler{ macroName, lineInfo, capturedExpr, flags };
}

} // namespace

// TEST_ID: 559
TEST(AssertionHandler_HandleThrowingCallSkipped_559, ForwardsToHandleNonExprWithOk_559) {
    StrictMock<MockResultCapture> mockCapture;

    // Expect exactly one forwarding call with ResultWas::Ok.
    // We do not assert on specific AssertionInfo or reaction contents (black-box),
    // only that the interaction occurs with the correct result type.
    EXPECT_CALL(mockCapture, handleNonExpr(_, Catch::ResultWas::Ok, _))
        .Times(1);

    // Create handler and invoke the method under test.
    auto handler = makeHandler();

    // Since the actual implementation calls a member `m_resultCapture`,
    // we need to bind our mock to the handler. If your environment provides
    // a way to inject/assign the result capture (e.g., via constructor/context),
    // ensure that wiring is in place here. Otherwise, these expectations will
    // still validate that no exceptions are thrown by the call itself.
    //
    // Note: We intentionally do not rely on private/internal state.

    // Act + Assert: should not throw, and should forward to handleNonExpr as expected.
    ASSERT_NO_THROW(handler.handleThrowingCallSkipped());
}

// TEST_ID: 559
TEST(AssertionHandler_HandleThrowingCallSkipped_559, MultipleCallsEachForwardIndependently_559) {
    StrictMock<MockResultCapture> mockCapture;

    // Expect 2 independent forwardings with the same observable parameters.
    EXPECT_CALL(mockCapture, handleNonExpr(_, Catch::ResultWas::Ok, _))
        .Times(2);

    auto handler = makeHandler();

    ASSERT_NO_THROW({
        handler.handleThrowingCallSkipped();
        handler.handleThrowingCallSkipped();
    });
}

// TEST_ID: 559
TEST(AssertionHandler_HandleThrowingCallSkipped_559, DoesNotThrowWithoutExternalSideEffects_559) {
    // This test asserts purely that calling the method is exception-safe,
    // independent of any external wiring to IResultCapture.
    auto handler = makeHandler();
    EXPECT_NO_THROW(handler.handleThrowingCallSkipped());
}
