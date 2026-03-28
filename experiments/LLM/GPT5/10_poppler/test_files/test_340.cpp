// LinkSubmitForm_getFields_340_test.cpp
//
// Unit tests for LinkSubmitForm::getFields()
// Constraints note: The provided interface does not expose a safe/portable way to
// construct a LinkSubmitForm instance (ctor needs `const Object*` and Object
// construction requirements are not given). Therefore, these tests focus on
// *observable interface guarantees* that can be validated at compile time
// (signatures / const-correctness / type properties) without inferring internal logic.

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Poppler header under test
#include "Link.h"

namespace {

// Helper to validate presence/signature via decltype without constructing the type.
template <typename T>
using GetFieldsExpr = decltype(std::declval<const T&>().getFields());

}  // namespace

// The TEST_ID is 340

TEST(LinkSubmitFormTest_340, GetFieldsExistsOnConstObject_340) {
  // This test will fail to compile if getFields() is not callable on const objects.
  (void)sizeof(GetFieldsExpr<LinkSubmitForm>);
  SUCCEED();
}

TEST(LinkSubmitFormTest_340, GetFieldsReturnTypeIsConstVectorStringRef_340) {
  using Ret = GetFieldsExpr<LinkSubmitForm>;
  static_assert(std::is_same_v<Ret, const std::vector<std::string>&>,
                "LinkSubmitForm::getFields() must return `const std::vector<std::string>&`");
  SUCCEED();
}

TEST(LinkSubmitFormTest_340, GetFieldsReturnIsLValueReference_340) {
  using Ret = GetFieldsExpr<LinkSubmitForm>;
  static_assert(std::is_lvalue_reference_v<Ret>,
                "LinkSubmitForm::getFields() should return an lvalue reference");
  SUCCEED();
}

TEST(LinkSubmitFormTest_340, GetFieldsReturnIsConstQualified_340) {
  using Ret = GetFieldsExpr<LinkSubmitForm>;
  static_assert(std::is_const_v<std::remove_reference_t<Ret>>,
                "LinkSubmitForm::getFields() should return a const-qualified reference");
  SUCCEED();
}

TEST(LinkSubmitFormTest_340, GetFieldsElementTypeIsStdString_340) {
  using Ret = GetFieldsExpr<LinkSubmitForm>;
  using Vec = std::remove_cv_t<std::remove_reference_t<Ret>>;
  static_assert(std::is_same_v<typename Vec::value_type, std::string>,
                "getFields() vector element type must be std::string");
  SUCCEED();
}

TEST(LinkSubmitFormTest_340, LinkSubmitFormIsCopyableOrMovableTypeTraitSmoke_340) {
  // Not asserting a specific policy; just ensuring the type participates in basic traits.
  // This helps catch accidental incomplete-type issues in the public header.
  const bool copyable = std::is_copy_constructible_v<LinkSubmitForm>;
  const bool movable = std::is_move_constructible_v<LinkSubmitForm>;
  EXPECT_TRUE(copyable || movable);
}