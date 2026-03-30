#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_xmlwriter.hpp"

#include "catch_stringref.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;

using ::testing::InSequence;



class XmlReporterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    XmlWriter mockXmlWriter{oss};

    XmlReporter reporter{{mockXmlWriter}};

};



TEST_F(XmlReporterTest_846, BenchmarkFailed_EmptyErrorString_846) {

    StringRef emptyError{};

    reporter.benchmarkFailed(emptyError);

    EXPECT_EQ(oss.str(), "<failed message=\"\"></failed>");

}



TEST_F(XmlReporterTest_846, BenchmarkFailed_NonEmptyErrorString_846) {

    StringRef nonEmptyError{"Test error"};

    reporter.benchmarkFailed(nonEmptyError);

    EXPECT_EQ(oss.str(), "<failed message=\"Test error\"></failed>");

}



TEST_F(XmlReporterTest_846, BenchmarkFailed_SpecialCharactersInErrorString_846) {

    StringRef specialCharsError{"<>&\"\'"};

    reporter.benchmarkFailed(specialCharsError);

    EXPECT_EQ(oss.str(), "<failed message=\"&lt;&gt;&amp;\\\"'\"></failed>");

}



TEST_F(XmlReporterTest_846, BenchmarkFailed_UnicodeCharactersInErrorString_846) {

    StringRef unicodeError{"😊"};

    reporter.benchmarkFailed(unicodeError);

    EXPECT_EQ(oss.str(), "<failed message=\"😊\"></failed>");

}
