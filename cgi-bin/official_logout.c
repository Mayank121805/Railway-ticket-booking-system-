#include <stdio.h>

int main() {
    printf("Content-type:text/html\n\n");
    FILE *fp = fopen("official_session.txt", "w");
    if (fp) fclose(fp);
    printf("<script>alert('Logged out successfully!');window.location.href='../railway/official_login.html';</script>");
    return 0;
}
