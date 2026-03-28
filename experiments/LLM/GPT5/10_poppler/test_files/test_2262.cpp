// File: poppler-document-convert-pdf-date-to-gtime-test_2262.cc
//
// Unit tests for: _poppler_convert_pdf_date_to_gtime
//
// Constraints followed:
// - Treat implementation as black box (no re-implementation of logic).
// - Verify observable behavior via return value, out-parameter, and external interaction
//   (poppler_date_parse call + parameters) using a mock.
// - No access to private/internal state.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>
#include <ctime>
#include <cstring>
#include <string>

#include "goo/GooString.h"

// Function under test (C++ linkage; defined in poppler-document.cc)
gboolean _poppler_convert_pdf_date_to_gtime(const GooString *date, time_t *gdate);

// ---- Mocking external collaborator: poppler_date_parse ----
// poppler_date_parse is an external function called by the function under test.
// We override the symbol in the test binary and forward it to a gMock object.
class PopplerDateParseMock {
public:
  MOCK_METHOD(gboolean, Parse, (const gchar *date_string, time_t *out), ());
};

static PopplerDateParseMock *g_parse_mock = nullptr;

extern "C" gboolean poppler_date_parse(const gchar *date_string, time_t *out)
{
  // If no mock is installed, behave safely and return FALSE.
  if (!g_parse_mock) {
    return FALSE;
  }
  return g_parse_mock->Parse(date_string, out);
}

class PopplerConvertPdfDateToGtimeTest_2262 : public ::testing::Test {
protected:
  PopplerDateParseMock mock_;

  void SetUp() override { g_parse_mock = &mock_; }
  void TearDown() override { g_parse_mock = nullptr; }

  static std::unique_ptr<GooString> MakeAsciiGooString(const std::string &s)
  {
    return std::make_unique<GooString>(s.c_str(), s.size());
  }

  // Build a UTF-16BE byte sequence with a BOM (FE FF) for ASCII input:
  // [FE FF] [00 'D'] [00 ':'] ...
  static std::unique_ptr<GooString> MakeUtf16BeBomFromAscii(const std::string &ascii)
  {
    std::string bytes;
    bytes.push_back(static_cast<char>(0xFE));
    bytes.push_back(static_cast<char>(0xFF));
    bytes.reserve(2 + ascii.size() * 2);
    for (unsigned char ch : ascii) {
      bytes.push_back('\0');
      bytes.push_back(static_cast<char>(ch));
    }
    return std::make_unique<GooString>(bytes.c_str(), bytes.size());
  }
};

TEST_F(PopplerConvertPdfDateToGtimeTest_2262, NonBomInput_ForwardsStringAndPropagatesResult_2262)
{
  const std::string pdf_date = "D:20240101000000Z";
  auto gs = MakeAsciiGooString(pdf_date);

  time_t out_time = static_cast<time_t>(0);
  const time_t kExpected = static_cast<time_t>(123456);

  EXPECT_CALL(mock_, Parse(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([&](const gchar *date_string, time_t *out) -> gboolean {
        EXPECT_STREQ(date_string, pdf_date.c_str());
        *out = kExpected;
        return TRUE;
      });

  gboolean ok = _poppler_convert_pdf_date_to_gtime(gs.get(), &out_time);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out_time, kExpected);
}

TEST_F(PopplerConvertPdfDateToGtimeTest_2262, BomUtf16BeInput_IsConvertedToUtf8BeforeParse_2262)
{
  const std::string pdf_date_utf8 = "D:20240203112233+09'00'";
  auto gs = MakeUtf16BeBomFromAscii(pdf_date_utf8);

  time_t out_time = static_cast<time_t>(0);
  const time_t kExpected = static_cast<time_t>(98765);

  EXPECT_CALL(mock_, Parse(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([&](const gchar *date_string, time_t *out) -> gboolean {
        // Observable behavior: parser should receive UTF-8 text equivalent.
        EXPECT_STREQ(date_string, pdf_date_utf8.c_str());
        *out = kExpected;
        return TRUE;
      });

  gboolean ok = _poppler_convert_pdf_date_to_gtime(gs.get(), &out_time);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out_time, kExpected);
}

TEST_F(PopplerConvertPdfDateToGtimeTest_2262, EmptyString_CallsParserWithEmptyString_2262)
{
  auto gs = MakeAsciiGooString(std::string());

  time_t out_time = static_cast<time_t>(111);

  EXPECT_CALL(mock_, Parse(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([&](const gchar *date_string, time_t *out) -> gboolean {
        EXPECT_STREQ(date_string, "");
        *out = static_cast<time_t>(222);
        return TRUE;
      });

  gboolean ok = _poppler_convert_pdf_date_to_gtime(gs.get(), &out_time);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out_time, static_cast<time_t>(222));
}

TEST_F(PopplerConvertPdfDateToGtimeTest_2262, NullOutPointer_IsPassedToParserAndReturnIsPropagated_2262)
{
  const std::string pdf_date = "D:20250101120000";
  auto gs = MakeAsciiGooString(pdf_date);

  EXPECT_CALL(mock_, Parse(::testing::NotNull(), ::testing::IsNull()))
      .WillOnce([&](const gchar *date_string, time_t *out) -> gboolean {
        EXPECT_STREQ(date_string, pdf_date.c_str());
        EXPECT_EQ(out, nullptr);
        return FALSE; // Observable: should propagate.
      });

  gboolean ok = _poppler_convert_pdf_date_to_gtime(gs.get(), nullptr);
  EXPECT_FALSE(ok);
}

TEST_F(PopplerConvertPdfDateToGtimeTest_2262, EmbeddedNulInNonBomInput_PassesCStringUpToFirstNul_2262)
{
  // Build bytes: "D:2024\0GARBAGE" (length includes embedded NUL).
  const char raw[] = {'D', ':', '2', '0', '2', '4', '\0', 'X', 'Y', 'Z'};
  auto gs = std::make_unique<GooString>(raw, sizeof(raw));

  time_t out_time = static_cast<time_t>(0);

  EXPECT_CALL(mock_, Parse(::testing::NotNull(), ::testing::NotNull()))
      .WillOnce([&](const gchar *date_string, time_t *out) -> gboolean {
        // Since parser receives a C string, observable content ends at first NUL.
        EXPECT_STREQ(date_string, "D:2024");
        EXPECT_EQ(std::strlen(date_string), 6u);
        *out = static_cast<time_t>(333);
        return TRUE;
      });

  gboolean ok = _poppler_convert_pdf_date_to_gtime(gs.get(), &out_time);
  EXPECT_TRUE(ok);
  EXPECT_EQ(out_time, static_cast<time_t>(333));
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerConvertPdfDateToGtimeTest_2262, NullDatePointer_DeathOrCrashIsObservable_2262)
{
  // Exceptional/error case: passing nullptr for `date` is invalid for this interface.
  // We assert that it terminates (or otherwise crashes) rather than silently succeeding.
  time_t out_time = static_cast<time_t>(0);
  EXPECT_DEATH(
      {
        (void)_poppler_convert_pdf_date_to_gtime(nullptr, &out_time);
      },
      "");
}
#endif