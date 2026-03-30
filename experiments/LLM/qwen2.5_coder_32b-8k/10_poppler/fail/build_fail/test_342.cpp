#include <gtest/gtest.h>

#include "Link.h"



class LinkSubmitFormTest_342 : public ::testing::Test {

protected:

    LinkSubmitForm* link_submit_form;



    void SetUp() override {

        // Assuming Object is a mockable or testable class, we create a mock object for it.

        // Since the actual implementation of Object is not provided, we use nullptr here.

        // In real scenarios, you would initialize this with appropriate values.

        link_submit_form = new LinkSubmitForm(nullptr);

    }



    void TearDown() override {

        delete link_submit_form;

    }

};



TEST_F(LinkSubmitFormTest_342, IsOkReturnsTrueForValidObject_342) {

    EXPECT_TRUE(link_submit_form->isOk());

}



TEST_F(LinkSubmitFormTest_342, GetKindReturnsCorrectType_342) {

    EXPECT_EQ(link_submit_form->getKind(), LinkActionKind::submitForm);

}



TEST_F(LinkSubmitFormTest_342, GetFieldsReturnsEmptyVectorByDefault_342) {

    EXPECT_TRUE(link_submit_form->getFields().empty());

}



TEST_F(LinkSubmitFormTest_342, GetUrlReturnsEmptyStringByDefault_342) {

    EXPECT_EQ(link_submit_form->getUrl(), "");

}



TEST_F(LinkSubmitFormTest_342, GetFlagsReturnsZeroByDefault_342) {

    EXPECT_EQ(link_submit_form->getFlags(), 0);

}

```


