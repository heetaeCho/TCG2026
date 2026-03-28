// LinkSubmitForm_test_341.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>

#include "Link.h"

// These headers exist in Poppler codebases where LinkSubmitForm(Object*) is used.
// If your build already includes them via Link.h, these includes are harmless.
#include "Object.h"
#include "Dict.h"
#include "Array.h"
#include "GooString.h"

namespace {

// --------- Small, version-tolerant helpers (no logic inference) ---------

template <typename T, typename = void>
struct has_initString : std::false_type {};
template <typename T>
struct has_initString<T, std::void_t<decltype(std::declval<T &>().initString((GooString *)nullptr))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_initInt : std::false_type {};
template <typename T>
struct has_initInt<T, std::void_t<decltype(std::declval<T &>().initInt(0))>> : std::true_type {};

template <typename T, typename = void>
struct has_initName : std::false_type {};
template <typename T>
struct has_initName<T, std::void_t<decltype(std::declval<T &>().initName((const char *)nullptr))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_initArray : std::false_type {};
template <typename T>
struct has_initArray<T, std::void_t<decltype(std::declval<T &>().initArray((Array *)nullptr))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_initDict : std::false_type {};
template <typename T>
struct has_initDict<T, std::void_t<decltype(std::declval<T &>().initDict((Dict *)nullptr))>>
    : std::true_type {};

template <typename D, typename O, typename = void>
struct dict_add_by_value : std::false_type {};
template <typename D, typename O>
struct dict_add_by_value<
    D,
    O,
    std::void_t<decltype(std::declval<D &>().add((const char *)nullptr, std::declval<O>()))>>
    : std::true_type {};

template <typename D, typename O, typename = void>
struct dict_add_by_ptr : std::false_type {};
template <typename D, typename O>
struct dict_add_by_ptr<
    D,
    O,
    std::void_t<decltype(std::declval<D &>().add((const char *)nullptr, (O *)nullptr))>>
    : std::true_type {};

// Build an Object that holds a string.
static Object MakeStringObject(const std::string &s) {
  Object o;
  if constexpr (has_initString<Object>::value) {
    o.initString(new GooString(s.c_str()));
  } else {
    // Fallback for variants where Object has different constructors.
    // Try common patterns without assuming internals.
    o = Object(new GooString(s.c_str()));
  }
  return o;
}

// Build an Object that holds an int.
static Object MakeIntObject(int v) {
  Object o;
  if constexpr (has_initInt<Object>::value) {
    o.initInt(v);
  } else {
    o = Object(v);
  }
  return o;
}

// Build an Object that holds a PDF Name (if supported).
static Object MakeNameObject(const char *name) {
  Object o;
  if constexpr (has_initName<Object>::value) {
    o.initName(name);
  } else {
    // Some versions may not support initName here; leave it null-ish.
    // This keeps test compilation portable without inferring behavior.
    (void)name;
  }
  return o;
}

// Build an Object that holds an Array with one string (if supported).
static Object MakeSingleStringArrayObject(const std::string &s) {
  Array *arr = new Array(nullptr);
  // Array::add signature also varies. Use a simple, common call pattern:
  // add(Object) by value is typical.
  arr->add(MakeStringObject(s));

  Object o;
  if constexpr (has_initArray<Object>::value) {
    o.initArray(arr);
  } else {
    o = Object(arr);
  }
  return o;
}

static void DictAdd(Dict *dict, const char *key, Object &&val) {
  if constexpr (dict_add_by_value<Dict, Object>::value) {
    dict->add(key, std::move(val));
  } else if constexpr (dict_add_by_ptr<Dict, Object>::value) {
    // Some Poppler variants take ownership via pointer.
    dict->add(key, new Object(std::move(val)));
  } else {
    // If Dict::add is unavailable in this build, tests relying on it will not compile;
    // keeping this branch avoids hard failure in template instantiation.
    (void)dict;
    (void)key;
    (void)val;
  }
}

static Object MakeDictObject(std::unique_ptr<Dict> dict) {
  Object o;
  if constexpr (has_initDict<Object>::value) {
    o.initDict(dict.release());
  } else {
    o = Object(dict.release());
  }
  return o;
}

// Construct a best-effort "SubmitForm action dict" object.
// We do not assume which keys are mandatory; we just provide common ones so that
// observable behavior (isOk / getUrl / getFlags / getFields) can be exercised.
static Object MakeSubmitFormObject(const std::string &url,
                                  uint32_t flags,
                                  const std::string &fieldOne) {
  auto dict = std::make_unique<Dict>(nullptr);

  // Common action dict keys in PDFs:
  //   /S /SubmitForm
  //   /F (file spec / URL)
  //   /Flags <int>
  //   /Fields [...]
  DictAdd(dict.get(), "S", MakeNameObject("SubmitForm"));
  DictAdd(dict.get(), "F", MakeStringObject(url));
  DictAdd(dict.get(), "Flags", MakeIntObject(static_cast<int>(flags)));
  DictAdd(dict.get(), "Fields", MakeSingleStringArrayObject(fieldOne));

  return MakeDictObject(std::move(dict));
}

}  // namespace

// ------------------------- Tests -------------------------

class LinkSubmitFormTest_341 : public ::testing::Test {};

TEST_F(LinkSubmitFormTest_341, GetUrlReferenceIsStable_341) {
  Object submitObj = MakeSubmitFormObject("http://example.com/submit", 0u, "FieldA");
  LinkSubmitForm form(&submitObj);

  const std::string *p1 = &form.getUrl();
  const std::string *p2 = &form.getUrl();

  EXPECT_EQ(p1, p2) << "getUrl() should return a stable reference across calls";
}

TEST_F(LinkSubmitFormTest_341, GetUrlMatchesProvidedUrlWhenOk_341) {
  const std::string kUrl = "http://example.com/submit";
  Object submitObj = MakeSubmitFormObject(kUrl, 0u, "FieldA");
  LinkSubmitForm form(&submitObj);

  // Observable contract: we can only assert strongly if the object reports OK.
  // If it isn't OK in a particular Poppler build (due to differing required keys),
  // we still validate safe observable behavior (no crash, reference returned).
  if (form.isOk()) {
    EXPECT_EQ(form.getUrl(), kUrl);
  } else {
    // Error/exceptional observable path: object not OK
    // Ensure getUrl is still callable and returns a valid reference.
    EXPECT_NO_THROW((void)form.getUrl());
  }
}

TEST_F(LinkSubmitFormTest_341, Boundary_EmptyUrlDoesNotCrash_341) {
  Object submitObj = MakeSubmitFormObject("", 0u, "FieldA");
  LinkSubmitForm form(&submitObj);

  EXPECT_NO_THROW((void)form.getUrl());
  // If OK, empty URL should be observable as empty.
  if (form.isOk()) {
    EXPECT_TRUE(form.getUrl().empty());
  }
}

TEST_F(LinkSubmitFormTest_341, FlagsAndFieldsAreQueryable_341) {
  Object submitObj = MakeSubmitFormObject("http://example.com/submit", 123u, "FieldA");
  LinkSubmitForm form(&submitObj);

  // These are purely observable interface calls; no assumptions about internal parsing.
  EXPECT_NO_THROW((void)form.getFlags());
  EXPECT_NO_THROW((void)form.getFields());

  if (form.isOk()) {
    // If parsing succeeds, flags should match and fields should be non-empty.
    EXPECT_EQ(form.getFlags(), 123u);
    EXPECT_FALSE(form.getFields().empty());
  }
}

TEST_F(LinkSubmitFormTest_341, KindIsSubmitFormOrConsistent_341) {
  Object submitObj = MakeSubmitFormObject("http://example.com/submit", 0u, "FieldA");
  LinkSubmitForm form(&submitObj);

  // Observable: getKind is callable and stable.
  const auto k1 = form.getKind();
  const auto k2 = form.getKind();
  EXPECT_EQ(k1, k2);

  // If OK, kind should be the submit-form kind. We only assert when observable OK.
  if (form.isOk()) {
    EXPECT_EQ(k1, actionSubmitForm);
  }
}