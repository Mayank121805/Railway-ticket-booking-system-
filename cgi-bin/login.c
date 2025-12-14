#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[50], password[50], file_user[50], file_pass[50];
    int found = 0;

    printf("Content-type:text/html\n\n");

    char input[200];
    fgets(input, sizeof(input), stdin);
    sscanf(input, "username=%49[^&]&password=%49s", username, password);

    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("<script>alert('No users found!');window.location.href='../railway_project/signup.html';</script>");
        return 0;
    }

    while (fscanf(fp, "%49[^,],%49s\n", file_user, file_pass) != EOF) {
        if (strcmp(username, file_user) == 0 && strcmp(password, file_pass) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        FILE *cur = fopen("current_user.txt", "w");
        fprintf(cur, "%s", username);
        fclose(cur);
        printf("<script>alert('Login successful!');window.location.href='../railway/dashboard.html';</script>");
    } else {
        printf("<script>alert('Invalid credentials!');window.location.href='../railway/login.html';</script>");
    }

    return 0;
}
