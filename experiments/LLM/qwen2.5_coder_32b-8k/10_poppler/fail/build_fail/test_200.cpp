#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



using namespace testing;



class EOFStreamTest_200 : public Test {

protected:

    std::unique_ptr<EOFStream> eofStream;



    void SetUp() override {

        eofStream = std::make_unique<EOFStream>(std::make_unique<Stream>());

    }

};



TEST_F(EOFStreamTest_200, LookCharReturnsEOF_200) {

    EXPECT_EQ(eofStream->lookChar(), EOF);

}



TEST_F(EOFStreamTest_200, GetCharReturnsEOF_200) {

    EXPECT_EQ(eofStream->getChar(), EOF);

}



TEST_F(EOFStreamTest_200, RewindReturnsFalse_200) {

    EXPECT_FALSE(eofStream->rewind());

}



TEST_F(EOFStreamTest_200, GetPSFilterReturnsNullopt_200) {

    EXPECT_EQ(eofStream->getPSFilter(1, ""), std::nullopt);

}



TEST_F(EOFStreamTest_200, IsBinaryReturnsTrue_200) {

    EXPECT_TRUE(eofStream->isBinary(true));

}
