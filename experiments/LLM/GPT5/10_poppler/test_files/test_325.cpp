// LinkOCGState_test_325.cpp
#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkOCGStateTest_325 : public ::testing::Test {
protected:
  // Helper that just exercises methods without assuming any semantics.
  static void ExercisePublicApi(const LinkOCGState& action) {
    // All of these must be callable and return values of the right types.
    const bool ok1 = action.isOk();
    const bool ok2 = action.isOk();
    (void)ok1;
    (void)ok2;

    const auto kind1 = action.getKind();
    const auto kind2 = action.getKind();
    (void)kind1;
    (void)kind2;

    const auto& sl1 = action.getStateList();
    const auto& sl2 = action.getStateList();
    (void)sl1;
    (void)sl2;

    const bool prb1 = action.getPreserveRB();
    const bool prb2 = action.getPreserveRB();
    (void)prb1;
    (void)prb2;
  }
};

}  // namespace

// Normal operation: constructing with an Object pointer and calling all public methods.
TEST_F(LinkOCGStateTest_325, ConstructWithDefaultObject_AllPublicMethodsCallable_325) {
  Object obj;  // Default-constructed Object should be valid to pass as a pointer.
  EXPECT_NO_THROW({
    LinkOCGState action(&obj);
    ExercisePublicApi(action);
  });
}

// Boundary condition: nullptr input should not crash; API should remain callable if construction succeeds.
TEST_F(LinkOCGStateTest_325, ConstructWithNullptr_DoesNotThrow_325) {
  EXPECT_NO_THROW({
    LinkOCGState action(nullptr);
    ExercisePublicApi(action);
  });
}

// Boundary/consistency: repeated calls return stable results (no assumption about true/false, only consistency).
TEST_F(LinkOCGStateTest_325, RepeatedCalls_AreConsistentWithinInstance_325) {
  Object obj;
  LinkOCGState action(&obj);

  EXPECT_NO_THROW({
    const bool ok1 = action.isOk();
    const bool ok2 = action.isOk();
    EXPECT_EQ(ok1, ok2);

    const auto kind1 = action.getKind();
    const auto kind2 = action.getKind();
    EXPECT_EQ(kind1, kind2);

    const bool prb1 = action.getPreserveRB();
    const bool prb2 = action.getPreserveRB();
    EXPECT_EQ(prb1, prb2);
  });
}

// Boundary: getStateList returns a reference; reference identity should be stable across calls.
TEST_F(LinkOCGStateTest_325, GetStateList_ReturnsStableReference_325) {
  Object obj;
  LinkOCGState action(&obj);

  const auto* addr1 = &action.getStateList();
  const auto* addr2 = &action.getStateList();
  EXPECT_EQ(addr1, addr2);

  // Also ensure accessing size/iteration doesn't throw (without assuming contents).
  EXPECT_NO_THROW({
    (void)action.getStateList().size();
    for (const auto& entry : action.getStateList()) {
      (void)entry;
    }
  });
}

// Kind verification (observable): kind is a LinkActionKind value and should be stable; if actionOCGState exists,
// it should match (this is a narrow, interface-level expectation for this specific class).
TEST_F(LinkOCGStateTest_325, GetKind_IsOCGStateOrAtLeastStable_325) {
  Object obj;
  LinkOCGState action(&obj);

  const auto k = action.getKind();
  EXPECT_EQ(k, action.getKind());

#ifdef actionOCGState
  // Some builds expose the enum value as an unscoped enumerator.
  EXPECT_EQ(k, actionOCGState);
#endif

#ifdef LinkActionKind::actionOCGState
  // Some builds may use a scoped enum.
  EXPECT_EQ(k, LinkActionKind::actionOCGState);
#endif
}

// Exceptional/error case (observable): If constructed from an "empty/null-like" Object, isOk should still be callable
// and return a boolean (no assumption about true/false).
TEST_F(LinkOCGStateTest_325, IsOk_CallableEvenWithDefaultObject_325) {
  Object obj;
  LinkOCGState action(&obj);

  EXPECT_NO_THROW({
    const bool ok = action.isOk();
    (void)ok;
  });
}