#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/tags_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



struct TagDetails {

    int64_t value_;

    const char* label_;

};



const TagDetails tagArray[] = {

    { 1, "TagOne" },

    { 2, "TagTwo" },

    { 3, "TagThree" }

};



TEST_F(PrintTagTest_182, KnownValuePrintsLabel_182) {

    std::ostringstream os;

    printTag<3, tagArray>(os, 1, nullptr);

    EXPECT_EQ(os.str(), "TagOne");

}



TEST_F(PrintTagTest_182, AnotherKnownValuePrintsLabel_182) {

    std::ostringstream os;

    printTag<3, tagArray>(os, 3, nullptr);

    EXPECT_EQ(os.str(), "TagThree");

}



TEST_F(PrintTagTest_182, UnknownValuePrintsNumeric_182) {

    std::ostringstream os;

    printTag<3, tagArray>(os, 4, nullptr);

    EXPECT_EQ(os.str(), "(4)");

}



TEST_F(PrintTagTest_182, BoundaryMinValuePrintsLabel_182) {

    std::ostringstream os;

    printTag<3, tagArray>(os, 1, nullptr);

    EXPECT_EQ(os.str(), "TagOne");

}



TEST_F(PrintTagTest_182, BoundaryMaxValuePrintsLabel_182) {

    std::ostringstream os;

    printTag<3, tagArray>(os, 3, nullptr);

    EXPECT_EQ(os.str(), "TagThree");

}
