#include <catch2/catch_message.hpp>
#include <catch2/internal/catch_message_info.hpp>
#include <catch2/interfaces/catch_interfaces_capture.hpp>
#include <catch2/internal/catch_context.hpp>
#include <catch2/catch_test_macros.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

using namespace Catch;
using ::testing::_;
using ::testing::Invoke;

class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef, const SourceLineInfo&, Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&&), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef, const SourceLineInfo&), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef, SourceLineInfo, Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo&, const ITransientExpression&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo&, ResultWas::OfType, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo&, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo&, ResultWas::OfType, AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(std::string const&, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

class ScopedMessageTest_1053 : public ::testing::Test {
protected:
    MockResultCapture mockCapture;
    IResultCapture* previousCapture = nullptr;

    void SetUp() override {
        previousCapture = &getResultCapture();
        auto& ctx = Catch::getMutableContext();
        ctx.setResultCapture(&mockCapture);
    }

    void TearDown() override {
        if (previousCapture) {
            auto& ctx = Catch::getMutableContext();
            ctx.setResultCapture(previousCapture);
        }
    }

    MessageBuilder createBuilder(const char* message = "test message") {
        MessageBuilder builder("TEST_MACRO"_catch_sr, SourceLineInfo("file.cpp", 42), ResultWas::Info);
        builder << message;
        return builder;
    }
};

TEST_F(ScopedMessageTest_1053, ConstructorCallsPushScopedMessage_1053) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg(createBuilder("hello"));
    }
}

TEST_F(ScopedMessageTest_1053, DestructorCallsPopScopedMessage_1053) {
    ::testing::InSequence seq;
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg(createBuilder("goodbye"));
    }
    // pop should have been called by now
}

TEST_F(ScopedMessageTest_1053, MessageContentIsPreserved_1053) {
    std::string capturedMessage;
    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillOnce(Invoke([&](const MessageInfo& info) {
            capturedMessage = info.message;
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg(createBuilder("specific content"));
    }

    EXPECT_EQ(capturedMessage, "specific content");
}

TEST_F(ScopedMessageTest_1053, MoveConstructorDoesNotDoublePop_1053) {
    // When moving a ScopedMessage, only one pop should happen (from the new one)
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg1(createBuilder("move test"));
        ScopedMessage msg2(std::move(msg1));
        // msg1 is moved-from, so its destructor should NOT call popScopedMessage
        // msg2's destructor should call popScopedMessage
    }
}

TEST_F(ScopedMessageTest_1053, MMovedFlagInitiallyFalse_1053) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg(createBuilder("flag test"));
        EXPECT_FALSE(msg.m_moved);
    }
}

TEST_F(ScopedMessageTest_1053, MoveConstructorSetsMMovedOnSource_1053) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg1(createBuilder("move flag test"));
        ScopedMessage msg2(std::move(msg1));
        EXPECT_TRUE(msg1.m_moved);
        EXPECT_FALSE(msg2.m_moved);
    }
}

TEST_F(ScopedMessageTest_1053, MultipleScopedMessagesCallPushAndPopMultipleTimes_1053) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(3);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(3);

    {
        ScopedMessage msg1(createBuilder("first"));
        ScopedMessage msg2(createBuilder("second"));
        ScopedMessage msg3(createBuilder("third"));
    }
}

TEST_F(ScopedMessageTest_1053, PushAndPopCalledInCorrectOrder_1053) {
    std::vector<std::string> operations;

    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillRepeatedly(Invoke([&](const MessageInfo&) {
            operations.push_back("push");
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_))
        .WillRepeatedly(Invoke([&](const MessageInfo&) {
            operations.push_back("pop");
        }));

    {
        ScopedMessage msg(createBuilder("order test"));
        ASSERT_EQ(operations.size(), 1u);
        EXPECT_EQ(operations[0], "push");
    }

    ASSERT_EQ(operations.size(), 2u);
    EXPECT_EQ(operations[1], "pop");
}

TEST_F(ScopedMessageTest_1053, EmptyMessageContent_1053) {
    std::string capturedMessage;
    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillOnce(Invoke([&](const MessageInfo& info) {
            capturedMessage = info.message;
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        ScopedMessage msg(createBuilder(""));
    }

    EXPECT_EQ(capturedMessage, "");
}

TEST_F(ScopedMessageTest_1053, StreamedIntMessageContent_1053) {
    std::string capturedMessage;
    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillOnce(Invoke([&](const MessageInfo& info) {
            capturedMessage = info.message;
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        MessageBuilder builder("TEST_MACRO"_catch_sr, SourceLineInfo("file.cpp", 10), ResultWas::Info);
        builder << 42;
        ScopedMessage msg(std::move(builder));
    }

    EXPECT_EQ(capturedMessage, "42");
}

TEST_F(ScopedMessageTest_1053, NestedScopedMessagesPopInReverseOrder_1053) {
    std::vector<std::string> pushOrder;
    std::vector<std::string> popOrder;

    EXPECT_CALL(mockCapture, pushScopedMessage(_))
        .WillRepeatedly(Invoke([&](const MessageInfo& info) {
            pushOrder.push_back(info.message);
        }));
    EXPECT_CALL(mockCapture, popScopedMessage(_))
        .WillRepeatedly(Invoke([&](const MessageInfo& info) {
            popOrder.push_back(info.message);
        }));

    {
        ScopedMessage msg1(createBuilder("outer"));
        {
            ScopedMessage msg2(createBuilder("inner"));
        }
    }

    ASSERT_EQ(pushOrder.size(), 2u);
    ASSERT_EQ(popOrder.size(), 2u);
    EXPECT_EQ(pushOrder[0], "outer");
    EXPECT_EQ(pushOrder[1], "inner");
    EXPECT_EQ(popOrder[0], "inner");
    EXPECT_EQ(popOrder[1], "outer");
}

TEST_F(ScopedMessageTest_1053, CopyConstructorIsDeleted_1053) {
    // This is a compile-time check; if copy is deleted, the following should not compile.
    // We verify this with a static_assert.
    static_assert(!std::is_copy_constructible<ScopedMessage>::value,
                  "ScopedMessage should not be copy constructible");
}

TEST_F(ScopedMessageTest_1053, MoveConstructorIsAvailable_1053) {
    static_assert(std::is_move_constructible<ScopedMessage>::value,
                  "ScopedMessage should be move constructible");
}
