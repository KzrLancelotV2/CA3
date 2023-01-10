#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <windows.h>
#define TRUE 1
#define FALSE 0
typedef struct Account Account;
typedef struct Post Post;
struct Account // a struct for each account
{
    char *username;
    char *password;
    Account *next_acc;
    int post_count;
};
struct Post // a struct for each post
{
    int post_id;
    char *body; // post body
    char *owner;
    int like_count;
    Post *next_post;
};
char *get_command(); // interact with user

void Create_Acc(char *username, char *password, Account **head); // create a new node and attach it to the front of the list

void Create_Post(char *body, char *owner, Post **head, int post_counter); // create a new post node

Account *find_user(Account *head, char *username); // check if an account with that user exists

void printAccList(Account *head); //print all accounts

void analyze_cmd(char *cmd, char **action, char **name, char **pass); //divide cmd into action name and pass

Post *find_post(int post_id, Post *Phead); //find a post with the given id

int chosen_action(char *action); //return a number for each valid action

int check_password(char *username, char *pass, Account *head); //check acc password

void printPostList(Post *Phead, char *username); //print all posts from a user

Post *delete_post(int post_to_delete, Post **Phead, char *currAccName); //delete a post

void all_Posts(FILE *posts, Post *Phead); //write all existing posts in a file stream

int numOfPosts(Post *Phead, char *username, Account *head); //number of posts each user has

void all_Accounts(Account *head, Post *Phead, FILE *accounts); //write all accounts in a file

void freeAccList(Account** head); //free all memory allocated to accounts

void freePostList(Post** Phead); //free all memory allocated to posts




char *get_command() // function for getting infinite size input
{
    int i = 2, j = 0;
    char *command;
    printf("What do you wish to do? : \n");

    command = (char *)malloc(sizeof(char));
    while ((command[j] = getchar()) != '\n') // getting characters one by one and reallocating the command each time
    {
        command = (char *)realloc(command, sizeof(char) * i);
        i++;
        j++;
    }
    command = (char *)realloc(command, sizeof(char) * i);
    command[strlen(command)] = '\0'; // putting null character in the end of the command
    return command;
}

void Create_Acc(char *name, char *pass, Account **head)
{
    Account *newAcc = (Account *)malloc(sizeof(Account)); // allocate space for new acc

    newAcc->username = (char *)malloc(sizeof(strlen(name) * sizeof(char) + 1));
    strcpy(newAcc->username, name);

    newAcc->password = (char *)malloc(sizeof(strlen(pass) * sizeof(char) + 1));
    strcpy(newAcc->password, pass);

    newAcc->post_count = 0;
    newAcc->next_acc = *head;

    *head = newAcc;
    printf("Account created.\n");
}

void printAccList(Account *head)
{
    Account *ptr = head;

    // start from the head and move backwards
    while (ptr != NULL)
    {
        printf("(%s) ", ptr->username);
        printf("(%s)\n ", ptr->password);

        ptr = ptr->next_acc;
    }
}
Account *find_user(Account *head, char *username) // if user is found return 1 || else if not found return 0
{
    Account *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->username, username) == 0)
        {
            return temp;
        }
        temp = temp->next_acc;
    }
    return NULL;
}

void analyze_cmd(char *cmd, char **action, char **name, char **pass) // analyze the cmd the user enters when logged out
{
    const char deviders[3] = {' ', '\n', '\0'}; // used for strtok

    *action = strtok(cmd, deviders);
    *name = strtok(NULL, deviders);
    *pass = strtok(NULL, deviders);
}
int chosen_action(char *action) // what does the user want to do???
{
    const char *actions[] = {"signup", "login", "logout", "info", "post", "delete", "find_user", "like"}; // valid cmd's
    if (strcmp(action, actions[0]) == 0)
    {
        return 0;
    }
    else if (strcmp(action, actions[1]) == 0)
    {
        return 1;
    }
    else if (strcmp(action, actions[2]) == 0)
    {
        return 2;
    }
    else if (strcmp(action, actions[3]) == 0)
    {
        return 3;
    }
    else if (strcmp(action, actions[4]) == 0)
    {
        return 4;
    }
    else if (strcmp(action, actions[5]) == 0)
    {
        return 5;
    }
    else if (strcmp(action, actions[6]) == 0)
    {
        return 6;
    }
    else if (strcmp(action, actions[7]) == 0)
    {
        return 7;
    }
    else
    {
        return -1;
    }
}
void Create_Post(char *body, char *owner, Post **Phead, int post_counter) // create a new post node
{
    Post *newPost = (Post *)malloc(sizeof(Post)); // reserve space for the new post
    if (newPost == NULL)
    {
        printf("Failed to create post.\n");
        return;
    }

    newPost->post_id = post_counter;
    newPost->body = (char *)malloc(strlen(body) * sizeof(char) + 1);
    strcpy(newPost->body, body);

    newPost->owner = (char *)malloc(strlen(owner) * sizeof(char) + 1);
    strcpy(newPost->owner, owner);

    newPost->like_count = 0;
    newPost->next_post = *Phead;

    printf("Post created successfully.\n");
    *Phead = newPost;
    /*printf("\nNew Post : \n");
    printf("%s says: \n", newPost->owner);
    printf("%s\n", newPost->body);
    printf("likes : %d\n", newPost->like_count);
    printf("post id : %d\n", newPost->post_id);*/
}
Post *find_post(int post_to_like, Post *Phead)
{

    // start from the first link
    Post *current = Phead;

    // if list is empty
    if (Phead == NULL)
    {
        return NULL;
    }

    // navigate through list
    while (current->post_id != post_to_like)
    {

        // if it is last node
        if (current->next_post == NULL)
        {
            return NULL;
        }
        else
        {
            // go to next link
            current = current->next_post;
        }
    }
    // if data found, return the current Link
    return current;
}
int check_password(char *username, char *pass, Account *head)
{
    Account *whichAcc = find_user(head, username);
    if (strcmp(whichAcc->password, pass) == 0)
    {
        return 1;
    }
    return 0;
}
void printPostList(Post *Phead, char *username)
{
    Post *Pptr = Phead;

    while (Pptr != NULL)

    {
        if (strcmp(Pptr->owner, username) == 0)
        {
            printf("Owner : %s\n", Pptr->owner);
            printf("%s", Pptr->body);
            printf("post id : %d\n", Pptr->post_id);
            printf("likes : %d\n", Pptr->like_count);
            printf("-------------------------------------------------------\n");
        }
        Pptr = Pptr->next_post;
    }
}
Post *delete_post(int post_to_delete, Post **Phead, char *currAccName)
{

    // start from the first link
    Post *current = *Phead;
    Post *previous = NULL;

    // if list is empty
    if (*Phead == NULL)
    {
        printf("Such a post doesn't exist!\n");
        return NULL;
    }

    // navigate through list
    while (current->post_id != post_to_delete)
    {

        // if it is last node
        if (current->next_post == NULL)
        {
            printf("Such a post doesn't exist!\n");
            return NULL;
        }
        else
        {
            // store reference to current link
            previous = current;
            // move to next link
            current = current->next_post;
        }
    }

    // found a match, update the link
    if (strcmp(current->owner, currAccName) == 0)
    {
        if (current == *Phead)
        {
            // change first to point to next link
            *Phead = (*Phead)->next_post;
            printf("Post successfully deleted.\n");
        }
        else
        {
            // bypass the current link
            previous->next_post = current->next_post;
            printf("Post successfully deleted.\n");
        }
    }
    else
    {
        printf("You can only delete your own posts!\n");
    }
    return current;
}
void all_Accounts(Account *head, Post *Phead, FILE *accounts)
{

    Account *ptr = head;
    fprintf(accounts, "Active accounts : \n");

    // start from the beginning
    while (ptr != NULL)
    {
        fprintf(accounts, ptr->username);
        fprintf(accounts, ptr->password);
        fprintf(accounts, (char *)numOfPosts(Phead, ptr->username, head));
        ptr = ptr->next_acc;
    }
}
int numOfPosts(Post *Phead, char *username, Account *head)
{
    Post *Pptr = Phead;

    while (Pptr != NULL)

    {
        if (strcmp(Pptr->owner, username) == 0)
        {
            ((find_user(head, username))->post_count)++;
        }
        Pptr = Pptr->next_post;
    }
    return ((find_user(head, username))->post_count);
}
void all_Posts(FILE *posts, Post *Phead)
{
    Post *Pptr = Phead;

    while (Pptr != NULL)

    {

        fprintf(posts, Pptr->owner);
        fprintf(posts, " ");
        fprintf(posts, Pptr->body);
        fprintf(posts, " ");
        fprintf(posts, (char *)Pptr->like_count);

        Pptr = Pptr->next_post;
    }
}
void freeAccList(Account** head)
{
   Account* tmp;

   while (*head != NULL)
    {
       tmp = *head;
       *head = (*head)->next_acc;
       free(tmp);
    }

}
void freePostList(Post** Phead)
{
   Post* tmp;

   while (*Phead != NULL)
    {
       tmp = *Phead;
       *Phead = (*Phead)->next_post;
       free(tmp);
    }

}
