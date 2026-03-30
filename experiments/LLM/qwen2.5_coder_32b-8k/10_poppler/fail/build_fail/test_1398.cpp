#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.h"

#include <memory>



using namespace Poppler;



class MockAnnot : public Annot {

public:

    MOCK_CONST_METHOD0(getType, Annot::Subtype());

};



class TextAnnotationPrivateTest_1398 : public ::testing::Test {

protected:

    std::unique_ptr<MockAnnot> mockPdfAnnot;

    std::shared_ptr<Page> mockDestPage;

    std::shared_ptr<DocumentData> mockDoc;

    TextAnnotationPrivate textAnnotationPrivate;



    void SetUp() override {

        mockPdfAnnot = std::make_unique<MockAnnot>();

        textAnnotationPrivate.pdfAnnot = mockPdfAnnot;

    }

};



TEST_F(TextAnnotationPrivateTest_1398, GetDefaultAppearanceFromNative_ReturnsEmpty_WhenNotFreeText_1398) {

    EXPECT_CALL(*mockPdfAnnot, getType()).WillOnce(::testing::Return(Annot::typeText));

    auto result = textAnnotationPrivate.getDefaultAppearanceFromNative();

    EXPECT_FALSE(result);

}



TEST_F(TextAnnotationPrivateTest_1398, GetDefaultAppearanceFromNative_ReturnsNonEmpty_WhenFreeText_1398) {

    auto mockFtextAnn = std::make_unique<AnnotFreeText>();

    mockPdfAnnot.reset(mockFtextAnn.release());



    EXPECT_CALL(*mockPdfAnnot, getType()).WillOnce(::testing::Return(Annot::typeFreeText));

    auto result = textAnnotationPrivate.getDefaultAppearanceFromNative();

    EXPECT_TRUE(result);

}



// Assuming DefaultAppearance has a default constructor and can be instantiated.

class MockDefaultAppearance : public DefaultAppearance {

public:

    MockDefaultAppearance() = default;

};



TEST_F(TextAnnotationPrivateTest_1398, GetDefaultAppearanceFromNative_CallsDefaultAppearance_WhenFreeText_1398) {

    auto mockFtextAnn = std::make_unique<MockAnnotFreeText>();

    mockPdfAnnot.reset(mockFtextAnn.release());



    EXPECT_CALL(*mockPdfAnnot, getType()).WillOnce(::testing::Return(Annot::typeFreeText));

    EXPECT_CALL(*static_cast<MockAnnotFreeText*>(mockPdfAnnot.get()), getDefaultAppearance())

        .WillOnce(::testing::Return(std::make_unique<MockDefaultAppearance>()));



    auto result = textAnnotationPrivate.getDefaultAppearanceFromNative();

    EXPECT_TRUE(result);

}
