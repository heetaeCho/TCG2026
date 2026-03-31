#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

#include "GfxState.h"
#include "Object.h"
#include "Function.h"

// Since we need to test GfxPatchMeshShading which requires construction with
// specific parameters, and we're treating the implementation as a black box,
// we test through the public interface.

// Helper to create a minimal GfxPatchMeshShading without functions (non-parameterized)
class GfxPatchMeshShadingTest_527 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a GfxPatchMeshShading with no patches and no functions reports correct patch count
TEST_F(GfxPatchMeshShadingTest_527, NoPatchesNonParameterized_527) {
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    // Create with 0 patches and no functions
    GfxPatchMeshShading shading(6, nullptr, 0, std::move(emptyFuncs));

    EXPECT_EQ(shading.getNPatches(), 0);
    EXPECT_FALSE(shading.isParameterized());
}

// Test that a GfxPatchMeshShading with patches reports correct patch count
TEST_F(GfxPatchMeshShadingTest_527, WithPatches_527) {
    GfxPatch patches[2];
    memset(patches, 0, sizeof(patches));

    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, patches, 2, std::move(emptyFuncs));

    EXPECT_EQ(shading.getNPatches(), 2);
    EXPECT_FALSE(shading.isParameterized());
}

// Test getPatch returns valid pointer for valid index
TEST_F(GfxPatchMeshShadingTest_527, GetPatchValidIndex_527) {
    GfxPatch patches[3];
    memset(patches, 0, sizeof(patches));

    // Set some distinguishable data
    patches[0].x[0][0] = 1.0;
    patches[1].x[0][0] = 2.0;
    patches[2].x[0][0] = 3.0;

    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, patches, 3, std::move(emptyFuncs));

    EXPECT_EQ(shading.getNPatches(), 3);

    const GfxPatch* p0 = shading.getPatch(0);
    ASSERT_NE(p0, nullptr);
    EXPECT_DOUBLE_EQ(p0->x[0][0], 1.0);

    const GfxPatch* p1 = shading.getPatch(1);
    ASSERT_NE(p1, nullptr);
    EXPECT_DOUBLE_EQ(p1->x[0][0], 2.0);

    const GfxPatch* p2 = shading.getPatch(2);
    ASSERT_NE(p2, nullptr);
    EXPECT_DOUBLE_EQ(p2->x[0][0], 3.0);
}

// Test isParameterized returns false when no functions are provided
TEST_F(GfxPatchMeshShadingTest_527, IsParameterizedFalseWithoutFunctions_527) {
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, nullptr, 0, std::move(emptyFuncs));

    EXPECT_FALSE(shading.isParameterized());
}

// Test copy produces a valid copy
TEST_F(GfxPatchMeshShadingTest_527, CopyPreservesPatches_527) {
    GfxPatch patches[2];
    memset(patches, 0, sizeof(patches));
    patches[0].x[0][0] = 42.0;
    patches[1].x[0][0] = 84.0;

    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, patches, 2, std::move(emptyFuncs));

    auto copied = shading.copy();
    ASSERT_NE(copied, nullptr);

    // Dynamic cast to GfxPatchMeshShading to verify
    GfxPatchMeshShading* copiedPatchMesh = dynamic_cast<GfxPatchMeshShading*>(copied.get());
    ASSERT_NE(copiedPatchMesh, nullptr);

    EXPECT_EQ(copiedPatchMesh->getNPatches(), 2);
    EXPECT_DOUBLE_EQ(copiedPatchMesh->getPatch(0)->x[0][0], 42.0);
    EXPECT_DOUBLE_EQ(copiedPatchMesh->getPatch(1)->x[0][0], 84.0);
}

// Test that type 6 and type 7 shadings can be created
TEST_F(GfxPatchMeshShadingTest_527, TypeSixShading_527) {
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, nullptr, 0, std::move(emptyFuncs));
    EXPECT_EQ(shading.getType(), 6);
}

TEST_F(GfxPatchMeshShadingTest_527, TypeSevenShading_527) {
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(7, nullptr, 0, std::move(emptyFuncs));
    EXPECT_EQ(shading.getType(), 7);
}

// Test single patch access
TEST_F(GfxPatchMeshShadingTest_527, SinglePatchAccess_527) {
    GfxPatch patch;
    memset(&patch, 0, sizeof(patch));
    patch.x[0][0] = 100.0;
    patch.y[0][0] = 200.0;

    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, &patch, 1, std::move(emptyFuncs));

    EXPECT_EQ(shading.getNPatches(), 1);
    const GfxPatch* retrieved = shading.getPatch(0);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_DOUBLE_EQ(retrieved->x[0][0], 100.0);
    EXPECT_DOUBLE_EQ(retrieved->y[0][0], 200.0);
}

// Test copy of non-parameterized shading maintains isParameterized == false
TEST_F(GfxPatchMeshShadingTest_527, CopyNonParameterized_527) {
    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(6, nullptr, 0, std::move(emptyFuncs));

    auto copied = shading.copy();
    GfxPatchMeshShading* copiedPatchMesh = dynamic_cast<GfxPatchMeshShading*>(copied.get());
    ASSERT_NE(copiedPatchMesh, nullptr);
    EXPECT_FALSE(copiedPatchMesh->isParameterized());
}

// Test with multiple patches that all patch data is preserved
TEST_F(GfxPatchMeshShadingTest_527, MultiplePatchesDataIntegrity_527) {
    const int numPatches = 5;
    GfxPatch patches[numPatches];
    memset(patches, 0, sizeof(patches));

    for (int i = 0; i < numPatches; i++) {
        patches[i].x[0][0] = static_cast<double>(i * 10);
        patches[i].y[0][0] = static_cast<double>(i * 20);
    }

    std::vector<std::unique_ptr<Function>> emptyFuncs;
    GfxPatchMeshShading shading(7, patches, numPatches, std::move(emptyFuncs));

    EXPECT_EQ(shading.getNPatches(), numPatches);

    for (int i = 0; i < numPatches; i++) {
        const GfxPatch* p = shading.getPatch(i);
        ASSERT_NE(p, nullptr);
        EXPECT_DOUBLE_EQ(p->x[0][0], static_cast<double>(i * 10));
        EXPECT_DOUBLE_EQ(p->y[0][0], static_cast<double>(i * 20));
    }
}
