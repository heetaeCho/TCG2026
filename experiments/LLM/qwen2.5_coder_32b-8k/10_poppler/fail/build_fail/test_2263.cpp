#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <gio/gio.h>

#include "TestProjects/poppler/goo/GooString.h"

#include "TestProjects/poppler/glib/poppler-document.cc"



using namespace testing;



class PopplerDocumentTest_2263 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PopplerDocumentTest_2263, ConvertValidDate_2263) {

    GooString date("D:20210915142300+02'00'");

    GDateTime* result = _poppler_convert_pdf_date_to_date_time(&date);

    ASSERT_NE(result, nullptr);



    EXPECT_EQ(g_date_time_get_year(result), 2021);

    EXPECT_EQ(g_date_time_get_month(result), 9);

    EXPECT_EQ(g_date_time_get_day_of_month(result), 15);

    EXPECT_EQ(g_date_time_get_hour(result), 14);

    EXPECT_EQ(g_date_time_get_minute(result), 23);

    EXPECT_EQ(g_date_time_get_second(result), 0);



    g_date_time_unref(result);

}



TEST_F(PopplerDocumentTest_2263, ConvertValidDateWithoutTZ_2263) {

    GooString date("D:20210915142300Z");

    GDateTime* result = _poppler_convert_pdf_date_to_date_time(&date);

    ASSERT_NE(result, nullptr);



    EXPECT_EQ(g_date_time_get_year(result), 2021);

    EXPECT_EQ(g_date_time_get_month(result), 9);

    EXPECT_EQ(g_date_time_get_day_of_month(result), 15);

    EXPECT_EQ(g_date_time_get_hour(result), 14);

    EXPECT_EQ(g_date_time_get_minute(result), 23);

    EXPECT_EQ(g_date_time_get_second(result), 0);



    g_date_time_unref(result);

}



TEST_F(PopplerDocumentTest_2263, ConvertInvalidDate_2263) {

    GooString date("D:invalid-date");

    GDateTime* result = _poppler_convert_pdf_date_to_date_time(&date);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2263, ConvertEmptyDate_2263) {

    GooString date("");

    GDateTime* result = _poppler_convert_pdf_date_to_date_time(&date);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2263, ConvertNullDate_2263) {

    GooString* nullDate = nullptr;

    GDateTime* result = _poppler_convert_pdf_date_to_date_time(nullDate);

    EXPECT_EQ(result, nullptr);

}
