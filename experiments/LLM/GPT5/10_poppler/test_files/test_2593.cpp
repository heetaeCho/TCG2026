// File: poppler-structure-element-get-table-headers-test_2593.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

class StructureElementGetTableHeadersTest_2593 : public ::testing::Test {
protected:
  void SetUp() override {
    const std::string pdf_path = FindAnyTaggedPdfWithStructure_2593();
    if (pdf_path.empty()) {
      GTEST_SKIP() << "No suitable tagged PDF test file found in test data directories.";
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(pdf_path.c_str(), nullptr, &error);
    ASSERT_NE(uri, nullptr) << "g_filename_to_uri failed: " << (error ? error->message : "unknown");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    document_ = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    ASSERT_NE(document_, nullptr) << "Failed to open PDF: " << (error ? error->message : "unknown");
    if (error) {
      g_error_free(error);
      error = nullptr;
    }

    root_iter_ = poppler_structure_element_iter_new(document_);
    if (!root_iter_) {
      GTEST_SKIP() << "PDF loaded but has no structure tree (poppler_structure_element_iter_new returned NULL).";
    }
  }

  void TearDown() override {
    if (root_iter_) {
      poppler_structure_element_iter_free(root_iter_);
      root_iter_ = nullptr;
    }
    if (document_) {
      g_object_unref(document_);
      document_ = nullptr;
    }
  }

  // Tries a handful of common locations/names used by Poppler/GLib tests.
  // If your project uses a single canonical file, add it to the candidates list.
  static std::string FindAnyTaggedPdfWithStructure_2593() {
    const std::vector<std::string> candidates = {
        // Commonly named tagged/structure PDFs in test suites (project-specific).
        "tagged-table.pdf",
        "structure-table.pdf",
        "table-headers.pdf",
        "table.pdf",
        "tagged.pdf",
        "structure.pdf",
        "struct-tree.pdf",
    };

    // 1) GLib test distribution dir (preferred for installed test data)
    for (const auto &name : candidates) {
      gchar *p = g_test_build_filename(G_TEST_DIST, name.c_str(), nullptr);
      if (p && g_file_test(p, G_FILE_TEST_IS_REGULAR)) {
        std::string out(p);
        g_free(p);
        return out;
      }
      g_free(p);
    }

    // 2) Source dir-based fallbacks (common in autotools/meson layouts)
    const gchar *srcdir = g_getenv("srcdir");
    const gchar *top_srcdir = g_getenv("top_srcdir");
    const std::vector<std::string> base_dirs = {
        srcdir ? srcdir : "",
        top_srcdir ? top_srcdir : "",
        // Some projects expose an explicit test data dir.
        g_getenv("POPPLER_TESTDATADIR") ? g_getenv("POPPLER_TESTDATADIR") : "",
    };

    for (const auto &base : base_dirs) {
      if (base.empty())
        continue;
      for (const auto &name : candidates) {
        gchar *p = g_build_filename(base.c_str(), name.c_str(), nullptr);
        if (p && g_file_test(p, G_FILE_TEST_IS_REGULAR)) {
          std::string out(p);
          g_free(p);
          return out;
        }
        g_free(p);
      }
    }

    return {};
  }

  // Depth-first walk over structure tree. The visitor returns true to stop early.
  static bool WalkStructure_2593(PopplerStructureElementIter *iter,
                                const std::function<bool(PopplerStructureElement *)> &visitor) {
    if (!iter) {
      return false;
    }

    // poppler_structure_element_iter_next() exists; but we can traverse using the standard pattern:
    // do { ...; child = get_child; walk(child); } while (poppler_structure_element_iter_next(iter));
    do {
      PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
      if (elem) {
        if (visitor(elem)) {
          g_object_unref(elem);
          return true;
        }
        g_object_unref(elem);
      }

      PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(iter);
      if (child) {
        const bool stopped = WalkStructure_2593(child, visitor);
        poppler_structure_element_iter_free(child);
        if (stopped) {
          return true;
        }
      }
    } while (poppler_structure_element_iter_next(iter));

    return false;
  }

  PopplerDocument *document_ = nullptr;
  PopplerStructureElementIter *root_iter_ = nullptr;
};

TEST_F(StructureElementGetTableHeadersTest_2593, NullElementReturnsNull_2593) {
  // Observable behavior: should return NULL for invalid input.
  // (This may also emit a critical warning internally; we don't assert on logs to keep the test robust.)
  gchar **headers = poppler_structure_element_get_table_headers(nullptr);
  EXPECT_EQ(headers, nullptr);
}

TEST_F(StructureElementGetTableHeadersTest_2593, NonTableElementReturnsNull_2593) {
  PopplerStructureElement *non_table = nullptr;

  // Find any element whose kind is not POPPLER_STRUCTURE_ELEMENT_TABLE.
  WalkStructure_2593(
      root_iter_, [&](PopplerStructureElement *elem) -> bool {
        const auto kind = poppler_structure_element_get_kind(elem);
        if (kind != POPPLER_STRUCTURE_ELEMENT_TABLE) {
          non_table = static_cast<PopplerStructureElement *>(g_object_ref(elem));
          return true; // stop
        }
        return false;
      });

  if (!non_table) {
    GTEST_SKIP() << "No non-table structure element found in this document.";
  }

  gchar **headers = poppler_structure_element_get_table_headers(non_table);
  EXPECT_EQ(headers, nullptr);

  g_object_unref(non_table);
}

TEST_F(StructureElementGetTableHeadersTest_2593, TableElementReturnsNullOrValidStrv_2593) {
  PopplerStructureElement *table = nullptr;

  WalkStructure_2593(
      root_iter_, [&](PopplerStructureElement *elem) -> bool {
        if (poppler_structure_element_get_kind(elem) == POPPLER_STRUCTURE_ELEMENT_TABLE) {
          table = static_cast<PopplerStructureElement *>(g_object_ref(elem));
          return true; // stop
        }
        return false;
      });

  if (!table) {
    GTEST_SKIP() << "No table structure element found in this document.";
  }

  gchar **headers = poppler_structure_element_get_table_headers(table);

  if (headers == nullptr) {
    // Boundary / absence case: attribute not defined is allowed per API docs.
    SUCCEED();
  } else {
    // Normal operation: validate returned zero-terminated string array.
    const gsize n = g_strv_length(headers);
    EXPECT_GT(n, 0u) << "Returned headers array should have at least one entry when non-NULL.";

    // Ensure zero termination is present at [n].
    EXPECT_EQ(headers[n], nullptr);

    for (gsize i = 0; i < n; ++i) {
      ASSERT_NE(headers[i], nullptr);
      EXPECT_TRUE(g_utf8_validate(headers[i], -1, nullptr))
          << "Header string must be valid UTF-8 at index " << i;
      EXPECT_NE(headers[i][0], '\0') << "Header string should not be empty at index " << i;
    }

    g_strfreev(headers);
  }

  g_object_unref(table);
}

TEST_F(StructureElementGetTableHeadersTest_2593, TableWithHeadersProvidesConsistentAllocation_2593) {
  PopplerStructureElement *table_with_headers = nullptr;
  gchar **headers_found = nullptr;

  // Search for a table element that actually has headers defined (function returns non-NULL).
  WalkStructure_2593(
      root_iter_, [&](PopplerStructureElement *elem) -> bool {
        if (poppler_structure_element_get_kind(elem) != POPPLER_STRUCTURE_ELEMENT_TABLE) {
          return false;
        }
        gchar **headers = poppler_structure_element_get_table_headers(elem);
        if (headers) {
          table_with_headers = static_cast<PopplerStructureElement *>(g_object_ref(elem));
          headers_found = headers; // take ownership; must free with g_strfreev
          return true;             // stop
        }
        return false;
      });

  if (!table_with_headers) {
    GTEST_SKIP() << "No table element with defined headers found in this document.";
  }
  ASSERT_NE(headers_found, nullptr);

  // Validate the strv contract and that g_strv_length() matches iteration until NULL.
  const gsize n = g_strv_length(headers_found);
  ASSERT_GT(n, 0u);

  gsize manual_count = 0;
  for (gchar **p = headers_found; *p != nullptr; ++p) {
    ASSERT_NE(*p, nullptr);
    EXPECT_TRUE(g_utf8_validate(*p, -1, nullptr));
    ++manual_count;
  }
  EXPECT_EQ(manual_count, n);

  // Free contract: caller must free with g_strfreev().
  g_strfreev(headers_found);
  g_object_unref(table_with_headers);
}

} // namespace