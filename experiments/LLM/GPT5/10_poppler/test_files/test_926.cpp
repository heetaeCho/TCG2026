// TEST_ID = 926
//
// Unit tests for FormFieldSignature::getSignatureType()
// File under test: ./TestProjects/poppler/poppler/Form.h
//
// NOTE:
// - These tests treat the implementation as a black box.
// - We only assert observable behavior via the public interface.
// - We avoid accessing any private state.

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler headers (paths may vary slightly in your build; adjust include paths as needed)
#include "Form.h"

namespace {

// Compile-time “interface contract” checks (no implementation assumptions).
TEST(FormFieldSignatureTest_926, GetSignatureType_ReturnTypeIsSignatureType_926)
{
  static_assert(std::is_same_v<decltype(std::declval<const FormFieldSignature &>().getSignatureType()),
                               CryptoSign::SignatureType>,
                "getSignatureType() must return CryptoSign::SignatureType by value");
  SUCCEED();
}

class FormFieldSignatureTest_926 : public ::testing::Test
{
protected:
  // Best-effort construction helper.
  // If the constructor is not usable in this unit-test context (e.g., requires a fully valid PDFDoc/Object),
  // we skip runtime behavioral tests rather than guessing internal requirements.
  static std::unique_ptr<FormFieldSignature> TryMake()
  {
    // The class under test is implemented elsewhere; we only use the public constructors.
    // Many Poppler objects require valid collaborators; this is a black-box best-effort setup.
    //
    // If your environment requires a real PDFDoc/Object/Ref, adapt this helper to build those
    // using existing Poppler APIs (still black-box).
    try {
      PDFDoc *doc = nullptr;
      Object dict; // default-constructed; moved into the ctor
      Ref ref = Ref::INVALID();
      FormField *parent = nullptr;
      std::set<int> usedParents;

      return std::make_unique<FormFieldSignature>(doc, std::move(dict), ref, parent, &usedParents);
    } catch (...) {
      return nullptr;
    }
  }
};

TEST_F(FormFieldSignatureTest_926, SetSignatureType_RoundTripsThroughGetter_926)
{
  auto field = TryMake();
  if (!field) {
    GTEST_SKIP() << "Unable to construct FormFieldSignature in this test environment.";
  }

  // Use only the public API: setSignatureType + getSignatureType.
  const auto original = field->getSignatureType();

  // Create a different enum value without assuming specific enumerators exist.
  // This remains a value of CryptoSign::SignatureType; we only validate round-trip storage behavior.
  const auto different = static_cast<CryptoSign::SignatureType>(static_cast<int>(original) + 1);

  field->setSignatureType(different);
  EXPECT_EQ(field->getSignatureType(), different);

  // Boundary-ish: set back to original and verify.
  field->setSignatureType(original);
  EXPECT_EQ(field->getSignatureType(), original);
}

TEST_F(FormFieldSignatureTest_926, GetSignatureType_CanBeCalledRepeatedly_926)
{
  auto field = TryMake();
  if (!field) {
    GTEST_SKIP() << "Unable to construct FormFieldSignature in this test environment.";
  }

  // Normal operation: repeated calls should be stable absent intervening setters.
  const auto v1 = field->getSignatureType();
  const auto v2 = field->getSignatureType();
  const auto v3 = field->getSignatureType();
  EXPECT_EQ(v1, v2);
  EXPECT_EQ(v2, v3);
}

TEST_F(FormFieldSignatureTest_926, SetSignatureType_IdempotentForSameValue_926)
{
  auto field = TryMake();
  if (!field) {
    GTEST_SKIP() << "Unable to construct FormFieldSignature in this test environment.";
  }

  const auto v = field->getSignatureType();
  field->setSignatureType(v);
  EXPECT_EQ(field->getSignatureType(), v);

  // Set again to the same value to ensure it remains unchanged.
  field->setSignatureType(v);
  EXPECT_EQ(field->getSignatureType(), v);
}

} // namespace