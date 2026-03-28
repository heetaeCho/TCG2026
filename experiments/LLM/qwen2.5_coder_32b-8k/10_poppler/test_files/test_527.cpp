#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "Function.h"



using namespace testing;



class GfxPatchMeshShadingTest : public Test {

protected:

    MockFunction<Function> mockFunc;

    std::vector<std::unique_ptr<Function>> funcs = {std::make_unique<NiceMock<MockFunction>>(mockFunc)};



    GfxPatchMeshShadingTest()

        : patches(nullptr), nPatches(0),

          shading(1, patches, nPatches, std::move(funcs)) {}



    ~GfxPatchMeshShadingTest() override = default;



    GfxPatch* patches;

    int nPatches;

    GfxPatchMeshShading shading;

};



TEST_F(GfxPatchMeshShadingTest_527, GetParameterDomainMin_ReturnsCorrectValueWhenParameterized_527) {

    EXPECT_CALL(mockFunc, getDomainMin(0)).WillOnce(Return(10.0));

    EXPECT_TRUE(shading.isParameterized());

    EXPECT_EQ(shading.getParameterDomainMin(), 10.0);

}



TEST_F(GfxPatchMeshShadingTest_527, GetParameterDomainMax_ReturnsCorrectValueWhenParameterized_527) {

    EXPECT_CALL(mockFunc, getDomainMax(0)).WillOnce(Return(20.0));

    EXPECT_TRUE(shading.isParameterized());

    EXPECT_EQ(shading.getParameterDomainMax(), 20.0);

}



TEST_F(GfxPatchMeshShadingTest_527, GetNPatches_ReturnsCorrectNumberOfPatches_527) {

    EXPECT_EQ(shading.getNPatches(), nPatches);

}



TEST_F(GfxPatchMeshShadingTest_527, IsParameterized_ReturnsTrueWhenFunctionsAreProvided_527) {

    EXPECT_TRUE(shading.isParameterized());

}



TEST_F(GfxPatchMeshShadingTest_527, GetParameterDomainMin_ThrowsAssertionFailureWhenNotParameterized_527) {

    GfxPatchMeshShading nonParametrizedShading(1, nullptr, 0, std::vector<std::unique_ptr<Function>>{});

    EXPECT_DEATH(nonParametrizedShading.getParameterDomainMin(), "");

}



TEST_F(GfxPatchMeshShadingTest_527, GetParameterDomainMax_ThrowsAssertionFailureWhenNotParameterized_527) {

    GfxPatchMeshShading nonParametrizedShading(1, nullptr, 0, std::vector<std::unique_ptr<Function>>{});

    EXPECT_DEATH(nonParametrizedShading.getParameterDomainMax(), "");

}
