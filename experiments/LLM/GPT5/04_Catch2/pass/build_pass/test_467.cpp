// File: xmlencode_ostream_tests_467.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the provided headers
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_xmlwriter.cpp" // if your build requires including the TU

using namespace Catch;

class XmlEncodeOstreamTest_467 : public ::testing::Test {};

// Verifies that streaming an XmlEncode has the same observable effect as calling encodeTo(os)
TEST_F(XmlEncodeOstreamTest_467, StreamInsertion_DelegatesToEncodeTo_467) {
    XmlEncode xml1("abc<&>\"'");  // concrete input; we do not assert exact encoding
    std::ostringstream via_stream;
    std::ostringstream via_encode;

    // Use operator<<
    via_stream << xml1;

    // Use encodeTo directly (public API) for baseline equivalence
    xml1.encodeTo(via_encode);

    EXPECT_EQ(via_stream.str(), via_encode.str());
}

// Verifies the returned reference is the same ostream, enabling chaining
TEST_F(XmlEncodeOstreamTest_467, StreamInsertion_ReturnsSameStreamAndChains_467) {
    XmlEncode xml("x");
    std::ostringstream os;

    std::ostream& ret = (os << xml);
    // The operator must return the same stream reference
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));

    // Chaining should continue writing to the same stream
    ret << "TAIL";
    // We don't assume the exact encoding of "x"; just that "TAIL" appears after the insertion
    const std::string s = os.str();
    ASSERT_NE(s.find("TAIL"), std::string::npos);
}

// Verifies chaining multiple XmlEncode insertions is equivalent to two encodeTo calls
TEST_F(XmlEncodeOstreamTest_467, StreamInsertion_ChainsMultipleEncodes_467) {
    XmlEncode a("A&B");
    XmlEncode b("<C>");

    std::ostringstream via_stream;
    std::ostringstream via_encode;

    via_stream << a << b;

    a.encodeTo(via_encode);
    b.encodeTo(via_encode);

    EXPECT_EQ(via_stream.str(), via_encode.str());
}

// Boundary: empty input should behave consistently with encodeTo
TEST_F(XmlEncodeOstreamTest_467, StreamInsertion_EmptyInput_467) {
    XmlEncode empty("");
    std::ostringstream via_stream;
    std::ostringstream via_encode;

    via_stream << empty;
    empty.encodeTo(via_encode);

    EXPECT_EQ(via_stream.str(), via_encode.str());
}
