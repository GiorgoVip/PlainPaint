#!/bin/zsh

#cd ~/Documents/raboti/SAUCE_OS/testo ; clear

CLANG_BASE="../../SAUCE_OS/applications/clang+llvm-9.0.1-x86_64-apple-darwin/bin/" ; CLANG=$CLANG_BASE"clang" ; LD=$CLANG_BASE"ld64.lld"
ASM_BASE="../../SAUCE_OS/applications/nasm-2_13rc23/" ; ASM=$ASM_BASE"nasm" ; OFORM="macho64"	;	T_VER="10.15" ;	SDK_PATH="../../SAUCE_OS/applications/sdk/MacOSX"$T_VER".sdk/" #SDK_PATH="/Library/Developer/CommandLineTools/SDKs/MacOSX"$T_VER".sdk/"
FRAMEWORKS="-framework CoreServices -framework " ; FRM_BASE=$SDK_PATH"System/Library/Frameworks" ; LIB_BASE=$SDK_PATH"usr/lib"

rm main.exc main.o vscript.o canvas.o ./Main.app/Contents/MacOS/main.exc
$CLANG -O0 main.c -mmacos-version-min=$T_VER -I "../../SAUCE_OS/applications/sdk/MacOSX"$T_VER".sdk/usr/include" -I "../../SAUCE_OS/applications/sdk/MacOSX"$T_VER".sdk/System/Library/Frameworks/CoreServices.framework/Versions/A/Frameworks/LaunchServices.framework/Versions/A/Headers" -c
$ASM -O0 -i. -f $OFORM -o vscript.o ./vscript/vscript.s -g
ld -O0 main.o vscript.o -o main.exc -platform_version "macos" $T_VER $T_VER -F $FRM_BASE -L $LIB_BASE -lc -framework CoreServices -F "../frameworks" -framework SDL2 -rpath @loader_path/../Frameworks
cp main.exc ./Main.app/Contents/MacOS/


printf "(I) ur arch is " && arch	#// Provide absolute -L -F paths for $LD
