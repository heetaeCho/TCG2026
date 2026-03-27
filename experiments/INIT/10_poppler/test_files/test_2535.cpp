// File: poppler-structure-element-iter-copy-test-2535.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>
#include <poppler.h>

namespace {

class PopplerStructureElementIterCopyTest_2535 : public ::testing::Test {
protected:
  static PopplerDocument* NewDocFromData(const unsigned char* data, int len) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(reinterpret_cast<const char*>(data), len,
                                       /*password=*/nullptr, &error);
    if (error) {
      g_error_free(error);
    }
    return doc;
  }

  static void WeakNotifySetBool(gpointer data, GObject* /*where_the_object_was*/) {
    *static_cast<bool*>(data) = true;
  }

  // Minimal Tagged PDF with a structure tree (root Document -> P) and one marked-content item.
  static constexpr unsigned char kTaggedPdf[1083] = {
      37, 80, 68, 70, 45, 49, 46, 55, 10, 37, 226, 227, 207, 211, 10, 49, 32,
      48, 32, 111, 98, 106, 10, 60, 60, 32, 47, 84, 121, 112, 101, 32, 47, 67,
      97, 116, 97, 108, 111, 103, 32, 47, 80, 97, 103, 101, 115, 32, 50, 32,
      48, 32, 82, 32, 47, 83, 116, 114, 117, 99, 116, 84, 114, 101, 101, 82,
      111, 111, 116, 32, 54, 32, 48, 32, 82, 32, 47, 77, 97, 114, 107, 73,
      110, 102, 111, 32, 60, 60, 32, 47, 77, 97, 114, 107, 101, 100, 32, 116,
      114, 117, 101, 32, 62, 62, 32, 62, 62, 10, 101, 110, 100, 111, 98, 106,
      10, 50, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32, 47, 84, 121, 112, 101,
      32, 47, 80, 97, 103, 101, 115, 32, 47, 75, 105, 100, 115, 32, 91, 51,
      32, 48, 32, 82, 93, 32, 47, 67, 111, 117, 110, 116, 32, 49, 32, 62, 62,
      10, 101, 110, 100, 111, 98, 106, 10, 51, 32, 48, 32, 111, 98, 106, 10,
      60, 60, 32, 47, 84, 121, 112, 101, 32, 47, 80, 97, 103, 101, 32, 47,
      80, 97, 114, 101, 110, 116, 32, 50, 32, 48, 32, 82, 32, 47, 77, 101,
      100, 105, 97, 66, 111, 120, 32, 91, 48, 32, 48, 32, 50, 48, 48, 32,
      50, 48, 48, 93, 32, 47, 67, 111, 110, 116, 101, 110, 116, 115, 32, 52,
      32, 48, 32, 82, 32, 47, 82, 101, 115, 111, 117, 114, 99, 101, 115, 32,
      60, 60, 32, 47, 70, 111, 110, 116, 32, 60, 60, 32, 47, 70, 49, 32, 53,
      32, 48, 32, 82, 32, 62, 62, 32, 62, 62, 32, 47, 83, 116, 114, 117, 99,
      116, 80, 97, 114, 101, 110, 116, 115, 32, 48, 32, 62, 62, 10, 101, 110,
      100, 111, 98, 106, 10, 52, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32,
      47, 76, 101, 110, 103, 116, 104, 32, 54, 49, 32, 62, 62, 10, 115, 116,
      114, 101, 97, 109, 10, 66, 84, 32, 47, 70, 49, 32, 49, 50, 32, 84, 102,
      32, 50, 48, 32, 49, 48, 48, 32, 84, 100, 32, 47, 80, 32, 60, 60, 47,
      77, 67, 73, 68, 32, 48, 62, 62, 32, 66, 68, 67, 32, 40, 72, 101, 108,
      108, 111, 41, 32, 84, 106, 32, 69, 77, 67, 32, 69, 84, 10, 101, 110,
      100, 115, 116, 114, 101, 97, 109, 10, 101, 110, 100, 111, 98, 106, 10,
      53, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32, 47, 84, 121, 112, 101, 32,
      47, 70, 111, 110, 116, 32, 47, 83, 117, 98, 116, 121, 112, 101, 32, 47,
      84, 121, 112, 101, 49, 32, 47, 66, 97, 115, 101, 70, 111, 110, 116, 32,
      47, 72, 101, 108, 118, 101, 116, 105, 99, 97, 32, 62, 62, 10, 101, 110,
      100, 111, 98, 106, 10, 54, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32,
      47, 84, 121, 112, 101, 32, 47, 83, 116, 114, 117, 99, 116, 84, 114, 101,
      101, 82, 111, 111, 116, 32, 47, 75, 32, 55, 32, 48, 32, 82, 32, 47, 80,
      97, 114, 101, 110, 116, 84, 114, 101, 101, 32, 49, 48, 32, 48, 32, 82,
      32, 62, 62, 10, 101, 110, 100, 111, 98, 106, 10, 55, 32, 48, 32, 111,
      98, 106, 10, 60, 60, 32, 47, 84, 121, 112, 101, 32, 47, 83, 116, 114,
      117, 99, 116, 69, 108, 101, 109, 32, 47, 83, 32, 47, 68, 111, 99, 117,
      109, 101, 110, 116, 32, 47, 80, 32, 54, 32, 48, 32, 82, 32, 47, 75, 32,
      56, 32, 48, 32, 82, 32, 62, 62, 10, 101, 110, 100, 111, 98, 106, 10, 56,
      32, 48, 32, 111, 98, 106, 10, 60, 60, 32, 47, 84, 121, 112, 101, 32, 47,
      83, 116, 114, 117, 99, 116, 69, 108, 101, 109, 32, 47, 83, 32, 47, 80,
      32, 47, 80, 32, 55, 32, 48, 32, 82, 32, 47, 80, 103, 32, 51, 32, 48,
      32, 82, 32, 47, 75, 32, 57, 32, 48, 32, 82, 32, 62, 62, 10, 101, 110,
      100, 111, 98, 106, 10, 57, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32,
      47, 84, 121, 112, 101, 32, 47, 77, 67, 82, 32, 47, 80, 103, 32, 51, 32,
      48, 32, 82, 32, 47, 77, 67, 73, 68, 32, 48, 32, 62, 62, 10, 101, 110,
      100, 111, 98, 106, 10, 49, 48, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32,
      47, 78, 117, 109, 115, 32, 91, 48, 32, 91, 57, 32, 48, 32, 82, 93, 93,
      32, 62, 62, 10, 101, 110, 100, 111, 98, 106, 10, 120, 114, 101, 102, 10,
      48, 32, 49, 49, 10, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 32, 54, 53,
      53, 51, 53, 32, 102, 32, 10, 48, 48, 48, 48, 48, 48, 48, 48, 49, 53, 32,
      48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 49,
      50, 57, 32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48,
      48, 48, 49, 57, 50, 32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48,
      48, 48, 48, 48, 48, 51, 50, 53, 32, 48, 48, 48, 48, 48, 32, 110, 32,
      10, 48, 48, 48, 48, 48, 48, 48, 52, 51, 55, 32, 48, 48, 48, 48, 48, 32,
      110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 53, 48, 55, 32, 48, 48, 48,
      48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 53, 56, 55, 32, 48,
      48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 54, 53, 55,
      32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 55,
      51, 55, 32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48,
      48, 55, 57, 49, 32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 116, 114, 97,
      105, 108, 101, 114, 10, 60, 60, 32, 47, 83, 105, 122, 101, 32, 49, 49,
      32, 47, 82, 111, 111, 116, 32, 49, 32, 48, 32, 82, 32, 62, 62, 10, 115,
      116, 97, 114, 116, 120, 114, 101, 102, 10, 55, 57, 56, 10, 37, 37, 69,
      79, 70, 10};

  // Minimal untagged PDF (no StructTreeRoot).
  static constexpr unsigned char kUntaggedPdf[580] = {
      37, 80, 68, 70, 45, 49, 46, 52, 10, 49, 32, 48, 32, 111, 98, 106, 10, 60,
      60, 32, 47, 84, 121, 112, 101, 32, 47, 67, 97, 116, 97, 108, 111, 103, 32,
      47, 80, 97, 103, 101, 115, 32, 50, 32, 48, 32, 82, 32, 62, 62, 10, 101,
      110, 100, 111, 98, 106, 10, 50, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32,
      47, 84, 121, 112, 101, 32, 47, 80, 97, 103, 101, 115, 32, 47, 75, 105,
      100, 115, 32, 91, 51, 32, 48, 32, 82, 93, 32, 47, 67, 111, 117, 110, 116,
      32, 49, 32, 62, 62, 10, 101, 110, 100, 111, 98, 106, 10, 51, 32, 48, 32,
      111, 98, 106, 10, 60, 60, 32, 47, 84, 121, 112, 101, 32, 47, 80, 97, 103,
      101, 32, 47, 80, 97, 114, 101, 110, 116, 32, 50, 32, 48, 32, 82, 32, 47,
      77, 101, 100, 105, 97, 66, 111, 120, 32, 91, 48, 32, 48, 32, 50, 48, 48,
      32, 50, 48, 48, 93, 32, 47, 67, 111, 110, 116, 101, 110, 116, 115, 32, 52,
      32, 48, 32, 82, 32, 47, 82, 101, 115, 111, 117, 114, 99, 101, 115, 32, 60,
      60, 32, 47, 70, 111, 110, 116, 32, 60, 60, 32, 47, 70, 49, 32, 53, 32, 48,
      32, 82, 32, 62, 62, 32, 62, 62, 32, 62, 62, 10, 101, 110, 100, 111, 98,
      106, 10, 52, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32, 47, 76, 101, 110,
      103, 116, 104, 32, 52, 52, 32, 62, 62, 10, 115, 116, 114, 101, 97, 109,
      10, 66, 84, 32, 47, 70, 49, 32, 49, 50, 32, 84, 102, 32, 50, 48, 32, 49,
      48, 48, 32, 84, 100, 32, 40, 72, 101, 108, 108, 111, 41, 32, 84, 106, 32,
      69, 84, 10, 101, 110, 100, 115, 116, 114, 101, 97, 109, 10, 101, 110, 100,
      111, 98, 106, 10, 53, 32, 48, 32, 111, 98, 106, 10, 60, 60, 32, 47, 84,
      121, 112, 101, 32, 47, 70, 111, 110, 116, 32, 47, 83, 117, 98, 116, 121,
      112, 101, 32, 47, 84, 121, 112, 101, 49, 32, 47, 66, 97, 115, 101, 70,
      111, 110, 116, 32, 47, 72, 101, 108, 118, 101, 116, 105, 99, 97, 32, 62,
      62, 10, 101, 110, 100, 111, 98, 106, 10, 120, 114, 101, 102, 10, 48, 32,
      54, 10, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 32, 54, 53, 53, 51, 53,
      32, 102, 32, 10, 48, 48, 48, 48, 48, 48, 48, 48, 48, 57, 32, 48, 48, 48,
      48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 48, 53, 56, 32, 48,
      48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 49, 50, 49,
      32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48, 48, 50,
      54, 56, 32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 48, 48, 48, 48, 48, 48,
      48, 51, 51, 54, 32, 48, 48, 48, 48, 48, 32, 110, 32, 10, 116, 114, 97,
      105, 108, 101, 114, 10, 60, 60, 32, 47, 83, 105, 122, 101, 32, 54, 32, 47,
      82, 111, 111, 116, 32, 49, 32, 48, 32, 82, 32, 62, 62, 10, 115, 116, 97,
      114, 116, 120, 114, 101, 102, 10, 51, 57, 55, 10, 37, 37, 69, 79, 70, 10};
};

TEST_F(PopplerStructureElementIterCopyTest_2535, CopyNullReturnsNull_2535) {
  PopplerStructureElementIter* copied = poppler_structure_element_iter_copy(nullptr);
  EXPECT_EQ(copied, nullptr);
}

TEST_F(PopplerStructureElementIterCopyTest_2535, CopyCreatesDistinctIterator_2535) {
  PopplerDocument* doc = NewDocFromData(kTaggedPdf, static_cast<int>(sizeof(kTaggedPdf)));
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElementIter* copied = poppler_structure_element_iter_copy(iter);
  ASSERT_NE(copied, nullptr);
  EXPECT_NE(copied, iter);

  // Both iterators should point at a valid element; the root is typically a Document element.
  PopplerStructureElement* e1 = poppler_structure_element_iter_get_element(iter);
  PopplerStructureElement* e2 = poppler_structure_element_iter_get_element(copied);
  ASSERT_NE(e1, nullptr);
  ASSERT_NE(e2, nullptr);

  EXPECT_EQ(poppler_structure_element_get_kind(e1), poppler_structure_element_get_kind(e2));
  EXPECT_EQ(poppler_structure_element_get_kind(e1), POPPLER_STRUCTURE_ELEMENT_KIND_DOCUMENT);

  // Advancing at the root level usually has no "next" sibling in minimal tagged docs.
  gboolean moved = poppler_structure_element_iter_next(iter);
  EXPECT_FALSE(moved);

  // Copied iterator should still be valid and still point at a Document-kind root.
  PopplerStructureElement* e2_after = poppler_structure_element_iter_get_element(copied);
  ASSERT_NE(e2_after, nullptr);
  EXPECT_EQ(poppler_structure_element_get_kind(e2_after), POPPLER_STRUCTURE_ELEMENT_KIND_DOCUMENT);

  poppler_structure_element_iter_free(copied);
  poppler_structure_element_iter_free(iter);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementIterCopyTest_2535, CopyKeepsDocumentAliveUntilAllIteratorsFreed_2535) {
  PopplerDocument* doc = NewDocFromData(kTaggedPdf, static_cast<int>(sizeof(kTaggedPdf)));
  ASSERT_NE(doc, nullptr);

  bool finalized = false;
  g_object_weak_ref(G_OBJECT(doc), &WeakNotifySetBool, &finalized);

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  PopplerStructureElementIter* copied = poppler_structure_element_iter_copy(iter);
  ASSERT_NE(copied, nullptr);

  // Drop our explicit reference. If iterators hold references internally (as copy() does),
  // the document should not be finalized yet.
  g_object_unref(doc);
  EXPECT_FALSE(finalized);

  poppler_structure_element_iter_free(iter);
  EXPECT_FALSE(finalized);

  poppler_structure_element_iter_free(copied);
  EXPECT_TRUE(finalized);
}

TEST_F(PopplerStructureElementIterCopyTest_2535, IterNewReturnsNullForUntaggedDocument_2535) {
  PopplerDocument* doc =
      NewDocFromData(kUntaggedPdf, static_cast<int>(sizeof(kUntaggedPdf)));
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter* iter = poppler_structure_element_iter_new(doc);
  EXPECT_EQ(iter, nullptr);

  g_object_unref(doc);
}

}  // namespace