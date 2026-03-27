#include <gtest/gtest.h>

#include "GfxState.h"

#include "Function.h"



using namespace poppler;



class GfxGouraudTriangleShadingTest_523 : public ::testing::Test {

protected:

    std::unique_ptr<Function> func;

    std::vector<std::unique_ptr<Function>> funcs;

    int typeA = 0;

    GfxGouraudVertex* verticesA = nullptr;

    int nVerticesA = 0;

    int (*trianglesA)[3] = nullptr;

    int nTrianglesA = 0;



    void SetUp() override {

        func = std::make_unique<Function>();

        funcs.push_back(std::move(func));

    }

};



TEST_F(GfxGouraudTriangleShadingTest_523, GetParameterDomainMax_NormalOperation_523) {

    GfxGouraudTriangleShading shading(typeA, verticesA, nVerticesA, trianglesA, nTrianglesA, std::move(funcs));

    EXPECT_CALL(*funcs[0], getDomainMax(0)).WillOnce(::testing::Return(1.0));

    EXPECT_EQ(shading.getParameterDomainMax(), 1.0);

}



TEST_F(GfxGouraudTriangleShadingTest_523, GetParameterDomainMax_IsParameterizedTrue_523) {

    GfxGouraudTriangleShading shading(typeA, verticesA, nVerticesA, trianglesA, nTrianglesA, std::move(funcs));

    EXPECT_CALL(*funcs[0], getDomainMax(0)).WillOnce(::testing::Return(1.0));

    EXPECT_EQ(shading.getParameterDomainMax(), 1.0);

}



TEST_F(GfxGouraudTriangleShadingTest_523, GetParameterDomainMax_IsParameterizedFalse_523) {

    GfxGouraudTriangleShading shading(typeA, verticesA, nVerticesA, trianglesA, nTrianglesA, std::move(funcs));

    EXPECT_CALL(*funcs[0], getDomainMax(0)).WillOnce(::testing::Return(1.0));

    EXPECT_THROW(shading.getParameterDomainMax(), std::runtime_error); // Assuming an exception is thrown when not parameterized

}



TEST_F(GfxGouraudTriangleShadingTest_523, GetParameterDomainMax_FunctionReturnsBoundaryValue_523) {

    GfxGouraudTriangleShading shading(typeA, verticesA, nVerticesA, trianglesA, nTrianglesA, std::move(funcs));

    EXPECT_CALL(*funcs[0], getDomainMax(0)).WillOnce(::testing::Return(std::numeric_limits<double>::max()));

    EXPECT_EQ(shading.getParameterDomainMax(), std::numeric_limits<double>::max());

}
