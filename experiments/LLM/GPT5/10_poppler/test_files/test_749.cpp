// AnnotBorder_getStyle_749_test.cpp
#include <gtest/gtest.h>

#include "poppler/Annot.h"

namespace {

// Minimal concrete type for testing: AnnotBorder has a protected default ctor,
// so we derive and expose it without touching internal/protected state.
class TestableAnnotBorder_749 final : public AnnotBorder {
public:
  TestableAnnotBorder_749() : AnnotBorder() {}
  ~TestableAnnotBorder_749() override = default;
};

class AnnotBorderTest_749 : public ::testing::Test {};

}  // namespace

TEST_F(AnnotBorderTest_749, GetStyle_IsCallableAndStableAcrossCalls_749) {
  TestableAnnotBorder_749 border;

  const auto s1 = border.getStyle();
  const auto s2 = border.getStyle();

  EXPECT_EQ(s1, s2);
}

TEST_F(AnnotBorderTest_749, GetStyle_WorksOnConstObject_749) {
  TestableAnnotBorder_749 border;
  const AnnotBorder& const_ref = border;

  const auto s1 = border.getStyle();
  const auto s2 = const_ref.getStyle();

  EXPECT_EQ(s1, s2);
}

TEST_F(AnnotBorderTest_749, GetStyle_CopyPreservesObservableStyle_749) {
  TestableAnnotBorder_749 border;

  const auto original_style = border.getStyle();
  std::unique_ptr<AnnotBorder> copied = border.copy();

  ASSERT_NE(copied, nullptr);
  EXPECT_EQ(copied->getStyle(), original_style);
}