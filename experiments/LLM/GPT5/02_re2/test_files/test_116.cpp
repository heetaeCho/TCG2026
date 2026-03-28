// File: prog_size_test_116.cc
#include "re2/prog.h"
#include <gtest/gtest.h>
#include <type_traits>

using re2::Prog;

// Fixture kept minimal for clarity and black-box testing discipline.
class ProgSizeTest_116 : public ::testing::Test {};

// [Normal operation] A default-constructed Prog should report a concrete size.
// We do not assume internal details beyond what is observable via the API.
TEST_F(ProgSizeTest_116, DefaultConstructed_SizeIsZero_116) {
  Prog p;
  // From the public interface, size() returns an int.
  // Observable expectation (per provided header behavior): default size is 0.
  EXPECT_EQ(p.size(), 0);
}

// [Consistency] size() should be stable/idempotent across repeated calls
// when no mutating API has been invoked.
TEST_F(ProgSizeTest_116, SizeIsIdempotentAcrossCalls_116) {
  Prog p;
  int first = p.size();
  int second = p.size();
  int third = p.size();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

// [Boundary-ish observation] Calling size() on a temporary should work and
// not produce UB or side effects visible via the return value.
TEST_F(ProgSizeTest_116, TemporaryObject_SizeQueryable_116) {
  // Just ensure the expression is valid and equals the default-observed value.
  EXPECT_EQ(Prog().size(), 0);
}

// [Interface-level property] Verify the return type is exactly int.
// This does not peek into internals and guards API stability.
TEST_F(ProgSizeTest_116, ReturnTypeIsInt_116) {
  static_assert(std::is_same<decltype(std::declval<Prog&>().size()), int>::value,
                "Prog::size() must return int");
  SUCCEED(); // Compile-time assertion is the real check.
}

// [Exceptional cases] Ensure size() does not throw when called.
// (We don't assert noexcept here, only observable behavior at runtime.)
TEST_F(ProgSizeTest_116, SizeDoesNotThrow_116) {
  Prog p;
  EXPECT_NO_THROW({
    (void)p.size();
  });
}
