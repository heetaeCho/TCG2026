// poppler_attachment_get_ctime_test_2272.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdlib>
#include <string>
#include <vector>

namespace {

class PopplerAttachmentGetCTimeTest_2272 : public ::testing::Test {
protected:
  static std::string GetEnv(const char* name) {
    const char* v = std::getenv(name);
    return v ? std::string(v) : std::string();
  }

  static bool FileExists(const std::string& path) {
    return g_file_test(path.c_str(), G_FILE_TEST_EXISTS) != 0;
  }

  // Tries common Poppler test-data layouts. If nothing is found, tests will skip.
  static std::string FindAnyPdfWithAttachments_2272() {
    const std::vector<std::string> base_dirs = {
        GetEnv("POPPLER_TEST_DATADIR"),
        GetEnv("TEST_DATA_DIR"),
        ".", "./test-data", "../test-data", "../../test-data",
        "./TestProjects/poppler/test-data",
        "./TestProjects/poppler/glib/test-data",
    };

    const std::vector<std::string> candidates = {
        // common-ish names used in many projects
        "attachments.pdf",
        "attachment.pdf",
        "embedded-files.pdf",
        "embeddedfiles.pdf",
        "test-attachment.pdf",
        "test-attachments.pdf",
    };

    for (const auto& base : base_dirs) {
      if (base.empty()) continue;
      for (const auto& name : candidates) {
        std::string p = base;
        if (!p.empty() && p.back() != '/') p += "/";
        p += name;
        if (FileExists(p)) return p;
      }
    }
    return {};
  }

  static PopplerDocument* LoadDocument_2272(const std::string& pdf_path) {
    GError* error = nullptr;
    gchar* uri = g_filename_to_uri(pdf_path.c_str(), /*hostname=*/nullptr, &error);
    if (!uri) {
      if (error) g_error_free(error);
      return nullptr;
    }

    PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    g_free(uri);

    if (!doc) {
      if (error) g_error_free(error);
      return nullptr;
    }
    if (error) g_error_free(error);
    return doc;
  }

  struct GListDeleter_2272 {
    void operator()(GList* l) const { g_list_free_full(l, g_object_unref); }
  };

  static PopplerAttachment* FirstAttachmentOrNull_2272(PopplerDocument* doc) {
    if (!doc) return nullptr;
    // poppler_document_get_attachments() returns a GList* of PopplerAttachment* (transfer full).
    GList* list = poppler_document_get_attachments(doc);
    if (!list) return nullptr;
    std::unique_ptr<GList, GListDeleter_2272> holder(list);

    if (!holder.get()->data) return nullptr;
    // Return a new ref so the caller can safely use it after list is freed.
    return POPPLER_ATTACHMENT(g_object_ref(holder.get()->data));
  }
};

TEST_F(PopplerAttachmentGetCTimeTest_2272, ReturnsStablePointerForSameAttachment_2272) {
  const std::string pdf_path = FindAnyPdfWithAttachments_2272();
  if (pdf_path.empty()) GTEST_SKIP() << "No attachment PDF found (set POPPLER_TEST_DATADIR).";

  PopplerDocument* doc = LoadDocument_2272(pdf_path);
  ASSERT_NE(doc, nullptr) << "Failed to load PDF: " << pdf_path;

  PopplerAttachment* attachment = FirstAttachmentOrNull_2272(doc);
  g_object_unref(doc);
  if (!attachment) GTEST_SKIP() << "PDF loaded but no attachments found: " << pdf_path;

  GDateTime* ctime1 = poppler_attachment_get_ctime(attachment);
  GDateTime* ctime2 = poppler_attachment_get_ctime(attachment);

  // Based on the public interface: the function returns a GDateTime* associated with the attachment.
  // If present, repeated calls should return the same pointer for the same attachment instance.
  EXPECT_EQ(ctime1, ctime2);

  // If non-null, the returned pointer should be usable with basic GDateTime API.
  if (ctime1) {
    // Should not crash; also validates the pointer is a real GDateTime instance.
    gchar* iso = g_date_time_format_iso8601(ctime1);
    ASSERT_NE(iso, nullptr);
    g_free(iso);

    // Reference/unreference should be safe.
    GDateTime* ref = g_date_time_ref(ctime1);
    ASSERT_NE(ref, nullptr);
    g_date_time_unref(ref);
  }

  g_object_unref(attachment);
}

TEST_F(PopplerAttachmentGetCTimeTest_2272, MayReturnNullWhenCreationTimeUnavailable_2272) {
  const std::string pdf_path = FindAnyPdfWithAttachments_2272();
  if (pdf_path.empty()) GTEST_SKIP() << "No attachment PDF found (set POPPLER_TEST_DATADIR).";

  PopplerDocument* doc = LoadDocument_2272(pdf_path);
  ASSERT_NE(doc, nullptr) << "Failed to load PDF: " << pdf_path;

  GList* list = poppler_document_get_attachments(doc);
  g_object_unref(doc);
  if (!list) GTEST_SKIP() << "No attachments list returned for: " << pdf_path;
  std::unique_ptr<GList, GListDeleter_2272> holder(list);

  // Boundary coverage: if any attachment lacks ctime, ensure API returns nullptr for it.
  bool found_null_ctime = false;
  for (GList* it = holder.get(); it; it = it->next) {
    if (!it->data) continue;
    PopplerAttachment* att = POPPLER_ATTACHMENT(it->data);
    GDateTime* ctime = poppler_attachment_get_ctime(att);
    if (ctime == nullptr) {
      found_null_ctime = true;
      EXPECT_EQ(poppler_attachment_get_ctime(att), nullptr);
      break;
    }
  }

  if (!found_null_ctime) {
    GTEST_SKIP() << "All attachments in fixture have non-null ctime; boundary case not observable.";
  }
}

TEST_F(PopplerAttachmentGetCTimeTest_2272, NullAttachmentReturnsNullIfGuarded_2272) {
  // Error case (observable through interface): if implementation uses GLib-style guards,
  // passing nullptr should return nullptr (and may log a critical).
  //
  // If the implementation does not guard against nullptr, this test may crash, revealing
  // a robustness issue for invalid inputs.
  GDateTime* ctime = poppler_attachment_get_ctime(nullptr);
  EXPECT_EQ(ctime, nullptr);
}

}  // namespace