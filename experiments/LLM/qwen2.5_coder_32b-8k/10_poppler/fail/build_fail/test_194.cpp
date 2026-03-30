#include <gtest/gtest.h>

#include "Stream.h"



class CCITTFaxStreamTest_194 : public ::testing::Test {

protected:

    std::unique_ptr<CCITTFaxStream> stream;



    void SetUp() override {

        // Create a valid instance of CCITTFaxStream for testing

        stream = std::make_unique<CCITTFaxStream>(

            std::make_unique<Stream>(), 0, false, false, 1728, 2200, false, true, 3);

    }

};



TEST_F(CCITTFaxStreamTest_194, GetBlackIs1_ReturnsTrue_194) {

    // Test normal operation where black is set to true

    EXPECT_TRUE(stream->getBlackIs1());

}



TEST_F(CCITTFaxStreamTest_194, GetBlackIs1_ReturnsFalse_194) {

    // Create a new instance with black set to false

    stream = std::make_unique<CCITTFaxStream>(

        std::make_unique<Stream>(), 0, false, false, 1728, 2200, false, false, 3);

    EXPECT_FALSE(stream->getBlackIs1());

}



TEST_F(CCITTFaxStreamTest_194, GetBlackIs1_BoundaryCondition_194) {

    // Test boundary condition with minimum columns and rows

    stream = std::make_unique<CCITTFaxStream>(

        std::make_unique<Stream>(), 0, false, false, 1, 1, false, true, 3);

    EXPECT_TRUE(stream->getBlackIs1());



    // Test boundary condition with maximum plausible values for columns and rows

    stream = std::make_unique<CCITTFaxStream>(

        std::make_unique<Stream>(), 0, false, false, INT_MAX, INT_MAX, false, true, 3);

    EXPECT_TRUE(stream->getBlackIs1());

}
