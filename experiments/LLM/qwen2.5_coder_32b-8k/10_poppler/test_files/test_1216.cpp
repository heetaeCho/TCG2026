#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextPageTest : public ::testing::Test {

protected:

    TextPage* textPage;



    void SetUp() override {

        textPage = new TextPage(false, false);

    }



    void TearDown() override {

        delete textPage;

    }

};



TEST_F(TextPageTest_1216, GetFlows_ReturnsNonNullPointer_1216) {

    const TextFlow* flows = textPage->getFlows();

    EXPECT_NE(flows, nullptr);

}



TEST_F(TextPageTest_1216, GetFlows_ReturnsSamePointerOnMultipleCalls_1216) {

    const TextFlow* flowsFirstCall = textPage->getFlows();

    const TextFlow* flowsSecondCall = textPage->getFlows();

    EXPECT_EQ(flowsFirstCall, flowsSecondCall);

}



TEST_F(TextPageTest_1216, GetFlows_ReturnsPointerToConstTextFlow_1216) {

    const TextFlow* flows = textPage->getFlows();

    // The return type is already a pointer to const, so this test case is more of an observation.

    EXPECT_TRUE((std::is_same<const TextFlow*, decltype(flows)>::value));

}
