// File: test_xref_geterrorcode_259.cpp
// Unit tests for XRef::getErrorCode() based strictly on the observable interface.
//
// The TEST_ID is 259

#include <gtest/gtest.h>

// Try common include paths used in this project layout.
#if __has_include("poppler/XRef.h")
#include "poppler/XRef.h"
#elif __has_include("XRef.h")
#include "XRef.h"
#else
#include "../poppler/XRef.h"
#endif

namespace {

class XRefTest_259 : public ::testing::Test {};

TEST_F(XRefTest_259, GetErrorCode_CanBeCalledOnNonConstInstance_259) {
  XRef xref;
  // Observable behavior: method is callable and returns an int.
  const int code = xref.getErrorCode();
  (void)code;

  // Calling again should be safe; we only assert self-consistency (no assumptions about value).
  EXPECT_EQ(xref.getErrorCode(), xref.getErrorCode());
}

TEST_F(XRefTest_259, GetErrorCode_CanBeCalledOnConstInstance_259) {
  const XRef xref;
  const int code = xref.getErrorCode();
  (void)code;

  // Self-consistency on const object as well.
  EXPECT_EQ(xref.getErrorCode(), xref.getErrorCode());
}

TEST_F(XRefTest_259, GetErrorCode_DoesNotModifyValueUnderRepeatedCalls_259) {
  XRef xref;

  const int first = xref.getErrorCode();
  const int second = xref.getErrorCode();
  const int third = xref.getErrorCode();

  // We cannot infer what the code should be, but repeated calls (with no other interactions)
  // should not produce different results.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

}  // namespace