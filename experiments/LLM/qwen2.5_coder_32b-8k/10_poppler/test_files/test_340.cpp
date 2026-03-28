#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



class LinkSubmitFormTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize with a valid Object pointer if necessary for actual tests

        submitObj = new Object();

        linkSubmitForm = std::make_unique<LinkSubmitForm>(submitObj);

    }



    void TearDown() override {

        delete submitObj;

    }



    Object* submitObj;

    std::unique_ptr<LinkSubmitForm> linkSubmitForm;

};



TEST_F(LinkSubmitFormTest_340, GetFields_ReturnsEmptyVectorByDefault_340) {

    EXPECT_TRUE(linkSubmitForm->getFields().empty());

}



TEST_F(LinkSubmitFormTest_340, IsOk_ReturnsTrueForValidObject_340) {

    EXPECT_TRUE(linkSubmitForm->isOk());

}



TEST_F(LinkSubmitFormTest_340, GetKind_ReturnsCorrectKind_340) {

    EXPECT_EQ(linkSubmitForm->getKind(), LinkActionKind::submit_form);

}



TEST_F(LinkSubmitFormTest_340, GetUrl_ReturnsEmptyStringByDefault_340) {

    EXPECT_TRUE(linkSubmitForm->getUrl().empty());

}



TEST_F(LinkSubmitFormTest_340, GetFlags_ReturnsZeroByDefault_340) {

    EXPECT_EQ(linkSubmitForm->getFlags(), 0u);

}
