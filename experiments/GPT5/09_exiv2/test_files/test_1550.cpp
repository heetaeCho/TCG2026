// File: test_orfimage_printstructure_1550.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <memory>

#include "exiv2/orfimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

using ::testing::_;
using ::testing::Return;

namespace {

class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::BasicIo::Position pos), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
};

static const std::string& StaticPath() {
  static const std::string kPath = "mock.orf";
  return kPath;
}

// Helper: we only assert observable facts (exception type and output prefix).
static void ExpectThrowsExiv2Error(std::function<void()> fn) {
  try {
    fn();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error&) {
    SUCCEED();
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but got a different exception type";
  }
}

class OrfImagePrintStructureTest_1550 : public ::testing::Test {
protected:
  std::unique_ptr<Exiv2::OrfImage> MakeImageWithFailingOpen(MockBasicIo** out_io_ptr) {
    auto io = std::make_unique<testing::NiceMock<MockBasicIo>>();
    auto* raw = io.get();

    ON_CALL(*raw, open()).WillByDefault(Return(1));               // fail
    ON_CALL(*raw, path()).WillByDefault(Return(StaticPath()));
    // These are here only to keep behavior well-defined if called.
    ON_CALL(*raw, error()).WillByDefault(Return(0));
    ON_CALL(*raw, eof()).WillByDefault(Return(false));
    ON_CALL(*raw, seek(_, _)).WillByDefault(Return(0));
    ON_CALL(*raw, close()).WillByDefault(Return(0));

    if (out_io_ptr) *out_io_ptr = raw;
    return std::make_unique<Exiv2::OrfImage>(std::move(io), /*create=*/false);
  }
};

} // namespace

TEST_F(OrfImagePrintStructureTest_1550, WritesHeaderBeforeOpenFailureAndThrows_1550) {
  MockBasicIo* io_raw = nullptr;
  auto img = MakeImageWithFailingOpen(&io_raw);

  EXPECT_CALL(*io_raw, open()).Times(1);
  // On open failure, implementation throws immediately after open() check,
  // so seek() should not be required/assumed.
  EXPECT_CALL(*io_raw, seek(_, _)).Times(0);

  std::ostringstream out;
  ExpectThrowsExiv2Error([&] {
    img->printStructure(out, static_cast<Exiv2::PrintStructureOption>(0), /*depth=*/0);
  });

  EXPECT_EQ(out.str(), std::string("ORF IMAGE\n"));
}

TEST_F(OrfImagePrintStructureTest_1550, DifferentDepthStillWritesHeaderAndThrowsOnOpenFailure_1550) {
  MockBasicIo* io_raw = nullptr;
  auto img = MakeImageWithFailingOpen(&io_raw);

  EXPECT_CALL(*io_raw, open()).Times(1);

  std::ostringstream out;
  ExpectThrowsExiv2Error([&] {
    img->printStructure(out, static_cast<Exiv2::PrintStructureOption>(0), /*depth=*/123456u);
  });

  EXPECT_EQ(out.str(), std::string("ORF IMAGE\n"));
}

TEST_F(OrfImagePrintStructureTest_1550, DifferentOptionStillWritesHeaderAndThrowsOnOpenFailure_1550) {
  MockBasicIo* io_raw = nullptr;
  auto img = MakeImageWithFailingOpen(&io_raw);

  EXPECT_CALL(*io_raw, open()).Times(1);

  std::ostringstream out;
  // Use a non-zero value to exercise the option parameter without assuming enum members.
  ExpectThrowsExiv2Error([&] {
    img->printStructure(out, static_cast<Exiv2::PrintStructureOption>(1), /*depth=*/1);
  });

  EXPECT_EQ(out.str(), std::string("ORF IMAGE\n"));
}

TEST_F(OrfImagePrintStructureTest_1550, MultipleCallsEachWriteHeaderAndThrowWhenOpenFails_1550) {
  MockBasicIo* io_raw = nullptr;
  auto img = MakeImageWithFailingOpen(&io_raw);

  EXPECT_CALL(*io_raw, open()).Times(2);

  std::ostringstream out1;
  ExpectThrowsExiv2Error([&] {
    img->printStructure(out1, static_cast<Exiv2::PrintStructureOption>(0), /*depth=*/0);
  });
  EXPECT_EQ(out1.str(), std::string("ORF IMAGE\n"));

  std::ostringstream out2;
  ExpectThrowsExiv2Error([&] {
    img->printStructure(out2, static_cast<Exiv2::PrintStructureOption>(0), /*depth=*/0);
  });
  EXPECT_EQ(out2.str(), std::string("ORF IMAGE\n"));
}