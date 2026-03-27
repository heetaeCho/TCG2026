// LinkUnknown_tests.cpp
// Unit tests for LinkUnknown (Poppler)
// TEST_ID: 344

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

// Poppler header under test
#include "poppler/Link.h"

// These tests are intentionally minimal/black-box:
// we only assert behavior observable via the public interface.

namespace {

class LinkUnknownTest_344 : public ::testing::Test {};

TEST_F(LinkUnknownTest_344, KindIsActionUnknown_344) {
  LinkUnknown a(std::string("SomeCustomAction"));
  EXPECT_EQ(a.getKind(), actionUnknown);
}

TEST_F(LinkUnknownTest_344, GetActionReturnsSameStringContent_344) {
  const std::string expected = "MyActionName";
  LinkUnknown a(std::string(expected));

  // Observable behavior: getAction() returns a const ref to the stored action string.
  EXPECT_EQ(a.getAction(), expected);
}

TEST_F(LinkUnknownTest_344, GetActionReferenceIsStableAcrossCalls_344) {
  LinkUnknown a(std::string("StableRef"));

  const std::string* p1 = &a.getAction();
  const std::string* p2 = &a.getAction();

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(*p1, "StableRef");
}

TEST_F(LinkUnknownTest_344, IsOkIsCallableAndStableAcrossCalls_344) {
  LinkUnknown a(std::string("Anything"));

  // We do not infer what "ok" means; we only verify callability and stability for same object state.
  const bool first = a.isOk();
  const bool second = a.isOk();
  EXPECT_EQ(first, second);
}

TEST_F(LinkUnknownTest_344, EmptyActionIsHandled_344) {
  LinkUnknown a(std::string(""));

  EXPECT_EQ(a.getKind(), actionUnknown);
  EXPECT_EQ(a.getAction(), "");
  (void)a.isOk();  // Should be callable even for empty action.
}

TEST_F(LinkUnknownTest_344, VeryLongActionIsHandled_344) {
  std::string longAction(64 * 1024, 'x');  // 64 KiB string
  LinkUnknown a(std::move(longAction));

  EXPECT_EQ(a.getKind(), actionUnknown);
  EXPECT_EQ(a.getAction().size(), 64u * 1024u);
  EXPECT_EQ(a.getAction().front(), 'x');
  EXPECT_EQ(a.getAction().back(), 'x');
}

TEST_F(LinkUnknownTest_344, CanBeUsedViaBasePointerAndVirtualDispatchWorks_344) {
  LinkUnknown derived(std::string("BaseDispatch"));

  // If LinkUnknown derives from LinkAction as declared, virtual dispatch should work.
  LinkAction* base = &derived;
  EXPECT_EQ(base->getKind(), actionUnknown);

  // isOk() is virtual per declaration; verify it is callable through base.
  (void)base->isOk();
}

TEST_F(LinkUnknownTest_344, ConstObjectSupportsConstMethods_344) {
  const LinkUnknown a(std::string("ConstOk"));

  EXPECT_EQ(a.getKind(), actionUnknown);
  EXPECT_EQ(a.getAction(), "ConstOk");
  (void)a.isOk();
}

// "Exceptional / error cases (if observable)".
// We don't know if constructor can throw; but we can still check that moving an empty string works
// and that no interface call triggers exceptions for basic usage.
TEST_F(LinkUnknownTest_344, NoThrowOnBasicQueriesAfterConstruction_344) {
  LinkUnknown a(std::string("QueryNoThrow"));

  EXPECT_NO_THROW({ (void)a.getKind(); });
  EXPECT_NO_THROW({ (void)a.isOk(); });
  EXPECT_NO_THROW({ (void)a.getAction(); });
}

// Compile-time boundary: ensure return types match the interface we rely on.
TEST_F(LinkUnknownTest_344, SignatureSanityChecks_344) {
  static_assert(std::is_same_v<decltype(std::declval<const LinkUnknown&>().getKind()), LinkActionKind>,
                "getKind() should return LinkActionKind");
  static_assert(std::is_same_v<decltype(std::declval<const LinkUnknown&>().getAction()), const std::string&>,
                "getAction() should return const std::string&");
  static_assert(std::is_same_v<decltype(std::declval<const LinkUnknown&>().isOk()), bool>,
                "isOk() should return bool");
}

}  // namespace