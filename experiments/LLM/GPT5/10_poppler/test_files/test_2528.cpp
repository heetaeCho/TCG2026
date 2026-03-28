// File: poppler-structure-element-get-id-2528-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include "poppler-private.h"

#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerStructureElementGetIdTest_2528 : public ::testing::Test {
protected:
  static std::string BuildTaggedPdfWithStructElemId_2528(const char *id_literal) {
    // Build a minimal Tagged PDF with a structure tree:
    // StructTreeRoot -> StructElem(/Document) -> StructElem(/P, /ID (id_literal))
    // And a single marked-content item (MCID 0) on the only page.
    //
    // This is intentionally minimal and only aims to be parseable by Poppler for
    // structure traversal + ID retrieval.

    struct Obj {
      int num;
      std::string body; // full "obj ... endobj" payload without the header/footer
    };

    std::vector<Obj> objs;

    // 1: Catalog
    objs.push_back({1,
                    "<< /Type /Catalog\n"
                    "   /Pages 2 0 R\n"
                    "   /StructTreeRoot 10 0 R\n"
                    ">>\n"});

    // 2: Pages
    objs.push_back({2,
                    "<< /Type /Pages\n"
                    "   /Kids [ 3 0 R ]\n"
                    "   /Count 1\n"
                    ">>\n"});

    // 3: Page
    objs.push_back({3,
                    "<< /Type /Page\n"
                    "   /Parent 2 0 R\n"
                    "   /MediaBox [ 0 0 200 200 ]\n"
                    "   /Contents 4 0 R\n"
                    "   /Resources << /Font << /F1 5 0 R >> >>\n"
                    ">>\n"});

    // 4: Contents stream with a marked-content sequence (MCID 0).
    // Use BDC/EMC to create tagged content.
    const char *stream =
        "/P <</MCID 0>> BDC\n"
        "BT\n"
        "/F1 12 Tf\n"
        "10 100 Td\n"
        "(Hello) Tj\n"
        "ET\n"
        "EMC\n";
    {
      std::ostringstream oss;
      oss << "<< /Length " << std::strlen(stream) << " >>\n"
          << "stream\n"
          << stream
          << "endstream\n";
      objs.push_back({4, oss.str()});
    }

    // 5: Font
    objs.push_back({5,
                    "<< /Type /Font\n"
                    "   /Subtype /Type1\n"
                    "   /BaseFont /Helvetica\n"
                    ">>\n"});

    // 10: StructTreeRoot (minimal; ParentTree omitted on purpose)
    // K -> top-level struct element 11
    objs.push_back({10,
                    "<< /Type /StructTreeRoot\n"
                    "   /K [ 11 0 R ]\n"
                    ">>\n"});

    // 11: Document struct element (no /ID)
    // K -> paragraph struct element 12
    objs.push_back({11,
                    "<< /Type /StructElem\n"
                    "   /S /Document\n"
                    "   /P 10 0 R\n"
                    "   /K [ 12 0 R ]\n"
                    ">>\n"});

    // 12: Paragraph struct element with /ID and an MCR child pointing to MCID 0
    // on page 3.
    {
      std::ostringstream oss;
      oss << "<< /Type /StructElem\n"
          << "   /S /P\n"
          << "   /P 11 0 R\n"
          << "   /ID (" << id_literal << ")\n"
          << "   /K [ << /Type /MCR /Pg 3 0 R /MCID 0 >> ]\n"
          << ">>\n";
      objs.push_back({12, oss.str()});
    }

    // Write PDF with xref.
    std::ostringstream out;
    out << "%PDF-1.7\n";
    std::vector<long> offsets(13, 0);

    for (const auto &o : objs) {
      offsets[o.num] = static_cast<long>(out.tellp());
      out << o.num << " 0 obj\n" << o.body << "endobj\n";
    }

    const long xref_pos = static_cast<long>(out.tellp());
    out << "xref\n";
    out << "0 13\n";
    // object 0
    out << "0000000000 65535 f \n";
    for (int i = 1; i <= 12; ++i) {
      char buf[32];
      std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
      out << buf;
    }

    out << "trailer\n";
    out << "<< /Size 13\n"
        << "   /Root 1 0 R\n"
        << ">>\n";
    out << "startxref\n" << xref_pos << "\n";
    out << "%%EOF\n";

    return out.str();
  }

  static std::pair<std::string, std::string> WriteTempPdfAndGetUri_2528(
      const std::string &pdf_bytes) {
    gchar tmpl[] = "poppler-struct-id-2528-XXXXXX.pdf";
    // g_mkstemp modifies the template in-place and returns an fd.
    int fd = g_mkstemp(tmpl);
    EXPECT_GE(fd, 0);

    gssize total = 0;
    const char *data = pdf_bytes.data();
    gssize len = static_cast<gssize>(pdf_bytes.size());

    while (total < len) {
      gssize w = write(fd, data + total, static_cast<size_t>(len - total));
      if (w <= 0) {
        break;
      }
      total += w;
    }
    close(fd);

    EXPECT_EQ(total, len);

    gchar *uri = g_filename_to_uri(tmpl, nullptr, nullptr);
    EXPECT_NE(uri, nullptr);

    std::string path(tmpl);
    std::string uri_str(uri);
    g_free(uri);

    return {path, uri_str};
  }

  static PopplerDocument *LoadDocFromPdfBytes_2528(const std::string &pdf_bytes) {
    auto [path, uri] = WriteTempPdfAndGetUri_2528(pdf_bytes);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
    if (error) {
      // Ensure we clean up temp file even on failure.
      g_remove(path.c_str());
      ADD_FAILURE() << "poppler_document_new_from_file failed: "
                    << (error->message ? error->message : "(no message)");
      g_error_free(error);
      return nullptr;
    }
    // Stash path for cleanup by attaching as qdata to the doc.
    g_object_set_data_full(G_OBJECT(doc), "tmp-pdf-path-2528",
                           g_strdup(path.c_str()), (GDestroyNotify)g_free);
    return doc;
  }

  static void CleanupTempPdfForDoc_2528(PopplerDocument *doc) {
    if (!doc) {
      return;
    }
    gchar *path = static_cast<gchar *>(g_object_get_data(G_OBJECT(doc), "tmp-pdf-path-2528"));
    if (path) {
      g_remove(path);
    }
  }

  static PopplerStructureElement *FindFirstElementWithId_2528(PopplerDocument *doc,
                                                              std::string *out_id) {
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
      return nullptr;
    }

    PopplerStructureElement *found = nullptr;
    gchar *found_id = nullptr;

    // Depth-first traversal.
    std::function<void(PopplerStructureElementIter *)> walk = [&](PopplerStructureElementIter *it) {
      if (!it || found) {
        return;
      }
      do {
        PopplerStructureElement *elem = poppler_structure_element_iter_get_element(it);
        if (elem && !found) {
          gchar *id = poppler_structure_element_get_id(elem);
          if (id) {
            found = static_cast<PopplerStructureElement *>(g_object_ref(elem));
            found_id = id; // own it
            return;
          }
        }

        PopplerStructureElementIter *child = poppler_structure_element_iter_get_child(it);
        if (child) {
          walk(child);
          poppler_structure_element_iter_free(child);
          if (found) {
            return;
          }
        }
      } while (poppler_structure_element_iter_next(it));
    };

    walk(iter);
    poppler_structure_element_iter_free(iter);

    if (found && out_id && found_id) {
      *out_id = found_id;
    }
    if (found_id) {
      g_free(found_id);
    }
    return found;
  }
};

TEST_F(PopplerStructureElementGetIdTest_2528, ReturnsNullAndLogsCriticalOnNullPointer_2528) {
  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL,
                        "*assertion*POPPLER_IS_STRUCTURE_ELEMENT*failed*");
  gchar *id = poppler_structure_element_get_id(nullptr);
  g_test_assert_expected_messages();
  EXPECT_EQ(id, nullptr);
}

TEST_F(PopplerStructureElementGetIdTest_2528, ReturnsNullAndLogsCriticalOnWrongGType_2528) {
  GObject *not_structure_element = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(not_structure_element, nullptr);

  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL,
                        "*assertion*POPPLER_IS_STRUCTURE_ELEMENT*failed*");
  gchar *id = poppler_structure_element_get_id(
      reinterpret_cast<PopplerStructureElement *>(not_structure_element));
  g_test_assert_expected_messages();

  EXPECT_EQ(id, nullptr);
  g_object_unref(not_structure_element);
}

TEST_F(PopplerStructureElementGetIdTest_2528, ReturnsNullAndLogsCriticalWhenElemIsNull_2528) {
  PopplerStructureElement *se =
      reinterpret_cast<PopplerStructureElement *>(g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
  ASSERT_NE(se, nullptr);

  // Ensure elem is null (this is only test scaffolding; observable behavior is the NULL return + log).
  se->elem = nullptr;

  g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL,
                        "*assertion*poppler_structure_element->elem != nullptr*failed*");
  gchar *id = poppler_structure_element_get_id(se);
  g_test_assert_expected_messages();

  EXPECT_EQ(id, nullptr);
  g_object_unref(se);
}

TEST_F(PopplerStructureElementGetIdTest_2528, ReturnsIdForElementThatDefinesId_2528) {
  const std::string pdf = BuildTaggedPdfWithStructElemId_2528("elem-id-2528");
  PopplerDocument *doc = LoadDocFromPdfBytes_2528(pdf);
  ASSERT_NE(doc, nullptr);

  std::string got;
  PopplerStructureElement *elem = FindFirstElementWithId_2528(doc, &got);
  ASSERT_NE(elem, nullptr);

  // Verify returned ID matches what we embedded.
  EXPECT_EQ(got, "elem-id-2528");

  // Also verify calling again returns a freshly allocated string (transfer full).
  gchar *id2 = poppler_structure_element_get_id(elem);
  ASSERT_NE(id2, nullptr);
  EXPECT_STREQ(id2, "elem-id-2528");
  g_free(id2);

  g_object_unref(elem);
  CleanupTempPdfForDoc_2528(doc);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetIdTest_2528, ReturnsNullForElementWithoutIdInSameTree_2528) {
  const std::string pdf = BuildTaggedPdfWithStructElemId_2528("elem-id-2528");
  PopplerDocument *doc = LoadDocFromPdfBytes_2528(pdf);
  ASSERT_NE(doc, nullptr);

  PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
  ASSERT_NE(iter, nullptr);

  // Root-level element should be the /Document StructElem we created (no /ID).
  PopplerStructureElement *root_elem = poppler_structure_element_iter_get_element(iter);
  ASSERT_NE(root_elem, nullptr);

  gchar *id = poppler_structure_element_get_id(root_elem);
  EXPECT_EQ(id, nullptr);

  poppler_structure_element_iter_free(iter);
  CleanupTempPdfForDoc_2528(doc);
  g_object_unref(doc);
}

TEST_F(PopplerStructureElementGetIdTest_2528, BoundaryEmptyIdStringIsReturnedAsEmpty_2528) {
  const std::string pdf = BuildTaggedPdfWithStructElemId_2528("");
  PopplerDocument *doc = LoadDocFromPdfBytes_2528(pdf);
  ASSERT_NE(doc, nullptr);

  std::string got;
  PopplerStructureElement *elem = FindFirstElementWithId_2528(doc, &got);
  ASSERT_NE(elem, nullptr);

  // If /ID is present but empty, we should still get a non-null string (empty).
  EXPECT_EQ(got, "");

  g_object_unref(elem);
  CleanupTempPdfForDoc_2528(doc);
  g_object_unref(doc);
}

} // namespace