// TEST_ID: 933
// File: form_getdefaultresources_test_933.cpp

#include <gtest/gtest.h>

#include "Form.h"

#include <type_traits>

namespace {

class FormTest_933 : public ::testing::Test {};

TEST_F(FormTest_933, FormIsNotCopyConstructible_933) {
  static_assert(!std::is_copy_constructible_v<Form>,
                "Form should not be copy constructible (copy ctor deleted).");
}

TEST_F(FormTest_933, FormIsNotCopyAssignable_933) {
  static_assert(!std::is_copy_assignable_v<Form>,
                "Form should not be copy assignable (copy assignment deleted).");
}

TEST_F(FormTest_933, GetDefaultResources_CanBeCalledOnConstObject_933) {
  Form form(nullptr);
  const Form& cform = form;

  // Observable behavior: method is callable and returns a pointer.
  EXPECT_NO_THROW({
    (void)cform.getDefaultResources();
  });
}

TEST_F(FormTest_933, GetDefaultResources_ReturnValueIsStableAcrossCalls_933) {
  Form form(nullptr);

  GfxResources* first = nullptr;
  GfxResources* second = nullptr;

  EXPECT_NO_THROW({
    first = form.getDefaultResources();
    second = form.getDefaultResources();
  });

  // Observable behavior: repeated calls should be consistent for a getter.
  EXPECT_EQ(first, second);
}

TEST_F(FormTest_933, GetDefaultResources_Boundary_NullDocConstruction_933) {
  // Boundary condition: construct Form with nullptr PDFDoc*.
  // We only verify the call is safe and yields a well-formed pointer value.
  Form form(nullptr);

  EXPECT_NO_THROW({
    GfxResources* res = form.getDefaultResources();
    (void)res;
  });
}

}  // namespace