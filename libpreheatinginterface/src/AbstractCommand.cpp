#include "LibPreheatingInterface.hpp"

LibPreheatingInterface::AbstractCommand::AbstractCommand(CommandHelper &helper)
    : remote(helper.remote), helper(helper) {}
