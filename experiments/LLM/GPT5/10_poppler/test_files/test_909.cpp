// FormFieldText_isComb_909_test.cc
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "Form.h" // ./TestProjects/poppler/poppler/Form.h

namespace {

// ---- Compile-time helpers (SFINAE) to keep the test robust across Poppler versions ----

template <typename T>
using iscomb_expr_t = decltype(std::declval<const T&>().isComb());

template <typename T, typename = void>
struct HasIsComb : std::false_type {};
template <typename T>
struct HasIsComb<T, std::void_t<iscomb_expr_t<T>>> : std::true_type {};

template <typename T, typename = void>
struct IsDefaultConstructible : std::false_type {};
template <typename T>
struct IsDefaultConstructible<T, std::void_t<decltype(T{})>> : std::true_type {};

// Some Poppler builds will have full FormFieldText with complex constructors; others (in trimmed
// harnesses) might be default-constructible. We try to construct only if possible; otherwise skip.
template <typename T>
T* TryDefaultNew() {
  if constexpr (IsDefaultConstructible<T>::value) {
    return new T{};
  } else {
    return nullptr;
  }
}

}  // namespace

class FormFieldTextTest_909 : public ::testing::Test {};

TEST_F(FormFieldTextTest_909, IsCombIsPresentAndReturnsBool_909) {
  static_assert(HasIsComb<FormFieldText>::value,
                "FormFieldText must provide isComb() const");

  // Requirement: test only based on the provided interface.
  // We only assert the observable signature/return type here.
  static_assert(std::is_same_v<decltype(std::declval<const FormFieldText&>().isComb()), bool>,
                "isComb() must return bool");
}

TEST_F(FormFieldTextTest_909, IsCombCallableOnConstObjectIfDefaultConstructible_909) {
  // If the harness provides a default constructor, we can do a minimal runtime check
  // without relying on internal state or constructor-side parsing.
  std::unique_ptr<FormFieldText> f(TryDefaultNew<FormFieldText>());
  if (!f) {
    GTEST_SKIP() << "FormFieldText is not default-constructible in this build; "
                    "constructor requires Poppler document/object dependencies.";
  }

  const FormFieldText& cf = *f;
  const bool v1 = cf.isComb();
  const bool v2 = cf.isComb();

  // Observable behavior: repeated calls should be stable for a const object.
  EXPECT_EQ(v1, v2);
}

TEST_F(FormFieldTextTest_909, IsCombDoesNotMutateObservableStateOnRepeatedCalls_909) {
  // Same idea as above, but explicitly emphasizes "no observable mutation".
  std::unique_ptr<FormFieldText> f(TryDefaultNew<FormFieldText>());
  if (!f) {
    GTEST_SKIP() << "FormFieldText is not default-constructible in this build.";
  }

  const bool before = f->isComb();
  const bool after = f->isComb();
  EXPECT_EQ(before, after);
}