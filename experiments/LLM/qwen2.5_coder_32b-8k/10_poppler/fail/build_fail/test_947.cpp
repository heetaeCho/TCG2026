#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/PDFDoc.h"



using namespace std;



class PDFDocTest_947 : public ::testing::Test {

protected:

    virtual void SetUp() {

        // Setup code if necessary, but avoid initializing objects with actual data.

    }



    virtual void TearDown() {

        // Cleanup code if necessary.

    }

};



TEST_F(PDFDocTest_947, GetErrorCode_ReturnsZeroInitially_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_EQ(doc.getErrorCode(), 0);

}



TEST_F(PDFDocTest_947, IsOk_ReturnsTrueInitially_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_TRUE(doc.isOk());

}



TEST_F(PDFDocTest_947, GetFopenErrno_ReturnsZeroInitially_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_EQ(doc.getFopenErrno(), 0);

}



TEST_F(PDFDocTest_947, GetFileName_ReturnsCorrectName_947) {

    auto fileName = make_unique<GooString>("testfile.pdf");

    PDFDoc doc(move(fileName), nullopt, nullopt, [](){});

    EXPECT_STREQ(doc.getFileName()->getCString(), "testfile.pdf");

}



TEST_F(PDFDocTest_947, GetXRef_ReturnsNonNullPointer_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_NE(doc.getXRef(), nullptr);

}



TEST_F(PDFDocTest_947, GetCatalog_ReturnsNonNullPointer_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_NE(doc.getCatalog(), nullptr);

}



TEST_F(PDFDocTest_947, GetNumPages_ReturnsZeroForEmptyDocument_947) {

    PDFDoc doc(make_unique<GooString>("empty.pdf"), nullopt, nullopt, [](){});

    EXPECT_EQ(doc.getNumPages(), 0);

}



TEST_F(PDFDocTest_947, GetPage_ReturnsNullPointerForInvalidPageNumber_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_EQ(doc.getPage(1), nullptr);

}



TEST_F(PDFDocTest_947, IsLinearized_ReturnsFalseInitially_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_FALSE(doc.isLinearized(false));

}



TEST_F(PDFDocTest_947, GetOutline_ReturnsNullPointerForNoOutline_947) {

    PDFDoc doc(make_unique<GooString>("no_outline.pdf"), nullopt, nullopt, [](){});

    EXPECT_EQ(doc.getOutline(), nullptr);

}



TEST_F(PDFDocTest_947, GetSignatureFields_ReturnsEmptyVectorInitially_947) {

    PDFDoc doc(make_unique<GooString>("dummy.pdf"), nullopt, nullopt, [](){});

    EXPECT_TRUE(doc.getSignatureFields().empty());

}
