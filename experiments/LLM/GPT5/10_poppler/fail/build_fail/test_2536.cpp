// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for poppler_structure_element_iter_free
// TEST_ID: 2536

#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

extern "C" {
// Include the implementation to access the real PopplerStructureElementIter
// definition used by poppler_structure_element_iter_free().
#include "./TestProjects/poppler/glib/poppler-structure-element.cc"
}

namespace {

// A tiny GObject subclass that increments a counter when finalized, so we can
// observe whether poppler_structure_element_iter_free() unrefs iter->document.
static gint g_finalize_count_2536 = 0;

typedef struct _FinalizeCounterObject2536 {
  GObject parent_instance;
} FinalizeCounterObject2536;

typedef struct _FinalizeCounterObject2536Class {
  GObjectClass parent_class;
} FinalizeCounterObject2536Class;

G_DEFINE_TYPE(FinalizeCounterObject2536, finalize_counter_object_2536, G_TYPE_OBJECT)

static void finalize_counter_object_2536_finalize(GObject* object) {
  g_atomic_int_inc(&g_finalize_count_2536);
  G_OBJECT_CLASS(finalize_counter_object_2536_parent_class)->finalize(object);
}

static void finalize_counter_object_2536_class_init(FinalizeCounterObject2536Class* klass) {
  GObjectClass* gobject_class = G_OBJECT_CLASS(klass);
  gobject_class->finalize = finalize_counter_object_2536_finalize;
}

static void finalize_counter_object_2536_init(FinalizeCounterObject2536*) {}

class PopplerStructureElementIterFreeTest_2536 : public ::testing::Test {
 protected:
  void SetUp() override { g_atomic_int_set(&g_finalize_count_2536, 0); }
  void TearDown() override {}

  static GObject* NewCounterObject() {
    return G_OBJECT(g_object_new(finalize_counter_object_2536_get_type(), nullptr));
  }
};

}  // namespace

TEST_F(PopplerStructureElementIterFreeTest_2536, NullptrDoesNothing_2536) {
  // Boundary: freeing a nullptr should be a no-op and must not crash.
  poppler_structure_element_iter_free(nullptr);
  EXPECT_EQ(g_atomic_int_get(&g_finalize_count_2536), 0);
}

TEST_F(PopplerStructureElementIterFreeTest_2536, UnrefsDocumentAndFinalizesWhenSoleOwner_2536) {
  // Normal: if iter holds the only reference to document, freeing iter should
  // unref document and allow it to finalize.
  PopplerStructureElementIter* iter = g_slice_new0(PopplerStructureElementIter);
  ASSERT_NE(iter, nullptr);

  GObject* doc = NewCounterObject();
  ASSERT_NE(doc, nullptr);

  // iter takes ownership of this reference (typical pattern for stored members).
  iter->document = doc;

  EXPECT_EQ(g_atomic_int_get(&g_finalize_count_2536), 0);

  poppler_structure_element_iter_free(iter);

  // After free, doc should have been unref'd; since no other refs exist,
  // it should be finalized exactly once.
  EXPECT_EQ(g_atomic_int_get(&g_finalize_count_2536), 1);
}

TEST_F(PopplerStructureElementIterFreeTest_2536, UnrefsDocumentButDoesNotFinalizeIfExternalRefHeld_2536) {
  // Boundary/interaction: if someone else holds a ref, freeing iter should only
  // drop its own reference, not finalize the object yet.
  PopplerStructureElementIter* iter = g_slice_new0(PopplerStructureElementIter);
  ASSERT_NE(iter, nullptr);

  GObject* doc = NewCounterObject();
  ASSERT_NE(doc, nullptr);

  // Hold an external reference in addition to the one stored in iter.
  g_object_ref(doc);  // external hold
  iter->document = doc;

  poppler_structure_element_iter_free(iter);

  // Should not be finalized yet because we still hold an external ref.
  EXPECT_EQ(g_atomic_int_get(&g_finalize_count_2536), 0);

  // Release external reference; now it should finalize.
  g_object_unref(doc);
  EXPECT_EQ(g_atomic_int_get(&g_finalize_count_2536), 1);
}

TEST_F(PopplerStructureElementIterFreeTest_2536, SafeWhenDocumentIsNull_2536) {
  // Error-ish/boundary: even if document is null, freeing should not crash.
  // (GLib's g_object_unref() is defensive and should g_return_if_fail.)
  PopplerStructureElementIter* iter = g_slice_new0(PopplerStructureElementIter);
  ASSERT_NE(iter, nullptr);

  iter->document = nullptr;

  poppler_structure_element_iter_free(iter);

  // No document existed, so nothing to finalize.
  EXPECT_EQ(g_atomic_int_get(&g_finalize_count_2536), 0);
}