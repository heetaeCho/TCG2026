#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mocking external dependencies if needed

class MockPopplerDocument {

public:

    MOCK_METHOD1(setDocInfoKeywords, void(std::unique_ptr<GooString>));

};



TEST_F(PopplerDocumentTest_2179, SetKeywordsNormalOperation_2179) {

    PopplerDocument document;

    document.doc = new MockPopplerDocument();

    

    EXPECT_CALL(*document.doc, setDocInfoKeywords(testing::_)).Times(1);

    

    poppler_document_set_keywords(&document, "test_keywords");

}



TEST_F(PopplerDocumentTest_2179, SetKeywordsNullPointer_2179) {

    PopplerDocument document;

    document.doc = new MockPopplerDocument();

    

    EXPECT_CALL(*document.doc, setDocInfoKeywords(testing::_)).Times(0);

    

    poppler_document_set_keywords(&document, nullptr);

}



TEST_F(PopplerDocumentTest_2179, SetKeywordsEmptyString_2179) {

    PopplerDocument document;

    document.doc = new MockPopplerDocument();

    

    EXPECT_CALL(*document.doc, setDocInfoKeywords(testing::_)).Times(1);

    

    poppler_document_set_keywords(&document, "");

}



TEST_F(PopplerDocumentTest_2179, SetKeywordsLongString_2179) {

    PopplerDocument document;

    document.doc = new MockPopplerDocument();

    

    EXPECT_CALL(*document.doc, setDocInfoKeywords(testing::_)).Times(1);

    

    std::string long_string(10000, 'a');

    poppler_document_set_keywords(&document, long_string.c_str());

}



TEST_F(PopplerDocumentTest_2179, SetKeywordsInvalidUTF8_2179) {

    PopplerDocument document;

    document.doc = new MockPopplerDocument();

    

    EXPECT_CALL(*document.doc, setDocInfoKeywords(testing::_)).Times(0);

    

    const gchar* invalid_utf8 = "\xC3\x28"; // Invalid UTF-8 sequence

    poppler_document_set_keywords(&document, invalid_utf8);

}
