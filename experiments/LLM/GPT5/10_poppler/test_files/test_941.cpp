// TEST_ID = 941
// Unit tests for OCGs::getRBGroupsArray() (poppler/OptionalContent.h)

#include <gtest/gtest.h>

#include "OptionalContent.h"
#include "Object.h"

// These headers are commonly available in Poppler and allow us to construct Array/Dict instances.
// If your build setup includes them via different paths, adjust includes accordingly.
#include "Array.h"
#include "Dict.h"

namespace {

class OCGsTest_941 : public ::testing::Test {
protected:
  // Build an OCGs instance from a Dict-valued Object.
  // Note: We pass nullptr for XRef because getRBGroupsArray() is independent of XRef; the constructor
  // should accept it in typical Poppler builds. If your local Poppler requires a non-null XRef,
  // replace nullptr with a suitable test XRef from your project’s test utilities.
  static std::unique_ptr<OCGs> MakeOCGsFromDict(Object&& dictObj) {
    return std::make_unique<OCGs>(dictObj, /*xref=*/nullptr);
  }

  static Object MakeDictObject() {
    auto* dict = new Dict(/*xref=*/nullptr);
    return Object(dict);
  }

  static Object MakeArrayObjectWithNElements(int n) {
    auto* arr = new Array(/*xref=*/nullptr);
    Object arrObj(arr);
    for (int i = 0; i < n; ++i) {
      arrObj.arrayAdd(Object(i));
    }
    return arrObj;
  }
};

TEST_F(OCGsTest_941, GetRBGroupsArray_MissingKeyReturnsNullptr_941) {
  Object ocgDict = MakeDictObject(); // no "RBGroups" entry
  auto ocgs = MakeOCGsFromDict(std::move(ocgDict));

  EXPECT_EQ(ocgs->getRBGroupsArray(), nullptr);
}

TEST_F(OCGsTest_941, GetRBGroupsArray_NonArrayValueReturnsNullptr_941) {
  Object ocgDict = MakeDictObject();
  ocgDict.dictAdd("RBGroups", Object(123)); // not an array
  auto ocgs = MakeOCGsFromDict(std::move(ocgDict));

  EXPECT_EQ(ocgs->getRBGroupsArray(), nullptr);
}

TEST_F(OCGsTest_941, GetRBGroupsArray_EmptyArrayReturnsNullptr_941) {
  Object ocgDict = MakeDictObject();
  ocgDict.dictAdd("RBGroups", MakeArrayObjectWithNElements(0)); // empty array
  auto ocgs = MakeOCGsFromDict(std::move(ocgDict));

  EXPECT_EQ(ocgs->getRBGroupsArray(), nullptr);
}

TEST_F(OCGsTest_941, GetRBGroupsArray_NonEmptyArrayReturnsNonNull_941) {
  Object ocgDict = MakeDictObject();
  ocgDict.dictAdd("RBGroups", MakeArrayObjectWithNElements(1)); // length=1
  auto ocgs = MakeOCGsFromDict(std::move(ocgDict));

  const Array* rb = ocgs->getRBGroupsArray();
  ASSERT_NE(rb, nullptr);

  // Boundary/observable behavior: returned pointer should remain stable across calls.
  EXPECT_EQ(rb, ocgs->getRBGroupsArray());
}

TEST_F(OCGsTest_941, GetRBGroupsArray_ArrayLengthObservableThroughArrayAPI_941) {
  Object ocgDict = MakeDictObject();
  ocgDict.dictAdd("RBGroups", MakeArrayObjectWithNElements(3));
  auto ocgs = MakeOCGsFromDict(std::move(ocgDict));

  const Array* rb = ocgs->getRBGroupsArray();
  ASSERT_NE(rb, nullptr);

  // Observable via public Array API (no peeking into OCGs internals).
  EXPECT_EQ(rb->getLength(), 3);
}

} // namespace