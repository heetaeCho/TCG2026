#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mocking external collaborators if needed

class MockPopplerDocument : public PopplerDocument {

public:

    MOCK_METHOD(std::unique_ptr<GooString>, getDocInfoSubject, (), (const, override));

};



TEST_F(PopplerDocumentTest_2176, GetSubject_ReturnsValidUtf8String_2176) {

    // Arrange

    MockPopplerDocument mock_document;

    auto mock_goo_subject = std::make_unique<GooString>("Test Subject");

    EXPECT_CALL(mock_document, getDocInfoSubject()).WillOnce(::testing::Return(std::move(mock_goo_subject)));



    // Act

    gchar *result = poppler_document_get_subject(&mock_document);



    // Assert

    ASSERT_STREQ(result, "Test Subject");

    g_free(result);

}



TEST_F(PopplerDocumentTest_2176, GetSubject_ReturnsNullForEmptyString_2176) {

    // Arrange

    MockPopplerDocument mock_document;

    auto mock_goo_subject = std::make_unique<GooString>("");

    EXPECT_CALL(mock_document, getDocInfoSubject()).WillOnce(::testing::Return(std::move(mock_goo_subject)));



    // Act

    gchar *result = poppler_document_get_subject(&mock_document);



    // Assert

    ASSERT_STREQ(result, "");

    g_free(result);

}



TEST_F(PopplerDocumentTest_2176, GetSubject_ReturnsNullForInvalidDocument_2176) {

    // Arrange

    PopplerDocument *invalid_document = nullptr;



    // Act & Assert

    gchar *result = poppler_document_get_subject(invalid_document);



    // Assert

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerDocumentTest_2176, GetSubject_ReturnsNullForNoSubject_2176) {

    // Arrange

    MockPopplerDocument mock_document;

    EXPECT_CALL(mock_document, getDocInfoSubject()).WillOnce(::testing::Return(nullptr));



    // Act

    gchar *result = poppler_document_get_subject(&mock_document);



    // Assert

    ASSERT_EQ(result, nullptr);

}
