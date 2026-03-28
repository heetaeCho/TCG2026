#include <gtest/gtest.h>

#include "Annot.h"



class AnnotBorderEffectTest_744 : public ::testing::Test {

protected:

    double testIntensity = 0.5;

    AnnotBorderEffect* annotBorderEffect;



    void SetUp() override {

        // Assuming a constructor that allows setting intensity for testing purposes

        annotBorderEffect = new AnnotBorderEffect(/* mock Dict */ nullptr);

        // Use reflection or other means to set the intensity if necessary

        annotBorderEffect->intensity = testIntensity;

    }



    void TearDown() override {

        delete annotBorderEffect;

    }

};



TEST_F(AnnotBorderEffectTest_744, GetIntensity_ReturnsExpectedValue_744) {

    EXPECT_DOUBLE_EQ(annotBorderEffect->getIntensity(), testIntensity);

}



// Assuming there are other observable behaviors or additional functions in the real class

// that need to be tested. Since only getIntensity is provided, we focus on it.



// Boundary conditions and exceptional cases are not applicable here as per the given interface.

```


