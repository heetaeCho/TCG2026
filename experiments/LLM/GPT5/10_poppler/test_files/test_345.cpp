// LinkUnknown_tests.cpp
// Unit tests for LinkUnknown (Poppler)
// TEST_ID = 345
//
// Constraints honored:
// - Black-box tests using only the public interface.
// - No access to private state.
// - No re-implementation/inference of internal logic beyond observable behavior.
// - GoogleMock not needed here (no external collaborators exposed by the interface).

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "Link.h"

// If Poppler exposes an enum name for LinkUnknown kind, we can verify it directly.
// If not available in this build, fall back to a weaker but still valid observable check.
#if defined(POPPLER_HAS_LINKACTIONKIND_UNKNOWN)
#define HAS_LINKACTIONKIND_UNKNOWN 1
#else
#define HAS_LINKACTIONKIND_UNKNOWN 0
#endif

namespace {

class LinkUnknownTest_345 : public ::testing::Test {};

TEST_F(LinkUnknownTest_345, ConstructorAcceptsRvalueStringAndGetActionMatches_345) {
  std::string s = "SomeAction";
  LinkUnknown u(std::move(s));

  EXPECT_EQ(u.getAction(), "SomeAction");
}

TEST_F(LinkUnknownTest_345, ConstructorAcceptsEmptyStringAndGetActionIsEmpty_345) {
  LinkUnknown u(std::string{});

  EXPECT_TRUE(u.getAction().empty());
  EXPECT_EQ(u.getAction(), "");
}

TEST_F(LinkUnknownTest_345, GetActionReturnsStableReferenceAcrossCalls_345) {
  LinkUnknown u(std::string("A"));

  const std::string& r1 = u.getAction();
  const std::string& r2 = u.getAction();

  // Observable: API promises a const reference. Repeated calls should refer to the same stored string.
  EXPECT_EQ(&r1, &r2);
  EXPECT_EQ(r1, "A");
  EXPECT_EQ(r2, "A");
}

TEST_F(LinkUnknownTest_345, GetActionDoesNotChangeAfterOtherCalls_345) {
  LinkUnknown u(std::string("KeepMe"));

  // Call other public methods and ensure action stays the same (black-box invariant check).
  (void)u.isOk();
  (void)u.getKind();

  EXPECT_EQ(u.getAction(), "KeepMe");
}

TEST_F(LinkUnknownTest_345, GetKindReturnsConsistentValueAcrossCalls_345) {
  LinkUnknown u(std::string("K"));

  const auto k1 = u.getKind();
  const auto k2 = u.getKind();

  EXPECT_EQ(k1, k2);
}

TEST_F(LinkUnknownTest_345, IsOkIsStableAcrossCalls_345) {
  LinkUnknown u(std::string("anything"));

  const bool ok1 = u.isOk();
  const bool ok2 = u.isOk();

  EXPECT_EQ(ok1, ok2);
}

TEST_F(LinkUnknownTest_345, BoundaryLargeActionStringGetActionMatches_345) {
  // Boundary: large but reasonable string size to exercise storage/return path.
  std::string big(1 << 16, 'x');  // 65536 chars
  const std::string expected = big;

  LinkUnknown u(std::move(big));
  EXPECT_EQ(u.getAction().size(), expected.size());
  EXPECT_EQ(u.getAction(), expected);
}

TEST_F(LinkUnknownTest_345, GetActionIsConstAndNonModifiableViaInterface_345) {
  LinkUnknown u(std::string("ConstRef"));

  // Compile-time observable property: getAction returns const std::string&
  static_assert(std::is_same_v<decltype(u.getAction()), const std::string&>,
                "getAction() must return const std::string&");

  // And the returned reference must be to const.
  static_assert(std::is_const_v<std::remove_reference_t<decltype(u.getAction())>>,
                "getAction() must return reference-to-const");
}

}  // namespace