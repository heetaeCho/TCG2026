// LinkSubmitForm_test.cpp
// Unit tests for LinkSubmitForm (Poppler)
// TEST_ID: 338

#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"

namespace {

class LinkSubmitFormTest_338 : public ::testing::Test {};

// Builds an action dictionary Object that *attempts* to represent a SubmitForm action.
// Different Poppler forks/versions may parse different keys; tests will probe a few.
static Object BuildSubmitFormActionObjWithUrlKey_338(const char* urlKey, const char* urlValue) {
  Object actionDict;
  actionDict.initDict(new Dict(nullptr));

  Dict* dict = actionDict.getDict();
  ASSERT_NE(dict, nullptr);

  Object s;
  s.initName("SubmitForm");
  dict->add("S", std::move(s));

  Object f;
  f.initString(new GooString(urlValue));
  dict->add(urlKey, std::move(f));

  // Optional: include common optional entries without asserting they must be parsed.
  Object flags;
  flags.initInt(0);
  dict->add("Flags", std::move(flags));

  Object fields;
  fields.initArray(nullptr);
  if (Array* arr = fields.getArray(); arr) {
    Object fld;
    fld.initString(new GooString("FieldA"));
    arr->add(std::move(fld));
  }
  dict->add("Fields", std::move(fields));

  return actionDict; // move
}

static LinkSubmitForm MakeSubmitFormTryingCommonKeys_338(const char* urlValue, Object* backingObjOut) {
  // Try a few commonly-used keys for URL/file spec in PDF actions.
  // NOTE: We do NOT assume which one Poppler uses; the test will accept whichever works.
  static const char* kCandidates[] = {"F", "URL", "Url", "URI"};

  for (const char* key : kCandidates) {
    *backingObjOut = BuildSubmitFormActionObjWithUrlKey_338(key, urlValue);
    LinkSubmitForm form(backingObjOut);
    if (form.isOk()) {
      return form;
    }
  }

  // Fall back to last attempt (likely invalid) so caller can decide to skip.
  LinkSubmitForm form(backingObjOut);
  return form;
}

TEST_F(LinkSubmitFormTest_338, IsOkMatchesGetUrlEmptiness_ForNullObject_338) {
  Object submitObj;
  submitObj.initNull();

  LinkSubmitForm form(&submitObj);

  // Based on the provided implementation: isOk() == !url.empty().
  // We validate the observable relationship via getUrl().
  EXPECT_EQ(form.isOk(), !form.getUrl().empty());
}

TEST_F(LinkSubmitFormTest_338, GetUrlReferenceIsStableAcrossCalls_338) {
  Object submitObj;
  submitObj.initNull();

  LinkSubmitForm form(&submitObj);

  const std::string* p1 = &form.getUrl();
  const std::string* p2 = &form.getUrl();
  EXPECT_EQ(p1, p2);
}

TEST_F(LinkSubmitFormTest_338, GetFieldsReferenceIsStableAcrossCalls_338) {
  Object submitObj;
  submitObj.initNull();

  LinkSubmitForm form(&submitObj);

  const std::vector<std::string>* p1 = &form.getFields();
  const std::vector<std::string>* p2 = &form.getFields();
  EXPECT_EQ(p1, p2);
}

TEST_F(LinkSubmitFormTest_338, IsOkTrueImpliesNonEmptyUrl_WhenActionObjectProvidesUrl_338) {
  Object actionObj;
  LinkSubmitForm form = MakeSubmitFormTryingCommonKeys_338("https://example.com/submit", &actionObj);

  if (!form.isOk()) {
    GTEST_SKIP() << "Unable to construct a SubmitForm action Object that this build parses "
                    "into a non-empty URL; skipping this interaction test.";
  }

  EXPECT_FALSE(form.getUrl().empty());
  EXPECT_TRUE(form.isOk());

  // Provided implementation relationship should hold for all observable states.
  EXPECT_EQ(form.isOk(), !form.getUrl().empty());
}

TEST_F(LinkSubmitFormTest_338, Boundary_EmptyUrlStaysNotOk_WhenProvidedEmptyString_338) {
  Object actionObj;
  LinkSubmitForm form = MakeSubmitFormTryingCommonKeys_338("", &actionObj);

  // Even if parsing succeeds, an empty URL should be observable as empty.
  // We avoid assuming parsing success; we only assert the invariant relationship.
  EXPECT_EQ(form.isOk(), !form.getUrl().empty());

  // If it *did* parse and URL is empty, it must not be OK (per provided implementation).
  if (form.getUrl().empty()) {
    EXPECT_FALSE(form.isOk());
  }
}

} // namespace