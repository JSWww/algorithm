#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int x;
    int y;
    int n;
    Node* left;
    Node* right;
};

bool comp(Node& a, Node& b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    
    return a.y > b.y;
}

void make_tree(Node& root, Node& child) {
    if (root.x > child.x) {
        if (root.left == NULL) {
            root.left = &child;
        } else {
            make_tree(*root.left, child);
        }
    } else {
        if (root.right == NULL) {
            root.right = &child;
        } else {
            make_tree(*root.right, child);
        }
    }
}

void preorder(Node& root, vector<vector<int>>& answer) {
    answer[0].push_back(root.n);
    if (root.left != NULL) preorder(*root.left, answer);
    if (root.right != NULL) preorder(*root.right, answer);
}

void postorder(Node& root, vector<vector<int>>& answer) {
    if (root.left != NULL) postorder(*root.left, answer);
    if (root.right != NULL) postorder(*root.right, answer);
    answer[1].push_back(root.n);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);
    vector<Node> nodes;
    Node root;
    
    for (int i = 0; i < nodeinfo.size(); i++) {
        Node node;
        node.x = nodeinfo[i][0];
        node.y = nodeinfo[i][1];
        node.n = i + 1;
        node.left = NULL;
        node.right = NULL;
        nodes.push_back(node);
    }
    
    sort(nodes.begin(), nodes.end(), comp);
    
    root = nodes[0];
    
    for (int i = 1; i < nodes.size(); i++) {
        make_tree(root, nodes[i]);
    }
    
    preorder(root, answer);
    postorder(root, answer);
    
    return answer;
}
