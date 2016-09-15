#pragma once

#include <string>

struct Device {
  std::string family;
};

struct Agent : Device {
  std::string major;
  std::string minor;
  std::string patch;

  std::string toString() const {
    return family + " " + toVersionString();
  }

  std::string toVersionString() const {
    return (major.empty() ? "0" : major) + "." +
      (minor.empty() ? "0" : minor) + "." +
      (patch.empty() ? "0" : patch);
  }
  std::string toVersionString2() const {
    if (! major.empty() && ! minor.empty() && ! patch.empty())
      return major + "." + minor + "." + patch;
    else if (! major.empty() && ! minor.empty() )
      return major + "." + minor;
    else if  (! major.empty() )
      return major;
    else return "";
  }
};

typedef Agent Os;
typedef Agent Browser;
typedef Agent Vendor;

struct UserAgent {
  Device device;
  Device deviceType;
  Vendor vendor;

  Os os;
  Browser browser;

  std::string toFullString() const {
    return browser.toString() + "/" + os.toString();
  }

  bool isSpider() const {
    return device.family == "Spider";
  }
};

class UserAgentParser {
 public:
  explicit UserAgentParser(const std::string& regexes_file_path);

  UserAgent parse(const std::string&) const;

  ~UserAgentParser();

 private:
  const std::string regexes_file_path_;
  const void* ua_store_;
};
