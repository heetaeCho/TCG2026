#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"



class FormFieldTest_882 : public ::testing::Test {

protected:

    PDFDoc* doc = nullptr;

    Object obj;

    Ref ref = {0, 0};

    FormField parentField(nullptr, std::move(obj), ref, nullptr, static_cast<std::set<int>*>(nullptr), formFieldTypeText);

    FormField field{&parentField, std::move(obj), ref, &parentField, static_cast<std::set<int>*>(nullptr), formFieldTypeText};



    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(FormFieldTest_882, SetStandAloneTrue_882) {

    field.setStandAlone(true);

    EXPECT_TRUE(field.isStandAlone());

}



TEST_F(FormFieldTest_882, SetStandAloneFalse_882) {

    field.setStandAlone(false);

    EXPECT_FALSE(field.isStandAlone());

}



TEST_F(FormFieldTest_882, GetNumWidgets_Default_882) {

    EXPECT_EQ(field.getNumWidgets(), 0);

}



TEST_F(FormFieldTest_882, GetNumChildren_Default_882) {

    EXPECT_EQ(field.getNumChildren(), 0);

}



TEST_F(FormFieldTest_882, IsReadOnly_Default_882) {

    EXPECT_FALSE(field.isReadOnly());

}



TEST_F(FormFieldTest_882, SetReadOnly_True_882) {

    field.setReadOnly(true);

    EXPECT_TRUE(field.isReadOnly());

}



TEST_F(FormFieldTest_882, SetReadOnly_False_882) {

    field.setReadOnly(false);

    EXPECT_FALSE(field.isReadOnly());

}



TEST_F(FormFieldTest_882, HasTextQuadding_Default_882) {

    EXPECT_FALSE(field.hasTextQuadding());

}



// Additional tests can be added based on other observable behaviors or functions

```


