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

MyVet is a veterinary clinic management application integrating a C++ / Crow backend with a React / TypeScript frontend.

---

## Features

- **Patient Management:** Track and update patient information (history, height, and weight).
- **Appointment Scheduling:** Manage clinic appointments.
- **Medical Records & Treatments:** Log treatments and costs.
- **Invoicing & Billing:** Generate invoice structures based on completed treatments.
- **Sales Logging (Ventas):** Log sales and calculate daily totals directly from the Admin Dashboard.
- **Authentication:** Salted SHA-256 password hashing and role-based JWT authorization.

---

## Technology Stack

| Component | Technology |
|---|---|
| **Backend** | [C++20](https://en.cppreference.com/w/cpp/20) / [Crow C++](https://crowcpp.org) |
| **Database** | [SQLite3](https://sqlite.org) |
| **Frontend** | [React](https://react.dev/) / [TypeScript](https://www.typescriptlang.org/) |
| **Styling** | [Tailwind CSS](https://tailwindcss.com/) |

---

## Quick Start

### Prerequisites
- **Node.js** (v16+) & **npm**
- **CMake** (v3.23+) & C++ Compiler supporting C++20
- **SQLite3** library & **Asio** headers (standalone)

---

### Running with Docker Compose (Recommended)

1. **Start the application:**
   ```bash
   ./start.sh
   ```
   *Or run:* `docker compose up --build -d`

2. **Access the application:**
   - **Frontend UI:** `http://localhost`
   - **Backend API:** `http://localhost:18080`

3. **Stop the services:**
   ```bash
   docker compose down
   ```

---

### Running Locally (Alternative)

#### Backend Setup
1. **Navigate to backend and build:**
   ```bash
   cd backend
   cmake -B build
   cmake --build build
   ```
2. **Run the server:**
   ```bash
   export JWT_SECRET="your_secure_secret"
   ./build/api
   ```

#### Frontend Setup
1. **Navigate to frontend and start:**
   ```bash
   cd frontend
   npm install
   npm run dev
   ```
   Available at `http://localhost:5173`.

---

## License

This project is licensed under the CC BY-NC 4.0 License. See the [LICENSE](https://creativecommons.org/licenses/by-nc/4.0/) file for details.

## Contact

Paul Contreras - [GitHub](https://github.com/pol-cova/)
