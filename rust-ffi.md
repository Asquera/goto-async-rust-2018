<section> <h2><code>Rust</code>  💖  <code>C/C++</code></h2>

A memory-violating love story


## Who here

<div class="fragment" data-fragment-index="2">
* has used C/C++ in Rust code?
</div>

<div class="fragment" data-fragment-index="3">
* would call themselves a C developer?
</div>

<div class="fragment" data-fragment-index="4">
* woudl call themselves a C++ developer?
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
    reverse(cstr::from(value).unwrap()).into()
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

```console
 👉 (rayya) my_proj> ls headers/
 reverse-rs.h 
 👉 (rayya) my_proj> cat headers/reverse-rs.h
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

## Problems

* I don't like writing headers
* Reading data from C and back again
* Keeping state and memory management
* Creating "pretty" APIs

---

## The Result

<img src="thunder_demo.png"  height="512px" />

---

## More fancy things

* Use comments for descriptions
* Allow global arguments via attribute parameters
* Correctly parse inputs, throw errors at match stage

---

```rust
struct Thor;

/// An application that shoots lightning out of its hands
#[thunderclap(drunk: bool: "Thor drinks a lot")]
impl Thor {
    /// Say hello to someone
    fn hello(name: &str, times: Option<u128>) { /* ... */ }
    
    /// I...I can totally jump that far
    fn no_argument() { println!("Drunk: {}", Self::drunk()); }
}

fn main() {
    Thor::start();
}
```

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