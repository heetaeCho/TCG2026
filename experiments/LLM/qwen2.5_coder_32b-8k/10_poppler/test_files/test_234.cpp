#include <gtest/gtest.h>



// Assuming CMYKGrayEncoder is part of a namespace or included correctly

// class CMYKGrayEncoder { public: bool isBinary(bool /*last = true*/) const override { return false; } };



TEST(CMYKGrayEncoderTest_234, IsBinary_ReturnsFalseByDefault_234) {

    CMYKGrayEncoder encoder;

    EXPECT_FALSE(encoder.isBinary());

}



TEST(CMYKGrayEncoderTest_234, IsBinary_ReturnsFalseWithLastTrue_234) {

    CMYKGrayEncoder encoder;

    EXPECT_FALSE(encoder.isBinary(true));

}



TEST(CMYKGrayEncoderTest_234, IsBinary_ReturnsFalseWithLastFalse_234) {

    CMYKGrayEncoder encoder;

    EXPECT_FALSE(encoder.isBinary(false));

}

```


