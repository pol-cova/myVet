# MyVet

Simple, Fast, and Secure Veterinary Administration System. Designed to streamline clinical workflows, client records, and appointment schedules.

[![GitHub license](https://img.shields.io/badge/License-CC%20BY--NC%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by-nc/4.0/)
[![C++ Standard](https://img.shields.io/badge/Language-C%2B%2B%2020-00599C.svg?logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/cpp/20)
[![React](https://img.shields.io/badge/Frontend-React%20%2F%20TypeScript-61DAFB.svg?logo=react&logoColor=black)](https://react.dev/)
[![Tailwind CSS](https://img.shields.io/badge/Styling-Tailwind%20CSS-38B2AC.svg?logo=tailwind-css&logoColor=white)](https://tailwindcss.com/)
[![SQLite](https://img.shields.io/badge/Database-SQLite-003B57.svg?logo=sqlite&logoColor=white)](https://sqlite.org/)
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square)](http://makeapullrequest.com)

---

## Overview

**MyVet** is an all-in-one veterinary clinic management application that integrates a blazing-fast **C++ / Crow** backend with a modern **React / TypeScript** frontend. It provides a robust, easy-to-use, and highly secure environment for veterinary staff, medical practitioners, and pet owners.

---

## Features

- **Patient Management:** Create, track, and update patient information (age, breed, medical history, height, and weight).
- **Appointment Scheduling:** Avoid scheduling conflicts with real-time, validation-backed appointment booking.
- **Medical Records & Treatments:** Log treatments, medical procedures, and costs securely linked to patients.
- **Invoicing & Billing:** Generate invoice structures (Facturas) based on completed treatments.
- **Sales Logging (Ventas):** Log sales and calculate daily totals directly from the Admin Dashboard.
- **Secure Authentication:** User accounts protected with salted SHA-256 password hashing and role-based JWT (JSON Web Tokens) authorization.

---

## Technology Stack

| Component | Technology | Description |
|---|---|---|
| **Backend** | [C++20](https://en.cppreference.com/w/cpp/20) | Blazing-fast performance and runtime efficiency |
| **API Framework** | [Crow C++](https://crowcpp.org) | Modern, fast microframework for C++ routing |
| **Database** | [SQLite3](https://sqlite.org) | Lightweight, single-file serverless database |
| **Authentication** | Spark Auth | Proprietary authentication helper library featuring SHA-256 and JWS tokens |
| **Frontend** | [React](https://react.dev/) | Dynamic, component-driven web UI |
| **Language** | [TypeScript](https://www.typescriptlang.org/) | Type-safety and developer productivity |
| **Styling** | [Tailwind CSS](https://tailwindcss.com/) | Clean, modern, responsive aesthetics |

---

## Repository Structure

```text
├── backend/            # C++ Crow Backend
│   ├── core/           # Database interface (SQLite wrappers)
│   ├── include/        # Third-party headers (Crow, JWT-cpp) & helper libraries
│   │   └── spark/      # Auth & JWT generation (Spark Auth library)
│   ├── utils/          # Scheduling helper functions
│   ├── main.cpp        # C++ Server Entry Point (Local server config)
│   └── api.cpp         # C++ API Handler (Unified routes and endpoints)
│
└── frontend/           # React TypeScript Frontend
    ├── src/
    │   ├── components/ # Shared UI Components (Dashboards, Modals, Navbars)
    │   ├── pages/      # Views (Login, Registration, Home)
    │   └── main.tsx    # App Entry Point & global Axios configuration
    └── tailwind.config.js
```

---

## Quick Start / Local Installation

### Prerequisites
- **Node.js** (v16+) & **npm** or **yarn**
- **CMake** (v3.23+) & a **C++ Compiler** (supporting C++20 or later)
- **SQLite3** library installed on your system
- **Asio** library headers (standalone)

---

### 🐳 Running with Docker Compose (Easiest Method)

If you have Docker installed, you can build and run both the C++ API server and the React frontend inside containers with a single command. This handles all dependencies (Asio, CMake, Node, SQLite, Nginx, etc.) automatically:

1. **Launch the startup script:**
   ```bash
   ./start.sh
   ```
   *Or directly run:* `docker compose up --build -d`

2. **Access the application:**
   - **Frontend UI:** `http://localhost` (port 80)
   - **Backend API:** `http://localhost:18080` (port 18080)

3. **Shutdown the services:**
   ```bash
   docker compose down
   ```

---

### Manual Local Setup (Alternative)

### 1. Backend Setup

1. **Navigate to the backend directory:**
   ```bash
   cd backend
   ```
2. **Configure with CMake:**
   ```bash
   cmake -B build
   ```
3. **Compile the targets:**
   ```bash
   cmake --build build
   ```
4. **Define your JWT Secret Environment Variable (Highly Recommended):**
   ```bash
   export JWT_SECRET="your_secure_random_key_here"
   ```
5. **Run the API server:**
   On startup, the backend binds to port `18080` (CORS enabled):
   ```bash
   ./build/api
   ```

---

### 2. Frontend Setup

1. **Navigate to the frontend directory:**
   ```bash
   cd ../frontend
   ```
2. **Install dependencies:**
   ```bash
   npm install
   ```
3. **Launch the development server:**
   ```bash
   npm run dev
   ```
   The site will be available at `http://localhost:5173`.

---

## Security Audit & Best Practices Implemented

- **Prepared Statements (SQLi Prevention):** Every SQL query is fully parametrized using `sqlite3_prepare_v2` and bound dynamically, ensuring absolute safety against SQL Injection attacks.
- **Secure Password Hashing:** User passwords are encrypted with unique random 16-character salts and SHA-256, protecting credentials at rest.
- **JWT Verification & Role Access:** API endpoints are secured. Endpoints like viewing all users or modifying clinic logs require active `admin` role-based tokens.
- **Broken Object Level Authorization (BOLA) Prevention:** User routes dynamically check ownership attributes (e.g. verifying that a user is requesting or editing their *own* pets' data), preventing privilege escalation.
- **Dynamic Local CORS Mapping:** CORS rules automatically echo local development origins safely, removing browser preflight blocks for developers.

---

## Contributing

Contributions are welcome! If you have suggestions or want to add a feature:
1. **Fork** the repository.
2. Create a feature branch: `git checkout -b feature/amazing-feature`.
3. Commit your changes: `git commit -m 'Add amazing feature'`.
4. Push to your branch: `git push origin feature/amazing-feature`.
5. Open a **Pull Request**.

---

## License

This project is licensed under the **Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)** license. See the [LICENSE](https://creativecommons.org/licenses/by-nc/4.0/) details for commercial restrictions.

## Contact & Support

Created by [Paul Contreras](https://github.com/pol-cova/). For inquiries, feel free to drop a message!
