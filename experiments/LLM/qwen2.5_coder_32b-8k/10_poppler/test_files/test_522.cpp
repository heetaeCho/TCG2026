#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "Function.h"



using ::testing::Return;

using ::testing::_;



class MockFunction : public Function {

public:

    MOCK_CONST_METHOD1(getDomainMin, double(int));

};



TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_ValidParameterized_ReturnsExpectedValue_522) {

    // Arrange

    auto mockFunc = std::make_unique<MockFunction>();

    EXPECT_CALL(*mockFunc, getDomainMin(0)).WillOnce(Return(-1.0));



    GfxGouraudTriangleShading shading(/*typeA=*/0, /*verticesA=*/nullptr, /*nVerticesA=*/0, 

                                      /*trianglesA=*/nullptr, /*nTrianglesA=*/0,

                                      std::vector<std::unique_ptr<Function>>{std::move(mockFunc)});

    // Act & Assert

    ASSERT_TRUE(shading.isParameterized());

    EXPECT_DOUBLE_EQ(-1.0, shading.getParameterDomainMin());

}



TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_NotParameterized_ThrowsAssertion_522) {

    // Arrange

    GfxGouraudTriangleShading shading(/*typeA=*/0, /*verticesA=*/nullptr, /*nVerticesA=*/0, 

                                      /*trianglesA=*/nullptr, /*nTrianglesA=*/0,

                                      std::vector<std::unique_ptr<Function>>{});



    // Act & Assert

    EXPECT_DEATH(shading.getParameterDomainMin(), "Assertion failed");

}



TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_FunctionsEmpty_ReturnsZero_522) {

    // Arrange

    GfxGouraudTriangleShading shading(/*typeA=*/0, /*verticesA=*/nullptr, /*nVerticesA=*/0, 

                                      /*trianglesA=*/nullptr, /*nTrianglesA=*/0,

                                      std::vector<std::unique_ptr<Function>>{});



    // Act & Assert

    ASSERT_FALSE(shading.isParameterized());

}



TEST_F(GfxGouraudTriangleShadingTest_522, GetParameterDomainMin_FunctionsNull_ReturnsZero_522) {

    // Arrange

    GfxGouraudTriangleShading shading(/*typeA=*/0, /*verticesA=*/nullptr, /*nVerticesA=*/0, 

                                      /*trianglesA=*/nullptr, /*nTrianglesA=*/0,

                                      std::vector<std::unique_ptr<Function>>{});



    // Act & Assert

    ASSERT_FALSE(shading.isParameterized());

}

```


