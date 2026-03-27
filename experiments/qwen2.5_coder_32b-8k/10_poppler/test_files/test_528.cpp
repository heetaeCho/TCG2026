#include <gtest/gtest.h>

#include "GfxState.h"

#include "Function.h"



using namespace std;



class GfxPatchMeshShadingTest_528 : public ::testing::Test {

protected:

    void SetUp() override {

        // Mock Functions to be used in tests

        functions.push_back(make_unique<Function>());

        EXPECT_CALL(*functions[0], getDomainMax(0)).WillRepeatedly(testing::Return(1.0));

        EXPECT_CALL(*functions[0], isOk()).WillRepeatedly(testing::Return(true));



        // Create a GfxPatchMeshShading object with the mocked functions

        patches = nullptr;

        nPatches = 0;

        shading = make_unique<GfxPatchMeshShading>(1, patches, nPatches, move(functions));

    }



    void TearDown() override {

        shading.reset();

        functions.clear();

    }



    vector<unique_ptr<Function>> functions;

    GfxPatch* patches;

    int nPatches;

    unique_ptr<GfxPatchMeshShading> shading;

};



TEST_F(GfxPatchMeshShadingTest_528, GetParameterDomainMax_NormalOperation_528) {

    EXPECT_TRUE(shading->isParameterized());

    EXPECT_EQ(shading->getParameterDomainMax(), 1.0);

}



TEST_F(GfxPatchMeshShadingTest_528, IsParameterized_BoundaryConditions_528) {

    // If no functions are available, isParameterized should return false

    shading.reset(new GfxPatchMeshShading(1, patches, nPatches, vector<unique_ptr<Function>>{}));

    EXPECT_FALSE(shading->isParameterized());

}



TEST_F(GfxPatchMeshShadingTest_528, GetParameterDomainMax_ExceptionalCase_528) {

    // If the function is not OK, getParameterDomainMax should return a default value

    EXPECT_CALL(*functions[0], isOk()).WillOnce(testing::Return(false));

    shading.reset(new GfxPatchMeshShading(1, patches, nPatches, move(functions)));

    EXPECT_THROW(shading->getParameterDomainMax(), logic_error);

}
