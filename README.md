# CPT
competitive programming template

## Usage

TL;DR: implement your main in `source/example.cpp`.

To create a new executable, copy `.template.cpp` to the source folder and add the line 
``add_executable([name] [name].cpp)`` to `source/CMakeLists.txt`.
There is a bash script that does these two steps, e.g., `./create [name]`.
Or write all your code in `source/example.cpp`, reset the file when done and depend on the judging systems to keep your code :)

## Setup

Most modern IDEs should have CMake support.
Just open this folder in your IDE.
You need to have a compiler installed and it should be GCC, because that's what most juding systems use.
When using clang the `<bits/stdc++.h>` header does not work.

### VSCode + Docker

You can open this repo inside a [devcontainer in VSCode](https://code.visualstudio.com/docs/devcontainers/containers).
It has all the settings and compiler already installed and ready to go.
This just needs Docker and VSCode with the Dev Containers Extension.

Works on all operating systems!


### Linux

You have GCC installed already.
Use CLion, VSCode, or the devcontainer.

### Windows

If you do not want to use the devcontainer, I recommend a [WSL and Clion](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html) setup.

### MacOS

Same as Linux. Optionally install GCC to use the `bits` header or just use the devcontainer.

## Sanitizers

I enabled sanitzers for gcc and clang via CMake.

For easier debugging, set `ASAN_OPTIONS=abort_on_error=1` and `UBSAN_OPTIONS=abort_on_error=1`.
This will open the debugger when the sanitizer finds an error.

The devcontainer already does this for you.
Clion has a settings page for these options. 
Go to `Settings / Preferences | Build, Execution, Deployment | Dynamic Analysis Tools | Sanitizers` and put
`abort_on_error=1` under `AddressSanitizer` and `UndefinedBehaviorSanitizer`.

When debugging reaches end of `main` the sanitizer might falsely detect an error. Ignore this.
