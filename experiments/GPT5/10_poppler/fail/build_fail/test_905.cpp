// TEST_ID: 905
// File: formfieldtext_ispassword_unittest.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Form.h"

namespace {

// These tests intentionally avoid constructing FormFieldText, because the provided
// interface snippet does not expose a way to control or observe the `password`
// flag through public APIs in a reliable, black-box manner.
//
// Instead, we verify *observable interface properties*:
// - method exists
// - callable on const objects
// - returns bool
// - has the expected const-qualified member-function signature

TEST(FormFieldTextTest_905, IsPasswordHasConstMemberSignature_905)
{
    using T = FormFieldText;

    // Verifies the exact const-qualified member function type is available.
    bool (T::*pmf)() const = &T::isPassword;
    (void)pmf;

    SUCCEED();
}

TEST(FormFieldTextTest_905, IsPasswordReturnTypeIsBool_905)
{
    using T = FormFieldText;

    // Verifies it is callable on const instances and returns a bool by value.
    static_assert(std::is_same_v<decltype(std::declval<const T &>().isPassword()), bool>,
                  "FormFieldText::isPassword() must return bool and be callable on const objects");

    SUCCEED();
}

TEST(FormFieldTextTest_905, IsPasswordIsNotADataMember_905)
{
    using T = FormFieldText;

    // If this compiles as a pointer-to-member-function, it is not a data member.
    auto pmf = &T::isPassword;
    static_assert(std::is_member_function_pointer_v<decltype(pmf)>,
                  "FormFieldText::isPassword must be a member function");

    SUCCEED();
}

} // namespace