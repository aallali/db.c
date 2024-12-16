# db.c

The goal of this program is to get me comfortable with the fundamentals of database internals. 
By that, I mean the data structures (B-Tree, B+Tree, etc.), indexing, hashing, storage, and memory management. 
I aim to implement a basic non-relational database, starting with an in-memory approach and later adding persistence.

I previously started a similar project ([safinaDB](https://github.com/aallali/safinaDB)) in Rust. 
However, I realized that I lacked understanding of kernel-level execution and database internals, 
so I decided to go back and build things brick by brick.

### Build and Execution Commands:
- **`make`**: Compiles the source code.
- **`db.bin`**: The compiled executable binary.
- **`make run`**: Run the compiled executable binary.
- **`make leak`**: Runs the binary with `valgrind` to check for memory leaks.
- **`make clean`**: Removes all generated build files and binaries.
