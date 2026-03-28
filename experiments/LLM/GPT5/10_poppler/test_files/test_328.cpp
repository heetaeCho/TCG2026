// File: test_link_ocg_state_328.cpp
// TEST_ID = 328

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/Link.h"

// NOTE:
// The provided interface snippet only exposes: `bool LinkOCGState::getPreserveRB() const`.
// The full class (per the prompt) has a non-trivial constructor taking `const Object*` and
// private state, so these tests avoid instantiation and instead verify observable properties
// available purely from the public interface (type/signature/const-callability).

namespace {

using ExposedGetterSig = bool (LinkOCGState::*)() const;

} // namespace

TEST(LinkOCGStateTest_328, GetPreserveRB_HasExpectedMemberFunctionSignature_328)
{
    // Verifies the getter exists with the expected signature: bool () const
    ExposedGetterSig fn = &LinkOCGState::getPreserveRB;
    (void)fn;
    SUCCEED();
}

TEST(LinkOCGStateTest_328, GetPreserveRB_ReturnTypeIsBool_328)
{
    // Verifies the return type is exactly bool when called on a const instance.
    static_assert(std::is_same_v<decltype(std::declval<const LinkOCGState&>().getPreserveRB()), bool>,
                  "LinkOCGState::getPreserveRB() must return bool");
    SUCCEED();
}

TEST(LinkOCGStateTest_328, GetPreserveRB_IsCallableOnConstReference_328)
{
    // Boundary/const-correctness check: callable on const reference (no instantiation required).
    using RetT = decltype(std::declval<const LinkOCGState&>().getPreserveRB());
    static_assert(std::is_same_v<RetT, bool>, "Expected callable on const object returning bool");
    SUCCEED();
}