#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[50], password[50];
    printf("Content-type:text/html\n\n");

    char *data = getenv("QUERY_STRING");
    if (!data) data = "";

    char *method = getenv("REQUEST_METHOD");
    if (method && strcmp(method, "POST") == 0) {
        char input[200];
        fgets(input, sizeof(input), stdin);
        sscanf(input, "username=%49[^&]&password=%49s", username, password);

        FILE *fp = fopen("users.txt", "a");
        fprintf(fp, "%s,%s\n", username, password);
        fclose(fp);

        printf("<script>alert('Signup successful!');window.location.href='../railway/login.html';</script>");
    } else {
        printf("<h3>Invalid Request</h3>");
    }
    return 0;
}
