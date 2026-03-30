// TEST_ID: 925
#include <gtest/gtest.h>

#include <type_traits>
#include <vector>

#include "Form.h"

// These tests treat FormFieldSignature as a black box and verify only what is
// observable through the provided interface (getSignature()).

class FormFieldSignatureTest_925 : public ::testing::Test {};

TEST_F(FormFieldSignatureTest_925, GetSignatureReturnTypeIsConstVectorRef_925) {
  using RetT = decltype(std::declval<const FormFieldSignature&>().getSignature());
  static_assert(std::is_same_v<RetT, const std::vector<unsigned char>&>,
                "getSignature() must return 'const std::vector<unsigned char>&'");
  SUCCEED();
}

TEST_F(FormFieldSignatureTest_925, GetSignatureIsCallableOnConstObject_925) {
  // Compile-time check that the method is callable on a const object.
  (void)std::declval<const FormFieldSignature&>().getSignature();
  SUCCEED();
}

TEST_F(FormFieldSignatureTest_925, DefaultConstructedSignatureIsEmptyIfDefaultConstructible_925) {
  if constexpr (std::is_default_constructible_v<FormFieldSignature>) {
    FormFieldSignature field;
    const auto& sig = field.getSignature();
    EXPECT_TRUE(sig.empty());
    EXPECT_EQ(sig.size(), 0u);
  } else {
    GTEST_SKIP() << "FormFieldSignature is not default-constructible in this build.";
  }
}

TEST_F(FormFieldSignatureTest_925, GetSignatureReturnsStableReferenceAcrossCalls_925) {
  if constexpr (std::is_default_constructible_v<FormFieldSignature>) {
    FormFieldSignature field;

    const auto* p1 = &field.getSignature();
    const auto* p2 = &field.getSignature();

    // Observable property: both calls return a reference to the same object.
    EXPECT_EQ(p1, p2);
  } else {
    GTEST_SKIP() << "FormFieldSignature is not default-constructible in this build.";
  }
}

TEST_F(FormFieldSignatureTest_925, GetSignatureOnConstAndNonConstReferToSameInternalObject_925) {
  if constexpr (std::is_default_constructible_v<FormFieldSignature>) {
    FormFieldSignature field;

    const auto* p_nonconst = &field.getSignature();
    const FormFieldSignature& cref = field;
    const auto* p_const = &cref.getSignature();

    EXPECT_EQ(p_nonconst, p_const);
  } else {
    GTEST_SKIP() << "FormFieldSignature is not default-constructible in this build.";
  }
}