// TEST_ID: 938
// File: test_ocgs_938.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// Poppler headers (project-local path in prompt)
#include "poppler/OptionalContent.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

namespace {

class OCGsTest_938 : public ::testing::Test {};

TEST_F(OCGsTest_938, Traits_CopyAndAssignDeleted_938) {
  static_assert(!std::is_copy_constructible_v<OCGs>,
                "OCGs must not be copy constructible (deleted copy ctor)");
  static_assert(!std::is_copy_assignable_v<OCGs>,
                "OCGs must not be copy assignable (deleted operator=)");
}

TEST_F(OCGsTest_938, Interface_IsOkSignature_938) {
  // Verify signature: bool (OCGs::*)() const
  using IsOkPtr = bool (OCGs::*)() const;
  static_assert(std::is_same_v<decltype(&OCGs::isOk), IsOkPtr>,
                "OCGs::isOk must be 'bool isOk() const'");
}

TEST_F(OCGsTest_938, ConstructWithDefaultObjectAndNullXRef_DoesNotThrow_938) {
  Object ocgObject;  // default/null object
  XRef* xref = nullptr;

  // We only verify observable behavior: construction succeeds (no exception),
  // and public methods are callable.
  EXPECT_NO_THROW({
    OCGs ocgs(ocgObject, xref);
    (void)ocgs.isOk();
  });
}

TEST_F(OCGsTest_938, IsOkIsCallableOnConstAndIdempotent_938) {
  Object ocgObject;  // default/null object
  XRef* xref = nullptr;

  OCGs ocgs(ocgObject, xref);

  const OCGs& cocgs = ocgs;
  const bool v1 = cocgs.isOk();
  const bool v2 = cocgs.isOk();
  EXPECT_EQ(v1, v2) << "isOk() should be stable across repeated calls on the same object";
}

TEST_F(OCGsTest_938, IsOkMatchesBetweenConstAndNonConstViews_938) {
  Object ocgObject;  // default/null object
  XRef* xref = nullptr;

  OCGs ocgs(ocgObject, xref);

  const bool nonConstValue = ocgs.isOk();
  const OCGs& cocgs = ocgs;
  const bool constValue = cocgs.isOk();

  EXPECT_EQ(nonConstValue, constValue);
}

}  // namespace