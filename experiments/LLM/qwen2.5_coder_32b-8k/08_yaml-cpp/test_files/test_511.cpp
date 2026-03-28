#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include "yaml-cpp/src/indentation.h"



using namespace YAML;



class IndentationTest_511 : public ::testing::Test {

protected:

    ostream_wrapper out;

};



TEST_F(IndentationTest_511, ZeroIndentWritesNothing_511) {

    Indentation indent(0);

    std::ostringstream oss;

    ostream_wrapper streamWrapper(oss);



    streamWrapper << indent;



    EXPECT_EQ(oss.str(), "");

}



TEST_F(IndentationTest_511, NormalIndentWritesSpaces_511) {

    Indentation indent(4);

    std::ostringstream oss;

    ostream_wrapper streamWrapper(oss);



    streamWrapper << indent;



    EXPECT_EQ(oss.str(), "    ");

}



TEST_F(IndentationTest_511, LargeIndentWritesManySpaces_511) {

    Indentation indent(20);

    std::ostringstream oss;

    ostream_wrapper streamWrapper(oss);



    streamWrapper << indent;



    EXPECT_EQ(oss.str(), std::string(20, ' '));

}



TEST_F(IndentationTest_511, MaxSizeTIndentWritesSpaces_511) {

    Indentation indent(std::numeric_limits<std::size_t>::max());

    std::ostringstream oss;

    ostream_wrapper streamWrapper(oss);



    // This test might be impractical due to memory constraints, but it's valid in theory.

    // In practice, this might cause a crash or throw an exception due to excessive memory usage.

    EXPECT_THROW(streamWrapper << indent, std::exception);

}
