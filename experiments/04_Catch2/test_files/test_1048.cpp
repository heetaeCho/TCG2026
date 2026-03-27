#include <gtest/gtest.h>

#include <catch2/interfaces/catch_interfaces_reporter.hpp>

#include <catch2/internal/catch_stringref.hpp>

#include <catch2/catch_totals.hpp>

#include <catch2/catch_assertion_result.hpp>

#include <catch2/internal/catch_message_info.hpp>



using namespace Catch;



class AssertionStatsTest : public ::testing::Test {

protected:

    SourceLineInfo sourceInfo = {"filename.cpp", 42};

    AssertionResult assertionResult;

    std::vector<MessageInfo> infoMessages;

    Totals totals;



    void SetUp() override {

        assertionResult = AssertionResult(AssertionInfo("MacroName", sourceInfo), AssertionResultData());

        infoMessages = {MessageInfo(StringRef("macro"), sourceInfo, ResultWas::OfType::Ok)};

        totals.assertions.total = 1;

        totals.testCases.total = 1;

    }

};



TEST_F(AssertionStatsTest_1048, ConstructorWithNoMessage_1048) {

    AssertionResult noMessageAssertion(AssertionInfo("MacroName", sourceInfo), AssertionResultData());

    ASSERT_FALSE(noMessageAssertion.hasMessage());



    AssertionStats stats(noMessageAssertion, infoMessages, totals);

    EXPECT_EQ(stats.assertionResult.getMessage().empty(), true);

}



TEST_F(AssertionStatsTest_1048, ConstructorWithMessage_1048) {

    assertionResult.m_resultData.message = "This is a message";

    AssertionStats stats(assertionResult, infoMessages, totals);

    EXPECT_EQ(stats.assertionResult.getMessage().data(), std::string("This is a message"));

}



TEST_F(AssertionStatsTest_1048, ConstructorWithEmptyMessageVector_1048) {

    std::vector<MessageInfo> emptyMessages;

    AssertionStats stats(assertionResult, emptyMessages, totals);

    EXPECT_EQ(stats.infoMessages.empty(), true);

}



TEST_F(AssertionStatsTest_1048, ConstructorWithNonEmptyMessageVector_1048) {

    ASSERT_FALSE(infoMessages.empty());



    AssertionStats stats(assertionResult, infoMessages, totals);

    EXPECT_EQ(stats.infoMessages.size(), 1);

}



TEST_F(AssertionStatsTest_1048, CopyConstructor_1048) {

    AssertionStats original(assertionResult, infoMessages, totals);

    AssertionStats copy = original;

    EXPECT_EQ(copy.assertionResult.getMessage(), original.assertionResult.getMessage());

    EXPECT_EQ(copy.infoMessages, original.infoMessages);

    EXPECT_EQ(copy.totals, original.totals);

}



TEST_F(AssertionStatsTest_1048, MoveConstructor_1048) {

    AssertionStats original(assertionResult, infoMessages, totals);

    AssertionStats moved = std::move(original);

    EXPECT_EQ(moved.assertionResult.getMessage(), assertionResult.getMessage());

    // The following may need to be adjusted based on move semantics behavior

    // EXPECT_TRUE(original.infoMessages.empty());

}



TEST_F(AssertionStatsTest_1048, AssignmentOperator_1048) {

    AssertionStats original(assertionResult, infoMessages, totals);

    AssertionStats assigned;

    assigned = original;



    EXPECT_EQ(assigned.assertionResult.getMessage(), original.assertionResult.getMessage());

    EXPECT_EQ(assigned.infoMessages, original.infoMessages);

    EXPECT_EQ(assigned.totals, original.totals);

}



TEST_F(AssertionStatsTest_1048, MoveAssignmentOperator_1048) {

    AssertionStats original(assertionResult, infoMessages, totals);

    AssertionStats moved;

    moved = std::move(original);



    EXPECT_EQ(moved.assertionResult.getMessage(), assertionResult.getMessage());

    // The following may need to be adjusted based on move semantics behavior

    // EXPECT_TRUE(original.infoMessages.empty());

}
