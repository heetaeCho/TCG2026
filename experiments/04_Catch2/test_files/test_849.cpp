#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_test_case_info.hpp"

#include "catch_source_line_info.hpp"

#include <vector>



using namespace Catch;

using ::testing::_;

using ::testing::Invoke;



class XmlReporterTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    ReporterConfig config{oss};

    XmlReporter xmlReporter{std::move(config)};

};



TEST_F(XmlReporterTest_849, ListTestsEmptyVector_849) {

    std::vector<TestCaseHandle> tests;

    xmlReporter.listTests(tests);

}



TEST_F(XmlReporterTest_849, ListTestsSingleElement_849) {

    TestCaseInfo info{"ClassName", {"Name", "Tag1"}, SourceLineInfo{"file.cpp", 42}};

    TestCaseHandle handle{&info, nullptr};

    std::vector<TestCaseHandle> tests{handle};



    xmlReporter.listTests(tests);

}



TEST_F(XmlReporterTest_849, ListTestsMultipleElements_849) {

    TestCaseInfo info1{"ClassName1", {"Name1", "Tag1"}, SourceLineInfo{"file1.cpp", 42}};

    TestCaseInfo info2{"ClassName2", {"Name2", "Tag2"}, SourceLineInfo{"file2.cpp", 43}};



    TestCaseHandle handle1{&info1, nullptr};

    TestCaseHandle handle2{&info2, nullptr};

    std::vector<TestCaseHandle> tests{handle1, handle2};



    xmlReporter.listTests(tests);

}



TEST_F(XmlReporterTest_849, ListTestsNoClassName_849) {

    TestCaseInfo info{"", {"Name", "Tag1"}, SourceLineInfo{"file.cpp", 42}};

    TestCaseHandle handle{&info, nullptr};

    std::vector<TestCaseHandle> tests{handle};



    xmlReporter.listTests(tests);

}



TEST_F(XmlReporterTest_849, ListTestsNoTags_849) {

    TestCaseInfo info{"ClassName", {"Name", ""}, SourceLineInfo{"file.cpp", 42}};

    TestCaseHandle handle{&info, nullptr};

    std::vector<TestCaseHandle> tests{handle};



    xmlReporter.listTests(tests);

}



TEST_F(XmlReporterTest_849, ListTestsEmptyFileName_849) {

    TestCaseInfo info{"ClassName", {"Name", "Tag1"}, SourceLineInfo{"", 42}};

    TestCaseHandle handle{&info, nullptr};

    std::vector<TestCaseHandle> tests{handle};



    xmlReporter.listTests(tests);

}



TEST_F(XmlReporterTest_849, ListTestsZeroLine_849) {

    TestCaseInfo info{"ClassName", {"Name", "Tag1"}, SourceLineInfo{"file.cpp", 0}};

    TestCaseHandle handle{&info, nullptr};

    std::vector<TestCaseHandle> tests{handle};



    xmlReporter.listTests(tests);

}
