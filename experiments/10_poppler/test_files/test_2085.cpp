#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include <glib-object.h>



// Mocking GDate for testing purposes

class MockGDate : public GDate {

public:

    MOCK_METHOD(void, set_time_t, (time_t timet), ());

};



// Test fixture for PopplerAnnotMarkup tests

class PopplerAnnotMarkupTest_2085 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize PopplerAnnotMarkup instance

        poppler_annot_markup = static_cast<PopplerAnnotMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

        annot_markup = new AnnotMarkup(nullptr, nullptr);

        POPPLER_ANNOT(poppler_annot_markup)->annot.reset(annot_markup);



        // Mock GDate

        mock_date = std::make_unique<MockGDate>();

    }



    void TearDown() override {

        g_object_unref(poppler_annot_markup);

    }



    PopplerAnnotMarkup *poppler_annot_markup;

    AnnotMarkup *annot_markup;

    std::unique_ptr<MockGDate> mock_date;

};



TEST_F(PopplerAnnotMarkupTest_2085, GetDate_ReturnsNullWhenNoDateSet_2085) {

    EXPECT_EQ(poppler_annot_markup_get_date(poppler_annot_markup), nullptr);

}



TEST_F(PopplerAnnotMarkupTest_2085, GetDate_ConvertsPdfDateToGDateCorrectly_2085) {

    const char* pdf_date_str = "D:20231004123456Z";

    auto pdf_date = std::make_unique<GooString>(pdf_date_str);

    annot_markup->setDate(std::move(pdf_date));



    EXPECT_CALL(*mock_date, set_time_t(::testing::_)).Times(1);



    GDate *result = poppler_annot_markup_get_date(poppler_annot_markup);

    ASSERT_NE(result, nullptr);

    g_date_free(result);

}



TEST_F(PopplerAnnotMarkupTest_2085, GetDate_ReturnsNullWhenConversionFails_2085) {

    const char* invalid_pdf_date_str = "InvalidDate";

    auto invalid_pdf_date = std::make_unique<GooString>(invalid_pdf_date_str);

    annot_markup->setDate(std::move(invalid_pdf_date));



    EXPECT_CALL(*mock_date, set_time_t(::testing::_)).Times(0);



    GDate *result = poppler_annot_markup_get_date(poppler_annot_markup);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerAnnotMarkupTest_2085, GetDate_HandlesNullPopplerAnnotMarkup_2085) {

    EXPECT_EQ(poppler_annot_markup_get_date(nullptr), nullptr);

}
