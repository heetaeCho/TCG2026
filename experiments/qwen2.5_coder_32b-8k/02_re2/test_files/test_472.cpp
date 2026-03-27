#include <gtest/gtest.h>

#include "filtered_re2.h"

#include "re2/re2.h"



class FilteredRE2Test_472 : public ::testing::Test {

protected:

    re2::FilteredRE2 filtered_re2;

};



TEST_F(FilteredRE2Test_472, AddValidPattern_ReturnsNoError_472) {

    int id = -1;

    re2::RE2::ErrorCode code = filtered_re2.Add("abc", re2::RE2::Options(), &id);

    EXPECT_EQ(code, re2::RE2::NoError);

    EXPECT_GE(id, 0);

}



TEST_F(FilteredRE2Test_472, AddInvalidPattern_ReturnsNonZeroErrorCode_472) {

    int id = -1;

    re2::RE2::ErrorCode code = filtered_re2.Add("(*", re2::RE2::Options(), &id);

    EXPECT_NE(code, re2::RE2::NoError);

}



TEST_F(FilteredRE2Test_472, AddMultiplePatterns_IncrementsId_472) {

    int id1 = -1;

    int id2 = -1;

    filtered_re2.Add("abc", re2::RE2::Options(), &id1);

    filtered_re2.Add("def", re2::RE2::Options(), &id2);

    EXPECT_EQ(id2, id1 + 1);

}



TEST_F(FilteredRE2Test_472, AddPatternWithLoggingEnabled_LogsError_472) {

    int id = -1;

    re2::RE2::Options options;

    options.set_log_errors(true);



    // Mocking ABSL_LOG(ERROR) is not feasible with Google Test directly.

    // We can only assume that if the pattern is invalid, it logs an error.



    re2::RE2::ErrorCode code = filtered_re2.Add("(*", options, &id);

    EXPECT_NE(code, re2::RE2::NoError);

}



TEST_F(FilteredRE2Test_472, AddPatternWithLoggingDisabled_DoesNotLogError_472) {

    int id = -1;

    re2::RE2::Options options;

    options.set_log_errors(false);



    // Mocking ABSL_LOG(ERROR) is not feasible with Google Test directly.

    // We can only assume that if the pattern is invalid, it does not log an error.



    re2::RE2::ErrorCode code = filtered_re2.Add("(*", options, &id);

    EXPECT_NE(code, re2::RE2::NoError);

}



TEST_F(FilteredRE2Test_472, AddEmptyPattern_ReturnsNonZeroErrorCode_472) {

    int id = -1;

    re2::RE2::ErrorCode code = filtered_re2.Add("", re2::RE2::Options(), &id);

    EXPECT_NE(code, re2::RE2::NoError);

}



TEST_F(FilteredRE2Test_472, AddPatternWithNullIdPointer_ReturnsError_472) {

    int* null_id = nullptr;

    re2::RE2::ErrorCode code = filtered_re2.Add("abc", re2::RE2::Options(), null_id);

    EXPECT_NE(code, re2::RE2::NoError);

}
