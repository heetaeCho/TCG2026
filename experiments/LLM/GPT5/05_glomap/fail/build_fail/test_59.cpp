// File: run_mapper_resume_test_59.cc

#include <gtest/gtest.h>

#include <string>
#include <vector>

namespace glomap {
// Declaration of the function under test (implemented in global_mapper.cc).
int RunMapperResume(int argc, char** argv);
}  // namespace glomap

// Test fixture for RunMapperResume
class RunMapperResumeTest_59 : public ::testing::Test {
 protected:
  // Helper to build argc/argv from a vector of strings.
  void BuildArgv(const std::vector<std::string>& args,
                 int& argc,
                 std::vector<char*>& argv_storage) {
    argc = static_cast<int>(args.size());
    argv_storage.clear();
    argv_storage.reserve(args.size());
    for (const auto& s : args) {
      // const_cast is safe here because RunMapperResume should not modify the strings.
      argv_storage.push_back(const_cast<char*>(s.c_str()));
    }
  }
};

// 1) input_path 가 디렉토리가 아닌 경우: ExistsDir 실패 → EXIT_FAILURE 기대
TEST_F(RunMapperResumeTest_59, ReturnsFailureWhenInputPathIsNotDirectory_59) {
  const std::string input_path = "non_existing_dir_for_run_mapper_resume_59";
  const std::string output_path = "output_dir_59";
  const std::string output_format = "bin";

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv({ "run_mapper_resume_59",
              "--input_path", input_path,
              "--output_path", output_path,
              "--output_format", output_format },
            argc, argv);

  const int result = glomap::RunMapperResume(argc, argv.data());

  EXPECT_EQ(EXIT_FAILURE, result);
}

// 2) output_format 이 bin/txt 가 아닐 때: 유효한 디렉토리와 함께 호출 → EXIT_FAILURE 기대
//    여기서는 현재 작업 디렉토리 "." 를 유효한 디렉토리로 사용한다.
TEST_F(RunMapperResumeTest_59, ReturnsFailureWhenOutputFormatIsInvalid_59) {
  const std::string input_path = ".";  // Assume current directory exists.
  const std::string output_path = "output_dir_59";
  const std::string output_format = "invalid_format_59";

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv({ "run_mapper_resume_59",
              "--input_path", input_path,
              "--output_path", output_path,
              "--output_format", output_format },
            argc, argv);

  const int result = glomap::RunMapperResume(argc, argv.data());

  EXPECT_EQ(EXIT_FAILURE, result);
}

// 3) 정상적인 인자 (존재하는 디렉토리 + 유효한 output_format) 인 경우
//    전체 파이프라인이 실행된 뒤 EXIT_SUCCESS 를 기대한다.
//    내부 동작(재구성, 변환, Solve 호출 등)은 블랙박스로 취급한다.
TEST_F(RunMapperResumeTest_59, ReturnsSuccessWithValidArguments_59) {
  const std::string input_path = ".";  // Assume current directory exists.
  const std::string output_path = "output_dir_59";
  const std::string output_format = "bin";

  int argc = 0;
  std::vector<char*> argv;
  BuildArgv({ "run_mapper_resume_59",
              "--input_path", input_path,
              "--output_path", output_path,
              "--output_format", output_format },
            argc, argv);

  const int result = glomap::RunMapperResume(argc, argv.data());

  EXPECT_EQ(EXIT_SUCCESS, result);
}
