# CPT
competitive programming template

## Usage

Write your code in `main.cpp`.
Once you get a problem accepted you can reset the file with `git restore main.cpp`.
I suggest to depend on the judging systems to keep your code. 
You can also copy the file somewhere for backup before you reset it.

## Setup 1: CLion

Works out-of-the-box on Linux because you have GCC already installed.
On Windows, I recommend a [WSL and Clion](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html) setup.
On macOS you need a compiler. Try `xcode-select --install` for clang or `brew install gcc` for GCC.

## Setup 2: VSCode + Docker

You can open this repo inside a [devcontainer in VSCode](https://code.visualstudio.com/docs/devcontainers/containers).
It has all the settings and compiler already installed and ready to go.
This just needs Docker and VSCode with the Dev Containers Extension.
If you want to use podman instead of docker, then dismiss the promt to install docker and change the `Docker Path` setting of the dev containers extension from `docker` to `podman`.

Works on all operating systems and even in the browser via GitHub codespaces!

## Setup 3: Anything else

Most modern IDEs should have CMake support.
Just open this folder in your IDE.
You need to have a compiler installed.

## Notes

- GCC on macOS does not support sanitizers
- on ARM `long double` is just 64 bit
- the `<bits/stdc++.h>` header is GCC only
- prefer GCC (except on mac), because that's what most juding systems use


## Sanitizers

I enabled sanitzers for gcc and clang via CMake.

For easier debugging, set `ASAN_OPTIONS=abort_on_error=1` and `UBSAN_OPTIONS=abort_on_error=1`.
This will open the debugger when the sanitizer finds an error.

The devcontainer already does this for you.
Clion has a settings page for these options. 
Go to `Settings / Preferences | Build, Execution, Deployment | Dynamic Analysis Tools | Sanitizers` and put
`abort_on_error=1` under `AddressSanitizer` and `UndefinedBehaviorSanitizer`.

When debugging reaches end of `main` the sanitizer might falsely detect an error. Ignore this.
