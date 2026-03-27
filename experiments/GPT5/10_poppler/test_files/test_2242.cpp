// get_optional_content_items_sorted_test_2242.cc
//
// NOTE:
// This test file directly includes the implementation file
//   ./TestProjects/poppler/glib/poppler-document.cc
// in order to access the file-local (static) function under test.
// The build system should ensure poppler-document.cc is NOT compiled
// separately into the same test binary, to avoid ODR/multiple-definition
// issues.

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler/Array.h"
#include "poppler/Object.h"
#include "poppler/OptionalContent.h"

// Include the private Layer definition used by the implementation.
#include "glib/poppler-private.h"

// Include the implementation to access the static function.
#include "glib/poppler-document.cc"

namespace {

class GetOptionalContentItemsSortedTest_2242 : public ::testing::Test {
protected:
  // Helper: create a Poppler Array with nullptr XRef (sufficient for these tests).
  static Array *NewArray() { return new Array(/*xrefA=*/nullptr); }

  static Object ObjString(const char *s) {
    // Object has constructors for std::string rvalue.
    return Object(std::string(s));
  }

  static Object ObjArray(Array *a) { return Object(a); }

  static int ListLength(GList *l) { return static_cast<int>(g_list_length(l)); }

  // Helper to fetch the Layer* at index i from a GList.
  static Layer *NthLayer(GList *l, int i) {
    GList *n = g_list_nth(l, static_cast<guint>(i));
    return n ? static_cast<Layer *>(n->data) : nullptr;
  }
};

// Normal / boundary: empty order yields empty list (nullptr).
TEST_F(GetOptionalContentItemsSortedTest_2242, EmptyOrderReturnsNullList_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  Array *order = NewArray();
  ASSERT_NE(order, nullptr);
  EXPECT_EQ(order->getLength(), 0);

  GList *items = get_optional_content_items_sorted(&ocgs, /*parent=*/nullptr, order);
  EXPECT_EQ(items, nullptr);

  delete order;
}

// Normal operation: a non-empty nested array triggers creation of a placeholder Layer
// when parent == nullptr, and a label inside the nested array sets the placeholder label.
TEST_F(GetOptionalContentItemsSortedTest_2242, NestedArrayCreatesPlaceholderAndSetsLabel_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  // Build: order = [ [ "LayerLabel" ] ]
  Array *inner = NewArray();
  inner->add(ObjString("LayerLabel"));

  Array *order = NewArray();
  order->add(ObjArray(inner));

  GList *items = get_optional_content_items_sorted(&ocgs, /*parent=*/nullptr, order);

  ASSERT_NE(items, nullptr);
  EXPECT_EQ(ListLength(items), 1);

  Layer *layer = NthLayer(items, 0);
  ASSERT_NE(layer, nullptr);
  // Observable effect through public struct field.
  EXPECT_NE(layer->label, nullptr);

  // Cleanup list container (Layer objects are owned by production code; avoid assuming freeing API).
  g_list_free(items);

  delete order; // deletes only container, not owned elements; ok for this black-box test harness.
  // NOTE: inner is now owned by Object/Array per poppler's object model; do not double free.
}

// Normal operation: multiple nested arrays create multiple placeholder layers preserving order.
TEST_F(GetOptionalContentItemsSortedTest_2242, MultipleNestedArraysPreserveOrder_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  // order = [ [ "A" ], [ "B" ] ]
  Array *innerA = NewArray();
  innerA->add(ObjString("A"));

  Array *innerB = NewArray();
  innerB->add(ObjString("B"));

  Array *order = NewArray();
  order->add(ObjArray(innerA));
  order->add(ObjArray(innerB));

  GList *items = get_optional_content_items_sorted(&ocgs, /*parent=*/nullptr, order);

  ASSERT_NE(items, nullptr);
  EXPECT_EQ(ListLength(items), 2);

  Layer *first = NthLayer(items, 0);
  Layer *second = NthLayer(items, 1);
  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);

  // Both should have labels assigned by the inner arrays.
  EXPECT_NE(first->label, nullptr);
  EXPECT_NE(second->label, nullptr);

  g_list_free(items);
  delete order;
}

// Boundary: an empty nested array (length == 0) should be ignored (no placeholder created).
TEST_F(GetOptionalContentItemsSortedTest_2242, EmptyNestedArrayIsIgnored_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  // order = [ [ ] ]  (inner length 0)
  Array *innerEmpty = NewArray();

  Array *order = NewArray();
  order->add(ObjArray(innerEmpty));

  GList *items = get_optional_content_items_sorted(&ocgs, /*parent=*/nullptr, order);

  // With only an empty array item, nothing should be created.
  EXPECT_EQ(items, nullptr);

  delete order;
}

// Boundary/normal: when parent is provided, a top-level string sets the parent's label
// and does not create list items.
TEST_F(GetOptionalContentItemsSortedTest_2242, TopLevelStringSetsParentLabelWithoutCreatingItems_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  Array *order = NewArray();
  order->add(ObjString("ParentLabel"));

  // Create a parent Layer without relying on internal constructors.
  Layer *parent = static_cast<Layer *>(g_malloc0(sizeof(Layer)));
  ASSERT_NE(parent, nullptr);
  EXPECT_EQ(parent->label, nullptr);

  GList *items = get_optional_content_items_sorted(&ocgs, parent, order);

  // No dict/array items => no list nodes expected.
  EXPECT_EQ(items, nullptr);

  // Observable: parent label set.
  EXPECT_NE(parent->label, nullptr);

  g_free(parent);
  delete order;
}

// Exceptional/error case (observable): If parent is nullptr and the first encountered
// top-level item is a string, the function dereferences last_item->label and may crash.
// We verify this behavior with a death test.
TEST_F(GetOptionalContentItemsSortedTest_2242, StringWithNullParentCanCrash_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  Array *order = NewArray();
  order->add(ObjString("OrphanString"));

#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH(
      {
        (void)get_optional_content_items_sorted(&ocgs, /*parent=*/nullptr, order);
      },
      ".*");
#else
  // If death tests are unavailable in this environment, at least exercise the call
  // in a way that doesn't fail compilation.
  (void)ocgs;
#endif

  delete order;
}

// Exceptional/error case (observable): A string after a nested array can also be unsafe
// because the nested-array path sets last_item to nullptr before continuing.
TEST_F(GetOptionalContentItemsSortedTest_2242, StringAfterNestedArrayCanCrash_2242) {
  Object ocgObj = Object::null();
  OCGs ocgs(ocgObj, /*xref=*/nullptr);

  // order = [ [ "A" ], "B" ]
  Array *innerA = NewArray();
  innerA->add(ObjString("A"));

  Array *order = NewArray();
  order->add(ObjArray(innerA));
  order->add(ObjString("B"));

#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH(
      {
        (void)get_optional_content_items_sorted(&ocgs, /*parent=*/nullptr, order);
      },
      ".*");
#else
  (void)ocgs;
#endif

  delete order;
}

} // namespace