workspace "fooplot"
  configurations { "Release", "Debug" }

project "fooplot"
   kind "ConsoleApp"

   language "C++"
   targetdir "/usr/local/bin/"

   files { "src/*.cpp", "src/*.h" }

   filter "configurations:Release"
      buildoptions { "-std=c++11" }
      defines { "NDEBUG" }
      optimize "On"
      postbuildcommands { "rm -rf obj/" }

   filter "configurations:Debug"
      buildoptions { "-std=c++11", "-pedantic" }
      defines { "DEBUG" }
      symbols "On"
      postbuildcommands { "rm -rf obj/" }
