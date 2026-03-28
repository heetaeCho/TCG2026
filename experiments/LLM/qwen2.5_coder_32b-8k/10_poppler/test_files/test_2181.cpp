#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using namespace testing;



class PopplerDocumentTest : public ::testing::Test {

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



TEST_F(PopplerDocumentTest_SetCreator_2181, NormalOperationWithValidString_2181) {

    const gchar* creator = "Test Creator";

    EXPECT_NO_THROW(poppler_document_set_creator(document, creator));

}



TEST_F(PopplerDocumentTest_SetCreator_2181, BoundaryConditionWithEmptyString_2181) {

    const gchar* creator = "";

    EXPECT_NO_THROW(poppler_document_set_creator(document, creator));

}



TEST_F(PopplerDocumentTest_SetCreator_2181, BoundaryConditionWithNullPointer_2181) {

    const gchar* creator = nullptr;

    EXPECT_NO_THROW(poppler_document_set_creator(document, creator));

}



// Since the internal behavior is treated as a black box and we cannot mock or verify

// the internal state changes, we focus on observable behavior such as exceptions.

```


