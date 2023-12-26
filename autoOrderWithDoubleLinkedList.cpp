#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_PLAYER_NAME = 10;

class LinkNode
{
private:
    float score;
    char *name;
    LinkNode *prev; // point to previous node
    LinkNode *next; // point to next node

public:
    char *getName()
    {
        return name;
    }
    float getScore()
    {
        return score;
    }
    LinkNode *getPrev()
    {
        return prev;
    };
    LinkNode *getNext()
    {
        return next;
    };
    void setPrev(LinkNode *prev)
    {
        this->prev = prev;
    }
    void setNext(LinkNode *next)
    {
        this->next = next;
    }
    void show()
    {
        cout << left << setw(10) << name << left << setw(10) << score;
    }

    // Constructor
    LinkNode(char *name, float score)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->score = score;
        setNext(nullptr);
        setPrev(nullptr);
    }
    // Destructor
    ~LinkNode()
    {
        delete[] name;
    }
};

class DoubledLink
{
private:
    LinkNode *head; // point to the head node
    LinkNode *tail; // point to the tail node

private:

    void insert(LinkNode *newNode, LinkNode *existNode)
    {

        if (newNode == nullptr) 
        {
        // Invalid nodes, cannot perform insertion
        return;
        }

            if(head == nullptr && tail == nullptr)
            {
                head = newNode;
                tail = newNode;
                newNode->setPrev(nullptr);
                newNode->setNext(nullptr);
                return;

            }
             // Insert at the last
            else if(existNode == nullptr)
            {
                newNode->setNext(nullptr);
                newNode->setPrev(tail);
                tail->setNext(newNode);
                tail = newNode;
                return;
            }
                // insert at the beginning
            else if(existNode == head)
            {
                newNode->setPrev(nullptr);
                newNode->setNext(existNode);
                existNode->setPrev(newNode);
                head = newNode;
                return;
            }
            else
            {
                // insert in between
                LinkNode *prev = existNode->getPrev();
                newNode->setNext(existNode);
                prev->setNext(newNode);
                newNode->setPrev(prev);
                existNode->setPrev(newNode);

                return; 

             }
        return;
    }

    void remove(LinkNode *node)
    {
        if (node == nullptr || head == nullptr) 
        {
        // Invalid nodes, cannot perform insertion
        return;
        }

        if(head == node & tail == node)
        {
            head = nullptr;
            tail = nullptr;

        
        }
        else if(head == node)
        {
            head = node->getNext();
            head->setPrev(nullptr);


       
        }
        else if(tail == node)
        {
            tail = node->getPrev();
            tail->setNext(nullptr);
        
        }
        else
        {
            LinkNode *next = node->getNext();
            LinkNode *prev = node->getPrev();
            next->setPrev(prev);
            prev->setNext(next);

        }
        delete node;
        node = nullptr;
        
        return;
    }

public:
    LinkNode *queryName(char *targetname)
    {
        LinkNode *curNode = head;
        while (curNode != nullptr)
        {
            if (strcmp(curNode->getName(), targetname) == 0)
            {
                return curNode;
            }
            curNode = curNode->getNext();
        }
        return nullptr;
    }
    LinkNode *queryBelowScore(float targetScore)
    {
        LinkNode *curNode = head;
        while (curNode != nullptr)
        {
            if (curNode->getScore() < targetScore)
            {
                return curNode;
            }
            curNode = curNode->getNext();
        }
        return nullptr;
    }
    void addPlayer(char *name, float score)
    {
        LinkNode *queryPlayer = this->queryName(name);
        if (queryPlayer != nullptr)
            this->remove(queryPlayer); // find existed player

        LinkNode *newPlayer = new LinkNode(name, score); // set Node in LinkNode
        LinkNode *insertPlayer = this->queryBelowScore(score);
        this->insert(newPlayer, insertPlayer);
    }
    void show()
    {
        LinkNode *curNode = head;
        int rank = 1;
        cout << "================ Game Leaderboard ==============" << endl;
        cout << "Rank  Name  Score" << endl;
        while (curNode != nullptr)
        {
            cout << rank << " ";
            curNode->show();
            cout << " " << endl;
            curNode = curNode->getNext();
            rank++;
        }
    }

public:
    // Constructor
    DoubledLink()
    {
        head = nullptr;
        tail = nullptr;
    }
    // Destructor
    ~DoubledLink()
    {
        LinkNode* current = head;
        while (current != nullptr) {
            LinkNode* next = current->getNext();
            delete current;
            current = next;
        }
    }
};

int main()
{
    DoubledLink *gameLeaderboard = new DoubledLink();
    cout << "This is a real-time updated game leaderboard, players ranked in descending order by score." << endl;
    cout << "Some new players join, some players update score." << endl;
    cout << "Game Ranking will show after each operation." << endl;
    cout << "Game over when input 0 0." << endl;

    while (true)
    {
        char name[MAX_PLAYER_NAME]; // Declare the Player's name
        float score;                // Declare the Player's score
        cin >> name >> score;
        if (strcmp(name, "0") == 0 && score == 0)
        {
            cout << "Game Over." << endl;
            break;
        }
        // update game leaderboard
        gameLeaderboard->addPlayer(name, score);
        gameLeaderboard->show();
    }

    delete gameLeaderboard;
    return 0;
}
