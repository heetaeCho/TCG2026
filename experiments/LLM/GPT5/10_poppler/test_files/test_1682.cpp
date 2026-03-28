// Attribute_getOwner_test_1682.cpp
#include <gtest/gtest.h>

#include "StructElement.h"
#include "Object.h"
#include "goo/GooString.h"

namespace {

class AttributeTest_1682 : public ::testing::Test {
protected:
  static Object MakeNullObject() {
    Object obj;
    obj.initNull();
    return obj;
  }
};

TEST_F(AttributeTest_1682, GetOwnerIsStableAcrossRepeatedCalls_1682) {
  Object obj = MakeNullObject();
  Attribute attr(GooString("TestAttribute"), &obj);

  const auto owner1 = attr.getOwner();
  const auto owner2 = attr.getOwner();

  EXPECT_EQ(owner1, owner2);
}

TEST_F(AttributeTest_1682, GetOwnerRemainsStableAfterNonOwnerMutations_1682) {
  Object obj = MakeNullObject();
  Attribute attr(GooString("AnotherAttribute"), &obj);

  const auto before = attr.getOwner();

  // Mutations observable through public interface (should not affect owner).
  attr.setRevision(0u);
  attr.setHidden(false);

  GooString formatted("formatted-value");
  attr.setFormattedValue(&formatted);

  attr.setRevision(std::numeric_limits<unsigned int>::max());
  attr.setHidden(true);

  const auto after = attr.getOwner();
  EXPECT_EQ(before, after);

  // Idempotence check after mutations
  EXPECT_EQ(after, attr.getOwner());
}

TEST_F(AttributeTest_1682, GetOwnerWorksWithEmptyNameBoundary_1682) {
  Object obj = MakeNullObject();
  Attribute attr(GooString(""), &obj);

  const auto owner1 = attr.getOwner();
  const auto owner2 = attr.getOwner();

  EXPECT_EQ(owner1, owner2);
}

TEST_F(AttributeTest_1682, GetOwnerCallableEvenWithNullValuePointer_1682) {
  // Boundary / potential error-case: nullptr value pointer.
  Attribute attr(GooString("NullValuePtr"), /*value=*/nullptr);

  const auto owner1 = attr.getOwner();
  const auto owner2 = attr.getOwner();

  EXPECT_EQ(owner1, owner2);

  // If the implementation exposes validity via isOk(), it should be safe to call.
  // (No assumptions about true/false.)
  (void)attr.isOk();
}

} // namespace