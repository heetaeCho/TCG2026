// File: re2_error_tests_3.cc
#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Use the project's header
#include "re2/re2.h"

using re2::RE2;

class RE2ErrorTest_3 : public ::testing::Test {};

// ------------------------------------------------------------------
// Interface-level type properties
// ------------------------------------------------------------------

// Verifies that error() returns a const std::string& (reference type & const).
TEST_F(RE2ErrorTest_3, ErrorReturnsConstStringRef_3) {
  static_assert(std::is_same<const std::string&, decltype(std::declval<const RE2>().error())>::value,
                "RE2::error() must return const std::string& per interface");
  SUCCEED(); // Compile-time check is the key assertion here.
}

// ------------------------------------------------------------------
// Basic observable behavior (black-box): callable, reference stability
// ------------------------------------------------------------------

// Calling error() should not throw (black-box safety of accessor).
TEST_F(RE2ErrorTest_3, ErrorNoThrow_3) {
  RE2 re("dummy");  // Treat implementation as black box; we only call error()
  EXPECT_NO_THROW({
    (void)re.error();
  });
}

// The returned reference should be stable across multiple calls on the same object.
TEST_F(RE2ErrorTest_3, ErrorReferenceStableAcrossCalls_3) {
  RE2 re("anything");
  const std::string& first = re.error();
  const std::string& second = re.error();
  // Same object, same accessor -> reference identity should remain stable.
  EXPECT_EQ(&first, &second);
}

// The reference returned by error() should remain valid while the object is alive.
// (We only verify that repeated access is safe; we do NOT modify or rely on internals.)
TEST_F(RE2ErrorTest_3, ErrorRefAddressRemainsValidWhileAlive_3) {
  RE2 re("still-alive");
  const std::string* addr_initial = &re.error();
  // Access again and ensure address is unchanged (observable reference stability).
  const std::string* addr_again = &re.error();
  EXPECT_EQ(addr_initial, addr_again);
}
