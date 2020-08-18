//-----------------------------------------------------------------------------
// z80asm restart
// Copyright (C) Paulo Custodio, 2011-2020
// License: The Artistic License 2.0, http://www.perlfoundation.org/artistic_license_2_0
//-----------------------------------------------------------------------------

#include "legacy.h"

#include "App.h"

#include "ghc/filesystem.hpp"
namespace fs = ghc::filesystem;		// util we have std::filesystem

#include <unordered_set>

static std::string envPendingOptions;

const char* CPU_Z80_NAME = "z80";
const char* CPU_Z80N_NAME = "z80n";
const char* CPU_Z180_NAME = "z180";
const char* CPU_R2K_NAME = "r2k";
const char* CPU_R3K_NAME = "r3k";
const char* CPU_8080_NAME = "8080";
const char* CPU_8085_NAME = "8085";
const char* CPU_GBZ80_NAME = "gbz80";

const char* CPU_Z80_DEFINE = "__CPU_Z80__";
const char* CPU_Z80N_DEFINE = "__CPU_Z80N__";
const char* CPU_Z180_DEFINE = "__CPU_Z180__";
const char* CPU_R2K_DEFINE = "__CPU_R2K__";
const char* CPU_R3K_DEFINE = "__CPU_R3K__";
const char* CPU_8080_DEFINE = "__CPU_8080__";
const char* CPU_8085_DEFINE = "__CPU_8085__";
const char* CPU_GBZ80_DEFINE = "__CPU_GBZ80__";

const char* CPU_ZILOG_DEFINE = "__CPU_ZILOG__";
const char* CPU_RABBIT_DEFINE = "__CPU_RABBIT__";
const char* CPU_INTEL_DEFINE = "__CPU_INTEL__";

const char* SWAP_IXIY_DEFINE = "__SWAP_IX_IY__";

void ClearEnvPendingOptions() {
    envPendingOptions.clear();
}

void SetEnvPendingOptions(const char* str) {
    envPendingOptions = str;
}

void AppendEnvPendingOptions(const char* str) {
    using namespace std;

    envPendingOptions += string(" ") + str;
}

const char* GetEnvPendingOptions() {
    return envPendingOptions.c_str();
}

bool OptionVerbose() {
    return app.options.verbose;
}

bool OptionMapfile() {
    return app.options.mapfile;
}

bool OptionSymtable() {
    return app.options.symtable;
}

bool OptionListfile() {
    return app.options.listfile;
}

bool OptionGlobaldef() {
    return app.options.globaldef;
}

void SetOutputLibrary(const char* library) {
    app.options.outputLibrary = library;
}

const char* GetOutputLibrary() {
    if (app.options.outputLibrary.empty())
        return NULL;
    else
        return app.options.outputLibrary.generic_string().c_str();
}





int GetCpu() {
    return static_cast<int>(app.options.cpu.GetType());
}

int GetInvokeOpcode() {
    return app.options.arch.INVOKE();
}

bool SwapIxIy() {
    return app.options.swapIxIy;
}

void TraverseDefines(void(*func)(const char* name, int value)) {
    for (auto it = app.options.defines.cbegin();
            it != app.options.defines.cend(); ++it)
        func((*it).first.c_str(), (*it).second);
}

bool OptionOptimizeSpeed() {
    return app.options.optimizeSpeed;
}

bool OptionDebugInfo() {
    return app.options.debugInfo;
}

const char* AddStringPool(const char* str) {
    using namespace std;

    if (!str)
        return nullptr;

    static unordered_set<string> pool;
    const char* pooledString = pool.insert(str).first->c_str();
    return pooledString;
}

const char* ExpandEnvironmentVarsC(const char* str_) {
    using namespace std;

    string str{ str_ };
    str = App::ExpandEnvironmentVars(str);
    return AddStringPool(str.c_str());
}

void PushSourceDirname(const char* filename) {
    fs::path dirname = fs::path(filename).parent_path();
    if (dirname.empty())
        app.options.includePath.push_back(fs::path("."));
    else
        app.options.includePath.push_back(dirname);
}

void PopSourceDirname() {
    if (!app.options.includePath.empty())
        app.options.includePath.pop_back();
}

const char* SearchIncludeFile(const char* filename) {
    using namespace std;

    fs::path file = App::SearchFile(filename, app.options.includePath);
    if (file.empty())
        return AddStringPool(filename);
    else
        return AddStringPool(file.generic_string().c_str());
}

const char* SearchLibraryFile(const char* filename) {
    using namespace std;

    fs::path file = App::SearchFile(filename, app.options.libraryPath);
    if (file.empty())
        return AddStringPool(filename);
    else
        return AddStringPool(file.generic_string().c_str());
}

