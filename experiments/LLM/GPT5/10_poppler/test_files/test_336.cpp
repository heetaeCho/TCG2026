// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for LinkResetForm (Poppler)
// File: LinkResetForm_test_336.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler headers (project local)
#include "poppler/Link.h"
#include "poppler/Object.h"  // for Object::initNull() (commonly available in Poppler)

namespace {

class LinkResetFormTest_336 : public ::testing::Test {
protected:
  static Object MakeNullObject() {
    Object o;
    // Poppler Object typically supports initNull(); treat as black-box dependency creation.
    o.initNull();
    return o;
  }
};

TEST_F(LinkResetFormTest_336, GetFields_ReturnTypeIsConstVectorRef_336) {
  using Ret = decltype(std::declval<const LinkResetForm&>().getFields());
  static_assert(std::is_same_v<Ret, const std::vector<std::string>&>,
                "LinkResetForm::getFields() must return const std::vector<std::string>&");
  SUCCEED();
}

TEST_F(LinkResetFormTest_336, GetFields_CanBeCalledOnConstObject_336) {
  Object nameObj = MakeNullObject();
  LinkResetForm action(&nameObj);

  const LinkResetForm& cref = action;

  EXPECT_NO_THROW({
    const auto& fields = cref.getFields();
    // Observable behavior: should be safe to query.
    (void)fields.size();
  });
}

TEST_F(LinkResetFormTest_336, GetFields_ReturnsStableReferenceAcrossCalls_336) {
  Object nameObj = MakeNullObject();
  LinkResetForm action(&nameObj);

  const auto& fields1 = action.getFields();
  const auto& fields2 = action.getFields();

  // Since API returns a const reference, repeated calls should refer to the same object.
  EXPECT_EQ(&fields1, &fields2);
}

TEST_F(LinkResetFormTest_336, GetFields_AllowsSafeIterationEvenIfEmpty_336) {
  Object nameObj = MakeNullObject();
  LinkResetForm action(&nameObj);

  EXPECT_NO_THROW({
    const auto& fields = action.getFields();
    for (const auto& s : fields) {
      // No assumptions about content; just ensure iterating is safe.
      (void)s.size();
    }
  });
}

}  // namespace