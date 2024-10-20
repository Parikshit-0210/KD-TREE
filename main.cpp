#include<bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <limits>
#include<algorithm>
using namespace std;

const int k = 2;
const int MAX_POINTS = 100; // Maximum number of points for range search

// A structure to represent node of kd tree
struct Node
{
    int point[k]; // To store k dimensional point
    Node *left, *right;
};

// A method to create a node of K D tree
struct Node* newNode(int arr[])
{
    struct Node* temp = new Node;

    for (int i=0; i<k; i++)
        temp->point[i] = arr[i];

    temp->left = temp->right = NULL;
    return temp;
}

// Inserts a new node and returns root of modified tree
// The parameter depth is used to decide axis of comparison
Node *insertRec(Node *root, int point[], unsigned depth)
{
    // Tree is empty?
    if (root == NULL)
        return newNode(point);

    // Calculate current dimension (cd) of comparison
    unsigned cd = depth % k;

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

// Function to insert a new point with given point in
// KD Tree and return new root. It mainly uses above recursive
// function "insertRec()"
Node* insert(Node *root, int point[])
{
    return insertRec(root, point, 0);
}

// A utility method to determine if two Points are same
// in K Dimensional space
bool arePointsSame(int point1[], int point2[])
{
    // Compare individual coordinate values
    for (int i = 0; i < k; ++i)
        if (point1[i] != point2[i])
            return false;

    return true;
}

// Searches a Point represented by "point[]" in the K D tree.
// The parameter depth is used to determine current axis.
bool searchRec(Node* root, int point[], unsigned depth)
{
    // Base cases
    if (root == NULL)
        return false;
    if (arePointsSame(root->point, point))
        return true;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

// Searches a Point in the K D tree. It mainly uses
// searchRec()
bool search(Node* root, int point[])
{
    // Pass current depth as 0
    return searchRec(root, point, 0);
}

// A utility function to find minimum of three integers
Node *minNode(Node *x, Node *y, Node *z, int d)
{
    Node *res = x;
    if (y != NULL && y->point[d] < res->point[d])
        res = y;
    if (z != NULL && z->point[d] < res->point[d])
        res = z;
    return res;
}

// Recursively finds minimum of d'th dimension in KD tree
// The parameter depth is used to determine current axis.
Node *findMinRec(Node* root, int d, unsigned depth)
{
    // Base cases
    if (root == NULL)
        return NULL;

    // Current dimension is computed using current depth and total
    // dimensions (k)
    unsigned cd = depth % k;

    // Compare point with root with respect to cd (Current dimension)
    if (cd == d)
    {
        if (root->left == NULL)
            return root;
        return findMinRec(root->left, d, depth+1);
    }

    // If current dimension is different then minimum can be anywhere
    // in this subtree
    return minNode(root,
                   findMinRec(root->left, d, depth+1),
                   findMinRec(root->right, d, depth+1), d);
}

// A wrapper over findMinRec(). Returns minimum of d'th dimension
Node *findMin(Node* root, int d)
{
    // Pass current level or depth as 0
    return findMinRec(root, d, 0);
}

// Copies point p2 to p1
void copyPoint(int p1[], int p2[])
{
    for (int i=0; i<k; i++)
        p1[i] = p2[i];
}

// Function to delete a given point 'point[]' from tree with root
// as 'root'. depth is current depth and passed as 0 initially.
// Returns root of the modified tree.
Node *deleteNodeRec(Node *root, int point[], int depth)
{
    // Given point is not present
    if (root == NULL)
        return NULL;

    // Find dimension of current node
    int cd = depth % k;

    // If the point to be deleted is present at root
    if (arePointsSame(root->point, point))
    {
        // 2.b) If right child is not NULL
        if (root->right != NULL)
        {
            // Find minimum of root's dimension in right subtree
            Node *min = findMin(root->right, cd);

            // Copy the minimum to root
            copyPoint(root->point, min->point);

            // Recursively delete the minimum
            root->right = deleteNodeRec(root->right, min->point, depth+1);
        }
        else if (root->left != NULL) // same as above
        {
            Node *min = findMin(root->left, cd);
            copyPoint(root->point, min->point);
            root->right = deleteNodeRec(root->left, min->point, depth+1);
        }
        else // If node to be deleted is leaf node
        {
            delete root;
            return NULL;
        }
        return root;
    }

    // 2) If current node doesn't contain point, search downward
    if (point[cd] < root->point[cd])
        root->left = deleteNodeRec(root->left, point, depth+1);
    else
        root->right = deleteNodeRec(root->right, point, depth+1);
    return root;
}

// Function to delete a given point from K D Tree with 'root'
Node* deleteNode(Node *root, int point[])
{
    // Pass depth as 0
    return deleteNodeRec(root, point, 0);
}
bool isInRange(int point[], int low[], int high[]) {
    for (int i = 0; i < k; i++) {
        if (point[i] < low[i] || point[i] > high[i])
            return false;
    }
    return true;
}

// Recursive function for range search
void rangeSearchRec(Node* root, int low[], int high[], int result[][k], int& count, unsigned depth) {
    if (root == NULL)
        return;

    // Check if current node's point is in range
    if (isInRange(root->point, low, high)) {
        for (int i = 0; i < k; i++) {
            result[count][i] = root->point[i]; // Store the point in the result array
        }
        count++; // Increment the count of found points
    }

    unsigned cd = depth % k;

    // Check left subtree
    if (low[cd] < root->point[cd]) {
        rangeSearchRec(root->left, low, high, result, count, depth + 1);
    }

    // Check right subtree
    if (high[cd] > root->point[cd]) {
        rangeSearchRec(root->right, low, high, result, count, depth + 1);
    }
}

// Function to perform range search in KD tree
void rangeSearch(Node* root, int low[], int high[], int result[][k], int& count) {
    count = 0; // Initialize count to zero
    rangeSearchRec(root, low, high, result, count, 0);
}

// Function to calculate squared distance between two points
double squaredDistance(int point1[], int point2[]) {
    double dist = 0.0;
    for (int i = 0; i < k; i++) {
        dist += pow(point1[i] - point2[i], 2);
    }
    return dist;
}

// Nearest neighbor search recursive function
void nearestNeighborRec(Node* root, int target[], Node*& bestNode,
                        double& bestDistSq, unsigned depth) {

    if (root == NULL)
        return;

    double distSq = squaredDistance(root->point, target);

    // Update best node and distance if current node is closer
    if (distSq < bestDistSq) {
        bestDistSq = distSq;
        bestNode = root;
    }

    unsigned cd = depth % k;

    // Determine which side of the tree to search first
    Node *nextBranch = target[cd] < root->point[cd] ? root->left : root->right;
    Node *otherBranch = target[cd] < root->point[cd] ? root->right : root->left;

    nearestNeighborRec(nextBranch, target, bestNode, bestDistSq, depth + 1);

    // Check if we need to explore the other branch
    if ((target[cd] - root->point[cd]) * (target[cd] - root->point[cd]) < bestDistSq) {
        nearestNeighborRec(otherBranch, target, bestNode, bestDistSq, depth + 1);
    }
}

// Function to perform nearest neighbor search in KD tree
Node* nearestNeighbor(Node* root, int target[]) {
    Node* bestNode = NULL;
    double bestDistSq = 10000000000;

    nearestNeighborRec(root, target, bestNode, bestDistSq, 0);

    return bestNode;
}

// Utility function to display points in KD tree using inorder traversal
void displayInorder(Node* root)
{
    if (root == NULL)
        return;

    // Display left subtree
    displayInorder(root->left);

    // Display current node
    cout << "(";
    for (int i = 0; i < k - 1; i++)
        cout << root->point[i] << ", ";
    cout << root->point[k - 1] << ")\n";

    // Display right subtree
    displayInorder(root->right);
}
// Utility function to display points in KD tree using preorder traversal
void displayPreorder(Node* root)
{
    if (root == NULL)
        return;

    // Display current node
    cout << "(";
    for (int i = 0; i < k - 1; i++)
        cout << root->point[i] << ", ";
    cout << root->point[k - 1] << ")\n";

    // Display left subtree
    displayPreorder(root->left);

    // Display right subtree
    displayPreorder(root->right);
}
// Utility function to display points in KD tree using postorder traversal
void displayPostorder(Node* root)
{
    if (root == NULL)
        return;

    // Display left subtree
    displayPostorder(root->left);

    // Display right subtree
    displayPostorder(root->right);

    // Display current node
    cout << "(";
    for (int i = 0; i < k - 1; i++)
        cout << root->point[i] << ", ";
    cout << root->point[k - 1] << ")\n";
}

// Driver program to test above functions
int main()
{
    struct Node *root = NULL;
    int points[][k] = {{30, 40}, {5, 25}, {70, 70},
                        {10, 12}, {50, 30}, {35, 45}};

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a point\n";
        cout << "2. Search for a point\n";
        cout << "3. Delete a point\n";
        cout << "4. Range Search\n";
        cout << "5. Nearest Neighbor Search\n";
        cout << "6. Display points (Inorder)\n";
        cout << "7. Display points (Preorder)\n";
        cout << "8. Display points (Postorder)\n";
        cout << "9. Find minimum of a dimension\n";
        cout << "10.Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int point[k];
                cout << "Enter point coordinates: ";
                for (int i = 0; i < k; i++)
                    cin >> point[i];
                root = insert(root, point);
                cout << "Point inserted successfully!\n";
                break;
            }
            case 2: {
                int point[k];
                cout << "Enter point to search for: ";
                for (int i = 0; i < k; i++)
                    cin >> point[i];
                if (search(root, point))
                    cout << "Point found!\n";
                else
                    cout << "Point not found!\n";
                break;
            }
            case 3: {
                int point[k];
                cout << "Enter point to delete: ";
                for (int i = 0; i < k; i++)
                    cin >> point[i];
                root = deleteNode(root, point);
                cout << "Point deleted successfully!\n";
                break;
            }
            case 4: { // Range Search
                 int low[k], high[k];
                 cout << "Enter lower bound coordinates: ";
                 for (int i = 0; i < k; ++i) cin >> low[i];
                 cout << "Enter upper bound coordinates: ";
                 for (int i = 0; i < k; ++i) cin >> high[i];

                 int result[MAX_POINTS][k], count;
                 rangeSearch(root , low , high , result , count);

                 cout << "Points in range [" << low[0] << ", " << high[0] << "] x ["
                      << low[1] << ", " << high[1] << "]:" << endl;

                 for (int i = 0; i < count; ++i) {
                     cout << "(" << result[i][0] << ", " << result[i][1] << ")" << endl;
                 }
                 break;
             }
             case 5: { // Nearest Neighbor Search
                 int target[k];
                 cout << "Enter coordinates of the target point: ";
                 for (int i = 0; i < k; ++i) cin >> target[i];

                 Node* nearestNode = nearestNeighbor(root , target);

                 if(nearestNode != NULL) {
                     cout << "Nearest neighbor to ("
                          << target[0] << ", "
                          << target[1] << ") is ("
                          << nearestNode->point[0]
                          << ", "
                          << nearestNode->point[1]
                          << ")"
                          << endl;
                 } else {
                     cout << "No points in the KD Tree."
                          << endl;
                 }
                 break;
             }
            case 6: {
                cout << "Points in the KD tree (Inorder):\n";
                displayInorder(root);
                break;
            }
            case 7: {
                cout << "Points in the KD tree (Preorder):\n";
                displayPreorder(root);
                break;
            }
            case 8: {
                cout << "Points in the KD tree (Postorder):\n";
                displayPostorder(root);
                break;
            }
            case 9: {
                int dim;
                cout << "Enter dimension to find minimum: ";
                cin >> dim;
                if (dim >= 0 && dim < k) {
                    Node* minNode = findMin(root, dim);
                    cout << "Minimum of dimension " << dim << " is (";
                    for (int i = 0; i < k - 1; i++)
                        cout << minNode->point[i] << ", ";
                    cout << minNode->point[k - 1] << ")\n";
                } else {
                    cout << "Invalid dimension!\n";
                }
                break;
            }
            case 10: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice! Please try again.\n";
                break;
            }
        }
    } while (choice != 10);

    return 0;
}
