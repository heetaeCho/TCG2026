// TEST_ID: 329
// File: linkhide_test_329.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>

#include "Link.h" // LinkHide, LinkAction, LinkActionKind, Object (typically included by Link.h)

namespace {

// ---- Minimal, compile-friendly Object construction helpers (black-box friendly) ----
// We avoid assuming how Object is built/parsed. We only try to create a "null/empty" Object
// if the type supports it; otherwise we fall back to nullptr.

template <typename T, typename = void>
struct IsDefaultConstructible : std::false_type {};
template <typename T>
struct IsDefaultConstructible<T, std::void_t<decltype(T())>> : std::true_type {};

template <typename T, typename = void>
struct HasInitNull : std::false_type {};
template <typename T>
struct HasInitNull<T, std::void_t<decltype(std::declval<T&>().initNull())>> : std::true_type {};

template <typename T, typename = void>
struct HasSetToNull : std::false_type {};
template <typename T>
struct HasSetToNull<T, std::void_t<decltype(std::declval<T&>().setToNull())>> : std::true_type {};

std::unique_ptr<Object> MakeEmptyObjectIfPossible() {
  if constexpr (IsDefaultConstructible<Object>::value) {
    auto obj = std::make_unique<Object>();
    if constexpr (HasInitNull<Object>::value) {
      obj->initNull();
    } else if constexpr (HasSetToNull<Object>::value) {
      obj->setToNull();
    }
    return obj;
  } else {
    return nullptr;
  }
}

struct Snapshot {
  bool ok = false;
  bool hasTarget = false;
  bool show = false;
  std::string name;
  LinkActionKind kind{};
};

Snapshot TakeSnapshot(const LinkHide& a) {
  Snapshot s;
  s.ok = a.isOk();
  s.hasTarget = a.hasTargetName();
  s.show = a.isShowAction();
  s.name = a.getTargetName();
  s.kind = a.getKind();
  return s;
}

} // namespace

class LinkHideTest_329 : public ::testing::Test {};

// Normal / boundary: construction with nullptr should be safe and methods callable.
TEST_F(LinkHideTest_329, NullObject_IsCallableAndSelfConsistent_329) {
  LinkHide action(nullptr);

  // Call all observable methods to ensure they are safe to invoke.
  const auto snap1 = TakeSnapshot(action);
  const auto snap2 = TakeSnapshot(action);

  // Self-consistency: repeated observations should be stable for a const object.
  EXPECT_EQ(snap1.ok, snap2.ok);
  EXPECT_EQ(snap1.hasTarget, snap2.hasTarget);
  EXPECT_EQ(snap1.show, snap2.show);
  EXPECT_EQ(snap1.name, snap2.name);
  EXPECT_EQ(snap1.kind, snap2.kind);

  // Additional black-box invariant checks that don't assume specific values:
  // - getTargetName() returns a stable reference (at least across consecutive reads)
  const std::string& r1 = action.getTargetName();
  const std::string& r2 = action.getTargetName();
  EXPECT_EQ(&r1, &r2);
  EXPECT_EQ(r1, r2);
}

// Boundary: construction with an "empty/null" Object (when possible) should be safe and stable.
TEST_F(LinkHideTest_329, EmptyObject_IsCallableAndStable_329) {
  auto obj = MakeEmptyObjectIfPossible();
  if (!obj) {
    GTEST_SKIP() << "Object is not default-constructible in this build; skipping empty-object test.";
  }

  LinkHide action(obj.get());

  const auto snap1 = TakeSnapshot(action);
  const auto snap2 = TakeSnapshot(action);

  EXPECT_EQ(snap1.ok, snap2.ok);
  EXPECT_EQ(snap1.hasTarget, snap2.hasTarget);
  EXPECT_EQ(snap1.show, snap2.show);
  EXPECT_EQ(snap1.name, snap2.name);
  EXPECT_EQ(snap1.kind, snap2.kind);

  // Reference stability (do not assume contents).
  const std::string& n1 = action.getTargetName();
  const std::string& n2 = action.getTargetName();
  EXPECT_EQ(&n1, &n2);
}

// Normal: two instances built from the same input should behave equivalently.
TEST_F(LinkHideTest_329, SameInput_TwoInstancesHaveEquivalentObservations_329) {
  auto obj = MakeEmptyObjectIfPossible();
  const Object* p = obj ? obj.get() : nullptr;

  LinkHide a1(p);
  LinkHide a2(p);

  const auto s1 = TakeSnapshot(a1);
  const auto s2 = TakeSnapshot(a2);

  EXPECT_EQ(s1.ok, s2.ok);
  EXPECT_EQ(s1.hasTarget, s2.hasTarget);
  EXPECT_EQ(s1.show, s2.show);
  EXPECT_EQ(s1.name, s2.name);
  EXPECT_EQ(s1.kind, s2.kind);
}

// Exceptional / error-ish (observable): ensure API remains callable even if input object pointer is
// a valid pointer to a default-constructed object (distinct from nullptr), when possible.
TEST_F(LinkHideTest_329, DefaultConstructedObjectPointer_IsCallable_329) {
  auto obj = MakeEmptyObjectIfPossible();
  if (!obj) {
    GTEST_SKIP() << "Object is not default-constructible in this build; skipping default-object-pointer test.";
  }

  LinkHide action(obj.get());

  // Just ensure calls succeed and are stable; do not assert semantic outcomes.
  EXPECT_NO_THROW((void)action.isOk());
  EXPECT_NO_THROW((void)action.getKind());
  EXPECT_NO_THROW((void)action.hasTargetName());
  EXPECT_NO_THROW((void)action.getTargetName());
  EXPECT_NO_THROW((void)action.isShowAction());

  const auto s1 = TakeSnapshot(action);
  const auto s2 = TakeSnapshot(action);

  EXPECT_EQ(s1.ok, s2.ok);
  EXPECT_EQ(s1.hasTarget, s2.hasTarget);
  EXPECT_EQ(s1.show, s2.show);
  EXPECT_EQ(s1.name, s2.name);
  EXPECT_EQ(s1.kind, s2.kind);
}