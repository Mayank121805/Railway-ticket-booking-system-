#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CONFIRMED_FILE "bookings.txt"
#define WAITING_FILE "waiting_list.txt"

/* URL Decode */
void url_decode(char *src, char *dest) {
    char a, b;
    while (*src) {
        if ((*src == '%') &&
            ((a = src[1]) && (b = src[2])) &&
            (isxdigit(a) && isxdigit(b))) {

            a = (a >= 'A') ? ((a & 0xdf) - 'A' + 10) : (a - '0');
            b = (b >= 'A') ? ((b & 0xdf) - 'A' + 10) : (b - '0');

            *dest++ = 16 * a + b;
            src += 3;
        } else if (*src == '+') {
            *dest++ = ' ';
            src++;
        } else {
            *dest++ = *src++;
        }
    }
    *dest = '\0';
}

/* Search function — ticket ONLY */
int search_file(const char *filename, char *ticket) {   // ★ name removed
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        char t[50], n[100], src[50], dest[50], status[20];
        int age;

        sscanf(line, "%[^,],%[^,],%d,%[^,],%[^,],%s",
               t, n, &age, src, dest, status);

        if (strcmp(ticket, t) == 0) {    // ★ ONLY ticket comparison
            printf("<p><b>Ticket No:</b> %s</p>", t);
            printf("<p><b>Name:</b> %s</p>", n);
            printf("<p><b>Age:</b> %d</p>", age);
            printf("<p><b>Source:</b> %s</p>", src);
            printf("<p><b>Destination:</b> %s</p>", dest);
            printf("<p><b>Status:</b> %s</p>", status);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int main() {
    char *lenStr = getenv("CONTENT_LENGTH");
    int len = lenStr ? atoi(lenStr) : 0;

    char post_data[1024] = {0};
    char decoded[1024] = {0};

    fread(post_data, 1, len, stdin);
    url_decode(post_data, decoded);

    char ticket[50];
    sscanf(decoded, "ticket_id=%[^&]", ticket);   // ★ name removed

    /* ===== HTML HEADER (UNCHANGED) ===== */
    printf("Content-Type:text/html\n\n");
    printf("<html><head>");
    printf("<title>Booking Status</title>");
    printf("<link rel='stylesheet' href='../railway/waiting_status.css'>");
    printf("</head><body>");
    printf("<div class='container'>");
    printf("<h2>Booking Status</h2>");

    /* ===== SEARCH CONFIRMED FIRST ===== */
    if (search_file(CONFIRMED_FILE, ticket)) {
        /* Found in confirmed */
    }
    /* ===== ELSE SEARCH WAITING ===== */
    else if (search_file(WAITING_FILE, ticket)) {
        /* Found in waiting */
    }
    else {
        printf("<p class='error'>Ticket not found!</p>");
    }

    printf("<br><a href='../railway/waiting.html'>Check Another</a>");
    printf("</div></body></html>");

    return 0;
}
