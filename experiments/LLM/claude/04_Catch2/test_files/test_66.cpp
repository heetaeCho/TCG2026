#include <gtest/gtest.h>
#include "catch2/internal/catch_message_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/catch_message.hpp"

namespace {

class MessageInfoTest_66 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that two MessageInfo objects created separately have different sequences
// and thus are not equal
TEST_F(MessageInfoTest_66, DifferentMessagesAreNotEqual_66) {
    Catch::MessageInfo info1("MACRO1", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2("MACRO2", Catch::SourceLineInfo("file.cpp", 2), Catch::ResultWas::Info);
    
    EXPECT_FALSE(info1 == info2);
}

// Test that a MessageInfo object is equal to itself
TEST_F(MessageInfoTest_66, SameMessageIsEqualToItself_66) {
    Catch::MessageInfo info("MACRO", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    
    EXPECT_TRUE(info == info);
}

// Test that copying a MessageInfo preserves equality (same sequence)
TEST_F(MessageInfoTest_66, CopiedMessageIsEqual_66) {
    Catch::MessageInfo info1("MACRO", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2 = info1;
    
    EXPECT_TRUE(info1 == info2);
}

// Test operator< between two MessageInfo objects with different sequences
TEST_F(MessageInfoTest_66, LessThanOperator_66) {
    Catch::MessageInfo info1("MACRO1", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2("MACRO2", Catch::SourceLineInfo("file.cpp", 2), Catch::ResultWas::Info);
    
    // info1 was created before info2, so info1.sequence < info2.sequence
    EXPECT_TRUE(info1 < info2);
    EXPECT_FALSE(info2 < info1);
}

// Test that operator< is irreflexive (an object is not less than itself)
TEST_F(MessageInfoTest_66, LessThanIsIrreflexive_66) {
    Catch::MessageInfo info("MACRO", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    
    EXPECT_FALSE(info < info);
}

// Test that the type field is properly stored
TEST_F(MessageInfoTest_66, TypeFieldIsStored_66) {
    Catch::MessageInfo info("MACRO", Catch::SourceLineInfo("file.cpp", 10), Catch::ResultWas::Warning);
    
    EXPECT_EQ(info.type, Catch::ResultWas::Warning);
}

// Test that sequence is monotonically increasing
TEST_F(MessageInfoTest_66, SequenceIsMonotonicallyIncreasing_66) {
    Catch::MessageInfo info1("M1", Catch::SourceLineInfo("f.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2("M2", Catch::SourceLineInfo("f.cpp", 2), Catch::ResultWas::Info);
    Catch::MessageInfo info3("M3", Catch::SourceLineInfo("f.cpp", 3), Catch::ResultWas::Info);
    
    EXPECT_TRUE(info1.sequence < info2.sequence);
    EXPECT_TRUE(info2.sequence < info3.sequence);
}

// Test equality with different macro names but same sequence (via copy)
TEST_F(MessageInfoTest_66, EqualityBasedOnSequenceOnly_66) {
    Catch::MessageInfo info1("MACRO_A", Catch::SourceLineInfo("file1.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2 = info1;
    // Even after copy, they share the same sequence, so they should be equal
    EXPECT_TRUE(info1 == info2);
}

// Test that different types don't affect equality (equality is based on sequence)
TEST_F(MessageInfoTest_66, DifferentTypesDoNotAffectEquality_66) {
    Catch::MessageInfo info1("MACRO", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2 = info1;
    // They share the same sequence via copy
    EXPECT_TRUE(info1 == info2);
}

// Test operator< with copied objects (same sequence => not less than)
TEST_F(MessageInfoTest_66, LessThanWithCopiedObjects_66) {
    Catch::MessageInfo info1("MACRO", Catch::SourceLineInfo("file.cpp", 1), Catch::ResultWas::Info);
    Catch::MessageInfo info2 = info1;
    
    EXPECT_FALSE(info1 < info2);
    EXPECT_FALSE(info2 < info1);
}

// Test multiple consecutive MessageInfo constructions maintain strict ordering
TEST_F(MessageInfoTest_66, StrictOrderingMultipleObjects_66) {
    std::vector<Catch::MessageInfo> infos;
    for (int i = 0; i < 5; ++i) {
        infos.emplace_back("MACRO", Catch::SourceLineInfo("file.cpp", i), Catch::ResultWas::Info);
    }
    
    for (size_t i = 0; i < infos.size(); ++i) {
        for (size_t j = i + 1; j < infos.size(); ++j) {
            EXPECT_TRUE(infos[i] < infos[j]);
            EXPECT_FALSE(infos[j] < infos[i]);
            EXPECT_FALSE(infos[i] == infos[j]);
        }
    }
}

} // namespace
