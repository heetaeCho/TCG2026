#include <gtest/gtest.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_stream_end_stop.hpp"



namespace Catch {



class StreamEndStopTests : public ::testing::Test {

protected:

    StreamEndStop streamEndStop;

};



TEST_F(StreamEndStopTests_71, OperatorPlusReturnsOriginalValue_71) {

    int value = 42;

    EXPECT_EQ(value + streamEndStop, value);

}



TEST_F(StreamEndStopTests_71, OperatorPlusWithDifferentType_71) {

    double value = 3.14;

    EXPECT_EQ(value + streamEndStop, value);

}



TEST_F(StreamEndStopTests_71, OperatorPlusWithZeroValue_71) {

    int zeroValue = 0;

    EXPECT_EQ(zeroValue + streamEndStop, zeroValue);

}



} // namespace Catch
