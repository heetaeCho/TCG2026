// ObjectArrayCtorTest_2751.cpp
#include <gtest/gtest.h>

#include "poppler/Object.h"
#include "poppler/Array.h"

#include <type_traits>

namespace {

class ObjectArrayCtorTest_2751 : public ::testing::Test {};

// Compile-time interface/boundary checks (observable at compile time).
TEST_F(ObjectArrayCtorTest_2751, TypeTraits_CopyIsDeleted_MoveIsAllowed_2751) {
  static_assert(!std::is_copy_constructible_v<Object>,
                "Object should not be copy-constructible (copy ctor is deleted).");
  static_assert(!std::is_copy_assignable_v<Object>,
                "Object should not be copy-assignable (copy assignment is deleted).");

  static_assert(std::is_move_constructible_v<Object>,
                "Object should be move-constructible.");
  static_assert(std::is_move_assignable_v<Object>,
                "Object should be move-assignable.");
}

TEST_F(ObjectArrayCtorTest_2751, ConstructWithNonNullArray_SetsArrayTypeAndPointer_2751) {
  // Array takes an XRef*; use nullptr unless the real implementation requires a valid XRef.
  Array arr(nullptr);

  Object obj(&arr);

  EXPECT_EQ(obj.getType(), objArray);
  EXPECT_TRUE(obj.isArray());
  EXPECT_FALSE(obj.isDict());
  EXPECT_FALSE(obj.isStream());
  EXPECT_EQ(obj.getArray(), &arr);
}

TEST_F(ObjectArrayCtorTest_2751, ConstructWithNonNullArray_TypeNameIsNonNullAndNonEmpty_2751) {
  Array arr(nullptr);
  Object obj(&arr);

  const char *typeName = obj.getTypeName();
  ASSERT_NE(typeName, nullptr);
  EXPECT_NE(typeName[0], '\0');
}

#ifndef NDEBUG
TEST_F(ObjectArrayCtorTest_2751, ConstructWithNullArray_TriggersAssertDeath_2751) {
  // The provided implementation explicitly asserts(arrayA).
  ASSERT_DEATH(
      {
        Object obj(static_cast<Array *>(nullptr));
        (void)obj;
      },
      "");
}
#endif

} // namespace