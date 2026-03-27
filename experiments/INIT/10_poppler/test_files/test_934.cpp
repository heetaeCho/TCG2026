// Form_getDefaultResourcesObj_ut_934.cpp

#include <gtest/gtest.h>

#include "poppler/Form.h"

namespace {

class FormTest_934 : public ::testing::Test {};

TEST_F(FormTest_934, GetDefaultResourcesObj_ReturnsNonNullPointer_934)
{
  Form form;
  Object *obj = form.getDefaultResourcesObj();
  EXPECT_NE(obj, nullptr);
}

TEST_F(FormTest_934, GetDefaultResourcesObj_ReturnsStablePointerAcrossCalls_934)
{
  Form form;
  Object *obj1 = form.getDefaultResourcesObj();
  Object *obj2 = form.getDefaultResourcesObj();

  EXPECT_NE(obj1, nullptr);
  EXPECT_EQ(obj1, obj2);
}

TEST_F(FormTest_934, GetDefaultResourcesObj_ReturnsDifferentPointersForDifferentInstances_934)
{
  Form form1;
  Form form2;

  Object *obj1 = form1.getDefaultResourcesObj();
  Object *obj2 = form2.getDefaultResourcesObj();

  EXPECT_NE(obj1, nullptr);
  EXPECT_NE(obj2, nullptr);

  // Boundary/instance-isolation expectation: each instance exposes its own Object.
  EXPECT_NE(obj1, obj2);
}

} // namespace