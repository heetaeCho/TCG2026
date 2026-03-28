#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



using ::testing::StrictMock;

using ::testing::_;



class PopplerDocumentTest : public ::testing::Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_malloc0(sizeof(PopplerDocument)));

        document->doc = new _PopplerDocument();

    }



    void TearDown() override {

        delete document->doc;

        g_free(document);

    }



    PopplerDocument* document;

};



TEST_F(PopplerDocumentTest, GetModificationDateTime_ReturnsNull_WhenDocIsNull_2190) {

    document->doc = nullptr;

    EXPECT_EQ(poppler_document_get_modification_date_time(document), nullptr);

}



TEST_F(PopplerDocumentTest, GetModificationDateTime_ReturnsNull_WhenModDateIsNotSet_2190) {

    EXPECT_CALL(*document->doc, getDocInfoModDate()).WillOnce(testing::Return(nullptr));

    EXPECT_EQ(poppler_document_get_modification_date_time(document), nullptr);

}



TEST_F(PopplerDocumentTest, GetModificationDateTime_ReturnsValidGDateTime_WhenModDateIsValid_2190) {

    std::unique_ptr<GooString> modDate(new GooString("D:20230401000000Z"));

    EXPECT_CALL(*document->doc, getDocInfoModDate()).WillOnce(testing::Return(modDate.get()));

    GDateTime* dateTime = poppler_document_get_modification_date_time(document);

    EXPECT_NE(dateTime, nullptr);

    g_date_time_unref(dateTime);

}



TEST_F(PopplerDocumentTest, GetModificationDateTime_HandlesBoundaryConditions_2190) {

    std::unique_ptr<GooString> modDate(new GooString("D:20230401000000Z"));

    EXPECT_CALL(*document->doc, getDocInfoModDate()).WillOnce(testing::Return(modDate.get()));

    GDateTime* dateTime = poppler_document_get_modification_date_time(document);

    EXPECT_NE(dateTime, nullptr);

    g_date_time_unref(dateTime);



    modDate.reset(new GooString("D:2023"));

    EXPECT_CALL(*document->doc, getDocInfoModDate()).WillOnce(testing::Return(modDate.get()));

    dateTime = poppler_document_get_modification_date_time(document);

    EXPECT_EQ(dateTime, nullptr);

}

```


