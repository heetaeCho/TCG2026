#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mocking external dependencies if needed.

class MockPopplerDocument {

public:

    MOCK_METHOD(const std::unique_ptr<GooString>*, getDocInfoProducer, (), (const));

};



TEST_F(PopplerDocumentTest_2182, GetProducer_ReturnsValidString_2182) {

    // Arrange

    PopplerDocument document;

    MockPopplerDocument* mock_doc = new MockPopplerDocument();

    document.doc = mock_doc;



    const char* expected_producer = "Test Producer";

    auto goo_string = std::make_unique<GooString>(expected_producer);

    EXPECT_CALL(*mock_doc, getDocInfoProducer()).WillOnce(::testing::Return(&goo_string));



    // Act

    gchar* result = poppler_document_get_producer(&document);



    // Assert

    ASSERT_STREQ(expected_producer, result);

    g_free(result);  // Free the allocated memory

}



TEST_F(PopplerDocumentTest_2182, GetProducer_ReturnsNullWhenNoProducer_2182) {

    // Arrange

    PopplerDocument document;

    MockPopplerDocument* mock_doc = new MockPopplerDocument();

    document.doc = mock_doc;



    EXPECT_CALL(*mock_doc, getDocInfoProducer()).WillOnce(::testing::Return(nullptr));



    // Act

    gchar* result = poppler_document_get_producer(&document);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2182, GetProducer_ReturnsNullWhenInvalidDocument_2182) {

    // Arrange

    PopplerDocument document;

    document.doc = nullptr;



    // Act

    gchar* result = poppler_document_get_producer(&document);



    // Assert

    ASSERT_EQ(result, nullptr);

}
