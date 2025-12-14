#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

int main() {
    printf("Content-Type: text/html\n\n");

    char queryString[300] = "";
    char query[200] = "";

    // ---- Fetch Query Parameter ----
    char *data = getenv("REQUEST_METHOD");

    if (data && strcmp(data, "POST") == 0) {
        int len = atoi(getenv("CONTENT_LENGTH"));
        fread(queryString, 1, len, stdin);
        sscanf(queryString, "query=%199s", query);
    } 
    else if (data && strcmp(data, "GET") == 0) {
        strcpy(queryString, getenv("QUERY_STRING"));
        sscanf(queryString, "query=%199s", query);
    }

    // URL decode "+" -> space
    for (int i = 0; query[i]; i++)
        if (query[i] == '+') query[i] = ' ';

    toLower(query);

    // ---- Output HTML ----
    printf("<html><body style='background:#0f172a; color:white; font-family:Poppins; text-align:center;'>");

    if (strstr(query, "book")) {
        printf("<h2>Redirecting to Book Ticket...</h2>");
        printf("<script>window.location.href='../railway/book_ticket.html'</script>");
    }
    else if (strstr(query, "cancel")) {
        printf("<h2>Redirecting to Cancel Ticket...</h2>");
        printf("<script>window.location.href='../railway/cancel_ticket.html'</script>");
    }
    else if (strstr(query, "view")) {
        printf("<h2>Redirecting to View Tickets...</h2>");
        printf("<script>window.location.href='../railway/view_tickets.html'</script>");
    }
    else if (strstr(query, "official")) {
        printf("<h2>Redirecting to Officials Area...</h2>");
        printf("<script>window.location.href='../railway/officials.html'</script>");
    }
    else {
        printf("<h2>No matching option found!</h2>");
        printf("<p>Try: book, cancel, view, official</p>");
    }

    printf("</body></html>");
    return 0;
}
