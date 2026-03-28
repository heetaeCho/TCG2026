// File: HtmlFont_isItalic_test_2619.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "TestProjects/poppler/utils/HtmlFonts.h"

class HtmlFontTest_2619 : public ::testing::Test {};

// Normal operation (interface-level): isItalic() is callable on a const HtmlFont&
TEST_F(HtmlFontTest_2619, IsItalicCallableOnConstRef_2619) {
  // This test is purely about the public interface shape.
  // It does not construct HtmlFont (constructor requires Poppler types).
  using Ret = decltype(std::declval<const HtmlFont&>().isItalic());
  EXPECT_TRUE((std::is_same_v<Ret, bool>));
}

// Boundary condition: isItalic() is callable on a const pointer as well
TEST_F(HtmlFontTest_2619, IsItalicCallableViaConstPointer_2619) {
  using Ret = decltype(std::declval<const HtmlFont*>()->isItalic());
  EXPECT_TRUE((std::is_same_v<Ret, bool>));
}

// Boundary condition: the method is const-qualified (cannot require a non-const object)
TEST_F(HtmlFontTest_2619, IsItalicIsConstQualified_2619) {
  // If isItalic were non-const, this line would fail to compile.
  const HtmlFont& ref = *static_cast<const HtmlFont*>(nullptr);
  (void)ref.isItalic();

  SUCCEED();
}

// Exceptional/error case (observable through interface): the expression is well-formed;
// no construction or private access is involved, and no exceptions are expected merely
// from forming the call expression type.
TEST_F(HtmlFontTest_2619, IsItalicCallExpressionIsWellFormed_2619) {
  // Verify the call expression can be formed in unevaluated context.
  EXPECT_TRUE((std::is_same_v<decltype(std::declval<const HtmlFont&>().isItalic()), bool>));
}