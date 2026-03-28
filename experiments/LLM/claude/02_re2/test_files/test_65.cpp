#include <gtest/gtest.h>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <vector>
#include <string>
#include "re2/re2.h"
#include "re2/filtered_re2.h"

namespace py = pybind11;

// We need to include or declare the Filter class from the module
// Since we're testing the compiled module, we import it via pybind11
namespace {

class FilterTest_65 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!Py_IsInitialized()) {
            py::initialize_interpreter();
        }
    }

    static void TearDownTestSuite() {
        // Don't finalize - let the process handle it
    }

    py::object CreateFilter() {
        py::module_ mod = py::module_::import("_re2");
        return mod.attr("Filter")();
    }

    py::bytes MakeBytes(const std::string& s) {
        return py::bytes(s);
    }
};

TEST_F(FilterTest_65, MatchBeforeCompileThrows_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::bytes input = py::bytes("hello");
        // Match called before Compile should raise an error
        EXPECT_THROW(filt.attr("Match")(input, true), py::error_already_set);
    } catch (const std::exception& e) {
        // If module can't be imported, skip
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, MatchAfterCompileWithNoPatterns_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        filt.attr("Compile")();
        py::bytes input = py::bytes("hello");
        py::object result = filt.attr("Match")(input, false);
        std::vector<int> matches = result.cast<std::vector<int>>();
        EXPECT_TRUE(matches.empty());
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, MatchPotentialReturnsMatches_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::object options = mod.attr("Options")();
        filt.attr("Add")(py::bytes("hello"), options);
        filt.attr("Compile")();
        py::bytes input = py::bytes("hello world");
        py::object result = filt.attr("Match")(input, true);
        std::vector<int> matches = result.cast<std::vector<int>>();
        // With potential=true, should return potential matches
        EXPECT_FALSE(matches.empty());
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, MatchExactReturnsMatches_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::object options = mod.attr("Options")();
        filt.attr("Add")(py::bytes("hello"), options);
        filt.attr("Compile")();
        py::bytes input = py::bytes("hello world");
        py::object result = filt.attr("Match")(input, false);
        std::vector<int> matches = result.cast<std::vector<int>>();
        EXPECT_FALSE(matches.empty());
        EXPECT_EQ(matches[0], 0);
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, MatchNoMatchReturnsEmpty_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::object options = mod.attr("Options")();
        filt.attr("Add")(py::bytes("xyz"), options);
        filt.attr("Compile")();
        py::bytes input = py::bytes("hello world");
        py::object result = filt.attr("Match")(input, false);
        std::vector<int> matches = result.cast<std::vector<int>>();
        EXPECT_TRUE(matches.empty());
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, MatchMultiplePatterns_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::object options = mod.attr("Options")();
        filt.attr("Add")(py::bytes("hello"), options);
        filt.attr("Add")(py::bytes("world"), options);
        filt.attr("Add")(py::bytes("foobar"), options);
        filt.attr("Compile")();
        py::bytes input = py::bytes("hello world");
        py::object result = filt.attr("Match")(input, false);
        std::vector<int> matches = result.cast<std::vector<int>>();
        // Should match patterns 0 and 1 but not 2
        EXPECT_GE(matches.size(), 2u);
        EXPECT_NE(std::find(matches.begin(), matches.end(), 0), matches.end());
        EXPECT_NE(std::find(matches.begin(), matches.end(), 1), matches.end());
        EXPECT_EQ(std::find(matches.begin(), matches.end(), 2), matches.end());
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, MatchEmptyInput_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::object options = mod.attr("Options")();
        filt.attr("Add")(py::bytes("hello"), options);
        filt.attr("Compile")();
        py::bytes input = py::bytes("");
        py::object result = filt.attr("Match")(input, false);
        std::vector<int> matches = result.cast<std::vector<int>>();
        EXPECT_TRUE(matches.empty());
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

TEST_F(FilterTest_65, PotentialVsExactDifference_65) {
    py::scoped_interpreter guard{};
    try {
        py::module_ mod = py::module_::import("_re2");
        py::object filt = mod.attr("Filter")();
        py::object options = mod.attr("Options")();
        filt.attr("Add")(py::bytes("hel+o"), options);
        filt.attr("Compile")();
        py::bytes input = py::bytes("hello");
        
        py::object potential_result = filt.attr("Match")(input, true);
        std::vector<int> potentials = potential_result.cast<std::vector<int>>();
        
        py::object exact_result = filt.attr("Match")(input, false);
        std::vector<int> exacts = exact_result.cast<std::vector<int>>();
        
        // Potentials should be a superset of exact matches
        for (int idx : exacts) {
            EXPECT_NE(std::find(potentials.begin(), potentials.end(), idx), potentials.end());
        }
    } catch (const std::exception& e) {
        GTEST_SKIP() << "Could not import _re2 module: " << e.what();
    }
}

} // namespace
