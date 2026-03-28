#include <gtest/gtest.h>

#include "Link.h"

#include <vector>

#include <string>



class LinkResetFormTest_335 : public ::testing::Test {

protected:

    std::unique_ptr<LinkResetForm> link_reset_form;



    void SetUp() override {

        // Assuming Object is a placeholder for actual construction parameters

        const Object* nameObj = nullptr; // This should be replaced with actual object if needed

        link_reset_form = std::make_unique<LinkResetForm>(nameObj);

    }

};



TEST_F(LinkResetFormTest_335, GetKindReturnsCorrectValue_335) {

    EXPECT_EQ(link_reset_form->getKind(), actionResetForm);

}



TEST_F(LinkResetFormTest_335, IsOkReturnsTrueWhenValid_335) {

    // Assuming a valid state for the object

    EXPECT_TRUE(link_reset_form->isOk());

}



TEST_F(LinkResetFormTest_335, GetFieldsReturnsEmptyVectorByDefault_335) {

    EXPECT_TRUE(link_reset_form->getFields().empty());

}



TEST_F(LinkResetFormTest_335, GetExcludeReturnsFalseByDefault_335) {

    EXPECT_FALSE(link_reset_form->getExclude());

}

```


