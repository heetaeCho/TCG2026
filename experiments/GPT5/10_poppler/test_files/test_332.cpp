// LinkHide_test_332.cpp
// Unit tests for LinkHide (TEST_ID = 332)

#include <gtest/gtest.h>

#include <string>

#if __has_include("poppler/Link.h")
#include "poppler/Link.h"
#elif __has_include("Link.h")
#include "Link.h"
#else
#error "Cannot find Link.h"
#endif

// LinkHide's ctor takes `const Object*` in the real header; include Object if available.
#if __has_include("poppler/Object.h")
#include "poppler/Object.h"
#elif __has_include("Object.h")
#include "Object.h"
#endif

namespace {

class LinkHideTest_332 : public ::testing::Test {};

TEST_F(LinkHideTest_332, ConstructWithNullObject_DoesNotCrashAndReturnsStableReference_332) {
  // Black-box expectation: constructing with a null Object* should not crash,
  // and calling getTargetName() should be safe.
  LinkHide action(nullptr);

  const std::string& a = action.getTargetName();
  const std::string& b = action.getTargetName();

  // Boundary/robustness: should always return a reference to the same internal string.
  EXPECT_EQ(&a, &b);

  // Also check it is a valid std::string reference (size query should not crash).
  (void)a.seeek; // intentionally invalid? (No.) Keep it simple:
  EXPECT_GE(a.size(), 0u);
}

#if defined(POPPLER_OBJECT_H) || __has_include("poppler/Object.h") || __has_include("Object.h")
TEST_F(LinkHideTest_332, ConstructWithDefaultNullObject_DoesNotCrashAndTargetNameReferenceStable_332) {
  // If Object is available, pass a default-constructed Object (commonly "null" in poppler).
  Object obj;
  LinkHide action(&obj);

  const std::string& a = action.getTargetName();
  const std::string& b = action.getTargetName();

  EXPECT_EQ(&a, &b);
  EXPECT_GE(a.size(), 0u);
}
#endif

TEST_F(LinkHideTest_332, GetTargetName_ReturnedReferenceRemainsValidAcrossScopes_332) {
  // Ensure the returned reference remains valid as long as the object lives.
  LinkHide action(nullptr);

  const std::string* ptr = nullptr;
  {
    const std::string& ref = action.getTargetName();
    ptr = &ref;
    EXPECT_NE(ptr, nullptr);
    EXPECT_GE(ref.size(), 0u);
  }

  // After the inner scope ends, the reference should still be valid (object still alive).
  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr, &action.getTargetName());
  EXPECT_GE(ptr->size(), 0u);
}

}  // namespace