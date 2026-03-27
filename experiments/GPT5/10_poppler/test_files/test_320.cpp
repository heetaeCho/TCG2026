// LinkSound_getMix_test_320.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Link.h" // from ./TestProjects/poppler/poppler/Link.h

namespace {

TEST(LinkSoundTest_320, GetMix_IsConstMemberFunction_320)
{
    // Verify signature: bool (LinkSound::*)() const
    using Expected = bool (LinkSound::*)() const;
    Expected pmf = &LinkSound::getMix;
    (void)pmf;
}

TEST(LinkSoundTest_320, GetMix_ReturnTypeIsBool_320)
{
    // Verify return type is exactly bool (not implicitly convertible).
    using Ret = decltype(std::declval<const LinkSound &>().getMix());
    static_assert(std::is_same_v<Ret, bool>, "LinkSound::getMix() must return bool");
    SUCCEED();
}

TEST(LinkSoundTest_320, GetMix_CanBeCalledOnConstReference_320)
{
    // This test intentionally avoids constructing LinkSound (ctor not part of the provided interface snippet).
    // It verifies that the expression is well-formed for a const object.
    [[maybe_unused]] bool v = std::declval<const LinkSound &>().getMix();
    SUCCEED();
}

} // namespace