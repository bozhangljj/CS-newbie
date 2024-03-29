cmake_minimum_required(VERSION 3.14)
set(CMAKE_OSX_DEPLOYMENT_TARGET "13.0" CACHE STRING "Minimum OS X deployment version")

if(NOT DEFINED URL_BASE)
    set(URL_BASE "github.com")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(VERSION "3.3.0")
set(VERSION_SUFFIX "")
include(Options)
configure_project()

# vcpkg init
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    find_package(Git REQUIRED)
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- vcpkg WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(FISCO-BCOS VERSION ${VERSION})

include(CompilerSettings)
include(BuildInfoGenerator)

include(IncludeDirectories)
include(TargetSettings)

add_subdirectory(bcos-boostssl)
add_subdirectory(bcos-framework)
add_subdirectory(bcos-crypto)
add_subdirectory(bcos-utilities)

if(WITH_LIGHTNODE)
    add_subdirectory(lightnode)
endif()

if(FULLNODE)
    if(WITH_WASM)
        include(ProjectWABT)
        include(ProjectBCOSWASM)
    endif()
    include(ProjectGroupSig)
    include(ProjectSDF)
    include(ProjectITTAPI)

    add_subdirectory(bcos-codec)
    add_subdirectory(bcos-sealer)
    add_subdirectory(bcos-security)
    add_subdirectory(bcos-table)
    add_subdirectory(bcos-tool)
    add_subdirectory(bcos-scheduler)
    add_subdirectory(bcos-executor)
    add_subdirectory(bcos-storage)
    add_subdirectory(bcos-ledger)
    add_subdirectory(bcos-protocol)
    add_subdirectory(bcos-tars-protocol)
    add_subdirectory(bcos-rpc)
    add_subdirectory(bcos-gateway)
    add_subdirectory(bcos-pbft)
    add_subdirectory(bcos-txpool)
    add_subdirectory(bcos-sync)
    add_subdirectory(bcos-front)
    add_subdirectory(bcos-leader-election)
    add_subdirectory(libinitializer)
    add_subdirectory(fisco-bcos-air)
    add_subdirectory(concepts)
    add_subdirectory(libtask)

    add_subdirectory(transaction-executor)

    if(WITH_TARS_SERVICES)
        add_subdirectory(fisco-bcos-tars-service)
    endif()

    if(TESTS)
        enable_testing()
        add_subdirectory(tests)
        add_subdirectory(benchmark)
    endif()
endif()

if(WITH_CPPSDK)
    add_subdirectory(bcos-sdk)
endif()

if(TOOLS)
  add_subdirectory(tools)
endif()

# for code coverage
if(COVERAGE)
    include(Coverage)
    config_coverage("coverage" "'/usr*' 'boost/*'")
endif()

print_config("FISCO BCOS")

include(CMakePackageConfigHelpers)
configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/cmake/fiscobcos-config.cmake.in"
  "${CMAKE_BINARY_DIR}/fiscobcos-config.cmake"
  INSTALL_DESTINATION "share/fiscobcos"
)

install(
  FILES "${CMAKE_BINARY_DIR}/fiscobcos-config.cmake"
  DESTINATION "share/fiscobcos"
)

install(
    EXPORT fiscobcosTargets
    DESTINATION share/fiscobcos
    NAMESPACE fiscobcos::
)