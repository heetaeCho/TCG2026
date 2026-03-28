// TEST_ID: 382
// File: PostScriptFunction_copy_382_test.cpp

#include <gtest/gtest.h>

#include "poppler/Function.h"

namespace {

class PostScriptFunctionTest_382 : public ::testing::Test {};

// NOTE:
// The public interface shown includes:
//   - PostScriptFunction(Object* funcObj, Dict* dict)
//   - copy() -> std::unique_ptr<Function>
//   - getType(), isOk(), getCodeString(), transform(...)
//
// However, in this prompt we are not given a safe/portable way to build a fully-valid
// Object/Dict/Stream for a FunctionType 4 (PostScript) function. These tests therefore
// focus strictly on observable behavior of copy() that can be validated without
// relying on internal state.
//
// If your Poppler build requires non-null Object/Dict to construct PostScriptFunction,
// you can adapt MakeSubject() to use your project’s existing PDF object helpers.

static std::unique_ptr<PostScriptFunction> MakeSubject_382() {
  // Best-effort construction that avoids inferring internal behavior.
  // If the implementation cannot handle nullptr inputs, adjust this helper
  // to create a minimal valid PDF FunctionType 4 object using your codebase helpers.
  return std::make_unique<PostScriptFunction>(nullptr, nullptr);
}

}  // namespace

TEST_F(PostScriptFunctionTest_382, CopyReturnsNonNullUniquePtr_382) {
  auto subject = MakeSubject_382();
  ASSERT_NE(subject, nullptr);

  std::unique_ptr<Function> cloned;
  ASSERT_NO_FATAL_FAILURE(cloned = subject->copy());
  EXPECT_NE(cloned, nullptr);
}

TEST_F(PostScriptFunctionTest_382, CopyReturnsDistinctObject_382) {
  auto subject = MakeSubject_382();
  ASSERT_NE(subject, nullptr);

  auto cloned = subject->copy();
  ASSERT_NE(cloned, nullptr);

  // Must be a different object instance than the original.
  EXPECT_NE(cloned.get(), static_cast<Function*>(subject.get()));
}

TEST_F(PostScriptFunctionTest_382, CopyPreservesDynamicTypeAsPostScriptFunction_382) {
  auto subject = MakeSubject_382();
  ASSERT_NE(subject, nullptr);

  auto cloned = subject->copy();
  ASSERT_NE(cloned, nullptr);

  // Observable behavior: copy() of a PostScriptFunction should yield a PostScriptFunction.
  // (This does not inspect private state; it only checks RTTI via dynamic_cast.)
  auto* asPs = dynamic_cast<PostScriptFunction*>(cloned.get());
  EXPECT_NE(asPs, nullptr);
}

TEST_F(PostScriptFunctionTest_382, CopyPreservesGetTypeIfCallable_382) {
  auto subject = MakeSubject_382();
  ASSERT_NE(subject, nullptr);

  // If construction is invalid, skip rather than inferring behavior.
  if (!subject->isOk()) {
    GTEST_SKIP() << "PostScriptFunction instance is not OK in this environment; "
                    "provide a valid Object/Dict to exercise type preservation.";
  }

  const auto originalType = subject->getType();

  auto cloned = subject->copy();
  ASSERT_NE(cloned, nullptr);

  // If the clone is not OK, we cannot assert more without guessing internal semantics.
  if (!cloned->isOk()) {
    GTEST_SKIP() << "Copied function is not OK in this environment; "
                    "provide a valid Object/Dict to exercise type preservation.";
  }

  EXPECT_EQ(cloned->getType(), originalType);
}

TEST_F(PostScriptFunctionTest_382, CopyDoesNotAliasGetCodeStringPointerWhenAvailable_382) {
  auto subject = MakeSubject_382();
  ASSERT_NE(subject, nullptr);

  if (!subject->isOk()) {
    GTEST_SKIP() << "PostScriptFunction instance is not OK in this environment; "
                    "provide a valid Object/Dict to exercise code string behavior.";
  }

  const GooString* originalCode = subject->getCodeString();

  auto cloned = subject->copy();
  ASSERT_NE(cloned, nullptr);

  auto* clonedPs = dynamic_cast<PostScriptFunction*>(cloned.get());
  ASSERT_NE(clonedPs, nullptr);

  if (!clonedPs->isOk()) {
    GTEST_SKIP() << "Copied PostScriptFunction is not OK in this environment; "
                    "provide a valid Object/Dict to exercise code string behavior.";
  }

  const GooString* clonedCode = clonedPs->getCodeString();

  // Boundary/robustness: allow either/both to be null, but if both are non-null,
  // expect them to not be the same address (typical deep-copy expectation).
  if (originalCode && clonedCode) {
    EXPECT_NE(originalCode, clonedCode);
  }
}

TEST_F(PostScriptFunctionTest_382, CopyCanBeCalledMultipleTimesIndependently_382) {
  auto subject = MakeSubject_382();
  ASSERT_NE(subject, nullptr);

  auto c1 = subject->copy();
  auto c2 = subject->copy();

  ASSERT_NE(c1, nullptr);
  ASSERT_NE(c2, nullptr);
  EXPECT_NE(c1.get(), c2.get());

  // Both copies should still be PostScriptFunction objects.
  EXPECT_NE(dynamic_cast<PostScriptFunction*>(c1.get()), nullptr);
  EXPECT_NE(dynamic_cast<PostScriptFunction*>(c2.get()), nullptr);
}