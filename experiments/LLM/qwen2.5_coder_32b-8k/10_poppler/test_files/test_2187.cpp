#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"

#include <glib-object.h>

#include <glib.h>



using ::testing::_;

using ::testing::Return;



class PopplerDocumentTest_2187 : public ::testing::Test {

protected:

    void SetUp() override {

        document = static_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

    }



    void TearDown() override {

        g_clear_object(&document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2187, SetCreationDateTimeWithNullDocument_2187) {

    GDateTime *datetime = g_date_time_new_now_utc();

    poppler_document_set_creation_date_time(nullptr, datetime);

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2187, SetCreationDateTimeWithNullDateTime_2187) {

    poppler_document_set_creation_date_time(document, nullptr);

}



TEST_F(PopplerDocumentTest_2187, SetCreationDateTimeWithValidDateTime_2187) {

    GDateTime *datetime = g_date_time_new_now_utc();

    poppler_document_set_creation_date_time(document, datetime);

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2187, SetCreationDateTimeMultipleTimes_2187) {

    GDateTime *datetime1 = g_date_time_new_now_utc();

    GDateTime *datetime2 = g_date_time_add_seconds(datetime1, 3600); // one hour later



    poppler_document_set_creation_date_time(document, datetime1);

    poppler_document_set_creation_date_time(document, datetime2);



    g_date_time_unref(datetime1);

    g_date_time_unref(datetime2);

}
