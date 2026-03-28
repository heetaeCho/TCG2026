#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.cc"

#include "Object.h"

#include "Link.h"

#include "Catalog.h"

#include "PDFDoc.h"



using namespace testing;



class MockObject : public Object {

public:

    MOCK_METHOD(Object, fetch, (XRef * xref), (const));

    MOCK_METHOD(bool, isDict, (), (const));

    MOCK_METHOD(Object, dictLookup, (std::string_view key), (const));

};



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(Catalog *, getCatalog, (), (const));

};



class MockCatalog : public Catalog {

public:

    MOCK_CONST_METHOD(std::optional<std::string>, getBaseURI, (), (override));

};



TEST_F(Test, GetAdditionalAction_NormalOperation_2019) {

    MockObject additionalActions;

    MockPDFDoc pdfDoc;

    MockCatalog catalog;



    EXPECT_CALL(additionalActions, fetch(_)).WillOnce(Return(Object()));

    EXPECT_CALL(additionalActions, isDict()).WillOnce(Return(true));



    Object actionObject;

    EXPECT_CALL(additionalActions, dictLookup("E")).WillOnce(Return(actionObject));



    EXPECT_CALL(pdfDoc, getCatalog()).WillOnce(Return(&catalog));

    EXPECT_CALL(catalog, getBaseURI()).WillOnce(Return(std::optional<std::string>("http://example.com")));



    auto result = getAdditionalAction(Annot::actionCursorEntering, &additionalActions, &pdfDoc);

    ASSERT_NE(result, nullptr);

}



TEST_F(Test, GetAdditionalAction_NotADict_2019) {

    MockObject additionalActions;

    MockPDFDoc pdfDoc;



    EXPECT_CALL(additionalActions, fetch(_)).WillOnce(Return(Object()));

    EXPECT_CALL(additionalActions, isDict()).WillOnce(Return(false));



    auto result = getAdditionalAction(Annot::actionCursorEntering, &additionalActions, &pdfDoc);

    ASSERT_EQ(result, nullptr);

}



TEST_F(Test, GetAdditionalAction_KeyNotFound_2019) {

    MockObject additionalActions;

    MockPDFDoc pdfDoc;



    EXPECT_CALL(additionalActions, fetch(_)).WillOnce(Return(Object()));

    EXPECT_CALL(additionalActions, isDict()).WillOnce(Return(true));

    EXPECT_CALL(additionalActions, dictLookup("E")).WillOnce(Return(Object::null()));



    auto result = getAdditionalAction(Annot::actionCursorEntering, &additionalActions, &pdfDoc);

    ASSERT_EQ(result, nullptr);

}



TEST_F(Test, GetAdditionalAction_DictLookupFails_2019) {

    MockObject additionalActions;

    MockPDFDoc pdfDoc;



    EXPECT_CALL(additionalActions, fetch(_)).WillOnce(Return(Object()));

    EXPECT_CALL(additionalActions, isDict()).WillOnce(Return(true));

    EXPECT_CALL(additionalActions, dictLookup("E")).WillOnce(Return(Object::error()));



    auto result = getAdditionalAction(Annot::actionCursorEntering, &additionalActions, &pdfDoc);

    ASSERT_EQ(result, nullptr);

}



TEST_F(Test, GetAdditionalAction_ParseActionFails_2019) {

    MockObject additionalActions;

    MockPDFDoc pdfDoc;

    MockCatalog catalog;



    Object actionObject;

    EXPECT_CALL(additionalActions, fetch(_)).WillOnce(Return(Object()));

    EXPECT_CALL(additionalActions, isDict()).WillOnce(Return(true));

    EXPECT_CALL(additionalActions, dictLookup("E")).WillOnce(Return(actionObject));



    EXPECT_CALL(pdfDoc, getCatalog()).WillOnce(Return(&catalog));

    EXPECT_CALL(catalog, getBaseURI()).WillOnce(Return(std::optional<std::string>("http://example.com")));



    EXPECT_CALL(LinkAction::parseAction(_, _)).WillOnce(Return(nullptr));



    auto result = getAdditionalAction(Annot::actionCursorEntering, &additionalActions, &pdfDoc);

    ASSERT_EQ(result, nullptr);

}
