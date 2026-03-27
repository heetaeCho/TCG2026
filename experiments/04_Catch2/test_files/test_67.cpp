#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_message_info.hpp"



namespace Catch {

    struct SourceLineInfo {};

}



using namespace Catch;



class MessageInfoTest_67 : public ::testing::Test {

protected:

    SourceLineInfo lineInfo;

};



TEST_F(MessageInfoTest_67, ConstructorInitializesSequence_67) {

    unsigned int initialSequence = 0;

    ResultWas::OfType type = ResultWas::Ok;

    StringRef macroName("INFO");

    

    MessageInfo info(macroName, lineInfo, type);

    

    EXPECT_EQ(info.sequence, ++initialSequence);

}



TEST_F(MessageInfoTest_67, ComparisonOperatorsWorkCorrectly_67) {

    unsigned int initialSequence = 0;

    ResultWas::OfType type1 = ResultWas::Ok;

    ResultWas::OfType type2 = ResultWas::Failure;

    StringRef macroName("INFO");

    

    MessageInfo info1(macroName, lineInfo, type1);

    MessageInfo info2(macroName, lineInfo, type2);



    EXPECT_TRUE(info1 < info2);

    EXPECT_FALSE(info2 < info1);

}



TEST_F(MessageInfoTest_67, EqualityOperatorWorksCorrectly_67) {

    unsigned int initialSequence = 0;

    ResultWas::OfType type = ResultWas::Ok;

    StringRef macroName("INFO");

    

    MessageInfo info1(macroName, lineInfo, type);

    MessageInfo info2(macroName, lineInfo, type);



    EXPECT_TRUE(info1 == info2);

}



TEST_F(MessageInfoTest_67, DifferentSequencesYieldInequality_67) {

    unsigned int initialSequence = 0;

    ResultWas::OfType type = ResultWas::Ok;

    StringRef macroName("INFO");

    

    MessageInfo info1(macroName, lineInfo, type);

    MessageInfo info2(macroName, lineInfo, type);



    EXPECT_FALSE(info1 == info2);

}
