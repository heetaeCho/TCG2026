#include <gtest/gtest.h>

#include "GfxState.h"



class GfxColorTransformTest_398 : public ::testing::Test {

protected:

    void *transform;

    int cmsIntent;

    unsigned int inputPixelType;

    unsigned int transformPixelType;



    void SetUp() override {

        transform = nullptr; // Assuming no specific initialization is required for the test

        cmsIntent = 0;

        inputPixelType = 1;

        transformPixelType = 2;

    }



    GfxColorTransform *getGfxColorTransformInstance() {

        return new GfxColorTransform(transform, cmsIntent, inputPixelType, transformPixelType);

    }

};



TEST_F(GfxColorTransformTest_398, GetInputPixelType_ReturnsCorrectValue_398) {

    auto *gfxColorTransform = getGfxColorTransformInstance();

    EXPECT_EQ(gfxColorTransform->getInputPixelType(), static_cast<int>(inputPixelType));

    delete gfxColorTransform;

}



TEST_F(GfxColorTransformTest_398, GetIntent_ReturnsCorrectValue_398) {

    auto *gfxColorTransform = getGfxColorTransformInstance();

    EXPECT_EQ(gfxColorTransform->getIntent(), cmsIntent);

    delete gfxColorTransform;

}



TEST_F(GfxColorTransformTest_398, GetTransformPixelType_ReturnsCorrectValue_398) {

    auto *gfxColorTransform = getGfxColorTransformInstance();

    EXPECT_EQ(gfxColorTransform->getTransformPixelType(), static_cast<int>(transformPixelType));

    delete gfxColorTransform;

}



// Assuming doTransform has observable side effects or return values, we would test it here.

// However, since the interface does not specify any return value or side effect, we assume no direct testing is possible.



TEST_F(GfxColorTransformTest_398, Constructor_WithValidParameters_CreatesInstance_398) {

    EXPECT_NO_THROW(getGfxColorTransformInstance());

}



TEST_F(GfxColorTransformTest_398, CopyConstructor_IsDeleted_398) {

    auto *gfxColorTransform = getGfxColorTransformInstance();

    EXPECT_DELETE_COPY_CONSTRUCTOR(*gfxColorTransform);

    delete gfxColorTransform;

}



TEST_F(GfxColorTransformTest_398, AssignmentOperator_IsDeleted_398) {

    auto *gfxColorTransform = getGfxColorTransformInstance();

    GfxColorTransform other(transform, cmsIntent, inputPixelType, transformPixelType);

    EXPECT_DELETE_ASSIGNMENT_OPERATOR(*gfxColorTransform, other);

    delete gfxColorTransform;

}

```


