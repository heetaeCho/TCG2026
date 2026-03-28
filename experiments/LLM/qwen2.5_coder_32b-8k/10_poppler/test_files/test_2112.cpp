#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-page.h"



// Mocking PopplerAnnotLine to verify interactions with setVertices

class MockPopplerAnnotLine : public _PopplerAnnotLine {

public:

    MOCK_METHOD(void, setVertices, (double x1, double y1, double x2, double y2), ());

};



TEST_F(PopplerAnnotLineTest_2112, SetVertices_NormalOperation_2112) {

    MockPopplerAnnotLine mockAnnotLine;

    PopplerPoint startPoint = {1.0, 2.0};

    PopplerPoint endPoint = {3.0, 4.0};



    EXPECT_CALL(mockAnnotLine, setVertices(1.0, 2.0, 3.0, 4.0));



    poppler_annot_line_set_vertices(reinterpret_cast<PopplerAnnotLine*>(&mockAnnotLine), &startPoint, &endPoint);

}



TEST_F(PopplerAnnotLineTest_2112, SetVertices_BoundaryConditions_2112) {

    MockPopplerAnnotLine mockAnnotLine;

    PopplerPoint startPoint = {0.0, 0.0};

    PopplerPoint endPoint = {0.0, 0.0};



    EXPECT_CALL(mockAnnotLine, setVertices(0.0, 0.0, 0.0, 0.0));



    poppler_annot_line_set_vertices(reinterpret_cast<PopplerAnnotLine*>(&mockAnnotLine), &startPoint, &endPoint);

}



TEST_F(PopplerAnnotLineTest_2112, SetVertices_ExceptionalCase_NullStartPoint_2112) {

    MockPopplerAnnotLine mockAnnotLine;

    PopplerPoint endPoint = {3.0, 4.0};



    EXPECT_DEATH(poppler_annot_line_set_vertices(reinterpret_cast<PopplerAnnotLine*>(&mockAnnotLine), nullptr, &endPoint), ".*g_return_if_fail.*start != nullptr.*");

}



TEST_F(PopplerAnnotLineTest_2112, SetVertices_ExceptionalCase_NullEndPoint_2112) {

    MockPopplerAnnotLine mockAnnotLine;

    PopplerPoint startPoint = {1.0, 2.0};



    EXPECT_DEATH(poppler_annot_line_set_vertices(reinterpret_cast<PopplerAnnotLine*>(&mockAnnotLine), &startPoint, nullptr), ".*g_return_if_fail.*end != nullptr.*");

}
