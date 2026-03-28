#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextLineTest : public ::testing::Test {

protected:

    TextBlock mockBlk;

    int rot = 0;

    double base = 0.0;



    std::unique_ptr<TextLine> textLine;



    void SetUp() override {

        textLine = std::make_unique<TextLine>(&mockBlk, rot, base);

    }

};



TEST_F(TextLineTest_1204, IsHyphenated_DefaultFalse_1204) {

    EXPECT_FALSE(textLine->isHyphenated());

}



// Assuming there's a way to set the hyphenated state externally for testing

// If not, we can only test the default behavior as shown above.

```


