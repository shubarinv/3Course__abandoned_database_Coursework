#include "select_server_ui.hpp"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

void initLog()
{
    // create color multi threaded logger
    auto console    = spdlog::stdout_color_mt("console");
    auto err_logger = spdlog::stderr_color_mt("stderr");
}

int main()
{
    initLog();
    spdlog::info("Program started");
    return 0;
}
