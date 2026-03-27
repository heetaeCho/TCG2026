#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_xml.hpp"

#include "catch_list.hpp"

#include "catch_xmlwriter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::InSequence;



class XmlReporterTest_850 : public ::testing::Test {

protected:

    std::ostringstream os;

    XmlWriter mockXmlWriter{os};

    XmlReporter reporter{{}, mockXmlWriter};



    void SetUp() override {

        // Reset the output stream before each test

        os.str("");

        os.clear();

    }

};



TEST_F(XmlReporterTest_850, ListTags_EmptyList_NoOutput_850) {

    std::vector<TagInfo> tags;

    reporter.listTags(tags);

    EXPECT_EQ(os.str(), "");

}



TEST_F(XmlReporterTest_850, ListTags_SingleTagWithAlias_OutputSingleTagAndAlias_850) {

    std::vector<TagInfo> tags = {{"[tag1]", 1}, {"alias1"}};

    reporter.listTags(tags);

    EXPECT_EQ(os.str(), "<TagsFromMatchingTests><Tag><Count Indent=\"yes\">1</Count><Aliases><Alias Indent=\"yes\">alias1</Alias></Aliases></Tag></TagsFromMatchingTests>");

}



TEST_F(XmlReporterTest_850, ListTags_MultipleTags_OutputMultipleTagsAndAliases_850) {

    std::vector<TagInfo> tags = {{"[tag1]", 2}, {"alias1", "alias2"},

                                 {"[tag2]", 3}, {"alias3"}};

    reporter.listTags(tags);

    EXPECT_EQ(os.str(), "<TagsFromMatchingTests><Tag><Count Indent=\"yes\">2</Count><Aliases><Alias Indent=\"yes\">alias1</Alias><Alias Indent=\"yes\">alias2</Alias></Aliases></Tag><Tag><Count Indent=\"yes\">3</Count><Aliases><Alias Indent=\"yes\">alias3</Alias></Aliases></Tag></TagsFromMatchingTests>");

}



TEST_F(XmlReporterTest_850, ListTags_TagWithMultipleAliases_OutputSingleTagAndMultipleAliases_850) {

    std::vector<TagInfo> tags = {{"[tag1]", 1}, {"alias1", "alias2", "alias3"}};

    reporter.listTags(tags);

    EXPECT_EQ(os.str(), "<TagsFromMatchingTests><Tag><Count Indent=\"yes\">1</Count><Aliases><Alias Indent=\"yes\">alias1</Alias><Alias Indent=\"yes\">alias2</Alias><Alias Indent=\"yes\">alias3</Alias></Aliases></Tag></TagsFromMatchingTests>");

}



TEST_F(XmlReporterTest_850, ListTags_BoundaryCondition_SingleCharacterTagAndAlias_850) {

    std::vector<TagInfo> tags = {{"[a]", 1}, {"b"}};

    reporter.listTags(tags);

    EXPECT_EQ(os.str(), "<TagsFromMatchingTests><Tag><Count Indent=\"yes\">1</Count><Aliases><Alias Indent=\"yes\">b</Alias></Aliases></Tag></TagsFromMatchingTests>");

}



TEST_F(XmlReporterTest_850, ListTags_BoundaryCondition_EmptyAliasList_850) {

    std::vector<TagInfo> tags = {{"[tag1]", 1}};

    reporter.listTags(tags);

    EXPECT_EQ(os.str(), "<TagsFromMatchingTests><Tag><Count Indent=\"yes\">1</Count><Aliases></Aliases></Tag></TagsFromMatchingTests>");

}
