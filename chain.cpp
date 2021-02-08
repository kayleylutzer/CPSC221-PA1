#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  Node *newNode = new Node(ndata);
  if (p == NULL) {
    newNode->next = head_;
    if (head_ == NULL) {
      head_ = newNode;
    } else {
      head_->prev = newNode;
      head_ = newNode;
    }
  } else {
    newNode->next = p->next;
    if (p->next != NULL) {
      p->next->prev = newNode; 
    } 
    newNode->prev = p;
    p->next = newNode;
  }
  length_++;
  return newNode;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  
  if( p == q || p == NULL || q == NULL) return;

  //create a new node at the beginning of the list called sentinel and make sure it points to what was the beginning and vice versa
  Node *sentinel = new Node();
  sentinel->next = head_;
  head_->prev = sentinel;

  //create a new node called end_sentinel
  Node *end_sentinel = new Node();
  //curr is temporary for iteration to find the node at the end of the list
  Node *curr = head_;
  while (curr->next != NULL) {
    curr = curr->next;
    cout << "loop" << endl;
  }
  //make it so end_sentinel is now at the end of the list and the previous end now points to the end_sentinel
  curr->next = end_sentinel;
  end_sentinel->prev = curr;

  //sentinel variables do not appear to be used - are these just to make the nodes at each end of the list have both their prev and next pointers defined?

  //keep track of what p and q previously pointed to
  //pp and qp do not appear to be used - why are the previous pointers not updated/swapped when the nodes are swapped?
  Node *pp = p->prev;
  Node *pn = p->next;
  Node *qp = q->prev;
  Node *qn = q->next;

  if (p == head_) {
    if (p->next == q) {
      q->next = p;
      p->prev = q;
      p->next = qn;
      qn->prev = p;
      head_ = q;
    } else {
      q->next = pn;
      pn->prev = q;
      p->next = qn;
      qn->prev = p;
      qp->next = p;
      p->prev = qp;
      head_ = q;
    }
    cout << "head swapped" << endl;
  } else if (q == head_) { 
    if (q->next == p) {
      p->next = q;
      q->prev = p;
      q->next = pn;
      pn->prev = q;
      head_ = p;
    } else {
      p->next = qn;
      qn->prev = p;
      q->next = pn;
      pn->prev = q;
      pp->next = q;
      q->prev = pp;
      head_ = p;
    }
    cout << "head swapped" << endl;
  } else if (q->next == p) {
    //scenario 5: p is after q but neither are at the head of list
    q->next = pn;
    pn->prev = q;
	  p->next = q;
    q->prev = p;
	  qp->next = p;
    p->prev = qp;
  } else if (p->next == q) {
    //scenario 6: q is after p but neither are at the head of list
    p->next = qn;
    qn->prev = p;
	  q->next = p;
    p->prev = q;
	  pp->next = q;
    q->prev = pp;
  } else {
    //scenario 7: p or q are one or more nodes apart from each other and neither is head of list
    //what happens if one of p or q is at the end of the list? the -> next pointer now points to end_sentinel which you're going to delete at the end of this.
    p->next = qn;
    qn->prev = p;
    qp->next = p;
    p->prev = qp;
    pp->next = q;
    q->prev = pp;
    q->next = pn;
    pn->prev = q;
  }
  cout << "swapped" << endl;
  if (p->next == end_sentinel){
    p->next = NULL;
  }
  if (q->next == end_sentinel){
    q->next = NULL;
  }
  if (p->prev == sentinel){
    p->prev = NULL;
  }
  if (q->prev == sentinel){
    q->prev = NULL;
  }

  //delete temporary variables
  end_sentinel = NULL;
  sentinel = NULL;  
  delete end_sentinel;
  delete sentinel;
}


/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  /* your code here */
  Node* curr = head_;

  while (curr != NULL) {
    Node* n = curr->next;
    delete curr;
    curr = n;
  }
  head_= NULL;
  length_ = 0;
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  /* your code here */
  clear();
  head_ = other.head_;

  Node* curr_other = other.head_;
  Node* curr = head_;

  while (curr_other != NULL){
    curr = insertAfter(curr, curr_other->data);
    curr_other = curr_other->next;
  }
}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  Node* curr = head_;
  Node* min;
  
  double max = 0;
  double value = (double) INT_MAX;

//finding leftmost block
cout << "start unscrambling" << endl;
  while (curr->next != NULL) {
    cout << "a" << endl;
    Node* curr2 = curr->next;
    value = (double) INT_MAX;
    while(curr2->next != NULL) {
      cout << "b" << endl;
      double distance = (curr2->data).distanceTo(curr->data); 
      cout << "calc" << endl;
      if (distance < value) {
        value = distance;
      }
      cout << value << endl;
      cout << "shift" << endl;
      curr2 = curr2->next;
    }
    if (value > max) {
      min = curr;
      max = value;
    }
    curr = curr->next;
  }
  cout << "swap in unscrambled" << endl;
  swap(head_, min);
  cout << "swapped in unscrambled" << endl;

  //repeating for rest of the chain 
  Node *minB = new Node();
  curr = head_;
  while (curr->next != NULL) {
    cout << "a" << endl;
    Node* curr2 = curr->next;
    value = (double) INT_MAX;
      while(curr2->next != NULL) {
        double distance = (curr2->data).distanceTo(curr->data);
        if (distance < value) {
          value = distance;
          minB = curr2;
        }
        curr2 = curr2->next;
      }
      curr = curr->next;
    }
  swap(curr->next, minB);
  curr = curr->next;
}