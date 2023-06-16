#include "GarrysMod/Lua/Interface.h"
#include <chrono>
#include <thread>

void ultra_hard(long long sec)
{
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

LUA_FUNCTION(OneThread)
{
    LUA->CheckType(1, GarrysMod::Lua::Type::Number); // Make sure a number is the first argument

    long long number = (LUA->GetNumber(1)); // Get the first argument

    ultra_hard(number);

    LUA->PushBool(true); // Push our bool onto the stack.

    return 1; // How many values we are returning
}

LUA_FUNCTION(DoubleThread)
{
    LUA->CheckType(1, GarrysMod::Lua::Type::Number); // Make sure a number is the first argument

    long long number = (LUA->GetNumber(1)); // Get the first argument

    std::thread th(ultra_hard, number);
    th.detach();

    LUA->PushBool(true); // Push our bool onto the stack.

    return 1; // How many values we are returning
}

GMOD_MODULE_OPEN()
{
    LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB); // Push the global table
    //LUA->CreateTable();
    LUA->PushCFunction(OneThread); // Push our function
    LUA->SetField(-2, "OneThread");
    LUA->PushCFunction(DoubleThread); // Push our function
    LUA->SetField(-2, "DoubleThread");
    LUA->Pop();

    return 0;
}


GMOD_MODULE_CLOSE()
{
    return 0;
}