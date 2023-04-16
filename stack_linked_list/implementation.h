#ifndef STACK_H
#define STACK_H

/*
 * Functions and macros to be used in this implementation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define STACK_SIZE      sizeof(struct Stack)
#define STACK_NODE_SIZE sizeof(struct StackNode)

/* Support for C++. */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Stack is represented using nodes (StackNode) of a linked list.
 * Each node consists of two fields: data and next (storing address of next node).
 * The data field of each node contains the assigned value,
 * and the next points to the node containing the next item in the stack.
 */
struct StackNode
{
  void *data;
  struct StackNode *next;
};

/*
 * Stack is data structure that follows the LIFO (Last in, First out) principle:
 * insertion and deletion can take place only at one end.
 * Implemented using a  linked list means we are implementing stack allocating dynamic memory,
 * whereas using array it has to be defined elsewhere.
 */
struct Stack
{
  size_t size;
  const size_t data_size;
  struct StackNode *head;
};

/*
 * @description Find whether the stack is empty or not.
 * @complexity O(1)
 * @parameters
 *   stack: to be perfomed on.
 * @returns
 *   true if empty;
 *   false if not empty;
 */
//[[nodiscard("Retuned boolean value must be used.")]]
bool stack_is_empty (const struct Stack *stack)
{
  return !stack || !stack->head;
}

/*
 * @description
 *   Find how many elements are in the stack.
 * @parameters
 *   stack: to be perfoemd on.
 * @returns
 *   size_t size of stack.
 */
//[[nodiscard("Returned size must be used.")]]
size_t stack_size (const struct Stack *stack)
{
  if (!stack_is_empty(stack))
    return stack->size;
  return 0;
}

/*
 * @description
 *   Allocate space for new data in top of the stack (already initialised).
 * @parameters
 *   stack: to be perfoemd on.
 * @returns
 *   true if successful.
 *   false if faield.
 */
//[[nodiscard("Returned boolean value must be used.")]]
static bool stack_allocate (struct Stack *stack)
{
  struct StackNode *temp = malloc(STACK_NODE_SIZE);
  if (!temp)
    return false;

  temp->next = stack->head;
  temp->data = malloc(stack->data_size);
  stack->head = temp;

  return true;
}

/*
 * @description Initialises given stack or allocates new space for next node in stack and move into it.
 * @warning:
 *   Should not be used given the user needs to allocate new items in the stack because the user needs to allocate data into it.
 *   For that it is recommended the functions stack_emplace() or stack_push() be used instead.
 * @complexity O(1)
 * @parameters
 *   data_size: total bytes of data in stack.
 * @returns
 *   struct stack pointer if successful;
 *   NULL if failed.
 */
struct Stack *stack_initialise (const size_t data_size)
{
  struct Stack init = { 0, data_size, NULL };
  struct Stack *stack = malloc(STACK_SIZE);

  if (!stack)
    return NULL;
  memcpy(stack, &init, sizeof *stack);

  return stack;
}

/*
 * @description Inserts an element to the top of the stack.
 * @warning
 *   User needs to pass data that is not trivially freed,
 *   meaning allocated in heap and managed by him/herself.
 *   Recommended the function stack_push() be used instead.
 * @complexity O(1)
 * @parameters
 *   stack: stack to be perfomed on;
 *   data: data to be stored in next node,
 * @returns
 *    true if sucessfull;
 *    false if failed.
 */
bool stack_emplace (struct Stack *stack, void *data)
{
  if (!data)
    return false;

  if (!stack_allocate(stack))
    return false;

  stack->head->data = data;
  stack->size++;

  return true;
}

/*
 * @description Copies and inserts given element to the top of the stack.
 * @complexity O(1)
 * @parameters
 *   stack: stack to be perfomed on;
 *   data: data to be stored in next node,
 * @returns
 *    true if sucessfull;
 *    false if failed.
 */
bool stack_push (struct Stack *stack, const void *data)
{
  if (!data)
    return false;

  if (!stack_allocate(stack))
    return false;

  memcpy(stack->head->data, data, stack->data_size);
  stack->size++;

  return true;
}

/*
 * @description
 *   Removes the element from the top of the stack, freeing also data emplaced.
 * @complexity O(1)
 * @parameters
 *   stack: stack to be perfomed.
 * @returns
 *   true if sucessfull;
 *   false if failed.
 */
 bool stack_pop (struct Stack *stack)
{
  if (stack_is_empty(stack))
    return false;

  struct StackNode *temp = stack->head;
  stack->head = stack->head->next;
  free(temp->data);
  free(temp);
  stack->size--;

  return true;
}

/*
 * @description Returns the element from the top of the stack.
 * @complexity O(1)
 * @parameters
 *  stack: stack to be perfomed.
 * @returns
 *   NULL if failed;
 *   void pointer to stored data.
 */
//[[nodiscard("Data value of top item in stack should be stored.")]]
void *stack_peek (const struct Stack *stack)
{
  if (stack_is_empty(stack))
    return NULL;

  return stack->head->data;
}

/*
 * @description: Swap the contents of one stack with another stack of same type but the size may vary.
 * @complexity O(?)
 * @parameters
 *  stack_one: first stack,
 *  stack_two: second stack.
 * @returns
 *  true if successful,
 *  false if failed.
 * TODO: Implementation of the function.
 */
/*const bool stack_swap (struct Stack *stack_one, struct Stack *stack_two)
{
  return true;
}*/

/*
 * @description:
 *   Removes all memory allocated into this stack, including data emplaced.
 *   Note it will not free the memory alocated for the stack itself, the user should do it.
 * @complexity O(n), where n is data->size.
 * @parameters
 *   stack: stack to be perfomed.
 */
void stack_destroy (struct Stack *stack)
{
  void *next = NULL;

  while (!stack_is_empty(stack))
  {
    free(stack_peek(stack));
    next = stack->head->next;
    stack->head = stack->head->next;
    free(next);
    stack->size--;
  }
}

/* Support for C++. */
#ifdef __cplusplus
}
#endif

#endif
