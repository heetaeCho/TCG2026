// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for LinkResetForm::getExclude()
// TEST_ID: 337

#include <gtest/gtest.h>

#include "Link.h"

// Poppler's Object type lives in Object.h in most builds; LinkResetForm ctor takes `const Object*`.
// Include defensively if available in your build graph.
#include "Object.h"

#include <type_traits>

namespace {

// SFINAE helper: call obj.initNull() if that member exists (common in Poppler), otherwise no-op.
template <typename T>
auto InitNullIfPossible(T &obj, int) -> decltype(obj.initNull(), void()) {
    obj.initNull();
}
template <typename T>
void InitNullIfPossible(T &, ...) {}

// Build a minimal Object usable for passing as `nameObj` without assuming semantics.
Object MakeMinimalObject()
{
    Object obj;
    InitNullIfPossible(obj, 0);
    return obj;
}

} // namespace

class LinkResetFormTest_337 : public ::testing::Test {
protected:
    Object nameObj_ = MakeMinimalObject();
};

TEST_F(LinkResetFormTest_337, GetExclude_ReturnTypeIsBool_337)
{
    // Compile-time contract: getExclude() returns bool.
    static_assert(std::is_same_v<decltype(std::declval<const LinkResetForm &>().getExclude()), bool>,
                  "LinkResetForm::getExclude() must return bool");
    SUCCEED();
}

TEST_F(LinkResetFormTest_337, GetExclude_IsCallableOnConst_337)
{
    LinkResetForm action(&nameObj_);
    const LinkResetForm &cref = action;

    // Observable behavior: callable and returns a bool value.
    const bool v = cref.getExclude();
    (void)v;

    SUCCEED();
}

TEST_F(LinkResetFormTest_337, GetExclude_IsStableAcrossMultipleCalls_337)
{
    LinkResetForm action(&nameObj_);

    const bool first = action.getExclude();
    const bool second = action.getExclude();

    // Without mutating through the public interface, repeated calls should be consistent.
    EXPECT_EQ(first, second);
}

TEST_F(LinkResetFormTest_337, GetExclude_DoesNotRequireNonConstAccess_337)
{
    LinkResetForm action(&nameObj_);

    // Ensure we can call through a const pointer/reference path.
    const LinkResetForm *ptr = &action;
    const bool v = ptr->getExclude();
    (void)v;

    SUCCEED();
}