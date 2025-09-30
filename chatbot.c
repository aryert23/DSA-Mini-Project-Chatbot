#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FAQ 8
#define MAX_KEYWORDS 3
#define MAX_LEN 100
#define MAX_HISTORY 10
#define MAX_QUEUE 20

// FAQ structure
typedef struct {
    char keywords[MAX_KEYWORDS][MAX_LEN];
    char answer[MAX_LEN];
} FAQ;

// Queue for unanswered queries
typedef struct {
    char query[MAX_LEN];
    char ticketID[20];
} Ticket;

Ticket queue[MAX_QUEUE];
int front = -1, rear = -1;

// Chat history
char history[MAX_HISTORY][2][MAX_LEN]; // [user/bot]
int historyCount = 0;

// Function to add chat to history
void addHistory(const char *user, const char *bot) {
    if (historyCount < MAX_HISTORY) {
        strcpy(history[historyCount][0], user);
        strcpy(history[historyCount][1], bot);
        historyCount++;
    }
}

// Function to show chat history
void showHistory() {
    printf("\n📜 Chat History:\n");
    for (int i = 0; i < historyCount; i++) {
        printf("You: %s\n", history[i][0]);
        printf("Bot: %s\n", history[i][1]);
    }
}

// Add ticket to queue
void enqueue(const char *query) {
    if (rear == MAX_QUEUE - 1) {
        printf("Queue is full! Cannot forward more queries.\n");
        return;
    }
    if (front == -1) front = 0;

    rear++;
    strcpy(queue[rear].query, query);

    // Generate ticket ID
    sprintf(queue[rear].ticketID, "SUP%04d", rear + 1);
    printf("❌ Sorry, I don’t know that. Forwarding to support...\n");
    printf("📩 Your ticket ID is %s\n", queue[rear].ticketID);
}

// Random joke function
void tellJoke() {
    const char *jokes[] = {
        "😂 Why don’t programmers like nature? Too many bugs!",
        "🤣 Why did the computer go to the doctor? Because it caught a virus!",
        "😆 Why do Java developers wear glasses? Because they don’t C#!"
    };
    int n = rand() % 3;
    printf("%s\n", jokes[n]);
}

// Main
int main() {
    srand(time(NULL));

    FAQ faqs[MAX_FAQ] = {
        {{"hello", "hi", "hey"}, "👋 Hey there! How can I help you?"},
        {{"price", "cost", "rate"}, "💰 Our products range from Rs. 500 to Rs. 5000."},
        {{"delivery", "shipping", "courier"}, "📦 Delivery takes 3-5 business days."},
        {{"return", "refund", "exchange"}, "🔄 You can return products within 7 days."},
        {{"support", "help", "contact"}, "☎️ You can email us at support@example.com."},
        {{"payment", "upi", "card"}, "💳 We accept UPI, Net Banking, and Cards."},
        {{"order", "track", "status"}, "📍 You can track your order in 'My Orders'."},
        {{"bye", "goodbye", "exit"}, "👋 Bye-bye! Come back soon 😁"}
    };

    char input[MAX_LEN];
    printf("🤖 Welcome to FunBot 1.0!\n");
    printf("Type 'exit' to quit, 'history' to see chat log, or 'joke' for fun!\n\n");

    while (1) {
        printf("You: ");
        fgets(input, MAX_LEN, stdin);
        input[strcspn(input, "\n")] = '\0'; // remove newline

        if (strcmp(input, "exit") == 0) {
            printf("Bot: 👋 Goodbye, have a nice day!\n");
            break;
        }
        if (strcmp(input, "history") == 0) {
            showHistory();
            continue;
        }
        if (strcmp(input, "joke") == 0) {
            printf("Bot: ");
            tellJoke();
            addHistory(input, "Told a joke 🤣");
            continue;
        }

        int found = 0;
        for (int i = 0; i < MAX_FAQ; i++) {
            for (int j = 0; j < MAX_KEYWORDS; j++) {
                if (strstr(input, faqs[i].keywords[j]) != NULL) {
                    printf("Bot: %s\n", faqs[i].answer);
                    addHistory(input, faqs[i].answer);
                    found = 1;
                    break;
                }
            }
            if (found) break;
        }

        if (!found) {
            enqueue(input);
            addHistory(input, "Forwarded to support ❌");
        }
    }

    return 0;
}

/*📌 FAQ List
Greeting
Keywords: "hello", "hi", "hey"
Answer: "👋 Hey there! How can I help you?"
Price
Keywords: "price", "cost", "rate"
Answer: "💰 Our products range from Rs. 500 to Rs. 5000."
Delivery / Shipping
Keywords: "delivery", "shipping", "courier"
Answer: "📦 Delivery takes 3-5 business days."
Return / Refund / Exchange
Keywords: "return", "refund", "exchange"
Answer: "🔄 You can return products within 7 days."
Support / Help
Keywords: "support", "help", "contact"
Answer: "☎️ You can email us at support@example.com."
Payment
Keywords: "payment", "upi", "card"
Answer: "💳 We accept UPI, Net Banking, and Cards."
Order Tracking
Keywords: "order", "track", "status"
Answer: "📍 You can track your order in 'My Orders'."
Goodbye
Keywords: "bye", "goodbye", "exit"
Answer: "👋 Bye-bye! Come back soon 😁"*/