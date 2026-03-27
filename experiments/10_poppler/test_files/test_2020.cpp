#include <gtest/gtest.h>

#include "Annot.h"



// Test fixture for Annot related tests with TEST_ID 2020

class AnnotTest_2020 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed in the future.

};



TEST_F(AnnotTest_2020, GetFormAdditionalActionKey_ReturnsCorrectStringForFieldModified_2020) {

    EXPECT_STREQ(getFormAdditionalActionKey(Annot::actionFieldModified), "K");

}



TEST_F(AnnotTest_2020, GetFormAdditionalActionKey_ReturnsCorrectStringForFormatField_2020) {

    EXPECT_STREQ(getFormAdditionalActionKey(Annot::actionFormatField), "F");

}



TEST_F(AnnotTest_2020, GetFormAdditionalActionKey_ReturnsCorrectStringForValidateField_2020) {

    EXPECT_STREQ(getFormAdditionalActionKey(Annot::actionValidateField), "V");

}



TEST_F(AnnotTest_2020, GetFormAdditionalActionKey_ReturnsCorrectStringForCalculateField_2020) {

    EXPECT_STREQ(getFormAdditionalActionKey(Annot::actionCalculateField), "C");

}



TEST_F(AnnotTest_2020, GetFormAdditionalActionKey_ReturnsNullptrForUnknownType_2020) {

    // Assuming there are no other defined types, passing an invalid enum value.

    EXPECT_STREQ(getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(4)), nullptr);

}
