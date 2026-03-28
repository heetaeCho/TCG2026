// poppler-fonts-iter-get-name-test-2221.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {

class TempFile {
 public:
  explicit TempFile(const std::string& suffix) {
    std::string tmpl = std::string(g_get_tmp_dir()) + "/poppler_ut_XXXXXX" + suffix;
    // mkstemp requires the XXXXXX be at the end; so create without suffix, then rename.
    std::string base_tmpl = std::string(g_get_tmp_dir()) + "/poppler_ut_XXXXXX";
    std::vector<char> path_buf(base_tmpl.begin(), base_tmpl.end());
    path_buf.push_back('\0');

    int fd = g_mkstemp(path_buf.data());
    EXPECT_GE(fd, 0);

    // Close immediately; we will write via GLib API.
    if (fd >= 0) {
      close(fd);
    }

    path_ = path_buf.data();

    if (!suffix.empty()) {
      std::string new_path = path_ + suffix;
      int rc = g_rename(path_.c_str(), new_path.c_str());
      EXPECT_EQ(rc, 0);
      path_ = new_path;
    }
  }

  ~TempFile() {
    if (!path_.empty()) {
      g_unlink(path_.c_str());
    }
  }

  const std::string& path() const { return path_; }

  std::string file_uri() const {
    // poppler_document_new_from_file expects a URI (e.g. file:///tmp/x.pdf)
    gchar* uri = g_filename_to_uri(path_.c_str(), /*hostname=*/nullptr, /*error=*/nullptr);
    std::string out = uri ? uri : "";
    if (uri) g_free(uri);
    return out;
  }

 private:
  std::string path_;
};

static std::string BuildPdfWithFonts(bool include_font_resources) {
  // Build a minimal, valid PDF. When include_font_resources==true, include:
  //  - F1: BaseFont /ABCDEF+Helvetica (subset-style tag)
  //  - F2: BaseFont /Helvetica
  //
  // We compute xref offsets dynamically to keep the PDF valid.
  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>\n"});
  // 2: Pages
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});

  // 3: Page (Resources depends on include_font_resources)
  std::string resources;
  if (include_font_resources) {
    resources =
        "<< /Font << /F1 4 0 R /F2 5 0 R >> >>";
  } else {
    resources = "<< >>";
  }

  // 6: Contents stream
  std::string content_stream;
  if (include_font_resources) {
    content_stream =
        "BT /F1 12 Tf 10 100 Td (Hi) Tj ET\n"
        "BT /F2 12 Tf 10  80 Td (Hi2) Tj ET\n";
  } else {
    // No font usage
    content_stream = "q\nQ\n";
  }

  // Page references /Contents 6 0 R always (we still include an empty-ish stream).
  std::string page =
      "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
      "   /Resources " +
      resources +
      "\n"
      "   /Contents 6 0 R >>\n";
  objs.push_back({3, page});

  if (include_font_resources) {
    // 4: subset-style font name
    objs.push_back({4, "<< /Type /Font /Subtype /Type1 /BaseFont /ABCDEF+Helvetica >>\n"});
    // 5: non-subset font name
    objs.push_back({5, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"});
  } else {
    // Still reserve object numbers 4 and 5? Not needed; we’ll just omit them and adjust /Size.
    // Keep object numbering contiguous by not adding them.
  }

  const int contents_obj_num = include_font_resources ? 6 : 4;
  const int trailer_size = contents_obj_num + 1;

  // Contents stream object
  {
    char len_buf[64];
    std::snprintf(len_buf, sizeof(len_buf), "%zu", content_stream.size());
    std::string contents =
        std::string("<< /Length ") + len_buf + " >>\n"
        "stream\n" +
        content_stream +
        "endstream\n";
    objs.push_back({contents_obj_num, contents});
  }

  std::string pdf;
  pdf += "%PDF-1.4\n";
  std::vector<long> offsets(trailer_size, -1);

  auto append_obj = [&](int num, const std::string& body) {
    offsets[num] = static_cast<long>(pdf.size());
    pdf += std::to_string(num) + " 0 obj\n";
    pdf += body;
    pdf += "endobj\n";
  };

  for (const auto& o : objs) {
    append_obj(o.num, o.body);
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 " + std::to_string(trailer_size) + "\n";
  pdf += "0000000000 65535 f \n";
  for (int i = 1; i < trailer_size; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
    pdf += buf;
  }
  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(trailer_size) + " /Root 1 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static void WriteFileOrFail(const std::string& path, const std::string& bytes) {
  GError* error = nullptr;
  gboolean ok = g_file_set_contents(path.c_str(), bytes.data(), static_cast<gssize>(bytes.size()), &error);
  ASSERT_TRUE(ok);
  if (error) {
    ADD_FAILURE() << "g_file_set_contents error: " << error->message;
    g_error_free(error);
  }
}

static PopplerDocument* LoadDocumentOrFail(const std::string& uri) {
  GError* error = nullptr;
  PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
  EXPECT_NE(doc, nullptr);
  if (!doc && error) {
    ADD_FAILURE() << "poppler_document_new_from_file failed: " << error->message;
  }
  if (error) g_error_free(error);
  return doc;
}

class PopplerFontsIterGetNameTest_2221 : public ::testing::Test {
 protected:
  static std::vector<std::string> ScanFontFullNames(PopplerDocument* doc) {
    std::vector<std::string> out;

    PopplerFontInfo* font_info = poppler_font_info_new(doc);
    EXPECT_NE(font_info, nullptr);
    if (!font_info) return out;

    const int n_pages = poppler_document_get_n_pages(doc);

    PopplerFontsIter* iter = nullptr;
    (void)poppler_font_info_scan(font_info, n_pages, &iter);

    if (!iter) {
      g_object_unref(font_info);
      return out;
    }

    do {
      const char* full = poppler_fonts_iter_get_full_name(iter);
      if (full) out.emplace_back(full);
    } while (poppler_fonts_iter_next(iter));

    poppler_fonts_iter_free(iter);
    g_object_unref(font_info);
    return out;
  }

  static std::vector<std::pair<std::string, std::string>> ScanFontFullAndShortNames(PopplerDocument* doc) {
    std::vector<std::pair<std::string, std::string>> out;

    PopplerFontInfo* font_info = poppler_font_info_new(doc);
    EXPECT_NE(font_info, nullptr);
    if (!font_info) return out;

    const int n_pages = poppler_document_get_n_pages(doc);

    PopplerFontsIter* iter = nullptr;
    (void)poppler_font_info_scan(font_info, n_pages, &iter);

    if (!iter) {
      g_object_unref(font_info);
      return out;
    }

    do {
      const char* full = poppler_fonts_iter_get_full_name(iter);
      const char* name = poppler_fonts_iter_get_name(iter);
      std::string full_s = full ? full : "";
      std::string name_s = name ? name : "";
      out.emplace_back(full_s, name_s);
    } while (poppler_fonts_iter_next(iter));

    poppler_fonts_iter_free(iter);
    g_object_unref(font_info);
    return out;
  }
};

TEST_F(PopplerFontsIterGetNameTest_2221, Normal_SubsetTaggedFullNameReturnsPostPlusSubstring_2221) {
  TempFile pdf(".pdf");
  WriteFileOrFail(pdf.path(), BuildPdfWithFonts(/*include_font_resources=*/true));

  PopplerDocument* doc = LoadDocumentOrFail(pdf.file_uri());
  ASSERT_NE(doc, nullptr);

  auto pairs = ScanFontFullAndShortNames(doc);
  g_object_unref(doc);

  // Find the subset-tagged font by the typical "ABCDEF+Name" pattern we injected.
  bool found_subset_full = false;
  bool verified_behavior = false;

  for (const auto& p : pairs) {
    const std::string& full = p.first;
    const std::string& name = p.second;

    if (full == "ABCDEF+Helvetica") {
      found_subset_full = true;

      // Observable behavior under test:
      // poppler_fonts_iter_get_name() should return the part after '+' for subset fonts.
      EXPECT_EQ(name, "Helvetica");
      verified_behavior = true;
    }
  }

  EXPECT_TRUE(found_subset_full) << "Expected to find injected subset-tagged font full name.";
  EXPECT_TRUE(verified_behavior) << "Expected get_name() behavior to be verifiable for subset-tagged font.";
}

TEST_F(PopplerFontsIterGetNameTest_2221, Normal_NonSubsetFontNameMatchesFullName_2221) {
  TempFile pdf(".pdf");
  WriteFileOrFail(pdf.path(), BuildPdfWithFonts(/*include_font_resources=*/true));

  PopplerDocument* doc = LoadDocumentOrFail(pdf.file_uri());
  ASSERT_NE(doc, nullptr);

  auto pairs = ScanFontFullAndShortNames(doc);
  g_object_unref(doc);

  bool found_helvetica = false;
  for (const auto& p : pairs) {
    const std::string& full = p.first;
    const std::string& name = p.second;

    if (full == "Helvetica") {
      found_helvetica = true;
      EXPECT_EQ(name, full) << "For non-subset fonts, get_name() is expected to match full name.";
    }
  }
  EXPECT_TRUE(found_helvetica) << "Expected to find injected non-subset Helvetica font.";
}

TEST_F(PopplerFontsIterGetNameTest_2221, Boundary_NoFontsFoundYieldsNullIterator_2221) {
  TempFile pdf(".pdf");
  WriteFileOrFail(pdf.path(), BuildPdfWithFonts(/*include_font_resources=*/false));

  PopplerDocument* doc = LoadDocumentOrFail(pdf.file_uri());
  ASSERT_NE(doc, nullptr);

  PopplerFontInfo* font_info = poppler_font_info_new(doc);
  ASSERT_NE(font_info, nullptr);

  const int n_pages = poppler_document_get_n_pages(doc);
  PopplerFontsIter* iter = nullptr;

  gboolean found = poppler_font_info_scan(font_info, n_pages, &iter);

  // Observable boundary behavior: If no fonts are present in scanned pages, Poppler may:
  //  - return FALSE and leave iter == nullptr (as shown in the reference manual example),
  //  - or return TRUE but still not provide an iterator.
  // We only assert the externally observable "no iterator to traverse" property.
  EXPECT_EQ(iter, nullptr);
  EXPECT_FALSE(found);

  g_object_unref(font_info);
  g_object_unref(doc);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerFontsIterGetNameTest_2221, Error_NullIterCausesDeath_2221) {
  // The interface does not document nullptr-safety; the implementation dereferences iter.
  // If the build enables death tests, verify it fails fast rather than silently succeeding.
  EXPECT_DEATH(
      {
        (void)poppler_fonts_iter_get_name(nullptr);
      },
      ".*");
}
#endif

}  // namespace