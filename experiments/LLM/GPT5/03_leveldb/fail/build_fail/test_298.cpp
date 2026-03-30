// File: sanitize_options_test.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/env.h"
#include "db/dbformat.h"  // For InternalKeyComparator / InternalFilterPolicy
// db_impl.cc declares/defines SanitizeOptions in namespace leveldb
// and kNumNonTableCacheFiles as a global. We forward-declare here to avoid
// including private .cc directly in tests.
namespace leveldb {
Options SanitizeOptions(const std::string& dbname,
                        const InternalKeyComparator* icmp,
                        const InternalFilterPolicy* ipolicy,
                        const Options& src);
extern const int kNumNonTableCacheFiles;
}  // namespace leveldb

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrictMock;

namespace {

// Minimal test doubles for comparator/filter policy inputs.
// We pass BytewiseComparator() into InternalKeyComparator as its user comparator.
class DummyFilterPolicy : public leveldb::FilterPolicy {
 public:
  const char* Name() const override { return "dummy"; }
  void CreateFilter(const leveldb::Slice*, int, std::string*) const override {}
  bool KeyMayMatch(const leveldb::Slice&, const leveldb::Slice&) const override { return true; }
};

// Strict mock for Env to verify external interactions when info_log is null.
class MockEnv : public leveldb::Env {
 public:
  MOCK_METHOD(leveldb::Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(leveldb::Status, RenameFile,
              (const std::string& src, const std::string& target), (override));
  MOCK_METHOD(leveldb::Status, NewLogger,
              (const std::string& fname, leveldb::Logger** result), (override));
};

class SanitizeOptionsTest_298 : public ::testing::Test {
 protected:
  // Helpers to make src Options with our mock env
  leveldb::Options BaseSrcWith(StrictMock<MockEnv>* env) {
    leveldb::Options src;
    src.env = env;  // ensure calls go to our mock
    return src;
  }
};

}  // namespace

// 298: Comparator is replaced and filter policy is conditionally substituted.
TEST_F(SanitizeOptionsTest_298, ComparatorAndFilterPolicySelection_298) {
  StrictMock<MockEnv> env;  // No calls expected in this test
  leveldb::Options src = BaseSrcWith(&env);

  // Prepare inputs
  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  // Case A: src.filter_policy == nullptr -> result.filter_policy must be nullptr
  src.filter_policy = nullptr;
  auto a = leveldb::SanitizeOptions("dbA", &ikc, &ifp, src);
  EXPECT_EQ(a.comparator, &ikc);
  EXPECT_EQ(a.filter_policy, nullptr);

  // Case B: src.filter_policy != nullptr -> result.filter_policy must be ipolicy
  src.filter_policy = &user_fp;  // non-null in src
  auto b = leveldb::SanitizeOptions("dbB", &ikc, &ifp, src);
  EXPECT_EQ(b.comparator, &ikc);
  EXPECT_EQ(b.filter_policy, &ifp);
}

// 298: Numeric fields are clipped to documented ranges (low-end).
TEST_F(SanitizeOptionsTest_298, ClipsNumericOptionsLow_298) {
  StrictMock<MockEnv> env;  // No info_log work in this test
  leveldb::Options src = BaseSrcWith(&env);

  // Force obviously too-small values
  src.max_open_files = 0;
  src.write_buffer_size = 1;   // bytes
  src.max_file_size = 1;       // bytes
  src.block_size = 1;          // bytes

  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  auto r = leveldb::SanitizeOptions("db", &ikc, &ifp, src);

  const int min_max_open_files = 64 + leveldb::kNumNonTableCacheFiles;  // from code under test
  EXPECT_GE(r.max_open_files, min_max_open_files);
  EXPECT_GE(r.write_buffer_size, static_cast<size_t>(64 << 10));
  EXPECT_GE(r.max_file_size, static_cast<size_t>(1 << 20));
  EXPECT_GE(r.block_size, static_cast<size_t>(1 << 10));
}

// 298: Numeric fields are clipped to documented ranges (high-end).
TEST_F(SanitizeOptionsTest_298, ClipsNumericOptionsHigh_298) {
  StrictMock<MockEnv> env;  // No info_log work in this test
  leveldb::Options src = BaseSrcWith(&env);

  // Force obviously too-large values
  src.max_open_files = 1'000'000;
  src.write_buffer_size = (1ull << 40);
  src.max_file_size = (1ull << 40);
  src.block_size = (1ull << 40);

  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  auto r = leveldb::SanitizeOptions("db", &ikc, &ifp, src);

  EXPECT_LE(r.max_open_files, 50000);
  EXPECT_LE(r.write_buffer_size, static_cast<size_t>(1ull << 30));
  EXPECT_LE(r.max_file_size, static_cast<size_t>(1ull << 30));
  EXPECT_LE(r.block_size, static_cast<size_t>(4ull << 20));
}

// 298: When src.info_log is nullptr, Env interactions occur and a logger is installed if creation succeeds.
TEST_F(SanitizeOptionsTest_298, CreatesInfoLogOnNullAndKeepsOnSuccess_298) {
  StrictMock<MockEnv> env;
  leveldb::Options src = BaseSrcWith(&env);
  src.info_log = nullptr;  // trigger path that uses Env

  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  // Provide a non-null logger pointer via out-param
  auto* fake_logger = reinterpret_cast<leveldb::Logger*>(0x1);

  EXPECT_CALL(env, CreateDir(_)).WillOnce(Return(leveldb::Status::OK()));
  EXPECT_CALL(env, RenameFile(_, _)).WillOnce(Return(leveldb::Status::OK()));
  EXPECT_CALL(env, NewLogger(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(fake_logger), Return(leveldb::Status::OK())));

  auto r = leveldb::SanitizeOptions("dbLogOK", &ikc, &ifp, src);
  EXPECT_EQ(r.info_log, fake_logger);
}

// 298: If logger creation fails, result.info_log stays nullptr (but directory/rename are still attempted).
TEST_F(SanitizeOptionsTest_298, LeavesInfoLogNullOnLoggerCreationFailure_298) {
  StrictMock<MockEnv> env;
  leveldb::Options src = BaseSrcWith(&env);
  src.info_log = nullptr;

  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  EXPECT_CALL(env, CreateDir(_)).WillOnce(Return(leveldb::Status::OK()));
  EXPECT_CALL(env, RenameFile(_, _)).WillOnce(Return(leveldb::Status::OK()));
  EXPECT_CALL(env, NewLogger(_, _))
      .WillOnce(Return(leveldb::Status::IOError("fail")));  // non-OK

  auto r = leveldb::SanitizeOptions("dbLogFail", &ikc, &ifp, src);
  EXPECT_EQ(r.info_log, nullptr);
}

// 298: If src.info_log is already set, no Env interactions occur and the pointer is preserved.
TEST_F(SanitizeOptionsTest_298, DoesNotTouchEnvWhenInfoLogAlreadyPresent_298) {
  StrictMock<MockEnv> env;  // strict: any unexpected call fails the test
  leveldb::Options src = BaseSrcWith(&env);

  auto* existing_logger = reinterpret_cast<leveldb::Logger*>(0x2);
  src.info_log = existing_logger;  // pre-set

  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  auto r = leveldb::SanitizeOptions("dbNoTouch", &ikc, &ifp, src);
  EXPECT_EQ(r.info_log, existing_logger);
}

// 298: block_cache is created when nullptr; preserved when non-null.
TEST_F(SanitizeOptionsTest_298, BlockCacheDefaultAndPreserve_298) {
  StrictMock<MockEnv> env;  // no Env interactions required for block_cache
  leveldb::Options srcA = BaseSrcWith(&env);
  srcA.block_cache = nullptr;

  leveldb::InternalKeyComparator ikc(leveldb::BytewiseComparator());
  DummyFilterPolicy user_fp;
  leveldb::InternalFilterPolicy ifp(&user_fp);

  auto a = leveldb::SanitizeOptions("dbCacheA", &ikc, &ifp, srcA);
  EXPECT_NE(a.block_cache, nullptr);  // default cache created

  leveldb::Options srcB = BaseSrcWith(&env);
  auto* existing_cache = reinterpret_cast<leveldb::Cache*>(0x3);
  srcB.block_cache = existing_cache;

  auto b = leveldb::SanitizeOptions("dbCacheB", &ikc, &ifp, srcB);
  EXPECT_EQ(b.block_cache, existing_cache);  // preserved
}
