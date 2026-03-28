// TEST_ID: 915
// File: test_formfieldchoice_getAppearanceSelectedChoice_915.cpp

#include <gtest/gtest.h>

#include <memory>
#include <set>

#include "poppler/Form.h"
#include "goo/GooString.h"
#include "poppler/Object.h"
#include "poppler/GlobalParams.h"

namespace {

class FormFieldChoiceTest_915 : public ::testing::Test {
protected:
  // Best-effort construction using only the public constructor signature we have.
  // These tests treat FormFieldChoice as a black box and only validate behavior
  // observable via its public API.
  static std::unique_ptr<FormFieldChoice> CreateSut() {
    PDFDoc* doc = nullptr;
    Object aobj;              // default/empty
    Ref ref = {0, 0};
    FormField* parent = nullptr;
    std::set<int> usedParents; // provided to satisfy constructor signature

    return std::make_unique<FormFieldChoice>(doc, std::move(aobj), ref, parent, &usedParents);
  }

  static const char* CStringOrNull(const GooString* s) {
    return s ? s->c_str() : nullptr;
  }
};

TEST_F(FormFieldChoiceTest_915, ReturnsAppearanceChoiceWhenSet_915) {
  auto sut = CreateSut();
  ASSERT_NE(sut, nullptr);

  auto content = std::make_unique<GooString>("appearance-915");
  const GooString* raw = content.get();

  sut->setAppearanceChoiceContent(std::move(content));

  const GooString* got = sut->getAppearanceSelectedChoice();
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got, raw);  // should be the stored appearance content pointer
  EXPECT_STREQ(CStringOrNull(got), "appearance-915");
}

TEST_F(FormFieldChoiceTest_915, ClearingAppearanceChoiceFallsBackToSelectedChoice_915) {
  auto sut = CreateSut();
  ASSERT_NE(sut, nullptr);

  // Set then clear (boundary: empty/null unique_ptr).
  sut->setAppearanceChoiceContent(std::make_unique<GooString>("temp-915"));
  sut->setAppearanceChoiceContent(std::unique_ptr<GooString>{}); // clear

  // Observable behavior per interface: getAppearanceSelectedChoice() returns
  // appearanceSelectedChoice if present, otherwise getSelectedChoice().
  const GooString* fallback = sut->getSelectedChoice();
  const GooString* got = sut->getAppearanceSelectedChoice();

  EXPECT_EQ(got, fallback);
}

TEST_F(FormFieldChoiceTest_915, ReturnedPointerTracksLastAppearanceContent_915) {
  auto sut = CreateSut();
  ASSERT_NE(sut, nullptr);

  sut->setAppearanceChoiceContent(std::make_unique<GooString>("first-915"));
  const GooString* firstPtr = sut->getAppearanceSelectedChoice();
  ASSERT_NE(firstPtr, nullptr);
  EXPECT_STREQ(CStringOrNull(firstPtr), "first-915");

  sut->setAppearanceChoiceContent(std::make_unique<GooString>("second-915"));
  const GooString* secondPtr = sut->getAppearanceSelectedChoice();
  ASSERT_NE(secondPtr, nullptr);
  EXPECT_STREQ(CStringOrNull(secondPtr), "second-915");

  // After update, pointer should refer to the latest appearance content
  // (we don't assume allocation behavior beyond observable pointer change).
  EXPECT_NE(firstPtr, secondPtr);
}

TEST_F(FormFieldChoiceTest_915, DoesNotCrashWhenCalledRepeatedlyWithoutAppearanceSet_915) {
  auto sut = CreateSut();
  ASSERT_NE(sut, nullptr);

  // Boundary/robustness: repeated calls when appearance content is not set.
  // We only assert consistency with getSelectedChoice(), without assuming non-nullness.
  const GooString* s1 = sut->getAppearanceSelectedChoice();
  const GooString* sel1 = sut->getSelectedChoice();
  EXPECT_EQ(s1, sel1);

  const GooString* s2 = sut->getAppearanceSelectedChoice();
  const GooString* sel2 = sut->getSelectedChoice();
  EXPECT_EQ(s2, sel2);
}

} // namespace