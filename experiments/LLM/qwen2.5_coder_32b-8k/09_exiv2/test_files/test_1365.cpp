#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "exiv2/tags.hpp"

#include "tags_int.cpp"  // Assuming the implementation is included for testing



using namespace Exiv2;

using namespace Exiv2::Internal;



class TaglistTest_1365 : public ::testing::Test {

protected:

    std::ostringstream os;

};



TEST_F(TaglistTest_1365, NormalOperation_1365) {

    IfdId ifdId = 0; // Assuming a valid IfdId for normal operation

    taglist(os, ifdId);

    EXPECT_FALSE(os.str().empty()) << "Output should not be empty for a valid IFD ID.";

}



TEST_F(TaglistTest_1365, BoundaryCondition_EmptyTagList_1365) {

    IfdId ifdId = 0xFFFF; // Assuming this IfdId has no tags

    taglist(os, ifdId);

    EXPECT_TRUE(os.str().empty()) << "Output should be empty for an IFD ID with no tags.";

}



TEST_F(TaglistTest_1365, BoundaryCondition_MaxTagList_1365) {

    IfdId ifdId = 1; // Assuming this IfdId has the maximum number of tags

    taglist(os, ifdId);

    EXPECT_FALSE(os.str().empty()) << "Output should not be empty for an IFD ID with maximum tags.";

}



TEST_F(TaglistTest_1365, ExceptionalCase_InvalidIfdId_1365) {

    IfdId ifdId = -1; // Assuming this is an invalid IfdId

    taglist(os, ifdId);

    EXPECT_TRUE(os.str().empty()) << "Output should be empty for an invalid IFD ID.";

}
