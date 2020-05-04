# Rust in DFHack

This is an example project to show that Rust can be used in the [DFHack](https://github.com/DFHack/dfhack) C++ codebase.
This project is a plugin for DFHack.

Output from plugin:
```
[DFHack]# hellorust
Hello World from C++
From rust: Hello World, Rust here!!
From rust: 17
[DFHack]#
```

# Build

Step 1: Add or link the whole content of the repo in the `DFHack/dfhack/plugins` folder of you dfhack source code.
![Showing the `DFHack_Rust_plugin` folder next to the `diggingInvaders` folder and others](https://i.imgur.com/L7w1GaR.png)

Step 2: Edit the `CMakeLists.custom.txt` file and add the line: `add_subdirectory(DFHack_Rust_plugin)` at the end.
This is the name of the folder. It will find the `CMakeLists.txt` file in that folder.

Step 3: Build DFhack as you always do. For example:
```
cd ./build
cmake .. -G Ninja -DCMAKE_BUILD_TYPE:string=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=../../df_linux_0.47.04;
ninja install
```
More info about compiling DFHack: https://docs.dfhack.org/en/stable/docs/Compile.html

Step 4: Execute dfhack so it opens dwarf fortress. Example `./dfhack`

Step 5: Run in the DFHack terminal: `hellorust`
It should output this:
```
[DFHack]# hellorust
Hello World from C++
From rust: Hello World, Rust here!!
From rust: 17
[DFHack]#
```

It works :)

# Troubleshooting
If you change the Rust code it might, as it did for me not recompile if there are changes make to the files.
You might have to recompile rust yourself.
Move to the `dfplugin_test` folder and use `cargo build` and `cargo build --release` to update the dev and release build.
If that does not work try: `cargo build --lib` and `cargo build --lib --release`
