#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace ariel
{
    class Node
    {
        std::string data;
        int level;
        std::vector<Node *> subs;

    public:
        Node(std::string &data)
        {
            this->data = data;
            this->level = 0;
        }
        std::string &getData() { return data; }
        std::vector<Node *> &getSubs() { return this->subs; }
        void addSub(std::string &input) { subs.push_back(new Node(input)); }
        void setLevel(int l) { this->level = l; }
        int getLevel() const { return this->level; }
        int size() const { return subs.size(); }
    };

    enum IteratorType
    {
        LevelOrder,
        LevelOrderReversed,
        PreOrder,
        None
    };

    class Iterator
    {
    private:
        Node *root;
        std::vector<Node *> list;
        size_t index;

    public:
        Iterator(Node *root, IteratorType type = None);

        Iterator &operator++()
        {
            index++;
            if (index == list.size())
            {
                this->root = NULL;
            }
            return *this;
        }

        Node *getRoot() const { return this->root; }

        std::string operator*()
        {
            return list[index]->getData();
        }

        std::string *operator->()
        {
            return &(list[index]->getData());
        }

        bool operator!=(const Iterator &it) const
        {
            return this->root != it.getRoot();
        }
    };

    // Orginization class
    class OrgChart
    {
    private:
        Node *root;
        static Node *findNode(Node *p, std::string data);
        static void clearTree(Node *root);

    public:
        OrgChart() { root = NULL; };
        ~OrgChart() { clearTree(root); };
        OrgChart &add_root(std::string input);
        OrgChart &add_sub(std::string input1, std::string input2);
        Iterator begin_level_order() const;
        Iterator end_level_order() const;
        Iterator begin_reverse_order() const;
        Iterator end_reverse_order() const;
        Iterator begin_preorder() const;
        Iterator end_preorder() const;
        Iterator begin() const;
        Iterator end() const;
        friend std::ostream &operator<<(std::ostream &out, const OrgChart &org);
    };

} // namespace ariel