#include <spdlog/spdlog.h>

#include "user.hpp"

void foo::entities::User::print() {
    spdlog::info( "PRINT DIRETO DO USER ENTITIES" );
}
