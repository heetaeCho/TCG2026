#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib-object.h>

#include "poppler-document.h"



// Mock class to simulate PopplerDocument for testing purposes.

class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(void, set_title, (const gchar*), (override));

    MOCK_METHOD(void, set_author, (const gchar*), (override));

    MOCK_METHOD(void, set_subject, (const gchar*), (override));

    MOCK_METHOD(void, set_keywords, (const gchar*), (override));

    MOCK_METHOD(void, set_creator, (const gchar*), (override));

    MOCK_METHOD(void, set_producer, (const gchar*), (override));

    MOCK_METHOD(void, set_creation_date, (gint), (override));

    MOCK_METHOD(void, set_creation_date_time, (GDateTime*), (override));

    MOCK_METHOD(void, set_modification_date, (gint), (override));

    MOCK_METHOD(void, set_modification_date_time, (GDateTime*), (override));

};



// Test fixture for PopplerDocument tests.

class PopplerDocumentTest_2210 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

        mock_document = static_cast<MockPopplerDocument*>(document);

    }



    void TearDown() override {

        g_object_unref(document);

    }



    PopplerDocument* document;

    MockPopplerDocument* mock_document;

};



TEST_F(PopplerDocumentTest_2210, SetTitleNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_title("Sample Title")).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Title");

    poppler_document_set_property(G_OBJECT(document), PROP_TITLE, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetAuthorNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_author("Sample Author")).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Author");

    poppler_document_set_property(G_OBJECT(document), PROP_AUTHOR, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetSubjectNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_subject("Sample Subject")).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Subject");

    poppler_document_set_property(G_OBJECT(document), PROP_SUBJECT, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetKeywordsNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_keywords("Sample Keywords")).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Keywords");

    poppler_document_set_property(G_OBJECT(document), PROP_KEYWORDS, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetCreatorNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_creator("Sample Creator")).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Creator");

    poppler_document_set_property(G_OBJECT(document), PROP_CREATOR, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetProducerNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_producer("Sample Producer")).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Producer");

    poppler_document_set_property(G_OBJECT(document), PROP_PRODUCER, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetCreationDateNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_creation_date(1633075200)).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_INT);

    g_value_set_int(&value, 1633075200);

    poppler_document_set_property(G_OBJECT(document), PROP_CREATION_DATE, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetCreationDateTimeNormalOperation_2210) {

    GDateTime* datetime = g_date_time_new_utc(2021, 10, 1, 0, 0, 0.0);

    EXPECT_CALL(*mock_document, set_creation_date_time(datetime)).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_BOXED);

    g_value_set_boxed(&value, datetime);

    poppler_document_set_property(G_OBJECT(document), PROP_CREATION_DATETIME, &value, nullptr);

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2210, SetModificationDateNormalOperation_2210) {

    EXPECT_CALL(*mock_document, set_modification_date(1633075200)).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_INT);

    g_value_set_int(&value, 1633075200);

    poppler_document_set_property(G_OBJECT(document), PROP_MOD_DATE, &value, nullptr);

}



TEST_F(PopplerDocumentTest_2210, SetModificationDateTimeNormalOperation_2210) {

    GDateTime* datetime = g_date_time_new_utc(2021, 10, 1, 0, 0, 0.0);

    EXPECT_CALL(*mock_document, set_modification_date_time(datetime)).Times(1);

    GValue value = {};

    g_value_init(&value, G_TYPE_BOXED);

    g_value_set_boxed(&value, datetime);

    poppler_document_set_property(G_OBJECT(document), PROP_MOD_DATETIME, &value, nullptr);

    g_date_time_unref(datetime);

}



TEST_F(PopplerDocumentTest_2210, InvalidPropertyIdBoundaryCondition_2210) {

    GValue value = {};

    g_value_init(&value, G_TYPE_STRING);

    g_value_set_string(&value, "Sample Value");

    EXPECT_DEATH(poppler_document_set_property(G_OBJECT(document), 999, &value, nullptr), ".*G_OBJECT_WARN_INVALID_PROPERTY_ID.*");

}
