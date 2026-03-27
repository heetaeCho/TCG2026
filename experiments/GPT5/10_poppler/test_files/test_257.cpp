// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xref_isok_257.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "poppler/XRef.h"

// NOTE: These tests treat XRef as a black box and only verify behavior observable
// through the provided public interface (here: isOk()) and type properties.

namespace {

class XRefTest_257 : public ::testing::Test {};

TEST_F(XRefTest_257, IsOkReturnTypeIsBool_257) {
  static_assert(std::is_same_v<decltype(std::declval<const XRef&>().isOk()), bool>,
                "XRef::isOk() must return bool");
  SUCCEED();
}

TEST_F(XRefTest_257, CopyOperationsAreDeleted_257) {
  // Based on the provided interface: copy ctor and copy assignment are deleted.
  static_assert(!std::is_copy_constructible_v<XRef>, "XRef should not be copy constructible");
  static_assert(!std::is_copy_assignable_v<XRef>, "XRef should not be copy assignable");
  SUCCEED();
}

TEST_F(XRefTest_257, DefaultConstructAndCallIsOkDoesNotThrow_257) {
  XRef xref;
  EXPECT_NO_THROW({
    const bool ok = xref.isOk();
    (void)ok;
  });
}

TEST_F(XRefTest_257, IsOkCallableOnConstObject_257) {
  const XRef xref;
  EXPECT_NO_THROW({
    const bool ok = xref.isOk();
    (void)ok;
  });
}

TEST_F(XRefTest_257, RepeatedCallsAreStableForSameInstance_257) {
  XRef xref;

  // We don't assume whether it's true or false; we only check that calling isOk()
  // doesn't mutate observable state (i.e., the result remains consistent).
  const bool first = xref.isOk();
  const bool second = xref.isOk();
  const bool third = xref.isOk();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(XRefTest_257, WorksThroughPointerIndirection_257) {
  auto xref = std::make_unique<XRef>();

  EXPECT_NO_THROW({
    const bool ok1 = xref->isOk();
    const bool ok2 = xref->isOk();
    EXPECT_EQ(ok1, ok2);
  });
}

}  // namespace