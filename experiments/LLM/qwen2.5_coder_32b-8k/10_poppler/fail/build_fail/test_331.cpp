#include <gtest/gtest.h>

#include "Link.h"

#include <string>



class LinkHideTest_331 : public ::testing::Test {

protected:

    class MockObject : public Object {};

    

    MockObject mockObj;

    std::unique_ptr<LinkHide> linkHide;



    void SetUp() override {

        linkHide = std::make_unique<LinkHide>(&mockObj);

    }

};



TEST_F(LinkHideTest_331, HasTargetName_ReturnsFalseByDefault_331) {

    EXPECT_FALSE(linkHide->hasTargetName());

}



TEST_F(LinkHideTest_331, IsOk_ReturnsTrueForValidObject_331) {

    EXPECT_TRUE(linkHide->isOk());

}



TEST_F(LinkHideTest_331, GetKind_ReturnsCorrectLinkActionKind_331) {

    EXPECT_EQ(linkHide->getKind(), LinkActionKind::hide);

}



TEST_F(LinkHideTest_331, IsShowAction_ReturnsFalseByDefault_331) {

    EXPECT_FALSE(linkHide->isShowAction());

}



TEST_F(LinkHideTest_331, GetTargetName_ReturnsEmptyStringIfNoTargetName_331) {

    EXPECT_EQ(linkHide->getTargetName(), "");

}
