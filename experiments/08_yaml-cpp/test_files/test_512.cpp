#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include "yaml-cpp/src/indentation.h"

#include <sstream>



using namespace YAML;

using namespace std;



class IndentToTest_512 : public ::testing::Test {

protected:

    void SetUp() override {

        output_stream.str("");

        stream_wrapper = ostream_wrapper(output_stream);

    }



    stringstream output_stream;

    ostream_wrapper stream_wrapper;

};



TEST_F(IndentToTest_512, PutIncreasesCount_NormalOperation_512) {

    IndentTo indent(4);

    stream_wrapper << indent;

    EXPECT_EQ(stream_wrapper.col(), 4u);

}



TEST_F(IndentToTest_512, PutNoSpacesWhenAlreadyIndented_512) {

    IndentTo indent(0);

    stream_wrapper.write("    ");

    stream_wrapper << indent;

    EXPECT_EQ(stream_wrapper.col(), 4u);

}



TEST_F(IndentToTest_512, PutBoundaryCondition_ZeroIndent_512) {

    IndentTo indent(0);

    stream_wrapper << indent;

    EXPECT_EQ(stream_wrapper.col(), 0u);

}



TEST_F(IndentToTest_512, PutBoundaryCondition_MaxIndent_512) {

    IndentTo indent(numeric_limits<size_t>::max());

    stream_wrapper << indent;

    EXPECT_EQ(output_stream.str().size(), numeric_limits<size_t>::max() - stream_wrapper.col());

}



TEST_F(IndentToTest_512, VerifyOutputContent_512) {

    IndentTo indent(4);

    stream_wrapper << indent;

    EXPECT_EQ(output_stream.str(), "    ");

}
