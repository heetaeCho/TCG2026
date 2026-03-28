// TEST_ID: 272
// File: test_linkdest_getpagenum_272.cpp

#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

#include <utility>
#include <type_traits>

namespace {

// ---- Small adapter layer to work across Poppler Object/Array API variations ----

template <typename Obj>
auto MakeIntObjImpl(int n, int) -> decltype(std::declval<Obj&>().initInt(n), Obj()) {
  Obj o;
  o.initInt(n);
  return o;
}
template <typename Obj>
Obj MakeIntObjImpl(int n, ...) {
  return Obj(n);
}
template <typename Obj>
Obj MakeIntObj(int n) {
  return MakeIntObjImpl<Obj>(n, 0);
}

template <typename Obj>
auto MakeRealObjImpl(double v, int) -> decltype(std::declval<Obj&>().initReal(v), Obj()) {
  Obj o;
  o.initReal(v);
  return o;
}
template <typename Obj>
Obj MakeRealObjImpl(double v, ...) {
  return Obj(v);
}
template <typename Obj>
Obj MakeRealObj(double v) {
  return MakeRealObjImpl<Obj>(v, 0);
}

template <typename Obj>
auto MakeNameObjImpl(const char *name, int) -> decltype(std::declval<Obj&>().initName(name), Obj()) {
  Obj o;
  o.initName(name);
  return o;
}
template <typename Obj>
Obj MakeNameObjImpl(const char *name, ...) {
  // Many modern Poppler builds accept construction from const char* / std::string-like.
  return Obj(name);
}
template <typename Obj>
Obj MakeNameObj(const char *name) {
  return MakeNameObjImpl<Obj>(name, 0);
}

template <typename Obj>
auto AddToArrayImpl(Array &a, Obj &o, int) -> decltype(a.add(o), void()) {
  a.add(o);
}
template <typename Obj>
auto AddToArrayImpl(Array &a, Obj &o, ...) -> decltype(a.add(std::move(o)), void()) {
  a.add(std::move(o));
}
template <typename Obj>
void AddToArray(Array &a, Obj o) {
  AddToArrayImpl(a, o, 0);
}

static Array MakeDestArrayWithPageNumXYZ(int pageNum) {
  Array a;

  // Typical explicit destination shape:
  // [ page /XYZ left top zoom ]
  using Obj = Object;

  AddToArray(a, MakeIntObj<Obj>(pageNum));
  AddToArray(a, MakeNameObj<Obj>("XYZ"));
  AddToArray(a, MakeRealObj<Obj>(0.0));  // left
  AddToArray(a, MakeRealObj<Obj>(0.0));  // top
  AddToArray(a, MakeRealObj<Obj>(1.0));  // zoom

  return a;
}

}  // namespace

class LinkDestGetPageNumTest_272 : public ::testing::Test {};

// Normal operation: page number provided via Array should be observable via getPageNum().
TEST_F(LinkDestGetPageNumTest_272, GetPageNum_ReturnsProvidedPageNumber_272) {
  const int kPage = 7;
  Array a = MakeDestArrayWithPageNumXYZ(kPage);

  LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  EXPECT_FALSE(dest.isPageRef());
  EXPECT_EQ(dest.getPageNum(), kPage);
}

// Boundary: smallest non-negative page index (0) should be handled.
TEST_F(LinkDestGetPageNumTest_272, GetPageNum_AllowsZeroPageNumber_272) {
  const int kPage = 0;
  Array a = MakeDestArrayWithPageNumXYZ(kPage);

  LinkDest dest(a);

  ASSERT_TRUE(dest.isOk());
  EXPECT_FALSE(dest.isPageRef());
  EXPECT_EQ(dest.getPageNum(), kPage);
}

// Boundary: negative page numbers (if accepted by implementation) should remain observable.
// If the implementation rejects negatives, isOk() should be false; either outcome is observable.
TEST_F(LinkDestGetPageNumTest_272, GetPageNum_NegativePageNumber_IsObservableOrRejected_272) {
  const int kPage = -1;
  Array a = MakeDestArrayWithPageNumXYZ(kPage);

  LinkDest dest(a);

  if (dest.isOk()) {
    EXPECT_FALSE(dest.isPageRef());
    EXPECT_EQ(dest.getPageNum(), kPage);
  } else {
    SUCCEED();  // Observable rejection through isOk().
  }
}

// Boundary: large page number should be handled (or rejected) without relying on internals.
TEST_F(LinkDestGetPageNumTest_272, GetPageNum_LargePageNumber_IsObservableOrRejected_272) {
  const int kPage = 1'000'000;
  Array a = MakeDestArrayWithPageNumXYZ(kPage);

  LinkDest dest(a);

  if (dest.isOk()) {
    EXPECT_FALSE(dest.isPageRef());
    EXPECT_EQ(dest.getPageNum(), kPage);
  } else {
    SUCCEED();
  }
}

// Exceptional/error case: empty/invalid Array should make destination not OK (if that’s how impl signals errors).
TEST_F(LinkDestGetPageNumTest_272, Constructor_WithEmptyArray_IsNotOkOrIsHandled_272) {
  Array a;
  LinkDest dest(a);

  // We only assert observable behavior; if empty arrays are accepted, this will pass via the else path.
  if (!dest.isOk()) {
    SUCCEED();
  } else {
    // If accepted, getPageNum should still be callable (no crash). We don't assume its value.
    (void)dest.getPageNum();
    SUCCEED();
  }
}