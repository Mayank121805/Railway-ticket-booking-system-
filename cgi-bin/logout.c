#include <stdio.h>

int main() {
    printf("Content-type:text/html\n\n");
    FILE *fp = fopen("current_user.txt", "w");
    if (fp) fclose(fp);
    printf("<script>alert('Logged out successfully!');window.location.href='../railway/dashboard.html';</script>");
    return 0;
}
