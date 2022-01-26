# estart

estart is my program launcher that I use on Windows machines when I develop
software.

I normally maintain multiple projects at a time and some of those projects have
tool-chain conflicts since they require specific environment variable settings.

Take the `PATH` environment variable as an example. Presume you're working on a
x64 project and you need to disassemble an assembly. The .Net developer tools
folder is in your `PATH` variable, so you type `ildasm.exe` in the CLI and
something runs, but it's the x86 version not the x64 version. You can change
`PATH` but then you're using the x64 version all the time. Or you could type
out the full path to the executable in the CLI or change folders but that is
painful. Estart launches my program with the environment variables of my
volition. Thus:

    estart ildasm 64 Herne

This tells estart that I want to launch `ildasm` with my 64bit environment using
the `Herne` profile. I've used batch files and scripting languages to do the
same thing but I was unsatisfied with those approaches because I do not like
arcane batch file syntax nor do I like additional install dependencies.

> I used to use PERL to success until I set up my new computer and forgot which
> version I installed. Estart.exe is static linked, so I only need to copy it to
> my path. I can backup and restore all my .lnk files from computer to computer
> because estart knows where each program is installed.

Estart also works from other environments that need batch file wrappers to work
right. For example, my .gitconfig contains the following setup for my external
diff viewer.

    [difftool �vsdiff�]
    cmd = estart.exe VSDIFF 64 HERNE -r1 \"$LOCAL\" \"$REMOTE\"

I've had problems in the past trying to wrap that command with PERL scripts or
found it tedious with batch files.

## Useful Commands
estart.exe BASH 64 IBARAKI
estart.exe CONSOLE 64 IBARAKI
estart.exe VSCODE 64 IBARAKI