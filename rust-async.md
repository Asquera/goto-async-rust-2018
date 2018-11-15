---
title: async in Rust 2018
subtitle: The future of `Future<T>`
transition: fade
---

I'm not Florian!

---

## `whoami(1)`

Katharina Fey ( `@spacekookie` )

* Active FOSS developer
* Avid tea drinker
* Hobbyist hardware maker 

---

I also make some attrocious puns

---

<img src="images/twitter_a.png" height=275px/>

<img src="images/twitter_b.png" height=250px/>

---

## `whoami(2)`

I do Rust things!

* Contributer of the CLI working group
* Member of the community team & `berlin.rs`
* Maintainer of several `use[ful|less]` libraries

---

## Rust

---

> Rust is a systems programming language that runs blazingly fast, prevents segfaults, and guarantees thread safety. 

---

<img src="images/confused_travolta.gif" height=350px />

---

## Safety

> * Memory safety
> * Thread safety

---

*spectrum of programming languages here*

---

## Memory Safety

---

* No garbage collector
* No manual memory allocations

---

**Ownership**

---

*some picture to show ownership*

---

**Borrowing**

---

*some picture to show borrowing*

---

## `Send` & `Sync`

> * Send = Can be sent between thread boundries safely
> * Sync = Can be *shared* between threads safely

---

```rust
struct MyFoo { ... }

fn main() {
    let foo = MyFoo { ... }; // Is neither Send nor Sync

    let mutex = Mutex::new(foo); // Provides Sync

    let arc = Arc::new(mutex); // Provides Send
}
```

---

**The type system enforces thread safety**

---

```rust
let tcp_listener = ...;
let state = ...; // Not Send or Sync

for connection in tcp_listener.incoming() {
    // Will not compile!
    thread::spawn(|| do_stuff(connection, state)); 
}
```

---

**Concurrency problems are made explicit**

---

## What about async then?

---

## What are Futures?

---

![](images/back_to_the_future.gif)

---

No, not that type of Futures

---

**`Future` = calculation that hasn't happened yet**

> * Is probably gonna happen at some point
> * Just keep asking

---

**Event Loop = runtime for `Future`s**

* Keeps polling `Future` until it is ready
* Runs your code whenever it can be run

---

**Other languages have this too**

---

**Future = Promise**

```js
Promise { -> foobar() }
    .and_then { -> barfoo() }
    .await()
```

---

## What about Rust then?

---

## Late 2013

---

### `libgreen`

---

![](images/libgreen_add.png)

* Rust had green threading support
* Enabled non-blocking IO

---

## Late 2014

---

**`libgreen` is dead, long live `libgreen`**

![](images/libgreen_remove.png)

---

Sorry, did I say ~~libgreen~~, I meant `mio.rs`

---

## `mio.rs`

<small>"Metal IO" 🤘</small>

---

* Light, non-blocking IO library
* Eventually developed an ecosystem around it

---

## Mid 2016

---

### `tokio-core`

---

* Wraps around `mio.rs`
* Futures abstraction
* Event reactor

---

## tokio

> * An event loop
> * Futures abstraction
> * Lots of utilities

---

*small code example*

---

**Thread safety still enforced by the typesystem**

---

## tokio

```rust

```

---


## That's it

Follow me on twitter **`@spacekookie`**

Or: **`kookie@spacekookie.de`**

<br/>

#### Thanks to my employers

* I do *Rust* work at **Ferrous Systems**
* I do *Distributed Systems* at **Asquera**