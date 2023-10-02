#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // support for basic file logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging

void InitLogger() {
    // Create a console sink (logs to console)
    auto console_sink = new spdlog::sinks::stdout_color_sink_mt();
    console_sink->set_level(spdlog::level::info);

    // Create a file sink (logs to a file)
    auto file_sink = new spdlog::sinks::basic_file_sink_mt("logfile.txt", true);
    file_sink->set_level(spdlog::level::trace);

    // Create a logger with both console and file sinks
    auto logger = new spdlog::logger("my_logger", spdlog::sinks_init_list{console_sink, file_sink});
    
    // Set the global logger to your custom logger
    spdlog::set_default_logger(logger);
}