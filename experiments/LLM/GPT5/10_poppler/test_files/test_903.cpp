// FormFieldText_getAppearanceContent_test.cpp
// TEST_ID: 903

#include <gtest/gtest.h>

#include <memory>
#include <set>
#include <string>

// Poppler headers (paths may vary slightly depending on the build layout)
#include "Form.h"
#include "goo/GooString.h"
#include "Object.h"
#include "PDFDoc.h"

namespace {

class FormFieldTextTest_903 : public ::testing::Test {
protected:
  // Helper to construct a FormFieldText with minimal/dummy collaborators.
  // We do NOT rely on any internal state; we only use the public interface.
  static std::unique_ptr<FormFieldText> MakeField()
  {
    PDFDoc *doc = nullptr;
    Object dictObj; // default/empty object; treated as a black box input
    Ref ref;
    ref.num = 0;
    ref.gen = 0;

    FormField *parent = nullptr;
    auto usedParents = std::make_unique<std::set<int>>();

    // Prefer the constructor using std::set<int>* as it's a concrete type here.
    return std::make_unique<FormFieldText>(doc, std::move(dictObj), ref, parent, usedParents.get());
  }

  static const char *CStringOrNull(const GooString *s) { return s ? s->getCString() : nullptr; }
};

TEST_F(FormFieldTextTest_903, ReturnsNullptrWhenNoContentSet_903)
{
  auto field = MakeField();

  // With neither content nor appearance content set, the method should be safe to call.
  const GooString *ap = field->getAppearanceContent();
  EXPECT_EQ(ap, nullptr);
}

TEST_F(FormFieldTextTest_903, ReturnsContentWhenAppearanceContentNotSet_903)
{
  auto field = MakeField();

  field->setContent(std::make_unique<GooString>("base-content"));
  const GooString *ap = field->getAppearanceContent();

  ASSERT_NE(ap, nullptr);
  EXPECT_STREQ(CStringOrNull(ap), "base-content");
}

TEST_F(FormFieldTextTest_903, ReturnsAppearanceContentWhenSet_903)
{
  auto field = MakeField();

  field->setContent(std::make_unique<GooString>("base-content"));
  field->setAppearanceContent(std::make_unique<GooString>("appearance-content"));

  const GooString *ap = field->getAppearanceContent();
  ASSERT_NE(ap, nullptr);
  EXPECT_STREQ(CStringOrNull(ap), "appearance-content");
}

TEST_F(FormFieldTextTest_903, FallsBackToContentAfterClearingAppearanceContent_903)
{
  auto field = MakeField();

  field->setContent(std::make_unique<GooString>("base-content"));
  field->setAppearanceContent(std::make_unique<GooString>("appearance-content"));

  // Clear appearance content using the public API (passing nullptr unique_ptr).
  field->setAppearanceContent(std::unique_ptr<GooString>());

  const GooString *ap = field->getAppearanceContent();
  ASSERT_NE(ap, nullptr);
  EXPECT_STREQ(CStringOrNull(ap), "base-content");
}

TEST_F(FormFieldTextTest_903, HandlesEmptyStringsForContentAndAppearance_903)
{
  auto field = MakeField();

  field->setContent(std::make_unique<GooString>(""));
  EXPECT_STREQ(CStringOrNull(field->getAppearanceContent()), "");

  field->setAppearanceContent(std::make_unique<GooString>(""));
  EXPECT_STREQ(CStringOrNull(field->getAppearanceContent()), "");
}

} // namespace