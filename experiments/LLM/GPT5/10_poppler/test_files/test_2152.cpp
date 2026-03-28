// poppler_document_get_page_test_2152.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct GObjectDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};
template <typename T>
using GObjectPtr = std::unique_ptr<T, GObjectDeleter>;

struct GFreeDeleter {
  void operator()(gpointer p) const { g_free(p); }
};
using GCharPtr = std::unique_ptr<gchar, GFreeDeleter>;

static std::string WriteMinimalPdfWithNPages_2152(const std::string& path, int n_pages) {
  // Minimal PDF generator for testing (not related to Poppler internals).
  // Creates N pages with empty content streams.
  struct Obj {
    int num;
    std::string body;
  };

  if (n_pages < 1) n_pages = 1;

  std::vector<Obj> objs;

  // 1: Catalog
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});

  // 2: Pages
  {
    std::ostringstream kids;
    kids << "[ ";
    // Pages will be 3..(2+n_pages)
    for (int i = 0; i < n_pages; ++i) {
      kids << (3 + i) << " 0 R ";
    }
    kids << "]";
    std::ostringstream pages;
    pages << "<< /Type /Pages /Kids " << kids.str() << " /Count " << n_pages << " >>";
    objs.push_back({2, pages.str()});
  }

  // Page objects + content stream objects
  // Page i object number: 3+i
  // Content i object number: 3+n_pages+i
  for (int i = 0; i < n_pages; ++i) {
    const int page_obj = 3 + i;
    const int content_obj = 3 + n_pages + i;

    std::ostringstream page;
    page << "<< /Type /Page /Parent 2 0 R "
         << "/MediaBox [0 0 612 792] "
         << "/Contents " << content_obj << " 0 R >>";
    objs.push_back({page_obj, page.str()});

    // Empty content stream
    std::ostringstream content;
    content << "<< /Length 0 >>\nstream\n\nendstream";
    objs.push_back({content_obj, content.str()});
  }

  // Build PDF with xref
  std::ostringstream out;
  out << "%PDF-1.4\n";

  // Track offsets; xref includes object 0 plus max object.
  const int max_obj_num = 2 + 2 * n_pages;  // 1..(2+2n)
  std::vector<long> offsets(max_obj_num + 1, 0);

  auto tellp_long = [&out]() -> long {
    return static_cast<long>(out.tellp());
  };

  // Object 0 is the free object; offset 0 in xref.
  for (const auto& obj : objs) {
    offsets[obj.num] = tellp_long();
    out << obj.num << " 0 obj\n" << obj.body << "\nendobj\n";
  }

  const long xref_pos = tellp_long();
  out << "xref\n";
  out << "0 " << (max_obj_num + 1) << "\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= max_obj_num; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    out << buf << " 00000 n \n";
  }
  out << "trailer\n";
  out << "<< /Size " << (max_obj_num + 1) << " /Root 1 0 R >>\n";
  out << "startxref\n" << xref_pos << "\n%%EOF\n";

  std::ofstream f(path, std::ios::binary);
  f << out.str();
  f.close();

  return path;
}

static std::string MakeTempPdfPath_2152() {
  // mkstemp wants a mutable template ending in XXXXXX
  std::string templ = std::string(g_get_tmp_dir()) + G_DIR_SEPARATOR_S + "poppler_get_page_2152_XXXXXX.pdf";
  std::vector<char> buf(templ.begin(), templ.end());
  buf.push_back('\0');

  int fd = g_mkstemp(buf.data());
  if (fd >= 0) {
    close(fd);
  }
  return std::string(buf.data());
}

static std::string FilePathToUri_2152(const std::string& path) {
  GError* err = nullptr;
  gchar* uri = g_filename_to_uri(path.c_str(), nullptr, &err);
  if (!uri) {
    if (err) g_error_free(err);
    return std::string();
  }
  std::string s(uri);
  g_free(uri);
  return s;
}

class PopplerDocumentGetPageTest_2152 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (!tmp_path_.empty()) {
      g_remove(tmp_path_.c_str());
    }
  }

  GObjectPtr<PopplerDocument> LoadDocWithPages(int n_pages) {
    tmp_path_ = MakeTempPdfPath_2152();
    WriteMinimalPdfWithNPages_2152(tmp_path_, n_pages);

    const std::string uri = FilePathToUri_2152(tmp_path_);
    EXPECT_FALSE(uri.empty());

    GError* error = nullptr;
    PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    EXPECT_NE(doc, nullptr);
    if (error) {
      // If creation failed, surface the error message for debugging.
      ADD_FAILURE() << "poppler_document_new_from_file failed: " << error->message;
      g_error_free(error);
      return GObjectPtr<PopplerDocument>(nullptr);
    }
    return GObjectPtr<PopplerDocument>(doc);
  }

 private:
  std::string tmp_path_;
};

TEST_F(PopplerDocumentGetPageTest_2152, ValidIndexReturnsNonNullPage_2152) {
  auto doc = LoadDocWithPages(2);
  ASSERT_NE(doc.get(), nullptr);

  ASSERT_EQ(poppler_document_get_n_pages(doc.get()), 2);

  GObjectPtr<PopplerPage> page0(poppler_document_get_page(doc.get(), 0));
  ASSERT_NE(page0.get(), nullptr);
  EXPECT_EQ(poppler_page_get_index(page0.get()), 0);

  GObjectPtr<PopplerPage> page1(poppler_document_get_page(doc.get(), 1));
  ASSERT_NE(page1.get(), nullptr);
  EXPECT_EQ(poppler_page_get_index(page1.get()), 1);
}

TEST_F(PopplerDocumentGetPageTest_2152, BoundaryIndexZeroOnSinglePageDoc_2152) {
  auto doc = LoadDocWithPages(1);
  ASSERT_NE(doc.get(), nullptr);

  ASSERT_EQ(poppler_document_get_n_pages(doc.get()), 1);

  GObjectPtr<PopplerPage> page(poppler_document_get_page(doc.get(), 0));
  ASSERT_NE(page.get(), nullptr);
  EXPECT_EQ(poppler_page_get_index(page.get()), 0);
}

TEST_F(PopplerDocumentGetPageTest_2152, NegativeIndexReturnsNull_2152) {
  auto doc = LoadDocWithPages(2);
  ASSERT_NE(doc.get(), nullptr);

  ASSERT_EQ(poppler_document_get_n_pages(doc.get()), 2);

  PopplerPage* page = poppler_document_get_page(doc.get(), -1);
  EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentGetPageTest_2152, IndexEqualToNumPagesReturnsNull_2152) {
  auto doc = LoadDocWithPages(2);
  ASSERT_NE(doc.get(), nullptr);

  const int n = poppler_document_get_n_pages(doc.get());
  ASSERT_EQ(n, 2);

  PopplerPage* page = poppler_document_get_page(doc.get(), n);
  EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentGetPageTest_2152, LargeOutOfRangeIndexReturnsNull_2152) {
  auto doc = LoadDocWithPages(1);
  ASSERT_NE(doc.get(), nullptr);

  ASSERT_EQ(poppler_document_get_n_pages(doc.get()), 1);

  PopplerPage* page = poppler_document_get_page(doc.get(), 1000000);
  EXPECT_EQ(page, nullptr);
}

}  // namespace