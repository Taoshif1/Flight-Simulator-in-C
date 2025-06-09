# ✈️ **Flight Management System in C**  
---
## 🚀 **A Journey into High-Performance Software Engineering**

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

## ✅ Core Functionalities:

- **Flight Management**: Add ✈️ | Search 🔍 | Delete ❌ | Sort 🔃 | List 📋
- **Passenger Management**: Add 👤 | Remove 🚫 | View Details 🧾
- **Ticketing**: Book 🎫 | Cancel ❌ | Seat Management 💺
- **Crew Assignment**: Assign flight crews 👨‍✈️
- **Payments**: Basic payment operations 💳
- **Data Persistence**: All data saved in `.txt` files and loaded at launch 📂

---

## ⚡ Highlights of Implementation:

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

  - ```html/index.html``` for web-based docs
  - ```latex/refman.pdf``` for a LaTeX PDF report

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

---

## 📸 SS- 

* File Structure:
 - ![Screenshot 2025-05-22 004908](https://github.com/user-attachments/assets/904218ef-d2a1-471c-9d8c-f3f6a578840f)

* OUTPUT:

  - ![Screenshot 2025-05-22 021353](https://github.com/user-attachments/assets/1f33940e-36ff-4cfc-9c0e-94876e4996e8)
  - ![Screenshot 2025-05-22 021405](https://github.com/user-attachments/assets/b8362983-6819-4d60-82c9-34d67fc70dac)
 - ![Screenshot 2025-05-22 021414](https://github.com/user-attachments/assets/ce64803a-415a-4b21-bfd1-bb1ac93b44e0)
 - ![Screenshot 2025-05-22 021423](https://github.com/user-attachments/assets/cb434b81-6c6b-4c24-9bec-9bcf01e3d7c7)
 - ![Screenshot 2025-05-22 021430](https://github.com/user-attachments/assets/5e2735ee-72d2-4db0-ac43-7964be7c8bcc)
 - ![Screenshot 2025-05-22 021439](https://github.com/user-attachments/assets/ec6e6700-8b20-4e65-a341-b73b295e6d51)
 - ![Screenshot 2025-05-22 021449](https://github.com/user-attachments/assets/59f2f8fe-8a1a-4442-b7b0-02895d60c08d)

* Doxygen:

 - ![Screenshot 2025-05-22 235830](https://github.com/user-attachments/assets/533a4325-7e02-4aab-a6f8-06f5b004969e)
---
