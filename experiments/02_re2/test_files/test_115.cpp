#include <gtest/gtest.h>

#include "re2/prog.h"



namespace re2 {

class ProgTest_115 : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_115, SetStartUnanchored_NormalOperation_115) {

    int start_value = 42;

    prog.set_start_unanchored(start_value);

    EXPECT_EQ(prog.start_unanchored(), start_value);

}



TEST_F(ProgTest_115, StartUnanchored_DefaultValue_115) {

    EXPECT_EQ(prog.start_unanchored(), 0);

}



TEST_F(ProgTest_115, SetStartUnanchored_BoundaryConditions_115) {

    prog.set_start_unanchored(-1);

    EXPECT_EQ(prog.start_unanchored(), -1);



    prog.set_start_unanchored(0);

    EXPECT_EQ(prog.start_unanchored(), 0);



    prog.set_start_unanchored(INT_MAX);

    EXPECT_EQ(prog.start_unanchored(), INT_MAX);

}

} // namespace re2
