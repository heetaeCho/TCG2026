// poppler-index-iter-get-child-test_2214.cc
//
// Unit tests for poppler_index_iter_get_child()
// Constraints honored:
// - Treat implementation as black box.
// - Drive behavior via public Poppler-GLib API + real PDFs.
// - No access to private/internal state of PopplerIndexIter.
// - Use observable behavior (return values, lifetime/ref behavior via weak refs).

#include <gtest/gtest.h>

#include <poppler.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct TempFile {
  std::string path;
  explicit TempFile(std::string p) : path(std::move(p)) {}
  ~TempFile() {
    if (!path.empty()) {
      g_remove(path.c_str());
    }
  }
};

static std::string ToFileUri(const std::string& path) {
  // Use GLib utility to create correct file:// URI for Poppler.
  gchar* uri = g_filename_to_uri(path.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
  std::string out = uri ? uri : "";
  g_free(uri);
  return out;
}

// Minimal PDF builder that writes a valid PDF with one page, plus an outline item.
// If with_kids=true, the top outline item has one child outline item.
// If with_kids=false, the top outline item has no kids.
static std::string BuildPdfWithOutlines(bool with_kids) {
  // Objects we will create:
  // 1 0 obj: Catalog
  // 2 0 obj: Pages
  // 3 0 obj: Page
  // 4 0 obj: Outlines
  // 5 0 obj: Outline item (Parent)
  // 6 0 obj: Outline item (Child) [optional]

  std::vector<std::string> objs;

  // 1: Catalog
  {
    std::ostringstream ss;
    ss << "1 0 obj\n"
       << "<< /Type /Catalog\n"
       << "   /Pages 2 0 R\n"
       << "   /Outlines 4 0 R\n"
       << ">>\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // 2: Pages
  {
    std::ostringstream ss;
    ss << "2 0 obj\n"
       << "<< /Type /Pages\n"
       << "   /Kids [3 0 R]\n"
       << "   /Count 1\n"
       << ">>\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // 3: Page
  {
    std::ostringstream ss;
    ss << "3 0 obj\n"
       << "<< /Type /Page\n"
       << "   /Parent 2 0 R\n"
       << "   /MediaBox [0 0 612 792]\n"
       << "   /Resources << >>\n"
       << "   /Contents 7 0 R\n"
       << ">>\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // 4: Outlines dictionary
  {
    std::ostringstream ss;
    ss << "4 0 obj\n"
       << "<< /Type /Outlines\n"
       << "   /First 5 0 R\n"
       << "   /Last 5 0 R\n"
       << "   /Count 1\n"
       << ">>\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // 5: Parent outline item
  {
    std::ostringstream ss;
    ss << "5 0 obj\n"
       << "<< /Title (Parent)\n"
       << "   /Parent 4 0 R\n"
       << "   /Dest [3 0 R /Fit]\n";
    if (with_kids) {
      ss << "   /First 6 0 R\n"
         << "   /Last 6 0 R\n"
         << "   /Count 1\n";
    }
    ss << ">>\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // 6: Child outline item (optional)
  if (with_kids) {
    std::ostringstream ss;
    ss << "6 0 obj\n"
       << "<< /Title (Child)\n"
       << "   /Parent 5 0 R\n"
       << "   /Dest [3 0 R /Fit]\n"
       << ">>\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // 7: Contents stream (empty-ish)
  {
    std::ostringstream ss;
    ss << "7 0 obj\n"
       << "<< /Length 0 >>\n"
       << "stream\n"
       << "\n"
       << "endstream\n"
       << "endobj\n";
    objs.push_back(ss.str());
  }

  // Build full PDF with xref.
  std::ostringstream pdf;
  pdf << "%PDF-1.4\n";

  // Track offsets for xref.
  // Object numbers go 1..7 (some may be absent from objs vector ordering,
  // so we will write them in numeric order explicitly).
  // We'll store offsets in a map by objnum.
  std::vector<long> offsets(8, 0);  // offsets[0] is special.

  auto write_obj = [&](int objnum, const std::string& content) {
    offsets[objnum] = static_cast<long>(pdf.tellp());
    pdf << content;
  };

  // objs currently contains: 1,2,3,4,5,(6),7 but in that order; we need to write correct ones.
  // We'll reconstruct by objnum.
  // Note: When with_kids=false, there is no 6, but we still have 7.
  // Indices in objs vector:
  // [0]=1, [1]=2, [2]=3, [3]=4, [4]=5, [5]=6(if kids) or 7(if no kids), last=7(if kids)
  write_obj(1, objs[0]);
  write_obj(2, objs[1]);
  write_obj(3, objs[2]);
  write_obj(4, objs[3]);
  write_obj(5, objs[4]);
  if (with_kids) {
    write_obj(6, objs[5]);
    write_obj(7, objs[6]);
  } else {
    write_obj(7, objs[5]);
  }

  const long xref_pos = static_cast<long>(pdf.tellp());
  pdf << "xref\n";
  pdf << "0 8\n";
  pdf << "0000000000 65535 f \n";
  for (int i = 1; i <= 7; ++i) {
    // If an object wasn't written (e.g., 6 when with_kids=false), mark it as free.
    if (offsets[i] == 0) {
      pdf << "0000000000 65535 f \n";
    } else {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
      pdf << buf << " 00000 n \n";
    }
  }

  pdf << "trailer\n";
  pdf << "<< /Size 8\n";
  pdf << "   /Root 1 0 R\n";
  pdf << ">>\n";
  pdf << "startxref\n";
  pdf << xref_pos << "\n";
  pdf << "%%EOF\n";

  return pdf.str();
}

static TempFile WriteTempPdf(const std::string& pdf_bytes) {
  gchar* tmp_name = nullptr;
  gint fd = g_file_open_tmp("poppler_index_iter_get_child_XXXXXX.pdf", &tmp_name, nullptr);
  EXPECT_NE(fd, -1);
  EXPECT_NE(tmp_name, nullptr);

  // Write to fd.
  const gssize total = static_cast<gssize>(pdf_bytes.size());
  gssize written = 0;
  while (written < total) {
    const gssize n = write(fd, pdf_bytes.data() + written, static_cast<size_t>(total - written));
    if (n <= 0) break;
    written += n;
  }
  close(fd);

  EXPECT_EQ(written, total);

  std::string path = tmp_name ? tmp_name : "";
  g_free(tmp_name);
  return TempFile(path);
}

static PopplerDocument* LoadDocFromPath(const std::string& path) {
  GError* error = nullptr;
  const std::string uri = ToFileUri(path);
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  if (!doc) {
    std::string msg = error ? error->message : "unknown error";
    if (error) g_error_free(error);
    ADD_FAILURE() << "Failed to load PDF via Poppler: " << msg;
  }
  if (error) g_error_free(error);
  return doc;
}

static PopplerIndexIter* NewIndexIter(PopplerDocument* doc) {
  // Public API in poppler-glib.
  return poppler_index_iter_new(doc);
}

static void FreeIndexIter(PopplerIndexIter* iter) {
  if (iter) poppler_index_iter_free(iter);
}

struct WeakNotifyState {
  bool notified = false;
};

static void WeakNotifyCb(gpointer data, GObject* /*where_the_object_was*/) {
  auto* st = static_cast<WeakNotifyState*>(data);
  st->notified = true;
}

}  // namespace

// --------------------------- Tests ---------------------------

TEST(PopplerIndexIterGetChildTest_2214, NullParentReturnsNull_2214) {
  // Observable behavior: g_return_val_if_fail should return NULL for null parent.
  EXPECT_EQ(poppler_index_iter_get_child(nullptr), nullptr);
}

TEST(PopplerIndexIterGetChildTest_2214, ParentWithKidsReturnsNonNullChildIter_2214) {
  TempFile tf = WriteTempPdf(BuildPdfWithOutlines(/*with_kids=*/true));
  ASSERT_FALSE(tf.path.empty());

  PopplerDocument* doc = LoadDocFromPath(tf.path);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter* parent = NewIndexIter(doc);
  ASSERT_NE(parent, nullptr);

  PopplerIndexIter* child = poppler_index_iter_get_child(parent);
  EXPECT_NE(child, nullptr);

  // Clean up.
  FreeIndexIter(child);
  FreeIndexIter(parent);
  g_object_unref(doc);
}

TEST(PopplerIndexIterGetChildTest_2214, ParentWithoutKidsReturnsNull_2214) {
  TempFile tf = WriteTempPdf(BuildPdfWithOutlines(/*with_kids=*/false));
  ASSERT_FALSE(tf.path.empty());

  PopplerDocument* doc = LoadDocFromPath(tf.path);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter* parent = NewIndexIter(doc);
  ASSERT_NE(parent, nullptr);

  PopplerIndexIter* child = poppler_index_iter_get_child(parent);
  EXPECT_EQ(child, nullptr);

  FreeIndexIter(parent);
  g_object_unref(doc);
}

TEST(PopplerIndexIterGetChildTest_2214, ChildIterWithoutKidsReturnsNull_2214) {
  TempFile tf = WriteTempPdf(BuildPdfWithOutlines(/*with_kids=*/true));
  ASSERT_FALSE(tf.path.empty());

  PopplerDocument* doc = LoadDocFromPath(tf.path);
  ASSERT_NE(doc, nullptr);

  PopplerIndexIter* parent = NewIndexIter(doc);
  ASSERT_NE(parent, nullptr);

  PopplerIndexIter* child = poppler_index_iter_get_child(parent);
  ASSERT_NE(child, nullptr);

  // The "Child" outline item has no kids in our PDF.
  PopplerIndexIter* grandchild = poppler_index_iter_get_child(child);
  EXPECT_EQ(grandchild, nullptr);

  FreeIndexIter(child);
  FreeIndexIter(parent);
  g_object_unref(doc);
}

TEST(PopplerIndexIterGetChildTest_2214, ChildIterKeepsDocumentAliveUntilFreed_2214) {
  // Verifies external interaction: poppler_index_iter_get_child takes a reference to the document
  // (observable via weak notify timing).
  TempFile tf = WriteTempPdf(BuildPdfWithOutlines(/*with_kids=*/true));
  ASSERT_FALSE(tf.path.empty());

  PopplerDocument* doc = LoadDocFromPath(tf.path);
  ASSERT_NE(doc, nullptr);

  WeakNotifyState st;
  g_object_weak_ref(G_OBJECT(doc), WeakNotifyCb, &st);

  PopplerIndexIter* parent = NewIndexIter(doc);
  ASSERT_NE(parent, nullptr);

  PopplerIndexIter* child = poppler_index_iter_get_child(parent);
  ASSERT_NE(child, nullptr);

  // Drop our explicit reference. If the iter(s) hold refs, object should not be finalized yet.
  g_object_unref(doc);
  EXPECT_FALSE(st.notified);

  // Free only the child first; parent iter is still alive and may also hold a ref.
  FreeIndexIter(child);
  EXPECT_FALSE(st.notified);

  // Now free parent; document should be allowed to finalize.
  FreeIndexIter(parent);

  // Weak notify should have been called by now (synchronously on finalize).
  EXPECT_TRUE(st.notified);
}