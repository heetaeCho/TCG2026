#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"

#include "gmock/gmock.h"



using namespace testing;



class PDFDocTest : public ::testing::Test {

protected:

    MockXRef* mock_xref;

    std::unique_ptr<GooString> fileName = std::make_unique<GooString>("dummy.pdf");

    std::optional<GooString> ownerPassword;

    std::optional<GooString> userPassword;

    std::function<void(void)> xrefReconstructedCallback;



    void SetUp() override {

        mock_xref = new MockXRef();

        ON_CALL(*mock_xref, isEncrypted()).WillByDefault(Return(false));

    }



    void TearDown() override {

        delete mock_xref;

    }

};



class MockXRef : public XRef {

public:

    MOCK_METHOD0(isEncrypted, bool());

};



TEST_F(PDFDocTest_963, IsEncrypted_ReturnsFalse_WhenXRefIsNotEncrypted_963) {

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    doc.xref = mock_xref;



    EXPECT_CALL(*mock_xref, isEncrypted()).WillOnce(Return(false));



    EXPECT_FALSE(doc.isEncrypted());

}



TEST_F(PDFDocTest_963, IsEncrypted_ReturnsTrue_WhenXRefIsEncrypted_963) {

    PDFDoc doc(std::move(fileName), ownerPassword, userPassword, xrefReconstructedCallback);

    doc.xref = mock_xref;



    EXPECT_CALL(*mock_xref, isEncrypted()).WillOnce(Return(true));



    EXPECT_TRUE(doc.isEncrypted());

}
