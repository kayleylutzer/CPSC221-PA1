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
    head_->prev = newNode; // FIX THIS
  } 
  p->next = newNode;
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
  Node *sentinel;
  sentinel->next = head_;

  Node *end_sentinel = new Node();
  Node *curr = head_ = new Node();
  while (curr->next != NULL) {
    curr->next = curr;
  }
  end_sentinel->prev = curr;

  if( p == q || p == NULL || q == NULL) return;
  Node *pp = p->prev;
  Node *pn = p->next;
  Node *qp = q->prev;
  Node *qn = q->next;
  if (q->next == p) {
    q->next = pn;
    p->prev = qp;
    p->next = q;

  } else if (p->next == q) {

    p->next = qn;
    q->prev = pp;
    q->next = p;

  } else {
    q->prev = pp;
    q->next = pn;
    p-> prev = qp;
    p->next = qn;

  }

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
  Node* curr = head_->next;
  Node* n = new Node();

  while (curr->next != NULL){
    n = curr->next;
    delete curr;
    curr = n;
  }
  delete curr;
  delete head_;
  head_=NULL;
  curr = NULL;
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
  length_ = other.length_;
  head_ = new Node();
  head_ = other.head_;

  Node* curr_other = other.head_;
  Node* curr = head_;

  while (curr_other != NULL){
    insertAfter (curr, curr_other->data);
    curr = curr->next;
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
  /* your code here */
}