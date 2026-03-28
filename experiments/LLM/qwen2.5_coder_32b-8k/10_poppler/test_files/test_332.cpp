#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Link.h"



class LinkHideTest_332 : public ::testing::Test {

protected:

    LinkHide *linkHide;



    virtual void SetUp() {

        // Assuming Object is a placeholder and we need to mock it or pass a valid instance

        // For simplicity, let's assume we have a way to create a valid Object for testing.

        // Here, we are just creating a null pointer as a placeholder.

        const Object* hideObj = nullptr;

        linkHide = new LinkHide(hideObj);

    }



    virtual void TearDown() {

        delete linkHide;

    }

};



TEST_F(LinkHideTest_332, IsOk_ReturnsTrue_332) {

    EXPECT_TRUE(linkHide->isOk());

}



TEST_F(LinkHideTest_332, GetKind_ReturnsCorrectKind_332) {

    EXPECT_EQ(linkHide->getKind(), LinkActionKind::hide);

}



TEST_F(LinkHideTest_332, HasTargetName_ReturnsFalseWhenNoTargetName_332) {

    EXPECT_FALSE(linkHide->hasTargetName());

}



TEST_F(LinkHideTest_332, GetTargetName_ReturnsEmptyStringWhenNoTargetName_332) {

    EXPECT_EQ(linkHide->getTargetName(), "");

}



TEST_F(LinkHideTest_332, IsShowAction_ReturnsFalse_332) {

    EXPECT_FALSE(linkHide->isShowAction());

}

```


