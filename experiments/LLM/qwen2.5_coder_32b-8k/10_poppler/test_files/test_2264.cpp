#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib.h>

#include <memory>

#include "poppler-document.cc"

#include "GooString.h"



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(PopplerDocumentTest_2264, ConvertDateTimeToPDFDateNormalOperation_2264) {

    GDateTime *datetime = g_date_time_new_utc(2023, 10, 5, 12, 30, 45);

    std::unique_ptr<GooString> result = _poppler_convert_date_time_to_pdf_date(datetime);

    EXPECT_EQ(result->toStr(), "D:20231005123045Z");

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2264, ConvertDateTimeToPDFDateWithPositiveOffset_2264) {

    GTimeZone *timezone = g_time_zone_new("UTC+02:30");

    GDateTime *datetime = g_date_time_new(1995, 7, 28, 14, 32, 45.5, timezone);

    std::unique_ptr<GooString> result = _poppler_convert_date_time_to_pdf_date(datetime);

    EXPECT_EQ(result->toStr(), "D:19950728143245+02'30'");

    g_date_time_unref(datetime);

    g_time_zone_unref(timezone);

}



TEST_F(PopplerDocumentTest_2264, ConvertDateTimeToPDFDateWithNegativeOffset_2264) {

    GTimeZone *timezone = g_time_zone_new("UTC-03:15");

    GDateTime *datetime = g_date_time_new(2000, 1, 1, 0, 0, 0.0, timezone);

    std::unique_ptr<GooString> result = _poppler_convert_date_time_to_pdf_date(datetime);

    EXPECT_EQ(result->toStr(), "D:20000101000000-03'15'");

    g_date_time_unref(datetime);

    g_time_zone_unref(timezone);

}



TEST_F(PopplerDocumentTest_2264, ConvertDateTimeToPDFDateBoundaryConditionStartOfYear_2264) {

    GDateTime *datetime = g_date_time_new_utc(2023, 1, 1, 0, 0, 0);

    std::unique_ptr<GooString> result = _poppler_convert_date_time_to_pdf_date(datetime);

    EXPECT_EQ(result->toStr(), "D:20230101000000Z");

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2264, ConvertDateTimeToPDFDateBoundaryConditionEndOfYear_2264) {

    GDateTime *datetime = g_date_time_new_utc(2023, 12, 31, 23, 59, 59);

    std::unique_ptr<GooString> result = _poppler_convert_date_time_to_pdf_date(datetime);

    EXPECT_EQ(result->toStr(), "D:20231231235959Z");

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2264, ConvertDateTimeToPDFDateInvalidTimeZone_2264) {

    GTimeZone *timezone = nullptr;

    GDateTime *datetime = g_date_time_new(2023, 1, 5, 8, 23, 17.0, timezone);

    std::unique_ptr<GooString> result = _poppler_convert_date_time_to_pdf_date(datetime);

    EXPECT_EQ(result->toStr(), "D:20230105082317Z");

    g_date_time_unref(datetime);

}
