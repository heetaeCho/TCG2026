// TEST_ID: 908
// File: formfieldtext_noscroll_unittest.cpp

#include <gtest/gtest.h>

#include "Form.h" // from ./TestProjects/poppler/poppler/Form.h

namespace {

class FormFieldTextTest_908 : public ::testing::Test {};

TEST_F(FormFieldTextTest_908, ValueInitializedDefaultsToFalse_908)
{
    // Value-initialization is the safest way to construct a trivial/aggregate type without
    // assuming anything about uninitialized members.
    FormFieldText field{};
    EXPECT_FALSE(field.noScroll());
}

TEST_F(FormFieldTextTest_908, RepeatedCallsAreStable_908)
{
    FormFieldText field{};
    const bool first = field.noScroll();
    const bool second = field.noScroll();
    EXPECT_EQ(first, second);
}

TEST_F(FormFieldTextTest_908, CallableOnConstObjectAndReturnsBool_908)
{
    const FormFieldText field{};
    static_assert(std::is_same_v<decltype(field.noScroll()), bool>,
                  "FormFieldText::noScroll() must return bool");

    const bool v = field.noScroll();
    EXPECT_EQ(v, field.noScroll());
}

} // namespace