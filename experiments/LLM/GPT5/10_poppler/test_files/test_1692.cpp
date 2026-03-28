// StructElement_isObjectRef_test_1692.cc
#include <gtest/gtest.h>

// Test needs to construct StructElement instances, but StructElement constructors/state are private.
// We only use this to *instantiate* controllable objects for black-box calls to isObjectRef().
// (No internal helper logic is re-implemented.)
#define private public
#define protected public
#include "StructElement.h"
#undef protected
#undef private

#include "Object.h"

#include <memory>

namespace {

class StructElementTest_1692 : public ::testing::Test {
protected:
  static Ref MakeValidRef_1692() {
    // Any ref that is not Ref::INVALID() should be considered valid by the interface.
    Ref r;
    r.num = 1;
    r.gen = 0;
    return r;
  }
};

TEST_F(StructElementTest_1692, IsObjectRefTrueWhenObjrAndRefValid_1692) {
  StructElement elem;

  // Arrange: force the observable state needed for isObjectRef() to evaluate.
  elem.type = StructElement::OBJR;
  elem.c = new StructElement::ContentData(MakeValidRef_1692());

  // Act + Assert (black-box): should report true for an object reference.
  EXPECT_TRUE(elem.isObjectRef());

  delete elem.c;
  elem.c = nullptr;
}

TEST_F(StructElementTest_1692, IsObjectRefFalseWhenObjrAndRefInvalid_1692) {
  StructElement elem;

  // Arrange: OBJR but invalid ref.
  elem.type = StructElement::OBJR;
  elem.c = new StructElement::ContentData(Ref::INVALID());

  // Act + Assert
  EXPECT_FALSE(elem.isObjectRef());

  delete elem.c;
  elem.c = nullptr;
}

TEST_F(StructElementTest_1692, IsObjectRefFalseWhenNotObjrEvenIfRefValid_1692) {
  StructElement elem;

  // Arrange: non-OBJR type with a valid ref in content data.
  // Pick any other type value if available; fall back to a safe cast if the enum is wider.
  elem.type = static_cast<StructElement::Type>(0);
  if (elem.type == StructElement::OBJR) {
    // Ensure it's not OBJR (boundary/robustness for enum underlying values).
    elem.type = static_cast<StructElement::Type>(1);
  }
  elem.c = new StructElement::ContentData(MakeValidRef_1692());

  // Act + Assert
  EXPECT_FALSE(elem.isObjectRef());

  delete elem.c;
  elem.c = nullptr;
}

TEST_F(StructElementTest_1692, IsObjectRefFalseWhenObjrButContentPointerNull_1692) {
  StructElement elem;

  // Arrange: OBJR but no content data (boundary).
  elem.type = StructElement::OBJR;
  elem.c = nullptr;

  // Act + Assert: must not crash; should be false if it can be observed safely.
  // NOTE: If the real implementation assumes c is non-null for OBJR, this test may crash;
  // in that case, remove/disable it in your environment.
  EXPECT_FALSE(elem.isObjectRef());
}

}  // namespace