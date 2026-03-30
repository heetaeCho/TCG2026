// FormFieldChoice_isListBox_922_test.cc
// Unit tests for FormFieldChoice::isListBox()
// TEST_ID: 922

#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Form.h"

#include <type_traits>
#include <utility>

namespace {

// ---- Construction helpers (try to build a FormFieldChoice without assuming internals) ----
//
// We attempt a few construction strategies at compile time.
// If none match in your build, you’ll get a clear static_assert message.
//
// NOTE: We intentionally avoid guessing PDF structures or parsing behavior.
// We only need an instance to call public methods.

template <typename T>
constexpr bool kDefaultConstructible = std::is_default_constructible_v<T>;

template <typename T>
auto MakeChoiceImpl(int) -> std::enable_if_t<kDefaultConstructible<T>, T> {
  return T{};
}

// Try the common Poppler ctor signature if available.
// We only pass value-initialized placeholders / nullptrs to satisfy the signature;
// tests are about isListBox(), not PDF parsing.
template <typename T>
auto MakeChoiceImpl(long) -> std::enable_if_t<
    std::is_constructible_v<T,
                           PDFDoc*,
                           Object&&,
                           Ref,
                           FormField*,
                           std::set<int>*>,
    T> {
  PDFDoc* doc = nullptr;
  Object obj;           // value-initialized
  Ref ref{};            // value-initialized
  FormField* parent = nullptr;
  std::set<int>* usedParents = nullptr;
  return T(doc, std::move(obj), ref, parent, usedParents);
}

// Fallback: if another ctor exists with (PDFDoc*, Object&&, Ref, FormField*, int*).
template <typename T>
auto MakeChoiceImpl(char) -> std::enable_if_t<
    std::is_constructible_v<T,
                           PDFDoc*,
                           Object&&,
                           Ref,
                           FormField*,
                           int*>,
    T> {
  PDFDoc* doc = nullptr;
  Object obj;
  Ref ref{};
  FormField* parent = nullptr;
  int* usedParents = nullptr;
  return T(doc, std::move(obj), ref, parent, usedParents);
}

template <typename T>
T MakeChoice() {
  if constexpr (kDefaultConstructible<T>) {
    return MakeChoiceImpl<T>(0);
  } else if constexpr (std::is_constructible_v<T,
                                               PDFDoc*,
                                               Object&&,
                                               Ref,
                                               FormField*,
                                               std::set<int>*>) {
    return MakeChoiceImpl<T>(0L);
  } else if constexpr (std::is_constructible_v<T,
                                               PDFDoc*,
                                               Object&&,
                                               Ref,
                                               FormField*,
                                               int*>) {
    return MakeChoiceImpl<T>(static_cast<char>(0));
  } else {
    static_assert(sizeof(T) == 0,
                  "FormFieldChoice is not constructible by the test harness. "
                  "Add another MakeChoiceImpl overload matching an available public constructor.");
  }
}

// ---- Feature-detection helpers ----
template <typename T>
constexpr bool HasIsCombo() {
  return requires(const T& t) {
    { t.isCombo() } -> std::convertible_to<bool>;
  };
}

// If isCombo() is available, we can verify the observable relationship
// without touching internal/protected state.
template <typename T>
void ExpectListBoxMatchesNotCombo(const T& c) {
  ASSERT_TRUE(HasIsCombo<T>())
      << "Internal test error: called ExpectListBoxMatchesNotCombo without isCombo().";
  EXPECT_EQ(c.isListBox(), !c.isCombo());
}

class FormFieldChoiceTest_922 : public ::testing::Test {};

}  // namespace

TEST_F(FormFieldChoiceTest_922, IsListBox_IsCallableOnConstObject_922) {
  const auto choice = MakeChoice<FormFieldChoice>();
  (void)choice.isListBox();  // should compile and be callable on const
  SUCCEED();
}

TEST_F(FormFieldChoiceTest_922, IsListBox_IsDeterministicAcrossRepeatedCalls_922) {
  const auto choice = MakeChoice<FormFieldChoice>();
  const bool first = choice.isListBox();
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(choice.isListBox(), first);
  }
}

TEST_F(FormFieldChoiceTest_922, IsListBox_ConsistentWithIsCombo_WhenAvailable_922) {
  const auto choice = MakeChoice<FormFieldChoice>();

  if constexpr (HasIsCombo<FormFieldChoice>()) {
    ExpectListBoxMatchesNotCombo(choice);
  } else {
    // If the build doesn’t expose isCombo(), we can’t assert more than
    // basic callability/determinism from the public interface provided.
    SUCCEED();
  }
}

TEST_F(FormFieldChoiceTest_922, IsListBox_DoesNotThrow_922) {
  const auto choice = MakeChoice<FormFieldChoice>();
  EXPECT_NO_THROW({
    volatile bool v = choice.isListBox();
    (void)v;
  });
}