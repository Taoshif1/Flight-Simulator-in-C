# ✈️ Flight Management System in C  
---

## 🚀 A Journey into High-Performance, Low-Level Software Engineering

Welcome to the repository for my **Flight Management System**, a console-based C project crafted from the ground up – line by line – in **Notepad**. That’s right. No fancy IDEs. Just raw logic, hard-earned syntax and pure dedication.

This isn’t just a project. It’s the story of one developer mastering the essentials of software engineering through **modular architecture**, **memory-efficient data structures** and **professional-grade documentation**.

---

## 📌 About the Project

This Flight Management System is designed to simulate core operations of an airline reservation platform with emphasis on:

- **Efficiency** (zero memory waste),
- **Maintainability** (clean modular code),
- **Documentation** (auto-generated using Doxygen).

Every feature, function and file was written with purpose & intense brainstorming. From the use of **bit-fields** and **bit-mapped seat allocation**, to robust **file handling**, this system is built like a tank—ready for production-level challenges.

---

## 🧠 Key Learnings & Motivation

- Learned to **manually configure and use GCC** to compile multi-file C programs
- Understood real-world use of **pointers**, **structs**, **enums**, **macros** and **dynamic memory allocation**
- Mastered the **Doxygen** documentation pipeline including **MiKTeX** for LaTeX PDF generation
- Experienced what it means to go **from scratch to executable**—a skill every hardcore CSE student needs 🔥

---

## ⚙️ System Features

### ✅ Core Functionalities:
- **Flight Management**: Add ✈️ | Search 🔍 | Delete ❌ | Sort 🔃 | List 📋
- **Passenger Management**: Add 👤 | Remove 🚫 | View Details 🧾
- **Ticketing**: Book 🎫 | Cancel ❌ | Seat Management 💺
- **Crew Assignment**: Assign flight crews 👨‍✈️
- **Payments**: Basic payment operations 💳
- **Data Persistence**: All data saved in `.txt` files and loaded at launch 📂

---

## 🧠 Technical Brilliance

---

### ⚡ Highlights of Implementation:

| Area | Implementation |
|------|----------------|
| **Modularity** | Separate `.c`/`.h` files for each module: `main`, `flight`, `passenger`, `ticket`, `crew`, `payment`, `common` |
| **Bit-Fields** | Used in `DateTime` struct for max memory efficiency |
| **Bit-Mapped Seat Management** | Seats stored as **bit arrays** to save space |
| **Dynamic Memory Allocation** | `malloc`, `free`, and `realloc` for runtime memory resizing |
| **File I/O** | Robust `fopen`, `fscanf`, `fprintf`, `strtok` implementations |
| **Input Validation** | Custom utility for cleaning input buffer, checking `scanf` returns, etc. |
| **Macros & Enums** | Clean constant definitions and structured control flows |

---

## 🧾 Doxygen Documentation

Every file, function, struct and constant is documented using Doxygen-style comments (`/** ... */`). This project is more than just code – it’s **engineered documentation**.

---

### 📚 How to Generate Docs

1. Install **Doxygen** and **MiKTeX**
2. In your terminal, run:
   ```
   doxygen Doxyfile
    ```
3. Open:
  ```
  html/index.html for web-based docs
  latex/refman.pdf for a LaTeX PDF report
  ```

---

## 🛠️ Compile & Run Instructions

1. To compile the system manually:
```
gcc main.c flight.c passenger.c ticket.c crew.c payment.c -o flight_system.exe
```

2. Then, run it with:
  ```
  ./flight_system.exe
  ```
💡 Note: The system is console-based, so interact via terminal.

---

## ✍️ Author & Creator

**👨‍💻 Gazi Taoshif**
**B.Sc. in Computer Science & Engineering**

> This project was my training ground. It taught me not just to write code—but to build systems—real, scalable, optimized software. It made me fall in love with engineering from scratch.

---

# **📣 “I wrote this entire system in Notepad. It wasn’t easy—but it was worth it.”**
