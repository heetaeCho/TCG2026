#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-annot.cc"

#include "./TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class PopplerAnnotMock : public AnnotGeometry {

public:

    MockFunction<AnnotColor*()> mockGetInteriorColor;

    

    PopplerAnnotMock(PDFDoc* docA, PDFRectangle* rect, AnnotSubtype subType)

        : AnnotGeometry(docA, rect, subType) {}



    AnnotColor* getInteriorColor() const override {

        return mockGetInteriorColor.Call();

    }

};



class PopplerAnnotTest_2113 : public ::testing::Test {

protected:

    void SetUp() override {

        PDFDoc* doc = nullptr; // Assuming a valid document is needed, but not used here

        PDFRectangle rect(0, 0, 0, 0);

        mockAnnotGeometry = std::make_unique<PopplerAnnotMock>(doc, &rect, AnnotSubtype::ANNOT_SUBTYPE_HIGHLIGHT);

        popplerAnnot = new PopplerAnnot();

        popplerAnnot->annot.reset(mockAnnotGeometry.release());

    }



    void TearDown() override {

        delete popplerAnnot;

    }



    std::unique_ptr<PopplerAnnotMock> mockAnnotGeometry;

    PopplerAnnot* popplerAnnot;

};



TEST_F(PopplerAnnotTest_2113, GetInteriorColor_ReturnsValidPointer_2113) {

    auto interiorColor = std::make_unique<AnnotColor>();

    EXPECT_CALL(*mockAnnotGeometry, mockGetInteriorColor())

        .WillOnce(Return(interiorColor.get()));



    PopplerColor* result = poppler_annot_geometry_get_interior_color(popplerAnnot);

    EXPECT_EQ(result, interiorColor.get());

}



TEST_F(PopplerAnnotTest_2113, GetInteriorColor_ReturnsNullPointer_2113) {

    EXPECT_CALL(*mockAnnotGeometry, mockGetInteriorColor())

        .WillOnce(Return(nullptr));



    PopplerColor* result = poppler_annot_geometry_get_interior_color(popplerAnnot);

    EXPECT_EQ(result, nullptr);

}
