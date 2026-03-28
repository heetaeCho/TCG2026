// poppler-attachment-save-to-callback-test_2279.cc
//
// Unit tests for poppler_attachment_save_to_callback()
// Constraints honored:
// - Treat implementation as black box (no private access, no reimplementation of internals).
// - Use only public Poppler GLib API to obtain PopplerAttachment instances (via a real PDF).
// - Verify observable behavior via return values, callback invocations, and error propagation.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>
#include <gio/gio.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

#include "poppler.h"  // Poppler GLib umbrella header in many builds.
                       // If your build uses a different include, replace accordingly, e.g.:
                       // #include <poppler/glib/poppler.h>

using ::testing::ElementsAreArray;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Gt;
using ::testing::IsEmpty;
using ::testing::Not;
using ::testing::SizeIs;

namespace {

// --- Helpers to create a minimal PDF with an embedded file (attachment) ---

static std::string BuildPdfWithSingleEmbeddedFile(const std::string &filename_in_pdf,
                                                 const std::string &payload_ascii) {
  // Build a minimal valid PDF with:
  // - Catalog /Names /EmbeddedFiles mapping the name to a Filespec.
  // - Filespec /EF pointing to an EmbeddedFile stream containing payload_ascii.
  //
  // Notes:
  // - payload is ASCII for simplicity (no binary escaping).
  // - Uses classic xref table with computed byte offsets.

  struct Obj {
    int num;
    std::string body;  // content between "obj\n" and "endobj\n"
  };

  const int kCatalog = 1;
  const int kFilespec = 2;
  const int kEmbeddedFile = 3;
  const int kPages = 4;
  const int kPage = 5;
  const int kContents = 6;

  auto esc_pdf_string = [](const std::string &s) -> std::string {
    // Minimal escaping for parentheses and backslashes.
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
      if (c == '(' || c == ')' || c == '\\') out.push_back('\\');
      out.push_back(c);
    }
    return out;
  };

  const std::string pdf_fname = esc_pdf_string(filename_in_pdf);
  const std::string payload = payload_ascii;  // keep as-is (ASCII)
  const int payload_len = static_cast<int>(payload.size());

  std::vector<Obj> objs;

  // 3 0 obj: EmbeddedFile stream
  {
    std::string body;
    body += "<< /Type /EmbeddedFile /Length " + std::to_string(payload_len) + " >>\n";
    body += "stream\n";
    body += payload;
    body += "\nendstream\n";
    objs.push_back({kEmbeddedFile, body});
  }

  // 2 0 obj: Filespec referencing the embedded file stream
  {
    std::string body;
    body += "<< /Type /Filespec\n";
    body += "   /F (" + pdf_fname + ")\n";
    body += "   /UF (" + pdf_fname + ")\n";
    body += "   /EF << /F " + std::to_string(kEmbeddedFile) + " 0 R >>\n";
    body += ">>\n";
    objs.push_back({kFilespec, body});
  }

  // 6 0 obj: empty page content
  {
    std::string body;
    body += "<< /Length 0 >>\n";
    body += "stream\n";
    body += "\nendstream\n";
    objs.push_back({kContents, body});
  }

  // 5 0 obj: a single page
  {
    std::string body;
    body += "<< /Type /Page /Parent " + std::to_string(kPages) + " 0 R\n";
    body += "   /MediaBox [0 0 200 200]\n";
    body += "   /Contents " + std::to_string(kContents) + " 0 R\n";
    body += ">>\n";
    objs.push_back({kPage, body});
  }

  // 4 0 obj: Pages
  {
    std::string body;
    body += "<< /Type /Pages /Count 1 /Kids [" + std::to_string(kPage) + " 0 R] >>\n";
    objs.push_back({kPages, body});
  }

  // 1 0 obj: Catalog with EmbeddedFiles name tree
  {
    std::string body;
    body += "<< /Type /Catalog\n";
    body += "   /Pages " + std::to_string(kPages) + " 0 R\n";
    body += "   /Names << /EmbeddedFiles << /Names [(" + pdf_fname + ") "
         + std::to_string(kFilespec) + " 0 R] >> >>\n";
    body += ">>\n";
    objs.push_back({kCatalog, body});
  }

  // Ensure objs are in object-number order for easier xref generation.
  std::sort(objs.begin(), objs.end(), [](const Obj &a, const Obj &b) { return a.num < b.num; });

  std::string out;
  out += "%PDF-1.4\n";
  out += "%\xE2\xE3\xCF\xD3\n";  // binary comment line

  // Track offsets: index by object number. We'll have objects 1..6.
  std::vector<long> offsets(7, 0);

  for (const auto &o : objs) {
    offsets[o.num] = static_cast<long>(out.size());
    out += std::to_string(o.num) + " 0 obj\n";
    out += o.body;
    out += "endobj\n";
  }

  const long xref_pos = static_cast<long>(out.size());

  out += "xref\n";
  out += "0 7\n";
  out += "0000000000 65535 f \n";
  for (int i = 1; i <= 6; i++) {
    char line[32];
    std::snprintf(line, sizeof(line), "%010ld 00000 n \n", offsets[i]);
    out += line;
  }

  out += "trailer\n";
  out += "<< /Size 7 /Root 1 0 R >>\n";
  out += "startxref\n";
  out += std::to_string(xref_pos) + "\n";
  out += "%%EOF\n";

  return out;
}

static std::string WriteTempFileOrDie(const std::string &bytes) {
  gchar *tmp_path = nullptr;
  GError *err = nullptr;

  // Create a temp file
  int fd = g_file_open_tmp("poppler-attachment-2279-XXXXXX.pdf", &tmp_path, &err);
  if (fd < 0 || tmp_path == nullptr) {
    std::string msg = "g_file_open_tmp failed";
    if (err) {
      msg += ": ";
      msg += err->message;
      g_error_free(err);
    }
    if (tmp_path) g_free(tmp_path);
    ADD_FAILURE() << msg;
    return "";
  }

#if defined(_WIN32)
  _close(fd);
  FILE *f = std::fopen(tmp_path, "wb");
#else
  FILE *f = fdopen(fd, "wb");
#endif
  if (!f) {
    close(fd);
    std::string p(tmp_path);
    g_free(tmp_path);
    ADD_FAILURE() << "fdopen/fopen failed for temp file: " << p;
    return "";
  }

  size_t written = std::fwrite(bytes.data(), 1, bytes.size(), f);
  std::fclose(f);

  std::string path(tmp_path);
  g_free(tmp_path);

  if (written != bytes.size()) {
    ADD_FAILURE() << "Failed to write complete PDF to temp file";
    return "";
  }
  return path;
}

static std::string PathToFileUri(const std::string &path) {
  // gio helper:
  GFile *f = g_file_new_for_path(path.c_str());
  gchar *uri = g_file_get_uri(f);
  std::string out(uri ? uri : "");
  if (uri) g_free(uri);
  g_object_unref(f);
  return out;
}

static PopplerAttachment *LoadSingleAttachmentOrDie(const std::string &pdf_path) {
  const std::string uri = PathToFileUri(pdf_path);

  GError *err = nullptr;
  PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), /*password=*/nullptr, &err);
  if (!doc) {
    std::string msg = "poppler_document_new_from_file failed";
    if (err) {
      msg += ": ";
      msg += err->message;
      g_error_free(err);
    }
    ADD_FAILURE() << msg;
    return nullptr;
  }

  // Prefer API that returns a list of attachments (common in poppler-glib).
  GList *attachments = poppler_document_get_attachments(doc);
  if (!attachments) {
    g_object_unref(doc);
    ADD_FAILURE() << "No attachments returned by poppler_document_get_attachments";
    return nullptr;
  }

  // Expect exactly one (for our crafted PDF).
  PopplerAttachment *att = POPPLER_ATTACHMENT(attachments->data);
  if (!att) {
    g_list_free(attachments);
    g_object_unref(doc);
    ADD_FAILURE() << "Attachment list contained null";
    return nullptr;
  }

  // Hold a ref for the caller; free list + doc.
  g_object_ref(att);
  g_list_free(attachments);
  g_object_unref(doc);
  return att;
}

// --- Callback capture ---

struct SaveCapture {
  std::string bytes;
  std::vector<size_t> chunk_sizes;
  int calls = 0;

  // Fail control:
  int fail_on_call = -1;               // if >=0, fail on that 0-based call index
  GQuark error_domain = 0;
  int error_code = 0;
  std::string error_message;
};

extern "C" gboolean SaveFuncCapture_2279(const gchar *buf,
                                        gsize count,
                                        gpointer user_data,
                                        GError **error) {
  auto *cap = static_cast<SaveCapture *>(user_data);
  cap->calls++;
  cap->chunk_sizes.push_back(static_cast<size_t>(count));
  cap->bytes.append(buf, buf + count);

  const int this_call = cap->calls - 1;
  if (cap->fail_on_call >= 0 && this_call == cap->fail_on_call) {
    if (error) {
      g_set_error(error,
                  cap->error_domain ? cap->error_domain : g_quark_from_static_string("test-2279"),
                  cap->error_code ? cap->error_code : 1,
                  "%s",
                  cap->error_message.empty() ? "save failed (test-2279)" : cap->error_message.c_str());
    }
    return FALSE;
  }
  return TRUE;
}

// Cleanup helper
static void RemoveFileBestEffort(const std::string &path) {
  if (path.empty()) return;
  g_remove(path.c_str());
}

class PopplerAttachmentSaveToCallbackTest_2279 : public ::testing::Test {
 public:
  void TearDown() override {
    for (const auto &p : temp_paths_) RemoveFileBestEffort(p);
    temp_paths_.clear();
  }

  std::string MakePdfWithAttachmentAndKeepPath(const std::string &name, const std::string &payload) {
    const std::string pdf = BuildPdfWithSingleEmbeddedFile(name, payload);
    std::string path = WriteTempFileOrDie(pdf);
    if (!path.empty()) temp_paths_.push_back(path);
    return path;
  }

 private:
  std::vector<std::string> temp_paths_;
};

}  // namespace

// ---- Tests ----

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, ReturnsFalseOnNullAttachment_2279) {
  // Observable behavior: g_return_val_if_fail should return FALSE for invalid attachment.
  SaveCapture cap;
  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(
      /*attachment=*/nullptr,
      /*save_func=*/SaveFuncCapture_2279,
      /*user_data=*/&cap,
      /*error=*/&err);

  EXPECT_FALSE(ok);
  EXPECT_EQ(cap.calls, 0);

  if (err) g_error_free(err);
}

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, SavesAllBytesAndInvokesCallbackAtLeastOnce_2279) {
  // Normal operation: payload smaller than BUF_SIZE should be delivered in one callback.
  const std::string payload = "Hello attachment!\nLine2\n";
  const std::string path = MakePdfWithAttachmentAndKeepPath("test.txt", payload);
  ASSERT_FALSE(path.empty());

  PopplerAttachment *att = LoadSingleAttachmentOrDie(path);
  ASSERT_NE(att, nullptr);

  SaveCapture cap;
  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(att, SaveFuncCapture_2279, &cap, &err);

  EXPECT_TRUE(ok);
  EXPECT_EQ(err, nullptr);
  EXPECT_THAT(cap.bytes, Eq(payload));
  EXPECT_THAT(cap.chunk_sizes, SizeIs(1));
  EXPECT_THAT(cap.chunk_sizes[0], Eq(payload.size()));
  EXPECT_EQ(cap.calls, 1);

  g_object_unref(att);
}

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, SplitsIntoMultipleChunksWhenPayloadExceedsBufSize_2279) {
  // Boundary/normal: payload > BUF_SIZE (1024) should yield multiple callback invocations.
  // We don't assume exact chunking beyond "no chunk should exceed BUF_SIZE" and all bytes preserved.
  std::string payload;
  payload.reserve(2500);
  for (int i = 0; i < 2500; i++) payload.push_back(static_cast<char>('A' + (i % 26)));

  const std::string path = MakePdfWithAttachmentAndKeepPath("big.bin", payload);
  ASSERT_FALSE(path.empty());

  PopplerAttachment *att = LoadSingleAttachmentOrDie(path);
  ASSERT_NE(att, nullptr);

  SaveCapture cap;
  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(att, SaveFuncCapture_2279, &cap, &err);

  EXPECT_TRUE(ok);
  EXPECT_EQ(err, nullptr);
  EXPECT_THAT(cap.bytes, Eq(payload));
  EXPECT_THAT(cap.chunk_sizes, SizeIs(Gt(1)));
  for (size_t sz : cap.chunk_sizes) {
    EXPECT_THAT(sz, Ge(static_cast<size_t>(1)));
    EXPECT_THAT(sz, ::testing::Le(static_cast<size_t>(1024)));
  }

  g_object_unref(att);
}

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, ExactBufSizePayloadUsesSingleChunk_2279) {
  // Boundary: exactly BUF_SIZE bytes should be emitted as a single chunk (common expectation),
  // but we keep assertions minimal: total bytes match and each chunk <= BUF_SIZE.
  std::string payload(1024, 'Z');

  const std::string path = MakePdfWithAttachmentAndKeepPath("exact.bin", payload);
  ASSERT_FALSE(path.empty());

  PopplerAttachment *att = LoadSingleAttachmentOrDie(path);
  ASSERT_NE(att, nullptr);

  SaveCapture cap;
  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(att, SaveFuncCapture_2279, &cap, &err);

  EXPECT_TRUE(ok);
  EXPECT_EQ(err, nullptr);
  EXPECT_THAT(cap.bytes, Eq(payload));
  ASSERT_THAT(cap.chunk_sizes, Not(IsEmpty()));
  for (size_t sz : cap.chunk_sizes) {
    EXPECT_THAT(sz, ::testing::Le(static_cast<size_t>(1024)));
  }

  // Stronger (but still black-box safe) expectation: typically 1 call for exactly BUF_SIZE.
  // If your Stream implementation splits differently, you can relax/remove this.
  EXPECT_EQ(cap.calls, 1);

  g_object_unref(att);
}

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, EmptyAttachmentReturnsTrueAndDoesNotInvokeCallback_2279) {
  // Boundary: empty stream should result in TRUE without calling save_func (since i==0 never triggers).
  const std::string payload;  // empty
  const std::string path = MakePdfWithAttachmentAndKeepPath("empty.dat", payload);
  ASSERT_FALSE(path.empty());

  PopplerAttachment *att = LoadSingleAttachmentOrDie(path);
  ASSERT_NE(att, nullptr);

  SaveCapture cap;
  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(att, SaveFuncCapture_2279, &cap, &err);

  EXPECT_TRUE(ok);
  EXPECT_EQ(err, nullptr);
  EXPECT_EQ(cap.calls, 0);
  EXPECT_TRUE(cap.bytes.empty());
  EXPECT_TRUE(cap.chunk_sizes.empty());

  g_object_unref(att);
}

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, PropagatesCallbackFailureAndStopsEarly_2279) {
  // Error/exceptional (observable): if save_func returns FALSE, the function returns FALSE and
  // exposes the error (if provided) and should not continue calling save_func.
  std::string payload;
  payload.reserve(2000);
  for (int i = 0; i < 2000; i++) payload.push_back(static_cast<char>('0' + (i % 10)));

  const std::string path = MakePdfWithAttachmentAndKeepPath("fail.bin", payload);
  ASSERT_FALSE(path.empty());

  PopplerAttachment *att = LoadSingleAttachmentOrDie(path);
  ASSERT_NE(att, nullptr);

  SaveCapture cap;
  cap.fail_on_call = 0;  // fail immediately on first chunk
  cap.error_domain = g_quark_from_static_string("save-fail-2279");
  cap.error_code = 2279;
  cap.error_message = "intentional failure";

  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(att, SaveFuncCapture_2279, &cap, &err);

  EXPECT_FALSE(ok);
  ASSERT_NE(err, nullptr);
  EXPECT_THAT(err->domain, Eq(cap.error_domain));
  EXPECT_THAT(err->code, Eq(cap.error_code));
  EXPECT_NE(std::string(err->message).find("intentional failure"), std::string::npos);

  // It should have called exactly once (failed on first call).
  EXPECT_EQ(cap.calls, 1);

  g_error_free(err);
  g_object_unref(att);
}

TEST_F(PopplerAttachmentSaveToCallbackTest_2279, FailureAfterFirstChunkReturnsFalseAndPreservesPartialData_2279) {
  // Error path: fail on second chunk; verify we saw at least 2 calls and captured partial bytes
  // up to the point of failure.
  std::string payload;
  payload.reserve(2500);
  for (int i = 0; i < 2500; i++) payload.push_back(static_cast<char>('a' + (i % 26)));

  const std::string path = MakePdfWithAttachmentAndKeepPath("partial.bin", payload);
  ASSERT_FALSE(path.empty());

  PopplerAttachment *att = LoadSingleAttachmentOrDie(path);
  ASSERT_NE(att, nullptr);

  SaveCapture cap;
  cap.fail_on_call = 1;  // fail on second callback
  cap.error_domain = g_quark_from_static_string("save-fail-2279b");
  cap.error_code = 2;
  cap.error_message = "fail on second chunk";

  GError *err = nullptr;

  gboolean ok = poppler_attachment_save_to_callback(att, SaveFuncCapture_2279, &cap, &err);

  EXPECT_FALSE(ok);
  ASSERT_NE(err, nullptr);
  EXPECT_NE(std::string(err->message).find("fail on second chunk"), std::string::npos);

  EXPECT_EQ(cap.calls, 2);

  // Partial bytes should be exactly the first chunk (and possibly the second chunk depending on
  // when the callback appends). Our callback appends before failing, so cap.bytes includes bytes
  // from the failing chunk too. Still observable and valid: it must be a prefix of payload.
  EXPECT_THAT(payload.substr(0, cap.bytes.size()), Eq(cap.bytes));

  g_error_free(err);
  g_object_unref(att);
}