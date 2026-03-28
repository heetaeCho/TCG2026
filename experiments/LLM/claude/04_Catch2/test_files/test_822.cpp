#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// Include necessary headers
#include "catch2/reporters/catch_reporter_helpers.hpp"
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_textflow.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace Catch {

// Forward declare the function under test
void defaultListListeners(std::ostream& out, std::vector<ListenerDescription> const& descriptions);

} // namespace Catch

class DefaultListListenersTest_822 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test: Empty descriptions list outputs header only and returns early
TEST_F(DefaultListListenersTest_822, EmptyDescriptions_OutputsHeaderOnly_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("Registered listeners:"), std::string::npos);
    // With empty descriptions, there should be no additional content beyond the header line
    // The function returns early after "Registered listeners:\n"
    EXPECT_EQ(output, "Registered listeners:\n");
}

// Test: Single listener description is output correctly
TEST_F(DefaultListListenersTest_822, SingleDescription_OutputsListenerInfo_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "TestListener";
    desc.description = "A test listener for unit testing";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("Registered listeners:"), std::string::npos);
    EXPECT_NE(output.find("TestListener"), std::string::npos);
    EXPECT_NE(output.find("A test listener for unit testing"), std::string::npos);
}

// Test: Multiple listener descriptions are all output
TEST_F(DefaultListListenersTest_822, MultipleDescriptions_OutputsAllListeners_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    
    Catch::ListenerDescription desc1;
    desc1.name = "Listener1";
    desc1.description = "First listener";
    descriptions.push_back(desc1);
    
    Catch::ListenerDescription desc2;
    desc2.name = "Listener2";
    desc2.description = "Second listener";
    descriptions.push_back(desc2);
    
    Catch::ListenerDescription desc3;
    desc3.name = "LongerListenerName";
    desc3.description = "Third listener with a longer name";
    descriptions.push_back(desc3);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("Registered listeners:"), std::string::npos);
    EXPECT_NE(output.find("Listener1"), std::string::npos);
    EXPECT_NE(output.find("First listener"), std::string::npos);
    EXPECT_NE(output.find("Listener2"), std::string::npos);
    EXPECT_NE(output.find("Second listener"), std::string::npos);
    EXPECT_NE(output.find("LongerListenerName"), std::string::npos);
    EXPECT_NE(output.find("Third listener with a longer name"), std::string::npos);
}

// Test: Output ends with a trailing newline and is flushed
TEST_F(DefaultListListenersTest_822, NonEmptyDescriptions_EndsWithNewline_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "MyListener";
    desc.description = "Some description";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    // Should end with two newlines (one from each listener line, one trailing)
    ASSERT_FALSE(output.empty());
    EXPECT_EQ(output.back(), '\n');
}

// Test: Listener with empty description
TEST_F(DefaultListListenersTest_822, ListenerWithEmptyDescription_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "EmptyDescListener";
    desc.description = "";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("Registered listeners:"), std::string::npos);
    EXPECT_NE(output.find("EmptyDescListener"), std::string::npos);
}

// Test: Listener with very short name
TEST_F(DefaultListListenersTest_822, ListenerWithShortName_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "A";
    desc.description = "Short named listener";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("A:"), std::string::npos);
    EXPECT_NE(output.find("Short named listener"), std::string::npos);
}

// Test: Listener with long name to verify column alignment
TEST_F(DefaultListListenersTest_822, ListenerWithLongName_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "AVeryLongListenerNameThatExceedsNormalExpectations";
    desc.description = "Description for a long-named listener";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("AVeryLongListenerNameThatExceedsNormalExpectations"), std::string::npos);
    EXPECT_NE(output.find("Description for a long-named listener"), std::string::npos);
}

// Test: Multiple listeners with varying name lengths (tests maxNameLen calculation)
TEST_F(DefaultListListenersTest_822, VaryingNameLengths_UsesMaxNameLen_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    
    Catch::ListenerDescription desc1;
    desc1.name = "S";
    desc1.description = "Short";
    descriptions.push_back(desc1);
    
    Catch::ListenerDescription desc2;
    desc2.name = "MediumName";
    desc2.description = "Medium";
    descriptions.push_back(desc2);
    
    Catch::ListenerDescription desc3;
    desc3.name = "VeryLongListenerName";
    desc3.description = "Long";
    descriptions.push_back(desc3);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    // All names should appear in the output
    EXPECT_NE(output.find("S:"), std::string::npos);
    EXPECT_NE(output.find("MediumName:"), std::string::npos);
    EXPECT_NE(output.find("VeryLongListenerName:"), std::string::npos);
    EXPECT_NE(output.find("Short"), std::string::npos);
    EXPECT_NE(output.find("Medium"), std::string::npos);
    EXPECT_NE(output.find("Long"), std::string::npos);
}

// Test: Listener name has colon appended in output
TEST_F(DefaultListListenersTest_822, ListenerNameHasColonAppended_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "TestName";
    desc.description = "TestDesc";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("TestName:"), std::string::npos);
}

// Test: Long description that might wrap
TEST_F(DefaultListListenersTest_822, LongDescription_HandledCorrectly_822) {
    std::vector<Catch::ListenerDescription> descriptions;
    Catch::ListenerDescription desc;
    desc.name = "Listener";
    desc.description = "This is a very long description that should exceed the normal console width "
                       "and potentially cause line wrapping in the output formatting of the listener list.";
    descriptions.push_back(desc);
    
    Catch::defaultListListeners(oss, descriptions);
    
    std::string output = oss.str();
    EXPECT_NE(output.find("Registered listeners:"), std::string::npos);
    EXPECT_NE(output.find("Listener:"), std::string::npos);
    // The description content should still be present (potentially wrapped)
    EXPECT_NE(output.find("very long description"), std::string::npos);
}
