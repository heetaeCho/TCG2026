#include <gtest/gtest.h>



// Assuming LZWEncoder is part of a namespace or included properly

class LZWEncoderTest : public ::testing::Test {

protected:

    LZWEncoder encoder;

};



TEST_F(LZWEncoderTest_228, IsBinary_ReturnsTrue_228) {

    // Test normal operation where isBinary should return true

    EXPECT_TRUE(encoder.isBinary());

}



TEST_F(LZWEncoderTest_228, IsBinary_ReturnsTrueWithLastFalse_228) {

    // Test boundary condition with last parameter set to false

    EXPECT_TRUE(encoder.isBinary(false));

}



TEST_F(LZWEncoderTest_228, IsBinary_ReturnsTrueWithLastTrue_228) {

    // Test boundary condition with last parameter set to true (default behavior)

    EXPECT_TRUE(encoder.isBinary(true));

}

```


