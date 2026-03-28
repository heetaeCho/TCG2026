#include <gtest/gtest.h>

#include "catch2/internal/catch_message_info.hpp"



namespace Catch {

    struct StringRef;

    struct SourceLineInfo;

}



class MessageInfoTest_66 : public ::testing::Test {

protected:

    Catch::StringRef macroName = "MACRO_NAME";

    Catch::SourceLineInfo lineInfo = {"file.cpp", 42};

    Catch::ResultWas::OfType type = Catch::ResultWas::Ok;



    Catch::MessageInfo createMessageInfo() {

        return Catch::MessageInfo(macroName, lineInfo, type);

    }

};



TEST_F(MessageInfoTest_66, ConstructorSetsSequence_66) {

    auto info1 = createMessageInfo();

    auto info2 = createMessageInfo();



    EXPECT_NE(info1.sequence, info2.sequence);

}



TEST_F(MessageInfoTest_66, EqualityOperatorSameSequence_66) {

    Catch::MessageInfo info1(macroName, lineInfo, type);

    Catch::MessageInfo info2(macroName, lineInfo, type);



    // Manually set sequence to be the same for testing

    new (&info2.sequence) unsigned int(info1.sequence);



    EXPECT_TRUE(info1 == info2);

}



TEST_F(MessageInfoTest_66, EqualityOperatorDifferentSequence_66) {

    Catch::MessageInfo info1(macroName, lineInfo, type);

    Catch::MessageInfo info2(macroName, lineInfo, type);



    EXPECT_FALSE(info1 == info2);

}



TEST_F(MessageInfoTest_66, LessThanOperatorSameSequence_66) {

    Catch::MessageInfo info1(macroName, lineInfo, type);

    Catch::MessageInfo info2(macroName, lineInfo, type);



    // Manually set sequence to be the same for testing

    new (&info2.sequence) unsigned int(info1.sequence);



    EXPECT_FALSE(info1 < info2);

}



TEST_F(MessageInfoTest_66, LessThanOperatorDifferentSequence_66) {

    Catch::MessageInfo info1(macroName, lineInfo, type);

    Catch::MessageInfo info2(macroName, lineInfo, type);



    EXPECT_TRUE(info1 < info2 || info2 < info1);

}
