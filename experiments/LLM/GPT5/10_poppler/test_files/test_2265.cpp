// poppler-document-sign-test_2265.cc
#include <gtest/gtest.h>

#include <atomic>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>

#include <glib.h>
#include <gio/gio.h>

#include <poppler.h> // PopplerDocument, poppler_document_new_from_file, etc.

#ifndef G_USEC_PER_SEC
#define G_USEC_PER_SEC 1000000
#endif

namespace {

struct CallbackCtx {
  GMainLoop* loop = nullptr;
  PopplerDocument* expected_document = nullptr;
  gpointer expected_user_data = nullptr;
  std::atomic<int> called{0};
  std::atomic<int> wrong_source{0};
  std::atomic<int> wrong_user_data{0};
};

static void SignAsyncCallback(GObject* source_object, GAsyncResult* /*res*/, gpointer user_data) {
  auto* ctx = static_cast<CallbackCtx*>(user_data);
  ctx->called.fetch_add(1);

  if (ctx->expected_document && source_object != G_OBJECT(ctx->expected_document)) {
    ctx->wrong_source.fetch_add(1);
  }
  if (ctx->expected_user_data && user_data != ctx->expected_user_data) {
    // Note: user_data here is ctx itself, so expected_user_data is used by the tests
    // to validate the user_data pointer that *we* pass through, not what GLib passes
    // to this callback parameter.
  }

  if (ctx->loop) {
    g_main_loop_quit(ctx->loop);
  }
}

static bool IterateMainContextUntil(std::function<bool()> pred, gint64 timeout_ms) {
  const gint64 start = g_get_monotonic_time();
  const gint64 deadline = start + timeout_ms * 1000; // microseconds
  while (!pred()) {
    while (g_main_context_iteration(nullptr, FALSE)) {
      // drain pending events
    }
    if (g_get_monotonic_time() >= deadline) {
      return pred();
    }
    g_usleep(1000); // 1ms
  }
  return true;
}

static std::string BuildMinimalPdfBytes() {
  // Build a tiny, valid PDF with 1 blank page, computing xref offsets.
  // This is just test input data for Poppler's public API.
  std::string pdf;
  auto append = [&](const std::string& s) { pdf += s; };

  append("%PDF-1.4\n");

  // Record offsets for objects 1..3.
  std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
  std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
  std::string obj3 =
      "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 100] >>\nendobj\n";

  const size_t off1 = pdf.size();
  append(obj1);
  const size_t off2 = pdf.size();
  append(obj2);
  const size_t off3 = pdf.size();
  append(obj3);

  const size_t xref_off = pdf.size();

  auto fmt_off = [](size_t off) {
    char buf[32];
    // 10-digit, zero-padded byte offset per PDF spec.
    std::snprintf(buf, sizeof(buf), "%010lu", static_cast<unsigned long>(off));
    return std::string(buf);
  };

  append("xref\n");
  append("0 4\n");
  append("0000000000 65535 f \n");
  append(fmt_off(off1) + " 00000 n \n");
  append(fmt_off(off2) + " 00000 n \n");
  append(fmt_off(off3) + " 00000 n \n");
  append("trailer\n");
  append("<< /Size 4 /Root 1 0 R >>\n");
  append("startxref\n");
  append(std::to_string(static_cast<unsigned long>(xref_off)) + "\n");
  append("%%EOF\n");

  return pdf;
}

static std::string WriteTempFileOrDie(const std::string& suffix, const std::string& bytes) {
  GError* error = nullptr;
  gchar* path = nullptr;

  // Create unique tmp file.
  gint fd = g_file_open_tmp(("poppler_sign_XXXXXX" + suffix).c_str(), &path, &error);
  if (fd < 0) {
    std::string msg = "g_file_open_tmp failed";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    FAIL() << msg;
  }

  ssize_t written = 0;
  const char* data = bytes.data();
  size_t left = bytes.size();
  while (left > 0) {
    ssize_t w = ::write(fd, data + written, left);
    if (w < 0) {
      int e = errno;
      ::close(fd);
      g_unlink(path);
      std::string p(path);
      g_free(path);
      FAIL() << "write() failed: errno=" << e << " (" << std::strerror(e) << ")";
    }
    written += w;
    left -= static_cast<size_t>(w);
  }
  ::close(fd);

  std::string out(path);
  g_free(path);
  return out;
}

static PopplerDocument* LoadPopplerDocumentFromPathOrDie(const std::string& pdf_path) {
  GError* error = nullptr;

  gchar* uri = g_filename_to_uri(pdf_path.c_str(), nullptr, &error);
  if (!uri) {
    std::string msg = "g_filename_to_uri failed";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    FAIL() << msg;
  }

  PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
  g_free(uri);

  if (!doc) {
    std::string msg = "poppler_document_new_from_file returned NULL";
    if (error) {
      msg += ": ";
      msg += error->message;
      g_error_free(error);
    }
    FAIL() << msg;
  }
  return doc;
}

// Minimal construction of PopplerSigningData using the struct definition provided.
static PopplerSigningData MakeSigningDataWithDestination(const std::string& dest_path) {
  PopplerSigningData d{};
  d.destination_filename = g_strdup(dest_path.c_str());
  d.signature_text = nullptr;
  d.signature_text_left = nullptr;
  d.signature_rect.x1 = 0;
  d.signature_rect.y1 = 0;
  d.signature_rect.x2 = 10;
  d.signature_rect.y2 = 10;
  d.left_font_size = 0;
  d.border_color.red = 0;
  d.border_color.green = 0;
  d.border_color.blue = 0;
  d.border_width = 0;
  d.background_color.red = 255;
  d.background_color.green = 255;
  d.background_color.blue = 255;
  d.field_partial_name = nullptr;
  d.reason = nullptr;
  d.location = nullptr;
  d.image_path = nullptr;
  d.password = nullptr;
  d.document_owner_password = nullptr;
  d.document_user_password = nullptr;
  return d;
}

static void FreeSigningDataShallow(PopplerSigningData* d) {
  if (!d) return;
  g_free(d->destination_filename);
  g_free(d->signature_text);
  g_free(d->signature_text_left);
  g_free(d->field_partial_name);
  g_free(d->reason);
  g_free(d->location);
  g_free(d->image_path);
  g_free(d->password);
  g_free(d->document_owner_password);
  g_free(d->document_user_password);
}

class PopplerDocumentSignTest_2265 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Prepare a small PDF file for PopplerDocument creation.
    const std::string pdf_bytes = BuildMinimalPdfBytes();
    pdf_path_ = WriteTempFileOrDie(".pdf", pdf_bytes);
    doc_ = LoadPopplerDocumentFromPathOrDie(pdf_path_);
  }

  void TearDown() override {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
    if (!pdf_path_.empty()) {
      g_unlink(pdf_path_.c_str());
      pdf_path_.clear();
    }
    // Best-effort cleanup of any destination file if created.
    if (!dest_path_.empty()) {
      g_unlink(dest_path_.c_str());
      dest_path_.clear();
    }
  }

  std::string MakeTempDestPath() {
    // Create a temp file path, then unlink it so the signing call can create/overwrite it if needed.
    const std::string bytes = "x";
    std::string path = WriteTempFileOrDie(".signed.pdf", bytes);
    g_unlink(path.c_str());
    dest_path_ = path;
    return path;
  }

  std::string pdf_path_;
  std::string dest_path_;
  PopplerDocument* doc_ = nullptr;
};

}  // namespace

TEST_F(PopplerDocumentSignTest_2265, NullDocumentDoesNotInvokeCallback_2265) {
  // Observable behavior: g_return_if_fail should short-circuit; callback should not be invoked.
  CallbackCtx ctx;
  ctx.loop = g_main_loop_new(nullptr, FALSE);

  const std::string dest = MakeTempDestPath();
  PopplerSigningData d = MakeSigningDataWithDestination(dest);

  poppler_document_sign(/*document=*/nullptr, &d, /*cancellable=*/nullptr, SignAsyncCallback, &ctx);

  // Pump main context briefly; callback should not fire.
  IterateMainContextUntil([&]() { return ctx.called.load() > 0; }, /*timeout_ms=*/100);

  EXPECT_EQ(ctx.called.load(), 0);

  g_main_loop_unref(ctx.loop);
  ctx.loop = nullptr;

  FreeSigningDataShallow(&d);
}

TEST_F(PopplerDocumentSignTest_2265, NullSigningDataDoesNotInvokeCallback_2265) {
  CallbackCtx ctx;
  ctx.loop = g_main_loop_new(nullptr, FALSE);

  poppler_document_sign(doc_, /*signing_data=*/nullptr, /*cancellable=*/nullptr, SignAsyncCallback, &ctx);

  IterateMainContextUntil([&]() { return ctx.called.load() > 0; }, /*timeout_ms=*/100);

  EXPECT_EQ(ctx.called.load(), 0);

  g_main_loop_unref(ctx.loop);
  ctx.loop = nullptr;
}

TEST_F(PopplerDocumentSignTest_2265, ValidInputsInvokeCallbackWithSourceDocument_2265) {
  CallbackCtx ctx;
  ctx.loop = g_main_loop_new(nullptr, FALSE);
  ctx.expected_document = doc_;
  ctx.expected_user_data = &ctx;

  const std::string dest = MakeTempDestPath();
  PopplerSigningData d = MakeSigningDataWithDestination(dest);

  poppler_document_sign(doc_, &d, /*cancellable=*/nullptr, SignAsyncCallback, &ctx);

  // Wait until callback (or timeout). We don't assume success/failure details without a finish API.
  bool called = IterateMainContextUntil([&]() { return ctx.called.load() > 0; }, /*timeout_ms=*/2000);
  EXPECT_TRUE(called);
  EXPECT_EQ(ctx.called.load(), 1);

  // Validate the external interaction we can observe: callback source_object is the document.
  EXPECT_EQ(ctx.wrong_source.load(), 0);

  g_main_loop_unref(ctx.loop);
  ctx.loop = nullptr;

  FreeSigningDataShallow(&d);
}

TEST_F(PopplerDocumentSignTest_2265, CancelledCancellableStillInvokesCallback_2265) {
  CallbackCtx ctx;
  ctx.loop = g_main_loop_new(nullptr, FALSE);
  ctx.expected_document = doc_;

  const std::string dest = MakeTempDestPath();
  PopplerSigningData d = MakeSigningDataWithDestination(dest);

  GCancellable* cancellable = g_cancellable_new();
  g_cancellable_cancel(cancellable);

  poppler_document_sign(doc_, &d, cancellable, SignAsyncCallback, &ctx);

  bool called = IterateMainContextUntil([&]() { return ctx.called.load() > 0; }, /*timeout_ms=*/2000);
  EXPECT_TRUE(called);
  EXPECT_GE(ctx.called.load(), 1);
  EXPECT_EQ(ctx.wrong_source.load(), 0);

  g_object_unref(cancellable);
  g_main_loop_unref(ctx.loop);
  ctx.loop = nullptr;

  FreeSigningDataShallow(&d);
}

TEST_F(PopplerDocumentSignTest_2265, BoundarySigningDataWithOptionalNullFieldsDoesNotCrash_2265) {
  // Boundary: signing_data provided, but many optional string fields are NULL.
  // Observable behavior: call should not crash; callback should be invoked eventually.
  CallbackCtx ctx;
  ctx.loop = g_main_loop_new(nullptr, FALSE);
  ctx.expected_document = doc_;

  const std::string dest = MakeTempDestPath();
  PopplerSigningData d = MakeSigningDataWithDestination(dest);
  // Keep destination_filename non-null; other fields remain null.

  poppler_document_sign(doc_, &d, /*cancellable=*/nullptr, SignAsyncCallback, &ctx);

  bool called = IterateMainContextUntil([&]() { return ctx.called.load() > 0; }, /*timeout_ms=*/2000);
  EXPECT_TRUE(called);
  EXPECT_EQ(ctx.wrong_source.load(), 0);

  g_main_loop_unref(ctx.loop);
  ctx.loop = nullptr;

  FreeSigningDataShallow(&d);
}