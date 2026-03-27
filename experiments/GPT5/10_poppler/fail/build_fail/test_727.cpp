// File: Page_getDuration_test_727.cpp
// TEST_ID: 727

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Adjust include path as needed for your build.
// Given: ./TestProjects/poppler/poppler/Page.h
#include "poppler/Page.h"

namespace {

using ::testing::Test;

// These tests are intentionally interface-only (compile-time) because the provided
// partial code exposes only Page::getDuration() and provides no safe/public way to
// construct a Page instance or set/observe duration via the public API.

TEST(PageTest_727, GetDuration_ReturnTypeIsDouble_727)
{
    // Verify the member exists and can have its address taken (not overloaded away).
    auto pmf = &Page::getDuration;
    (void)pmf;

    // Verify the declared return type is exactly double.
    static_assert(std::is_same_v<decltype(std::declval<const Page&>().getDuration()), double>,
                  "Page::getDuration() must return double");
    SUCCEED();
}

TEST(PageTest_727, GetDuration_IsConstCallable_727)
{
    // Must be callable on a const Page& and return double.
    static_assert(std::is_invocable_r_v<double, decltype(&Page::getDuration), const Page&>,
                  "Page::getDuration() must be invocable on const Page& and return double");

    // And (as a sanity check) it should also be callable on non-const as well.
    static_assert(std::is_invocable_r_v<double, decltype(&Page::getDuration), Page&>,
                  "Page::getDuration() must be invocable on Page& and return double");

    SUCCEED();
}

TEST(PageTest_727, GetDuration_IsMemberFunctionPointer_727)
{
    // Ensure we have the expected member-function-pointer category.
    using PMF = decltype(&Page::getDuration);
    static_assert(std::is_member_function_pointer_v<PMF>,
                  "&Page::getDuration must be a member function pointer");

    SUCCEED();
}

TEST(PageTest_727, GetDuration_CallExpressionIsWellFormed_727)
{
    // This test checks that the call expression is well-formed without constructing Page.
    // (Unevaluated context, no runtime behavior assumptions.)
    using Ret = decltype(std::declval<const Page&>().getDuration());
    static_assert(std::is_same_v<Ret, double>, "Call expression must yield double");

    SUCCEED();
}

} // namespace