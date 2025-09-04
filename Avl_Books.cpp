// AVL tree
#include <bits/stdc++.h>
using namespace std;

template<class T>
class AVL_tree {
public:
    struct Value {
        string name;
        string phone;
        string email;
    };

    struct Node {
        T id;
        Node* left;
        Node* right;
        int height;
        Value v;
        Node(T val, Value data) : id(val), left(NULL), right(NULL), height(1), v(data) {}
    };

    Node* root;
    AVL_tree() {
        root = NULL;
    }

    Node* insert(Node* node, T id, Value v) {
        if (node == NULL) {
            return new Node(id, v);
        }

        if (id < node->id) {
            node->left = insert(node->left, id, v);
        }
        else if (id > node->id) {
            node->right = insert(node->right, id, v);
        }
        else {
            return node;
        }

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = get_balance(node);

        if (balance > 1 && id < node->left->id) {
            return right_rotation(node);
        }
        else if (balance < -1 && id > node->right->id) {
            return left_rotation(node);
        }
        else if (balance > 1 && id > node->left->id) {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        else if (balance < -1 && id < node->right->id) {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }

        return node;
    }

    Node* GetSuccessor(Node* node) {
        Node* curr = node->right;
        while (curr && curr->left != NULL) {
            curr = curr->left;
        }
        return curr;
    }

    Node* remove(Node* node, T value) {
        if (node == NULL) {
            return node;
        }

        if (value < node->id) {
            node->left = remove(node->left, value);
        }
        else if (value > node->id) {
            node->right = remove(node->right, value);
        }
        else {
            if (node->left == NULL || node->right == NULL) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    delete node;
                    return NULL;
                }
                else {
                    *node = *temp;
                    delete temp;
                }
            }
            else {
                Node* successor = GetSuccessor(node);
                node->id = successor->id;
                node->v = successor->v;
                node->right = remove(node->right, successor->id);
            }
        }

        if (node == NULL)
            return node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = get_balance(node);

        if (balance > 1 && get_balance(node->left) >= 0)
            return right_rotation(node);
        if (balance > 1 && get_balance(node->left) < 0) {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
        if (balance < -1 && get_balance(node->right) <= 0)
            return left_rotation(node);
        if (balance < -1 && get_balance(node->right) > 0) {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node == NULL) {
            return;
        }
        inorder(node->left);
        cout << "\n";
        cout << "ID: " << node->id << "| Name: " << node->v.name << "| Phone: " << node->v.phone << "| Email: " << node->v.email << endl;
        inorder(node->right);
    }

    int getHeight(Node* node) {
        if (!node) {
            return 0;
        }
        return node->height;
    }

    void updateHeight(Node* node) {
        if (node)
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    Node* right_rotation(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* left_rotation(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    int get_balance(Node* node) {
        if (node == NULL) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    //////////////////////////////////////////////////////
    void displayTree(Node* node, int level = 0) {
        if (!node) {
            cout << "Tree is empty.\n";
            return;
        }
    
        if (node->left || node->right) {
            cout << "  " << node->id << endl;
            cout << " /     \\ " << endl;
            cout << (node->left ? to_string(node->left->id) : " ") << "   "
                 << (node->right ? to_string(node->right->id) : " ") << endl;
        } else {
            cout << node->id << endl;
        }
    }
    
    
    //////////////////////////////////////////////////////

    void add_contact() {
        Value v;
        int id;
        cout << "Enter unique ID (integer): ";
        cin >> id;
        cout << "Enter Name: ";
        getline(cin >> ws, v.name);
        cout << "Enter Phone : ";
        getline(cin >> ws, v.phone);
        cout << "Enter Email: ";
        getline(cin >> ws, v.email);
        bool f = search(root, id);
        if (f) {
            cout << "Contact with ID " << id << " already exists.\n";
        }
        else {
            root = insert(root, id, v);
            cout << "Contact added successfully.\n";
        }
    }

    void serch_id() {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        Node* val = search(root, id);
        if (val) {
            cout << "\nContact found:\nID: " << val->id
                 << "\nName: " << val->v.name
                 << "\nPhone: " << val->v.phone
                 << "\nEmail: " << val->v.email << "\n";
        }
        else {
            cout << "Contact not found.\n";
        }
    }

    void remove_id() {
        int id;
        cout << "Enter ID to delete it : ";
        cin >> id;
        Node* val = search(root, id);
        if (val) {
            root = remove(root, id);
            cout << "Contact deleted successfully.\n";
        }
        else {
            cout << "Contact not found.\n";
        }
    }

    void list_cont() {
        cout << "Contacts in Address Book (sorted by ID):\n";
        inorder(root);
    }

    void tree_struc() {
        cout << "Current AVL Tree:\n";
        displayTree(root);
    }

    Node* search(Node* node, int id) {
        if (node == NULL || node->id == id)
            return node;
        if (id < node->id)
            return search(node->left, id);
        return search(node->right, id);
    }
};

int main() {
    AVL_tree<int> bt;
    int ch;
    while (true) {
        cout << "\nAddress Book Application\n------------------------\n";
        cout << "1. Add New Contact\n2. Search for Contact\n3. Delete Contact (Optional)\n";
        cout << "4. List All Contacts (Sorted by ID)\n5. Display Current Tree Structure\n";
        cout << "------------------------\nEnter operation (1-5): ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            bt.add_contact();
            break;
        case 2:
            bt.serch_id();
            break;
        case 3:
            bt.remove_id();
            break;
        case 4:
            bt.list_cont();
            break;
        case 5:
            bt.tree_struc();
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    return 0;
}
