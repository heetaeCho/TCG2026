#include <gtest/gtest.h>

#include "yaml-cpp/emitter.h"



class EmitterTest_528 : public ::testing::Test {

protected:

    YAML::Emitter emitter;

};



TEST_F(EmitterTest_528, SetDoublePrecision_NormalOperation_528) {

    EXPECT_TRUE(emitter.SetDoublePrecision(10));

}



TEST_F(EmitterTest_528, SetDoublePrecision_BoundaryCondition_Zero_528) {

    EXPECT_TRUE(emitter.SetDoublePrecision(0));

}



TEST_F(EmitterTest_528, SetDoublePrecision_BoundaryCondition_MaxSizeT_528) {

    EXPECT_TRUE(emitter.SetDoublePrecision(std::numeric_limits<std::size_t>::max()));

}



// Assuming there is no error case for setting double precision based on the provided interface

// If there were any observable errors, they would be tested here.

```


