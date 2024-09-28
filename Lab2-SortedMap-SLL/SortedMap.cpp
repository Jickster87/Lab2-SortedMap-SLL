#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
    rel = r;
    head = nullptr;
    totalPairs = 0;
}

TValue SortedMap::add(TKey k, TValue v) {
    
    Node * nomad = head;
    Node * prevNomad = nullptr;
    
    //search and replace old value with new v
    while (nomad != nullptr) {
        if (nomad->elem.first == k) {
            TValue oldValue = nomad->elem.second;
            nomad->elem.second = v;
            return oldValue;
        }
        prevNomad = nomad;
        nomad = nomad->next;
    }
    
    
    TElem newElem = std::make_pair(k, v);
    Node * newNode = new Node(newElem);
//    
//    //if list is empty
//    if (nomad == nullptr) {
//        newNode->next = head;
//        head = newNode;
//        totalPairs++;
//        //delete nomad;
//        return true;
//    }
//
//    //place pointer to correct pos
//    while (nomad != nullptr && rel(nomad->elem.first, k)) {
//        prevNomad = nomad;
//        nomad = nomad->next;
    
    
//    OLD BAD CODE, why??? -------------------------
//-----------------------------------------------
//-----------------------------------------------
//    if (prevNomad == nullptr) {
//        newNode->next = head;
//        head = newNode;
//    }
//    else if (nomad == nullptr) {
//        prevNomad->next = newNode;
//        newNode->next = nullptr;
//    }
//    else {
//        prevNomad->next = newNode;
//        newNode->next = nomad;
//    }
//-----------------------------------------------
    if (prevNomad == nullptr || !rel(head->elem.first, k)) {
        newNode->next = head;
        head = newNode;
    } else {
        // Find the appropriate position based on the relation `rel`
        nomad = head;
        while (nomad != nullptr && rel(nomad->elem.first, k)) {
            prevNomad = nomad;
            nomad = nomad->next;
        }
        prevNomad->next = newNode;
        newNode->next = nomad;
    }
    
    totalPairs++;
	return NULL_TVALUE;
}

TValue SortedMap::remove(TKey k) {
    if (head == nullptr) {
        return NULL_TVALUE;
    }
    //go to node
    Node * nomad = head;
    Node * prevNomad = nullptr;
    
    while (nomad != nullptr && nomad->elem.first != k) {
        prevNomad = nomad;
        nomad = nomad->next;
    }
    //elem not found
    if (nomad == nullptr) {
          return NULL_TVALUE;
    }
    
    TValue oldValue = nomad->elem.second;
    //3 cases (head, tail+in between)
    if (nomad == head) {
        head = head->next;
    } else {
        prevNomad->next = nomad->next;
    }
    delete nomad;
    totalPairs--;
    return oldValue;
}

TValue SortedMap::search(TKey k) const {
    Node * nomad = head;
    while (nomad != nullptr) {
        if (nomad->elem.first == k) {
            return nomad->elem.second;
        }
        nomad = nomad->next;
    }
    return NULL_TVALUE;
}

int SortedMap::size() const {
    return totalPairs;
}

bool SortedMap::isEmpty() const {
    return totalPairs == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}
