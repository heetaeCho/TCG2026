// poppler_document_new_from_fd_test_2144.cc
#include <gtest/gtest.h>

#include <poppler.h>

#include <errno.h>
#include <fcntl.h>
#include <glib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>
#include <vector>

namespace {

struct GErrorDeleter {
  void operator()(GError *e) const { g_clear_error(&e); }
};

using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;

struct FdCloser {
  int fd{-1};
  explicit FdCloser(int f = -1) : fd(f) {}
  ~FdCloser() {
    if (fd != -1) close(fd);
  }
  FdCloser(const FdCloser &) = delete;
  FdCloser &operator=(const FdCloser &) = delete;
  FdCloser(FdCloser &&o) noexcept : fd(o.fd) { o.fd = -1; }
  FdCloser &operator=(FdCloser &&o) noexcept {
    if (this != &o) {
      if (fd != -1) close(fd);
      fd = o.fd;
      o.fd = -1;
    }
    return *this;
  }
};

struct TempFile {
  int fd{-1};
  std::string path;

  TempFile() {
    char tmpl[] = "/tmp/poppler_fd_test_XXXXXX";
    int tfd = ::mkstemp(tmpl);
    if (tfd == -1) {
      // In unit tests, fail hard if we can't create a temp file.
      ADD_FAILURE() << "mkstemp failed: " << strerror(errno);
      return;
    }
    path = tmpl;
    fd = tfd;
  }

  ~TempFile() {
    if (fd != -1) close(fd);
    if (!path.empty()) ::unlink(path.c_str());
  }

  TempFile(const TempFile &) = delete;
  TempFile &operator=(const TempFile &) = delete;
};

static bool WriteAll(int fd, const void *buf, size_t n) {
  const uint8_t *p = static_cast<const uint8_t *>(buf);
  size_t off = 0;
  while (off < n) {
    ssize_t w = ::write(fd, p + off, n - off);
    if (w < 0) {
      if (errno == EINTR) continue;
      return false;
    }
    off += static_cast<size_t>(w);
  }
  return true;
}

static void Append(std::string &out, const std::string &s) { out.append(s); }

static std::vector<uint8_t> MakeMinimalPdfBytes() {
  // Build a tiny, valid PDF with correct xref offsets.
  // This is test data generation, not re-implementing poppler logic.
  std::string pdf;
  Append(pdf, "%PDF-1.4\n");
  std::vector<long> obj_off(6, -1);

  auto mark = [&](int objnum) { obj_off[objnum] = static_cast<long>(pdf.size()); };

  // 1: Catalog
  mark(1);
  Append(pdf, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

  // 2: Pages
  mark(2);
  Append(pdf, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

  // 3: Page
  mark(3);
  Append(pdf,
         "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
         "/Contents 4 0 R >>\nendobj\n");

  // 4: Empty contents stream
  mark(4);
  Append(pdf, "4 0 obj\n<< /Length 0 >>\nstream\nendstream\nendobj\n");

  // xref
  const long xref_off = static_cast<long>(pdf.size());
  Append(pdf, "xref\n");
  Append(pdf, "0 5\n");
  Append(pdf, "0000000000 65535 f \n");
  for (int i = 1; i <= 4; ++i) {
    char line[32];
    // 10-digit zero-padded offset, then generation and in-use marker.
    snprintf(line, sizeof(line), "%010ld 00000 n \n", obj_off[i]);
    Append(pdf, line);
  }

  // trailer
  Append(pdf, "trailer\n");
  Append(pdf, "<< /Size 5 /Root 1 0 R >>\n");
  Append(pdf, "startxref\n");
  {
    char line[64];
    snprintf(line, sizeof(line), "%ld\n", xref_off);
    Append(pdf, line);
  }
  Append(pdf, "%%EOF\n");

  return std::vector<uint8_t>(pdf.begin(), pdf.end());
}

static bool IsFdClosed(int fd) {
  errno = 0;
  int flags = ::fcntl(fd, F_GETFL);
  return (flags == -1 && errno == EBADF);
}

class PopplerDocumentNewFromFdTest_2144 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Ensure GLib warnings don't carry across tests.
  }
};

}  // namespace

TEST_F(PopplerDocumentNewFromFdTest_2144, ReturnsNullForMinusOneFd_2144) {
  GError *err_raw = nullptr;

  PopplerDocument *doc = poppler_document_new_from_fd(-1, /*password=*/nullptr, &err_raw);

  EXPECT_EQ(doc, nullptr);
  // g_return_val_if_fail typically returns early without setting GError.
  EXPECT_EQ(err_raw, nullptr);
}

TEST_F(PopplerDocumentNewFromFdTest_2144, SetsErrorForClosedFd_2144) {
  // Create and close a valid fd number, then pass it (fd != -1 but invalid).
  TempFile tf;
  ASSERT_NE(tf.fd, -1);
  int fd = tf.fd;
  tf.fd = -1;  // prevent TempFile dtor from closing again
  ASSERT_EQ(::close(fd), 0);

  GError *err_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_fd(fd, /*password=*/nullptr, &err_raw);

  GErrorPtr err(err_raw);

  EXPECT_EQ(doc, nullptr);
  ASSERT_NE(err.get(), nullptr);
  EXPECT_EQ(err->domain, G_FILE_ERROR);
  // EBADF should map to G_FILE_ERROR_BADF.
  EXPECT_EQ(err->code, G_FILE_ERROR_BADF);
  EXPECT_TRUE(err->message != nullptr);
}

TEST_F(PopplerDocumentNewFromFdTest_2144, RejectsWriteOnlyFdAndClosesIt_2144) {
  TempFile tf;
  ASSERT_NE(tf.path.size(), 0u);

  // Re-open write-only.
  int wfd = ::open(tf.path.c_str(), O_WRONLY);
  ASSERT_NE(wfd, -1);

  // Do not let TempFile close wfd (it only tracks tf.fd). Manage separately.
  int fd_under_test = wfd;

  GError *err_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_fd(fd_under_test, /*password=*/nullptr, &err_raw);

  GErrorPtr err(err_raw);

  EXPECT_EQ(doc, nullptr);
  ASSERT_NE(err.get(), nullptr);
  EXPECT_EQ(err->domain, G_FILE_ERROR);
  EXPECT_EQ(err->code, G_FILE_ERROR_BADF);
  ASSERT_NE(err->message, nullptr);
  EXPECT_NE(std::string(err->message).find("not readable"), std::string::npos);

  // Observable side-effect: the function closes the fd on this failure path.
  EXPECT_TRUE(IsFdClosed(fd_under_test));
}

TEST_F(PopplerDocumentNewFromFdTest_2144, ReturnsDocumentForRegularFilePdf_2144) {
  auto pdf = MakeMinimalPdfBytes();

  TempFile tf;
  ASSERT_NE(tf.fd, -1);

  ASSERT_TRUE(WriteAll(tf.fd, pdf.data(), pdf.size()));
  ASSERT_EQ(::lseek(tf.fd, 0, SEEK_SET), 0);

  // Use a separate read-only fd, so we can independently manage the temp file fd lifetime.
  int rfd = ::open(tf.path.c_str(), O_RDONLY);
  ASSERT_NE(rfd, -1);
  FdCloser closer(rfd);

  GError *err_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_fd(rfd, /*password=*/nullptr, &err_raw);
  GErrorPtr err(err_raw);

  ASSERT_EQ(err.get(), nullptr) << (err ? err->message : "");
  ASSERT_NE(doc, nullptr);

  // Basic observable behavior through public API: n_pages should be >= 1 for our PDF.
  int n_pages = poppler_document_get_n_pages(doc);
  EXPECT_GE(n_pages, 1);

  g_object_unref(doc);
}

TEST_F(PopplerDocumentNewFromFdTest_2144, ReturnsDocumentForPipeFdPdf_2144) {
  auto pdf = MakeMinimalPdfBytes();

  int fds[2] = {-1, -1};
  ASSERT_EQ(::pipe(fds), 0);
  FdCloser rcloser(fds[0]);
  FdCloser wcloser(fds[1]);

  ASSERT_TRUE(WriteAll(fds[1], pdf.data(), pdf.size()));
  // Close write end to signal EOF.
  wcloser.~FdCloser();
  fds[1] = -1;

  GError *err_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_fd(fds[0], /*password=*/nullptr, &err_raw);
  GErrorPtr err(err_raw);

  ASSERT_EQ(err.get(), nullptr) << (err ? err->message : "");
  ASSERT_NE(doc, nullptr);

  EXPECT_GE(poppler_document_get_n_pages(doc), 1);

  g_object_unref(doc);

  // Success path should not necessarily close the fd; avoid asserting ownership.
}

TEST_F(PopplerDocumentNewFromFdTest_2144, InvalidPdfReturnsNullAndSetsError_2144) {
  // Provide non-PDF data; observable outcome should be failure with an error.
  const char junk[] = "this is not a pdf";

  TempFile tf;
  ASSERT_NE(tf.fd, -1);
  ASSERT_TRUE(WriteAll(tf.fd, junk, sizeof(junk)));
  ASSERT_EQ(::lseek(tf.fd, 0, SEEK_SET), 0);

  int rfd = ::open(tf.path.c_str(), O_RDONLY);
  ASSERT_NE(rfd, -1);
  FdCloser closer(rfd);

  GError *err_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_fd(rfd, /*password=*/nullptr, &err_raw);
  GErrorPtr err(err_raw);

  EXPECT_EQ(doc, nullptr);
  EXPECT_NE(err.get(), nullptr);
}

TEST_F(PopplerDocumentNewFromFdTest_2144, EmptyPasswordDoesNotCrashOnInvalidPdf_2144) {
  // Boundary-ish: password provided but empty string.
  const char junk[] = "still not a pdf";

  TempFile tf;
  ASSERT_NE(tf.fd, -1);
  ASSERT_TRUE(WriteAll(tf.fd, junk, sizeof(junk)));
  ASSERT_EQ(::lseek(tf.fd, 0, SEEK_SET), 0);

  int rfd = ::open(tf.path.c_str(), O_RDONLY);
  ASSERT_NE(rfd, -1);
  FdCloser closer(rfd);

  GError *err_raw = nullptr;
  PopplerDocument *doc = poppler_document_new_from_fd(rfd, /*password=*/"", &err_raw);
  GErrorPtr err(err_raw);

  EXPECT_EQ(doc, nullptr);
  EXPECT_NE(err.get(), nullptr);
}