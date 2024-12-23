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
- **`make test`**: Run all unit tests with valgrind checks
- **`make test-single FILE="tests/test_crud_avl.c"`**: Run single file of unit tests with valgrind cecks as well

### **Checklist for Learnings:**
<details>
<summary><b>Step 1: Deepen Understanding of Binary Search Trees (BST)</b></summary>

- [x] Implement core BST operations:
  - [x] Insertion.
  - [x] Search.
  - [x] Deletion (delete node of 2 children not handled yet).
- [x] Calculate the **height** of the tree.
- [x] Implement **level-order traversal** (BFS) using a queue.
- [x] Ignore **duplicate values**
- [x] Implement functions to find the:
  - [x] **Predecessor** of a node.
  - [x] **Successor** of a node.
- [x] Implement full functionally of Deletion using (Predecessor & Successor)

</details>
<details>
<summary><b>Step 2: Move to Balanced Trees</b></summary>

- [ ] Learn and implement **AVL Trees**:
  - [ ] Add necessary methods (delete, traverse, find)
  - [x] Add rotations (left, right, left-right, right-left).
  - [ ] Maintain height balancing after insertion/deletion.
- [ ] Implement a **Red-Black Tree**:
  - [ ] Add node coloring (red or black).
  - [ ] Maintain balance after insertion/deletion.
  - [ ] Handle edge cases like double-red or double-black.

</details>
