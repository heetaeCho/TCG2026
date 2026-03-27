#include <gtest/gtest.h>

#include "Link.h"



class LinkUnknownTest_344 : public ::testing::Test {

protected:

    std::unique_ptr<LinkUnknown> linkUnknown;



    void SetUp() override {

        linkUnknown = std::make_unique<LinkUnknown>("testAction");

    }

};



TEST_F(LinkUnknownTest_344, GetKindReturnsCorrectValue_344) {

    EXPECT_EQ(linkUnknown->getKind(), actionUnknown);

}



TEST_F(LinkUnknownTest_344, IsOkReturnsTrueForValidAction_344) {

    EXPECT_TRUE(linkUnknown->isOk());

}



TEST_F(LinkUnknownTest_344, GetActionReturnsCorrectString_344) {

    EXPECT_EQ(linkUnknown->getAction(), "testAction");

}



TEST_F(LinkUnknownTest_344, BoundaryConditionEmptyStringAction_344) {

    std::unique_ptr<LinkUnknown> linkUnknownEmpty = std::make_unique<LinkUnknown>("");

    EXPECT_TRUE(linkUnknownEmpty->isOk());

    EXPECT_EQ(linkUnknownEmpty->getAction(), "");

}



// Assuming isOk() can return false based on the action string, if not, this test can be removed.

// TEST_F(LinkUnknownTest_344, ExceptionalCaseInvalidAction_344) {

//     std::unique_ptr<LinkUnknown> linkUnknownInvalid = std::make_unique<LinkUnknown>("invalidAction");

//     EXPECT_FALSE(linkUnknownInvalid->isOk());

// }
