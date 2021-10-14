# CPT
competitive programming template

TL;DR: write all your code in `source/example.cpp`, reset the file when done and depend on the judging systems to keep your code :)

## Linux

To add a new task use:
``./create exampleTask``

A new file called `exampleTask.cpp` will be created in the source folder and is added to the cmake build system.
The new file contains our current c++ template. All left to do is implement your main!


## Windows

I recommend a [WSL and Clion](https://www.jetbrains.com/help/clion/how-to-use-wsl-development-environment-in-product.html) setup.
If you cloned this repo into the windows filesystem, then you probably have windows line endings and get an error when running the create script from WSL.
You can change this with `dos2unix ./create` which changes line endings of the `create` file.
To avoid this in the future read about the [git `core.autocrlf` option](https://git-scm.com/book/en/v2/Customizing-Git-Git-Configuration).


## MacOS

Try the same as for Linux. 
When using clang the `<bits/stdc++.h>` header does not work.
I recommend gcc because that's what most juding systems use.


## Sanitizers

I enabled sanitzers for gcc and clang.
Set `ASAN_OPTIONS=abort_on_error=1` for easier debugging.
Same for UBSAN_OPTIONS. Clion has a settings page for these options. 
Go to `Settings / Preferences | Build, Execution, Deployment | Dynamic Analysis Tools | Sanitizers` and put
`abort_on_error=1` under `AddressSanitizer` and `UndefinedBehaviorSanitizer`.
This will open the debugger when the sanitizer finds an error.

When debugging reaches end of `main` the sanitizer might falsely detect an error. Ignore this.


## I don't want to use the ./create script -.-

Ok. To create a new executable copy `.template.cpp` to the source folder and add the line 
``add_executable([name] [name].cpp)`` to `source/CMakeLists.txt`.

