#include "PreheatingCommandResult.hpp"
#include <cstddef>

Commands::PreheatingCommandResult::PreheatingCommandResult(const char* message) : message(message) { }
bool Commands::PreheatingCommandResult::IsError() { return message != NULL; }
const char* Commands::PreheatingCommandResult::ErrorMessage() { return message; }


