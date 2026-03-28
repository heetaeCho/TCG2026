#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



class PopplerDocumentTest_2186 : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(new _PopplerDocument());

    }



    void TearDown() override {

        delete reinterpret_cast<_PopplerDocument*>(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest_2186, GetCreationDateTime_ReturnsNullptrForInvalidDocument_2186) {

    GDateTime* result = poppler_document_get_creation_date_time(nullptr);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2186, GetCreationDateTime_ReturnsNullptrWhenDocInfoCreatDateIsNull_2186) {

    EXPECT_CALL(*document->doc, getDocInfoCreatDate()).WillOnce(testing::Return(nullptr));

    GDateTime* result = poppler_document_get_creation_date_time(document);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2186, GetCreationDateTime_ReturnsValidGDateTimeForNonEmptyCreateDate_2186) {

    std::unique_ptr<GooString> mockDate(new GooString("D:20231005143000Z"));

    EXPECT_CALL(*document->doc, getDocInfoCreatDate()).WillOnce(testing::Return(mockDate.get()));

    GDateTime* result = poppler_document_get_creation_date_time(document);

    EXPECT_NE(result, nullptr);

    g_date_time_unref(result);

}



TEST_F(PopplerDocumentTest_2186, GetCreationDateTime_HandlesMalformedDateStringGracefully_2186) {

    std::unique_ptr<GooString> mockDate(new GooString("InvalidDateFormat"));

    EXPECT_CALL(*document->doc, getDocInfoCreatDate()).WillOnce(testing::Return(mockDate.get()));

    GDateTime* result = poppler_document_get_creation_date_time(document);

    EXPECT_EQ(result, nullptr);

}

```


