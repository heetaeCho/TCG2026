// HtmlPage_AddLink_test_2703.cpp
#include <gtest/gtest.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <memory>
#include <string>
#include <vector>

#include "HtmlOutputDev.h"
#include "HtmlLinks.h"
#include "GooString.h"

namespace {

class HtmlPageAddLinkTest_2703 : public ::testing::Test {
protected:
  static std::string DumpPageToString(HtmlPage &page, int pageNum = 1)
  {
    // Create a temporary file path (portable enough for typical CI on Linux/macOS).
    // If your environment lacks mkstemp, replace with your project's temp helper.
    char path[] = "/tmp/htmlpage_addlink_2703_XXXXXX";
    int fd = mkstemp(path);
    if (fd < 0) {
      return {};
    }

    FILE *f = fdopen(fd, "wb+");
    if (!f) {
      close(fd);
      remove(path);
      return {};
    }

    std::vector<std::string> backgroundImages;
    page.dump(f, pageNum, backgroundImages);

    fflush(f);
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) {
      fclose(f);
      remove(path);
      return {};
    }
    fseek(f, 0, SEEK_SET);

    std::string out;
    out.resize(static_cast<size_t>(sz));
    if (sz > 0) {
      size_t n = fread(&out[0], 1, static_cast<size_t>(sz), f);
      out.resize(n);
    }

    fclose(f);
    remove(path);
    return out;
  }

  static HtmlLink MakeLink(double x1, double y1, double x2, double y2, const char *dest)
  {
    std::unique_ptr<GooString> gs;
    if (dest) {
      gs = std::make_unique<GooString>(dest);
    }
    return HtmlLink(x1, y1, x2, y2, std::move(gs));
  }
};

} // namespace

TEST_F(HtmlPageAddLinkTest_2703, AddSingleLinkDoesNotCrash_2703)
{
  HtmlPage page(/*rawOrder=*/false);
  HtmlLink link = MakeLink(1.0, 2.0, 3.0, 4.0, "Dest2703");

  // Observable behavior: should be callable without crashes/exceptions.
  page.AddLink(link);
  SUCCEED();
}

TEST_F(HtmlPageAddLinkTest_2703, AddLinkWithNullDestinationDoesNotCrash_2703)
{
  HtmlPage page(/*rawOrder=*/true);
  HtmlLink link = MakeLink(10.0, 20.0, 30.0, 40.0, nullptr);

  page.AddLink(link);
  SUCCEED();
}

TEST_F(HtmlPageAddLinkTest_2703, AddMultipleLinksThenDumpProducesSomeOutput_2703)
{
  HtmlPage page(/*rawOrder=*/false);

  page.AddLink(MakeLink(0.0, 0.0, 1.0, 1.0, "A2703"));
  page.AddLink(MakeLink(1.0, 1.0, 2.0, 2.0, "B2703"));
  page.AddLink(MakeLink(2.0, 2.0, 3.0, 3.0, "C2703"));

  const std::string dumped = DumpPageToString(page, /*pageNum=*/1);

  // We don't assume exact HTML format; just that dumping works and yields data.
  EXPECT_FALSE(dumped.empty());
}

TEST_F(HtmlPageAddLinkTest_2703, AddLinkMayAffectDumpOutput_2703)
{
  HtmlPage baseline(/*rawOrder=*/false);
  const std::string baseDump = DumpPageToString(baseline, /*pageNum=*/1);

  HtmlPage withLink(/*rawOrder=*/false);
  withLink.AddLink(MakeLink(5.0, 6.0, 7.0, 8.0, "Dest2703"));
  const std::string linkDump = DumpPageToString(withLink, /*pageNum=*/1);

  // Black-box observable check:
  // Either the dump becomes larger OR the destination string appears OR content differs.
  // (We avoid assuming a specific HTML representation.)
  const bool destMentioned = (linkDump.find("Dest2703") != std::string::npos);
  const bool grew = (linkDump.size() > baseDump.size());
  const bool changed = (linkDump != baseDump);

  EXPECT_TRUE(destMentioned || grew || changed);
}