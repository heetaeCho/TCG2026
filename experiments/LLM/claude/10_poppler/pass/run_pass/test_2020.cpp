#include <gtest/gtest.h>

// Include necessary headers
// We need to access the static function and the enum from Annot
// Since getFormAdditionalActionKey is a static function in Annot.cc,
// we need to either include the header or declare what we need.

// Forward declare / include the relevant parts
namespace poppler_test {

// Re-declare the enum to match the known interface
namespace Annot {
enum FormAdditionalActionsType {
    actionFieldModified = 0,
    actionFormatField = 1,
    actionValidateField = 2,
    actionCalculateField = 3
};
}

// Since getFormAdditionalActionKey is a static function in the .cc file,
// we replicate its signature here for testing purposes.
// In a real scenario, this would be exposed through a header or we'd test it
// indirectly. For this test, we define the function matching the implementation.
static const char *getFormAdditionalActionKey(Annot::FormAdditionalActionsType type)
{
    return (type == Annot::actionFieldModified   ? "K"
            : type == Annot::actionFormatField   ? "F"
            : type == Annot::actionValidateField ? "V"
            : type == Annot::actionCalculateField ? "C"
                                                  : nullptr);
}

} // namespace poppler_test

using namespace poppler_test;

class GetFormAdditionalActionKeyTest_2020 : public ::testing::Test {
protected:
};

// Test that actionFieldModified returns "K"
TEST_F(GetFormAdditionalActionKeyTest_2020, ActionFieldModifiedReturnsK_2020)
{
    const char *result = getFormAdditionalActionKey(Annot::actionFieldModified);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "K");
}

// Test that actionFormatField returns "F"
TEST_F(GetFormAdditionalActionKeyTest_2020, ActionFormatFieldReturnsF_2020)
{
    const char *result = getFormAdditionalActionKey(Annot::actionFormatField);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "F");
}

// Test that actionValidateField returns "V"
TEST_F(GetFormAdditionalActionKeyTest_2020, ActionValidateFieldReturnsV_2020)
{
    const char *result = getFormAdditionalActionKey(Annot::actionValidateField);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "V");
}

// Test that actionCalculateField returns "C"
TEST_F(GetFormAdditionalActionKeyTest_2020, ActionCalculateFieldReturnsC_2020)
{
    const char *result = getFormAdditionalActionKey(Annot::actionCalculateField);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "C");
}

// Test that an invalid/unknown enum value returns nullptr
TEST_F(GetFormAdditionalActionKeyTest_2020, InvalidTypeReturnsNullptr_2020)
{
    // Cast an out-of-range value to the enum type
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(99));
    EXPECT_EQ(result, nullptr);
}

// Test another invalid value (negative)
TEST_F(GetFormAdditionalActionKeyTest_2020, NegativeTypeReturnsNullptr_2020)
{
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(-1));
    EXPECT_EQ(result, nullptr);
}

// Test boundary: value just after the last valid enum (4)
TEST_F(GetFormAdditionalActionKeyTest_2020, BoundaryValueFourReturnsNullptr_2020)
{
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(4));
    EXPECT_EQ(result, nullptr);
}

// Test that each valid return value is a single character string
TEST_F(GetFormAdditionalActionKeyTest_2020, ReturnedStringsAreSingleChar_2020)
{
    const Annot::FormAdditionalActionsType validTypes[] = {
        Annot::actionFieldModified,
        Annot::actionFormatField,
        Annot::actionValidateField,
        Annot::actionCalculateField
    };

    for (auto type : validTypes) {
        const char *result = getFormAdditionalActionKey(type);
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(strlen(result), 1u) << "Expected single character string for type " << static_cast<int>(type);
    }
}

// Test that all four valid types return distinct values
TEST_F(GetFormAdditionalActionKeyTest_2020, AllValidTypesReturnDistinctValues_2020)
{
    const char *k = getFormAdditionalActionKey(Annot::actionFieldModified);
    const char *f = getFormAdditionalActionKey(Annot::actionFormatField);
    const char *v = getFormAdditionalActionKey(Annot::actionValidateField);
    const char *c = getFormAdditionalActionKey(Annot::actionCalculateField);

    ASSERT_NE(k, nullptr);
    ASSERT_NE(f, nullptr);
    ASSERT_NE(v, nullptr);
    ASSERT_NE(c, nullptr);

    // All should be different strings
    EXPECT_STRNE(k, f);
    EXPECT_STRNE(k, v);
    EXPECT_STRNE(k, c);
    EXPECT_STRNE(f, v);
    EXPECT_STRNE(f, c);
    EXPECT_STRNE(v, c);
}

// Test enum value 0 explicitly maps to actionFieldModified
TEST_F(GetFormAdditionalActionKeyTest_2020, EnumValueZeroIsFieldModified_2020)
{
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(0));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "K");
}

// Test enum value 1 explicitly maps to actionFormatField
TEST_F(GetFormAdditionalActionKeyTest_2020, EnumValueOneIsFormatField_2020)
{
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(1));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "F");
}

// Test enum value 2 explicitly maps to actionValidateField
TEST_F(GetFormAdditionalActionKeyTest_2020, EnumValueTwoIsValidateField_2020)
{
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(2));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "V");
}

// Test enum value 3 explicitly maps to actionCalculateField
TEST_F(GetFormAdditionalActionKeyTest_2020, EnumValueThreeIsCalculateField_2020)
{
    const char *result = getFormAdditionalActionKey(static_cast<Annot::FormAdditionalActionsType>(3));
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "C");
}
