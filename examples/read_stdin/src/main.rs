use std::io::BufReader;
use tokio::io;
use tokio::prelude::*;

fn main() {
    let stdin = io::stdin();
    let mut stdout = io::stdout();

    let reader = BufReader::new(stdin);

    let buffer = Vec::new();
    let fut = io::read_until(reader, b'\n', buffer)
      .and_then(move |(stdin, buffer)| {
          stdout.write_all(&buffer).map_err(|e| panic!(e))
      }).map_err(|e| panic!(e));

    tokio::run(fut);
}
