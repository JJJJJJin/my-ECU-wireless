# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/jin/.pico-sdk/sdk/1.5.1/tools/pioasm"
  "/Users/jin/Downloads/pico_wireless/build/pioasm"
  "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm"
  "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
  "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/jin/Downloads/pico_wireless/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/PioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
