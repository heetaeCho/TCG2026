#include <gtest/gtest.h>

#include "NullOStream.h"



class NullOStreamTest : public ::testing::Test {

protected:

    NullOStream nullOStream;

};



TEST_F(NullOStreamTest_NormalOperation_19, RdbufReturnsThisPointer_19) {

    EXPECT_EQ(nullOStream.rdbuf(), static_cast<NullStreambuf*>(&nullOStream));

}



TEST_F(NullOStreamTest_BoundaryConditions_19, RdbufConsistencyCheck_19) {

    NullStreambuf* rdbufPtr = nullOStream.rdbuf();

    EXPECT_EQ(rdbufPtr, static_cast<NullStreambuf*>(&nullOStream));

    EXPECT_EQ(nullOStream.rdbuf(), rdbufPtr);

}



TEST_F(NullOStreamTest_ExceptionalCases_19, NoThrowOnRdbufCall_19) {

    EXPECT_NO_THROW({

        nullOStream.rdbuf();

    });

}
