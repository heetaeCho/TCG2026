#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mock for GooString to simulate its behavior

class MockGooString {

public:

    MOCK_METHOD(const char*, getCString, (), (const));

};



// Using a global mock object since we cannot change the original function signature

MockGooString* mock_goo_string = nullptr;



// Overriding _poppler_goo_string_to_utf8 to use our mock object

extern "C" gchar* _poppler_goo_string_to_utf8(GooString* goo_title) {

    if (mock_goo_string && goo_title == reinterpret_cast<GooString*>(mock_goo_string)) {

        return g_strdup(mock_goo_string->getCString());

    }

    return nullptr;

}



// Test fixture for PopplerDocument

class PopplerDocumentTest_2172 : public ::testing::Test {

protected:

    void SetUp() override {

        document = new PopplerDocument();

        mock_goo_string = new MockGooString();

    }



    void TearDown() override {

        delete document;

        delete mock_goo_string;

    }



    PopplerDocument* document;

};



// Test case for normal operation with a non-empty title

TEST_F(PopplerDocumentTest_2172, GetTitle_NormalOperation_NonEmpty_2172) {

    EXPECT_CALL(*mock_goo_string, getCString()).WillOnce(::testing::Return("Sample Title"));

    document->doc->getDocInfoTitle = [this]() -> std::unique_ptr<GooString> {

        return std::unique_ptr<GooString>(reinterpret_cast<GooString*>(mock_goo_string));

    };



    gchar* title = poppler_document_get_title(document);

    ASSERT_STREQ(title, "Sample Title");

    g_free(title);

}



// Test case for normal operation with an empty title

TEST_F(PopplerDocumentTest_2172, GetTitle_NormalOperation_Empty_2172) {

    EXPECT_CALL(*mock_goo_string, getCString()).WillOnce(::testing::Return(""));

    document->doc->getDocInfoTitle = [this]() -> std::unique_ptr<GooString> {

        return std::unique_ptr<GooString>(reinterpret_cast<GooString*>(mock_goo_string));

    };



    gchar* title = poppler_document_get_title(document);

    ASSERT_STREQ(title, "");

    g_free(title);

}



// Test case for boundary condition with a null document

TEST_F(PopplerDocumentTest_2172, GetTitle_BoundaryCondition_NullDocument_2172) {

    PopplerDocument* null_document = nullptr;

    gchar* title = poppler_document_get_title(null_document);

    ASSERT_EQ(title, nullptr);

}



// Test case for exceptional case where getDocInfoTitle returns a nullptr

TEST_F(PopplerDocumentTest_2172, GetTitle_ExceptionalCase_NullGooString_2172) {

    document->doc->getDocInfoTitle = []() -> std::unique_ptr<GooString> { return nullptr; };



    gchar* title = poppler_document_get_title(document);

    ASSERT_EQ(title, nullptr);

}
