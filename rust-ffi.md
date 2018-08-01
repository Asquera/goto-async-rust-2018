---
title: Rust  💖  C/C++
subtitle: A memory-violating love story
---

## `whoami(1)`

Katharina Fey (`@spacekookie`)

<br/>

Thanks to

* My company **Ferris Systems**
* Mozilla 🧡

---

## `whoami(2)`

* Contributer to the CLI-WG
* Author of (too) many `use[ful|less]` crates
* Hobbyist hardware maker

---

## `whoami(3)`

* Core contributer to `qaul.net`
  * ~500kloc of C99
  * Primary inspiration for this talk

---

## Why

<br/>

Rust promises easy FFI to C code

What does this mean?

<div class="fragment" data-fragment-index="2">
What do we *want* it to mean?
</div>

---

## Question time

<br/>

Who here

> * has used `C/C++` in `Rust` code?
> * would call themselves a C developer?
> * would call themselves a C++ developer?

---

## ABI

Application Binary Interface

<br/>

* Defines the function signature (in binary)
* Much like an API but for linkers

---

## ABI

```rust
extern "C" {
    // ...
}

#[repr(C)]
struct Foo { /* ... */ }

#[repr(C)]
enum Bar { /* ... */ }

union OhYea { /* unions are just cool by default */ }
```

---

## ABI

<img src="images/ABIs.png"  height=545px>

---

## C code from Rust

<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>
<br/>

---

## Boring FFi

<div class="fragment" data-fragment-index="2">

* Bind to native API with `extern` functions
* Wrap function calls in `unsafe`
* Make data C-compatible
</div>

<div class="fragment" data-fragment-index="3">

```rust
extern "C" {
    fn reverse(const *c_char) -> const *c_char;
}

unsafe fn danger_zone<'a>(value: &'a str) -> &'a str {
    CStr::from_ptr(
        reverse(
            CStr::from(value).unwrap()
        )
    ).to_str()
}
```

</div>

---

## Turning tables

* `extern "C"` declares an ABI in both directions
* Use `#[no_mangle]` to preserve the function name

```rust
#[no_mangle]
pub extern "C" fn reverse(word: *const c_char) -> *const c_char {
    let mut s: String = match unsafe { 
            CStr::from_ptr(word) 
        }.to_str() {
            Ok(s) => s,
            _ => return unsafe { ::std::mem::uninitialized() },
    }.into();
    ur::reverse_grapheme_clusters_in_place(&mut s);
    println!("{}", s);
    CString::new(s).unwrap().into_raw()
}
```

---

## Turning tables (part 2)

* How do we call this?

<div class="fragment" data-fragment-index="2">

```C
// Safely reverse a unicode string
const char *reverse(const char *in);
```

```C
#include "reverse-rs.h"
void main() {
    printf("'%s' reversed: '%s' \n", greeting, reverse(greeting));
}
```

</div>

<div class="fragment" data-fragment-index="3">
```console```
'привет Rustfest 👩🏽‍💻' reversed: '💻👩🏽‍ tseftsuR тевирп'
```
</div>



## Some Problems

* Writing headers is boooring
* Reading data from C and back again
* Keeping state and memory management
* Creating "pretty" APIs

---

## Memory management

Put your troubles in a box ✨

```rust
#[repr(C)]
struct MyThing {
    /* ... */
}

#[no_mangle]
extern "C" fn make_thing() -> Box<MyThing> {
    Box::new(MyThing {
        /* ... */
    })
}
```

---

## Memory management (part 2)

C:

```C
void main() {
    MyThing *t = make_thing();
    free(t);
}
```

<div class="fragment" data-fragment-index="2">
Rust:

```rust
::std::mem::forget(thing);
```
</div>

---

## Creating "pretty" APIs

What does that mean anyway?

---

C

```C
pr_mod_ctx ctx; // or *ctx
int ret = proj_module_init(&ctx, a, b, /* ... */);
if (ret) {
    /* Handle error explicitly */
    goto fail;
}
```

```C
ret = proj_module_function(ctx, a, b, /* ... */);
if (ret) {
    /* Handle error explicitly */
    goto fail;
}
```

---

C++

```Cpp
MyObj obj = MyObj::create(a, b, /* .. */);
if (obj == null) {
    /* handle errors explicitly */
}
```

```Cpp
class MyObj {
public:
  MyObj() {
    throw CantBeBotheredException();
  }
}

try {
    MyObj obj = new MyObj(a, b, /* .. */);
} catch (CantBeBotheredException *e) {
    /* handle errors implicitly */
}
```

---

### Can you throw a `C++` exception from Rust?

---

### 😱

---

### Well

---

### That depends...

<div class="fragment" data-fragment-index="2">
* An exception is a setjmp/ longjmp pair on stack
* Compiler swaps `throw` keyword with `libc++` calls
* Those unwind the stack to find a `setjmp` marker
* Resuming execution from that point
</div>

---

### But how?


---

### Exception ABI

```
typedef _Unwind_Reason_Code (*_Unwind_Stop_Fn)
    (int version,
        _Unwind_Action actions,
        uint64 exceptionClass,
        struct _Unwind_Exception *exceptionObject,
        struct _Unwind_Context *context,
        void *stop_parameter );

_Unwind_Reason_Code _Unwind_ForcedUnwind
    ( struct _Unwind_Exception *exception_object,
        _Unwind_Stop_Fn stop,
        void *stop_parameter );
```

---

### Anyway

```rust
/// Ok(...) or Err(...)
fn foo() -> Result<T, Error>;

/// Some(...) or None
fn bar() -> Option<T>;
```

How does `None` compare to `null`?

---

### Emulating `Option<T>`

```rust
fn bar() -> Option<const *c_char> { /* ... */ }
```

```Cpp
char *str = bar();
if(str == null) {
    /* this is None */
}
```

---

### Emulating `Result<T,E>`

* This is a lot harder
* There are `C++` implementations of `Result`

---

### So what about C?

```C
int ret = some_rust_function(&ctx, "abc", 42);
```

C pointers become `const *c_void`

```rust
#[no_mangle]
extern "C" fn some_rust_function(
    ctx: const *c_void, 
    s: const *c_char, 
    num: uint32_t)
{
    /* ... */
}

```

--- 

But: `c_void` just refers to a Rust type, right?

```rust
#[no_mangle]
extern "C" fn some_rust_function(
   /* ... */
{
    let ctx: &mut MyState = unsafe {
        &mut *ctx as &mut MyState
    };

    ctx.some_mut_function();
}
```

---

### Generating headers

* `cbindgen` generates C-headers from Rust code
* Can be hooked into the build-pipline
  * Don't keep headers in the repo – generate them!

---

### Some thoughts on linking

* Rust links statically by default
* Each `foo.so` would be several MB big!
* `-C prefer-dynamic` to the rescue
  * Dynamically link libraries
  * Requires you to link them together yourself in your build pipeline