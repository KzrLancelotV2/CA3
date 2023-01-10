#include "P3_headers.h"

int main()
{

    // variable declarations
    int i, j;
    char *action;
    char *name;
    char *pass;
    const char deviders[3] = {' ', '\n', '\0'};
    Account *head = NULL;
    Post *Phead = NULL;
    int loginGATE = 0;
    int post_counter = 1;
    char *cmd;
    int w = 0;
    int *likedPosts_id = (int *)malloc(sizeof(int) * 5);
    while (TRUE) // keep running until exit
    {
        cmd = get_command();
        analyze_cmd(cmd, &action, &name, &pass);

        if (chosen_action(action) == 0)
        {
            if (find_user(head, name) == 0)
            {
                Create_Acc(name, pass, &head);
                printAccList(head);
            }
            else
            {
                printf("An account with that username already exists.\n");
            }
        }

        else if (chosen_action(action) == 1)

        {
            // loop and check if id exists
            // if so check its password
            // if its a match:
            if (find_user(head, name) == NULL)
            {
                printf("Incorrect username or password.\n");
            }
            else
            {
                if (check_password(name, pass, head))
                {
                    system("cls");
                    printf("Logged in! ");

                    char *currAccName = (char *)malloc(sizeof(strlen(name) * sizeof(char) + 1));
                    char *currAccPass = (char *)malloc(sizeof(strlen(pass) * sizeof(char) + 1));
                    strcpy(currAccName, name); // save the logged in user's account info and use them if commanded so
                    strcpy(currAccPass, pass);
                    loginGATE++;
                    if (loginGATE)
                    {
                        while (TRUE)
                        {
                            char *logged_cmd;
                            logged_cmd = get_command();
                            char *logged_cmd_cpy; // a copy of the given cmd
                            logged_cmd_cpy = (char *)malloc(strlen(logged_cmd) * sizeof(char) + 1);
                            strcpy(logged_cmd_cpy, logged_cmd);
                            action = strtok(logged_cmd, deviders);
                            if (chosen_action(action) == 0 || chosen_action(action) == 1) // DONE
                            {
                                printf("Cant do that while logged in. Please log out first.\n! ");
                            }
                            else if (chosen_action(action) == 2) // DONE
                            {
                                system("cls");
                                printf("Logged out.\n");
                                break;
                            }
                            else if (chosen_action(action) == 3) // DONE
                            {
                                // info
                                printf("-------------------------------------------------------\n");
                                printf("Username : %s\n", currAccName);
                                printf("Password : %s\n", currAccPass);
                                printf("-------------------------------------------------------\n");
                                printPostList(Phead, currAccName);
                                // print user and password
                                // loop and find all posts with currAccName and print each one
                            }
                            else if (chosen_action(action) == 4) // DONE
                            {
                                // post
                                i = 0;
                                j = 5;
                                char *body;
                                body = (char *)malloc(strlen(logged_cmd_cpy) * sizeof(char));
                                for (i = 0; i < strlen(logged_cmd_cpy) - 5; i++)
                                {
                                    body[i] = logged_cmd_cpy[j];
                                    j++;
                                }
                                // create a post with the following body
                                Create_Post(body, currAccName, &Phead, post_counter);
                                post_counter++;
                            }
                            else if (chosen_action(action) == 5)
                            {
                                // delete post
                                int post_to_delete = atoi(logged_cmd_cpy + 7);
                                // search post list for a post with matching id.
                                delete_post(post_to_delete, &Phead, currAccName);
                                // if found delete post with function
                            }
                            else if (chosen_action(action) == 6) // find_user
                            {
                                i = 0;
                                j = 10;
                                char *wantedUser;
                                wantedUser = (char *)malloc(strlen(logged_cmd_cpy) * sizeof(char)); // should turn this part into a function
                                wantedUser = strtok(NULL, deviders);
                                if (find_user(head, wantedUser) == NULL)
                                {
                                    printf("User not found! Please check the username again.\n");
                                }
                                else
                                {
                                    printf("-------------------------------------------------------\n");
                                    printf("Username : %s\n", (find_user(head, wantedUser))->username);
                                    printf("-------------------------------------------------------\n");
                                    printPostList(Phead, wantedUser);
                                }
                            }
                            else if (chosen_action(action) == 7)
                            { // like
                                int post_to_like = atoi(logged_cmd_cpy + 5);
                                int flag;
                                if (find_post(post_to_like, Phead) != NULL)
                                {
                                    flag = 0;
                                    for (int t = 0; t < (sizeof(likedPosts_id) / 4); t++)
                                    {
                                        if (likedPosts_id[t] == post_to_like)
                                        {
                                            flag++;
                                            break;
                                        }
                                    }
                                    if (flag == 0)
                                    {
                                        likedPosts_id = (int *)realloc(likedPosts_id, sizeof(likedPosts_id) + 1);
                                        ((find_post(post_to_like, Phead))->like_count)++;
                                        likedPosts_id[w] = post_to_like;
                                        w++;
                                    }
                                    else
                                    {
                                        printf("You've already liked that post!\n");
                                    }
                                }
                                else
                                {
                                    printf("A post with that id doesn't exist!\n");
                                }
                            }
                            else
                            {
                                printf("Invalid input.\n");
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    printf("Username or password not correct.");
                }
            }
        }
        else
        {
            printf("invalid input.\n");
        }


            FILE *accountss;
            FILE *postss;
            accountss = fopen("accountsss.txt", "w"); // username password no of posts
            postss = fopen("postsss.txt", "w");       // postbody owner likes

            Post *fPptr = Phead;

             while (fPptr != NULL)

            {
                fprintf(postss,"%s", fPptr->body);
                fprintf(postss,"%s", " ");
                fprintf(postss,"%s", fPptr->owner);
                fprintf(postss,"%s", " ");
                fprintf(postss,"%d", fPptr->like_count);
                fprintf(postss,"%s", "-------------------------------------------------------\n");
                fPptr = fPptr->next_post;
            }
            Account *fptr = head;

            // start from the head and move backwards
            while (fptr != NULL)
            {   
                fprintf(accountss,"%s ", fptr->username);
                fprintf(accountss,"%s\n", fptr->password);

                fptr = fptr->next_acc;
            }

            fclose(accountss);
            fclose(postss);
    }
    loginGATE = 0; // set gate back to 0 once user has logged out
}
