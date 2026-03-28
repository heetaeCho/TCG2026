#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"

#include <memory>



using namespace testing;



class EOFStreamTest_197 : public ::testing::Test {

protected:

    std::unique_ptr<EOFStream> eofStream;

};



TEST_F(EOFStreamTest_197, GetKindReturnsStrWeird_197) {

    auto stream = std::make_unique<OwnedFilterStream>(nullptr); // Mock or dummy OwnedFilterStream

    eofStream = std::make_unique<EOFStream>(std::move(stream));

    EXPECT_EQ(eofStream->getKind(), strWeird);

}



TEST_F(EOFStreamTest_197, RewindReturnsFalseByDefault_197) {

    auto stream = std::make_unique<OwnedFilterStream>(nullptr); // Mock or dummy OwnedFilterStream

    eofStream = std::make_unique<EOFStream>(std::move(stream));

    EXPECT_FALSE(eofStream->rewind());

}



TEST_F(EOFStreamTest_197, GetCharReturnsEOFByDefault_197) {

    auto stream = std::make_unique<OwnedFilterStream>(nullptr); // Mock or dummy OwnedFilterStream

    eofStream = std::make_unique<EOFStream>(std::move(stream));

    EXPECT_EQ(eofStream->getChar(), EOF);

}



TEST_F(EOFStreamTest_197, LookCharReturnsEOFByDefault_197) {

    auto stream = std::make_unique<OwnedFilterStream>(nullptr); // Mock or dummy OwnedFilterStream

    eofStream = std::make_unique<EOFStream>(std::move(stream));

    EXPECT_EQ(eofStream->lookChar(), EOF);

}



TEST_F(EOFStreamTest_197, GetPSFilterReturnsEmptyOptionalByDefault_197) {

    auto stream = std::make_unique<OwnedFilterStream>(nullptr); // Mock or dummy OwnedFilterStream

    eofStream = std::make_unique<EOFStream>(std::move(stream));

    EXPECT_FALSE(eofStream->getPSFilter(0, "").has_value());

}



TEST_F(EOFStreamTest_197, IsBinaryReturnsTrueByDefault_197) {

    auto stream = std::make_unique<OwnedFilterStream>(nullptr); // Mock or dummy OwnedFilterStream

    eofStream = std::make_unique<EOFStream>(std::move(stream));

    EXPECT_TRUE(eofStream->isBinary(true));

}
