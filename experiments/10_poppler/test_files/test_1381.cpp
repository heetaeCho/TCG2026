#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the function arePgpSignaturesAllowed is part of a namespace called Poppler

namespace Poppler {

    bool arePgpSignaturesAllowed();

}



// Test fixture for testing the Poppler namespace functions

class PopplerTest_1381 : public ::testing::Test {

protected:

    // Setup and teardown can be added here if needed in the future

};



TEST_F(PopplerTest_1381, ArePgpSignaturesAllowed_ReturnsFalseWhenGPGMEIsDisabled_1381) {

    EXPECT_FALSE(Poppler::arePgpSignaturesAllowed());

}



// Since ENABLE_GPGME is a preprocessor directive, we cannot change it at runtime.

// Therefore, we can only test the behavior when GPGME is disabled as shown above.

// If there were a way to enable GPGME for testing purposes, additional tests could be written

// to verify the behavior when GPGME is enabled.



```


