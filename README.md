# DSA Mini Project – Fun Customer Service Chatbot 🤖

## 📌 Project Overview
A simple, fun chatbot built in C for the DSA mini-project.  
It answers common customer queries like delivery, returns, payment, etc.  
If the query is unknown, it forwards it to human support using a queue.  

## 🛠️ Data Structures Used
- **Array of Structures** → FAQ list (keywords + answers)  
- **Queue** → Forward unanswered queries with Ticket IDs  
- **Array** → Chat history  

## 🚀 Features
- FAQ keyword matching  
- Forwarding unknown queries with Ticket IDs  
- Chat history (last 10 queries)  
- Fun responses (emojis + random jokes 🤣)  

## ▶️ How to Run
```bash
gcc chatbot.c -o chatbot
./chatbot
🤖 Welcome to FunBot 1.0!
You: hello
Bot: 👋 Hey there! How can I help you?
You: refund not working
Bot: ❌ Sorry, I don’t know that. Forwarding to support...
📩 Your ticket ID is SUP0001
