// File: ./TestProjects/re2/tests/compiler_nomatch_290_test.cc

#include "gtest/gtest.h"
#include <type_traits>
#include <vector>

// Include the partial implementation so the test can see the interface.
#include "../re2/compile.cc"  // path relative to this test file

namespace {

using re2::Compiler;

class CompilerNoMatchTest_290 : public ::testing::Test {
protected:
  Compiler c_;
};

// [Normal] Calling NoMatch() returns a value object that we can hold.
// Also verifies that a default-constructed object of the same type can be created.
TEST_F(CompilerNoMatchTest_290, NoMatch_ReturnsDefaultConstructible_290) {
  auto f = c_.NoMatch();           // Should compile and return a value
  (void)f;                         // Silence unused warning

  // Default-construct an object of the same type as NoMatch() returns.
  using FragT = decltype(f);
  FragT df{};                      // If this compiles, the type is default-constructible
  (void)df;

  SUCCEED();
}

// [Normal] Multiple calls should succeed and produce distinct objects that can
// be stored (copied/moved) into standard containers.
TEST_F(CompilerNoMatchTest_290, NoMatch_MultipleCalls_ContainerStoresTwoElements_290) {
  auto f1 = c_.NoMatch();
  auto f2 = c_.NoMatch();

  using FragT = decltype(f1);
  std::vector<FragT> vec;
  vec.push_back(f1);   // requires copy/move
  vec.push_back(f2);   // requires copy/move

  EXPECT_EQ(vec.size(), 2u);
}

// [Boundary/Type traits] The return type should be copy/move constructible/assignable.
// We do not assume internal details; we only check basic value semantics useful for callers.
TEST_F(CompilerNoMatchTest_290, NoMatch_ReturnType_HasBasicValueSemantics_290) {
  auto f = c_.NoMatch();
  using FragT = decltype(f);

  // Use EXPECT_* on the type traits (rather than static_assert) to keep failures as test failures.
  EXPECT_TRUE(std::is_default_constructible<FragT>::value);
  EXPECT_TRUE(std::is_copy_constructible<FragT>::value);
  EXPECT_TRUE(std::is_move_constructible<FragT>::value);
  EXPECT_TRUE(std::is_copy_assignable<FragT>::value);
  EXPECT_TRUE(std::is_move_assignable<FragT>::value);
}

// [Exceptional/Error case] There is no documented error channel in the interface for NoMatch().
// Still, ensure calling it does not throw (for environments with exceptions enabled).
TEST_F(CompilerNoMatchTest_290, NoMatch_DoesNotThrow_290) {
  EXPECT_NO_THROW({
    auto f = c_.NoMatch();
    (void)f;
  });
}

}  // namespace
