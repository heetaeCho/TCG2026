#include <gtest/gtest.h>

#include "Link.h"



class LinkResetFormTest_337 : public ::testing::Test {

protected:

    std::unique_ptr<LinkResetForm> linkResetForm;



    void SetUp() override {

        // Assuming Object* can be nullptr for a basic setup, adjust as necessary

        linkResetForm = std::make_unique<LinkResetForm>(nullptr);

    }

};



TEST_F(LinkResetFormTest_337, GetExclude_ReturnsFalseByDefault_337) {

    EXPECT_FALSE(linkResetForm->getExclude());

}



TEST_F(LinkResetFormTest_337, IsOk_ReturnsTrueForValidObject_337) {

    // Assuming a valid Object* setup is required for isOk() to return true

    EXPECT_TRUE(linkResetForm->isOk());

}



TEST_F(LinkResetFormTest_337, GetKind_ReturnsCorrectLinkActionKind_337) {

    // Assuming LinkActionKind has a specific value for reset form actions

    EXPECT_EQ(linkResetForm->getKind(), LinkActionKind::reset_form);

}



TEST_F(LinkResetFormTest_337, GetFields_ReturnsEmptyVectorByDefault_337) {

    EXPECT_TRUE(linkResetForm->getFields().empty());

}
