// LinkUnknown_test.cpp
// Unit tests for LinkUnknown (Poppler)
// Constraints respected: black-box testing via public interface only.

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

// Include the production header under test.
#include "poppler/Link.h"

// NOTE:
// - We only rely on the public interface shown in the prompt.
// - We do not inspect or depend on any private state.
// - Where enum values are not known, we only assert stability (same value across calls).

namespace {

class LinkUnknownTest_343 : public ::testing::Test {};

TEST_F(LinkUnknownTest_343, IsOkAlwaysTrue_343) {
  LinkUnknown u(std::string("any-action"));
  EXPECT_TRUE(u.isOk());
}

TEST_F(LinkUnknownTest_343, IsOkTrueForEmptyAction_343) {
  LinkUnknown u(std::string(""));
  EXPECT_TRUE(u.isOk());
}

TEST_F(LinkUnknownTest_343, GetActionReturnsExactStoredValue_343) {
  const std::string action = "GoToR(123)";
  LinkUnknown u(std::string(action));

  const std::string &ref = u.getAction();
  EXPECT_EQ(ref, action);
}

TEST_F(LinkUnknownTest_343, GetActionReferenceIsStableAcrossCalls_343) {
  LinkUnknown u(std::string("X"));

  const std::string *p1 = &u.getAction();
  const std::string *p2 = &u.getAction();

  // Observable behavior: same internal string object is returned by reference.
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(*p1, "X");
}

TEST_F(LinkUnknownTest_343, GetKindIsStableAcrossCalls_343) {
  LinkUnknown u(std::string("whatever"));

  const auto k1 = u.getKind();
  const auto k2 = u.getKind();

  EXPECT_EQ(k1, k2);
}

TEST_F(LinkUnknownTest_343, ConstructFromMovedStringPreservesContent_343) {
  std::string action = "moved-action";
  LinkUnknown u(std::move(action));

  // We do NOT assert anything about `action` after move (unspecified).
  EXPECT_EQ(u.getAction(), "moved-action");
  EXPECT_TRUE(u.isOk());
}

TEST_F(LinkUnknownTest_343, GetActionAllowsLongStrings_343) {
  std::string longAction(4096, 'a');
  longAction += "TAIL";

  LinkUnknown u(std::string(longAction));
  EXPECT_EQ(u.getAction(), longAction);
  EXPECT_TRUE(u.isOk());
}

TEST_F(LinkUnknownTest_343, PolymorphicDeleteViaBaseDoesNotCrash_343) {
  // This verifies the destructor is virtual/override-capable as declared,
  // and that deleting via base pointer is safe (observable: no crash).
  LinkAction *base = new LinkUnknown(std::string("delete-me"));
  EXPECT_TRUE(base->isOk());
  delete base;
  SUCCEED();
}

TEST_F(LinkUnknownTest_343, KindMatchesAcrossDifferentActions_343) {
  // Boundary/consistency: "unknown action" kind should not depend on action string.
  // We don't assume the enum value; we only compare outputs.
  LinkUnknown u1(std::string("A"));
  LinkUnknown u2(std::string("B"));
  LinkUnknown u3(std::string(""));

  EXPECT_EQ(u1.getKind(), u2.getKind());
  EXPECT_EQ(u2.getKind(), u3.getKind());
}

}  // namespace