// TEST_ID: 2205
// File: poppler-document-get-pdf-conformance-test-2205.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include "poppler-document.h"

// Function under test (implemented in poppler-document.cc)
extern "C" PopplerPDFConformance poppler_document_get_pdf_conformance(PopplerDocument *document);

namespace {

class ScopedGObject {
public:
  explicit ScopedGObject(gpointer obj = nullptr) : obj_(obj) {}
  ~ScopedGObject() {
    if (obj_) {
      g_object_unref(obj_);
    }
  }
  ScopedGObject(const ScopedGObject &) = delete;
  ScopedGObject &operator=(const ScopedGObject &) = delete;

  gpointer get() const { return obj_; }
  gpointer release() {
    gpointer tmp = obj_;
    obj_ = nullptr;
    return tmp;
  }

private:
  gpointer obj_;
};

class ScopedGFree {
public:
  explicit ScopedGFree(gpointer p = nullptr) : p_(p) {}
  ~ScopedGFree() {
    if (p_) {
      g_free(p_);
    }
  }
  ScopedGFree(const ScopedGFree &) = delete;
  ScopedGFree &operator=(const ScopedGFree &) = delete;

  gpointer get() const { return p_; }
  gpointer release() {
    gpointer tmp = p_;
    p_ = nullptr;
    return tmp;
  }

private:
  gpointer p_;
};

class PopplerDocumentGetPdfConformanceTest_2205 : public ::testing::Test {
protected:
  static bool IsValidEnumValue(PopplerPDFConformance v) {
    // Enum values are defined in poppler-document.h.
    return (static_cast<int>(v) >= static_cast<int>(POPPLER_PDF_SUBTYPE_CONF_UNSET)) &&
           (static_cast<int>(v) <= static_cast<int>(POPPLER_PDF_SUBTYPE_CONF_NONE));
  }

  static PopplerDocument *CreateDocumentFromEmbeddedPdfOrNull(GError **error_out) {
    // A small, valid, single-page PDF generated with ReportLab and base64-encoded.
    // We avoid assuming any particular conformance classification for this PDF; tests only
    // validate observable properties like "returns a valid enum value" and stability.
    static const char *kPdfBase64 =
        "JVBERi0xLjMKJZOMi54gUmVwb3J0TGFiIEdlbmVyYXRlZCBQREYgZG9jdW1lbnQgaHR0"
        "cDovL3d3dy5yZXBvcnRsYWIuY29tCjEgMCBvYmoKPDwKL0YxIDIgMCBSCj4+CmVuZG9i"
        "agoyIDAgb2JqCjw8Ci9CYXNlRm9udCAvSGVsdmV0aWNhIC9FbmNvZGluZyAvV2luQW5z"
        "aUVuY29kaW5nIC9OYW1lIC9GMSAvU3VidHlwZSAvVHlwZTEgL1R5cGUgL0ZvbnQKPj4K"
        "ZW5kb2JqCjMgMCBvYmoKPDwKL0NvbnRlbnRzIDcgMCBSIC9NZWRpYUJveCBbIDAgMCAy"
        "MDAgMjAwIF0gL1BhcmVudCA2IDAgUiAvUmVzb3VyY2VzIDw8Ci9Gb250IDEgMCBSCj4+"
        "IC9Sb3RhdGUgMCAvVHJhbnMgPDwKPj4gCi9UeXBlIC9QYWdlCj4+CmVuZG9iago0IDAg"
        "b2JqCjw8Ci9QYWdlTW9kZSAvVXNlTm9uZSAvUGFnZUxhYmVscyA8PAovTm1zIFsgXQo+"
        "PiAvVHlwZSAvQ2F0YWxvZwo+PgplbmRvYmoKNSAwIG9iago8PAovQ291bnQgMSAvS2lk"
        "cyBbIDMgMCBSIF0gL1R5cGUgL1BhZ2VzCj4+CmVuZG9iago2IDAgb2JqCjw8Ci9Db3Vu"
        "dCAxIC9LaWRzIFsgMyAwIFIgXSAKL1R5cGUgL1BhZ2VzCj4+CmVuZG9iago3IDAgb2Jq"
        "Cjw8Ci9MZW5ndGggODgKPj4Kc3RyZWFtCkJUCi9GMSAxMiBUZgowIDAgVGQKKDUwIDE1"
        "MCkgVGQKKEhlbGxvKSBUagpFVAplbmRzdHJlYW0KZW5kb2JqCnhyZWYKMCA4CjAwMDAw"
        "MDAwMDAgNjU1MzUgZiAKMDAwMDAwMDA4OCAwMDAwMCBuIAowMDAwMDAwMTIxIDAwMDAw"
        "IG4gCjAwMDAwMDAyMzUgMDAwMDAgbiAKMDAwMDAwMDM5OSAwMDAwMCBuIAowMDAwMDAw"
        "NDYxIDAwMDAwIG4gCjAwMDAwMDA1MzUgMDAwMDAgbiAKMDAwMDAwMDYxMSAwMDAwMCBu"
        "IAp0cmFpbGVyCjw8Ci9JRCBbPDgwMDc0NzUyMzU4N2NhMTI5ZmJmMWM4M2E1N2JmOWUx"
        "Pjw4MDA3NDc1MjM1ODdjYTEyOWZiZjFjODNhNTdiZjllMT5dCi9JbmZvIDggMCBSCi9S"
        "b290IDQgMCBSCi9TaXplIDgKPj4Kc3RhcnR4cmVmCjcwMQolJUVPRgo=";

    gsize pdf_len = 0;
    ScopedGFree pdf_data(g_base64_decode(kPdfBase64, &pdf_len));
    if (!pdf_data.get() || pdf_len == 0) {
      return nullptr;
    }

    // poppler_document_new_from_data is part of the Poppler GLib API.
    // Signature (commonly): PopplerDocument* poppler_document_new_from_data(const char*, int, const char*, GError**)
    PopplerDocument *doc = poppler_document_new_from_data(
        reinterpret_cast<const char *>(pdf_data.get()),
        static_cast<int>(pdf_len),
        /*password=*/nullptr,
        error_out);

    // pdf_data freed automatically; PopplerDocument (if created) owns its internal data.
    return doc;
  }
};

} // namespace

TEST_F(PopplerDocumentGetPdfConformanceTest_2205, NullDocumentReturnsNone_2205) {
  PopplerPDFConformance conf = poppler_document_get_pdf_conformance(nullptr);
  EXPECT_EQ(conf, POPPLER_PDF_SUBTYPE_CONF_NONE);
}

TEST_F(PopplerDocumentGetPdfConformanceTest_2205, InvalidGObjectTypeReturnsNone_2205) {
  ScopedGObject obj(g_object_new(G_TYPE_OBJECT, nullptr));
  ASSERT_NE(obj.get(), nullptr);

  // Intentionally pass an object of the wrong type. The function should fail its type-check
  // and return the documented g_return_val_if_fail default.
  PopplerDocument *as_doc = reinterpret_cast<PopplerDocument *>(obj.get());
  PopplerPDFConformance conf = poppler_document_get_pdf_conformance(as_doc);

  EXPECT_EQ(conf, POPPLER_PDF_SUBTYPE_CONF_NONE);
}

TEST_F(PopplerDocumentGetPdfConformanceTest_2205, ValidDocumentReturnsAValidEnumValue_2205) {
  GError *error = nullptr;
  ScopedGObject doc(CreateDocumentFromEmbeddedPdfOrNull(&error));
  if (!doc.get()) {
    if (error) {
      g_error_free(error);
    }
    GTEST_SKIP() << "Could not create PopplerDocument from embedded PDF data in this environment.";
  }
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  PopplerPDFConformance conf = poppler_document_get_pdf_conformance(
      reinterpret_cast<PopplerDocument *>(doc.get()));

  EXPECT_TRUE(PopplerDocumentGetPdfConformanceTest_2205::IsValidEnumValue(conf))
      << "Returned value is outside expected PopplerPDFConformance enum range: "
      << static_cast<int>(conf);
}

TEST_F(PopplerDocumentGetPdfConformanceTest_2205, SameDocumentReturnsStableValueAcrossCalls_2205) {
  GError *error = nullptr;
  ScopedGObject doc(CreateDocumentFromEmbeddedPdfOrNull(&error));
  if (!doc.get()) {
    if (error) {
      g_error_free(error);
    }
    GTEST_SKIP() << "Could not create PopplerDocument from embedded PDF data in this environment.";
  }
  if (error) {
    g_error_free(error);
    error = nullptr;
  }

  PopplerDocument *document = reinterpret_cast<PopplerDocument *>(doc.get());
  PopplerPDFConformance conf1 = poppler_document_get_pdf_conformance(document);
  PopplerPDFConformance conf2 = poppler_document_get_pdf_conformance(document);

  EXPECT_TRUE(PopplerDocumentGetPdfConformanceTest_2205::IsValidEnumValue(conf1));
  EXPECT_TRUE(PopplerDocumentGetPdfConformanceTest_2205::IsValidEnumValue(conf2));
  EXPECT_EQ(conf1, conf2);
}