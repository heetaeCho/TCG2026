#include <gtest/gtest.h>

#include "Stream.h"



class EOFStreamTest_201 : public ::testing::Test {

protected:

    std::unique_ptr<EOFStream> stream;



    void SetUp() override {

        stream = std::make_unique<EOFStream>();

    }

};



TEST_F(EOFStreamTest_201, GetPSFilterReturnsEmptyOptional_201) {

    auto result = stream->getPSFilter(0, "");

    EXPECT_FALSE(result.has_value());

}



TEST_F(EOFStreamTest_201, GetPSFilterBoundaryConditionPSLevelNegative_201) {

    auto result = stream->getPSFilter(-1, "");

    EXPECT_FALSE(result.has_value());

}



TEST_F(EOFStreamTest_201, GetPSFilterBoundaryConditionPSLevelLarge_201) {

    auto result = stream->getPSFilter(1000, "");

    EXPECT_FALSE(result.has_value());

}



TEST_F(EOFStreamTest_201, GetPSFilterBoundaryConditionIndentNull_201) {

    auto result = stream->getPSFilter(0, nullptr);

    EXPECT_FALSE(result.has_value());

}
