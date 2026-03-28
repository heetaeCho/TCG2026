#include <gtest/gtest.h>

#include "Link.h"



class LinkResetFormTest_336 : public ::testing::Test {

protected:

    std::vector<std::string> sampleFields = {"field1", "field2"};

    LinkResetForm* linkResetForm;



    void SetUp() override {

        // Assuming a mock or some way to create a valid LinkResetForm object

        // For the sake of this example, we'll assume it can be created with sample fields

        linkResetForm = new LinkResetForm(/* mock Object */);

    }



    void TearDown() override {

        delete linkResetForm;

    }

};



TEST_F(LinkResetFormTest_336, GetFields_ReturnsCorrectVector_336) {

    // Assuming some way to set the fields in the object

    EXPECT_EQ(linkResetForm->getFields(), sampleFields);

}



TEST_F(LinkResetFormTest_336, IsOk_ReturnsTrueForValidObject_336) {

    EXPECT_TRUE(linkResetForm->isOk());

}



TEST_F(LinkResetFormTest_336, GetKind_ReturnsCorrectLinkActionKind_336) {

    // Assuming LinkActionKind has a known value for LinkResetForm

    EXPECT_EQ(linkResetForm->getKind(), /* expected LinkActionKind */);

}



TEST_F(LinkResetFormTest_336, GetExclude_ReturnsFalseByDefault_336) {

    // Assuming exclude is false by default or can be set to false

    EXPECT_FALSE(linkResetForm->getExclude());

}



// Boundary conditions and exceptional cases are not directly observable from the given interface.

// If there are ways to trigger such cases (e.g., invalid Object in constructor), they should be tested here.

```


