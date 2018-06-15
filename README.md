# Embedding Rust in C/C++ applications

Let's maybe start the outline of the talk 2 1/2 months before giving it. Following is a rough structre.

1. Rust is really good at FFI, easily integrate "native" code
2. How does it work the other way around? Show `extern "C" fn` example
3. Show some problems (Writing headers is annoying, data exchange & keeping state, memory management, getting binary sizes to be smaller)
4. Also explain the differences between creating C++ and C-like APIs
5. Go into details about what issues need to be solved (memory management, build automation, etc)
6. Then start explaining how to solve these issues
7. Additionally: talk about communicating errors
8. Bringing it all together (mention `qaul.net` which uses Rust for certain components, de-duplicates library dependencies and tries to keep binary sizes small)

### When talking about C++ we should mention

 - Dynamic dispatch with vtables
 - Is it possible to emulate a C++ class?
 - Throwing exceptions

### When we talk about C we should mention

 - Creating C-like APIs (return uint32_t, use reference pointer buffers)

### Talking about both C/C++

 - Creating headers
 - Transforming data
 - Calling back into native code (taking callbacks)
 - Integrating `cargo`into `cmake`
 - Dynamicly linking std and dependencies in Rust projects (applicable to *all* projects)
 - And much more :)