#include <gtest/gtest.h>

#include "AnnotStampImageHelper.h"



// Mock PDFDoc for dependency injection

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST_F(AnnotStampImageHelperTest_732, GetWidthReturnsCorrectValue_732) {

    MockPDFDoc mockPdfDoc;

    int widthA = 100;

    AnnotStampImageHelper helper(&mockPdfDoc, widthA, 50, ColorSpace::DeviceRGB, 8, nullptr, 0);

    EXPECT_EQ(helper.getWidth(), widthA);

}



TEST_F(AnnotStampImageHelperTest_732, GetHeightReturnsCorrectValue_732) {

    MockPDFDoc mockPdfDoc;

    int heightA = 50;

    AnnotStampImageHelper helper(&mockPdfDoc, 100, heightA, ColorSpace::DeviceRGB, 8, nullptr, 0);

    EXPECT_EQ(helper.getHeight(), heightA);

}



TEST_F(AnnotStampImageHelperTest_732, GetWidthBoundaryConditionZero_732) {

    MockPDFDoc mockPdfDoc;

    AnnotStampImageHelper helper(&mockPdfDoc, 0, 50, ColorSpace::DeviceRGB, 8, nullptr, 0);

    EXPECT_EQ(helper.getWidth(), 0);

}



TEST_F(AnnotStampImageHelperTest_732, GetHeightBoundaryConditionZero_732) {

    MockPDFDoc mockPdfDoc;

    AnnotStampImageHelper helper(&mockPdfDoc, 100, 0, ColorSpace::DeviceRGB, 8, nullptr, 0);

    EXPECT_EQ(helper.getHeight(), 0);

}



TEST_F(AnnotStampImageHelperTest_732, GetRefDoesNotThrowException_732) {

    MockPDFDoc mockPdfDoc;

    AnnotStampImageHelper helper(&mockPdfDoc, 100, 50, ColorSpace::DeviceRGB, 8, nullptr, 0);

    EXPECT_NO_THROW(helper.getRef());

}



TEST_F(AnnotStampImageHelperTest_732, RemoveAnnotStampImageObjectDoesNotThrowException_732) {

    MockPDFDoc mockPdfDoc;

    AnnotStampImageHelper helper(&mockPdfDoc, 100, 50, ColorSpace::DeviceRGB, 8, nullptr, 0);

    EXPECT_NO_THROW(helper.removeAnnotStampImageObject());

}
