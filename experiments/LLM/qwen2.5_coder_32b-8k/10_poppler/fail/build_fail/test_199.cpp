#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class EOFStreamTest_199 : public ::testing::Test {

protected:

    std::unique_ptr<EOFStream> eofStream;

    

    void SetUp() override {

        eofStream = std::make_unique<EOFStream>(0); // Using int constructor

    }

};



TEST_F(EOFStreamTest_199, GetCharReturnsEOF_199) {

    EXPECT_EQ(eofStream->getChar(), EOF);

}



TEST_F(EOFStreamTest_199, LookCharReturnsEOF_199) {

    EXPECT_EQ(eofStream->lookChar(), EOF);

}



TEST_F(EOFStreamTest_199, RewindAlwaysReturnsFalse_199) {

    EXPECT_FALSE(eofStream->rewind());

}



TEST_F(EOFStreamTest_199, GetPSFilterReturnsEmptyOptional_199) {

    EXPECT_EQ(eofStream->getPSFilter(0, ""), std::nullopt);

}



TEST_F(EOFStreamTest_199, IsBinaryAlwaysReturnsFalse_199) {

    EXPECT_FALSE(eofStream->isBinary(true));

}
