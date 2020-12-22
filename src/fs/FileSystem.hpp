#pragma once

 #ifndef __has_include
   static_assert(false, "__has_include not supported");
 #else
 #  if __has_include(<filesystem>)
 #    include <filesystem>
      namespace fs = std::filesystem;
 #  elif __has_include(<experimental/filesystem>)
 #    include <experimental/filesystem>
      namespace fs = std::experimental::filesystem;
 #  endif
 #endif

