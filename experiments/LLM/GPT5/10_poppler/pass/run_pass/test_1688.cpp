// StructElement_Attribute_setHidden_test_1688.cpp

#include <gtest/gtest.h>

#include "StructElement.h"

// These includes are common in Poppler-based test builds.
// If StructElement.h already includes them in your environment, these will be redundant but harmless.
#include "Object.h"
#include "goo/GooString.h"

namespace {

// Helper: create an Attribute instance using only public constructors.
// We avoid assuming anything about internal validation; we just provide a reasonable Object value.
static Attribute MakeAttributeForHiddenTests_1688() {
  Object obj;
  // Use the (GooString&& name, Object* value) constructor so we don't need Attribute::Type enum values.
  return Attribute(GooString("HiddenTestAttr"), &obj);
}

class AttributeTest_1688 : public ::testing::Test {};

}  // namespace

TEST_F(AttributeTest_1688, SetHiddenTrueMakesIsHiddenTrue_1688) {
  Attribute attr = MakeAttributeForHiddenTests_1688();

  attr.setHidden(true);

  EXPECT_TRUE(attr.isHidden());
}

TEST_F(AttributeTest_1688, SetHiddenFalseMakesIsHiddenFalse_1688) {
  Attribute attr = MakeAttributeForHiddenTests_1688();

  // First set true to ensure we observe a transition back to false through the public API.
  attr.setHidden(true);
  ASSERT_TRUE(attr.isHidden());

  attr.setHidden(false);

  EXPECT_FALSE(attr.isHidden());
}

TEST_F(AttributeTest_1688, SetHiddenIsIdempotentForTrue_1688) {
  Attribute attr = MakeAttributeForHiddenTests_1688();

  attr.setHidden(true);
  ASSERT_TRUE(attr.isHidden());

  // Re-applying the same value should keep the observable state consistent.
  attr.setHidden(true);

  EXPECT_TRUE(attr.isHidden());
}

TEST_F(AttributeTest_1688, SetHiddenIsIdempotentForFalse_1688) {
  Attribute attr = MakeAttributeForHiddenTests_1688();

  attr.setHidden(false);
  ASSERT_FALSE(attr.isHidden());

  // Re-applying the same value should keep the observable state consistent.
  attr.setHidden(false);

  EXPECT_FALSE(attr.isHidden());
}

TEST_F(AttributeTest_1688, SetHiddenCanToggleMultipleTimes_1688) {
  Attribute attr = MakeAttributeForHiddenTests_1688();

  attr.setHidden(false);
  EXPECT_FALSE(attr.isHidden());

  attr.setHidden(true);
  EXPECT_TRUE(attr.isHidden());

  attr.setHidden(false);
  EXPECT_FALSE(attr.isHidden());

  attr.setHidden(true);
  EXPECT_TRUE(attr.isHidden());
}

TEST_F(AttributeTest_1688, SetHiddenHandlesRepeatedAlternationBoundary_1688) {
  Attribute attr = MakeAttributeForHiddenTests_1688();

  // Boundary-style: many rapid changes; we only verify the final observable state.
  bool expected = false;
  for (int i = 0; i < 101; ++i) {
    expected = (i % 2 == 0);  // true on even iterations, false on odd
    attr.setHidden(expected);
  }

  EXPECT_EQ(attr.isHidden(), expected);
}