#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"



// Mock dependencies if needed

class MockPDFDoc : public PDFDoc {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST_F(AnnotTest_781, GetAnnotObj_ReturnsReferenceToObject_781) {

    // Arrange

    Object mockObject;

    Annot annot(nullptr, std::move(mockObject));



    // Act

    const Object& result = annot.getAnnotObj();



    // Assert

    EXPECT_EQ(&result, &mockObject);

}



TEST_F(AnnotTest_781, GetRect_ReturnsCorrectValues_781) {

    // Arrange

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);

    Annot annot(nullptr, std::move(rect));



    // Act & Assert

    double x1, y1, x2, y2;

    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 1.0);

    EXPECT_DOUBLE_EQ(y1, 2.0);

    EXPECT_DOUBLE_EQ(x2, 3.0);

    EXPECT_DOUBLE_EQ(y2, 4.0);

}



TEST_F(AnnotTest_781, GetAppearance_ReturnsValidObject_781) {

    // Arrange

    Object mockAppearance;

    Annot annot(nullptr, std::move(mockAppearance));



    // Act & Assert

    const Object& result = annot.getAppearance();

    EXPECT_EQ(&result, &mockAppearance);

}



TEST_F(AnnotTest_781, IsOk_ReturnsTrueForValidObject_781) {

    // Arrange

    Object mockObject;

    Annot annot(nullptr, std::move(mockObject));



    // Act & Assert

    EXPECT_TRUE(annot.isOk());

}



TEST_F(AnnotTest_781, InRect_ReturnsTrueForPointInsideRectangle_781) {

    // Arrange

    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);

    Annot annot(nullptr, std::move(rect));



    // Act & Assert

    EXPECT_TRUE(annot.inRect(1.0, 1.0));

}



TEST_F(AnnotTest_781, InRect_ReturnsFalseForPointOutsideRectangle_781) {

    // Arrange

    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);

    Annot annot(nullptr, std::move(rect));



    // Act & Assert

    EXPECT_FALSE(annot.inRect(3.0, 3.0));

}



TEST_F(AnnotTest_781, GetContents_ReturnsCorrectString_781) {

    // Arrange

    auto contents = std::make_unique<GooString>("Test Content");

    Annot annot(nullptr, Object());

    annot.setContents(std::move(contents));



    // Act & Assert

    EXPECT_STREQ(annot.getContents()->getCString(), "Test Content");

}



TEST_F(AnnotTest_781, GetModified_ReturnsCorrectString_781) {

    // Arrange

    auto modified = std::make_unique<GooString>("2023-10-01");

    Annot annot(nullptr, Object());

    annot.setModified(std::move(modified));



    // Act & Assert

    EXPECT_STREQ(annot.getModified()->getCString(), "2023-10-01");

}



TEST_F(AnnotTest_781, GetPageNum_ReturnsCorrectPageNumber_781) {

    // Arrange

    PDFRectangle rect(0.0, 0.0, 2.0, 2.0);

    Annot annot(nullptr, std::move(rect));

    annot.setPage(5, false);



    // Act & Assert

    EXPECT_EQ(annot.getPageNum(), 5);

}



TEST_F(AnnotTest_781, GetFlags_ReturnsCorrectFlags_781) {

    // Arrange

    Annot annot(nullptr, Object());

    unsigned int flags = 0x1F;

    annot.setFlags(flags);



    // Act & Assert

    EXPECT_EQ(annot.getFlags(), flags);

}



TEST_F(AnnotTest_781, SetAndGetBorder_CorrectlySetsAndReturnsBorder_781) {

    // Arrange

    auto border = std::make_unique<AnnotBorder>(2.0, 3.0, 4.0);

    Annot annot(nullptr, Object());

    annot.setBorder(std::move(border));



    // Act & Assert

    EXPECT_EQ(annot.getBorder()->getWidth(), 2.0);

    EXPECT_EQ(annot.getBorder()->getHorizontalRadius(), 3.0);

    EXPECT_EQ(annot.getBorder()->getVerticalRadius(), 4.0);

}



TEST_F(AnnotTest_781, SetAndGetColor_CorrectlySetsAndReturnsColor_781) {

    // Arrange

    auto color = std::make_unique<AnnotColor>(255, 0, 0);

    Annot annot(nullptr, Object());

    annot.setColor(std::move(color));



    // Act & Assert

    EXPECT_EQ(annot.getColor()->getRed(), 255);

    EXPECT_EQ(annot.getColor()->getGreen(), 0);

    EXPECT_EQ(annot.getColor()->getBlue(), 0);

}



TEST_F(AnnotTest_781, GetAppearState_ReturnsCorrectState_781) {

    // Arrange

    Annot annot(nullptr, Object());

    annot.setAppearanceState("Normal");



    // Act & Assert

    EXPECT_STREQ(annot.getAppearState(), "Normal");

}
