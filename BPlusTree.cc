struct Node;

struct TernaryNode {
    Node *kid_[3];
    int key_[2];
};

struct BinaryNode {
    Node *kid_[2];
    int key_;
};

struct Node {
    union {
        TernaryNode ternary;
        BinaryNode binary;
    };
    bool is_ternay;
};

struct Split {
    Node *left;
    Node *right;
    int key;
};

struct InsertRes {
    Split split;
    bool is_split;
};

InsertRes InsertValue(Node *p, int key) {
    InsertRes s;
    s.is_split = false;

    if (!p) {
        s.is_split = true;
        s.split.left = nullptr;
        s.split.right = nullptr;
        s.split.key = key;
        return s;
    }

    if (p->is_ternay) {
        if (key < p->ternary.key_[0]) {
            if (p->ternary.kid_[0]) {
                auto r = InsertValue(p->ternary.kid_[0], key);
                if (r.is_split) {
                    s.is_split = true;
                    auto content = *p;
                    s.split.left = new Node();
                    s.split.left->is_ternay = false;
                    s.split.left->binary.key_ = r.split.key;
                    s.split.left->binary.kid_[0] = r.split.left;
                    s.split.left->binary.kid_[1] = r.split.right;
                    s.split.right = p;
                    s.split.right->is_ternay = false;
                    s.split.right->binary.key_ = content.ternary.key_[1];
                    s.split.right->binary.kid_[0] = content.ternary.kid_[1];
                    s.split.right->binary.kid_[1] = content.ternary.kid_[2];
                    s.split.key = content.ternary.key_[0];
                }
            } else {
                s.is_split = true;
                auto content = *p;
                s.split.left = new Node();
                s.split.left->is_ternay = true;
                s.split.left->ternary.kid_[0] = nullptr;
                s.split.left->ternary.key_[0] = key;
                s.split.left->ternary.kid_[1] = nullptr;
                s.split.left->ternary.key_[1] = content.ternary.key_[0];
                s.split.left->ternary.kid_[2] = nullptr;
                s.split.right = p;
                s.split.right->is_ternay = false;
                s.split.right->binary.kid_[0] = nullptr;
                s.split.right->binary.key_ = content.ternary.key_[1];
                s.split.right->binary.kid_[1] = nullptr;
                s.split.key = content.ternary.key_[0];
            }
        } else if (key == p->ternary.key_[0]) {
            // nothing
        } else if (key < p->ternary.key_[1]) {
            if (p->ternary.kid_[1]) {
                auto r = InsertValue(p->ternary.kid_[1], key);
                if (r.is_split) {
                    s.is_split = true;
                    auto content = *p;
                    s.split.left = new Node();
                    s.split.left->is_ternay = false;
                    s.split.left->binary.key_ = content.ternary.key_[0];
                    s.split.left->binary.kid_[0] = content.ternary.kid_[0];
                    s.split.left->binary.kid_[1] = r.split.left;
                    s.split.right = p;
                    s.split.right->is_ternay = false;
                    s.split.right->binary.key_ = content.ternary.key_[1];
                    s.split.right->binary.kid_[0] = r.split.right;
                    s.split.right->binary.kid_[1] = content.ternary.kid_[2];
                    s.split.key = r.split.key;
                }
            } else {
                s.is_split = true;
                auto content = *p;
                s.split.left = new Node();
                s.split.left->is_ternay = true;
                s.split.left->ternary.kid_[0] = nullptr;
                s.split.left->ternary.key_[0] = content.ternary.key_[0];
                s.split.left->ternary.kid_[1] = nullptr;
                s.split.left->ternary.key_[1] = key;
                s.split.left->ternary.kid_[2] = nullptr;
                s.split.right = p;
                s.split.right->is_ternay = false;
                s.split.right->binary.kid_[0] = nullptr;
                s.split.right->binary.key_ = content.ternary.key_[1];
                s.split.right->binary.kid_[1] = nullptr;
                s.split.key = key;
            }
        } else if (key == p->ternary.key_[1]) {
            // nothing
        } else {
            if (p->ternary.kid_[2]) {
                auto r = InsertValue(p->ternary.kid_[2], key);
                if (r.is_split) {
                    s.is_split = true;
                    auto content = *p;
                    s.split.left = p;
                    s.split.left->is_ternay = false;
                    s.split.left->binary.key_ = content.ternary.key_[0];
                    s.split.left->binary.kid_[0] = content.ternary.kid_[0];
                    s.split.left->binary.kid_[1] = content.ternary.kid_[1];
                    s.split.right = new Node();
                    s.split.right->is_ternay = false;
                    s.split.right->binary.key_ = r.split.key;
                    s.split.right->binary.kid_[0] = r.split.left;
                    s.split.right->binary.kid_[1] = r.split.right;
                    s.split.key = content.ternary.key_[1];
                }
            } else {
                s.is_split = true;
                auto content = *p;
                s.split.left = new Node();
                s.split.left->is_ternay = true;
                s.split.left->ternary.kid_[0] = nullptr;
                s.split.left->ternary.key_[0] = content.ternary.key_[0];
                s.split.left->ternary.kid_[1] = nullptr;
                s.split.left->ternary.key_[1] = content.ternary.key_[1];
                s.split.left->ternary.kid_[2] = nullptr;
                s.split.right = p;
                s.split.right->is_ternay = false;
                s.split.right->binary.kid_[0] = nullptr;
                s.split.right->binary.key_ = key;
                s.split.right->binary.kid_[1] = nullptr;
                s.split.key = content.ternary.key_[1];
            }
        }
    } else {
        if (key < p->binary.key_) {
            if (p->binary.kid_[0]) {
                auto r = InsertValue(p->binary.kid_[0], key);
                if (r.is_split) {
                    auto content = *p;
                    p->is_ternay = true;
                    p->ternary.kid_[0] = r.split.left;
                    p->ternary.key_[0] = r.split.key;
                    p->ternary.kid_[1] = r.split.right;
                    p->ternary.key_[1] = content.binary.key_;
                    p->ternary.kid_[2] = content.binary.kid_[1];
                }
            }
        } else if (key == p->binary.key_) {
            // nothing
        } else {
            auto r = InsertValue(p->binary.kid_[1], key);
            if (r.is_split) {
                auto content = *p;
                p->is_ternay = true;
                p->ternary.kid_[0] = content.binary.kid_[0];
                p->ternary.key_[0] = content.binary.key_;
                p->ternary.kid_[1] = r.split.left;
                p->ternary.key_[1] = r.split.key;
                p->ternary.kid_[2] = r.split.right;
            }
        }
    }
    return s;
}

#include <stdio.h>

void PrintEdges(Node *p) {
    if (p->is_ternay) {
        printf("node_%p [label=\"%d, %d\"]\n", p, p->ternary.key_[0], p->ternary.key_[1]);
        for (size_t i = 0; i < 3; ++i) {
            if (p->ternary.kid_[i]) {
                PrintEdges(p->ternary.kid_[i]);
                printf("\"node_%p\" -> \"node_%p\"\n", p, p->ternary.kid_[i]);
            }
        }
    } else {
        printf("node_%p [label=\"%d\"]\n", p, p->binary.key_);
        for (size_t i = 0; i < 2; ++i) {
            if (p->ternary.kid_[i]) {
                PrintEdges(p->binary.kid_[i]);
                printf("\"node_%p\" -> \"node_%p\"\n", p, p->binary.kid_[i]);
            }
        }
    }
}

struct BTree {
    Node *root_;
    void Insert(int key) {
        auto r = InsertValue(root_, key);
        if (r.is_split) {
            root_ = new Node();
            root_->is_ternay = false;
            root_->binary.key_ = r.split.key;
            root_->binary.kid_[0] = r.split.left;
            root_->binary.kid_[1] = r.split.right;
        }
    }

    void Dump() {
        printf("digraph {\n");
        PrintEdges(root_);
        printf("}\n");
    }

    BTree() : root_(nullptr) {}
};

#include <string>

int main(int argc, char **argv) {
    int num = 20;
    if (argc > 1) {
        num = std::stoi(argv[1]);
    }
    BTree t;
    for (int i = 0; i < num; ++i) {
        t.Insert(i);
    }
    t.Dump();
}