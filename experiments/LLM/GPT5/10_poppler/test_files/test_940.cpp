// TEST_ID: 940
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "poppler/OptionalContent.h"
#include "poppler/Object.h"

namespace {

static Dict *NewDict(XRef *xref)
{
  if constexpr (std::is_constructible_v<Dict, XRef *>) {
    return new Dict(xref);
  } else if constexpr (std::is_default_constructible_v<Dict>) {
    (void)xref;
    return new Dict();
  } else {
    // If this fails to compile, the project likely provides a different Dict ctor.
    // Adjust this helper to match your local poppler build.
    return nullptr;
  }
}

static Array *NewArray(XRef *xref)
{
  if constexpr (std::is_constructible_v<Array, XRef *>) {
    return new Array(xref);
  } else if constexpr (std::is_default_constructible_v<Array>) {
    (void)xref;
    return new Array();
  } else {
    // If this fails to compile, the project likely provides a different Array ctor.
    // Adjust this helper to match your local poppler build.
    return nullptr;
  }
}

static Object MakeEmptyArrayObject(XRef *xref)
{
  Array *arr = NewArray(xref);
  EXPECT_NE(arr, nullptr);
  return Object(arr);
}

static Object MakeArrayObjectWithOneInt(XRef *xref, int v)
{
  Object arrObj = MakeEmptyArrayObject(xref);
  arrObj.arrayAdd(Object(v));
  return arrObj;
}

static Object MakeDictObject(XRef *xref)
{
  Dict *dict = NewDict(xref);
  EXPECT_NE(dict, nullptr);
  return Object(dict);
}

// Builds an ocgObject dictionary that mirrors the keys OCGs is expected to look up:
// - "OCGs": an array (can be empty)
// - "D": a dict containing "Order" and/or other keys
static Object MakeOCPropertiesObjectWithD(Object &&dDict, XRef *xref)
{
  Object root = MakeDictObject(xref);
  root.dictAdd("OCGs", MakeEmptyArrayObject(xref)); // keep it structurally valid
  root.dictAdd("D", std::move(dDict));
  return root;
}

} // namespace

class OCGsTest_940 : public ::testing::Test {
protected:
  XRef *xref_ = nullptr; // tests use nullptr; OCGs should tolerate it if implementation does.
};

TEST_F(OCGsTest_940, GetOrderArray_ReturnsNull_WhenNoDefaultConfigDict_940)
{
  Object root = MakeDictObject(xref_);
  root.dictAdd("OCGs", MakeEmptyArrayObject(xref_));

  OCGs ocgs(root, xref_);
  EXPECT_EQ(ocgs.getOrderArray(), nullptr);
}

TEST_F(OCGsTest_940, GetOrderArray_ReturnsNull_WhenOrderMissing_940)
{
  Object d = MakeDictObject(xref_);
  Object root = MakeOCPropertiesObjectWithD(std::move(d), xref_);

  OCGs ocgs(root, xref_);
  EXPECT_EQ(ocgs.getOrderArray(), nullptr);
}

TEST_F(OCGsTest_940, GetOrderArray_ReturnsNull_WhenOrderIsNotArray_940)
{
  Object d = MakeDictObject(xref_);
  d.dictAdd("Order", Object(123)); // not an array
  Object root = MakeOCPropertiesObjectWithD(std::move(d), xref_);

  OCGs ocgs(root, xref_);
  EXPECT_EQ(ocgs.getOrderArray(), nullptr);
}

TEST_F(OCGsTest_940, GetOrderArray_ReturnsNull_WhenOrderArrayIsEmpty_940)
{
  Object d = MakeDictObject(xref_);
  d.dictAdd("Order", MakeEmptyArrayObject(xref_)); // empty array
  Object root = MakeOCPropertiesObjectWithD(std::move(d), xref_);

  OCGs ocgs(root, xref_);
  EXPECT_EQ(ocgs.getOrderArray(), nullptr);
}

TEST_F(OCGsTest_940, GetOrderArray_ReturnsNonNull_WhenOrderArrayHasAtLeastOneElement_940)
{
  Object d = MakeDictObject(xref_);
  d.dictAdd("Order", MakeArrayObjectWithOneInt(xref_, 1)); // non-empty array
  Object root = MakeOCPropertiesObjectWithD(std::move(d), xref_);

  OCGs ocgs(root, xref_);
  EXPECT_NE(ocgs.getOrderArray(), nullptr);
}