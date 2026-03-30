#include <gtest/gtest.h>

#include "GfxState.h"



using namespace std;



class GfxPatchMeshShadingTest_526 : public ::testing::Test {

protected:

    GfxPatchMeshShading* shadingWithFuncs;

    GfxPatchMeshShading* shadingWithoutFuncs;



    void SetUp() override {

        // Mock data for patches

        GfxPatch* patches = nullptr;  // Assuming patches initialization is not relevant for this test



        std::vector<std::unique_ptr<Function>> funcsA;

        funcsA.emplace_back(std::make_unique<Function>());  // Mock Function object



        shadingWithFuncs = new GfxPatchMeshShading(1, patches, 0, std::move(funcsA));



        shadingWithoutFuncs = new GfxPatchMeshShading(1, patches, 0, std::vector<std::unique_ptr<Function>>{});

    }



    void TearDown() override {

        delete shadingWithFuncs;

        delete shadingWithoutFuncs;

    }

};



TEST_F(GfxPatchMeshShadingTest_526, IsParameterized_ReturnTrueWhenFunctionsExist_526) {

    EXPECT_TRUE(shadingWithFuncs->isParameterized());

}



TEST_F(GfxPatchMeshShadingTest_526, IsParameterized_ReturnFalseWhenNoFunctions_526) {

    EXPECT_FALSE(shadingWithoutFuncs->isParameterized());

}
