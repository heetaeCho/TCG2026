#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"

#include <sstream>



using namespace Exiv2;

using ::testing::Return;



TEST(IfdIdStreamOperatorTest_123, NormalOperation_123) {

    std::ostringstream oss;

    IfdId id = static_cast<IfdId>(42);

    oss << id;

    EXPECT_EQ("42", oss.str());

}



TEST(IfdIdStreamOperatorTest_123, BoundaryConditionMin_123) {

    std::ostringstream oss;

    IfdId id = static_cast<IfdId>(std::numeric_limits<int>::min());

    oss << id;

    EXPECT_EQ(std::to_string(std::numeric_limits<int>::min()), oss.str());

}



TEST(IfdIdStreamOperatorTest_123, BoundaryConditionMax_123) {

    std::ostringstream oss;

    IfdId id = static_cast<IfdId>(std::numeric_limits<int>::max());

    oss << id;

    EXPECT_EQ(std::to_string(std::numeric_limits<int>::max()), oss.str());

}
