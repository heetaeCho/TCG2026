// File: named_captures_walker_test_357.cc

#include <gtest/gtest.h>
#include <type_traits>
#include <map>
#include <string>

// Rely on the public interface only.
#include "re2/regexp.h"

namespace {

// Fixture kept minimal—no peeking into internals.
class NamedCapturesWalkerTest_357 : public ::testing::Test {};

}  // namespace

// Verifies the type is constructible and destructible without accessing internals.
TEST(NamedCapturesWalkerTest_357, DefaultConstructibleAndDestructible_357) {
  re2::NamedCapturesWalker walker;  // Should construct and destroy cleanly.
  SUCCEED();
}

// Compile-time interface/contract checks (no runtime assumptions).
TEST(NamedCapturesWalkerTest_357, MethodSignatures_And_ReturnTypes_357) {
  using Walker = re2::NamedCapturesWalker;

  // TakeMap() must return a pointer to std::map<std::string,int>.
  static_assert(std::is_same<decltype(std::declval<Walker>().TakeMap()),
                             std::map<std::string, int>*>::value,
                "TakeMap() return type must be std::map<std::string,int>*");

  // PreVisit signature and return type.
  // We only check the signature and return type at compile-time.
  using PreVisitRet = decltype(std::declval<Walker>().PreVisit(
      static_cast<re2::Regexp*>(nullptr),
      re2::Ignored{},                   // second parameter type
      static_cast<bool*>(nullptr)));    // third parameter type
  static_assert(std::is_same<PreVisitRet, re2::Ignored>::value,
                "PreVisit must return re2::Ignored");

  // ShortVisit signature and return type.
  using ShortVisitRet = decltype(std::declval<Walker>().ShortVisit(
      static_cast<re2::Regexp*>(nullptr),
      re2::Ignored{}));
  static_assert(std::is_same<ShortVisitRet, re2::Ignored>::value,
                "ShortVisit must return re2::Ignored");

  SUCCEED();
}

// Copying and copy-assignment are explicitly deleted per interface; verify via traits.
TEST(NamedCapturesWalkerTest_357, DeletedCopyAndAssign_357) {
  using Walker = re2::NamedCapturesWalker;
  EXPECT_FALSE(std::is_copy_constructible<Walker>::value);
  EXPECT_FALSE(std::is_copy_assignable<Walker>::value);
}

// Ownership transfer through TakeMap(): after taking the map, destroying the walker
// should be safe (no double-delete). We do not assume the map is populated.
TEST(NamedCapturesWalkerTest_357, TakeMap_TransfersOwnership_AndDestructorSafe_357) {
  std::unique_ptr<std::map<std::string, int>> taken;

  {
    re2::NamedCapturesWalker walker;
    // Take ownership of any internal map (may be nullptr); we don't assume contents.
    taken.reset(walker.TakeMap());

    // If non-null, verify the returned map is usable by the caller.
    if (taken) {
      (*taken)["key"] = 42;
      EXPECT_EQ((*taken)["key"], 42);
    }
    // walker goes out of scope here; test passes if no crash/double free occurs.
  }

  // If we received a non-null map, it is owned solely by 'taken' now.
  // Destructor of 'taken' (at end of test) should also be safe.
  SUCCEED();
}
