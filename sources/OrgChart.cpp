#include "OrgChart.hpp"
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

namespace ariel
{

    void preOrder(Node *root, std::vector<std::string> &list)
    {
        if (!root)
        {
            return;
        }
        list.push_back(root->getData());
        for (Node *p : root->getSubs())
        {
            preOrder(p, list);
        }
    }

    void bfsOrder(Node *root, std::vector<std::string> &list)
    {
        list.clear();
        std::queue<Node *> q;
        q.push(root);

        int currentLevel = 0;
        while (!q.empty())
        {
            Node *p = q.front();
            list.push_back(p->getData());
            for (Node *n : p->getSubs())
            {
                n->setLevel(p->getLevel() + 1);
                q.push(n);
            }
            q.pop();
        }
    }

    Iterator::Iterator(Node *root, IteratorType type)
    {
        this->root = root;
        index = 0;
        if (root != NULL)
        {
            switch (type)
            {
            case LevelOrder:
                bfsOrder(root, this->list);
                break;
            case LevelOrderReversed:
                bfsOrder(root, this->list);
                std::reverse(this->list.begin(), this->list.end());
                break;
            case PreOrder:
                preOrder(root, this->list);
                break;
            default:;
            }
        }
    }

    /**
     * @brief OrgChart  Functions
     *
     * @return
     */

    void OrgChart::clearTree(Node *root)
    {
        if (!root)
        {
            return;
        }

        for (Node *p : root->getSubs())
        {
            clearTree(p);
        }

        delete root;
    }

    /**
     * @brief A default iterator which use level order scan on the tree
     *
     * @return Iterator
     */
    Iterator OrgChart::begin() const
    {
        return Iterator(root, LevelOrder);
    }

    Iterator OrgChart::end() const
    {
        return Iterator(NULL);
    }

    Iterator OrgChart::begin_preorder() const
    {
        return Iterator(root, PreOrder);
    }

    Iterator OrgChart::end_preorder() const
    {
        return Iterator(NULL);
    }

    Iterator OrgChart::begin_reverse_order() const
    {
        return Iterator(root, LevelOrderReversed);
    }

    Iterator OrgChart::end_reverse_order() const
    {
        return Iterator(NULL);
    }

    Iterator OrgChart::begin_level_order() const
    {
        return Iterator(root, LevelOrder);
    }

    Iterator OrgChart::end_level_order() const
    {
        return Iterator(NULL);
    }

    std::ostream &operator<<(std::ostream &out, const OrgChart &org)
    {

        return out;
    }

    /**
     * @brief Add this input as a root for the tree
     *
     * @param input
     * @return OrgChart&
     */
    OrgChart &OrgChart::add_root(std::string input)
    {
        if (this->root)
        {
            clearTree(root);
        }
        this->root = new Node(input);
        return *this;
    }

    /**
     * @brief Find the node with this data
     *
     * @param p
     * @param data
     * @return Node*
     */
    Node *OrgChart::findNode(Node *p, std::string data)
    {
        if (!p)
        {
            return NULL;
        }

        if (p->getData() == data)
        {
            return p;
        }

        for (Node *ptr : p->getSubs())
        {
            Node *n = findNode(ptr, data);
            if (n != NULL)
            {
                return n;
            }
        }

        return NULL;
    }

    /**
     * @brief  Adding a sub to the input1 in the tree , If input1 is not found in tree then an exception will be throughn
     *
     * @param input1
     * @param input2
     * @return OrgChart&
     */
    OrgChart &OrgChart::add_sub(std::string input1, std::string input2)
    {
        Node *p = findNode(this->root, input1);
        if (p)
        {
            p->addSub(input2);
        }
        else
        {
            throw std::invalid_argument("Error: input1 node was not found !");
        }
        return *this;
    }

} // namespace ariel
