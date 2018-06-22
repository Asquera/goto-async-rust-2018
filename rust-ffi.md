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
* Use `#[no_mangle]` to preserve the function name as-is

```rust
use unicode_segmentation::UnicodeSegmentation;

#[no_mangle]
extern "C" fn reverse(const *c_char) -> const *c_char {
    /* ... TODO ... */
}
```

---

## Turning tables (part 2)

* But...how do we call this?

<div class="fragment" data-fragment-index="2">

```C
// Safely reverse a unicode string
const char *reverse(const char *in);
```

```C
#include "reverse-rs.h"
void main() {
    printf("%s\n", reverse("Hello, RustConf 💝!"));
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
::std::mem::forget(t);
```
</div>

---

## Creating "pretty" APIs

What constitutes a "pretty" API in each language?

---

```C
pr_mod_ctx ctx;
int ret = proj_module_init(&ctx, a, b, /* ... */);
if (ret) {
    /* Handle error explicitly */
}
```

---

```Cpp
MyObj obj = new MyObj(a, b, /* .. */);
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

<section> 
<h2> 😱 </h2>
</section>

---

### YES

--- 

### But please don't

- Very unsafe
- *Very* dependant on the compiler you use

---

### Some Drawbacks

* Requires nightly rust because `proc_macro`
* Makes a lot of assumptions about use-cases

---

### Lots of work left to do

* Error messages sometimes less than awesome
* sub-sub-commands not supported (yet)
* No application state with `self` (yet)
* Non-optional flags are always in-order

---

## In Conclusion

* [github.com/spacekookie/thunder](https://github.com/spacekookie/thunder)
* [crates.io/crates/thunder](https://crates.io/crates/thunder)

<br/><br/>

* https://spacekookie.de
* https://twitter.com/spacekookie