#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/JPEG2000Stream.h"



class JPXStreamTest_1466 : public ::testing::Test {

protected:

    std::unique_ptr<JPXStream> jpxStream;



    void SetUp() override {

        auto mockStream = std::make_unique<::testing::StrictMock<Stream>>();

        jpxStream = std::make_unique<JPXStream>(std::move(mockStream));

    }

};



TEST_F(JPXStreamTest_1466, SetSupportJPXtransparency_DefaultValue_1466) {

    EXPECT_FALSE(jpxStream->supportJPXtransparency());

}



TEST_F(JPXStreamTest_1466, SetSupportJPXtransparency_EnableTransparency_1466) {

    jpxStream->setSupportJPXtransparency(true);

    EXPECT_TRUE(jpxStream->supportJPXtransparency());

}



TEST_F(JPXStreamTest_1466, SetSupportJPXtransparency_DisableTransparency_1466) {

    jpxStream->setSupportJPXtransparency(false);

    EXPECT_FALSE(jpxStream->supportJPXtransparency());

}



TEST_F(JPXStreamTest_1466, SetSupportJPXtransparency_ToggleMultipleTimes_1466) {

    jpxStream->setSupportJPXtransparency(true);

    EXPECT_TRUE(jpxStream->supportJPXtransparency());



    jpxStream->setSupportJPXtransparency(false);

    EXPECT_FALSE(jpxStream->supportJPXtransparency());



    jpxStream->setSupportJPXtransparency(true);

    EXPECT_TRUE(jpxStream->supportJPXtransparency());

}
