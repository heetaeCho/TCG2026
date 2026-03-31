#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "PDFDocFactory.h"

#include <memory>
#include <string>

class AnnotGeometryTest_843 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that getBorderEffect returns a value (possibly null) without crashing
// when constructed with a rectangle for Square subtype
TEST_F(AnnotGeometryTest_843, GetBorderEffectReturnsValue_Square_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    // getBorderEffect may return nullptr if no border effect is set
    AnnotBorderEffect *effect = annot->getBorderEffect();
    // We just verify the call doesn't crash; the value may be null
    SUCCEED();
}

// Test that getBorderEffect returns a value (possibly null) without crashing
// when constructed with a rectangle for Circle subtype
TEST_F(AnnotGeometryTest_843, GetBorderEffectReturnsValue_Circle_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(50, 50, 150, 150);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeCircle);
    
    AnnotBorderEffect *effect = annot->getBorderEffect();
    // May be nullptr if not set
    SUCCEED();
}

// Test getInteriorColor returns value after construction
TEST_F(AnnotGeometryTest_843, GetInteriorColorAfterConstruction_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    // Interior color may be nullptr by default
    AnnotColor *color = annot->getInteriorColor();
    SUCCEED();
}

// Test getGeometryRect returns value after construction
TEST_F(AnnotGeometryTest_843, GetGeometryRectAfterConstruction_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    PDFRectangle *geomRect = annot->getGeometryRect();
    // geomRect may be nullptr if not explicitly set from dict
    SUCCEED();
}

// Test setType changes the annotation subtype
TEST_F(AnnotGeometryTest_843, SetTypeChangesSubtype_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    EXPECT_EQ(annot->getType(), Annot::typeSquare);
    
    annot->setType(Annot::typeCircle);
    EXPECT_EQ(annot->getType(), Annot::typeCircle);
}

// Test setType from Circle to Square
TEST_F(AnnotGeometryTest_843, SetTypeFromCircleToSquare_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeCircle);
    
    EXPECT_EQ(annot->getType(), Annot::typeCircle);
    
    annot->setType(Annot::typeSquare);
    EXPECT_EQ(annot->getType(), Annot::typeSquare);
}

// Test setInteriorColor with a valid color
TEST_F(AnnotGeometryTest_843, SetInteriorColorWithValidColor_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));
    
    AnnotColor *retrievedColor = annot->getInteriorColor();
    ASSERT_NE(retrievedColor, nullptr);
}

// Test setInteriorColor with nullptr (clearing the color)
TEST_F(AnnotGeometryTest_843, SetInteriorColorWithNullptr_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    annot->setInteriorColor(nullptr);
    
    AnnotColor *retrievedColor = annot->getInteriorColor();
    EXPECT_EQ(retrievedColor, nullptr);
}

// Test getBorderEffect consistency - calling multiple times returns same pointer
TEST_F(AnnotGeometryTest_843, GetBorderEffectConsistency_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    AnnotBorderEffect *effect1 = annot->getBorderEffect();
    AnnotBorderEffect *effect2 = annot->getBorderEffect();
    EXPECT_EQ(effect1, effect2);
}

// Test with boundary rectangle values (zero-sized rect)
TEST_F(AnnotGeometryTest_843, ZeroSizedRectangle_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0, 0, 0, 0);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    // Should still be constructable and queryable
    AnnotBorderEffect *effect = annot->getBorderEffect();
    AnnotColor *color = annot->getInteriorColor();
    PDFRectangle *geomRect = annot->getGeometryRect();
    SUCCEED();
}

// Test with large rectangle values
TEST_F(AnnotGeometryTest_843, LargeRectangleValues_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0, 0, 10000, 10000);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeCircle);
    
    EXPECT_EQ(annot->getType(), Annot::typeCircle);
    AnnotBorderEffect *effect = annot->getBorderEffect();
    SUCCEED();
}

// Test setting interior color with different color spaces
TEST_F(AnnotGeometryTest_843, SetInteriorColorGray_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    auto color = std::make_unique<AnnotColor>(0.5);
    annot->setInteriorColor(std::move(color));
    
    AnnotColor *retrievedColor = annot->getInteriorColor();
    ASSERT_NE(retrievedColor, nullptr);
}

// Test setType with same type (idempotent)
TEST_F(AnnotGeometryTest_843, SetTypeSameType_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    annot->setType(Annot::typeSquare);
    EXPECT_EQ(annot->getType(), Annot::typeSquare);
}

// Test negative coordinate rectangle
TEST_F(AnnotGeometryTest_843, NegativeCoordinateRectangle_843) {
    GooString fileName("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(fileName));
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(-100, -100, 100, 100);
    auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
    
    EXPECT_EQ(annot->getType(), Annot::typeSquare);
    SUCCEED();
}
