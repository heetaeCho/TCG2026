// File: session_cli_tests_454.cpp

#include <gtest/gtest.h>
#include "catch2/catch_session.hpp"  // Provided interface

// For type checks without instantiating:
// If your project uses a different include path, adjust accordingly.
#include <type_traits>

using Catch::Session;

namespace {

// A simple test suite name; every test ends with _454 per requirement.
class SessionCliTest_454 : public ::testing::Test {};

} // namespace

// Verifies at compile-time that cli() returns a const reference (no mutation allowed through it).
TEST_F(SessionCliTest_454, ReturnsConstReference_454) {
  static_assert(std::is_same<
                    decltype(std::declval<const Session&>().cli()),
                    const Clara::Parser&
                >::value,
                "Session::cli() must return const Clara::Parser&");
  SUCCEED(); // If it compiles, the assertion holds.
}

// Verifies that multiple calls return a reference to the same underlying object
// (observable via reference identity). This does not assume what that object is.
TEST_F(SessionCliTest_454, ReferenceStableAcrossCalls_454) {
  Session s;
  const Clara::Parser& ref1 = s.cli();
  const Clara::Parser& ref2 = s.cli();
  EXPECT_EQ(&ref1, &ref2);
}

// Verifies that cli() is callable on a const Session object and yields a usable const reference.
TEST_F(SessionCliTest_454, CallableOnConstObject_454) {
  Session s;
  const Session& cs = s;        // simulate const context
  const Clara::Parser& ref = cs.cli();
  (void)ref;                    // only checking access; no mutation possible
  SUCCEED();
}

// Verifies that a previously obtained reference remains valid as long as the Session is alive.
// (We don’t assume anything about internal mutations; we only check address stability across calls.)
TEST_F(SessionCliTest_454, ReferenceRemainsValidWhileSessionAlive_454) {
  Session s;
  const Clara::Parser* p_before = &s.cli();
  ASSERT_NE(p_before, nullptr);

  // Re-access the reference; should still point to the same underlying object.
  const Clara::Parser* p_after = &s.cli();
  EXPECT_EQ(p_before, p_after);
}
