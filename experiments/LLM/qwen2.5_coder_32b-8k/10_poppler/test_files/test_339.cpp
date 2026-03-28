#include <gtest/gtest.h>

#include "Link.h"

#include <vector>

#include <string>



class LinkSubmitFormTest_339 : public ::testing::Test {

protected:

    std::unique_ptr<LinkSubmitForm> link;



    void SetUp() override {

        // Assuming a mock or dummy Object* can be passed for testing purposes

        // In real scenarios, this would require actual object creation which is not possible here.

        // For the sake of test cases, we assume successful creation.

        link = std::make_unique<LinkSubmitForm>(nullptr);

    }

};



TEST_F(LinkSubmitFormTest_339, GetKindReturnsCorrectValue_339) {

    EXPECT_EQ(link->getKind(), actionSubmitForm);

}



TEST_F(LinkSubmitFormTest_339, IsOkReturnsTrueOnValidInitialization_339) {

    // Assuming the object is valid after initialization

    EXPECT_TRUE(link->isOk());

}



TEST_F(LinkSubmitFormTest_339, GetFieldsReturnsEmptyVectorByDefault_339) {

    EXPECT_TRUE(link->getFields().empty());

}



TEST_F(LinkSubmitFormTest_339, GetUrlReturnsEmptyStringByDefault_339) {

    EXPECT_EQ(link->getUrl(), "");

}



TEST_F(LinkSubmitFormTest_339, GetFlagsReturnsZeroByDefault_339) {

    EXPECT_EQ(link->getFlags(), 0);

}

```


