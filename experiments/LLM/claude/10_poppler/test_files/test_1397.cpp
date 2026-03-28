#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"

#include "Annot.h"
#include "Page.h"
#include "PDFDoc.h"
#include "Catalog.h"
#include "Form.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"
#include "PDFDocFactory.h"

#include <QFont>
#include <QColor>
#include <QString>
#include <QRectF>

namespace {

class TextAnnotationPrivateTest_1397 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure globalParams is initialized
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a simple PDF document in memory for testing
    std::unique_ptr<PDFDoc> createSimplePDF(const std::string& filename) {
        auto fileNameGoo = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fileNameGoo), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test that setDefaultAppearanceToNative does not crash when pdfAnnot is null
TEST_F(TextAnnotationPrivateTest_1397, NullPdfAnnotDoesNotCrash_1397) {
    Poppler::TextAnnotationPrivate priv;
    // pdfAnnot is null by default
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
}

// Test that setDefaultAppearanceToNative does not crash when pdfAnnot is non-FreeText type
TEST_F(TextAnnotationPrivateTest_1397, NonFreeTextAnnotDoesNothing_1397) {
    Poppler::TextAnnotationPrivate priv;
    // If we can construct a text annotation (not free text), calling setDefaultAppearanceToNative
    // should be safe since it checks for typeFreeText
    // With null pdfAnnot this is effectively a no-op
    priv.pdfAnnot = nullptr;
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
}

// Test that setDefaultAppearanceToNative handles null textFont
TEST_F(TextAnnotationPrivateTest_1397, NullTextFontHandled_1397) {
    Poppler::TextAnnotationPrivate priv;
    // textFont should be null/default initially
    // pdfAnnot is null, so method returns early
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
}

// Test that setDefaultAppearanceToNative handles null pdfPage gracefully
TEST_F(TextAnnotationPrivateTest_1397, NullPdfPageDoesNotCrash_1397) {
    Poppler::TextAnnotationPrivate priv;
    priv.pdfPage = nullptr;
    // pdfAnnot is null, method should return early
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
}

// Test default construction of TextAnnotationPrivate
TEST_F(TextAnnotationPrivateTest_1397, DefaultConstruction_1397) {
    Poppler::TextAnnotationPrivate priv;
    EXPECT_EQ(priv.inplaceAlign, 0);
    EXPECT_EQ(priv.pdfPage, nullptr);
    EXPECT_EQ(priv.pdfAnnot, nullptr);
}

// Test that calling setDefaultAppearanceToNative multiple times does not crash
TEST_F(TextAnnotationPrivateTest_1397, MultipleCallsDoNotCrash_1397) {
    Poppler::TextAnnotationPrivate priv;
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
}

// Test with a real PDF document if available - integration style test
TEST_F(TextAnnotationPrivateTest_1397, WithRealDocumentFreeTextAnnotation_1397) {
    // Try to load a test PDF - this test is conditional on file existence
    auto fileName = std::make_unique<GooString>("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping integration test";
    }

    Poppler::TextAnnotationPrivate priv;
    // Even with a valid doc but no annotation tied, should not crash
    EXPECT_NO_FATAL_FAILURE(priv.setDefaultAppearanceToNative());
}

// Test the DefaultAppearance class used by setDefaultAppearanceToNative
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceConstruction_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Helvetica");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 12.0);
    EXPECT_NE(da.getFontColor(), nullptr);
}

// Test DefaultAppearance with empty font name
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceEmptyFontName_1397) {
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    DefaultAppearance da("", 10.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 10.0);
}

// Test DefaultAppearance with negative font size (boundary condition)
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceNegativeFontSize_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Courier", -1.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Courier");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), -1.0);
}

// Test DefaultAppearance with zero font size
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceZeroFontSize_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Times", 0.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Times");
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 0.0);
}

// Test DefaultAppearance setFontName
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceSetFontName_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontName("Courier");
    EXPECT_EQ(da.getFontName(), "Courier");
}

// Test DefaultAppearance setFontPtSize
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceSetFontPtSize_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    da.setFontPtSize(24.0);
    EXPECT_DOUBLE_EQ(da.getFontPtSize(), 24.0);
}

// Test DefaultAppearance with Invalid_font (the fallback used in setDefaultAppearanceToNative)
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceInvalidFont_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Invalid_font", 12.0, std::move(color));
    
    EXPECT_EQ(da.getFontName(), "Invalid_font");
}

// Test DefaultAppearance toAppearanceString produces non-empty output
TEST_F(TextAnnotationPrivateTest_1397, DefaultAppearanceToString_1397) {
    auto color = std::make_unique<AnnotColor>(0.0, 0.0, 0.0);
    DefaultAppearance da("Helvetica", 12.0, std::move(color));
    
    std::string result = da.toAppearanceString();
    EXPECT_FALSE(result.empty());
}

} // namespace
