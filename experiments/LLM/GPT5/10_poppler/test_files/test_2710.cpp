// File: HtmlOutputDev_checkPageSlice_2710_test.cc
#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/poppler/utils/HtmlOutputDev.h"

// The interface takes Page* and Annot* but we don't need real Poppler objects
// to test observable behavior for this black-box method.
struct Page {};
struct Annot {};

class HtmlOutputDevTest_2710 : public ::testing::Test {
protected:
  HtmlOutputDev dev;
};

// Normal operation: should return true regardless of inputs (as observable behavior).
TEST_F(HtmlOutputDevTest_2710, ReturnsTrueWithTypicalInputs_2710) {
  Page page;
  bool ok = dev.checkPageSlice(
      &page,
      72.0, 72.0,
      0,
      /*useMediaBox=*/true,
      /*crop=*/false,
      /*sliceX=*/0, /*sliceY=*/0, /*sliceW=*/100, /*sliceH=*/200,
      /*printing=*/false);
  EXPECT_TRUE(ok);
}

// Boundary: null Page* (if allowed by interface) should still be observable via return value.
TEST_F(HtmlOutputDevTest_2710, ReturnsTrueWithNullPagePointer_2710) {
  bool ok = dev.checkPageSlice(
      /*p=*/nullptr,
      72.0, 72.0,
      0,
      /*useMediaBox=*/false,
      /*crop=*/false,
      /*sliceX=*/0, /*sliceY=*/0, /*sliceW=*/0, /*sliceH=*/0,
      /*printing=*/false);
  EXPECT_TRUE(ok);
}

// Boundary: unusual DPI values and rotation.
TEST_F(HtmlOutputDevTest_2710, ReturnsTrueWithExtremeDPIAndRotation_2710) {
  Page page;
  bool ok = dev.checkPageSlice(
      &page,
      /*hDPI=*/0.0, /*vDPI=*/1e6,
      /*rotate=*/-90,
      /*useMediaBox=*/true,
      /*crop=*/true,
      /*sliceX=*/-1000, /*sliceY=*/-1000, /*sliceW=*/1, /*sliceH=*/1,
      /*printing=*/true);
  EXPECT_TRUE(ok);
}

// Boundary: very large slice dimensions.
TEST_F(HtmlOutputDevTest_2710, ReturnsTrueWithLargeSliceDimensions_2710) {
  Page page;
  bool ok = dev.checkPageSlice(
      &page,
      300.0, 300.0,
      360,
      /*useMediaBox=*/false,
      /*crop=*/true,
      /*sliceX=*/0, /*sliceY=*/0,
      /*sliceW=*/std::numeric_limits<int>::max(),
      /*sliceH=*/std::numeric_limits<int>::max(),
      /*printing=*/false);
  EXPECT_TRUE(ok);
}

// Exceptional/error cases (observable): provide callbacks that would fail if called.
// Since behavior is black-box, we only assert the method returns true and does not crash.
namespace {
bool AbortCheckShouldNotBeCalled(void * /*data*/) {
  // If this is called unexpectedly, fail the test.
  ADD_FAILURE() << "abortCheckCbk should not have been called (observable crash/interaction).";
  return true;
}

bool AnnotDisplayShouldNotBeCalled(Annot * /*annot*/, void * /*user_data*/) {
  ADD_FAILURE() << "annotDisplayDecideCbk should not have been called (observable crash/interaction).";
  return true;
}
}  // namespace

TEST_F(HtmlOutputDevTest_2710, ReturnsTrueWithNonNullCallbacksProvided_2710) {
  Page page;
  int dummy = 123;

  bool ok = dev.checkPageSlice(
      &page,
      96.0, 96.0,
      0,
      /*useMediaBox=*/true,
      /*crop=*/false,
      /*sliceX=*/10, /*sliceY=*/20, /*sliceW=*/30, /*sliceH=*/40,
      /*printing=*/false,
      /*abortCheckCbk=*/&AbortCheckShouldNotBeCalled,
      /*abortCheckCbkData=*/&dummy,
      /*annotDisplayDecideCbk=*/&AnnotDisplayShouldNotBeCalled,
      /*annotDisplayDecideCbkData=*/&dummy);

  EXPECT_TRUE(ok);
}

// Boundary: pass "weird" callback data pointers (including nullptr).
TEST_F(HtmlOutputDevTest_2710, ReturnsTrueWithNullCallbackDataPointers_2710) {
  Page page;

  bool ok = dev.checkPageSlice(
      &page,
      96.0, 96.0,
      0,
      /*useMediaBox=*/true,
      /*crop=*/false,
      /*sliceX=*/0, /*sliceY=*/0, /*sliceW=*/10, /*sliceH=*/10,
      /*printing=*/false,
      /*abortCheckCbk=*/&AbortCheckShouldNotBeCalled,
      /*abortCheckCbkData=*/nullptr,
      /*annotDisplayDecideCbk=*/&AnnotDisplayShouldNotBeCalled,
      /*annotDisplayDecideCbkData=*/nullptr);

  EXPECT_TRUE(ok);
}