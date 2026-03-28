// poppler-fonts-iter-get-substitute-name-test_2222.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace {

struct GCharDeleter {
  void operator()(gchar *p) const { g_free(p); }
};
using UniqueGChar = std::unique_ptr<gchar, GCharDeleter>;

struct GErrorDeleter {
  void operator()(GError *e) const {
    if (e) g_error_free(e);
  }
};
using UniqueGError = std::unique_ptr<GError, GErrorDeleter>;

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};
template <typename T>
using UniqueGObject = std::unique_ptr<T, GObjectUnrefDeleter>;

struct FontsIterFreeDeleter {
  void operator()(PopplerFontsIter *it) const {
    if (it) poppler_fonts_iter_free(it);
  }
};
using UniqueFontsIter = std::unique_ptr<PopplerFontsIter, FontsIterFreeDeleter>;

static bool WriteMinimalPdfWithHelvetica(const std::string &path) {
  // Build a tiny, valid PDF with a single Type1 Helvetica font (not embedded).
  // We compute xref offsets so Poppler can parse it reliably.
  struct Obj {
    int num;
    std::string body;  // body should include trailing newline(s) as needed
  };

  const std::string content_stream = "BT /F1 12 Tf 72 120 Td (Hello) Tj ET\n";
  std::ostringstream obj5;
  obj5 << "<< /Length " << content_stream.size() << " >>\n"
       << "stream\n"
       << content_stream
       << "endstream\n";

  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>\n"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"});
  objs.push_back({3,
                  "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200]\n"
                  "   /Resources << /Font << /F1 4 0 R >> >>\n"
                  "   /Contents 5 0 R >>\n"});
  objs.push_back({4, "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"});
  objs.push_back({5, obj5.str()});

  std::ostringstream out;
  out << "%PDF-1.4\n";

  // Offsets for xref: index is object number; element is byte offset.
  // Entry 0 is the free object.
  std::vector<long> offsets(6, 0);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.tellp());
    out << o.num << " 0 obj\n" << o.body << "endobj\n";
  }

  const long xref_pos = static_cast<long>(out.tellp());
  out << "xref\n";
  out << "0 6\n";
  out << "0000000000 65535 f \n";
  for (int i = 1; i <= 5; ++i) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", offsets[i]);
    out << buf << " 00000 n \n";
  }
  out << "trailer\n";
  out << "<< /Size 6 /Root 1 0 R >>\n";
  out << "startxref\n";
  out << xref_pos << "\n";
  out << "%%EOF\n";

  std::ofstream ofs(path, std::ios::binary);
  if (!ofs) return false;
  const std::string bytes = out.str();
  ofs.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
  ofs.close();
  return static_cast<bool>(ofs);
}

class PopplerFontsIterGetSubstituteNameTest_2222 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Create temp file path
    gchar *tmp_name = nullptr;
    GError *err = nullptr;

    // GLib's template must end with "XXXXXX"
    int fd = g_file_open_tmp("poppler-fonts-iter-XXXXXX.pdf", &tmp_name, &err);
    UniqueGError uerr(err);
    ASSERT_NE(fd, -1) << (uerr ? uerr->message : "g_file_open_tmp failed");
    ASSERT_NE(tmp_name, nullptr);
#ifdef _WIN32
    _close(fd);
#else
    close(fd);
#endif
    tmp_path_.reset(tmp_name);

    ASSERT_TRUE(WriteMinimalPdfWithHelvetica(tmp_path_.get()));

    // Convert to URI and open document
    err = nullptr;
    gchar *uri = g_filename_to_uri(tmp_path_.get(), nullptr, &err);
    uerr.reset(err);
    ASSERT_NE(uri, nullptr) << (uerr ? uerr->message : "g_filename_to_uri failed");
    UniqueGChar uuri(uri);

    err = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uuri.get(), nullptr, &err);
    uerr.reset(err);
    ASSERT_NE(doc, nullptr) << (uerr ? uerr->message : "poppler_document_new_from_file failed");
    doc_.reset(doc);

    PopplerFontsIter *it = poppler_document_get_fonts_iter(doc_.get());
    ASSERT_NE(it, nullptr);
    iter_.reset(it);
  }

  void TearDown() override {
    iter_.reset();
    doc_.reset();

    // Best-effort cleanup of temp file
    if (tmp_path_) {
      std::remove(tmp_path_.get());
    }
  }

  UniqueGChar tmp_path_{nullptr};
  UniqueGObject<PopplerDocument> doc_{nullptr};
  UniqueFontsIter iter_{nullptr};
};

TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, ReturnsNullOrNonEmpty_NoCrash_2222) {
  // Behavior under test: function is callable for a valid iterator and does not crash.
  const char *sub = poppler_fonts_iter_get_substitute_name(iter_.get());
  if (sub) {
    EXPECT_GT(std::strlen(sub), 0u);
  } else {
    SUCCEED();  // Substitute name may legitimately be absent.
  }
}

TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, StableWithinSameIteratorPosition_2222) {
  // Behavior under test: repeated calls at the same iterator position are consistent.
  const char *sub1 = poppler_fonts_iter_get_substitute_name(iter_.get());
  const char *sub2 = poppler_fonts_iter_get_substitute_name(iter_.get());

  if (!sub1 || !sub2) {
    EXPECT_EQ(sub1, sub2);
  } else {
    EXPECT_STREQ(sub1, sub2);
  }
}

TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, AfterNextCall_IsCallable_NoCrash_2222) {
  // Boundary behavior: calling after advancing the iterator (if possible) remains safe/callable.
  // We do not assert specific contents because it depends on font discovery/substitution.
  if (poppler_fonts_iter_next(iter_.get())) {
    const char *sub = poppler_fonts_iter_get_substitute_name(iter_.get());
    if (sub) {
      EXPECT_GT(std::strlen(sub), 0u);
    }
  } else {
    // If there's only one font entry, this test still validates boundary handling by not forcing UB.
    SUCCEED();
  }
}

TEST_F(PopplerFontsIterGetSubstituteNameTest_2222, NullIter_DeathTest_2222) {
  // Exceptional/error case: the function does not document null-safety; verify it fails fast.
  // This is an observable behavior test (process termination) and does not infer internal logic.
#if GTEST_HAS_DEATH_TEST
  ASSERT_DEATH(
      {
        (void)poppler_fonts_iter_get_substitute_name(nullptr);
      },
      "");
#else
  GTEST_SKIP() << "Death tests are not supported on this platform/configuration.";
#endif
}

}  // namespace