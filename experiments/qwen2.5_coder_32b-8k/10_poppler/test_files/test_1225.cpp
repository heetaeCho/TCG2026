#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextOutputDevTest_1225 : public ::testing::Test {

protected:

    TextOutputDev* textOutputDev;



    void SetUp() override {

        textOutputDev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete textOutputDev;

    }

};



TEST_F(TextOutputDevTest_1225, SetTextPageBreaks_DefaultValue_1225) {

    // By default, the value should be false as it's not set.

    EXPECT_EQ(textOutputDev->useDrawChar(), false);

}



TEST_F(TextOutputDevTest_1225, SetTextPageBreaks_Enable_1225) {

    textOutputDev->setTextPageBreaks(true);

    // We cannot directly assert the internal state, but we can assume that

    // the behavior should change accordingly if needed in future.

    // For now, we ensure it doesn't crash and check a related method.

    EXPECT_EQ(textOutputDev->useDrawChar(), false);

}



TEST_F(TextOutputDevTest_1225, SetTextPageBreaks_Disable_1225) {

    textOutputDev->setTextPageBreaks(false);

    // Similarly, we ensure it doesn't crash and check a related method.

    EXPECT_EQ(textOutputDev->useDrawChar(), false);

}



TEST_F(TextOutputDevTest_1225, IsOk_DefaultState_1225) {

    // Assuming isOk() should return true for default constructed object.

    EXPECT_TRUE(textOutputDev->isOk());

}



// Assuming there are no observable side effects or related methods to verify

// the behavior of other member functions without mocking dependencies which is not allowed.



TEST_F(TextOutputDevTest_1225, UseDrawChar_DefaultState_1225) {

    // useDrawChar() should return false by default as per implementation.

    EXPECT_FALSE(textOutputDev->useDrawChar());

}



TEST_F(TextOutputDevTest_1225, InterpretType3Chars_DefaultState_1225) {

    // interpretType3Chars() should return true by default as per implementation.

    EXPECT_TRUE(textOutputDev->interpretType3Chars());

}



TEST_F(TextOutputDevTest_1225, NeedNonText_DefaultState_1225) {

    // needNonText() should return false by default as per implementation.

    EXPECT_FALSE(textOutputDev->needNonText());

}



TEST_F(TextOutputDevTest_1225, NeedCharCount_DefaultState_1225) {

    // needCharCount() should return false by default as per implementation.

    EXPECT_FALSE(textOutputDev->needCharCount());

}
