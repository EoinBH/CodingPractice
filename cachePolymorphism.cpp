/*
Abstract base classes in C++ can only be used as base classes.
Thus, they are allowed to have virtual member functions without definitions.

A cache is a component that stores data so future requests for that data can be served faster.
The data stored in a cache might be the results of an earlier computation, or the duplicates of data stored elsewhere.
A cache hit occurs when the requested data can be found in a cache, while a cache miss occurs when it cannot.
Cache hits are served by reading data from the cache which is faster than recomputing a result or reading from a slower
data store. Thus, the more requests that can be served from the cache, the faster the system performs.

One of the popular cache replacement policies is: "least recently used" (LRU).
It discards the least recently used items first.

For example, if a cache with a capacity to store 5 keys has the following state (arranged from most recently used key
to least recently used key) -

5 3 2 1 4

Now, If the next key comes as 1 (which is a cache hit), then the cache state in the same order will be -

1 5 3 2 4

Now, If the next key comes as 6 (which is a cache miss), then the cache state in the same order will be -

6 1 5 3 2

You can observe that 4 has been discarded because it was the least recently used key and since the capacity of cache is 5,
it could not be retained in the cache any longer.

Given an abstract base class Cache with member variables and functions:

mp - Map the key to the node in the linked list
cp - Capacity
tail - Double linked list tail pointer
head - Double linked list head pointer
set() - Set/insert the value of the key, if present, otherwise add the key as the most recently used key.
    If the cache has reached its capacity, it should replace the least recently used key with a new key.
get() - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.

You have to write a class LRUCache which extends the class Cache and uses the member functions and variables to implement
an LRU cache.

Input Format:

First line of input will contain the N number of lines containing get or set commands followed by the capacity M of the cache.
The following N lines can either contain get or set commands.
An input line starting with get will be followed by a key to be found in the cache. An input line starting with set will be
followed by the key and value respectively to be inserted/replaced in the cache.

Constraints:
1 <= N <= 500000
1 <= M <= 1000
1 <= key <= 20
1 <= value <= 2000

Output Format:

The code provided in the editor will use your derived class LRUCache to output the value whenever a get command is encountered.

Sample Input:

3 1
set 1 2
get 1
get 2

Sample Output:

2
-1

Explanation:

Since the capacity of the cache is 1, the first set results in setting up the key 1 with its value 2.
The first get results in a cache hit of key 1, so 2 is printed as the value for the first get.
The second get is a cache miss, so -1 is printed.
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
//using namespace std;

struct Node {
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
   ~Node(){};
};

class Cache {
   
   protected: 
   std::map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache: public Cache {
    public:
    //Constructor
    LRUCache(int& capacity) {
        cp = capacity;
    }

    void set(int key, int value) {
        //Check Node with key exists
        if (mp.find(key) != mp.end()) {
            //Node with key exists
            //Update value:
            mp[key]->value = value;
        } else {
            //Node with key does not exist
            //Create new Node and set as Most Recently Used (new head)
            if (mp.size() == 0) {
                //No Nodes exist yet
                Node* newNode = new Node(key, value); //Node newNode(key, value);
                //std::cout << "newNode->key = " << newNode->key << std::endl;
                //std::cout << "newNode->value = " << newNode->value << std::endl;
                mp.insert(std::pair<int, Node*>(key, newNode));
                tail = newNode;
                head = newNode;
            } else {
                //At least one Node already exists
                //Node newNode(prev, NULL, key, value);
                //Head is currently pointing to a Node which will now become prev
                Node* prev = head;
                Node* newNode = new Node(prev, NULL, key, value);
                //Add to map
                mp.insert(std::pair<int, Node*>(key, newNode));
                //Point head to new Node
                head = newNode;
                //Update prev.next to point to new Node
                prev->next = newNode;
                //If over capacity
                if (mp.size() > cp) {
                    //Over capacity
                    tail->next->prev = NULL;
                    //Remove Node key, pointer pair from map
                    mp.erase(mp.find(tail->key));
                    //Delete trailing Node object
                    tail->~Node();
                    //Update tail
                    tail = tail->next;
                }
            }
        }
    }

    int get(int key) {
        //Get value associated with key
        //Check Node with key exists
        if (mp.find(key) != mp.end()) {
            //Node with key exists
            Node* currentNode = mp[key];
            //Node with key is now Most Recently Used so it becomes the new head
            //If not already head
            if (head != currentNode) {
                //Not already head
                currentNode->next->prev = currentNode->prev; //NULL
                if (tail != currentNode) {
                    //Not tail Node
                    currentNode->prev->next = currentNode->next;
                } else {
                    //Tail Node
                    tail = currentNode->next;
                }
                currentNode->prev = head;
                head->next = currentNode;
                currentNode->next = NULL;
                head = currentNode;
            }

            return mp[key]->value;
        } else {
            //Node with key does not exist
            return -1;
        }
    }

    void showCache() {
        std::cout << "Current state of keys in cache: ";
        Node* iterator = head;
        while(iterator != NULL) {
            std::cout << iterator->key << " ";
            iterator = iterator->prev;
        }
        std::cout << std::endl;
    }

    void showMap() {
        std::cout << "Map: " << std::endl;
        for (std::map<int, Node*>::iterator it = mp.begin(); it != mp.end(); it++) {
            std::cout << "Key: " << it->first << ", " << "Value: " << it->second->value << std::endl;
        }
    }
};

int main() {
   int n, capacity, i;
   std::cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      std::string command;
      std::cin >> command;
      if(command == "get") {
         int key;
         std::cin >> key;
         std::cout << l.get(key) << std::endl;
         l.showCache();
         l.showMap();
      } 
      else if(command == "set") {
         int key, value;
         std::cin >> key >> value;
         l.set(key,value);
         l.showCache();
         l.showMap();
      }
   }
   return 0;
}