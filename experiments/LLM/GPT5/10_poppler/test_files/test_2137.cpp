// poppler-document-new-from-pdfdoc-test-2137.cc
//
// Unit tests for _poppler_document_new_from_pdfdoc() (static in poppler-document.cc)
//
// Notes:
// - We treat implementation as a black box and only verify observable outcomes:
//   * return value
//   * GError domain/code/message
//   * observable external interaction: CairoOutputDev::startDoc called with the PDFDoc pointer
// - To access the static function, we include the .cc directly in this TU.
// - Where the real build provides GLib/Poppler types, those will be used.
//   Where they are not available in the trimmed test harness, minimal fallbacks below kick in.

#include <gtest/gtest.h>

#include <cerrno>
#include <cstdarg>
#include <cstring>
#include <memory>
#include <string>

//
// -------- Minimal fallbacks (only used if the real headers are not present) --------
//
#if __has_include(<glib.h>)
  #include <glib.h>
#else
  using gchar = char;
  using gint = int;
  using guint = unsigned int;
  using gpointer = void*;

  struct GError {
    gint domain = 0;
    gint code = 0;
    gchar* message = nullptr;
  };

  inline void g_clear_error(GError** err) {
    if (!err || !*err) return;
    delete[] (*err)->message;
    delete *err;
    *err = nullptr;
  }

  inline const char* g_strerror(int e) { return std::strerror(e); }

  inline int g_file_error_from_errno(int e) { return e; }

  // Very small g_set_error clone (format is "%s" only as used by the SUT).
  inline void g_set_error(GError** err, gint domain, gint code, const char* fmt, ...) {
    if (!err) return;
    if (!*err) *err = new GError();
    (*err)->domain = domain;
    (*err)->code = code;

    va_list ap;
    va_start(ap, fmt);
    const char* s = nullptr;
    // The SUT only uses "%s", so read one const char*.
    s = va_arg(ap, const char*);
    va_end(ap);

    std::string msg = (s ? s : "");
    delete[] (*err)->message;
    (*err)->message = new char[msg.size() + 1];
    std::memcpy((*err)->message, msg.c_str(), msg.size() + 1);
  }

  // Domain constants (fallback values)
  #ifndef G_FILE_ERROR
    #define G_FILE_ERROR 1
  #endif
#endif

// Poppler error domain + codes fallbacks.
#ifndef POPPLER_ERROR
  #define POPPLER_ERROR 2
#endif

#ifndef POPPLER_ERROR_BAD_CATALOG
  #define POPPLER_ERROR_BAD_CATALOG 10
#endif
#ifndef POPPLER_ERROR_DAMAGED
  #define POPPLER_ERROR_DAMAGED 11
#endif
#ifndef POPPLER_ERROR_ENCRYPTED
  #define POPPLER_ERROR_ENCRYPTED 12
#endif
#ifndef POPPLER_ERROR_INVALID
  #define POPPLER_ERROR_INVALID 13
#endif

// PDFDoc error codes fallbacks.
#ifndef errOpenFile
  #define errOpenFile 100
#endif
#ifndef errBadCatalog
  #define errBadCatalog 101
#endif
#ifndef errDamaged
  #define errDamaged 102
#endif
#ifndef errEncrypted
  #define errEncrypted 103
#endif

// GObject fallbacks if not available.
#if __has_include(<glib-object.h>)
  #include <glib-object.h>
#else
  using GType = unsigned long;

  // Minimal g_object_new fallback returning raw memory.
  inline gpointer g_object_new(GType /*type*/, const gchar* /*first_property_name*/, ...) {
    // The PopplerDocument struct is defined/visible through poppler-private.h or the included .cc.
    // We'll just allocate a large enough block later if needed; if the real build is present,
    // it won't use this fallback anyway.
    return std::calloc(1, 1024);
  }
#endif

//
// -------- Seam types to observe interactions (only if real ones are not available) --------
//
struct GlobalParamsIniter {
  virtual ~GlobalParamsIniter() = default;
};

// If the real PDFDoc is available via includes in poppler-document.cc, we won't use this.
// Otherwise, this stub matches the minimal interface used by the SUT.
struct PDFDoc {
  bool ok = true;
  int errCode = 0;
  int fopenErrno = 0;

  bool isOk() const { return ok; }
  int getErrorCode() const { return errCode; }
  int getFopenErrno() const { return fopenErrno; }
};

// Interceptable CairoOutputDev: we want to observe startDoc calls.
struct CairoOutputDev {
  static inline int startDocCalls = 0;
  static inline const void* lastDocPtr = nullptr;

  CairoOutputDev() = default;
  void startDoc(PDFDoc* docA) {
    startDocCalls++;
    lastDocPtr = docA;
  }
};

// PopplerDocument minimal shape needed by the SUT.
#ifndef POPPLER_TYPE_DOCUMENT
  #define POPPLER_TYPE_DOCUMENT 42
#endif

struct _PopplerDocument {
  // In the real build this is a GObject; we only need the fields touched by the SUT.
  std::unique_ptr<GlobalParamsIniter> initer;
  std::unique_ptr<PDFDoc> doc;
  CairoOutputDev* output_dev = nullptr;
};
using PopplerDocument = _PopplerDocument;

//
// -------- Include the implementation under test (to access the static function) --------
//
#include "./TestProjects/poppler/glib/poppler-document.cc"

//
// -------- Test fixture --------
//
class PopplerDocumentNewFromPdfDocTest_2137 : public ::testing::Test {
protected:
  void SetUp() override {
    CairoOutputDev::startDocCalls = 0;
    CairoOutputDev::lastDocPtr = nullptr;
  }

  void TearDown() override {
#if !__has_include(<glib.h>)
    // nothing
#endif
  }
};

//
// -------- Tests --------
//

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, ReturnsNullAndSetsFileErrorForErrOpenFile_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = false;
  doc->errCode = errOpenFile;
  doc->fopenErrno = EACCES; // stable errno

  GError* error = nullptr;
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), &error);

  EXPECT_EQ(out, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, G_FILE_ERROR);
  EXPECT_EQ(error->code, g_file_error_from_errno(EACCES));
  ASSERT_NE(error->message, nullptr);
  EXPECT_STREQ(error->message, g_strerror(EACCES));

#if __has_include(<glib.h>)
  g_clear_error(&error);
#else
  g_clear_error(&error);
#endif
}

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, ReturnsNullAndSetsBadCatalogError_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = false;
  doc->errCode = errBadCatalog;

  GError* error = nullptr;
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), &error);

  EXPECT_EQ(out, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, POPPLER_ERROR);
  EXPECT_EQ(error->code, POPPLER_ERROR_BAD_CATALOG);
  ASSERT_NE(error->message, nullptr);
  EXPECT_STREQ(error->message, "Failed to read the document catalog");

#if __has_include(<glib.h>)
  g_clear_error(&error);
#else
  g_clear_error(&error);
#endif
}

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, ReturnsNullAndSetsDamagedError_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = false;
  doc->errCode = errDamaged;

  GError* error = nullptr;
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), &error);

  EXPECT_EQ(out, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, POPPLER_ERROR);
  EXPECT_EQ(error->code, POPPLER_ERROR_DAMAGED);
  ASSERT_NE(error->message, nullptr);
  EXPECT_STREQ(error->message, "PDF document is damaged");

#if __has_include(<glib.h>)
  g_clear_error(&error);
#else
  g_clear_error(&error);
#endif
}

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, ReturnsNullAndSetsEncryptedError_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = false;
  doc->errCode = errEncrypted;

  GError* error = nullptr;
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), &error);

  EXPECT_EQ(out, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, POPPLER_ERROR);
  EXPECT_EQ(error->code, POPPLER_ERROR_ENCRYPTED);
  ASSERT_NE(error->message, nullptr);
  EXPECT_STREQ(error->message, "Document is encrypted");

#if __has_include(<glib.h>)
  g_clear_error(&error);
#else
  g_clear_error(&error);
#endif
}

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, ReturnsNullAndSetsInvalidErrorForUnknownCode_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = false;
  doc->errCode = 999999; // unknown

  GError* error = nullptr;
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), &error);

  EXPECT_EQ(out, nullptr);
  ASSERT_NE(error, nullptr);
  EXPECT_EQ(error->domain, POPPLER_ERROR);
  EXPECT_EQ(error->code, POPPLER_ERROR_INVALID);
  ASSERT_NE(error->message, nullptr);
  EXPECT_STREQ(error->message, "Failed to load document");

#if __has_include(<glib.h>)
  g_clear_error(&error);
#else
  g_clear_error(&error);
#endif
}

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, SuccessCreatesDocumentAndStartsOutputDev_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = true;

  PDFDoc* rawDocPtr = doc.get();

  GError* error = nullptr;
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), &error);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(error, nullptr) << "On success, no error should be set";

  // Observable external interaction: startDoc called with the created document's PDFDoc.
  EXPECT_EQ(CairoOutputDev::startDocCalls, 1);
  EXPECT_EQ(CairoOutputDev::lastDocPtr, rawDocPtr);

  // Basic observable state: output_dev should be non-null.
  ASSERT_NE(out->output_dev, nullptr);

  // Cleanup (best-effort; real build may manage via GObject)
#if __has_include(<glib-object.h>)
  // If PopplerDocument is a real GObject in the build, g_object_unref should be correct.
  // Otherwise it may not exist; guarded by header check.
  g_object_unref(reinterpret_cast<GObject*>(out));
#else
  delete out->output_dev;
  std::free(out);
#endif
}

TEST_F(PopplerDocumentNewFromPdfDocTest_2137, PassingNullErrorPointerDoesNotCrashOnFailure_2137) {
  auto initer = std::make_unique<GlobalParamsIniter>();
  auto doc = std::make_unique<PDFDoc>();
  doc->ok = false;
  doc->errCode = errBadCatalog;

  // Boundary/robustness: error == nullptr should be accepted (no observable error reporting).
  PopplerDocument* out =
      _poppler_document_new_from_pdfdoc(std::move(initer), std::move(doc), nullptr);

  EXPECT_EQ(out, nullptr);
}