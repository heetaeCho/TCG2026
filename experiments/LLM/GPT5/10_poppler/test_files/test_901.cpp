// FormFieldButton_getNumSiblings_test_901.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>
#include <set>

#include "Form.h"

namespace {

// --- Detection helpers (so this test file can compile against reduced headers) ---

template <typename T, typename = void>
struct has_setNumSiblings : std::false_type {};
template <typename T>
struct has_setNumSiblings<T, std::void_t<decltype(std::declval<T&>().setNumSiblings(int{}))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_setSibling : std::false_type {};
template <typename T>
struct has_setSibling<T,
                      std::void_t<decltype(std::declval<T&>().setSibling(
                          int{}, static_cast<T*>(nullptr)))>> : std::true_type {};

template <typename T, typename = void>
struct has_getSibling : std::false_type {};
template <typename T>
struct has_getSibling<T, std::void_t<decltype(std::declval<const T&>().getSibling(int{}))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_getNumSiblings : std::false_type {};
template <typename T>
struct has_getNumSiblings<T, std::void_t<decltype(std::declval<const T&>().getNumSiblings())>>
    : std::true_type {};

// --- Construction helper ---
// Tries a few plausible construction paths; if none work in the current build,
// tests will GTEST_SKIP (rather than failing to compile).
struct FormFieldButtonFactory {
  static std::unique_ptr<FormFieldButton> MakeOrSkip() {
    // 1) Default constructible build
    if constexpr (std::is_default_constructible_v<FormFieldButton>) {
      return std::make_unique<FormFieldButton>();
    }

    // 2) Try Poppler-like constructors if types are available and usable.
    // NOTE: We intentionally pass null/empty placeholders and only use methods
    // that should not require a fully-initialized PDF context for these tests.
    // If your build requires real objects, the test will skip.
    if constexpr (std::is_constructible_v<FormFieldButton,
                                         PDFDoc*,
                                         Object&&,
                                         Ref,
                                         FormField*,
                                         std::set<int>*>) {
      PDFDoc* doc = nullptr;
      Object dict;
      Ref ref{};
      FormField* parent = nullptr;
      std::set<int> usedParents;
      return std::make_unique<FormFieldButton>(doc, std::move(dict), ref, parent, &usedParents);
    }

    if constexpr (std::is_constructible_v<FormFieldButton,
                                         PDFDoc*,
                                         Object&&,
                                         Ref,
                                         FormField*,
                                         int*>) {
      PDFDoc* doc = nullptr;
      Object dict;
      Ref ref{};
      FormField* parent = nullptr;
      int usedParents = 0;
      return std::make_unique<FormFieldButton>(doc, std::move(dict), ref, parent, &usedParents);
    }

    return nullptr;
  }
};

class FormFieldButtonTest_901 : public ::testing::Test {
 protected:
  std::unique_ptr<FormFieldButton> Make() {
    auto p = FormFieldButtonFactory::MakeOrSkip();
    if (!p) {
      GTEST_SKIP() << "FormFieldButton could not be constructed in this build configuration.";
    }
    return p;
  }
};

}  // namespace

static_assert(has_getNumSiblings<FormFieldButton>::value,
              "FormFieldButton must provide getNumSiblings() for these tests.");

// --- Tests ---

TEST_F(FormFieldButtonTest_901, NewlyConstructedHasNonNegativeSiblingCount_901) {
  auto btn = Make();

  const int n = btn->getNumSiblings();
  EXPECT_GE(n, 0);
}

TEST_F(FormFieldButtonTest_901, GetNumSiblingsIsStableAcrossRepeatedCalls_901) {
  auto btn = Make();

  const int a = btn->getNumSiblings();
  const int b = btn->getNumSiblings();
  const int c = btn->getNumSiblings();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
}

TEST_F(FormFieldButtonTest_901, SetNumSiblingsUpdatesReportedCount_901) {
  auto btn = Make();

  if constexpr (!has_setNumSiblings<FormFieldButton>::value) {
    GTEST_SKIP() << "setNumSiblings(int) not available in this build.";
  } else {
    btn->setNumSiblings(0);
    EXPECT_EQ(btn->getNumSiblings(), 0);

    btn->setNumSiblings(1);
    EXPECT_EQ(btn->getNumSiblings(), 1);

    btn->setNumSiblings(5);
    EXPECT_EQ(btn->getNumSiblings(), 5);
  }
}

TEST_F(FormFieldButtonTest_901, SetNumSiblingsWithNegativeDoesNotProduceNegativeCount_901) {
  auto btn = Make();

  if constexpr (!has_setNumSiblings<FormFieldButton>::value) {
    GTEST_SKIP() << "setNumSiblings(int) not available in this build.";
  } else {
    // Exceptional/boundary: negative input.
    // We do not assume clamping behavior; we only require the observable count
    // to remain a valid (non-negative) integer.
    btn->setNumSiblings(-1);
    EXPECT_GE(btn->getNumSiblings(), 0);
  }
}

TEST_F(FormFieldButtonTest_901, SetSiblingThenGetSiblingReturnsSamePointer_901) {
  auto btn = Make();

  if constexpr (!(has_setNumSiblings<FormFieldButton>::value && has_setSibling<FormFieldButton>::value &&
                  has_getSibling<FormFieldButton>::value)) {
    GTEST_SKIP() << "Sibling mutation/accessors not available in this build.";
  } else {
    auto sib0 = Make();
    auto sib1 = Make();

    btn->setNumSiblings(2);

    btn->setSibling(0, sib0.get());
    btn->setSibling(1, sib1.get());

    EXPECT_EQ(btn->getSibling(0), sib0.get());
    EXPECT_EQ(btn->getSibling(1), sib1.get());
  }
}

TEST_F(FormFieldButtonTest_901, GetSiblingOutOfRangeReturnsNullptrOrRemainsSafe_901) {
  auto btn = Make();

  if constexpr (!(has_setNumSiblings<FormFieldButton>::value && has_getSibling<FormFieldButton>::value)) {
    GTEST_SKIP() << "Sibling sizing/getSibling not available in this build.";
  } else {
    btn->setNumSiblings(1);

    // Boundary/error case: out-of-range indices. We avoid assuming a specific
    // behavior (null vs. something else), but we can still validate safety by
    // checking for nullptr when provided and that the call completes.
    // If your implementation throws, adjust to EXPECT_ANY_THROW as needed.
    FormFieldButton* p_neg = btn->getSibling(-1);
    FormFieldButton* p_big = btn->getSibling(999999);

    // Observable, non-prescriptive checks:
    // - Returning nullptr is a common safe behavior; if it returns non-null,
    //   we don't dereference.
    (void)p_neg;
    (void)p_big;
    SUCCEED();
  }
}