#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_CONFIRMED 10

/* -------- URL Decode Function -------- */
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
    char name[50], source[50], destination[50];
    int age;
    char ticket_no[20];

    printf("Content-type:text/html\n\n");

    /* -------- Read POST Data -------- */
    char input[300] = {0};
    char decoded[300] = {0};

    fgets(input, sizeof(input), stdin);
    url_decode(input, decoded);

    sscanf(decoded,
           "name=%49[^&]&age=%d&source=%49[^&]&destination=%49[^&]",
           name, &age, source, destination);

    /* -------- Count Confirmed Tickets -------- */
    FILE *fp = fopen("bookings.txt", "a+");
    if (!fp) {
        printf("<script>alert('Server error!');</script>");
        return 0;
    }

    int confirmed = 0;
    char line[300];
    rewind(fp);
    while (fgets(line, sizeof(line), fp)) confirmed++;

    /* -------- Generate Ticket No -------- */
    srand(time(NULL));
    sprintf(ticket_no, "TK%d", 10000 + rand() % 90000);

    /* -------- CONFIRMED OR WAITING -------- */
    if (confirmed < MAX_CONFIRMED) {

        /* CONFIRMED booking */
        fprintf(fp, "%s,%s,%d,%s,%s,CONFIRMED\n",
                ticket_no, name, age, source, destination);
        fclose(fp);

        printf("<script>");
        printf("alert('Ticket CONFIRMED! Ticket No: %s');", ticket_no);
        printf("window.location.href='/railway/thank_you.html';");
        printf("</script>");

    } else {
        fclose(fp);

        /* WAITING booking */
        FILE *wl = fopen("waiting_list.txt", "a+");
        if (!wl) {
            printf("<script>alert('Server error!');</script>");
            return 0;
        }

        fprintf(wl, "%s,%s,%d,%s,%s,WAITING\n",
                ticket_no, name, age, source, destination);
        fclose(wl);

        printf("<script>");
        printf("alert('All confirmed tickets are full! You are in WAITING LIST. Ticket No: %s');", ticket_no);
        printf("window.location.href='/railway/waiting.html';");
        printf("</script>");
    }

    return 0;
}
