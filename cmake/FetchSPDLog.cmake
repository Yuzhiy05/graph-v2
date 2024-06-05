include(FetchContent)
set(FETCHCONTENT_QUIET ON)

message(STATUS "Cloning External Project: spdlog")

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.9.2
)
FetchContent_MakeAvailable(spdlog)
set(SPDLOG_SOURCE_DIR "${spdlog_SOURCE_DIR}")
set(SPDLOG_INCLUDE_DIR "${spdlog_INCLUDE_DIR}")

