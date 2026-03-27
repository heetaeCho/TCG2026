#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exp.h"



using namespace YAML;

using namespace Exp;



class ScanScalarEndTest_148 : public ::testing::Test {

protected:

    const RegEx& scan_scalar_end = ScanScalarEnd();

};



TEST_F(ScanScalarEndTest_148, Matches_EndOfScalar_148) {

    EXPECT_TRUE(scan_scalar_end.Matches("\n"));

}



TEST_F(ScanScalarEndTest_148, Matches_BlankFollowedByComment_148) {

    EXPECT_TRUE(scan_scalar_end.Matches(" # This is a comment"));

}



TEST_F(ScanScalarEndTest_148, DoesNotMatch_EmptyString_148) {

    EXPECT_FALSE(scan_scalar_end.Matches(""));

}



TEST_F(ScanScalarEndTest_148, DoesNotMatch_RandomCharacters_148) {

    EXPECT_FALSE(scan_scalar_end.Matches("random"));

}



TEST_F(ScanScalarEndTest_148, Matches_BlankOnly_148) {

    EXPECT_TRUE(scan_scalar_end.Matches(" "));

}



TEST_F(ScanScalarEndTest_148, Matches_CommentOnly_148) {

    EXPECT_TRUE(scan_scalar_end.Matches("# Comment only"));

}



TEST_F(ScanScalarEndTest_148, Matches_NewlineFollowedByComment_148) {

    EXPECT_TRUE(scan_scalar_end.Matches("\n# Another comment"));

}
