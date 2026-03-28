#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Poppler includes
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"

#include "Annot.h"
#include "PDFDoc.h"
#include "Page.h"
#include "DefaultAppearance.h"

using namespace Poppler;

class TextAnnotationPrivateTest_1398 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a default-constructed TextAnnotationPrivate (with no native annotation)
// returns a null/empty unique_ptr from getDefaultAppearanceFromNative
TEST_F(TextAnnotationPrivateTest_1398, DefaultConstructed_ReturnsNull_1398)
{
    TextAnnotationPrivate priv;
    // pdfAnnot should be null by default, so the method should return empty unique_ptr
    auto result = priv.getDefaultAppearanceFromNative();
    EXPECT_EQ(result, nullptr);
}

// Test that getDefaultAppearanceFromNative returns empty when pdfAnnot is not set
TEST_F(TextAnnotationPrivateTest_1398, NoPdfAnnot_ReturnsEmpty_1398)
{
    TextAnnotationPrivate priv;
    // Without setting pdfAnnot, it should be nullptr
    std::unique_ptr<DefaultAppearance> da = priv.getDefaultAppearanceFromNative();
    EXPECT_FALSE(da);
}

// Test through the public TextAnnotation interface - a text annotation without
// native backing should yield default/empty appearance behavior
TEST_F(TextAnnotationPrivateTest_1398, TextAnnotationNoNative_DefaultAppearance_1398)
{
    // Create a TextAnnotation of InPlace subtype (which maps to FreeText)
    TextAnnotation ann(TextAnnotation::InPlace);
    
    // The annotation should have some default font and color properties
    // Even without native annotation, we can verify the annotation was created
    EXPECT_EQ(ann.textType(), TextAnnotation::InPlace);
}

// Test that a Linked (Text) type annotation can be created and queried
TEST_F(TextAnnotationPrivateTest_1398, LinkedTextAnnotation_Creation_1398)
{
    TextAnnotation ann(TextAnnotation::Linked);
    EXPECT_EQ(ann.textType(), TextAnnotation::Linked);
    // Default icon should be "Note"
    EXPECT_EQ(ann.textIcon(), QStringLiteral("Note"));
}

// Test default inplace alignment
TEST_F(TextAnnotationPrivateTest_1398, DefaultInplaceAlign_1398)
{
    TextAnnotation ann(TextAnnotation::InPlace);
    // Default inplaceAlign should be 0
    EXPECT_EQ(ann.inplaceAlign(), 0);
}

// Test setting and getting textIcon
TEST_F(TextAnnotationPrivateTest_1398, SetGetTextIcon_1398)
{
    TextAnnotation ann(TextAnnotation::Linked);
    ann.setTextIcon(QStringLiteral("Comment"));
    EXPECT_EQ(ann.textIcon(), QStringLiteral("Comment"));
}

// Test setting and getting inplaceAlign
TEST_F(TextAnnotationPrivateTest_1398, SetGetInplaceAlign_1398)
{
    TextAnnotation ann(TextAnnotation::InPlace);
    ann.setInplaceAlign(1);
    EXPECT_EQ(ann.inplaceAlign(), 1);
}

// Test boundary: setting inplaceAlign to edge values
TEST_F(TextAnnotationPrivateTest_1398, InplaceAlignBoundary_1398)
{
    TextAnnotation ann(TextAnnotation::InPlace);
    ann.setInplaceAlign(0);
    EXPECT_EQ(ann.inplaceAlign(), 0);
    ann.setInplaceAlign(2);
    EXPECT_EQ(ann.inplaceAlign(), 2);
}

// Test subType returns correct annotation type
TEST_F(TextAnnotationPrivateTest_1398, SubType_1398)
{
    TextAnnotation ann(TextAnnotation::Linked);
    EXPECT_EQ(ann.subType(), Annotation::AText);
}

// Test that setting empty textIcon works
TEST_F(TextAnnotationPrivateTest_1398, EmptyTextIcon_1398)
{
    TextAnnotation ann(TextAnnotation::Linked);
    ann.setTextIcon(QString());
    EXPECT_EQ(ann.textIcon(), QString());
}
