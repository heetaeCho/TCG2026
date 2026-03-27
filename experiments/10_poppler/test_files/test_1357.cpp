#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



using namespace Poppler;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



class DocumentDataTest_1357 : public ::testing::Test {

protected:

    DocumentData *docData;



    void SetUp() override {

        docData = new DocumentData("", std::nullopt, std::nullopt);

    }



    void TearDown() override {

        delete docData;

    }

};



TEST_F(DocumentDataTest_1357, CheckDocument_NormalOperation_IsOk_1357) {

    // Assuming isOk returns true

    EXPECT_CALL(*(docData->doc), isOk()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*(docData->doc), getErrorCode()).Times(0);

    Document *result = docData->checkDocument(docData);

    ASSERT_NE(result, nullptr);

    EXPECT_FALSE(result->m_doc->locked);

}



TEST_F(DocumentDataTest_1357, CheckDocument_NormalOperation_Encrypted_1357) {

    // Assuming isOk returns false but getErrorCode returns errEncrypted

    EXPECT_CALL(*(docData->doc), isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*(docData->doc), getErrorCode()).WillOnce(::testing::Return(errEncrypted));

    Document *result = docData->checkDocument(docData);

    ASSERT_NE(result, nullptr);

    EXPECT_TRUE(result->m_doc->locked);

}



TEST_F(DocumentDataTest_1357, CheckDocument_BoundaryCondition_NullDoc_1357) {

    // Boundary condition: doc is null

    DocumentData *nullDocData = new DocumentData();

    nullDocData->doc = nullptr;

    Document *result = nullDocData->checkDocument(nullDocData);

    EXPECT_EQ(result, nullptr);

    delete nullDocData;

}



TEST_F(DocumentDataTest_1357, CheckDocument_ExceptionalCase_IsNotOk_ErrorCodeNotEncrypted_1357) {

    // Assuming isOk returns false and getErrorCode returns an error other than errEncrypted

    EXPECT_CALL(*(docData->doc), isOk()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*(docData->doc), getErrorCode()).WillOnce(::testing::Return(errBadFile));

    Document *result = docData->checkDocument(docData);

    EXPECT_EQ(result, nullptr);

}



TEST_F(DocumentDataTest_1357, CheckDocument_VerifyExternalInteractions_XrefReconstructedCallback_1357) {

    // Assuming notifyXRefReconstructed is called

    EXPECT_CALL(*(docData->doc), isOk()).WillOnce(::testing::Return(true));

    testing::StrictMock< ::testing::FunctionMock0<void>> callbackMock;

    docData->xrefReconstructedCallback = std::bind(&decltype(callbackMock)::Invoke, &callbackMock);

    EXPECT_CALL(callbackMock, Invoke()).Times(1);

    Document *result = docData->checkDocument(docData);

    ASSERT_NE(result, nullptr);

}
