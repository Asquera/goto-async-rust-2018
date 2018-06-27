<script src="//twemoji.maxcdn.com/2/twemoji.min.js?11.0"></script>
<section> <h2><code>Rust</code>  💖  <code>C/C++</code></h2>

A memory-violating love story


## Who here

<div class="fragment" data-fragment-index="2">
* has used `C/C++` in `Rust` code?
</div>

<div class="fragment" data-fragment-index="3">
* would call themselves a C developer?
</div>

<div class="fragment" data-fragment-index="4">
* would call themselves a C++ developer?
</div>

</section>

---

## Boring FFi

- Declare some headers to native code
- Use `unsafe` a lot
- Make data C-compatible

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

---

## Turning tables

* `extern "C"` declares an ABI in both directions
* Use `#[no_mangle]` to preserve the function name

```rust
use unicode_segmentation::UnicodeSegmentation;

#[no_mangle]
extern "C" fn reverse(const *c_char) -> const *c_char {
    /* ... TODO ... */
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
    printf("%s\n", reverse("Hello, RustConf 👩🏽‍💻!"));
}
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

### YES

--- 

### But please don't

* Very unsafe
* *Very* dependant on the compiler you use
* The world doesn't need more exceptions

---

### But how?

* `throw` keyword is replaced to `libc++` call by compiler
* Use `libc++` directly, then C++ "higher up" catches

```rust
// TODO: Implement this with Rust
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
