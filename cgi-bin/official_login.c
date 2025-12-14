#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* URL Decode */
void url_decode(char *src, char *dest) {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            isxdigit(a) && isxdigit(b)) {

            a = (a >= 'A') ? ((a & 0xdf) - 'A' + 10) : (a - '0');
            b = (b >= 'A') ? ((b & 0xdf) - 'A' + 10) : (b - '0');

            *dest++ = 16 * a + b;
            src += 3;
        }
        else if (*src == '+') {
            *dest++ = ' ';
            src++;
        }
        else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

int main() {
    printf("Content-Type:text/html\n\n");

    /* Read POST data */
    char raw[256] = {0}, decoded[256] = {0};
    fgets(raw, sizeof(raw), stdin);
    url_decode(raw, decoded);

    char official_id[50], password[50];
    sscanf(decoded, "official_id=%49[^&]&password=%49s", official_id, password);

    FILE *fp = fopen("official_login.txt", "r");
    if (!fp) {
        printf("<script>alert('Server error!');history.back();</script>");
        return 0;
    }

    char line[100];
    int authenticated = 0;

    while (fgets(line, sizeof(line), fp)) {
        char id[50], pass[50];
        sscanf(line, "%[^|]|%s", id, pass);

        if (strcmp(id, official_id) == 0 &&
            strcmp(pass, password) == 0) {
            authenticated = 1;
            break;
        }
    }
    fclose(fp);

    if (authenticated) {
        /* Create session */
        FILE *sess = fopen("officials_session.txt", "w");
        fprintf(sess, "%s", official_id);
        fclose(sess);

        printf("<script>");
        printf("alert('Officials login successful!');");
        printf("window.location.href='../railway/official_dashboard.html';");
        printf("</script>");
    } else {
        printf("<script>");
        printf("alert('Invalid Official ID or Password');");
        printf("window.location.href='../railway/officials_login.html';");
        printf("</script>");
    }

    return 0;
}
