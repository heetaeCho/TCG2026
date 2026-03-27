// Copyright (C) 2026
// Unit tests for poppler-structure-element.cc finalize behavior
//
// TEST_ID: 2517

#include <gtest/gtest.h>

#include <glib-object.h>

#include "poppler.h"
#include "poppler-private.h"

namespace {

class PopplerStructureElementTest_2517 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Ensure type system is initialized (safe no-op on modern GLib).
#if !GLIB_CHECK_VERSION(2, 36, 0)
    g_type_init();
#endif
  }

  static GObject* NewPlainGObject() {
    return G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  }

  static void WeakNotify(gpointer data, GObject* /*where_the_object_was*/) {
    *static_cast<bool*>(data) = true;
  }
};

// Normal operation: unref of PopplerStructureElement should drop exactly one ref
// on its associated document (which is a GObject).
TEST_F(PopplerStructureElementTest_2517, UnrefElementUnrefsDocumentExactlyOnce_2517) {
  // Create a "document" object we can observe destruction for.
  GObject* doc = NewPlainGObject();
  ASSERT_NE(doc, nullptr);

  bool doc_destroyed = false;
  g_object_weak_ref(doc, &WeakNotify, &doc_destroyed);

  // Bump refcount so that one unref in finalize should NOT destroy it yet.
  // This makes the test robust even if PopplerStructureElement holds/doesn't hold
  // an extra reference elsewhere; we verify one unref happens from finalize.
  g_object_ref(doc);  // now: at least 2 refs total

  // Create the structure element instance.
  PopplerStructureElement* elem_obj =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(elem_obj, nullptr);

  // Populate the internal document pointer (private struct).
  // The finalize() implementation unrefs poppler_structure_element->document.
  elem_obj->document = reinterpret_cast<PopplerDocument*>(doc);

  // When we drop our reference to the structure element, finalize should run and unref doc once.
  g_object_unref(elem_obj);

  // Document should still be alive because we kept an extra reference above.
  EXPECT_FALSE(doc_destroyed);

  // Now drop our remaining reference(s) to doc: it should be destroyed exactly now if finalize
  // performed the expected unref.
  g_object_unref(doc);

  EXPECT_TRUE(doc_destroyed);
}

// Boundary-ish: multiple structure elements each unref their own document reference.
// This verifies finalize interaction scales and doesn't "over-unref" unrelated documents.
TEST_F(PopplerStructureElementTest_2517, TwoElementsUnrefTwoDocumentsIndependently_2517) {
  GObject* doc1 = NewPlainGObject();
  GObject* doc2 = NewPlainGObject();
  ASSERT_NE(doc1, nullptr);
  ASSERT_NE(doc2, nullptr);

  bool doc1_destroyed = false;
  bool doc2_destroyed = false;
  g_object_weak_ref(doc1, &WeakNotify, &doc1_destroyed);
  g_object_weak_ref(doc2, &WeakNotify, &doc2_destroyed);

  // Ensure each doc survives exactly one unref from finalize.
  g_object_ref(doc1);
  g_object_ref(doc2);

  PopplerStructureElement* e1 =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  PopplerStructureElement* e2 =
      POPPLER_STRUCTURE_ELEMENT(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(e1, nullptr);
  ASSERT_NE(e2, nullptr);

  e1->document = reinterpret_cast<PopplerDocument*>(doc1);
  e2->document = reinterpret_cast<PopplerDocument*>(doc2);

  g_object_unref(e1);
  g_object_unref(e2);

  EXPECT_FALSE(doc1_destroyed);
  EXPECT_FALSE(doc2_destroyed);

  g_object_unref(doc1);
  EXPECT_TRUE(doc1_destroyed);
  EXPECT_FALSE(doc2_destroyed);

  g_object_unref(doc2);
  EXPECT_TRUE(doc2_destroyed);
}

}  // namespace