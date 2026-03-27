// File: poppler_ps_file_new_fd_test_2257.cc
#include <gtest/gtest.h>

#include <glib-object.h>
#include <glib.h>

#include <poppler.h>

#include <fcntl.h>
#include <unistd.h>

#include <string>

// Simple RAII for GObject*
template <typename T>
class GObjectPtr {
public:
  GObjectPtr() : ptr_(nullptr) {}
  explicit GObjectPtr(T* p) : ptr_(p) {}
  ~GObjectPtr() { reset(); }

  GObjectPtr(const GObjectPtr&) = delete;
  GObjectPtr& operator=(const GObjectPtr&) = delete;

  GObjectPtr(GObjectPtr&& other) noexcept : ptr_(other.ptr_) { other.ptr_ = nullptr; }
  GObjectPtr& operator=(GObjectPtr&& other) noexcept {
    if (this != &other) {
      reset();
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  T* get() const { return ptr_; }
  T* release() {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }
  void reset(T* p = nullptr) {
    if (ptr_) {
      g_object_unref(ptr_);
    }
    ptr_ = p;
  }
  explicit operator bool() const { return ptr_ != nullptr; }

private:
  T* ptr_;
};

// Minimal one-page PDF (kept small and deterministic for tests).
static const char kMinimalPdf_2257[] =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Length 0 >>\n"
    "stream\n"
    "endstream\n"
    "endobj\n"
    "xref\n"
    "0 5\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "0000000202 00000 n \n"
    "trailer\n"
    "<< /Size 5 /Root 1 0 R >>\n"
    "startxref\n"
    "260\n"
    "%%EOF\n";

class PopplerPsFileNewFdTest_2257 : public ::testing::Test {
protected:
  static std::string WriteTempPdfAndGetUri_2257(std::string* out_path) {
    char* tmp_path_c = nullptr;
    int fd = g_file_open_tmp("poppler_ps_file_new_fd_2257_XXXXXX.pdf", &tmp_path_c, nullptr);
    EXPECT_NE(fd, -1);
    ASSERT_NE(tmp_path_c, nullptr);

    // Write PDF bytes
    const gsize len = static_cast<gsize>(strlen(kMinimalPdf_2257));
    gssize written = write(fd, kMinimalPdf_2257, len);
    EXPECT_EQ(written, static_cast<gssize>(len));
    close(fd);

    std::string path(tmp_path_c);
    g_free(tmp_path_c);

    char* uri_c = g_filename_to_uri(path.c_str(), nullptr, nullptr);
    EXPECT_NE(uri_c, nullptr);
    std::string uri(uri_c);
    g_free(uri_c);

    if (out_path) *out_path = path;
    return uri;
  }

  static GObjectPtr<PopplerDocument> LoadMinimalDocument_2257(std::string* out_path) {
    std::string path;
    const std::string uri = WriteTempPdfAndGetUri_2257(&path);

    if (out_path) *out_path = path;

    GError* error = nullptr;
    PopplerDocument* doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &error);
    if (!doc) {
      if (error) {
        g_error_free(error);
      }
      return GObjectPtr<PopplerDocument>(nullptr);
    }
    if (error) {
      g_error_free(error);
    }
    return GObjectPtr<PopplerDocument>(doc);
  }

  static void RemoveTempFile_2257(const std::string& path) {
    if (!path.empty()) {
      g_remove(path.c_str());
    }
  }
};

TEST_F(PopplerPsFileNewFdTest_2257, ReturnsNullWhenDocumentIsNull_2257) {
  // fd and n_pages are valid, but document is not.
  PopplerPSFile* ps = poppler_ps_file_new_fd(nullptr, /*fd=*/0, /*first_page=*/0, /*n_pages=*/1);
  EXPECT_EQ(ps, nullptr);
}

TEST_F(PopplerPsFileNewFdTest_2257, ReturnsNullWhenFdIsMinusOne_2257) {
  std::string path;
  auto doc = LoadMinimalDocument_2257(&path);
  ASSERT_TRUE(doc);

  PopplerPSFile* ps =
      poppler_ps_file_new_fd(doc.get(), /*fd=*/-1, /*first_page=*/0, /*n_pages=*/1);
  EXPECT_EQ(ps, nullptr);

  RemoveTempFile_2257(path);
}

TEST_F(PopplerPsFileNewFdTest_2257, ReturnsNullWhenNPagesIsZeroOrNegative_2257) {
  std::string path;
  auto doc = LoadMinimalDocument_2257(&path);
  ASSERT_TRUE(doc);

  {
    PopplerPSFile* ps =
        poppler_ps_file_new_fd(doc.get(), /*fd=*/0, /*first_page=*/0, /*n_pages=*/0);
    EXPECT_EQ(ps, nullptr);
  }
  {
    PopplerPSFile* ps =
        poppler_ps_file_new_fd(doc.get(), /*fd=*/0, /*first_page=*/0, /*n_pages=*/-3);
    EXPECT_EQ(ps, nullptr);
  }

  RemoveTempFile_2257(path);
}

TEST_F(PopplerPsFileNewFdTest_2257, ReturnsPsFileForValidInputs_2257) {
  std::string path;
  auto doc = LoadMinimalDocument_2257(&path);
  ASSERT_TRUE(doc);

  int pipefd[2] = {-1, -1};
  ASSERT_EQ(pipe(pipefd), 0);

  PopplerPSFile* ps_raw =
      poppler_ps_file_new_fd(doc.get(), /*fd=*/pipefd[1], /*first_page=*/0, /*n_pages=*/1);
  ASSERT_NE(ps_raw, nullptr);

  // Observable behavior: it is a GObject and of the expected type.
  EXPECT_TRUE(G_IS_OBJECT(ps_raw));
  EXPECT_TRUE(G_TYPE_CHECK_INSTANCE_TYPE(reinterpret_cast<GTypeInstance*>(ps_raw), POPPLER_TYPE_PS_FILE));

  g_object_unref(ps_raw);

  close(pipefd[0]);
  close(pipefd[1]);
  RemoveTempFile_2257(path);
}

TEST_F(PopplerPsFileNewFdTest_2257, KeepsDocumentAliveUntilPsFileIsDestroyed_2257) {
  std::string path;
  auto doc = LoadMinimalDocument_2257(&path);
  ASSERT_TRUE(doc);

  // Use a weak ref to observe when the document is finalized (no private state access).
  struct WeakState {
    bool finalized = false;
  } state;

  g_object_weak_ref(
      G_OBJECT(doc.get()),
      [](gpointer data, GObject* /*where_the_object_was*/) {
        auto* st = static_cast<WeakState*>(data);
        st->finalized = true;
      },
      &state);

  int pipefd[2] = {-1, -1};
  ASSERT_EQ(pipe(pipefd), 0);

  GObjectPtr<PopplerPSFile> ps(
      poppler_ps_file_new_fd(doc.get(), /*fd=*/pipefd[1], /*first_page=*/0, /*n_pages=*/1));
  ASSERT_TRUE(ps);

  // Drop our strong reference to the document; it should still be kept alive by the PS file.
  doc.reset(nullptr);
  EXPECT_FALSE(state.finalized);

  // Now destroy the PS file; document should be allowed to finalize.
  ps.reset(nullptr);
  EXPECT_TRUE(state.finalized);

  close(pipefd[0]);
  close(pipefd[1]);
  RemoveTempFile_2257(path);
}

TEST_F(PopplerPsFileNewFdTest_2257, AcceptsNegativeFirstPageAsBoundaryInput_2257) {
  std::string path;
  auto doc = LoadMinimalDocument_2257(&path);
  ASSERT_TRUE(doc);

  int pipefd[2] = {-1, -1};
  ASSERT_EQ(pipe(pipefd), 0);

  // first_page has no documented/visible validation here; ensure it doesn't reject negatives.
  PopplerPSFile* ps =
      poppler_ps_file_new_fd(doc.get(), /*fd=*/pipefd[1], /*first_page=*/-5, /*n_pages=*/1);
  EXPECT_NE(ps, nullptr);

  if (ps) g_object_unref(ps);

  close(pipefd[0]);
  close(pipefd[1]);
  RemoveTempFile_2257(path);
}