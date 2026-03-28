#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "prog.h"

#include <string>



using namespace re2;



class ProgTest_404 : public ::testing::Test {

protected:

    Prog* prog;



    void SetUp() override {

        prog = new Prog();

    }



    void TearDown() override {

        delete prog;

    }

};



TEST_F(ProgTest_404, DumpByteMap_DefaultConstructor_404) {

    std::string result = prog->DumpByteMap();

    EXPECT_EQ(result.size(), 256 * 13); // Each line is 13 characters long.

}



TEST_F(ProgTest_404, DumpByteMap_AllSameValues_404) {

    for (int c = 0; c < 256; ++c) {

        prog->bytemap_[c] = 1;

    }

    std::string result = prog->DumpByteMap();

    EXPECT_EQ(result.size(), 13); // All characters map to the same value, so one line.

}



TEST_F(ProgTest_404, DumpByteMap_AllUniqueValues_404) {

    for (int c = 0; c < 256; ++c) {

        prog->bytemap_[c] = c;

    }

    std::string result = prog->DumpByteMap();

    EXPECT_EQ(result.size(), 256 * 13); // All characters map to unique values, so 256 lines.

}



TEST_F(ProgTest_404, DumpByteMap_RandomValues_404) {

    for (int c = 0; c < 256; ++c) {

        prog->bytemap_[c] = rand() % 10;

    }

    std::string result = prog->DumpByteMap();

    EXPECT_GT(result.size(), 0);

}



TEST_F(ProgTest_404, DumpByteMap_AllZeroValues_404) {

    for (int c = 0; c < 256; ++c) {

        prog->bytemap_[c] = 0;

    }

    std::string result = prog->DumpByteMap();

    EXPECT_EQ(result.size(), 13); // All characters map to zero, so one line.

}
