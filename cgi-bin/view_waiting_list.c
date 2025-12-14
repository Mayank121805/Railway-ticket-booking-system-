#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    printf("Content-type:text/html\n\n");

    /* ===== HTML + CSS ===== */
    printf("<!DOCTYPE html>");
    printf("<html><head><meta charset='UTF-8'>");
    printf("<title>Waiting List</title>");

    printf("<style>");
    printf("body{"
           "margin:0;"
           "padding:20px;"
           "font-family:Poppins,sans-serif;"
           "background:linear-gradient(135deg,#0a0f1f,#111827,#1e293b);"
           "color:#f1f5f9;"
           "}");
    printf("h2{"
           "text-align:center;"
           "margin-bottom:20px;"
           "color:#60a5fa;"
           "}");
    printf("table{"
           "width:100%%;"
           "border-collapse:collapse;"
           "background:rgba(17,24,39,0.9);"
           "border-radius:12px;"
           "overflow:hidden;"
           "}");
    printf("th,td{"
           "padding:12px;"
           "text-align:center;"
           "border-bottom:1px solid rgba(255,255,255,0.15);"
           "}");
    printf("th{"
           "background:#0f172a;"
           "color:#93c5fd;"
           "}");
    printf("tr:hover{"
           "background:rgba(59,130,246,0.15);"
           "}");
    printf("</style>");

    printf("</head><body>");

    FILE *fp = fopen("waiting_list.txt", "r");
    if (!fp) {
        printf("<h3 style='text-align:center;'>No passenger is in waiting yet.</h3>");
        printf("</body></html>");
        return 0;
    }

    printf("<h2>Waiting List Passengers</h2>");
    printf("<table>");
    printf("<tr>"
           "<th>Ticket No</th>"
           "<th>Name</th>"
           "<th>Age</th>"
           "<th>From</th>"
           "<th>To</th>"
           "</tr>");

    char line[256];
    char ticket[20], name[50], src[50], dst[50], status[20];
    int age;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%[^,],%[^,],%d,%[^,],%[^,],%s",
                   ticket, name, &age, src, dst, status) == 6) {

            printf("<tr>"
                   "<td>%s</td>"
                   "<td>%s</td>"
                   "<td>%d</td>"
                   "<td>%s</td>"
                   "<td>%s</td>"
                   "</tr>",
                   ticket, name, age, src, dst);
        }
    }

    printf("</table>");
    fclose(fp);

    printf("</body></html>");
    return 0;
}
