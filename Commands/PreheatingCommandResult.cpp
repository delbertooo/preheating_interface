#include "PreheatingCommandResult.hpp"
#include <cstddef>

PreheatingCommandResult::PreheatingCommandResult(const char* message) : message(message) { }
bool PreheatingCommandResult::IsError() { return message != NULL; }
const char* PreheatingCommandResult::ErrorMessage() { return message; }
