// File: regexp_set_tmp_test_138.cc

#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "re2/regexp.h"

using re2::RegexpStatus;

class RegexpStatusTest_138 : public ::testing::Test {};

// [138] Boundary: accepts nullptr and remains usable
TEST_F(RegexpStatusTest_138, SetTmp_AllowsNullptr_138) {
  RegexpStatus s;
  // Should not crash/throw when setting nullptr
  s.set_tmp(nullptr);

  // Object should remain usable for other public methods that are noexcept/const-ish.
  // We only assert non-crash semantics here (no internal assumptions).
  SUCCEED();
}

// [138] Normal: setting a valid pointer should succeed (ownership is an internal detail)
TEST_F(RegexpStatusTest_138, SetTmp_WithValidStringPointer_138) {
  RegexpStatus s;
  // Dynamically allocate to match the signature (std::string*)
  std::string* p = new std::string("hello");
  s.set_tmp(p);

  // We do not delete p here, as ownership is assumed to transfer per interface intent.
  // Only observable requirement: call completes without crashing.
  SUCCEED();
}

// [138] Normal/Boundary: calling set_tmp multiple times with different pointers is safe
TEST_F(RegexpStatusTest_138, SetTmp_CanReplacePreviousPointer_138) {
  RegexpStatus s;

  std::string* first = new std::string("first");
  s.set_tmp(first);

  std::string* second = new std::string("second");
  // Replacing prior value should be safe and not crash.
  s.set_tmp(second);

  // No further observable behavior guaranteed; just verify it doesn't crash.
  SUCCEED();
}

// [138] Lifetime: object destruction after set_tmp should be safe
TEST_F(RegexpStatusTest_138, SetTmp_ObjectDestructionIsSafe_138) {
  {
    RegexpStatus s;
    std::string* p = new std::string("temp");
    s.set_tmp(p);
    // Scope ends; destructor runs. Test passes if no crash/UB is observed.
  }
  SUCCEED();
}

// [138] Independence: multiple instances manage their own temp pointers safely
TEST_F(RegexpStatusTest_138, SetTmp_MultipleInstancesIndependent_138) {
  RegexpStatus a;
  RegexpStatus b;

  std::string* pa = new std::string("A");
  std::string* pb = new std::string("B");

  a.set_tmp(pa);
  b.set_tmp(pb);

  // Replace one but not the other to ensure no cross-instance interference.
  std::string* pa2 = new std::string("A2");
  a.set_tmp(pa2);

  SUCCEED();
}
