// File: ./TestProjects/yaml-cpp/util/read_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <istream>

// The implementation snippet shows `run` as a free function in util/read.cpp.
// Include the real header if it exists in your project; otherwise, this forward
// declaration matches the provided signature.
void run(std::istream& in);

#include <yaml-cpp/exceptions.h>

class RunTest_673 : public ::testing::Test {};

// Normal operation: valid YAML should not throw.
TEST_F(RunTest_673, ValidSingleDocumentDoesNotThrow_673) {
  std::stringstream ss;
  ss << "a: 1\nb: 2\n";

  EXPECT_NO_THROW(run(ss));
}

// Boundary: empty input stream should be handled gracefully (no observable error).
TEST_F(RunTest_673, EmptyStreamDoesNotThrow_673) {
  std::stringstream ss;

  EXPECT_NO_THROW(run(ss));
}

// Boundary + observable behavior: run() calls HandleNextDocument once.
// Using an explicit document end (`...`) ensures the first document is complete.
// If only the first document is handled, the invalid second document should not
// affect the first run, but should be observed on a second run using the same stream.
TEST_F(RunTest_673, HandlesOnlyNextDocumentSecondRunSeesNextDoc_673) {
  std::stringstream ss;
  ss << "---\n"
        "a: 1\n"
        "...\n"
        "---\n"
        "a: [\n";  // invalid YAML (unterminated sequence)

  EXPECT_NO_THROW(run(ss));                         // first document only
  EXPECT_THROW(run(ss), YAML::Exception);           // now the invalid second doc is encountered
}

// Exceptional/error case: invalid YAML in the first document should throw.
TEST_F(RunTest_673, InvalidYamlThrows_673) {
  std::stringstream ss;
  ss << "a: [\n";  // invalid YAML

  EXPECT_THROW(run(ss), YAML::Exception);
}