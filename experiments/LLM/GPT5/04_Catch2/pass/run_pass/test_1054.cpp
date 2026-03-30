// File: tests/scoped_message_move_ctor_1054_tests.cpp

#include <gtest/gtest.h>
#include <type_traits>

// Include the public header that declares Catch::ScopedMessage.
// If your include path differs, adjust accordingly.
#include "catch2/catch_message.hpp"

namespace {

using Catch::ScopedMessage;

// -------------------------
// TEST SUITE
// -------------------------

// Verifies that ScopedMessage is move-constructible and the move ctor is noexcept.
// (This matches the observable interface: move ctor is declared/defined `noexcept`.)
TEST(ScopedMessageTest_1054, IsMoveConstructibleAndNoexcept_1054) {
    static_assert(std::is_move_constructible<ScopedMessage>::value,
                  "ScopedMessage must be move-constructible");
    static_assert(std::is_nothrow_move_constructible<ScopedMessage>::value,
                  "ScopedMessage move constructor should be noexcept");

    EXPECT_TRUE((std::is_move_constructible<ScopedMessage>::value));
    EXPECT_TRUE((std::is_nothrow_move_constructible<ScopedMessage>::value));
}

// Verifies that the copy constructor is deleted (i.e., not copy-constructible)
// based solely on the class interface.
TEST(ScopedMessageTest_1054, NotCopyConstructible_1054) {
    static_assert(!std::is_copy_constructible<ScopedMessage>::value,
                  "ScopedMessage copy constructor should be deleted");
    EXPECT_FALSE((std::is_copy_constructible<ScopedMessage>::value));
}

// Verifies that the type is constructible from an rvalue (move) but NOT from an lvalue (copy).
TEST(ScopedMessageTest_1054, ConstructibilityFromRvalueButNotLvalue_1054) {
    static_assert(std::is_constructible<ScopedMessage, ScopedMessage&&>::value,
                  "Should be constructible from rvalue (move)");
    static_assert(!std::is_constructible<ScopedMessage, ScopedMessage&>::value,
                  "Should NOT be constructible from lvalue (copy)");

    EXPECT_TRUE((std::is_constructible<ScopedMessage, ScopedMessage&&>::value));
    EXPECT_FALSE((std::is_constructible<ScopedMessage, ScopedMessage&>::value));
}

// If the header exposes `m_moved` as a public boolean (as shown in the provided interface),
// verify that it is present and of type bool. We only inspect its type via unevaluated context;
// no reliance on internal/private state or on constructing instances.
TEST(ScopedMessageTest_1054, PublicMovedFlagTypeIsBool_1054) {
    // This uses unevaluated context and does not instantiate an object.
    using MovedT = decltype(std::declval<ScopedMessage&>().m_moved);
    static_assert(std::is_same<MovedT, bool>::value,
                  "m_moved should be a public bool per the provided interface");
    EXPECT_TRUE((std::is_same<MovedT, bool>::value));
}

} // namespace
