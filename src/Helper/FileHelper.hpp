#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>


#ifdef _WIN32
#include <windows.h>
#endif

void
OpenInFileExplorer(const std::filesystem::path& relativePath)
{
  std::filesystem::path absolutePath = std::filesystem::absolute(relativePath);
  if (!std::filesystem::exists(absolutePath))
  {
    throw std::runtime_error("Path does not exist: " + absolutePath.string());
  }

#ifdef _WIN32
  ShellExecuteW(nullptr,
                L"open",
                absolutePath.wstring().c_str(),
                nullptr,
                nullptr,
                SW_SHOWNORMAL);
#elif __linux__
  std::string command = "xdg-open \"" + absolutePath.string() + "\" &";
  std::system(command.c_str());
#else
#error "Platform not supported"
#endif
}
