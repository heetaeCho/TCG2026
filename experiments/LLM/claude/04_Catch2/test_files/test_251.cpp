#include <string>
#include <vector>
#include <memory>

#include "catch2/catch_message.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_test_macros.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace Catch;
using ::testing::_;
using ::testing::Invoke;
using ::testing::AtLeast;

class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo& info), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo& sectionLineInfo, Counts& assertions), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&& endInfo), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&& endInfo), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo& lineInfo), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr&& generator), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& info), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& stats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo& message), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo& message), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&& builder), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef message), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo& info, const ITransientExpression& expr, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo& info, ResultWas::OfType resultType, std::string&& message, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo& info, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo& info, std::string&& message, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo& info), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo& info, ResultWas::OfType resultType, AssertionReaction& reaction), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

class CapturerTest_251 : public ::testing::Test {
protected:
    MockResultCapture mockCapture;

    void SetUp() override {
        // Set the mock as the current result capture context
        // This depends on Catch2's internal mechanism for getResultCapture()
        // We need to register our mock so that getResultCapture() returns it
        Catch::IContext* ctx = &Catch::getCurrentMutableContext();
        if (ctx) {
            ctx->setResultCapture(&mockCapture);
        }
    }

    void TearDown() override {
        // Cleanup: the destructor of Capturer will call popScopedMessage
        // for captured messages, so we allow that
    }
};

// Test that captureValue with a single variable name calls pushScopedMessage once
TEST_F(CapturerTest_251, CaptureValueCallsPushScopedMessage_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    // Allow popScopedMessage calls during destruction
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x"_catch_sr);
        capturer.captureValue(0, "42");
    }
}

// Test that captureValue appends the value to the message
TEST_F(CapturerTest_251, CaptureValueAppendsValueToMessage_251) {
    std::string capturedMessage;
    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillOnce(Invoke([&](const MessageInfo& msg) {
            capturedMessage = msg.message;
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x"_catch_sr);
        capturer.captureValue(0, "42");
    }

    // The message should contain the value "42" appended to the name
    EXPECT_NE(capturedMessage.find("42"), std::string::npos);
}

// Test that captureValue with multiple names creates multiple messages
TEST_F(CapturerTest_251, CaptureMultipleValuesCallsPushScopedMessageMultipleTimes_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(2);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x, y"_catch_sr);
        capturer.captureValue(0, "42");
        capturer.captureValue(1, "100");
    }
}

// Test that the destructor calls popScopedMessage for each captured value
TEST_F(CapturerTest_251, DestructorCallsPopScopedMessageForEachCaptured_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(2);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(2);

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x, y"_catch_sr);
        capturer.captureValue(0, "42");
        capturer.captureValue(1, "100");
    }
}

// Test that destructor pops zero messages if no values were captured
TEST_F(CapturerTest_251, DestructorPopsNothingIfNothingCaptured_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(0);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(0);

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x"_catch_sr);
        // Do not call captureValue
    }
}

// Test that capturing only some of the declared values pops only those captured
TEST_F(CapturerTest_251, PartialCaptureOnlyPopsThoseCaptured_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x, y, z"_catch_sr);
        capturer.captureValue(0, "10");
        // Only capture first of three
    }
}

// Test that captured message contains the variable name
TEST_F(CapturerTest_251, CapturedMessageContainsVariableName_251) {
    std::string capturedMessage;
    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillOnce(Invoke([&](const MessageInfo& msg) {
            capturedMessage = msg.message;
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "myVar"_catch_sr);
        capturer.captureValue(0, "hello");
    }

    // The message should contain both the variable name and value
    EXPECT_NE(capturedMessage.find("myVar"), std::string::npos);
    EXPECT_NE(capturedMessage.find("hello"), std::string::npos);
}

// Test captureValue with empty string value
TEST_F(CapturerTest_251, CaptureValueWithEmptyString_251) {
    std::string capturedMessage;
    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillOnce(Invoke([&](const MessageInfo& msg) {
            capturedMessage = msg.message;
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "x"_catch_sr);
        capturer.captureValue(0, "");
    }

    // Message should still contain variable name even with empty value
    EXPECT_NE(capturedMessage.find("x"), std::string::npos);
}

// Test with a single variable having spaces in name string
TEST_F(CapturerTest_251, CaptureValueWithSpacesInNames_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("file.cpp", 5),
                          ResultWas::Info,
                          " x "_catch_sr);
        capturer.captureValue(0, "99");
    }
}

// Test that captureValues template works for single value
TEST_F(CapturerTest_251, CaptureValuesTemplateSingleValue_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "val"_catch_sr);
        capturer.captureValues(0, 42);
    }
}

// Test that captureValues template works for multiple values
TEST_F(CapturerTest_251, CaptureValuesTemplateMultipleValues_251) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(3);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(::testing::AnyNumber());

    {
        Capturer capturer("CAPTURE"_catch_sr,
                          SourceLineInfo("test.cpp", 10),
                          ResultWas::Info,
                          "a, b, c"_catch_sr);
        capturer.captureValues(0, 1, 2, 3);
    }
}
