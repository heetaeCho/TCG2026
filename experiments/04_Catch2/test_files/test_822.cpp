#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "./TestProjects/Catch2/src/catch2/reporters/catch_reporter_helpers.cpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_list.hpp"



using namespace Catch;



TEST(defaultListListeners_822, EmptyDescriptions_822) {

    std::ostringstream out;

    std::vector<ListenerDescription> descriptions;

    defaultListListeners(out, descriptions);

    EXPECT_EQ("Registered listeners:\n\n", out.str());

}



TEST(defaultListListeners_822, SingleDescription_822) {

    std::ostringstream out;

    ListenerDescription desc1;

    desc1.name = "Console";

    desc1.description = "Reports test results to console.";

    std::vector<ListenerDescription> descriptions = {desc1};

    defaultListListeners(out, descriptions);

    EXPECT_EQ("Registered listeners:\n"

              "  Console:           Reports test results to console.\n\n", out.str());

}



TEST(defaultListListeners_822, MultipleDescriptions_822) {

    std::ostringstream out;

    ListenerDescription desc1, desc2;

    desc1.name = "Console";

    desc1.description = "Reports test results to console.";

    desc2.name = "JunitReporter";

    desc2.description = "Generates JUnit-style XML reports.";

    std::vector<ListenerDescription> descriptions = {desc1, desc2};

    defaultListListeners(out, descriptions);

    EXPECT_EQ("Registered listeners:\n"

              "  Console:           Reports test results to console.\n"

              "  JunitReporter:     Generates JUnit-style XML reports.\n\n", out.str());

}



TEST(defaultListListeners_822, LongerNameDescription_822) {

    std::ostringstream out;

    ListenerDescription desc1, desc2;

    desc1.name = "VeryLongListenerName";

    desc1.description = "A very long description that should still fit within the console width.";

    desc2.name = "ShortName";

    desc2.description = "Short description.";

    std::vector<ListenerDescription> descriptions = {desc1, desc2};

    defaultListListeners(out, descriptions);

    EXPECT_EQ("Registered listeners:\n"

              "  VeryLongListenerN: A very long description that should still fit\n"

              "                     within the console width.\n"

              "  ShortName:         Short description.\n\n", out.str());

}
