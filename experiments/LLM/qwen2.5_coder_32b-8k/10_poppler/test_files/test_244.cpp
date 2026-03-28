#include <gtest/gtest.h>



// Assuming the class SplashBitmapCMYKEncoder is part of a namespace or included properly.

// Since no namespace is provided, we'll assume it's in the global namespace for this test file.



class SplashBitmapCMYKEncoderTest : public ::testing::Test {

protected:

    SplashBitmapCMYKEncoder encoder;

};



TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_ReturnsTrueForLastFalse_244) {

    EXPECT_TRUE(encoder.isBinary(false));

}



TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_ReturnsTrueForLastTrue_244) {

    EXPECT_TRUE(encoder.isBinary(true));

}



// Since the function always returns true and has no observable side effects,

// there are no boundary conditions or exceptional/error cases to test.
