// FormFieldText_getContent_902_test.cpp
// Unit tests for FormFieldText::getContent()
// TEST_ID: 902

#include <gtest/gtest.h>

#include <memory>
#include <set>
#include <type_traits>
#include <utility>

#include "Form.h"

// ---- Small compile-time helpers (do not infer internal logic) ----

namespace {

template <typename T, typename = void>
struct HasSetContentUniquePtr : std::false_type {};
template <typename T>
struct HasSetContentUniquePtr<T, std::void_t<decltype(std::declval<T&>().setContent(std::unique_ptr<GooString>{}))>>
    : std::true_type {};

template <typename T, typename = void>
struct HasSetContentInt : std::false_type {};
template <typename T>
struct HasSetContentInt<T, std::void_t<decltype(std::declval<T&>().setContent(int{}))>> : std::true_type {};

template <typename T>
std::unique_ptr<T> TryMakeFormFieldText()
{
  // We avoid depending on private/internal state. Construction uses only the public constructors (if available).
  // If construction is not possible in this test build/config, tests will be skipped.

  // These types are expected to be available via Form.h in Poppler.
  PDFDoc *doc = nullptr;
  Object dictObj; // default/empty object
  Ref ref{};      // default ref
  FormField *parent = nullptr;

  // Prefer the constructor with std::set<int>* if available.
  if constexpr (std::is_constructible_v<T, PDFDoc *, Object &&, Ref, FormField *, std::set<int> *>) {
    auto usedParents = std::make_unique<std::set<int>>();
    // Note: usedParents lifetime must outlive the constructed object if it stores the pointer.
    // To avoid guessing, we intentionally keep it leaked via release() and never free it in tests.
    // This is acceptable for unit tests and avoids making assumptions about ownership.
    return std::make_unique<T>(doc, std::move(dictObj), ref, parent, usedParents.release());
  } else if constexpr (std::is_constructible_v<T, PDFDoc *, Object &&, Ref, FormField *, int *>) {
    auto usedParents = std::make_unique<int>(0);
    return std::make_unique<T>(doc, std::move(dictObj), ref, parent, usedParents.release());
  } else {
    return nullptr;
  }
}

} // namespace

// ---- Tests (black-box, interface-only) ----

TEST(FormFieldTextTest_902, GetContentInitiallyNullOrStable_902)
{
  auto field = TryMakeFormFieldText<FormFieldText>();
  if (!field) {
    GTEST_SKIP() << "FormFieldText cannot be constructed with available public constructors in this build.";
  }

  // Observable behavior: getter returns a pointer (may be nullptr initially).
  const GooString *p1 = field->getContent();
  const GooString *p2 = field->getContent();

  // Boundary/consistency: repeated calls should be stable/consistent (no mutation expected from const getter).
  EXPECT_EQ(p1, p2);
}

TEST(FormFieldTextTest_902, GetContentConstCallable_902)
{
  auto field = TryMakeFormFieldText<FormFieldText>();
  if (!field) {
    GTEST_SKIP() << "FormFieldText cannot be constructed with available public constructors in this build.";
  }

  const FormFieldText &cref = *field;
  const GooString *p = cref.getContent();
  (void)p;

  SUCCEED(); // Compiles and runs: getContent is callable on const object.
}

TEST(FormFieldTextTest_902, SetContentUniquePtrThenGetContentReturnsSamePointer_902)
{
  auto field = TryMakeFormFieldText<FormFieldText>();
  if (!field) {
    GTEST_SKIP() << "FormFieldText cannot be constructed with available public constructors in this build.";
  }

  if constexpr (!HasSetContentUniquePtr<FormFieldText>::value) {
    GTEST_SKIP() << "FormFieldText::setContent(std::unique_ptr<GooString>) not available in this build.";
  } else {
    auto gs = std::make_unique<GooString>("hello");
    GooString *raw = gs.get();

    field->setContent(std::move(gs));

    // Observable behavior: getContent returns a pointer; after setting, it should reflect the set value.
    // We only assert pointer identity (no internal string assumptions).
    EXPECT_EQ(field->getContent(), raw);
  }
}

TEST(FormFieldTextTest_902, SetContentUniquePtrNullClearsOrReturnsNull_902)
{
  auto field = TryMakeFormFieldText<FormFieldText>();
  if (!field) {
    GTEST_SKIP() << "FormFieldText cannot be constructed with available public constructors in this build.";
  }

  if constexpr (!HasSetContentUniquePtr<FormFieldText>::value) {
    GTEST_SKIP() << "FormFieldText::setContent(std::unique_ptr<GooString>) not available in this build.";
  } else {
    // Boundary: set a non-null value first, then set null.
    auto gs = std::make_unique<GooString>("x");
    field->setContent(std::move(gs));
    ASSERT_NE(field->getContent(), nullptr);

    std::unique_ptr<GooString> nullGs;
    field->setContent(std::move(nullGs));

    // Observable: after setting nullptr unique_ptr, getter should reasonably become nullptr.
    // If implementation differs, this will expose it.
    EXPECT_EQ(field->getContent(), nullptr);
  }
}

TEST(FormFieldTextTest_902, SetContentIntDoesNotCrashAndGetterIsCallable_902)
{
  auto field = TryMakeFormFieldText<FormFieldText>();
  if (!field) {
    GTEST_SKIP() << "FormFieldText cannot be constructed with available public constructors in this build.";
  }

  if constexpr (!HasSetContentInt<FormFieldText>::value) {
    GTEST_SKIP() << "FormFieldText::setContent(int) not available in this build.";
  } else {
    // Exceptional/error case (observable): calling with an arbitrary value should not crash,
    // and getter should remain callable.
    field->setContent(0);
    (void)field->getContent();
    SUCCEED();
  }
}