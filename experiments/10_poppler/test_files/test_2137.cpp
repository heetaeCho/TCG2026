#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler/glib/poppler-document.cc>



using namespace testing;



class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(bool, isOk, (), (const override));

    MOCK_METHOD(int, getErrorCode, (), (const override));

    MOCK_METHOD(int, getFopenErrno, (), (const override));

};



TEST(_poppler_document_new_from_pdfdoc_Test_2137, NormalOperation_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(true));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_NE(document, nullptr);

    EXPECT_EQ(error, nullptr);



    g_object_unref(document);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrOpenFile_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(errOpenFile));

    EXPECT_CALL(*mockPdfDoc, getFopenErrno()).WillOnce(Return(EACCES));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_EQ(document, nullptr);

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(error->domain, G_FILE_ERROR);

    EXPECT_EQ(error->code, g_file_error_from_errno(EACCES));

    g_clear_error(&error);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrBadCatalog_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(errBadCatalog));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_EQ(document, nullptr);

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(error->domain, POPPLER_ERROR);

    EXPECT_EQ(error->code, POPPLER_ERROR_BAD_CATALOG);

    g_clear_error(&error);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrDamaged_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(errDamaged));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_EQ(document, nullptr);

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(error->domain, POPPLER_ERROR);

    EXPECT_EQ(error->code, POPPLER_ERROR_DAMAGED);

    g_clear_error(&error);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrEncrypted_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(errEncrypted));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_EQ(document, nullptr);

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(error->domain, POPPLER_ERROR);

    EXPECT_EQ(error->code, POPPLER_ERROR_ENCRYPTED);

    g_clear_error(&error);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrInvalid_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(99)); // Some other error code



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_EQ(document, nullptr);

    EXPECT_NE(error, nullptr);

    EXPECT_EQ(error->domain, POPPLER_ERROR);

    EXPECT_EQ(error->code, POPPLER_ERROR_INVALID);

    g_clear_error(&error);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrorParameterNull_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(errOpenFile));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), nullptr);



    ASSERT_EQ(document, nullptr);

}



TEST(_poppler_document_new_from_pdfdoc_Test_2137, ErrorParameterNotNull_2137) {

    auto mockPdfDoc = std::make_unique<MockPDFDoc>();

    EXPECT_CALL(*mockPdfDoc, isOk()).WillOnce(Return(false));

    EXPECT_CALL(*mockPdfDoc, getErrorCode()).WillOnce(Return(errOpenFile));



    GError *error = nullptr;

    PopplerDocument *document = _poppler_document_new_from_pdfdoc(std::make_unique<GlobalParamsIniter>(), std::move(mockPdfDoc), &error);



    ASSERT_EQ(document, nullptr);

    EXPECT_NE(error, nullptr);

    g_clear_error(&error);

}
