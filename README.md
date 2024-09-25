### KD Tree Project - 3D KD-Tree Implementation in C++

This project implements a 3-dimensional KD-Tree (K-Dimensional Tree) in C++. A KD-Tree is a binary search tree used for organizing points in a k-dimensional space, useful for search and range queries in multi-dimensional data.

#### Key Features:
- **Node Structure**: Each node contains a point in 3D space (`k = 3`), and pointers to its left and right subtrees.
- **Insertion**: Points are inserted based on the current depth, alternating between dimensions.
- **Search**: Efficiently searches for a given point in 3D space.
- **Nearest neighbor search**: efficiently finds the closest point to a query in multi-dimensional space by recursively partitioning the data and minimizing the number of comparisons.
- **Deletion**: Removes a point from the tree while maintaining the KD-Tree structure.
- **Find Minimum**: Retrieves the minimum point in a specified dimension.
- **Traversal**: Displays points using Inorder, Preorder, and Postorder traversal methods.

#### User Interaction:
A simple menu-based interface allows users to:
- Insert new points.
- Search for existing points.
- Delete points from the tree.
- Display the tree contents in different traversal orders.
- Find the minimum value in any dimension.

This project serves as a practical demonstration of KD-Tree functionality and can be used for tasks such as **nearest neighbor search, range queries, and spatial partitioning** in 3D applications.
KD Trees are widely used in computer graphics, machine learning, and spatial databases where multidimensional data needs to be processed efficiently.
### Team Members
- 1.Parikshit V
- 2.Om Prakash P
---
