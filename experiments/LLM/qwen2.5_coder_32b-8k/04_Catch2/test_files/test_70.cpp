#include <gtest/gtest.h>

#include "catch2/internal/catch_stream_end_stop.hpp"



using namespace Catch;



class StreamEndStopTest_70 : public ::testing::Test {

protected:

    StreamEndStop streamEndStop;

};



TEST_F(StreamEndStopTest_70, OperatorPlusReturnsEmptyStringRef_70) {

    StringRef result = +streamEndStop;

    EXPECT_EQ(result.size(), 0);

}



// Since the class and its method are very simple, there aren't many boundary conditions

// or exceptional cases to test. The main observable behavior is tested above.
