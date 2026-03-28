// poppler-document-find-dest-test.cc
//
// Unit tests for poppler_document_find_dest()
// TEST_ID: 2159
//
// NOTE:
// - Treats implementation as a black box.
// - Verifies only observable behavior via public API.
// - Uses a tiny in-memory PDF with a named destination to exercise the "success" path.

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

// ---------------------------
// Small helpers / RAII
// ---------------------------
struct GErrorDeleter {
  void operator()(GError* e) const {
    if (e) g_error_free(e);
  }
};
using GErrorPtr = std::unique_ptr<GError, GErrorDeleter>;

struct GObjectUnrefDeleter {
  void operator()(gpointer p) const {
    if (p) g_object_unref(p);
  }
};
using PopplerDocumentPtr = std::unique_ptr<PopplerDocument, GObjectUnrefDeleter>;

struct PopplerDestDeleter {
  void operator()(PopplerDest* d) const {
    if (!d) return;
    // Poppler GLib exposes poppler_dest_free() for PopplerDest*
    poppler_dest_free(d);
  }
};
using PopplerDestPtr = std::unique_ptr<PopplerDest, PopplerDestDeleter>;

// Builds a minimal, valid PDF with:
// - 1 page
// - A /Names tree for /Dests with a single entry: (dest_name) -> [page /XYZ 0 0 0]
//
// This is constructed with correct xref offsets.
static std::string BuildPdfWithNamedDest(const std::string& dest_name) {
  // Objects (numbered 1..N) will be appended; xref offsets computed afterwards.
  std::vector<std::string> objs;

  // 1 0 obj: Catalog with /Pages and /Names
  // Names dictionary:
  //   /Dests << /Names [ (dest_name) 6 0 R ] >>
  objs.push_back(
      "1 0 obj\n"
      "<< /Type /Catalog\n"
      "   /Pages 2 0 R\n"
      "   /Names << /Dests << /Names [ (" + dest_name + ") 6 0 R ] >> >>\n"
      ">>\n"
      "endobj\n");

  // 2 0 obj: Pages
  objs.push_back(
      "2 0 obj\n"
      "<< /Type /Pages\n"
      "   /Kids [ 3 0 R ]\n"
      "   /Count 1\n"
      ">>\n"
      "endobj\n");

  // 3 0 obj: Page
  objs.push_back(
      "3 0 obj\n"
      "<< /Type /Page\n"
      "   /Parent 2 0 R\n"
      "   /MediaBox [ 0 0 200 200 ]\n"
      "   /Contents 4 0 R\n"
      "   /Resources << >>\n"
      ">>\n"
      "endobj\n");

  // 4 0 obj: empty content stream
  objs.push_back(
      "4 0 obj\n"
      "<< /Length 0 >>\n"
      "stream\n"
      "\n"
      "endstream\n"
      "endobj\n");

  // 5 0 obj: Info (optional but harmless)
  objs.push_back(
      "5 0 obj\n"
      "<< /Producer (unit-test) >>\n"
      "endobj\n");

  // 6 0 obj: Destination array referencing page 3
  objs.push_back(
      "6 0 obj\n"
      "[ 3 0 R /XYZ 0 0 0 ]\n"
      "endobj\n");

  std::string pdf;
  pdf.reserve(2048);
  pdf += "%PDF-1.4\n";
  // Some readers like a binary marker line; include it.
  pdf += "%\xE2\xE3\xCF\xD3\n";

  // Track offsets: xref needs byte offsets from beginning of file.
  // xref includes object 0 (free) + objects 1..N.
  std::vector<size_t> offsets;
  offsets.resize(objs.size() + 1);
  offsets[0] = 0;

  for (size_t i = 0; i < objs.size(); ++i) {
    offsets[i + 1] = pdf.size();
    pdf += objs[i];
  }

  const size_t xref_offset = pdf.size();

  // xref table
  pdf += "xref\n";
  pdf += "0 " + std::to_string(objs.size() + 1) + "\n";
  pdf += "0000000000 65535 f \n";
  for (size_t i = 1; i <= objs.size(); ++i) {
    char buf[64];
    // 10-digit, zero-padded byte offset, then generation 00000, in-use 'n'
    std::snprintf(buf, sizeof(buf), "%010lu 00000 n \n",
                  static_cast<unsigned long>(offsets[i]));
    pdf += buf;
  }

  // trailer
  pdf += "trailer\n";
  pdf += "<< /Size " + std::to_string(objs.size() + 1) + "\n";
  pdf += "   /Root 1 0 R\n";
  pdf += "   /Info 5 0 R\n";
  pdf += ">>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset) + "\n";
  pdf += "%%EOF\n";

  return pdf;
}

static PopplerDocumentPtr LoadDocFromData(const std::string& pdf_bytes) {
  GError* err_raw = nullptr;

  // poppler_document_new_from_data takes:
  //   const char *data, int length, const char *password, GError **error
  PopplerDocument* doc =
      poppler_document_new_from_data(pdf_bytes.data(),
                                     static_cast<int>(pdf_bytes.size()),
                                     /*password=*/nullptr, &err_raw);

  GErrorPtr err(err_raw);
  if (!doc) {
    // Keep assertion-friendly failure message if load fails.
    ADD_FAILURE() << "Failed to create PopplerDocument from in-memory PDF. "
                  << "GError: " << (err ? err->message : "(none)");
    return PopplerDocumentPtr(nullptr);
  }
  return PopplerDocumentPtr(doc);
}

class PopplerDocumentFindDestTest_2159 : public ::testing::Test {};

}  // namespace

// ---------------------------
// Tests
// ---------------------------

TEST_F(PopplerDocumentFindDestTest_2159, ReturnsNullWhenDocumentIsNull_2159) {
  // g_return_val_if_fail() should emit a CRITICAL and return nullptr.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
  PopplerDest* dest = poppler_document_find_dest(nullptr, "dest1");
  g_test_assert_expected_messages();

  EXPECT_EQ(dest, nullptr);
}

TEST_F(PopplerDocumentFindDestTest_2159, ReturnsNullWhenLinkNameIsNull_2159) {
  const std::string pdf = BuildPdfWithNamedDest("dest1");
  PopplerDocumentPtr doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  // g_return_val_if_fail() should emit a CRITICAL and return nullptr.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*link_name != nullptr*");
  PopplerDest* dest = poppler_document_find_dest(doc.get(), nullptr);
  g_test_assert_expected_messages();

  EXPECT_EQ(dest, nullptr);
}

TEST_F(PopplerDocumentFindDestTest_2159, ReturnsNonNullForExistingNamedDest_2159) {
  const std::string pdf = BuildPdfWithNamedDest("dest1");
  PopplerDocumentPtr doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  PopplerDestPtr dest(poppler_document_find_dest(doc.get(), "dest1"));
  EXPECT_NE(dest.get(), nullptr);

  // No assumptions about dest fields (black box); just ensure it is a valid handle
  // and can be freed by poppler_dest_free via RAII.
}

TEST_F(PopplerDocumentFindDestTest_2159, ReturnsNullForMissingNamedDest_2159) {
  const std::string pdf = BuildPdfWithNamedDest("dest1");
  PopplerDocumentPtr doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  PopplerDest* dest = poppler_document_find_dest(doc.get(), "does_not_exist");
  EXPECT_EQ(dest, nullptr);
}

TEST_F(PopplerDocumentFindDestTest_2159, EmptyLinkNameDoesNotCrashAndReturnsNull_2159) {
  const std::string pdf = BuildPdfWithNamedDest("dest1");
  PopplerDocumentPtr doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  // Boundary: empty string is non-null input; expect "not found" behavior (nullptr).
  PopplerDest* dest = poppler_document_find_dest(doc.get(), "");
  EXPECT_EQ(dest, nullptr);
}

TEST_F(PopplerDocumentFindDestTest_2159, NonUtf8BytesInLinkNameDoesNotCrash_2159) {
  const std::string pdf = BuildPdfWithNamedDest("dest1");
  PopplerDocumentPtr doc = LoadDocFromData(pdf);
  ASSERT_NE(doc.get(), nullptr);

  // Provide a byte sequence that is not valid UTF-8; behavior may vary depending on
  // poppler_named_dest_to_bytestring() conversion rules. Observable requirement:
  // - must not crash
  // - if a PopplerDest* is returned, it must be freeable.
  const char invalid_utf8[] = {static_cast<char>(0xC3), static_cast<char>(0x28), '\0'};

  PopplerDest* raw = nullptr;
  EXPECT_NO_FATAL_FAILURE({
    raw = poppler_document_find_dest(doc.get(), invalid_utf8);
  });

  if (raw) {
    PopplerDestPtr dest(raw);  // ensure it can be freed safely
    EXPECT_NE(dest.get(), nullptr);
  } else {
    SUCCEED();
  }
}