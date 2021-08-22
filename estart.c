#include <Windows.h>
#include <strsafe.h>
#include <shlwapi.h>

/* Misc */
#define ENVIRONMENT_BUFFER_SIZE 3072

#include "c_only.h"
#include "c_d.h"

enum dir {
    DIR_CL14_32,
    DIR_CL14_64,
    DIR_CMAKE,
    DIR_DOTNET32,
    DIR_DOTNET64,
    DIR_DOTNET461_32,
    DIR_DOTNET461_64,
    DIR_DOTNET461_TOOLS32,
    DIR_DOTNET461_TOOLS64,
    DIR_DOTNET471_TOOLS32,
    DIR_DOTNET471_TOOLS64,
    DIR_DOTNET472_TOOLS32,
    DIR_DOTNET472_TOOLS64,
    DIR_DOTNET480_TOOLS32,
    DIR_DOTNET480_TOOLS64,
    DIR_DOTNET4_32,
    DIR_DOTNET4_64,
    DIR_DOTNET4_TOOLS32,
    DIR_DOTNET4_TOOLS64,
    DIR_GIT,
    DIR_GIT_BIN,
    DIR_GIT_CMD,
    DIR_GIT_TF,
    DIR_HOME,
    DIR_JRE,
    DIR_MSBUILD12_32,
    DIR_MSBUILD12_64,
    DIR_MSBUILD14_32,
    DIR_MSBUILD14_64,
    DIR_MSBUILD15_32,
    DIR_MSBUILD15_64,
    DIR_MSBUILD16_32,
    DIR_MSBUILD16_64,
    DIR_NASM,
    DIR_PROJECT,
    DIR_SLICKEDIT,
    DIR_SLICKEDIT_CFG,
    DIR_TBC,
    DIR_TDK_FREETOWN,
    DIR_TDK_HERNE,
    DIR_TDK_HOBART,
    DIR_TDK_IBARAKI,
    DIR_VIM,
    DIR_VS2012,
    DIR_VS2013,
    DIR_VS2015,
    DIR_VS2017,
    DIR_VS2019,
    DIR_WINDBG32,
    DIR_WINDBG64,
    DIR_WINSDK81_32,
    DIR_WINSDK81_64,
    DIR_WINSDK10_32,
    DIR_WINSDK10_64,
    DIR_WPT,
    DIR_NUM
};

enum tool {
    TOOL_BASH,
    TOOL_CONSOLE,
    TOOL_SLICKEDIT,
    TOOL_SLICKEDIT_DIFF,
    TOOL_SLICKEDIT_MERGE,
    TOOL_VIM,
    TOOL_VS2012,
    TOOL_VS2013,
    TOOL_VS2015,
    TOOL_VS2017,
    TOOL_VS2019,
    TOOL_WINDBG32,
    TOOL_WINDBG64,
    TOOL_VSCODE,
    TOOL_NUM
};

enum var {
    VAR_NT_SYMBOL_PATH,
    VAR_PATH,
    VAR_TERM,
    VAR_HOME,
    VAR_NUM
};

enum file {
    FILE_VS2012_SETTINGS_CURRENT,
    FILE_VS2012_SETTINGS_MASTER,
    FILE_VS2013_SETTINGS_CURRENT,
    FILE_VS2013_SETTINGS_MASTER,
    FILE_VS2015_SETTINGS_CURRENT,
    FILE_VS2015_SETTINGS_MASTER,
    FILE_VS2017_SETTINGS_CURRENT,
    FILE_VS2017_SETTINGS_MASTER,
    FILE_NUM
};

enum arch {
    NULL_ARCH,
    X86,
    X64
};

enum env {
    ENV_NULL,
    ENV_FREETOWN,
    ENV_HERNE,
    ENV_HOBART,
    ENV_IBARAKI
};

enum pc {
    C_ONLY,
    C_D,
    PC_NULL
};

enum opcode {
    OPC_NULL,
    OPC_BASH,
    OPC_COMMIT,
    OPC_CMD,
    OPC_SLICKEDIT,
    OPC_TFS2012,
    OPC_TFS2013,
    OPC_VIM,
    OPC_VS2012,
    OPC_VS2013,
    OPC_VS2015,
    OPC_VS2017,
    OPC_VS2019,
    OPC_SLICKEDIT_DIFF,
    OPC_SLICKEDIT_MERGE,
    OPC_WINDBG,
    OPC_VSCODE
};

/**
 * struct profile - computer runtime profile
 * @pc:     the computer this profile belongs to
 * @var:    profile variable mappings
 * @file:   profile file mappings
 * @dir:    profile directory mappings
 * @tool:   profile tool mappings
 */
struct profile {
    enum pc pc;
    wchar_t* var[VAR_NUM];
    wchar_t* file[FILE_NUM];
    wchar_t* dir[DIR_NUM];
    wchar_t* tool[TOOL_NUM];
};

struct command {
    enum env env;
    enum opcode opcode;
    enum arch arch;
};

#define ALLOCATE_RUNTIME_PROFILE(COMPUTERNAME)\
struct profile profile##COMPUTERNAME =\
{\
    COMPUTERNAME,\
    {\
        COMPUTERNAME ## _NT_SYMBOL_PATH,\
        COMPUTERNAME ## _PATH,\
        COMPUTERNAME ## _TERM,\
    },\
    {\
        COMPUTERNAME ## _VS2012_CURRENT_SETTINGS,\
        COMPUTERNAME ## _VS2012_MASTER_SETTINGS,\
        COMPUTERNAME ## _VS2013_CURRENT_SETTINGS,\
        COMPUTERNAME ## _VS2013_MASTER_SETTINGS,\
        COMPUTERNAME ## _VS2015_CURRENT_SETTINGS,\
        COMPUTERNAME ## _VS2015_MASTER_SETTINGS,\
        COMPUTERNAME ## _VS2017_CURRENT_SETTINGS,\
        COMPUTERNAME ## _VS2017_MASTER_SETTINGS,\
    },\
    {\
        COMPUTERNAME ## _DIR_CL14_32,\
        COMPUTERNAME ## _DIR_CL14_64,\
        COMPUTERNAME ## _DIR_CMAKE,\
        COMPUTERNAME ## _DIR_DOTNET32,\
        COMPUTERNAME ## _DIR_DOTNET64,\
        COMPUTERNAME ## _DIR_DOTNET461_32,\
        COMPUTERNAME ## _DIR_DOTNET461_64,\
        COMPUTERNAME ## _DIR_DOTNET461_TOOLS32,\
        COMPUTERNAME ## _DIR_DOTNET461_TOOLS64,\
        COMPUTERNAME ## _DIR_DOTNET471_TOOLS32,\
        COMPUTERNAME ## _DIR_DOTNET471_TOOLS64,\
        COMPUTERNAME ## _DIR_DOTNET472_TOOLS32,\
        COMPUTERNAME ## _DIR_DOTNET472_TOOLS64,\
        COMPUTERNAME ## _DIR_DOTNET480_TOOLS32,\
        COMPUTERNAME ## _DIR_DOTNET480_TOOLS64,\
        COMPUTERNAME ## _DIR_DOTNET4_32,\
        COMPUTERNAME ## _DIR_DOTNET4_64,\
        COMPUTERNAME ## _DIR_DOTNET4_TOOLS32,\
        COMPUTERNAME ## _DIR_DOTNET4_TOOLS64,\
        COMPUTERNAME ## _DIR_GIT,\
        COMPUTERNAME ## _DIR_GIT_BIN,\
        COMPUTERNAME ## _DIR_GIT_CMD,\
        COMPUTERNAME ## _DIR_GIT_TF,\
        COMPUTERNAME ## _DIR_HOME,\
        COMPUTERNAME ## _DIR_JRE,\
        COMPUTERNAME ## _DIR_MSBUILD12_32,\
        COMPUTERNAME ## _DIR_MSBUILD12_64,\
        COMPUTERNAME ## _DIR_MSBUILD14_32,\
        COMPUTERNAME ## _DIR_MSBUILD14_64,\
        COMPUTERNAME ## _DIR_MSBUILD15_32,\
        COMPUTERNAME ## _DIR_MSBUILD15_64,\
        COMPUTERNAME ## _DIR_MSBUILD16_32,\
        COMPUTERNAME ## _DIR_MSBUILD16_64,\
        COMPUTERNAME ## _DIR_NASM,\
        COMPUTERNAME ## _DIR_PROJECT,\
        COMPUTERNAME ## _DIR_SLICKEDIT,\
        COMPUTERNAME ## _DIR_SLICKEDIT_CFG,\
        COMPUTERNAME ## _DIR_TBC,\
        COMPUTERNAME ## _DIR_TDK_FREETOWN,\
        COMPUTERNAME ## _DIR_TDK_HERNE,\
        COMPUTERNAME ## _DIR_TDK_HOBART,\
        COMPUTERNAME ## _DIR_TDK_IBARAKI,\
        COMPUTERNAME ## _DIR_VIM,\
        COMPUTERNAME ## _DIR_VS2012,\
        COMPUTERNAME ## _DIR_VS2013,\
        COMPUTERNAME ## _DIR_VS2015,\
        COMPUTERNAME ## _DIR_VS2017,\
        COMPUTERNAME ## _DIR_WINDBG32,\
        COMPUTERNAME ## _DIR_WINDBG64,\
        COMPUTERNAME ## _DIR_WINSDK81_32,\
        COMPUTERNAME ## _DIR_WINSDK81_64,\
        COMPUTERNAME ## _DIR_WINSDK10_32,\
        COMPUTERNAME ## _DIR_WINSDK10_64,\
        COMPUTERNAME ## _DIR_WPT\
    },\
    {\
        COMPUTERNAME ## _BASH,\
        COMPUTERNAME ## _CONSOLE,\
        COMPUTERNAME ## _SLICKEDIT,\
        COMPUTERNAME ## _SLICKEDIT_DIFF,\
        COMPUTERNAME ## _SLICKEDIT_MERGE,\
        COMPUTERNAME ## _VIM,\
        COMPUTERNAME ## _VS2012,\
        COMPUTERNAME ## _VS2013,\
        COMPUTERNAME ## _VS2015,\
        COMPUTERNAME ## _VS2017,\
        COMPUTERNAME ## _VS2019,\
        COMPUTERNAME ## _WINDBG32,\
        COMPUTERNAME ## _WINDBG64,\
        COMPUTERNAME ## _VSCODE \
    }\
}
ALLOCATE_RUNTIME_PROFILE(C_ONLY);
ALLOCATE_RUNTIME_PROFILE(C_D);
#undef ALLOCATE_RUNTIME_PROFILE

/* Support */
enum pc pc_conv(const wchar_t* const pc);
enum opcode opcode_conv(const wchar_t* const opcode);
enum arch arch_conv(const wchar_t* const arch);
struct command command_get();
struct profile* profile_get();
int arg_rinse(wchar_t* dirtyArg);
int set_child_startupinfo(STARTUPINFO *inf);

/* Process Environment */
enum env env_conv(const wchar_t* const env);
int env_arg_append(wchar_t* variable, wchar_t* val);
int env_path_add_cwd();
int env_switchto(enum arch arch, enum env env, struct profile* prf);
int env_switchto_freetown32(struct profile *prf);
int env_switchto_freetown64(struct profile *prf);
int env_switchto_herne32(struct profile *prf);
int env_switchto_herne64(struct profile *prf);
int env_switchto_hobart32(struct profile *prf);
int env_switchto_hobart64(struct profile *prf);
int env_switchto_ibaraki32(struct profile *prf);
int env_switchto_ibaraki64(struct profile *prf);

/* Tools */
int run_bash(enum arch, enum env);
int run_cmd(enum arch, enum env);
int run_commit(enum arch, enum env);
int run_diff(enum arch, enum env);
int run_merge(enum arch, enum env);
int run_slickedit(enum arch, enum env);
int run_tfs2012(enum arch, enum env);
int run_tfs2013(enum arch, enum env);
int run_vim(enum arch, enum env);
int run_vs2012(enum arch, enum env);
int run_vs2013(enum arch, enum env);
int run_vs2015(enum arch, enum env);
int run_vs2017(enum arch, enum env);
int run_vs2019(enum arch, enum env);
int run_windbg(enum arch, enum env);
int run_vscode(enum arch, enum env);

/**
 * env_switchto - Switch environments
 * @arch:
 * @env:
 * @prf:
 *
 * Returns zero on success.
 */
int env_switchto(enum arch arch, enum env env, struct profile *prf)
{
    switch (arch) {
    case X86:
        switch (env) {
        case ENV_FREETOWN:
            env_switchto_freetown32(prf);
            break;
        case ENV_HERNE:
            env_switchto_herne32(prf);
            break;
        case ENV_HOBART:
            env_switchto_hobart32(prf);
            break;
        case ENV_IBARAKI:
            env_switchto_ibaraki32(prf);
            break;
        }
        break;
    case X64:
        switch (env) {
        case ENV_FREETOWN:
            env_switchto_freetown64(prf);
            break;
        case ENV_HERNE:
            env_switchto_herne64(prf);
            break;
        case ENV_HOBART:
            env_switchto_hobart64(prf);
            break;
        case ENV_IBARAKI:
            env_switchto_ibaraki64(prf);
            break;
        }
        break;
    }
    return 0;
}

/**
 * command_get - Convert the estart command line into something useful
 */
struct command command_get()
{
    int argc;
    struct command ret;

    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) {
        ret.opcode = opcode_conv(L"VSCODE");
        ret.arch = arch_conv(L"64");
        ret.env = env_conv(L"IBARAKI");
        return ret;
    }

    ret.opcode = opcode_conv(argv[1]);
    ret.arch = arch_conv(argv[2]);
    ret.env = env_conv(argv[3]);
    LocalFree(argv);
    return ret;
}

/*
 * opcode_conv - Convert an opcode from a string to an enum
 * @opcode: the text opcode to convert
 */
enum opcode opcode_conv(const wchar_t* const opcode)
{
    if (0 == lstrcmpi(opcode, L"BASH"))
        return OPC_BASH;
    if (0 == lstrcmpi(opcode, L"COMMIT"))
        return OPC_COMMIT;
    if (0 == lstrcmpi(opcode, L"CONSOLE"))
        return OPC_CMD;
    if (0 == lstrcmpi(opcode, L"SLICKEDIT"))
        return OPC_SLICKEDIT;
    if (0 == lstrcmpi(opcode, L"TFS2012"))
        return OPC_TFS2012;
    if (0 == lstrcmpi(opcode, L"TFS2013"))
        return OPC_TFS2013;
    if (0 == lstrcmpi(opcode, L"VIM"))
        return OPC_VIM;
    if (0 == lstrcmpi(opcode, L"VS2012"))
        return OPC_VS2012;
    if (0 == lstrcmpi(opcode, L"VS2013"))
        return OPC_VS2013;
    if (0 == lstrcmpi(opcode, L"VS2015"))
        return OPC_VS2015;
    if (0 == lstrcmpi(opcode, L"VS2017"))
        return OPC_VS2017;
    if (0 == lstrcmpi(opcode, L"VS2019"))
        return OPC_VS2019;
    if (0 == lstrcmpi(opcode, L"VSDIFF"))
        return OPC_SLICKEDIT_DIFF;
    if (0 == lstrcmpi(opcode, L"VSMERGE"))
        return OPC_SLICKEDIT_MERGE;
    if (0 == lstrcmpi(opcode, L"WINDBG"))
        return OPC_WINDBG;
    if (0 == lstrcmpi(opcode, L"VSCODE"))
        return OPC_VSCODE;
    return OPC_NULL;
}

/**
 * env_conv - Convert an environment from a string to an enum
 * @env:
 */
enum env env_conv(const wchar_t* const env)
{
    if (0 == lstrcmpi(env, L"IBARAKI"))
        return ENV_IBARAKI;
    if (0 == lstrcmpi(env, L"HOBART"))
        return ENV_HOBART;
    if (0 == lstrcmpi(env, L"HERNE"))
        return ENV_HERNE;
    if (0 == lstrcmpi(env, L"FREETOWN"))
        return ENV_FREETOWN;
    return ENV_NULL;
}

/**
 * arch_conv - Convert an architecture from a string to an enum
 * @arch:
 */
enum arch arch_conv(const wchar_t* const arch)
{
    if (0 == lstrcmpi(arch, L"32"))
        return X86;
    if (0 == lstrcmpi(arch, L"64"))
        return X64;
    return NULL_ARCH;
}

/**
 * pc_conv - Convert a well-known computer name from a string to its enum
 * @pc:     the computer name to convert
 */
enum pc pc_conv(const wchar_t* const pc)
{
    if (0 == lstrcmpi(pc, L"DUS9377B"))
        return C_ONLY;
    if (0 == lstrcmpi(pc, L"ELSA"))
        return C_ONLY;
    if (0 == lstrcmpi(pc, L"CHICK-B"))
        return C_D;

    return PC_NULL;
}

/**
 * profile_get - Get the active computer profile
 *
 * Returns the active computer profile based on the `COMPUTERNAME`
 * environment variable.
 *
 * Returns zero on success.
 */
#define CASE_PROFILE(CNAME) case CNAME : { return &profile ## CNAME ; }
struct profile* profile_get()
{
    wchar_t computerName[ENVIRONMENT_BUFFER_SIZE];
    GetEnvironmentVariable(L"COMPUTERNAME", &computerName[0],
                ENVIRONMENT_BUFFER_SIZE);

    switch(pc_conv(computerName)) {
        CASE_PROFILE(C_ONLY)
        CASE_PROFILE(C_D)
    }
    return &profileC_ONLY;
}
#undef CASE_PROFILE

/**
 * wWinMain - Program entry point
 * @hInstance:
 * @hPrevInstance:
 * @lpCmndLine:
 * @nCmdShow:
 *
 * Returns zero on success.
 */
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPWSTR lpCmdLine, int nCmdShow)
{
    hInstance; hPrevInstance; lpCmdLine; nCmdShow;

    struct command cmd = command_get();
    switch (cmd.opcode) {
    case OPC_BASH:
        run_bash(cmd.arch, cmd.env);
        break;
    case OPC_COMMIT:
        run_commit(cmd.arch, cmd.env);
        break;
    case OPC_CMD:
        run_cmd(cmd.arch, cmd.env);
        break;
    case OPC_SLICKEDIT:
        run_slickedit(cmd.arch, cmd.env);
        break;
    case OPC_TFS2012:
        run_tfs2012(cmd.arch, cmd.env);
        break;
    case OPC_TFS2013:
        run_tfs2013(cmd.arch, cmd.env);
        break;
    case OPC_VS2012:
        run_vs2012(cmd.arch, cmd.env);
        break;
    case OPC_VIM:
        run_vim(cmd.arch, cmd.env);
        break;
    case OPC_VS2013:
        run_vs2013(cmd.arch, cmd.env);
        break;
    case OPC_VS2015:
        run_vs2015(cmd.arch, cmd.env);
        break;
    case OPC_VS2017:
        run_vs2017(cmd.arch, cmd.env);
        break;
    case OPC_VS2019:
        run_vs2019(cmd.arch, cmd.env);
        break;
    case OPC_SLICKEDIT_DIFF:
        run_diff(cmd.arch, cmd.env);
        break;
    case OPC_SLICKEDIT_MERGE:
        run_merge(cmd.arch, cmd.env);
        break;
    case OPC_WINDBG:
        run_windbg(cmd.arch, cmd.env);
        break;
    case OPC_VSCODE:
        run_vscode(cmd.arch, cmd.env);
        break;
    }
    return 0;
}

/**
 * env_arg_append - Missing documentation
 * @variable:
 * @val:
 *
 * Returns zero on success.
 */
int env_arg_append(wchar_t* var, wchar_t* val)
{
    wchar_t oldVal[ENVIRONMENT_BUFFER_SIZE];
    wchar_t newVal[ENVIRONMENT_BUFFER_SIZE];

    GetEnvironmentVariable(var, &oldVal[0], ENVIRONMENT_BUFFER_SIZE);
    StringCchPrintf(newVal, sizeof(newVal) / sizeof(wchar_t), L"%s;%s",
            oldVal, val);
    SetEnvironmentVariable(var, newVal);
    return 0;
}

/**
 * env_switchto_freetown32 - Switch to 32-bit Freetown build environment
 * @prf:    Get environment variables from this profile
 *
 * Set the current process environment to the 32-bit Freetown build
 * environment obtaining its values from the specified profile.
 *
 * Returns zero on success.
 */
int env_switchto_freetown32(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);

    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_JRE]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_TF]);
    env_arg_append(L"PATH", prf->dir[DIR_SLICKEDIT]);
    env_arg_append(L"PATH", prf->dir[DIR_CMAKE]);
    env_arg_append(L"PATH", prf->dir[DIR_WPT]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD12_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET4_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET4_TOOLS32]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2013]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK81_32]);
    env_arg_append(L"PATH", prf->dir[DIR_WINDBG32]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_FREETOWN]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);

    SetEnvironmentVariable(L"_NT_SYMBOL_PATH",
                prf->var[VAR_NT_SYMBOL_PATH]);

    SetEnvironmentVariable(L"TargetFrameworkSDKToolsDirectory",
                prf->dir[DIR_DOTNET4_TOOLS32]);

    return 0;
}

/**
 * env_switchto_freetown64 - Switch to 64-bit Freetown build environment
 * @prf:    Get environment values from this profile
 *
 * Set the current process environment to the 64-bit Freetown build
 * environment obtaining its values from the specified profile.
 *
 * Returns zero on success.
 */
int env_switchto_freetown64(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);

    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_JRE]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_TF]);
    env_arg_append(L"PATH", prf->dir[DIR_SLICKEDIT]);
    env_arg_append(L"PATH", prf->dir[DIR_CMAKE]);
    env_arg_append(L"PATH", prf->dir[DIR_WPT]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD12_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET4_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET4_TOOLS64]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2013]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK81_64]);
    env_arg_append(L"PATH", prf->dir[DIR_WINDBG64]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_FREETOWN]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);

    SetEnvironmentVariable(L"_NT_SYMBOL_PATH",
                prf->var[VAR_NT_SYMBOL_PATH]);

    SetEnvironmentVariable(L"TargetFrameworkSDKToolsDirectory",
                prf->dir[DIR_DOTNET4_TOOLS64]);

    return 0;
}

/**
 * env_switchto_herne32 - Switch to 32-bit Herne build environment
 * @prf:    Get environment values from this profile
 *
 * Set the current process environment to the 32-bit Herne build environment
 * obtaining its values from the specified profile.
 *
 * Returns zero on success.
 */
int env_switchto_herne32(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);
    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_VIM]);
    env_arg_append(L"PATH", prf->dir[DIR_JRE]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_TF]);
    env_arg_append(L"PATH", prf->dir[DIR_CMAKE]);
    env_arg_append(L"PATH", prf->dir[DIR_WPT]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD14_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_TOOLS32]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK81_32]);
    env_arg_append(L"PATH", prf->dir[DIR_WINDBG32]);
    env_arg_append(L"PATH", prf->dir[DIR_NASM]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2015]);
    env_arg_append(L"PATH", prf->dir[DIR_CL14_32]);
    env_arg_append(L"PATH", prf->dir[DIR_TDK_HERNE]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET32]);

    SetEnvironmentVariable(L"_NT_SYMBOL_PATH",
                prf->var[VAR_NT_SYMBOL_PATH]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_HERNE]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);
    return 0;
}

/**
* env_switchto_herne32 - Switch to 32-bit Herne build environment
* @prf: Get environment values from this profile
*
* Set the current process environment to the 32-bit Herne build environment
* obtaining its values from the specified profile.
*
* Returns zero on success.
*/
int env_switchto_hobart32(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);
    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_VIM]);
    env_arg_append(L"PATH", prf->dir[DIR_JRE]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_TF]);
    env_arg_append(L"PATH", prf->dir[DIR_CMAKE]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD15_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET471_TOOLS32]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK10_32]);
    env_arg_append(L"PATH", prf->dir[DIR_WINDBG32]);
    env_arg_append(L"PATH", prf->dir[DIR_NASM]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2017]);
    env_arg_append(L"PATH", prf->dir[DIR_CL14_32]);
    env_arg_append(L"PATH", prf->dir[DIR_TDK_HOBART]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET32]);

    SetEnvironmentVariable(L"_NT_SYMBOL_PATH",
        prf->var[VAR_NT_SYMBOL_PATH]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_HOBART]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);
    return 0;
}

/**
 * env_switchto_herne64 - Switch to 64-bit Herne build environment
 * @prf:    Get environment values from this profile
 *
 * Set the current process environment to the 64-bit Herne build environment
 * obtaining its values from the specified profile.
 *
 * Returns zero on success.
 */
int env_switchto_herne64(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);
    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_VIM]);
    env_arg_append(L"PATH", prf->dir[DIR_JRE]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_TF]);
    env_arg_append(L"PATH", prf->dir[DIR_CMAKE]);
    env_arg_append(L"PATH", prf->dir[DIR_WPT]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD14_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_TOOLS64]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK81_64]);
    env_arg_append(L"PATH", prf->dir[DIR_WINDBG64]);
    env_arg_append(L"PATH", prf->dir[DIR_NASM]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2015]);
    env_arg_append(L"PATH", prf->dir[DIR_CL14_64]);
    env_arg_append(L"PATH", prf->dir[DIR_TDK_HERNE]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET64]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_HERNE]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);

    SetEnvironmentVariable(L"_NT_SYMBOL_PATH",
                prf->var[VAR_NT_SYMBOL_PATH]);
    return 0;
}

/**
* env_switchto_herne64 - Switch to 64-bit Herne build environment
* @prf: Get environment values from this profile
*
* Set the current process environment to the 64-bit Herne build environment
* obtaining its values from the specified profile.
*
* Returns zero on success.
*/
int env_switchto_hobart64(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);
    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_VIM]);
    env_arg_append(L"PATH", prf->dir[DIR_JRE]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_TF]);
    env_arg_append(L"PATH", prf->dir[DIR_CMAKE]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD15_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET472_TOOLS64]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK10_64]);
    env_arg_append(L"PATH", prf->dir[DIR_WINDBG64]);
    env_arg_append(L"PATH", prf->dir[DIR_NASM]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2017]);
    env_arg_append(L"PATH", prf->dir[DIR_CL14_64]);
    env_arg_append(L"PATH", prf->dir[DIR_TDK_HOBART]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET64]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_HOBART]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);

    SetEnvironmentVariable(L"_NT_SYMBOL_PATH",
        prf->var[VAR_NT_SYMBOL_PATH]);
    return 0;
}

int env_switchto_ibaraki32(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);
    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD16_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_32]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET472_TOOLS32]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK10_32]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2019]);
    env_arg_append(L"PATH", prf->dir[DIR_CL14_32]);
    env_arg_append(L"PATH", prf->dir[DIR_TDK_IBARAKI]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET32]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_IBARAKI]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);

    return 0;
}

int env_switchto_ibaraki64(struct profile *prf)
{
    SetEnvironmentVariable(L"PATH", prf->var[VAR_PATH]);
    env_path_add_cwd();
    env_arg_append(L"PATH", prf->dir[DIR_VIM]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_BIN]);
    env_arg_append(L"PATH", prf->dir[DIR_GIT_CMD]);
    env_arg_append(L"PATH", prf->dir[DIR_MSBUILD16_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET461_64]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET480_TOOLS64]);
    env_arg_append(L"PATH", prf->dir[DIR_WINSDK10_64]);
    env_arg_append(L"PATH", prf->dir[DIR_VS2019]);
    env_arg_append(L"PATH", prf->dir[DIR_CL14_64]);
    env_arg_append(L"PATH", prf->dir[DIR_TDK_IBARAKI]);
    env_arg_append(L"PATH", prf->dir[DIR_DOTNET64]);

    SetEnvironmentVariable(L"GITDIR", prf->dir[DIR_GIT]);
    SetEnvironmentVariable(L"HOME", prf->dir[DIR_HOME]);
    SetEnvironmentVariable(L"TBC", prf->dir[DIR_TBC]);
    SetEnvironmentVariable(L"TDK", prf->dir[DIR_TDK_IBARAKI]);
    SetEnvironmentVariable(L"TERM", prf->var[VAR_TERM]);

    return 0;
}

/**
 * run_slickedit - Run Visual SlickEdit
 * @arch:
 * @env:
 *
 * Run Visual SlickEdit, passing along additional estart command line arguments
 * after the standard estart arguments {opcode}{arch}{env} and inject SlickEdit
 * arguments.
 *
 * The final command line looks like the following:
 *
 * "vs.exe" -sc "{dir}" {varargs}
 *
 * -sc: Tells SlickEdit to use {dir} as its configuration directory. We
 *  deliberately use it to avoid using the default configuration.
 *
 * Returns zero on success.
 */
int run_slickedit(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    wchar_t child_argv[MAX_PATH];
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    struct profile *prf = profile_get();
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);


    child_argv[0] = '\0';
    for (int n = 4; n < argc; ++n) {
        StringCchCat(child_argv, MAX_PATH, L" \"");
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L"\"");
    }
    LocalFree(argv);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" -sc %s %s",
            prf->tool[TOOL_SLICKEDIT],
            prf->dir[DIR_SLICKEDIT_CFG],
            child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_SLICKEDIT], cmdline, 0, 0, FALSE,
            createFlags, 0, 0, &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/*
 * Missing documentation
 */
int set_child_startupinfo(STARTUPINFO *inf)
{
    GetStartupInfo(inf);
    inf->dwX = 50;
    inf->dwY = 50;
    inf->lpTitle = 0;
    inf->dwXSize = 800;
    inf->dwYSize = 600;
    inf->wShowWindow = SW_NORMAL;
    inf->dwFlags = STARTF_USESHOWWINDOW | STARTF_USESIZE
            | STARTF_USEPOSITION;

    return 0;
}

/*
 * Missing documentation
 */
int run_commit(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    wchar_t child_argv[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    child_argv[0] = '\0';
    for (int n = 4; n < argc-1; ++n) {
        StringCchCat(child_argv, MAX_PATH, L" \"");
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L"\"");
    }
    LocalFree(argv);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" %s %s %s", prf->tool[TOOL_SLICKEDIT],
            L"+new -sc ", prf->dir[DIR_SLICKEDIT_CFG], child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_SLICKEDIT], cmdline, 0, 0, FALSE,
            createFlags, 0, 0, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/*
 * Run Microsoft Windows console
 */
int run_cmd(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    struct profile *prf = profile_get();

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t), L"\"%s\"",
            prf->tool[TOOL_CONSOLE]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_CONSOLE], cmdline, 0, 0, FALSE,
            createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/*
 * Missing documentation
 */
int run_diff(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    wchar_t cmdline[8192];
    PROCESS_INFORMATION pi;
    wchar_t child_argv[MAX_PATH];
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    struct profile *prf = profile_get();
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    child_argv[0] = '\0';
    for (int n = 4; n < argc; ++n) {
        arg_rinse(argv[n]);
        StringCchCat(child_argv, MAX_PATH, L" \"");
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L"\"");
    }
    LocalFree(argv);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" %s %s %s", prf->tool[TOOL_SLICKEDIT_DIFF],
            L"-sc ", prf->dir[DIR_SLICKEDIT_CFG], child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_SLICKEDIT_DIFF], cmdline, 0, 0, FALSE,
            createFlags, 0, 0, &si, &pi);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/*
 * Missing documentation
 */
int run_merge(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    wchar_t cmdline[8192];
    PROCESS_INFORMATION pi;
    wchar_t child_argv[MAX_PATH];
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    struct profile *prf = profile_get();
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    child_argv[0] = '\0';
    for (int n = 4; n < argc; ++n) {
        arg_rinse(argv[n]);
        StringCchCat(child_argv, MAX_PATH, L" \"");
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L"\"");
    }
    LocalFree(argv);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" %s %s %s", prf->tool[TOOL_SLICKEDIT_MERGE],
            L"-sc ", prf->dir[DIR_SLICKEDIT_CFG], child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_SLICKEDIT_MERGE], cmdline, 0, 0, FALSE,
            createFlags, 0, 0, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * arg_rinse - Sanitize an input argument
 * @val:    sanitize this
 *
 * Convert forward slashes to back slashes in place.
 *
 * Returns zero on success.
 */
int arg_rinse(wchar_t* val)
{
    wchar_t* index;

    if (!val)
        return -1;

    index = val;
    while ('\0' != *index) {
        if ('/' == *index)
            *index = '\\';
        ++index;
    }
    return 0;
}

/**
 * env_path_add_cwd - Append current working directory to `PATH`
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Append the current working directory to the `PATH` environment variable.
 *
 * Returns zero on success.
 */
int env_path_add_cwd()
{
    wchar_t szFname[MAX_PATH];
    GetModuleFileName(GetModuleHandle(0), szFname, MAX_PATH);
    PathRemoveFileSpec(szFname);
    env_arg_append(L"PATH", szFname);
    return 0;
}

/**
 * run_bash - Run the MySys GIT BASH shell
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_bash(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" --login -i", prf->tool[TOOL_BASH]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_BASH], cmdline, 0, 0, FALSE, createFlags,
            0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_vs2012 - Run Visual Studio 2012
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_vs2012(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    DeleteFile(prf->file[FILE_VS2012_SETTINGS_CURRENT]);
    CopyFile(prf->file[FILE_VS2012_SETTINGS_MASTER],
         prf->file[FILE_VS2012_SETTINGS_CURRENT], FALSE);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t), L"",
            prf->tool[TOOL_VS2012]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2012], cmdline, 0, 0, FALSE,
            createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_vs2013 - Run Visual Studio 2013
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_vs2013(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    DeleteFile(prf->file[FILE_VS2013_SETTINGS_CURRENT]);
    CopyFile(prf->file[FILE_VS2013_SETTINGS_MASTER],
            prf->file[FILE_VS2013_SETTINGS_CURRENT], FALSE);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t), L"",
            prf->tool[TOOL_VS2013]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2013], cmdline, 0, 0, FALSE, createFlags,
            0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_vs2015 - Run Visual Studio 2015
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_vs2015(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    DeleteFile(prf->file[FILE_VS2015_SETTINGS_CURRENT]);
    CopyFile(prf->file[FILE_VS2015_SETTINGS_MASTER],
         prf->file[FILE_VS2015_SETTINGS_CURRENT], FALSE);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t), L"",
            prf->tool[TOOL_VS2015]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2015], cmdline, 0, 0, FALSE,
            createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
* run_vs2017 - Run Visual Studio 2017
* @arch:    processor architecture X86 or X64
* @env: the desired environment
*
* Returns zero on success.
*/
int run_vs2017(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t), L"",
        prf->tool[TOOL_VS2017]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2017], cmdline, 0, 0, FALSE,
        createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
* run_vs2017 - Run Visual Studio 2017
* @arch:    processor architecture X86 or X64
* @env: the desired environment
*
* Returns zero on success.
*/
int run_vs2019(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    StringCchPrintf(cmdline, sizeof(cmdline) /sizeof(wchar_t),
                    L"\"%s\" %s", prf->tool[TOOL_VS2019], L"/LOG");

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2019], cmdline, 0, 0, FALSE,
        createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_tfs2013 - Run Visual Studio 2013 wit Team Foundation Server settings
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_tfs2013(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    DeleteFile(prf->file[FILE_VS2013_SETTINGS_CURRENT]);
    CopyFile(prf->file[FILE_VS2013_SETTINGS_MASTER],
         prf->file[FILE_VS2013_SETTINGS_CURRENT], FALSE);

    StringCchPrintf(cmdline, sizeof(cmdline)/sizeof(wchar_t), L"",
            prf->tool[TOOL_VS2013]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2013], cmdline, 0, 0, FALSE,
            createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_vim - Run VIM82
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_vim(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    wchar_t child_argv[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    child_argv[0] = '\0';
    for (int n = 4; n < argc; ++n) {
        StringCchCat(child_argv, MAX_PATH, L" \"");
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L"\"");
    }
    LocalFree(argv);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" %s",
            prf->tool[TOOL_VIM],
            child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VIM], cmdline, 0, 0, FALSE,
            createFlags, 0, 0, &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_tfs2012 - Run Visual Studio 2012 with Team Foundation Server settings
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_tfs2012(enum arch arch, enum env env)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;

    DeleteFile(prf->file[FILE_VS2012_SETTINGS_CURRENT]);
    CopyFile(prf->file[FILE_VS2012_SETTINGS_MASTER],
         prf->file[FILE_VS2012_SETTINGS_CURRENT], FALSE);

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t), L"",
            prf->tool[TOOL_VS2012]);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess(prf->tool[TOOL_VS2012], cmdline, 0, 0, FALSE,
            createFlags, 0, prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
 * run_windbg - Run WINDBG the Microsoft Windows user mode debugger
 * @arch:   processor architecture X86 or X64
 * @env:    the desired environment
 *
 * Returns zero on success.
 */
int run_windbg(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    wchar_t child_argv[MAX_PATH];
    wchar_t *tool;
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    child_argv[0] = '\0';
    for (int n = 4; n < argc; ++n) {
        arg_rinse(argv[n]);
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L" ");
    }
    LocalFree(argv);

    if (X64 == arch)
        tool = prf->tool[TOOL_WINDBG64];
    else
        tool = prf->tool[TOOL_WINDBG32];

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
            L"\"%s\" %s", tool, child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess((X64 == arch) ? prf->tool[TOOL_WINDBG64] : prf->tool[TOOL_WINDBG32],
            cmdline, 0, 0, FALSE, createFlags, 0,
            prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}

/**
* run_vscode - Run Visual Studio Code editor
* @arch : processor architecture X86 or X64
* @env  : the desired environment
*
* Returns zero on success.
*/
int run_vscode(enum arch arch, enum env env)
{
    int argc;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    wchar_t cmdline[MAX_PATH];
    wchar_t child_argv[MAX_PATH];
    wchar_t *tool;
    struct profile *prf = profile_get();
    DWORD createFlags = CREATE_UNICODE_ENVIRONMENT;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);

    child_argv[0] = '\0';
    for (int n = 4; n < argc; ++n) {
        arg_rinse(argv[n]);
        StringCchCat(child_argv, MAX_PATH, argv[n]);
        StringCchCat(child_argv, MAX_PATH, L" ");
    }
    LocalFree(argv);

    if (X64 == arch)
        tool = prf->tool[TOOL_VSCODE];
    else
        tool = prf->tool[TOOL_VSCODE];

    StringCchPrintf(cmdline, sizeof(cmdline) / sizeof(wchar_t),
        L"\"%s\" %s", tool, child_argv);

    env_switchto(arch, env, prf);
    set_child_startupinfo(&si);
    memset(&pi, 0, sizeof(pi));
    CreateProcess((X64 == arch) ? prf->tool[TOOL_VSCODE] : prf->tool[TOOL_VSCODE],
        cmdline, 0, 0, FALSE, createFlags, 0,
        prf->dir[DIR_PROJECT], &si, &pi);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
