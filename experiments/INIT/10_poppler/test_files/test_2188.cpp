// File: poppler-document-get-modification-date-test-2188.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstring>
#include <optional>
#include <string>
#include <vector>

namespace {

class ScopedGError {
public:
  ScopedGError() = default;
  ~ScopedGError() {
    if (err_) {
      g_error_free(err_);
      err_ = nullptr;
    }
  }
  GError **out() { return &err_; }
  GError *get() const { return err_; }

private:
  GError *err_ = nullptr;
};

template <typename T>
class ScopedGObject {
public:
  explicit ScopedGObject(T *ptr = nullptr) : ptr_(ptr) {}
  ~ScopedGObject() {
    if (ptr_) {
      g_object_unref(ptr_);
      ptr_ = nullptr;
    }
  }
  ScopedGObject(const ScopedGObject &) = delete;
  ScopedGObject &operator=(const ScopedGObject &) = delete;

  ScopedGObject(ScopedGObject &&other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }
  ScopedGObject &operator=(ScopedGObject &&other) noexcept {
    if (this != &other) {
      if (ptr_) {
        g_object_unref(ptr_);
      }
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  T *get() const { return ptr_; }
  T *release() {
    T *tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }

private:
  T *ptr_;
};

static std::string BuildMinimalPdfWithInfoDict(std::optional<std::string> mod_date_literal) {
  // Build a minimal PDF with a Catalog, Pages, Page, empty contents, and an Info dict.
  // If mod_date_literal is std::nullopt => Info dict does not contain /ModDate.
  // If mod_date_literal is present => /ModDate (<literal>) will be included as a PDF string literal.

  struct Obj {
    int num;
    std::string body;
  };

  std::vector<Obj> objs;
  objs.push_back({1, "<< /Type /Catalog /Pages 2 0 R >>"});
  objs.push_back({2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>"});
  objs.push_back({3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>"});
  objs.push_back({4, "<< /Length 0 >>\nstream\n\nendstream"});

  std::string info = "<< /Producer (poppler-test) ";
  if (mod_date_literal.has_value()) {
    info += "/ModDate ";
    info += "(";
    // Keep it simple: do not escape; tests only use safe ASCII without parentheses/backslashes.
    info += *mod_date_literal;
    info += ") ";
  }
  info += ">>";
  objs.push_back({5, info});

  std::string out;
  out += "%PDF-1.4\n";
  out += "%\xE2\xE3\xCF\xD3\n";

  std::vector<long> offsets;
  offsets.resize(6, 0); // objects 0..5

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += std::to_string(o.num);
    out += " 0 obj\n";
    out += o.body;
    out += "\nendobj\n";
  }

  const long xref_pos = static_cast<long>(out.size());
  out += "xref\n";
  out += "0 6\n";
  out += "0000000000 65535 f \n";

  auto fmt10 = [](long v) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%010ld", v);
    return std::string(buf);
  };

  for (int i = 1; i <= 5; ++i) {
    out += fmt10(offsets[i]);
    out += " 00000 n \n";
  }

  out += "trailer\n";
  out += "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos);
  out += "\n%%EOF\n";
  return out;
}

static std::string WriteTempFile(const std::string &bytes) {
  // Create a temporary file path
  gchar *tmpname = nullptr;
#if GLIB_CHECK_VERSION(2, 30, 0)
  tmpname = g_strdup_printf("%s%cpoppler_moddate_2188_XXXXXX.pdf", g_get_tmp_dir(), G_DIR_SEPARATOR);
#else
  tmpname = g_strdup("poppler_moddate_2188_XXXXXX.pdf");
#endif

  int fd = g_mkstemp(tmpname);
  if (fd == -1) {
    std::string path = tmpname ? tmpname : "";
    g_free(tmpname);
    return path;
  }

  // Write bytes
  const gssize to_write = static_cast<gssize>(bytes.size());
  gssize written = 0;
  while (written < to_write) {
    const gssize w = static_cast<gssize>(::write(fd, bytes.data() + written, to_write - written));
    if (w <= 0) break;
    written += w;
  }
  ::close(fd);

  std::string path = tmpname;
  g_free(tmpname);
  return path;
}

static ScopedGObject<PopplerDocument> LoadPopplerDocumentFromPath(const std::string &path, GError **error_out) {
  gchar *uri = g_filename_to_uri(path.c_str(), nullptr, error_out);
  if (!uri) {
    return ScopedGObject<PopplerDocument>(nullptr);
  }

  PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, error_out);
  g_free(uri);
  return ScopedGObject<PopplerDocument>(doc);
}

class PopplerDocumentGetModificationDateTest_2188 : public ::testing::Test {
protected:
  void TearDown() override {
    for (const auto &p : temp_paths_) {
      if (!p.empty()) {
        g_remove(p.c_str());
      }
    }
    temp_paths_.clear();
  }

  std::string MakeTempPdf(std::optional<std::string> mod_date_literal) {
    const std::string pdf = BuildMinimalPdfWithInfoDict(mod_date_literal);
    const std::string path = WriteTempFile(pdf);
    temp_paths_.push_back(path);
    return path;
  }

private:
  std::vector<std::string> temp_paths_;
};

} // namespace

TEST_F(PopplerDocumentGetModificationDateTest_2188, NullDocumentReturnsMinusOne_2188) {
  // g_return_val_if_fail() should return -1 for invalid document.
  EXPECT_EQ((time_t)-1, poppler_document_get_modification_date(nullptr));
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, ValidDocumentWithModDateReturnsNonMinusOne_2188) {
  const std::string path = MakeTempPdf(std::string("D:19700101000000Z"));

  ScopedGError err;
  auto doc = LoadPopplerDocumentFromPath(path, err.out());
  ASSERT_NE(nullptr, doc.get()) << (err.get() ? err.get()->message : "Failed to load document");

  const time_t t = poppler_document_get_modification_date(doc.get());
  EXPECT_NE((time_t)-1, t);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithoutModDateReturnsMinusOne_2188) {
  const std::string path = MakeTempPdf(std::nullopt);

  ScopedGError err;
  auto doc = LoadPopplerDocumentFromPath(path, err.out());
  ASSERT_NE(nullptr, doc.get()) << (err.get() ? err.get()->message : "Failed to load document");

  const time_t t = poppler_document_get_modification_date(doc.get());
  EXPECT_EQ((time_t)-1, t);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithInvalidModDateReturnsMinusOne_2188) {
  // Provide a clearly invalid date string so conversion should fail (observable via return value).
  const std::string path = MakeTempPdf(std::string("NOT_A_PDF_DATE"));

  ScopedGError err;
  auto doc = LoadPopplerDocumentFromPath(path, err.out());
  ASSERT_NE(nullptr, doc.get()) << (err.get() ? err.get()->message : "Failed to load document");

  const time_t t = poppler_document_get_modification_date(doc.get());
  EXPECT_EQ((time_t)-1, t);
}