#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace Annot {
    enum FormAdditionalActionsType { actionFieldModified = 0, actionFormatField = 1, actionValidateField = 2, actionCalculateField = 3 };
}

static const char *getFormAdditionalActionKey(Annot::FormAdditionalActionsType type) {
    return (type == Annot::actionFieldModified ? "K" :
            type == Annot::actionFormatField ? "F" :
            type == Annot::actionValidateField ? "V" :
            type == Annot::actionCalculateField ? "C" :
            nullptr);
}

TEST_F(GetFormAdditionalActionKeyTest_2020, ReturnsKForActionFieldModified_2020) {
    // Normal operation: Verifying if "K" is returned for actionFieldModified
    const char* result = getFormAdditionalActionKey(Annot::actionFieldModified);
    EXPECT_STREQ(result, "K");
}

TEST_F(GetFormAdditionalActionKeyTest_2020, ReturnsFForActionFormatField_2020) {
    // Normal operation: Verifying if "F" is returned for actionFormatField
    const char* result = getFormAdditionalActionKey(Annot::actionFormatField);
    EXPECT_STREQ(result, "F");
}

TEST_F(GetFormAdditionalActionKeyTest_2020, ReturnsVForActionValidateField_2020) {
    // Normal operation: Verifying if "V" is returned for actionValidateField
    const char* result = getFormAdditionalActionKey(Annot::actionValidateField);
    EXPECT_STREQ(result, "V");
}

TEST_F(GetFormAdditionalActionKeyTest_2020, ReturnsCForActionCalculateField_2020) {
    // Normal operation: Verifying if "C" is returned for actionCalculateField
    const char* result = getFormAdditionalActionKey(Annot::actionCalculateField);
    EXPECT_STREQ(result, "C");
}

TEST_F(GetFormAdditionalActionKeyTest_2020, ReturnsNullptrForUnknownAction_2020) {
    // Boundary case: Verifying if nullptr is returned for an unknown action
    const char* result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(999));
    EXPECT_EQ(result, nullptr);
}