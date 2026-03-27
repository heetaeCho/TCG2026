#include <gtest/gtest.h>

#include "leveldb/status.h"



namespace leveldb {



class StatusTest_22 : public ::testing::Test {

protected:

    Status okStatus;

    Status notFoundStatus;



    StatusTest_22() : okStatus(Status::OK()), notFoundStatus(Status::NotFound("Not found")) {}

};



TEST_F(StatusTest_22, OkReturnsTrueForOkStatus_22) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_22, OkReturnsFalseForNotFoundStatus_22) {

    EXPECT_FALSE(notFoundStatus.ok());

}



TEST_F(StatusTest_22, IsNotFoundReturnsTrueForNotFoundStatus_22) {

    EXPECT_TRUE(notFoundStatus.IsNotFound());

}



TEST_F(StatusTest_22, IsNotFoundReturnsFalseForOkStatus_22) {

    EXPECT_FALSE(okStatus.IsNotFound());

}



TEST_F(StatusTest_22, ToStringIsNotEmptyForOkStatus_22) {

    EXPECT_FALSE(okStatus.ToString().empty());

}



TEST_F(StatusTest_22, ToStringIsNotEmptyForNotFoundStatus_22) {

    EXPECT_FALSE(notFoundStatus.ToString().empty());

}



}  // namespace leveldb
