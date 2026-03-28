// TEST_ID: 913
// File: test_form_field_choice_getChoice_913.cpp

#include <gtest/gtest.h>

#include "poppler/Form.h"
#include "poppler/Object.h"

namespace {

class FormFieldChoiceTest_913 : public ::testing::Test {
protected:
  static Object MakeNullObject() {
    Object o;
    o.initNull();
    return o;
  }

  static Ref MakeDummyRef() {
    Ref r{};
    r.num = 0;
    r.gen = 0;
    return r;
  }

  // Best-effort construction with minimal inputs.
  // The tests below only rely on observable behavior of getChoice()
  // and do not inspect/modify any internal state.
  static std::unique_ptr<FormFieldChoice> MakeMinimalChoiceField() {
    Object obj = MakeNullObject();
    auto usedParents = std::make_unique<std::set<int>>();
    return std::make_unique<FormFieldChoice>(
        /*docA=*/nullptr,
        /*aobj=*/std::move(obj),
        /*ref=*/MakeDummyRef(),
        /*parent=*/nullptr,
        /*usedParents=*/usedParents.get());
  }
};

TEST_F(FormFieldChoiceTest_913, GetChoiceReturnsNullWhenNoChoices_913) {
  auto field = MakeMinimalChoiceField();
  ASSERT_NE(field, nullptr);

  // When there are no choices available, getChoice should return nullptr.
  EXPECT_EQ(field->getChoice(0), nullptr);
}

TEST_F(FormFieldChoiceTest_913, GetChoiceReturnsNullForNegativeIndexWhenNoChoices_913) {
  auto field = MakeMinimalChoiceField();
  ASSERT_NE(field, nullptr);

  // Boundary: negative index.
  EXPECT_EQ(field->getChoice(-1), nullptr);
}

TEST_F(FormFieldChoiceTest_913, GetChoiceReturnsNullForLargeIndexWhenNoChoices_913) {
  auto field = MakeMinimalChoiceField();
  ASSERT_NE(field, nullptr);

  // Boundary: very large index.
  EXPECT_EQ(field->getChoice(1'000'000), nullptr);
}

}  // namespace