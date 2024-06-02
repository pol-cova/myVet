# MyVet
Simple, Fast and Secure Veterinary Administration System

<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/pol-cova/myVet">MyVet System</a> by <a rel="cc:attributionURL dct:creator" property="cc:attributionName" href="https://github.com/pol-cova/">Paul Contreras</a> is licensed under <a href="https://creativecommons.org/licenses/by-nc/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-NC 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/nc.svg?ref=chooser-v1" alt=""></a></p>

## Overview
MyVet is a comprehensive veterinary administration system designed to streamline the management of veterinary practices. This application offers robust features for patient management, appointment scheduling, and medical record keeping, ensuring a seamless experience for both staff and clients.

## Features
- **Patient Management:** Track and manage patient information including medical history, treatments, and prescriptions.
- **Appointment Scheduling:** Efficiently schedule, reschedule, and manage appointments.
- **Medical Records:** Securely store and access detailed medical records and treatment histories.
- **User Authentication:** Secure login system to protect sensitive information.
- **Reporting:** Generate various reports for insights into clinic operations.

## Technology Stack

### Backend
- **Language:** C++
- **Framework:** Crow
- **Database:** SQLite

### Frontend
- **Framework:** React
- **Language:** TypeScript
- **Styling:** Tailwind CSS

## Installation

### Prerequisites
- **Node.js** (for frontend)
- **npm** or **yarn** (for frontend package management)
- **C++ Compiler** (compatible with C++11 or later)
- **SQLite** (database)

### Backend Setup
1. Clone the repository:
    ```bash
    git clone https://github.com/pol-cova/myVet.git
    cd myVet/backend
    ```
2. Build the backend:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```
3. Run the backend server:
    ```bash
    ./myVetBackend
    ```

### Frontend Setup
1. Navigate to the frontend directory:
    ```bash
    cd ../frontend
    ```
2. Install dependencies:
    ```bash
    npm install
    ```
3. Start the frontend development server:
    ```bash
    npm run dev
    ```

.

## License
This project is licensed under the CC BY-NC 4.0 License. See the [LICENSE](https://creativecommons.org/licenses/by-nc/4.0/?ref=chooser-v1) file for more details.

## Contact
For any questions or feedback, please reach out to [Paul Contreras](https://github.com/pol-cova/).

---

By following this README, you should be able to set up and run the MyVet system on your local machine. Happy coding!
