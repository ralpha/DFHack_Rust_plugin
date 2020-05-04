#include "Core.h"
#include "Console.h"
#include "Export.h"
#include "PluginManager.h"

#include "DataDefs.h"

using std::string;
using std::vector;
using namespace DFHack;

DFHACK_PLUGIN("hellorust");

// Adding links to Rust functions
extern "C" {
  int add(int a, int b);
  const char * hello_world_in_rust();
  void free_rust_cstring(const char *);
}

// Function called by `plugin_init`
// expected output from this:
// ```
// [DFHack]# hellorust
// Hello World from C++
// From rust: Hello World, Rust here!
// From rust: 17
// [DFHack]#
// ```
command_result df_hello (color_ostream &out, vector <string> & parameters) {
    // Print a normal C++ string
    out.print("Hello World from C++\n");
    // Print a rust string
    const char *rust_string = hello_world_in_rust();
    out.print("From rust: %s\n", rust_string);
    // Free the rust string with rust,
    // because rust might have a different memery allocator
    // see: https://doc.rust-lang.org/stable/std/ffi/struct.CString.html#method.into_raw
    // and: https://doc.rust-lang.org/stable/std/ffi/struct.CString.html#method.from_raw
    free_rust_cstring(rust_string);
    // Create some numbers and add them in rust and return the result
    int a = 5;
    int b = 12;
    out.print("From rust: %d\n", add(a,b));
    // Done
    return CR_OK;
}

// DFHack plugin init and shutdown
DFhackCExport command_result plugin_init ( color_ostream &out, std::vector <PluginCommand> &commands) {
    commands.push_back(PluginCommand("hellorust",
        "Print hello from Rust.",
        df_hello));
    return CR_OK;
}

DFhackCExport command_result plugin_shutdown ( color_ostream &out ) {
    return CR_OK;
}
