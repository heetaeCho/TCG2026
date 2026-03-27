// FormFieldSignature_setSignatureType_927_test.cc
#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "Form.h"

// Helper: create a FormFieldSignature instance if the build exposes a usable constructor.
// If none is available in this build configuration, tests will be skipped at runtime.
static std::unique_ptr<FormFieldSignature> MakeFormFieldSignature_927() {
  if constexpr (std::is_default_constructible_v<FormFieldSignature>) {
    return std::make_unique<FormFieldSignature>();
  } else if constexpr (std::is_constructible_v<FormFieldSignature, PDFDoc*, Object&&, Ref, FormField*, std::set<int>*>) {
    Object dict;
    return std::make_unique<FormFieldSignature>(
        static_cast<PDFDoc*>(nullptr), std::move(dict), Ref::INVALID(), static_cast<FormField*>(nullptr),
        static_cast<std::set<int>*>(nullptr));
  } else if constexpr (std::is_constructible_v<FormFieldSignature, PDFDoc*, Object&&, Ref, FormField*, int*>) {
    Object dict;
    int usedParents = 0;
    return std::make_unique<FormFieldSignature>(
        static_cast<PDFDoc*>(nullptr), std::move(dict), Ref::INVALID(), static_cast<FormField*>(nullptr), &usedParents);
  } else {
    return nullptr;
  }
}

class FormFieldSignatureTest_927 : public ::testing::Test {};

TEST_F(FormFieldSignatureTest_927, SetSignatureType_IsInvocable_927) {
  static_assert(std::is_invocable_r_v<void, decltype(&FormFieldSignature::setSignatureType),
                                      FormFieldSignature*, CryptoSign::SignatureType>,
                "setSignatureType must be callable with (CryptoSign::SignatureType) and return void.");
}

TEST_F(FormFieldSignatureTest_927, DefaultSignatureType_IsUnsignedIfAvailable_927) {
  auto sig = MakeFormFieldSignature_927();
  if (!sig) {
    GTEST_SKIP() << "No accessible FormFieldSignature constructor in this build; skipping runtime checks.";
  }

  // Observable behavior through the public getter (if present in this build).
  if constexpr (requires(const FormFieldSignature& s) { s.getSignatureType(); }) {
    EXPECT_EQ(sig->getSignatureType(), CryptoSign::SignatureType::unsigned_signature_field);
  } else {
    GTEST_SKIP() << "getSignatureType() not available in this build; cannot observe the stored signature type.";
  }
}

TEST_F(FormFieldSignatureTest_927, SetSignatureType_ToUnsigned_ReflectsInGetter_927) {
  auto sig = MakeFormFieldSignature_927();
  if (!sig) {
    GTEST_SKIP() << "No accessible FormFieldSignature constructor in this build; skipping runtime checks.";
  }

  if constexpr (requires(const FormFieldSignature& s) { s.getSignatureType(); }) {
    sig->setSignatureType(CryptoSign::SignatureType::unsigned_signature_field);
    EXPECT_EQ(sig->getSignatureType(), CryptoSign::SignatureType::unsigned_signature_field);
  } else {
    GTEST_SKIP() << "getSignatureType() not available in this build; cannot observe the stored signature type.";
  }
}

TEST_F(FormFieldSignatureTest_927, SetSignatureType_CanBeCalledRepeatedly_927) {
  auto sig = MakeFormFieldSignature_927();
  if (!sig) {
    GTEST_SKIP() << "No accessible FormFieldSignature constructor in this build; skipping runtime checks.";
  }

  // Boundary-style check: repeated calls should be safe and not require any additional setup.
  EXPECT_NO_THROW(sig->setSignatureType(CryptoSign::SignatureType::unsigned_signature_field));
  EXPECT_NO_THROW(sig->setSignatureType(CryptoSign::SignatureType::unsigned_signature_field));

  if constexpr (requires(const FormFieldSignature& s) { s.getSignatureType(); }) {
    EXPECT_EQ(sig->getSignatureType(), CryptoSign::SignatureType::unsigned_signature_field);
  }
}