#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include <memory>



using namespace testing;



class PopplerDocumentTest_2188 : public Test {

protected:

    struct _PopplerDocument* mockDoc;

    PopplerDocument* document;



    void SetUp() override {

        mockDoc = static_cast<_PopplerDocument*>(g_malloc0(sizeof(_PopplerDocument)));

        document = POPPLER_DOCUMENT(mockDoc);

    }



    void TearDown() override {

        g_free(mockDoc);

    }

};



TEST_F(PopplerDocumentTest_2188, GetModificationDate_ReturnsNegativeOneWhenNull_2188) {

    EXPECT_EQ(poppler_document_get_modification_date(nullptr), static_cast<time_t>(-1));

}



TEST_F(PopplerDocumentTest_2188, GetModificationDate_ReturnsNegativeOneWhenModDateIsNull_2188) {

    mockDoc->doc = new PopplerDocumentPrivate();

    EXPECT_EQ(poppler_document_get_modification_date(document), static_cast<time_t>(-1));

}



TEST_F(PopplerDocumentTest_2188, GetModificationDate_ReturnsValidTimeWhenConversionSuccessful_2188) {

    mockDoc->doc = new PopplerDocumentPrivate();

    mockDoc->doc->setDocInfoModDate(new GooString("D:20231005144832Z"));

    EXPECT_NE(poppler_document_get_modification_date(document), static_cast<time_t>(-1));

}



TEST_F(PopplerDocumentTest_2188, GetModificationDate_ReturnsNegativeOneWhenConversionFails_2188) {

    mockDoc->doc = new PopplerDocumentPrivate();

    mockDoc->doc->setDocInfoModDate(new GooString("InvalidDateFormat"));

    EXPECT_EQ(poppler_document_get_modification_date(document), static_cast<time_t>(-1));

}

```



**Note:** The provided code does not include the `PopplerDocumentPrivate` class definition or methods like `setDocInfoModDate`. These are assumed to be part of the internal implementation. The tests focus on the observable behavior as per the constraints.


