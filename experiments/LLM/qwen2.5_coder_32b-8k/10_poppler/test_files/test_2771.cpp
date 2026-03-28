#include <gtest/gtest.h>

#include "poppler-annotation.cc"

#include "poppler/Annot.h"



using namespace Poppler;



class AnnotationAppearancePrivateTest_2771 : public ::testing::Test {

protected:

    Annot* annot;

    Object appearanceObject;

    

    void SetUp() override {

        // Setup a mock or dummy Annot object

        annot = new Annot(nullptr, nullptr);

        // Optionally setup appearanceObject if needed for tests

    }



    void TearDown() override {

        delete annot;

    }

};



TEST_F(AnnotationAppearancePrivateTest_2771, ConstructorWithAnnot_2771) {

    AnnotationAppearancePrivate privateAppearance(annot);



    EXPECT_FALSE(privateAppearance.appearance.isNull());

}



TEST_F(AnnotationAppearancePrivateTest_2771, ConstructorWithNullAnnot_2771) {

    AnnotationAppearancePrivate privateAppearance(nullptr);



    EXPECT_TRUE(privateAppearance.appearance.isNull());

}



TEST_F(AnnotationAppearancePrivateTest_2771, VerifyNonDefaultConstructorBehavior_2771) {

    // Assuming some behavior is expected when Annot has specific values

    // Since we treat the implementation as a black box, we can only test observable outcomes

    AnnotationAppearancePrivate privateAppearance(annot);



    EXPECT_EQ(privateAppearance.appearance.getType(), annot->getAppearance().getType());

}



TEST_F(AnnotationAppearancePrivateTest_2771, VerifyNullAnnotSetsToNull_2771) {

    AnnotationAppearancePrivate privateAppearance(nullptr);



    EXPECT_TRUE(privateAppearance.appearance.isNull());

}
