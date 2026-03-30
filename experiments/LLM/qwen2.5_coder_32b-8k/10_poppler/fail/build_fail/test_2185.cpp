#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using ::testing::_;

using ::testing::Mock;

using ::testing::Return;



class PopplerDocumentTest_2185 : public ::testing::Test {

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



TEST_F(PopplerDocumentTest_2185, SetCreationDateValidTime_2185) {

    time_t test_time = 1633072800; // Example timestamp

    poppler_document_set_creation_date(document, test_time);

}



TEST_F(PopplerDocumentTest_2185, SetCreationDateInvalidTime_2185) {

    time_t invalid_time = (time_t)-1;

    poppler_document_set_creation_date(document, invalid_time);

}



TEST_F(PopplerDocumentTest_2185, SetCreationDateBoundaryConditionZero_2185) {

    time_t zero_time = 0;

    poppler_document_set_creation_date(document, zero_time);

}
