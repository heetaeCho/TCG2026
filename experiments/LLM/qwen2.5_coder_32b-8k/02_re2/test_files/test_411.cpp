#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/prog.h"



using namespace re2;



class ProgTest : public ::testing::Test {

protected:

    Prog prog;

};



TEST_F(ProgTest_411, ComputeByteMap_NormalOperation_411) {

    // Setup: Arrange the program with some instructions that include kInstByteRange and kInstEmptyWidth.

    Inst* inst0 = new Inst();

    inst0->InitByteRange('a', 'z', 0, 0);

    prog.inst_[0] = *inst0;



    Inst* inst1 = new Inst();

    inst1->InitByteRange('A', 'Z', 0, 0);

    prog.inst_[1] = *inst1;



    Inst* inst2 = new Inst();

    inst2->InitEmptyWidth(kEmptyBeginLine | kEmptyWordBoundary, 0);

    prog.inst_[2] = *inst2;



    prog.size_ = 3;



    // Act: Call ComputeByteMap

    prog.ComputeByteMap();



    // Assert: Verify the bytemap_range and specific bytes in the bytemap

    EXPECT_EQ(prog.bytemap_range(), 256);

    for (int i = 'a'; i <= 'z'; ++i) {

        EXPECT_NE(prog.bytemap_[i], prog.bytemap_['A']);

    }

    for (int i = 'A'; i <= 'Z'; ++i) {

        EXPECT_EQ(prog.bytemap_[i], prog.bytemap_['a']);

    }

    EXPECT_EQ(prog.bytemap_['\n'], prog.bytemap_['a'] + 1); // Line boundary

}



TEST_F(ProgTest_411, ComputeByteMap_BoundaryConditions_411) {

    // Setup: Arrange the program with minimal instructions.

    Inst* inst0 = new Inst();

    inst0->InitByteRange('a', 'a', 0, 0);

    prog.inst_[0] = *inst0;



    prog.size_ = 1;



    // Act: Call ComputeByteMap

    prog.ComputeByteMap();



    // Assert: Verify the bytemap_range and specific bytes in the bytemap

    EXPECT_EQ(prog.bytemap_range(), 256);

    EXPECT_NE(prog.bytemap_['a'], 0);

}



TEST_F(ProgTest_411, ComputeByteMap_ExceptionalCases_411) {

    // Setup: Arrange the program with no instructions.

    prog.size_ = 0;



    // Act: Call ComputeByteMap

    prog.ComputeByteMap();



    // Assert: Verify the bytemap_range and specific bytes in the bytemap

    EXPECT_EQ(prog.bytemap_range(), 256);

    for (int i = 0; i < 256; ++i) {

        EXPECT_EQ(prog.bytemap_[i], 0);

    }

}



TEST_F(ProgTest_411, ComputeByteMap_WordBoundaryHandling_411) {

    // Setup: Arrange the program with instructions that include word boundaries.

    Inst* inst0 = new Inst();

    inst0->InitEmptyWidth(kEmptyWordBoundary | kEmptyNonWordBoundary, 0);

    prog.inst_[0] = *inst0;



    prog.size_ = 1;



    // Act: Call ComputeByteMap

    prog.ComputeByteMap();



    // Assert: Verify the bytemap_range and specific bytes in the bytemap for word boundaries

    EXPECT_EQ(prog.bytemap_range(), 256);

    int word_char_color = prog.bytemap_['a'];

    int non_word_char_color = prog.bytemap_[' '];



    // Check transitions at word boundaries

    EXPECT_NE(word_char_color, non_word_char_color);



    for (int i = 0; i < 256; ++i) {

        if (Prog::IsWordChar(static_cast<uint8_t>(i))) {

            EXPECT_EQ(prog.bytemap_[i], word_char_color);

        } else {

            EXPECT_NE(prog.bytemap_[i], word_char_color);

        }

    }

}



TEST_F(ProgTest_411, ComputeByteMap_LineBoundaryHandling_411) {

    // Setup: Arrange the program with instructions that include line boundaries.

    Inst* inst0 = new Inst();

    inst0->InitEmptyWidth(kEmptyBeginLine | kEmptyEndLine, 0);

    prog.inst_[0] = *inst0;



    prog.size_ = 1;



    // Act: Call ComputeByteMap

    prog.ComputeByteMap();



    // Assert: Verify the bytemap_range and specific bytes in the bytemap for line boundaries

    EXPECT_EQ(prog.bytemap_range(), 256);

    int line_boundary_color = prog.bytemap_['\n'];



    EXPECT_NE(line_boundary_color, 0);



    // Check line boundary character

    EXPECT_EQ(prog.bytemap_['\n'], line_boundary_color);

}
