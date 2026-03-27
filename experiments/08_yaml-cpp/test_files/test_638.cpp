#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/emitterutils.h"

#include "yaml-cpp/binary.h"

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML::Utils;

using namespace YAML;



class WriteBatchTest_638 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper out{oss};

};



TEST_F(WriteBatchTest_638, WriteBinary_NormalOperation_638) {

    Binary binary{(const unsigned char*)"test", 4};

    EXPECT_TRUE(WriteBinary(out, binary));

    EXPECT_EQ(oss.str(), "dGVzdA==");

}



TEST_F(WriteBatchTest_638, WriteBinary_EmptyData_638) {

    Binary binary;

    EXPECT_TRUE(WriteBinary(out, binary));

    EXPECT_EQ(oss.str(), "");

}



TEST_F(WriteBatchTest_638, WriteBinary_BoundaryCondition_638) {

    Binary binary{(const unsigned char*)"\x00", 1};

    EXPECT_TRUE(WriteBinary(out, binary));

    EXPECT_EQ(oss.str(), "AA==");

}



TEST_F(WriteBatchTest_638, WriteBinary_LargerData_638) {

    std::string data(1024, 'A');

    Binary binary{(const unsigned char*)data.data(), data.size()};

    EXPECT_TRUE(WriteBinary(out, binary));
