#include <gtest/gtest.h>

#include "exiv2/riffvideo.hpp"



using namespace Exiv2;



class HeaderReaderTest_74 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> ioMock;

    RiffVideo::HeaderReader* headerReader;



    void SetUp() override {

        ioMock = BasicIo::createMemIo();

        headerReader = new RiffVideo::HeaderReader(ioMock);

    }



    void TearDown() override {

        delete headerReader;

    }

};



TEST_F(HeaderReaderTest_74, DefaultSizeIsZero_74) {

    EXPECT_EQ(headerReader->getSize(), 0U);

}



// Assuming getId returns an empty string by default if not set

TEST_F(HeaderReaderTest_74, DefaultIdIsEmptyString_74) {

    EXPECT_EQ(headerReader->getId(), "");

}
