#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_helpers.hpp>

#include <catch2/internal/catch_reusable_string_stream.hpp>

#include <catch2/internal/catch_textflow.hpp>

#include <catch2/internal/catch_list.hpp>

#include <sstream>



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockOutputStream : public std::ostream {

public:

    MockOutputStream() : std::ostream(&buffer) {}

    virtual ~MockOutputStream() {}



    class Buffer : public std::stringbuf {

        friend class MockOutputStream;

        MOCK_METHOD(int, sync, (), (override));

    };



    Buffer buffer;



protected:

    void PrintString(const std::string& str) {

        std::cout << str;

    }

};



class TagInfoHelperTest : public ::testing::Test {

protected:

    MockOutputStream mockStream;

    std::vector<TagInfo> tags;

};



TEST_F(TagInfoHelperTest, DefaultListTags_NoTags_823) {

    defaultListTags(mockStream, tags, false);

    EXPECT_EQ(mockStream.buffer.str(), "All available tags:\n0 tag\n\n");

}



TEST_F(TagInfoHelperTest, DefaultListTags_OneTag_823) {

    TagInfo tag;

    tag.add("example_tag");

    tag.count = 1;

    tags.push_back(tag);



    defaultListTags(mockStream, tags, false);

    EXPECT_EQ(mockStream.buffer.str(), "All available tags:\n 1  example_tag\n1 tag\n\n");

}



TEST_F(TagInfoHelperTest, DefaultListTags_MultipleTags_823) {

    TagInfo tag1, tag2;

    tag1.add("tag_one");

    tag1.count = 5;

    tag2.add("tag_two");

    tag2.count = 3;



    tags.push_back(tag1);

    tags.push_back(tag2);



    defaultListTags(mockStream, tags, false);

    EXPECT_EQ(mockStream.buffer.str(), "All available tags:\n 5  tag_one\n 3  tag_two\n2 tags\n\n");

}



TEST_F(TagInfoHelperTest, DefaultListTags_Filtered_823) {

    TagInfo tag;

    tag.add("example_tag");

    tag.count = 1;

    tags.push_back(tag);



    defaultListTags(mockStream, tags, true);

    EXPECT_EQ(mockStream.buffer.str(), "Tags for matching test cases:\n 1  example_tag\n1 tag\n\n");

}



TEST_F(TagInfoHelperTest, DefaultListTags_BoundaryWidth_823) {

    TagInfo tag;

    tag.add("a_long_tag_name_that_exactly_fits_in_the_width_limitation_of_the_console_output");

    tag.count = 1;

    tags.push_back(tag);



    defaultListTags(mockStream, tags, false);

    EXPECT_EQ(mockStream.buffer.str(),

        "All available tags:\n 1  a_long_tag_name_that_exactly_fits_i\n"

        "                  n_the_width_limitation_of_\n"

        "                  the_console_output\n"

        "1 tag\n\n");

}
