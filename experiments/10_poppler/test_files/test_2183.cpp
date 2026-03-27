#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using ::testing::_;

using ::testing::Return;



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(malloc(sizeof(PopplerDocument)));

        memset(document, 0, sizeof(PopplerDocument));

        document->doc = new _PopplerDocument();

    }



    void TearDown() override {

        delete document->doc;

        free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2183, SetProducer_ValidString_2183) {

    const gchar* producer = "Example Producer";

    EXPECT_NO_THROW(poppler_document_set_producer(document, producer));

}



TEST_F(PopplerDocumentTest_2183, SetProducer_EmptyString_2183) {

    const gchar* producer = "";

    EXPECT_NO_THROW(poppler_document_set_producer(document, producer));

}



TEST_F(PopplerDocumentTest_2183, SetProducer_NullPointer_2183) {

    const gchar* producer = nullptr;

    EXPECT_NO_THROW(poppler_document_set_producer(document, producer));

}



TEST_F(PopplerDocumentTest_2183, SetProducer_LongString_2183) {

    const gchar* producer = "A very long string that should be accepted without any issues as the producer name in a Poppler document.";

    EXPECT_NO_THROW(poppler_document_set_producer(document, producer));

}
