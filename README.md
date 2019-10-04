# CPT
competitive programming template

to add a new task use:
``./create exampleTask``

A new file called exampleTask will be created in the source folder and is added to the cmake build system.
The new file contains our current c++ template. All left to do is implement your main!

If you use sanitizers and gcc then set `ASAN_OPTIONS=abort_on_error=1` for easier debugging.
Same for UBSAN_OPTIONS. Clion has a settings page for these options. You might also want to disable
the fancy sanitizer output checkbox. Otherwise there is no sanitizer output when debugging.
