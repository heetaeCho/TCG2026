// File: poppler_document_set_creator_test_2181.cc
//
// Unit tests for poppler_document_set_creator()
// Interface under test (from poppler-document.cc):
//   void poppler_document_set_creator(PopplerDocument *document, const gchar *creator);
//
// Constraints followed:
// - Treat implementation as a black box
// - Test only via public/observable behavior (poppler_document_get_creator())
// - No access to private/internal state
// - Includes normal, boundary, and observable error/exceptional cases
//
// NOTE: These tests assume the Poppler GLib API provides:
//   - poppler_document_new_from_data
//   - poppler_document_get_creator
// as is typical in poppler-glib.

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

namespace {

static std::string BuildMinimalPdfWithCreatorInfo(const char *creator_utf8_or_null)
{
  // Build a tiny valid PDF with an /Info dictionary containing /Creator (..)
  // Objects:
  //  1 0: Catalog
  //  2 0: Pages
  //  3 0: Page
  //  4 0: Contents stream (empty)
  //  5 0: Info dict (Creator optional)
  //
  // We compute xref offsets programmatically to ensure validity.

  std::vector<std::string> objs;
  objs.reserve(5);

  objs.push_back("1 0 obj\n"
                 "<< /Type /Catalog /Pages 2 0 R >>\n"
                 "endobj\n");

  objs.push_back("2 0 obj\n"
                 "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                 "endobj\n");

  objs.push_back("3 0 obj\n"
                 "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792]\n"
                 "   /Contents 4 0 R /Resources << >> >>\n"
                 "endobj\n");

  // Empty content stream with /Length 0.
  objs.push_back("4 0 obj\n"
                 "<< /Length 0 >>\n"
                 "stream\n"
                 "\n"
                 "endstream\n"
                 "endobj\n");

  // Info dictionary; if creator is null, omit /Creator entry (still valid Info object).
  std::string info = "5 0 obj\n<< ";
  if (creator_utf8_or_null) {
    // Keep it simple: put the string in literal parentheses.
    // (We do not attempt to escape parentheses/backslashes; tests use simple values.)
    info += "/Creator (";
    info += creator_utf8_or_null;
    info += ") ";
  }
  info += ">>\nendobj\n";
  objs.push_back(std::move(info));

  std::string pdf;
  pdf.reserve(2048);

  pdf += "%PDF-1.4\n";

  // Track offsets for xref.
  std::vector<long> offsets;
  offsets.resize(6, 0); // index 0..5; 0 is free object.

  // Object 0 (free) is always offset 0 in xref table.
  // We'll compute actual offsets for objects 1..5.
  for (int i = 1; i <= 5; ++i) {
    offsets[i] = static_cast<long>(pdf.size());
    pdf += objs[static_cast<size_t>(i - 1)];
  }

  const long xref_offset = static_cast<long>(pdf.size());
  pdf += "xref\n";
  pdf += "0 6\n";
  pdf += "0000000000 65535 f \n";

  auto fmt_offset = [](long off) {
    char buf[32];
    // 10-digit, zero-padded as required by PDF xref.
    std::snprintf(buf, sizeof(buf), "%010ld", off);
    return std::string(buf);
  };

  for (int i = 1; i <= 5; ++i) {
    pdf += fmt_offset(offsets[i]);
    pdf += " 00000 n \n";
  }

  pdf += "trailer\n";
  pdf += "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n";
  pdf += "startxref\n";
  pdf += std::to_string(xref_offset);
  pdf += "\n%%EOF\n";

  return pdf;
}

static void ExpectNullOrEmptyCreator(const gchar *creator)
{
  if (creator == nullptr) {
    SUCCEED();
    return;
  }
  EXPECT_EQ(std::strlen(creator), 0u);
}

class PopplerDocumentSetCreatorTest_2181 : public ::testing::Test {
protected:
  void TearDown() override
  {
    if (doc_) {
      g_object_unref(doc_);
      doc_ = nullptr;
    }
  }

  void LoadDocWithInitialCreator(const char *initial_creator_utf8_or_null)
  {
    const std::string pdf = BuildMinimalPdfWithCreatorInfo(initial_creator_utf8_or_null);

    GError *error = nullptr;
    doc_ = poppler_document_new_from_data(pdf.data(),
                                          static_cast<int>(pdf.size()),
                                          /*password=*/nullptr,
                                          &error);
    ASSERT_NE(doc_, nullptr);
    ASSERT_EQ(error, nullptr) << (error ? error->message : "");

    // Sanity: ensure getter is callable.
    gchar *creator = poppler_document_get_creator(doc_);
    if (initial_creator_utf8_or_null == nullptr) {
      // If initial creator wasn't provided, allow null/empty.
      ExpectNullOrEmptyCreator(creator);
    } else {
      ASSERT_NE(creator, nullptr);
      EXPECT_STREQ(creator, initial_creator_utf8_or_null);
    }
    g_free(creator);
  }

  PopplerDocument *doc_ = nullptr;
};

} // namespace

TEST_F(PopplerDocumentSetCreatorTest_2181, SetsCreatorToNewValue_2181)
{
  LoadDocWithInitialCreator("InitialCreator");

  poppler_document_set_creator(doc_, "NewCreator");

  gchar *creator = poppler_document_get_creator(doc_);
  ASSERT_NE(creator, nullptr);
  EXPECT_STREQ(creator, "NewCreator");
  g_free(creator);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithNullClearsOrEmptiesValue_2181)
{
  LoadDocWithInitialCreator("InitialCreator");

  poppler_document_set_creator(doc_, nullptr);

  gchar *creator = poppler_document_get_creator(doc_);
  ExpectNullOrEmptyCreator(creator);
  g_free(creator);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, SetCreatorWithEmptyStringResultsInEmptyOrCleared_2181)
{
  LoadDocWithInitialCreator("InitialCreator");

  poppler_document_set_creator(doc_, "");

  gchar *creator = poppler_document_get_creator(doc_);
  // Some implementations store empty string; others may clear the entry.
  ExpectNullOrEmptyCreator(creator);
  g_free(creator);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, InvalidUtf8DoesNotChangeExistingCreator_2181)
{
  LoadDocWithInitialCreator("KeepMe");

  // Provide an invalid UTF-8 sequence.
  const gchar invalid_utf8[] = {'\xC3', '\x28', '\0'}; // invalid 2-byte sequence

  poppler_document_set_creator(doc_, invalid_utf8);

  gchar *creator = poppler_document_get_creator(doc_);
  ASSERT_NE(creator, nullptr);
  EXPECT_STREQ(creator, "KeepMe");
  g_free(creator);
}

TEST_F(PopplerDocumentSetCreatorTest_2181, NullDocumentDoesNotCrash_2181)
{
  // g_return_if_fail should early-return; observable behavior here is "no crash".
  EXPECT_NO_FATAL_FAILURE(poppler_document_set_creator(nullptr, "Whatever"));
}

TEST_F(PopplerDocumentSetCreatorTest_2181, WorksWhenNoInitialCreatorInfoPresent_2181)
{
  LoadDocWithInitialCreator(nullptr);

  poppler_document_set_creator(doc_, "CreatorAfterNone");

  gchar *creator = poppler_document_get_creator(doc_);
  ASSERT_NE(creator, nullptr);
  EXPECT_STREQ(creator, "CreatorAfterNone");
  g_free(creator);
}