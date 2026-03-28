#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/JBIG2Stream.h"



class JBIG2StreamTest : public ::testing::Test {

protected:

    std::unique_ptr<Stream> mockStream;

    Object globalsStream;

    Ref expectedRef = 123; // Example reference value



    void SetUp() override {

        mockStream = std::make_unique<Stream>();

        globalsStream.initNull();

        JBIG2Stream* jbig2Stream = new JBIG2Stream(std::move(mockStream), std::move(globalsStream), &expectedRef);

        stream.reset(jbig2Stream);

    }



    void TearDown() override {

        stream.release();

    }



    std::unique_ptr<JBIG2Stream> stream;

};



TEST_F(JBIG2StreamTest_1483, GetGlobalsStreamRef_ReturnsExpectedValue_1483) {

    EXPECT_EQ(stream->getGlobalsStreamRef(), expectedRef);

}



// Additional test cases can be added here following the same pattern
