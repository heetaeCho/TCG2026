#include <gtest/gtest.h>

#include "Link.h"



using namespace testing;



class LinkHideTest : public ::testing::Test {

protected:

    MockObject mockObj;

    std::unique_ptr<LinkHide> linkHide;



    void SetUp() override {

        linkHide = std::make_unique<LinkHide>(&mockObj);

    }

};



TEST_F(LinkHideTest_330, IsOk_ReturnsTrue_330) {

    EXPECT_TRUE(linkHide->isOk());

}



TEST_F(LinkHideTest_330, GetKind_ReturnsActionHide_330) {

    EXPECT_EQ(linkHide->getKind(), actionHide);

}



TEST_F(LinkHideTest_330, HasTargetName_ReturnsFalse_WhenNoTargetNameFlag_330) {

    // Assuming hasTargetNameFlag is false by default or setup

    EXPECT_FALSE(linkHide->hasTargetName());

}



TEST_F(LinkHideTest_330, GetTargetName_ReturnsEmptyString_WhenNoTargetNameFlag_330) {

    // Assuming targetName is empty by default or setup

    EXPECT_EQ(linkHide->getTargetName(), "");

}



TEST_F(LinkHideTest_330, IsShowAction_ReturnsFalse_ByDefault_330) {

    // Assuming show is false by default

    EXPECT_FALSE(linkHide->isShowAction());

}

```


