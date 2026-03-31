#include <gtest/gtest.h>
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

class MessageInfoTest_67 : public ::testing::Test {
protected:
    // Helper to create MessageInfo instances
    Catch::MessageInfo createMessageInfo(const char* macroName = "TEST_MACRO",
                                          unsigned int line = 1,
                                          Catch::ResultWas::OfType type = Catch::ResultWas::Info) {
        Catch::SourceLineInfo lineInfo(macroName, line);
        return Catch::MessageInfo(Catch::StringRef(macroName), lineInfo, type);
    }
};

// Test that operator< returns true when left sequence is less than right sequence
TEST_F(MessageInfoTest_67, OperatorLessThan_LeftLessThanRight_67) {
    // Create two MessageInfo objects sequentially
    // The first one should have a smaller sequence number
    Catch::MessageInfo first = createMessageInfo("MACRO1", 10);
    Catch::MessageInfo second = createMessageInfo("MACRO2", 20);

    EXPECT_TRUE(first < second);
}

// Test that operator< returns false when left sequence is greater than right sequence
TEST_F(MessageInfoTest_67, OperatorLessThan_LeftGreaterThanRight_67) {
    Catch::MessageInfo first = createMessageInfo("MACRO1", 10);
    Catch::MessageInfo second = createMessageInfo("MACRO2", 20);

    EXPECT_FALSE(second < first);
}

// Test that operator< returns false when both have the same sequence (same object)
TEST_F(MessageInfoTest_67, OperatorLessThan_SameObject_67) {
    Catch::MessageInfo msg = createMessageInfo("MACRO", 5);

    EXPECT_FALSE(msg < msg);
}

// Test that operator== returns true for the same object
TEST_F(MessageInfoTest_67, OperatorEquals_SameObject_67) {
    Catch::MessageInfo msg = createMessageInfo("MACRO", 5);

    EXPECT_TRUE(msg == msg);
}

// Test that operator== returns false for different objects (different sequences)
TEST_F(MessageInfoTest_67, OperatorEquals_DifferentObjects_67) {
    Catch::MessageInfo first = createMessageInfo("MACRO", 5);
    Catch::MessageInfo second = createMessageInfo("MACRO", 5);

    // Different sequence numbers, so they should not be equal
    EXPECT_FALSE(first == second);
}

// Test that sequence numbers are monotonically increasing
TEST_F(MessageInfoTest_67, SequenceIsMonotonicallyIncreasing_67) {
    Catch::MessageInfo msg1 = createMessageInfo("M1", 1);
    Catch::MessageInfo msg2 = createMessageInfo("M2", 2);
    Catch::MessageInfo msg3 = createMessageInfo("M3", 3);

    EXPECT_TRUE(msg1 < msg2);
    EXPECT_TRUE(msg2 < msg3);
    EXPECT_TRUE(msg1 < msg3);
}

// Test transitivity of operator<
TEST_F(MessageInfoTest_67, OperatorLessThan_Transitivity_67) {
    Catch::MessageInfo a = createMessageInfo("A", 1);
    Catch::MessageInfo b = createMessageInfo("B", 2);
    Catch::MessageInfo c = createMessageInfo("C", 3);

    // If a < b and b < c, then a < c
    ASSERT_TRUE(a < b);
    ASSERT_TRUE(b < c);
    EXPECT_TRUE(a < c);
}

// Test irreflexivity of operator<
TEST_F(MessageInfoTest_67, OperatorLessThan_Irreflexivity_67) {
    Catch::MessageInfo msg = createMessageInfo("MACRO", 42);

    EXPECT_FALSE(msg < msg);
}

// Test asymmetry of operator<: if a < b then !(b < a)
TEST_F(MessageInfoTest_67, OperatorLessThan_Asymmetry_67) {
    Catch::MessageInfo a = createMessageInfo("A", 1);
    Catch::MessageInfo b = createMessageInfo("B", 2);

    if (a < b) {
        EXPECT_FALSE(b < a);
    } else {
        EXPECT_TRUE(b < a);
    }
}

// Test MessageInfo with different ResultWas types
TEST_F(MessageInfoTest_67, ConstructionWithDifferentTypes_67) {
    Catch::SourceLineInfo lineInfo("file.cpp", 100);

    Catch::MessageInfo infoMsg(Catch::StringRef("INFO"), lineInfo, Catch::ResultWas::Info);
    Catch::MessageInfo warnMsg(Catch::StringRef("WARN"), lineInfo, Catch::ResultWas::Warning);

    // Both should be valid and have sequential ordering
    EXPECT_TRUE(infoMsg < warnMsg);
}

// Test that the type member is properly stored
TEST_F(MessageInfoTest_67, TypeIsStoredCorrectly_67) {
    Catch::SourceLineInfo lineInfo("file.cpp", 50);
    Catch::MessageInfo msg(Catch::StringRef("MACRO"), lineInfo, Catch::ResultWas::Info);

    EXPECT_EQ(msg.type, Catch::ResultWas::Info);
}

// Test that multiple messages created in sequence maintain strict ordering
TEST_F(MessageInfoTest_67, MultipleMessagesStrictOrdering_67) {
    std::vector<Catch::MessageInfo> messages;
    for (int i = 0; i < 10; ++i) {
        messages.push_back(createMessageInfo("MACRO", static_cast<unsigned int>(i)));
    }

    for (size_t i = 0; i < messages.size(); ++i) {
        for (size_t j = i + 1; j < messages.size(); ++j) {
            EXPECT_TRUE(messages[i] < messages[j])
                << "Expected messages[" << i << "] < messages[" << j << "]";
            EXPECT_FALSE(messages[j] < messages[i])
                << "Expected !(messages[" << j << "] < messages[" << i << "])";
        }
    }
}

// Test operator== reflexivity
TEST_F(MessageInfoTest_67, OperatorEquals_Reflexivity_67) {
    Catch::MessageInfo msg = createMessageInfo("MACRO", 1);
    EXPECT_TRUE(msg == msg);
}

// Test that sequence member is accessible and increases
TEST_F(MessageInfoTest_67, SequenceMemberAccessible_67) {
    Catch::MessageInfo first = createMessageInfo("M1", 1);
    Catch::MessageInfo second = createMessageInfo("M2", 2);

    EXPECT_LT(first.sequence, second.sequence);
}

} // namespace
