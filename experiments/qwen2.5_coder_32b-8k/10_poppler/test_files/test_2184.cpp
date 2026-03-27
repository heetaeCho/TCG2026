#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



class PopplerDocumentTest_2184 : public ::testing::Test {

protected:

    PopplerDocument* document;



    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(malloc(sizeof(PopplerDocument)));

        new(document) PopplerDocument();

        document->doc = new _PopplerDocument;

    }



    void TearDown() override {

        document->doc->~_PopplerDocument();

        delete document->doc;

        document->~PopplerDocument();

        free(document);

    }

};



TEST_F(PopplerDocumentTest_2184, GetCreationDate_ReturnsNegativeOneWhenNullDocument_2184) {

    EXPECT_EQ(poppler_document_get_creation_date(nullptr), (time_t)-1);

}



TEST_F(PopplerDocumentTest_2184, GetCreationDate_ReturnsNegativeOneWhenNoCreationDate_2184) {

    document->doc->getDocInfoCreatDate = []() -> std::unique_ptr<GooString> { return nullptr; };

    EXPECT_EQ(poppler_document_get_creation_date(document), (time_t)-1);

}



TEST_F(PopplerDocumentTest_2184, GetCreationDate_ReturnsConvertedTimeWhenValidCreationDate_2184) {

    auto mockGooString = std::make_unique<GooString>("D:20231015000000Z");

    document->doc->getDocInfoCreatDate = [mockGooString]() mutable -> std::unique_ptr<GooString> { return std::move(mockGooString); };



    EXPECT_CALL(*testing::MockFunction<gboolean(const char*, time_t*)>().AsStdFunction(), Call("20231015000000Z", testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(1697318400), testing::Return(G_TRUE)));



    EXPECT_EQ(poppler_document_get_creation_date(document), 1697318400);

}



TEST_F(PopplerDocumentTest_2184, GetCreationDate_ReturnsNegativeOneWhenConversionFails_2184) {

    auto mockGooString = std::make_unique<GooString>("D:20231015000000Z");

    document->doc->getDocInfoCreatDate = [mockGooString]() mutable -> std::unique_ptr<GooString> { return std::move(mockGooString); };



    EXPECT_CALL(*testing::MockFunction<gboolean(const char*, time_t*)>().AsStdFunction(), Call("20231015000000Z", testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(0), testing::Return(G_FALSE)));



    EXPECT_EQ(poppler_document_get_creation_date(document), (time_t)-1);

}

```


