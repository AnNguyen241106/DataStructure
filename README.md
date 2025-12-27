# Data Structures Implementation

This repository contains custom implementations of fundamental data structures, focusing on memory efficiency and algorithmic performance.

---

## 1. Dynamic Array
A contiguous block of memory that automatically resizes when it reaches capacity.
* **Logic:** When the array is full, a new array is allocated (typically $2 \times$ the size) and elements are copied over.
* **Time Complexity:** $O(1)$ amortized for insertions, $O(1)$ for access by index.

---

## 2. Stack (LIFO)
A "Last-In, First-Out" structure where elements are added and removed from the same end.

* **Operations:** `push`, `pop`, `peek`.
* **Use Cases:** Function call management (Recursion), Undo mechanisms, Expression parsing.

---

## 3. Queue (FIFO)
A "First-In, First-Out" structure where elements enter at the back and exit from the front.

* **Operations:** `enqueue` (add to rear), `dequeue` (remove from front).
* **Use Cases:** CPU scheduling, IO Buffers, Breadth-First Search (BFS).

---

## 4. Binary Heap (Min/Max)
A complete binary tree usually implemented using an array. It is used to quickly find the highest or lowest priority element.

* **Heap Property:** For a Min-Heap, the value of the parent node is $\le$ the values of its children.
* **Array Mapping:**
    * Parent: `(i - 1) / 2`
    * Left Child: `2i + 1`
    * Right Child: `2i + 2`

---

## 5. AVL Tree (Self-Balancing BST)
A Binary Search Tree that maintains a "Balance Factor" to ensure the height remains logarithmic, preventing the tree from becoming a linked list.

* **Balance Factor ($BF$):**
    $$BF = \text{height}(left\_subtree) - \text{height}(right\_subtree)$$
* **Requirement:** $|BF| \le 1$. If violated, the tree performs rotations (LL, RR, LR, RL) to rebalance.

---

## Performance Comparison

| Data Structure | Access | Search | Insertion | Deletion |
| :--- | :--- | :--- | :--- | :--- |
| **Dynamic Array** | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Stack** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Queue** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Binary Heap** | $O(1)$ | $O(n)$ | $O(\log n)$ | $O(\log n)$ |
| **AVL Tree** | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ | $O(\log n)$ |

---

## How to Run
1. Clone the repository.
2. Compile the source files (e.g., `g++ main.cpp -o ds_demo`).
3. Run the executable `./ds_demo`.
