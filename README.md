# CPT
competitive programming template for vscode with devcontainers

You need:
- docker
- vscode + [remote-containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension

To start coding:
- open vscode
- click the remote-containers icon (green icon bottom left)
- choose "Clone a repository from GitHub in a Container Volume"
- paste the URL of this branch: `https://github.com/chistopher/CPT/tree/vscode`
- wait
- now your vscode instance is connected to a dev-container running debian with cmake, GCC and some dev extensions for vscode

To start coding, open a new terminal (`CTRL`+`SHIFT`+ `) and add a new task with:
``./create exampleTask``

A new file called `exampleTask.cpp` will be created in the source folder and is added to the cmake build system.
The new file contains our current c++ template. All left to do is implement your main!

Switching between build/release, choosing compiler, choosing target to run, running and debugging is all done via icons in the status bar.