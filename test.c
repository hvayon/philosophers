
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
 
// #define MAX_SIZE 20
 
// typedef struct User {
//     char *login;
//     char *password;
//     int id;
// } User;
 
// void jsonUser(User *user) {
//     printf("{id: %d, login: \"%s\", password: \"%s\"}\n", 
//             user->id, user->login, user->password);
// }
 
// void freeUsersArray(User** users, unsigned size) {
//     unsigned i;
//     for (i = 0; i < size; i++) {
//         free((*users)[i].login);
//         free((*users)[i].password);
//     }
//     free(*users);
// }
 
// int main() {
//     User *users = NULL;
//     unsigned size;
//     char buffer[128];
//     unsigned i;
 
//     printf("Enter number of users: ");
//     scanf("%d", &size);
 
//     size = size <= MAX_SIZE? size: MAX_SIZE;
//     users = (User*) malloc(size * sizeof(User));
 
//     for (i = 0; i < size; i++) {
//         printf("user #%d\nname: ", i);
//         scanf("%127s", buffer);
//         users[i].id = i;
//         users[i].login = (char*) malloc(strlen(buffer) + 1);
//         strcpy(users[i].login, buffer);
//         printf("password: ");
//         scanf("%127s", buffer);
//         users[i].password = (char*) malloc(strlen(buffer) + 1);
//         strcpy(users[i].password, buffer);
//     }
 
//     for (i = 0; i < size; i++) {
//         jsonUser(&users[i]);
//     }
 
//     freeUsersArray(&users, size);
//     return (0);
// }

