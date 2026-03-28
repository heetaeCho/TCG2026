// File: poppler-document-get-attachments-test_2156.cc
//
// Unit tests for poppler_document_get_attachments()
// Target: ./TestProjects/poppler/glib/poppler-document.cc
//
// NOTE: These tests treat the implementation as a black box and only verify
// observable behavior via the public GLib/Poppler interface.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerDocumentGetAttachmentsTest_2156 : public ::testing::Test {
protected:
  static std::string BuildPdfWithEmbeddedFiles(
      const std::vector<std::pair<std::string, std::string>>& files) {
    // Builds a minimal PDF with an /EmbeddedFiles name tree entry in the catalog.
    //
    // This is test data generation (not re-implementing any Poppler logic).
    //
    // Objects layout (object numbers):
    // 1: Catalog (references Pages + Names/EmbeddedFiles)
    // 2: Pages
    // 3: Page
    // 4: Contents stream (empty)
    // Then for each file i (0-based):
    //   EmbeddedFile stream: obj = 5 + i*2
    //   FileSpec dict:       obj = 6 + i*2

    auto pdf_escape = [](const std::string& s) -> std::string {
      // Escape parentheses/backslashes in PDF literal strings.
      std::string out;
      out.reserve(s.size());
      for (char c : s) {
        if (c == '(' || c == ')' || c == '\\') out.push_back('\\');
        out.push_back(c);
      }
      return out;
    };

    std::vector<std::string> objs;

    // Placeholder entries up to max object id; we'll push in order.
    // We'll assemble exact objects as strings and later compute xref offsets.
    const int base_embedded_obj = 5;
    const int n_files = static_cast<int>(files.size());
    const int max_obj = (n_files == 0) ? 4 : (base_embedded_obj + (n_files * 2) - 1);

    objs.resize(max_obj + 1); // index == obj number, leave [0] unused.

    // 4: Empty contents stream.
    {
      std::string stream_data; // empty
      std::ostringstream o;
      o << "4 0 obj\n"
        << "<< /Length " << stream_data.size() << " >>\n"
        << "stream\n"
        << stream_data
        << "\nendstream\n"
        << "endobj\n";
      objs[4] = o.str();
    }

    // 3: Page (minimal).
    {
      std::ostringstream o;
      o << "3 0 obj\n"
        << "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
        << "endobj\n";
      objs[3] = o.str();
    }

    // 2: Pages.
    {
      std::ostringstream o;
      o << "2 0 obj\n"
        << "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        << "endobj\n";
      objs[2] = o.str();
    }

    // Embedded files objects.
    for (int i = 0; i < n_files; ++i) {
      const int emb_obj = base_embedded_obj + i * 2;
      const int fs_obj = emb_obj + 1;

      const std::string& filename = files[i].first;
      const std::string& content = files[i].second;

      // EmbeddedFile stream.
      {
        std::ostringstream o;
        o << emb_obj << " 0 obj\n"
          << "<< /Type /EmbeddedFile /Length " << content.size() << " >>\n"
          << "stream\n"
          << content
          << "\nendstream\n"
          << "endobj\n";
        objs[emb_obj] = o.str();
      }

      // FileSpec dictionary referencing the embedded stream.
      {
        std::ostringstream o;
        o << fs_obj << " 0 obj\n"
          << "<< /Type /Filespec /F (" << pdf_escape(filename) << ")"
          << " /EF << /F " << emb_obj << " 0 R >> >>\n"
          << "endobj\n";
        objs[fs_obj] = o.str();
      }
    }

    // 1: Catalog with /Names << /EmbeddedFiles << /Names [ (name) fileSpecRef ... ] >> >>
    {
      std::ostringstream names_array;
      names_array << "[";
      for (int i = 0; i < n_files; ++i) {
        const int fs_obj = base_embedded_obj + i * 2 + 1;
        names_array << " (" << pdf_escape(files[i].first) << ") " << fs_obj << " 0 R";
      }
      names_array << " ]";

      std::ostringstream o;
      o << "1 0 obj\n"
        << "<< /Type /Catalog /Pages 2 0 R";
      if (n_files > 0) {
        o << " /Names << /EmbeddedFiles << /Names " << names_array.str() << " >> >>";
      }
      o << " >>\n"
        << "endobj\n";
      objs[1] = o.str();
    }

    // PDF header.
    std::string pdf;
    pdf.reserve(2048);
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n";

    // Compute offsets.
    std::vector<long long> xref_offsets(max_obj + 1, 0);
    for (int obj = 1; obj <= max_obj; ++obj) {
      xref_offsets[obj] = static_cast<long long>(pdf.size());
      pdf += objs[obj];
    }

    const long long xref_start = static_cast<long long>(pdf.size());

    // Xref table.
    {
      std::ostringstream x;
      x << "xref\n";
      x << "0 " << (max_obj + 1) << "\n";
      // Object 0: free entry.
      x << "0000000000 65535 f \n";
      for (int obj = 1; obj <= max_obj; ++obj) {
        // 10-digit, zero-padded offsets, generation 00000, in-use 'n'
        char buf[64];
        std::snprintf(buf, sizeof(buf), "%010lld 00000 n \n", xref_offsets[obj]);
        x << buf;
      }
      pdf += x.str();
    }

    // Trailer.
    {
      std::ostringstream t;
      t << "trailer\n"
        << "<< /Size " << (max_obj + 1) << " /Root 1 0 R >>\n"
        << "startxref\n"
        << xref_start << "\n"
        << "%%EOF\n";
      pdf += t.str();
    }

    return pdf;
  }

  static PopplerDocument* NewDocFromPdfDataOrFail(const std::string& pdf_bytes) {
    GError* error = nullptr;
    PopplerDocument* doc =
        poppler_document_new_from_data(pdf_bytes.data(),
                                       static_cast<int>(pdf_bytes.size()),
                                       /*password=*/nullptr,
                                       &error);
    if (!doc) {
      std::string msg = "poppler_document_new_from_data failed";
      if (error && error->message) {
        msg += ": ";
        msg += error->message;
      }
      if (error) g_error_free(error);
      ADD_FAILURE() << msg;
      return nullptr;
    }
    if (error) g_error_free(error);
    return doc;
  }

  static void FreeAttachmentList(GList* list) {
    for (GList* l = list; l != nullptr; l = l->next) {
      if (l->data) {
        // PopplerAttachment is a GObject in poppler-glib.
        g_object_unref(G_OBJECT(l->data));
      }
    }
    g_list_free(list);
  }
};

TEST_F(PopplerDocumentGetAttachmentsTest_2156, NullDocumentReturnsNull_2156) {
  // g_return_val_if_fail should return NULL for invalid instance.
  // It may log a critical; we expect and consume it to avoid test noise/fatality.
  g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");
  GList* list = poppler_document_get_attachments(nullptr);
  g_test_assert_expected_messages();
  EXPECT_EQ(list, nullptr);
}

TEST_F(PopplerDocumentGetAttachmentsTest_2156, NonDocumentInstanceReturnsNull_2156) {
  // Pass a non-PopplerDocument GObject to trigger POPPLER_IS_DOCUMENT failure.
  GObject* not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_a_doc, nullptr);

  g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");
  GList* list = poppler_document_get_attachments(reinterpret_cast<PopplerDocument*>(not_a_doc));
  g_test_assert_expected_messages();

  EXPECT_EQ(list, nullptr);
  g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetAttachmentsTest_2156, NoAttachmentsReturnsNull_2156) {
  // PDF with no /EmbeddedFiles entry should produce NULL list (not an empty list).
  const std::string pdf = BuildPdfWithEmbeddedFiles({});
  PopplerDocument* doc = NewDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  GList* list = poppler_document_get_attachments(doc);
  EXPECT_EQ(list, nullptr);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetAttachmentsTest_2156, SingleAttachmentReturnsOneElement_2156) {
  const std::string pdf =
      BuildPdfWithEmbeddedFiles({{"hello.txt", "Hello from embedded file!\n"}});
  PopplerDocument* doc = NewDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  GList* list = poppler_document_get_attachments(doc);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(g_list_length(list), 1u);

  // Verify returned element is a PopplerAttachment (observable via type macro).
  ASSERT_NE(list->data, nullptr);
  EXPECT_TRUE(POPPLER_IS_ATTACHMENT(list->data));

  FreeAttachmentList(list);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetAttachmentsTest_2156, MultipleAttachmentsReturnsAll_2156) {
  const std::string pdf = BuildPdfWithEmbeddedFiles({
      {"a.txt", "AAA\n"},
      {"b.txt", "BBB\n"},
  });
  PopplerDocument* doc = NewDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  GList* list = poppler_document_get_attachments(doc);
  ASSERT_NE(list, nullptr);
  EXPECT_EQ(g_list_length(list), 2u);

  for (GList* l = list; l != nullptr; l = l->next) {
    ASSERT_NE(l->data, nullptr);
    EXPECT_TRUE(POPPLER_IS_ATTACHMENT(l->data));
  }

  FreeAttachmentList(list);
  g_object_unref(doc);
}

TEST_F(PopplerDocumentGetAttachmentsTest_2156, CallingTwiceProducesIndependentLists_2156) {
  const std::string pdf = BuildPdfWithEmbeddedFiles({
      {"one.bin", "1"},
      {"two.bin", "22"},
      {"three.bin", "333"},
  });
  PopplerDocument* doc = NewDocFromPdfDataOrFail(pdf);
  ASSERT_NE(doc, nullptr);

  GList* list1 = poppler_document_get_attachments(doc);
  GList* list2 = poppler_document_get_attachments(doc);

  ASSERT_NE(list1, nullptr);
  ASSERT_NE(list2, nullptr);

  EXPECT_EQ(g_list_length(list1), 3u);
  EXPECT_EQ(g_list_length(list2), 3u);

  // Free both lists; should not affect each other and should not crash.
  FreeAttachmentList(list1);
  FreeAttachmentList(list2);

  g_object_unref(doc);
}

} // namespace