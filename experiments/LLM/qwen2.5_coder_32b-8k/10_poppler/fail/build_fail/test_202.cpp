#include <gtest/gtest.h>

#include "Stream.h"



class EOFStreamTest_202 : public ::testing::Test {

protected:

    std::unique_ptr<EOFStream> eofStream;



    void SetUp() override {

        eofStream = std::make_unique<EOFStream>();

    }

};



TEST_F(EOFStreamTest_202, IsBinaryReturnsFalseWhenLastIsTrue_202) {

    EXPECT_FALSE(eofStream->isBinary(true));

}



TEST_F(EOFStreamTest_202, IsBinaryReturnsFalseWhenLastIsFalse_202) {

    EXPECT_FALSE(eofStream->isBinary(false));

}
