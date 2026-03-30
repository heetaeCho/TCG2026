// File: poppler-structure-element-get-table-column-span-test-2592.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) {
      g_object_unref(p);
    }
  }
};

template <typename T>
using GObjPtr = std::unique_ptr<T, GObjectUnrefDeleter>;

struct GErrorDeleter {
  void operator()(GError* e) const {
    if (e) g_error_free(e);
  }
};
using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;

static std::string GetTestDataDir() {
  // Common patterns in Poppler/GLib tests.
  const char* dir = g_getenv("TESTDATADIR");
  if (dir && *dir) return dir;

  dir = g_getenv("G_TEST_SRCDIR");
  if (dir && *dir) return dir;

#ifdef TESTDATADIR
  return TESTDATADIR;
#endif

#ifdef SRCDIR
  return SRCDIR;
#endif

  // Fallback: current directory.
  return ".";
}

static std::string FindFirstExistingPdfPath(const std::vector<std::string>& candidates) {
  const std::string base = GetTestDataDir();
  for (const auto& name : candidates) {
    gchar* path = g_build_filename(base.c_str(), name.c_str(), nullptr);
    const bool exists = g_file_test(path, G_FILE_TEST_EXISTS) == TRUE;
    std::string out;
    if (exists) out = path;
    g_free(path);
    if (!out.empty()) return out;
  }
  return {};
}

static GObjPtr<PopplerDocument> OpenDocumentFromPathOrSkip(const std::string& pdf_path) {
  if (pdf_path.empty()) {
    GTEST_SKIP() << "No suitable tagged/table PDF found in test data directory.";
  }

  GError* err_raw = nullptr;
  gchar* uri = g_filename_to_uri(pdf_path.c_str(), nullptr, &err_raw);
  GErrorPtr uri_err(err_raw);
  if (!uri) {
    GTEST_SKIP() << "Failed to create file URI for test PDF: " << pdf_path
                 << " (GError: " << (uri_err ? uri_err->message : "unknown") << ")";
  }

  err_raw = nullptr;
  PopplerDocument* doc =
      poppler_document_new_from_file(uri, /*password=*/nullptr, &err_raw);
  g_free(uri);
  GErrorPtr err(err_raw);

  if (!doc) {
    GTEST_SKIP() << "Failed to open test PDF: " << pdf_path
                 << " (GError: " << (err ? err->message : "unknown") << ")";
  }

  return GObjPtr<PopplerDocument>(doc);
}

static PopplerStructureElement* FindFirstElementOfKind(PopplerStructureElementIter* iter,
                                                      PopplerStructureElementKind target_kind) {
  if (!iter) return nullptr;

  do {
    PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter);
    if (elem && poppler_structure_element_get_kind(elem) == target_kind) {
      return elem;
    }

    PopplerStructureElementIter* child = poppler_structure_element_iter_get_child(iter);
    if (child) {
      PopplerStructureElement* found = FindFirstElementOfKind(child, target_kind);
      poppler_structure_element_iter_free(child);
      if (found) return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

static PopplerStructureElement* FindFirstElementNotOfKind(PopplerStructureElementIter* iter,
                                                         PopplerStructureElementKind not_kind) {
  if (!iter) return nullptr;

  do {
    PopplerStructureElement* elem = poppler_structure_element_iter_get_element(iter);
    if (elem && poppler_structure_element_get_kind(elem) != not_kind) {
      return elem;
    }

    PopplerStructureElementIter* child = poppler_structure_element_iter_get_child(iter);
    if (child) {
      PopplerStructureElement* found = FindFirstElementNotOfKind(child, not_kind);
      poppler_structure_element_iter_free(child);
      if (found) return found;
    }
  } while (poppler_structure_element_iter_next(iter));

  return nullptr;
}

class PopplerStructureElementGetTableColumnSpanTest_2592 : public ::testing::Test {
 protected:
  void SetUp() override {
    // We try a few commonly used tagged/structure/table test PDF names.
    const std::vector<std::string> candidates = {
        "table.pdf",
        "tables.pdf",
        "tagged-table.pdf",
        "tagged_tables.pdf",
        "structure.pdf",
        "structure-elements.pdf",
        "tagged.pdf",
    };

    pdf_path_ = FindFirstExistingPdfPath(candidates);
    doc_ = OpenDocumentFromPathOrSkip(pdf_path_);

    root_iter_ = poppler_structure_element_iter_new(doc_.get());
    if (!root_iter_) {
      GTEST_SKIP() << "Document has no structure tree iterator (not tagged?): " << pdf_path_;
    }

    // Cache elements (ref to keep them valid even if iterators are freed later).
    PopplerStructureElement* table_raw =
        FindFirstElementOfKind(root_iter_, POPPLER_STRUCTURE_ELEMENT_TABLE);
    if (table_raw) {
      table_elem_.reset(POPPLER_STRUCTURE_ELEMENT(g_object_ref(table_raw)));
    }

    PopplerStructureElement* non_table_raw =
        FindFirstElementNotOfKind(root_iter_, POPPLER_STRUCTURE_ELEMENT_TABLE);
    if (non_table_raw) {
      non_table_elem_.reset(POPPLER_STRUCTURE_ELEMENT(g_object_ref(non_table_raw)));
    }
  }

  void TearDown() override {
    if (root_iter_) {
      poppler_structure_element_iter_free(root_iter_);
      root_iter_ = nullptr;
    }
  }

  std::string pdf_path_;
  GObjPtr<PopplerDocument> doc_{nullptr};
  PopplerStructureElementIter* root_iter_{nullptr};

  GObjPtr<PopplerStructureElement> table_elem_{nullptr};
  GObjPtr<PopplerStructureElement> non_table_elem_{nullptr};
};

TEST_F(PopplerStructureElementGetTableColumnSpanTest_2592, NullPointerReturnsZero_2592) {
  // Observable behavior: g_return_val_if_fail should cause a critical log and return 0.
  g_test_expect_message(/*log_domain=*/nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
  const guint span = poppler_structure_element_get_table_column_span(nullptr);
  g_test_assert_expected_messages();
  EXPECT_EQ(span, 0u);
}

TEST_F(PopplerStructureElementGetTableColumnSpanTest_2592, NonTableKindReturnsZero_2592) {
  if (!non_table_elem_) {
    GTEST_SKIP() << "Could not find a non-table structure element in: " << pdf_path_;
  }

  // Function guards on kind==TABLE. For non-table element it should return 0.
  g_test_expect_message(/*log_domain=*/nullptr, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
  const guint span = poppler_structure_element_get_table_column_span(non_table_elem_.get());
  g_test_assert_expected_messages();

  EXPECT_EQ(span, 0u);
}

TEST_F(PopplerStructureElementGetTableColumnSpanTest_2592, TableKindReturnsPositiveAndStable_2592) {
  if (!table_elem_) {
    GTEST_SKIP() << "Could not find a table structure element in: " << pdf_path_;
  }

  const guint span1 = poppler_structure_element_get_table_column_span(table_elem_.get());
  EXPECT_GT(span1, 0u) << "API contract expects a positive, non-zero span for table elements.";

  const guint span2 = poppler_structure_element_get_table_column_span(table_elem_.get());
  EXPECT_EQ(span1, span2) << "Repeated calls should be stable for the same element.";
}

}  // namespace