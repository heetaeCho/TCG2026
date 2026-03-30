// poppler-structure-element-test.cc
//
// Unit tests for _poppler_structure_element_new().
//
// NOTE: The function under test is a static function in a .cc file. To test it
// as a black box without re-implementing logic, we include the implementation
// file so the static symbol is visible in this translation unit.

#include <gtest/gtest.h>

#include <glib-object.h>

// Poppler GLib public API (for PopplerDocument type/macro).
#include <poppler.h>

namespace {

class PopplerStructureElementTest_2516 : public ::testing::Test {
 protected:
  static void SetUpTestSuite() {
    // Since GLib 2.36, g_type_init() is unnecessary; kept empty intentionally.
  }

  static PopplerDocument* CreateDummyDocumentOrSkip() {
    // The function under test requires POPPLER_IS_DOCUMENT(document).
    // In many Poppler-GLib builds, PopplerDocument is instantiable as a GObject.
    // If it isn't (e.g., abstract or requires construction properties), skip.
    PopplerDocument* doc = reinterpret_cast<PopplerDocument*>(
        g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));
    if (!doc || !POPPLER_IS_DOCUMENT(doc)) {
      if (doc) g_object_unref(doc);
      return nullptr;
    }
    return doc;
  }

  static void WeakNotifyFlagSetter(gpointer data, GObject* /*where_the_object_was*/) {
    bool* flag = static_cast<bool*>(data);
    *flag = true;
  }

  static const StructElement* FakeNonNullStructElement() {
    // The tested function only asserts that element != nullptr and stores it.
    // It does not (in the provided code) dereference the pointer.
    return reinterpret_cast<const StructElement*>(static_cast<uintptr_t>(0x1));
  }
};

TEST_F(PopplerStructureElementTest_2516, NewKeepsDocumentAliveUntilElementUnref_2516) {
  PopplerDocument* doc = CreateDummyDocumentOrSkip();
  if (!doc) GTEST_SKIP() << "PopplerDocument could not be constructed in this build.";

  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), &WeakNotifyFlagSetter, &doc_finalized);

  const StructElement* elem = FakeNonNullStructElement();

  PopplerStructureElement* se = _poppler_structure_element_new(doc, elem);
  ASSERT_NE(se, nullptr);

  // The function is expected to hold a reference to the document internally.
  // Observable behavior: unref'ing our original doc should NOT finalize it yet.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // When the structure element is unref'ed, the document ref it holds (if any)
  // should be released, allowing finalization to occur.
  g_object_unref(se);

  // Finalization should be immediate when refcount reaches zero.
  EXPECT_TRUE(doc_finalized);
}

TEST_F(PopplerStructureElementTest_2516, MultipleElementsHoldIndependentRefs_2516) {
  PopplerDocument* doc = CreateDummyDocumentOrSkip();
  if (!doc) GTEST_SKIP() << "PopplerDocument could not be constructed in this build.";

  bool doc_finalized = false;
  g_object_weak_ref(G_OBJECT(doc), &WeakNotifyFlagSetter, &doc_finalized);

  const StructElement* elem = FakeNonNullStructElement();

  PopplerStructureElement* se1 = _poppler_structure_element_new(doc, elem);
  PopplerStructureElement* se2 = _poppler_structure_element_new(doc, elem);
  ASSERT_NE(se1, nullptr);
  ASSERT_NE(se2, nullptr);

  // Drop our own reference.
  g_object_unref(doc);
  EXPECT_FALSE(doc_finalized);

  // Releasing one element should still keep the document alive because the other
  // element should hold its own reference.
  g_object_unref(se1);
  EXPECT_FALSE(doc_finalized);

  // Releasing the last element should allow the document to finalize.
  g_object_unref(se2);
  EXPECT_TRUE(doc_finalized);
}

TEST_F(PopplerStructureElementTest_2516, DeathOnNullDocument_2516) {
  const StructElement* elem = FakeNonNullStructElement();

  // g_assert(POPPLER_IS_DOCUMENT(document)) should abort.
  ASSERT_DEATH(
      {
        (void)_poppler_structure_element_new(nullptr, elem);
      },
      ".*");
}

TEST_F(PopplerStructureElementTest_2516, DeathOnNullElement_2516) {
  PopplerDocument* doc = CreateDummyDocumentOrSkip();
  if (!doc) GTEST_SKIP() << "PopplerDocument could not be constructed in this build.";

  // g_assert(element) should abort.
  ASSERT_DEATH(
      {
        (void)_poppler_structure_element_new(doc, nullptr);
      },
      ".*");

  g_object_unref(doc);
}

}  // namespace

// Include the implementation to access the static function under test.
// Keep this include LAST to avoid accidental macro/typedef interference.
#include "./TestProjects/poppler/glib/poppler-structure-element.cc"