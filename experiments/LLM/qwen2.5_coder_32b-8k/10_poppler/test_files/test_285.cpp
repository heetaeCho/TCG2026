#include <gtest/gtest.h>

#include "Link.h"



class LinkGoToTest_285 : public ::testing::Test {

protected:

    std::unique_ptr<LinkGoTo> link;



    void SetUp() override {

        // Assuming Object* destObj can be nullptr for testing purposes

        link = std::make_unique<LinkGoTo>(nullptr);

    }

};



TEST_F(LinkGoToTest_285, GetNamedDest_ReturnsNullptr_285) {

    EXPECT_EQ(link->getNamedDest(), nullptr);

}



TEST_F(LinkGoToTest_285, IsOk_ReturnsFalse_WhenDestIsInvalid_285) {

    // Assuming invalid state can be set through constructor or other means

    EXPECT_FALSE(link->isOk());

}



TEST_F(LinkGoToTest_285, GetKind_ReturnsCorrectType_285) {

    // Assuming getKind returns a specific type for LinkGoTo

    EXPECT_EQ(link->getKind(), LinkActionKind::goTo);

}



TEST_F(LinkGoToTest_285, GetDest_ReturnsNullptr_285) {

    EXPECT_EQ(link->getDest(), nullptr);

}
