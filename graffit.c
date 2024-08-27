#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

#ifndef MAT_SIZE
#define MAT_SIZE 3 // A small graph
#endif

typedef struct user_struct
{
  char name[MAX_STR_LEN];
  struct friend_node_struct *friends;
  struct brand_node_struct *brands;
  bool visited;
  int depth;
  // struct friend_node_struct* userList;
} User;

typedef struct friend_node_struct
{
  User *user;
  struct friend_node_struct *next;
} FriendNode;

typedef struct brand_node_struct
{
  char brand_name[MAX_STR_LEN];
  bool visited;
  struct brand_node_struct *next;
} BrandNode;

typedef struct queue_struct
{
  User *node;
  struct queue_struct *next;
} Queue;

FriendNode *allUsers = NULL;

int brand_adjacency_matrix[MAT_SIZE][MAT_SIZE];
char brand_names[MAT_SIZE][MAX_STR_LEN];

/**
 * Given the head to a FriendNode linked list, returns true if a
 * given user's name exists in the list. Returns false otherwise.
 */

bool in_friend_list(FriendNode *head, User *node)
{
  for (FriendNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->user->name, node->name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a BrandNode linked list, returns true if a
 * given brand's name exists in the list. Returns false otherwise.
 */
bool in_brand_list(BrandNode *head, char *name)
{
  for (BrandNode *cur = head; cur != NULL; cur = cur->next)
  {
    if (strcmp(cur->brand_name, name) == 0)
    {
      return true;
    }
  }
  return false;
}

/**
 * Given the head to a FriendNode linked list, inserts a given user
 * into the linked list and returns the head of the new linked list.
 * The insertion is done in alphabetical order. If the user already
 * exists, no modifications are made and the list is returned as is.
 */
FriendNode *insert_into_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (in_friend_list(head, node))
  {
    printf("User already in list\n");
    return head;
  }

  FriendNode *fn = calloc(1, sizeof(FriendNode));
  fn->user = node;
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->user->name, node->name) > 0)
  {
    fn->next = head;
    return fn;
  }

  FriendNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->user->name, node->name) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a BrandNode linked list, inserts a given brand into
 * the linked list and returns the head of the new linked list. The
 * insertion is done in alphabetical order. If the brand already exists,
 * no modifications are made and the list is returned as is.
 */
BrandNode *insert_into_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (in_brand_list(head, node))
  {
    printf("Brand already in list\n");
    return head;
  }

  BrandNode *fn = calloc(1, sizeof(BrandNode));
  strcpy(fn->brand_name, node);
  fn->next = NULL;

  if (head == NULL)
    return fn;

  if (strcmp(head->brand_name, node) > 0)
  {
    fn->next = head;
    return fn;
  }

  BrandNode *cur;
  for (cur = head; cur->next != NULL && strcmp(cur->next->brand_name, node) < 0;
       cur = cur->next)
    ;

  fn->next = cur->next;
  cur->next = fn;

  return head;
}

/**
 * Given the head to a FriendNode linked list, removes a given user from
 * the linked list and returns the head of the new linked list. If the user
 * does not exist, no modifications are made and the list is returned as is.
 */
FriendNode *delete_from_friend_list(FriendNode *head, User *node)
{
  if (node == NULL)
    return head;

  if (!in_friend_list(head, node))
  {
    printf("User not in list\n");
    return head;
  }

  if (strcmp(head->user->name, node->name) == 0)
  {
    FriendNode *temp = head->next;
    free(head);
    return temp;
  }

  FriendNode *cur;
  for (cur = head; cur->next->user != node; cur = cur->next)
    ;

  FriendNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given the head to a BrandNode linked list, removes a given brand from
 * the linked list and returns the head of the new linked list. If the brand
 * does not exist, no modifications are made and the list is returned as is.
 */
BrandNode *delete_from_brand_list(BrandNode *head, char *node)
{
  if (node == NULL)
    return head;

  if (!in_brand_list(head, node))
  {
    printf("Brand not in list\n");
    return head;
  }

  if (strcmp(head->brand_name, node) == 0)
  {
    BrandNode *temp = head->next;
    free(head);
    return temp;
  }

  BrandNode *cur;
  for (cur = head; strcmp(cur->next->brand_name, node) != 0; cur = cur->next)
    ;

  BrandNode *temp = cur->next;
  cur->next = temp->next;
  free(temp);

  return head;
}

/**
 * Given a user, prints their name, friends, and liked brands.
 */
void print_user_data(User *user)
{
  printf("User name: %s\n", user->name);

  printf("Friends:\n");
  for (FriendNode *f = user->friends; f != NULL; f = f->next)
  {
    printf("   %s\n", f->user->name);
  }

  printf("Brands:\n");
  for (BrandNode *b = user->brands; b != NULL; b = b->next)
  {
    printf("   %s\n", b->brand_name);
  }
}

/**
 * Given a brand, returns the index of the brand inside the brand_names array.
 * If it doesn't exist in the array, return -1
 */
int get_brand_index(char *name)
{
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (strcmp(brand_names[i], name) == 0)
    {
      return i;
    }
  }

  printf("Brand '%s' not found\n", name);
  return -1; // Not found
}

/**
 * Given a brand, prints their name, index (inside the brand_names
 * array), and the names of other similar brands.
 */
void print_brand_data(char *brand_name)
{
  int idx = get_brand_index(brand_name);
  if (idx < 0)
  {
    printf("Brand '%s' not in the list.\n", brand_name);
    return;
  }

  printf("Brand name: %s\n", brand_name);
  printf("Brand idx: %d\n", idx);

  printf("Similar brands:\n");
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (brand_adjacency_matrix[idx][i] == 1 && strcmp(brand_names[i], "") != 0)
    {
      printf("   %s\n", brand_names[i]);
    }
  }
}

/**
 * Read from a given file and populate a the brand list and brand matrix.
 **/
void populate_brand_matrix(char *file_name)
{
  // Read the file
  char buff[MAX_STR_LEN];
  FILE *f = fopen(file_name, "r");
  fscanf(f, "%s", buff);
  char *line = buff;
  // Load up the brand_names matrix
  for (int i = 0; i < MAT_SIZE; i++)
  {
    if (i == MAT_SIZE - 1)
    {
      strcpy(brand_names[i], line);
      break;
    }
    int index = strchr(line, ',') - line;
    strncpy(brand_names[i], line, index);
    line = strchr(line, ',') + sizeof(char);
  }
  // Load up the brand_adjacency_matrix
  for (int x = 0; x < MAT_SIZE; x++)
  {
    fscanf(f, "%s", buff);
    for (int y = 0; y < MAT_SIZE; y++)
    {
      int value = (int)buff[y * 2];
      if (value == 48)
      {
        value = 0;
      }
      else
      {
        value = 1;
      }
      brand_adjacency_matrix[x][y] = value;
    }
  }
}

/**
 * Creates and returns a user.
 */
User *create_user(char *name)
{
  User *new_user = NULL;
  new_user = (User *)calloc(1, sizeof(User));
  strcpy(new_user->name, name);
  new_user->visited = false;
  new_user->friends = NULL;
  new_user->brands = NULL;
  new_user->depth = -1;

  if (in_friend_list(allUsers, new_user))
    return NULL;
  allUsers = insert_into_friend_list(allUsers, new_user);
  // new_user->userList = allUsers;

  return new_user;
}

/**
 * Deletes a given user.
 */
int delete_user(User *user)
{
  // Removes a given user from the platform. The user must be removed from the allUsers linked list and the friend list of any users that they belong to.
  // Return 0 if the user was successfully removed. If the user does not exist, return -1 instead.
  // FriendNode *allUsers -> FN *user *next, (user we want to delete)
  //                            name *friends *brands visited (visit their friends node)
  //                                 FN *user *next
  //                                     name *friends *brands visited

  if (!in_friend_list(allUsers, user) || user == NULL)
    return -1;

  FriendNode *p = user->friends;
  FriendNode *ptr = NULL;
  BrandNode *q = NULL;
  BrandNode *qtr = NULL;

  while (p != NULL) // deleting user from user's friend's list
  {
    ptr = p->next;
    p->user->friends = delete_from_friend_list(p->user->friends, user);
    free(p);
    p = ptr;
  }

  q = user->brands;

  while (q != NULL) // deleting brands
  {
    qtr = q->next;
    free(q);
    q = qtr;
  }

  ptr = user->friends;

  while (ptr != NULL)
  {
    p = ptr->next;
    free(ptr);
    ptr = p;
  }

  allUsers = delete_from_friend_list(allUsers, user); // deleting from allUsers

  return 0;
}

/**
 * Create a friendship between user and friend.
 */
int add_friend(User *user, User *friend)
{
  if (user == NULL || friend == NULL || !in_friend_list(allUsers, user) || !in_friend_list(allUsers, friend))
    return -1;
  if (in_friend_list(user->friends, friend) || in_friend_list(friend->friends, user))
    return -1;
  if (strcmp(user->name, friend->name) == 0)
    return -1;

  // find user, insert friend into user's friends list
  // find friend, insert user into friend's friend list
  /*FriendNode *p = allUsers;

  while (p != NULL)
  {
    if (strcmp(p->user->name, user->name) == 0)
    {
      p->user->friends = insert_into_friend_list(p->user->friends, friend);
    }
    else if (strcmp(p->user->name, friend->name) == 0)
    {
      p->user->friends = insert_into_friend_list(p->user->friends, user);
    }
    p = p->next;
  }*/

  user->friends = insert_into_friend_list(user->friends, friend);
  friend->friends = insert_into_friend_list(friend->friends, user);

  return 0;
}

/**
 * Removes a friendship between user and friend.
 */
int remove_friend(User *user, User *friend)
{
  if (user == NULL || friend == NULL || !in_friend_list(allUsers, user) || !in_friend_list(allUsers, friend))
    return -1;
  if (!in_friend_list(user->friends, friend) || !in_friend_list(friend->friends, user))
    return -1;
  if (strcmp(user->name, friend->name) == 0)
    return -1;

  /*
  FriendNode *p = NULL;
  p = allUsers;

  while (p != NULL)
  {
    if (strcmp(p->user->name, user->name) == 0)
    {
      p->user->friends = delete_from_friend_list(p->user->friends, friend);
    }
    else if (strcmp(p->user->name, friend->name) == 0)
    {
      p->user->friends = delete_from_friend_list(p->user->friends, user);
    }
    p = p->next;
  }*/

  user->friends = delete_from_friend_list(user->friends, friend);
  friend->friends = delete_from_friend_list(friend->friends, user);

  return 0;
}

/**
 * Creates a follow relationship, the user follows the brand.
 */
int follow_brand(User *user, char *brand_name)
{
  if (user == NULL || !in_friend_list(allUsers, user))
    return -1;
  if (get_brand_index(brand_name) < 0 || in_brand_list(user->brands, brand_name))
    return -1;

  user->brands = insert_into_brand_list(user->brands, brand_name);

  return 0;
}

/**
 * Removes a follow relationship, the user unfollows the brand.
 */
int unfollow_brand(User *user, char *brand_name)
{
  if (user == NULL || !in_friend_list(allUsers, user))
    return -1;
  if (get_brand_index(brand_name) < 0 || !in_brand_list(user->brands, brand_name))
    return -1;

  user->brands = delete_from_brand_list(user->brands, brand_name);

  return 0;
}

/**
 * Return the number of mutual friends between two users.
 */
int get_mutual_friends(User *a, User *b)
{
  if (strcmp(a->name, b->name) == 0)
    return 0;
  if (a == NULL || b == NULL || !in_friend_list(allUsers, a) || !in_friend_list(allUsers, b))
    return 0;
  int count = 0;
  FriendNode *p = NULL;
  User *q = NULL;
  p = b->friends;
  // I need to loop through user b's friends list, for each user, check if its in user a's friends list

  while (p != NULL)
  {
    q = p->user;
    if (in_friend_list(a->friends, q))
      count++;
    p = p->next;
  }

  return count;
}

/**
 * A degree of connection is the number of steps it takes to get from
 * one user to another. Returns a non-negative integer representing
 * the degrees of connection between two users.
 */

Queue *createQueueNode(User *user)
{
  Queue *newQueueNode = NULL;
  newQueueNode = (Queue *)calloc(1, sizeof(Queue));

  newQueueNode->node = user;
  newQueueNode->next = NULL;

  return newQueueNode;
}

Queue *enqueuee(Queue *head, FriendNode *friendss) // enqueue // inserting into head of linked list, last one out is the one at the head
{                                                  // head of Queue is last one out
  // head->next = NULL;
  Queue *newNode = NULL;
  newNode = createQueueNode(friendss->user);
  friendss->user->visited = true;
  newNode->next = head;
  return newNode;
}

Queue *deletingTheYard(Queue *head) // dequeue // returns head of Queue, removes from tail of linked list, end of queue, first one out basically
{
  if (head == NULL)
    return NULL;
  /*if (head->next == NULL)
  {
    free(head);
    return NULL;
  }*/

  Queue *p = NULL;
  Queue *q = NULL;
  p = head;
  q = p->next;

  if (q == NULL)
  {
    free(p);
    return NULL;
  }

  while (q->next != NULL)
  {
    p = p->next;
    q = q->next;
  }
  free(q);
  p->next = NULL;

  return head;
}

Queue *dequeuee(Queue *head) // return
{
  if (head == NULL)
    return NULL;
  Queue *p = NULL;
  p = head;
  while (p->next != NULL)
  {
    p = p->next;
  }
  // p->node->visited = true;
  return p;
}

int lengthOfAllUsers()
{
  FriendNode *p = NULL;
  p = allUsers;
  int count = 0;

  while (p != NULL)
  {
    count++;
    p = p->next;
  }
  return count;
}

void setAllToFalse()
{
  FriendNode *p = allUsers;

  while (p != NULL)
  {
    p->user->visited = false;
    p = p->next;
  }
}

bool isEmpty(Queue *head)
{
  if (head == NULL)
    return true;
  return false;
}

void getUsersInQueue(Queue *head)
{
  Queue *p = head;

  while (p != NULL)
  {
    printf("%s: depth: %d\n", p->node->name, p->node->depth);
    p = p->next;
  }
}

int getDegrees(User *a, User *b, Queue *head)
{
  if (in_friend_list(a->friends, b))
    return a->depth;
  if (a->depth >= lengthOfAllUsers() - 1)
    return -1;

  FriendNode *p = NULL;
  User *q = NULL;
  p = a->friends;

  while (p != NULL)
  {
    if (!p->user->visited)
    {
      head = enqueuee(head, p);
      p->user->depth = a->depth + 1; // set depth of user to last depth + 1
    }
    p = p->next;
  }

  q = dequeuee(head)->node;
  // printf("Name: %s, Depth %d\n", q->name, q->depth);

  if (!isEmpty(head))
    head = deletingTheYard(head);

  return getDegrees(q, b, head);
}

void printUsersFriends(User *usr)
{
  FriendNode *p = NULL;
  p = usr->friends;
  while (p != NULL)
  {
    printf("%s\n", p->user->name);
    p = p->next;
  }
}

void printingUsers()
{
  FriendNode *p = NULL;
  p = allUsers;

  while (p != NULL)
  {
    printf("%s\n", p->user->name);
    if (p->user->visited)
      printf("User has been visited\n");
    else
      printf("User has not been visited\n");
    p = p->next;
  }
}

int get_degrees_of_connection(User *a, User *b)
{

  setAllToFalse();

  // base case -> if user b is in a's friends
  if (strcmp(a->name, b->name) == 0)
    return 0;
  // if (in_friend_list(a->friends, b)) return 1;

  Queue *head = NULL;
  a->visited = true;
  a->depth = 1;

  // base case when (a == b) or (a == a) or (b == b)
  // insert node into queue, b stays the same, insert first one out of queue into degrees(a!!, b);

  return getDegrees(a, b, head);
}

/**
 * Marks two brands as similar.
 */
void connect_similar_brands(char *brandNameA, char *brandNameB)
{
  if (strcmp(brandNameA, brandNameB) == 0 ||
      (get_brand_index(brandNameA) < 0 || get_brand_index(brandNameB) < 0))
    return;

  int brandA = get_brand_index(brandNameA);
  int brandB = get_brand_index(brandNameB);

  brand_adjacency_matrix[brandA][brandB] = 1;
  brand_adjacency_matrix[brandB][brandA] = 1;

  return;
}

/**
 * Marks two brands as not similar.
 */
void remove_similar_brands(char *brandNameA, char *brandNameB)
{
  if (strcmp(brandNameA, brandNameB) == 0 ||
      (get_brand_index(brandNameA) < 0 || get_brand_index(brandNameB) < 0))
    return;

  int brandA = get_brand_index(brandNameA);
  int brandB = get_brand_index(brandNameB);

  brand_adjacency_matrix[brandA][brandB] = 0;
  brand_adjacency_matrix[brandB][brandA] = 0;

  return;
}

/**
 * Returns a suggested friend for the given user.
 */
User *get_suggested_friend(User *user)
{
  FriendNode *p = NULL;
  User *q = NULL;
  BrandNode *ptr = NULL;
  p = allUsers;
  int count = 0;
  int largest = 0;
  if (user == NULL)
    return NULL;

  while (p != NULL)
  {
    if (strcmp(user->name, p->user->name) != 0 && !in_friend_list(user->friends, p->user)) // checks if user is itself, user is already friends with user and if user has been visited already
    {
      ptr = p->user->brands;
      while (ptr != NULL)
      {
        if (in_brand_list(user->brands, ptr->brand_name))
          count++;
        ptr = ptr->next;
      }
      if (count >= largest)
      {
        q = p->user;
        largest = count;
      }
    }
    count = 0;
    p = p->next;
  }
  if (q == NULL)
    return NULL;

  return q;
}

/**
 * Adds n suggested friends for the given user.
 * Returns how many friends were successfully followed.
 */
int largerThanCount(User *user) // helper
{
  // total number of users - (friends of user + 1)
  FriendNode *p = NULL;
  p = allUsers;
  int count = 0;

  while (p != NULL) // total number of users
  {
    count++;
    p = p->next;
  }

  p = user->friends;
  while (p != NULL)
  {
    count--;
    p = p->next;
  }

  return count - 1;
}

int add_suggested_friends(User *user, int n)
{
  if (user == NULL)
    return 0;
  User *p = NULL;
  int count = 0;
  int count2 = largerThanCount(user);
  // if (count2 <= 0) return 0;
  // printf("largerThanCount: %d\n", largerThanCount(user));

  while (count < n && count < count2)
  {
    p = get_suggested_friend(user);
    // if (p == NULL) return 0;
    // p->visited = true;
    user->friends = insert_into_friend_list(user->friends, p);
    p->friends = insert_into_friend_list(p->friends, user);
    count++;
    // printf("***%d\n", count);
  }
  // printf("***%d\n", largerThanCount(user));
  // printf("Count: %d\n", count);
  // printf("********%d\n", largerThanCount(user));

  return count;
}

/**
 *
 * Follows n suggested brands for the given user.
 * Returns how many brands were successfully followed.
 */
int largerThanCountV2(User *user)
{
  int count = 0;
  BrandNode *p = NULL;
  p = user->brands;

  while (p != NULL)
  {
    count++;
    p = p->next;
  }

  return MAT_SIZE - count;
}

bool ifInArray(int arr[], int x, int count)
{
  for (int i = 0; i < count; i++)
  {
    if (arr[i] == x)
      return true;
  }
  return false; // returns false if array does not contain number
}

int follow_suggested_brands(User *user, int n)
{
  // check adj matrix
  int count = 0;
  int count2 = largerThanCountV2(user);
  int largest = -1;
  int i, j, k;
  int tracker;
  int arrayCounter = 0;
  int count1;

  if (user == NULL)
    return 0;

  // insert_into_brand_list()
  // in_brand_list()
  // indexing for char names array, if brand is in user's brand list then skip
  //
  // loop till matt size
  if (n > count2)
    count1 = count2;
  else
    count1 = n;
  if (count1 <= 0)
    return 0;
  // printf("%d\n", count1);

  int brandNames[count1];
  for (i = 0; i < count1; i++)
  {
    brandNames[i] = -1;
  }
  // printf("******\n");
  for (k = 0; k < count1; k++)
  {
    for (i = 0; i < MAT_SIZE; i++)
    {
      if (!in_brand_list(user->brands, brand_names[i]) && !ifInArray(brandNames, get_brand_index(brand_names[i]), count1))
      {
        for (j = 0; j < MAT_SIZE; j++)
        {
          if (brand_adjacency_matrix[i][j] == 1 && in_brand_list(user->brands, brand_names[j]))
            count++; // checking similar in matrix
        }
        if (count > largest)
        {
          // brandNames[arrayCounter] = get_brand_index(brand_names[i]);
          largest = count;
          tracker = get_brand_index(brand_names[i]);
          // printf("tracker1: %d\n", tracker);
          // arrayCounter++;
        }
        // else if (arrayCounter == 0 )

        else if (count == largest && strcmp(brand_names[tracker], brand_names[i]) < 0)
        {
          // brandNames[arrayCounter] = get_brand_index(brand_names[i])
          tracker = get_brand_index(brand_names[i]);
          // printf("tracker2: %d\n", tracker);
          // printf("%d\n", tracker);
        }
        /*
        else if (count == largest && strcmp(pointer, brand_names[i]) < 0)
        {
          pointer = brand_names[i];
        }*/
      }
      count = 0;
    }
    brandNames[arrayCounter] = tracker;
    arrayCounter++;
    largest = -1;
    // user->brands = insert_into_brand_list(user->brands, pointer);
    // printf("%d\n", tracker);
  }
  // printf("count1: %d\n", count1);

  for (i = 0; i < count1; i++)
  {
    // printf("i = %d\n", i);
    // printf("%d\n", brandNames[i]);
    user->brands = insert_into_brand_list(user->brands, brand_names[brandNames[i]]);
  }

  return count1;
}
