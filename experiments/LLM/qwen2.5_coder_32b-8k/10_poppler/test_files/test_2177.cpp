#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



class PopplerDocumentTest_2177 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(malloc(sizeof(PopplerDocument)));

        document->doc = new _PopplerDocument();

    }



    void TearDown() override {

        delete document->doc;

        free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2177, SetSubject_NormalOperation_2177) {

    const gchar* subject = "Test Subject";

    poppler_document_set_subject(document, subject);

    // Assuming there is a way to verify the subject was set, this would be done here.

}



TEST_F(PopplerDocumentTest_2177, SetSubject_EmptyString_2177) {

    const gchar* subject = "";

    poppler_document_set_subject(document, subject);

    // Assuming there is a way to verify the subject was set, this would be done here.

}



TEST_F(PopplerDocumentTest_2177, SetSubject_NullPointer_2177) {

    poppler_document_set_subject(document, nullptr);

    // Assuming there is a way to verify the subject was not changed or set, this would be done here.

}



TEST_F(PopplerDocumentTest_2177, SetSubject_UTF8ConversionFailure_2177) {

    const gchar* invalid_utf8 = "\xC3\x28"; // Invalid UTF-8 sequence

    poppler_document_set_subject(document, invalid_utf8);

    // Assuming there is a way to verify the subject was not changed or set, this would be done here.

}
