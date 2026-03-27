// TEST_ID: 924
#include <gtest/gtest.h>

#include "poppler/Form.h"

#include <set>
#include <utility>

class FormFieldSignatureTest_924 : public ::testing::Test {
protected:
  // Helper to build a minimally-initialized instance using the public constructor.
  // We intentionally avoid relying on any internal behavior beyond successful construction.
  static FormFieldSignature MakeMinimal() {
    PDFDoc *doc = nullptr;
    Object dict;                 // default-constructed Object
    Ref ref = Ref::INVALID();    // sentinel invalid ref is part of the public API
    FormField *parent = nullptr;
    auto usedParents = std::make_unique<std::set<int>>();

    // Constructor signature is part of the public interface in Form.h.
    return FormFieldSignature(doc, std::move(dict), ref, parent, usedParents.get());
  }
};

TEST_F(FormFieldSignatureTest_924, GetByteRangeReturnsNonNull_924) {
  auto sig = MakeMinimal();

  Object *br = sig.getByteRange();
  ASSERT_NE(br, nullptr);
}

TEST_F(FormFieldSignatureTest_924, GetByteRangeIsStableAcrossCalls_924) {
  auto sig = MakeMinimal();

  Object *br1 = sig.getByteRange();
  Object *br2 = sig.getByteRange();

  ASSERT_NE(br1, nullptr);
  ASSERT_NE(br2, nullptr);
  EXPECT_EQ(br1, br2);
}

TEST_F(FormFieldSignatureTest_924, GetByteRangeDoesNotThrow_924) {
  auto sig = MakeMinimal();

  EXPECT_NO_THROW({
    Object *br = sig.getByteRange();
    (void)br;
  });
}