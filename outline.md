


Who am I? Why am I giving this talk? 
Thanks for my employer and Mozilla for allowing me to be at RustConf (specific to Portland)

We've all seen the sales pitch for easy FFI from Rust. What does that mean?

Who has used FFI features before at all? (native code in Rust), who codes mostly C and who codes mostly in C++?

Start at the basics: what's an ABI? Application Binary Interface; much like an API but only used by linkers, not humans.
Has a binary layout that defines how to call the function. The C ABI is stable, the Rust ABI is _not_
C++ ABI is also not stable and as such, only FFI via the C ABI is supported (more in detail)

(maybe show an example for an ABI)

`extern "C"` is a way to specify the ABI for a function (`extern "Rust"` is default)

So how to use this? Calling C from Rust is easy. extern "C" block, using `build.rs` to link some C code.
Many crates available to make this easier: gcc, clang, cmake, meson, ...
Important process: making data C compatible.

This process is well documented. Booooring

===

We want to embed Rust into an existing C/C++ project. Show a minimal example: small Rust function that uses a C-ABI. 
Show cargo flags, show external build tool that's needed (use cmake because easy)

`repr(C)` is the same as `extern "C"` but for structures/ enums. union is always c compatible (requires unsafe)

Some problems that become apparent

- Writing headers is boring (throw tooling at it)
- Dealing with errors
- Keeping state and memory safety
- Creating "pretty API's"

## Easiest first:

Don't want to write C headers and keep them in sync? **Don't**, use `cbindgen` instead. 
It's like bindgen but the other way around.

## Keeping state:

By default Rust puts everything on the stack. This isn't really useful when 
dealing with C because it has no concept of lifetimes for data.
So instead: put it in a `Box<T>`

This is Rusts heap applicated pointer, meaning if a function returns `Box<T>`, 
C will then simply have a pointer to this thing.

Let's address the elephant in the room though: API design. Rust uses Option<T> or Result<T, E>
to communicate when things go wrong. C and C++ have different patterns, so let's talk about errors.

Also important: past our Rust API, there is no memory safety. Treat all comings and goings as unsafe. 
They are unsafe!

## Error handling:

There are things that are possible to do, but not feasable or "production-ready". Using errno to communicate last error
or just return uint32_t (or unsigned int) from functions. Two religions on how to handle errors.

~ fill in more details here ~

## Pretty APIs

So...we've already made some assumptions about what the API for our crate should look like.
It's a very C heavy style, using return values or errno's to communicate errors. Whenever we use this
from some C++ code, we wrap those errors into exceptions (or other errors) on the native code side.

Don't be afraid to use enums; they're simply tagged unions in C-land and can solve a lot of your problems!

Let's talk about what a pretty API is, and yes by saying it that way I'm practically inviting people to flame me.
Let's still do it though.

So in C it's kinda easy. Use one of the patterns outlined earlier about errors

 - errno
 - or int foobar(... params ...)

So what about C++? Can we pretend to be a C++ module that happens to be called via some C code?

Well...

Not quite, but: create a normal C API as you would. Then dynamically load the object, 
map C++ class functions to your Rust functions via a vtable and you've almost
got the same thing. (almost)

(Actually don't! It works, but it's very unstable and not reliable)

Much better: wrap your Rust/C API in C++ objects via RAII.

Next:

Can you throw C++ exceptions from Rust?

😱

Well...

Kinda?!

`try`/`throw` keyword is replaced by the compiler setjmp/longjmp (kinda)
Calls into libc++ can be made from Rust
It works (kinda) – lots of undefined behaviour